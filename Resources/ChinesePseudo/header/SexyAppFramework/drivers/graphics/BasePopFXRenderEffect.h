#ifndef BASEPOPFXRENDEREFFECT_H_INCLUDED
#define BASEPOPFXRENDEREFFECT_H_INCLUDED

#include "RenderEffect.h"
#include "RenderDevice.h"
#include "drivers/graphics/PopFXFormat.h"

using namespace PopFXFormat;

namespace Sexy
{
	template <typename RenderEffectPassT>
	class BasePopFXRenderEffect : public RenderEffect
	{
	public:

		struct RenderEffectTechnique
		{
			std::vector<RenderEffectPassT> mPasses;
			bool mIsValid; //for now based on if the shaders compile
		};

		class ParamData
		{
		public:
			std::vector<float> mFloatData;
			
			void SetValue(const float* inFloatData, ulong inFloatCount)
			{
				mFloatData.resize(inFloatCount);
				memcpy(&mFloatData[0], inFloatData, inFloatCount*sizeof(float));
				assert(mFloatData.size() == inFloatCount);
				while (mFloatData.size() & 3)
					mFloatData.push_back(0.f); // pad out zeros to 4-float vector length
			}
		};

		class ParamCollection
		{
		public:
			typedef std::map<std::string, ParamData> ParamMap;
			ParamMap mParamMap;
			
			ParamData* GetParamNamed(const std::string& inName, bool inAllowCreate = true)
			{
				typename ParamMap::iterator it = mParamMap.find(inName);
				if (it != mParamMap.end())
					return &it->second;
				
				if (inAllowCreate)
				{
					mParamMap[inName] = ParamData();
					return GetParamNamed(inName, false);
				}
				else
				{
					return false;
				}
			}
		};
		
		BasePopFXRenderEffect(RenderDevice3D* theDevice, RenderEffectDefinition* theDefinition)
		{
			mDevice = theDevice;
			mDefinition = theDefinition;
			
			mBuffer = &mDefinition->mData[0];
			mCurrentTechnique = NULL;
			mBeginPassRefCount = 0;
			
			mIsValid = false;
		}
		
		bool Initialize()
		{
			mHeader = (PopFXHeader*)mBuffer;
			if (mHeader->id != PopFXID) return false;
			
			
			//compile shaders for all of these passes
			//need to build a 2d and 3d version of each (if there is a pixel shader but no vertex shader)
			for (uint32 i=0; i<mHeader->num_techniques; i++)
			{
				PopFXTechnique* aTechnique = GetPopFXTechnique(i);
				
				if (!InitializeTechnique(aTechnique))
				{
					OutputDebug("Technique %s could not be initialized\n",GetPopFXString(aTechnique->name));
				}
			}

			SetCurrentTechnique("Default");
			return true;
		}
		
		// General effect information
		virtual RenderDevice3D* GetDevice(){ return mDevice; };
		
		virtual RenderEffectDefinition* GetDefinition(){ return mDefinition; };
		
		virtual void SetParameter(const std::string& inParamName, const float* inFloatData, ulong inFloatCount)
		{
			//have to add it to a list of params to update, because these are shared really...
			ParamData* aParam = mParams.GetParamNamed(inParamName, true);
			aParam->SetValue(inFloatData, inFloatCount);
			
			if (mBeginPassRefCount)
			{
				if (mCurrentTechnique!=NULL)
				{
					UpdateParams();
				}
			}
		}
		
		virtual void SetMatrix(const std::string& inParamName, const float* inValue)
		{
			SetParameter(inParamName, inValue, 16);
		}
		
		virtual void GetParameterBySemantic(ulong/*EStandardConstantSemantic*/ inSemantic, float* outFloatData, ulong inMaxFloatCount)
		{
		}
		
		virtual void SetCurrentTechnique(const std::string& inName, bool inCheckValid = true)
		{
			//jvw todo : needs fallback support
			mCurrentTechnique = GetPopFXTechnique(inName.c_str());
			if (mCurrentTechnique != NULL)
			{
				//for debugging
				const char* name = GetPopFXString(mCurrentTechnique->name);
				//OutputDebug("shader name is %s\n",name);
				//check for fallback and validity...
				if (!mTechniques[mCurrentTechnique->technique_number].mIsValid)
				{
					mCurrentTechnique = NULL;
				}
			}
		}
		
		virtual std::string GetCurrentTechniqueName()
		{
			return mCurrentTechnique!=NULL ? GetPopFXString(mCurrentTechnique->name) : "";
		}
		
		virtual int Begin(HRunHandle& outRunHandle, const HRenderContext& inRenderContext = HRenderContext((void*)0))
		{
			HRenderContext aContext = inRenderContext;
			if (aContext.IsValid())
			{
				mDevice->SetCurrentContext(aContext);
			}
			else 
			{
				aContext = mDevice->GetCurrentContext();
			}
			
			outRunHandle = aContext.GetPointer();
			
			mCurrentPass = 0;
			if (mCurrentTechnique!=NULL)
			{
				
				return mCurrentTechnique->num_passes;
			}
			else 
			{
				return 1;
			}
		}
		virtual void SetShadersForPass(RenderEffectPassT &pass) = 0;

		virtual void BeginPass(const HRunHandle& inRunHandle, int inPass)
		{
			mDevice->SetCurrentContext(HRenderContext(inRunHandle));
			++mBeginPassRefCount;
			mCurrentPass = inPass;
			mDevice->PushState();
			
			if (mCurrentTechnique!=NULL)
			{
				//PopFXPass* aPass = GetPopFXPass(mCurrentTechnique->pass_begin + inPass);

				//begin the pass here
				RenderEffectPassT& aPassData = mTechniques[mCurrentTechnique->technique_number].mPasses[inPass];
				
//				if (aPassData.mProgram!=0)
//				{
					mDevice->Flush( RenderDevice3D::FLUSHF_BufferedTris );
					
					SetShadersForPass(aPassData);

					//set params... (note may have to commit to make sure the program is set)
					UpdateParams();
//				}
			}
		}
		virtual void EndPass(const HRunHandle& inRunHandle, int inPass)
		{
			mDevice->SetCurrentContext(HRenderContext(inRunHandle));
			
			if (mCurrentTechnique!=NULL)
			{
				//PopFXPass* aPass = GetPopFXPass(mCurrentTechnique->pass_begin + inPass);
			}
			
			mDevice->PopState();
			--mBeginPassRefCount;
		}
		
		virtual void End(const HRunHandle& inRunHandle)
		{
			mDevice->SetCurrentContext(HRenderContext(inRunHandle));
			
			if (mCurrentTechnique!=NULL)
			{
				//end the technique here
			}
		}
		virtual bool PassUsesVertexShader(int inPass)
		{
			if (mCurrentTechnique!=NULL)
			{
				PopFXPass* aPass = GetPopFXPass(mCurrentTechnique->pass_begin + inPass);
				return aPass->vertex_shader!=EmptyIndex;
			}
			else 
			{
				return false;
			}
		}

		virtual bool PassUsesPixelShader(int inPass)
		{
			if (mCurrentTechnique!=NULL)
			{
				PopFXPass* aPass = GetPopFXPass(mCurrentTechnique->pass_begin + inPass);
				return aPass->pixel_shader!=EmptyIndex;
			}
			else 
			{
				return false;
			}
		}
		
	protected:
		bool InitializeTechnique(PopFXTechnique* theTechnique)
		{
			mTechniques.push_back(RenderEffectTechnique());
			RenderEffectTechnique& aTechData = mTechniques.back();

			for (uint32 i=0; i<theTechnique->num_passes; i++)
			{
				PopFXPass* aPass = GetPopFXPass(i);
				
				if (!this->InitializePass(aPass,aTechData))
				{
					aTechData.mIsValid = false;
					return false;
				}
			}
			
			aTechData.mIsValid = true;
			return true;
		}
		virtual bool InitializePass(PopFXPass* thePass, RenderEffectTechnique& theTechData) = 0;
		
		virtual void UpdateParams() = 0;
		
		PopFXTechnique* GetPopFXTechnique(const char* theName)
		{
			//if this is too slow, a compiled map could be added into popfx
			for (uint32 i=0; i<mHeader->num_techniques; i++)
			{
				PopFXTechnique* aTech = GetPopFXTechnique(i);
				if (stricmp(GetPopFXString(aTech->name),theName)==0)
				{
					return aTech;
				}
			}
			return NULL;
		}
		
		inline PopFXTechnique* GetPopFXTechnique(int theIndex)
		{
			return (PopFXTechnique*)(mBuffer + mHeader->technique_table + theIndex * mHeader->technique_size);
		}
		
		inline PopFXPass* GetPopFXPass(int theIndex)
		{
			return (PopFXPass*)(mBuffer + mHeader->pass_table + theIndex * mHeader->pass_size);
		}
		
		inline PopFXShader* GetPopFXShader(int theIndex)
		{
			return (PopFXShader*)(mBuffer + mHeader->shader_table + theIndex * mHeader->shader_size);
		}
		
		inline PopFXShaderParam* GetPopFXShaderParam(int theIndex)
		{
			return (PopFXShaderParam*)(mBuffer + mHeader->shader_param_table + theIndex * mHeader->shader_param_size);
		}

		inline const char* GetPopFXString(int theIndex)
		{
			PopFXString* aString = (PopFXString*)(mBuffer + mHeader->string_table + theIndex * mHeader->string_size);
			//assert on format (should only be 0 for this function) ??
			return (const char*)(mBuffer + mHeader->string_data_offset + aString->offset);
		}
		
	protected:
		
		RenderDevice3D* mDevice;
		RenderEffectDefinition* mDefinition;
		PopFXTechnique* mCurrentTechnique;
		
		uint8* mBuffer;
		PopFXHeader* mHeader;
		
		bool mIsValid;
		
		std::vector<RenderEffectTechnique> mTechniques;
		
		int mBeginPassRefCount;
		ParamCollection mParams;
		int mCurrentPass;
	};
};

#endif
