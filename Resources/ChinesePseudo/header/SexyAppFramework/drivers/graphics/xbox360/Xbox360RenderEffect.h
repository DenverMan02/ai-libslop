#ifndef XBOX360RENDEREFFECT_H_INCLUDED
#define XBOX360RENDEREFFECT_H_INCLUDED

#include "RenderEffect.h"

#include "Xbox360RenderDevice.h"
#include "DeviceStateConstants.h"

#include "SexyAppBase.h"
#include "Buffer.h"

namespace Sexy
{

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

class Xbox360EffectStateManager
: public ID3DXEffectStateManager
{
public:
	enum ECommand
	{
		CMD_None=0,
		CMD_SetRenderState			= 1, // dword state, dword value
		CMD_SetSamplerState			= 2, // byte sampler, dword state, dword value
		CMD_SetTextureStageState	= 3, // byte stage, dword state, dword value
	};

	ULONG mRefCount;
	IDirect3DDevice9* mDevice;
	Buffer* mBuffer;
	std::string mErrorStr;
	
	Xbox360EffectStateManager(IDirect3DDevice9 *inDevice, Buffer* inBuffer) :
	mDevice(inDevice),
	mBuffer(inBuffer),
	mRefCount(1)
	{}

	void Reset()
	{
		mErrorStr.clear();
	}

	void Log(const std::string& inStr)
	{
		OutputDebug("STATEMAN: %s\n",inStr.c_str());
	}

	void Error(const std::string& inStr)
	{
		if (mErrorStr.empty())
			mErrorStr = inStr;
	}

	/*
		IUnknown
	*/
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject)
	{
		Log("QueryInterface");
		return E_NOINTERFACE;
	}
	ULONG __stdcall AddRef(void)
	{
		Log("AddRef");
		++mRefCount;
		return mRefCount;
	}
	ULONG __stdcall Release(void)
	{
		Log("Release");
		if (mRefCount)
		{
			--mRefCount;
			return mRefCount;
		}
		else
		{
			DBG_ASSERTE(false && "Xbox360EffectStateManager is stack-allocated; how are we getting here?");
			delete this;
			return 0;
		}
	}

	/*
		ID3DXEffectStateManager
	*/
	HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable)
	{
		Log(StrFormat("LightEnable: %d, %d", Index, Enable));
		Error("Fixed-function lighting parameters should not be set directly in fx files");
		return S_OK;
	}
	HRESULT __stdcall SetFVF(DWORD FVF)
	{
		Log(StrFormat("SetFVF: %d", FVF));
		Error("Vertex format should not be set directly in fx files");
		return S_OK;
	}
	HRESULT __stdcall SetLight(DWORD Index, const D3DLIGHT9* pLight)
	{
		Log(StrFormat("SetLight: %d", Index));
		Error("Fixed-function lighting parameters should not be set directly in fx files");
		return S_OK;
	}
	HRESULT __stdcall SetMaterial(const D3DMATERIAL9* pMaterial)
	{
		Log("SetMaterial:");
		Error("Fixed-function lighting parameters should not be set directly in fx files");
		return S_OK;
	}
	HRESULT __stdcall SetNPatchMode(FLOAT nSegments)
	{
		Log(StrFormat("SetNPatchMode: %f", nSegments));
		Error("NPatchMode is not supported in our framework");
		return S_OK;
	}
	HRESULT __stdcall SetPixelShader(IDirect3DPixelShader9* pShader)
	{
		Log("SetPixelShader:");
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetPixelShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT RegisterCount)
	{
		Log(StrFormat("SetPixelShaderConstantB: %d, %d", StartRegister, RegisterCount));
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetPixelShaderConstantF(UINT StartRegister, const FLOAT* pConstantData, UINT RegisterCount)
	{
		Log(StrFormat("SetPixelShaderConstantF: %d, %d", StartRegister, RegisterCount));
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetPixelShaderConstantI(UINT StartRegister, const INT* pConstantData, UINT RegisterCount)
	{
		Log(StrFormat("SetPixelShaderConstantI: %d, %d", StartRegister, RegisterCount));
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
	{
		Log(StrFormat("SetRenderState: %d = %d", State, Value));

		mBuffer->WriteByte(CMD_SetRenderState);
		mBuffer->WriteLong(State);
		mBuffer->WriteLong(Value);

		return S_OK;
	}
	HRESULT __stdcall SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
	{
		Log(StrFormat("SetSamplerState: %d[%d] = %d", Type, Sampler, Value));

		mBuffer->WriteByte(CMD_SetSamplerState);
		mBuffer->WriteByte((uchar)Sampler);
		mBuffer->WriteLong(Type);
		mBuffer->WriteLong(Value);

		return S_OK;
	}
	HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
	{
		Log(StrFormat("SetTexture: %d, 0x%08x", Stage, pTexture));
		Error("Textures should not be set directly from fx files");
		return S_OK;
	}
	HRESULT __stdcall Do_Not_Use_SetTextureStageState(DWORD Stage, DWORD Type, DWORD Value)
	{
		Log(StrFormat("SetTextureStageState: %d[%d] = %d", Type, Stage, Value));

		mBuffer->WriteByte(CMD_SetTextureStageState);
		mBuffer->WriteByte((uchar)Stage);
		mBuffer->WriteLong(Type);
		mBuffer->WriteLong(Value);

		return S_OK;
	}
	HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
	{
		Log(StrFormat("SetTransform: %d", State));
		Error("Fixed-function transform parameters should not be set directly in fx files");
		return S_OK;
	}
	HRESULT __stdcall SetVertexShader(IDirect3DVertexShader9* pShader)
	{
		Log("SetVertexShader:");
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetVertexShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT RegisterCount)
	{
		Log(StrFormat("SetVertexShaderConstantB: %d, %d", StartRegister, RegisterCount));
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetVertexShaderConstantF(UINT StartRegister, const FLOAT* pConstantData, UINT RegisterCount)
	{
		Log(StrFormat("SetVertexShaderConstantF: %d, %d", StartRegister, RegisterCount));
		// ignored; we trap this outside the state manager
		return S_OK;
	}
	HRESULT __stdcall SetVertexShaderConstantI(UINT StartRegister, const INT* pConstantData, UINT RegisterCount)
	{
		Log(StrFormat("SetVertexShaderConstantF: %d, %d", StartRegister, RegisterCount));
		// ignored; we trap this outside the state manager
		return S_OK;
	}
};
class Xbox360RenderEffectDefInfo
{
	friend class Xbox360RenderEffect;

	static bool CompileEffect(const char* inEffect, uint32 len, Buffer& outBuffer);

	class Annotation
	{
	public:
		enum EAnnotType
		{
			AT_Bool,
			AT_Int,
			AT_Float,
			AT_Vector,
			AT_String
		};

		EAnnotType mType;
		std::vector<uchar> mData;
		std::string mName;

		inline bool GetBool() const { return mData[0] != 0; }
		inline int GetInt() const { return *((int*)&mData[0]); }
		inline float GetFloat() const { return *((float*)&mData[0]); }
		inline void GetVector(float& outX, float& outY, float& outZ, float& outW) const { float* f = (float*)&mData[0]; outX = f[0]; outY = f[1]; outZ = f[2]; outW = f[3]; }
		inline std::string GetString() const { return std::string((char*)&mData[0]); }
	};
	class ShaderConstant
	{
	public:
		enum EConstantType
		{
			CT_Float,
			CT_Sampler
		};
		enum EStandardConstantSemantic
		{
			SCS_None=0,

			// Values 0-31 = flag-based transform semantics
			//   0-15 = world/view/proj/inv flagged
			//  16-31 = texture transform, index in low 3 bits, only inv flag is used
			SCS_World		= (1 << 0),
			SCS_View		= (1 << 1),
			SCS_Proj		= (1 << 2),
			SCS_Transpose	= (1 << 3),
			SCS_Texture		= (1 << 4),

			// Lighting
			SCS_LightAmbient = 32,
			SCS_LightAttenuation,
			SCS_LightDiffuse,
			SCS_LightSpecular,
			SCS_LightDirection,
			SCS_LightPosition,
			SCS_LightMisc,

			SCS_MaterialAmbient,
			SCS_MaterialDiffuse,
			SCS_MaterialSpecular,
			SCS_MaterialEmissive,
			SCS_MaterialPower,

			SCS_GlobalAmbient,

			// Other
			SCS_TextureFactor,

			// Markers
			SCS_LIGHTFIRST = SCS_LightAmbient,
			SCS_LIGHTLAST = SCS_LightMisc,
			SCS_MATERIALFIRST = SCS_MaterialAmbient,
			SCS_MATERIALLAST = SCS_MaterialPower
		};

		EConstantType mType;
		std::string mConstantName;
		std::string mSemantic;
		EStandardConstantSemantic mStandardSemantic;
		int mRegisterIndex;
		int mRegisterCount;
	};
	class Shader
	{
	public:
		std::vector<uchar> mCode;
		std::vector<ShaderConstant> mConstants;
	};
	class StateCommand
	{
	public:
		enum ECommandType
		{
			CMD_None					= 0,
			CMD_SetRenderState			= 1,
			CMD_SetSamplerState			= 2,
			CMD_SetTextureStageState	= 3
		};

		ECommandType mType;
		int mState;
		int mSamplerOrTextureStage;
		int mValue;
	};
	class Pass
	{
	public:
		std::string mPassName;
		std::vector<Annotation> mAnnotations;
		std::vector<StateCommand> mStateCommands;
		Shader mVertexShader;
		Shader mPixelShader;
	};
	class Technique
	{
	public:
		std::string mTechniqueName;
		std::vector<Annotation> mAnnotations;
		std::vector<Pass> mPasses;
	};

public:
	RenderEffectDefinition* mDefinition;
	std::vector<Technique> mTechniques;

	bool Build(RenderEffectDefinition* inDefinition)
	{
		struct Local
		{
			static void LoadAnnotations(Buffer& inBuffer, std::vector<Xbox360RenderEffectDefInfo::Annotation>& outAnnotations)
			{
				int aAnnotCount = inBuffer.ReadByte();
				for (int iAnnot=0; iAnnot<aAnnotCount; ++iAnnot)
				{
					int aAnnotType = inBuffer.ReadByte();
					if (!aAnnotType)
						continue; // ignored annotation; continue to next one, do not read rest of structure

					outAnnotations.push_back(Xbox360RenderEffectDefInfo::Annotation());
					Xbox360RenderEffectDefInfo::Annotation* aAnnot = &outAnnotations.back();

					switch(aAnnotType)
					{
					case 1:
						{
							aAnnot->mType = Xbox360RenderEffectDefInfo::Annotation::AT_Bool;
							aAnnot->mName = inBuffer.ReadString();
							aAnnot->mData.resize(1);
							aAnnot->mData[0] = inBuffer.ReadByte();
						}
						break;
					case 2:
						{
							aAnnot->mType = Xbox360RenderEffectDefInfo::Annotation::AT_Int;
							aAnnot->mName = inBuffer.ReadString();
							aAnnot->mData.resize(sizeof(int));
							*((int*)&aAnnot->mData[0]) = inBuffer.ReadLong();
						}
						break;
					case 3:
						{
							aAnnot->mType = Xbox360RenderEffectDefInfo::Annotation::AT_Float;
							aAnnot->mName = inBuffer.ReadString();
							aAnnot->mData.resize(sizeof(float));
							inBuffer.ReadBytes(&aAnnot->mData[0], sizeof(float));
						}
						break;
					case 4:
						{
							aAnnot->mType = Xbox360RenderEffectDefInfo::Annotation::AT_Vector;
							aAnnot->mName = inBuffer.ReadString();
							aAnnot->mData.resize(4*sizeof(float));
							inBuffer.ReadBytes(&aAnnot->mData[0], 4*sizeof(float));
						}
						break;
					case 5:
						{
							aAnnot->mType = Xbox360RenderEffectDefInfo::Annotation::AT_String;
							aAnnot->mName = inBuffer.ReadString();
							std::string aStr = inBuffer.ReadString();
							aAnnot->mData.resize(aStr.length()+1);
							strcpy((char*)&aAnnot->mData[0], aStr.c_str());
						}
						break;
					default:
						{
							assert(false && "Invalid annotation type");
						}
						break;
					}
				}
			}

			static void LoadShader(Buffer& inBuffer, Xbox360RenderEffectDefInfo::Shader& outShader)
			{
				int aShaderCodeSize = inBuffer.ReadShort();
				if (!aShaderCodeSize)
					return; // no shader code; nothing else to read, we're done

				outShader.mCode.resize(aShaderCodeSize);
				inBuffer.ReadBytes(&outShader.mCode[0], aShaderCodeSize);

				int aConstantCount = inBuffer.ReadShort();
				for (int iConstant=0; iConstant<aConstantCount; ++iConstant)
				{
					int aConstantType = inBuffer.ReadByte();
					if (!aConstantType)
						continue; // ignored constant; continue to next one, do not read rest of structure

					outShader.mConstants.push_back(Xbox360RenderEffectDefInfo::ShaderConstant());
					Xbox360RenderEffectDefInfo::ShaderConstant* aConstant = &outShader.mConstants.back();

					switch(aConstantType)
					{
					case 1: aConstant->mType = Xbox360RenderEffectDefInfo::ShaderConstant::CT_Float; break;
					case 2: aConstant->mType = Xbox360RenderEffectDefInfo::ShaderConstant::CT_Sampler; break;
					default: assert(false && "Invalid shader constant type"); break;
					}

					aConstant->mConstantName = inBuffer.ReadString();
					aConstant->mSemantic = inBuffer.ReadString();
					aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_None;
					aConstant->mRegisterIndex = inBuffer.ReadShort();
					aConstant->mRegisterCount = inBuffer.ReadByte();

					// identify standard semantics
					if (!aConstant->mSemantic.empty())
					{
						std::string aSemantic = aConstant->mSemantic;

						enum ETransformFlags
						{
							TF_World		= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_World,
							TF_View			= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_View,
							TF_Proj			= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Proj,
							TF_Transpose	= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Transpose,
							TF_Texture		= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Texture,
						};

						ulong aTransformFlags = 0;

						if (aSemantic == "WORLD") { aTransformFlags = TF_World; }
						else if (aSemantic == "VIEW") { aTransformFlags = TF_View; }
						else if (aSemantic == "PROJ") { aTransformFlags = TF_Proj; }
						else if (aSemantic == "WORLDVIEW") { aTransformFlags = TF_World | TF_View; }
						else if (aSemantic == "VIEWPROJ") { aTransformFlags = TF_View | TF_Proj; }
						else if (aSemantic == "WORLDVIEWPROJ") { aTransformFlags = TF_World | TF_View | TF_Proj; }
						else if (aSemantic == "WORLD_TRANSPOSE") { aTransformFlags = TF_World | TF_Transpose; }
						else if (aSemantic == "VIEW_TRANSPOSE") { aTransformFlags = TF_View | TF_Transpose; }
						else if (aSemantic == "PROJ_TRANSPOSE") { aTransformFlags = TF_Proj | TF_Transpose; }
						else if (aSemantic == "WORLDVIEW_TRANSPOSE") { aTransformFlags = TF_World | TF_View | TF_Transpose; }
						else if (aSemantic == "VIEWPROJ_TRANSPOSE") { aTransformFlags = TF_View | TF_Proj | TF_Transpose; }
						else if (aSemantic == "WORLDVIEWPROJ_TRANSPOSE") { aTransformFlags = TF_World | TF_View | TF_Proj | TF_Transpose; }
						
						if (aTransformFlags)
						{
							aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)aTransformFlags;
						}
						else if (aSemantic.substr(0, 16) == "TEXTURETRANSFORM")
						{
							if (aSemantic == "TEXTURETRANSFORM0") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 0); }
							if (aSemantic == "TEXTURETRANSFORM1") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 1); }
							if (aSemantic == "TEXTURETRANSFORM2") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 2); }
							if (aSemantic == "TEXTURETRANSFORM3") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 3); }
							if (aSemantic == "TEXTURETRANSFORM4") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 4); }
							if (aSemantic == "TEXTURETRANSFORM5") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 5); }
							if (aSemantic == "TEXTURETRANSFORM6") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 6); }
							if (aSemantic == "TEXTURETRANSFORM7") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)(TF_Texture + 7); }
						}
						else if (aSemantic.substr(0, 19) == "INVTEXTURETRANSFORM")
						{
							if (aSemantic == "INVTEXTURETRANSFORM0") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 0); }
							if (aSemantic == "INVTEXTURETRANSFORM1") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 1); }
							if (aSemantic == "INVTEXTURETRANSFORM2") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 2); }
							if (aSemantic == "INVTEXTURETRANSFORM3") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 3); }
							if (aSemantic == "INVTEXTURETRANSFORM4") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 4); }
							if (aSemantic == "INVTEXTURETRANSFORM5") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 5); }
							if (aSemantic == "INVTEXTURETRANSFORM6") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 6); }
							if (aSemantic == "INVTEXTURETRANSFORM7") { aConstant->mStandardSemantic = (Xbox360RenderEffectDefInfo::ShaderConstant::EStandardConstantSemantic)((TF_Texture|TF_Transpose) + 7); }
						}
						else if (aSemantic.substr(0, 5) == "LIGHT")
						{
							if (aSemantic == "LIGHTAMBIENT") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightAmbient; }
							if (aSemantic == "LIGHTATTENUATION") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightAttenuation; }
							if (aSemantic == "LIGHTDIFFUSE") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightDiffuse; }
							if (aSemantic == "LIGHTSPECULAR") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightSpecular; }
							if (aSemantic == "LIGHTDIRECTION") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightDirection; }
							if (aSemantic == "LIGHTPOSITION") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightPosition; }
							if (aSemantic == "LIGHTMISC") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightMisc; }
						}
						else if (aSemantic.substr(0, 8) == "MATERIAL")
						{
							if (aSemantic == "MATERIALAMBIENT") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialAmbient; }
							if (aSemantic == "MATERIALDIFFUSE") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialDiffuse; }
							if (aSemantic == "MATERIALSPECULAR") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialSpecular; }
							if (aSemantic == "MATERIALEMISSIVE") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialEmissive; }
							if (aSemantic == "MATERIALPOWER") { aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialPower; }
						}
						else if (aSemantic == "GLOBALAMBIENT")
						{
							aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_GlobalAmbient;
						}
						else if (aSemantic == "TEXTUREFACTOR")
						{
							aConstant->mStandardSemantic = Xbox360RenderEffectDefInfo::ShaderConstant::SCS_TextureFactor;
						}
					}
				}
			}
		};

		mDefinition = inDefinition;
		mTechniques.clear();

		//Compile effects at runtime for development purposes
		if(Lower(inDefinition->mDataFormat) == "fx" )
		{
			OutputDebug("Compiling Effect '%s'...\n",inDefinition->mSrcFileName.c_str() );

			Buffer b;
			if( !Xbox360RenderEffectDefInfo::CompileEffect((const char *)&inDefinition->mData[0],inDefinition->mData.size(),b) )
			{
				OutputDebug("Failed to compile effect \"%s\"\n", inDefinition->mSrcFileName.c_str());
				return false;
			}

			mDefinition->LoadFromMem( b.GetDataLen(), b.GetDataPtr(), inDefinition->mSrcFileName.c_str(), "d3dfx");
		}

		if (Lower(inDefinition->mDataFormat) != "d3dfx")
		{
			gSexyAppBase->Popup(StrFormat("Effect \"%s\" is not in required D3DFX format", inDefinition->mSrcFileName.c_str()));
			return false;
		}

		Buffer aBuffer;
		aBuffer.SetData(inDefinition->mData);
		aBuffer.SeekFront();

		ulong aStartMagic = aBuffer.ReadLong();
		if (aStartMagic != 0x1234ffff)
		{
			assert(false && "Xbox360RenderEffectDefInfo::Build: Invalid start-magic; check resource serialization code");
			return false;
		}
		ushort aVersion = aBuffer.ReadShort();
		if (aVersion != 1)
			return false;

		int aTechniqueCount = aBuffer.ReadShort();
		for (int iTechnique=0; iTechnique<aTechniqueCount; ++iTechnique)
		{
			mTechniques.push_back(Technique());
			Technique* aTech = &mTechniques.back();

			aTech->mTechniqueName = aBuffer.ReadString();
			Local::LoadAnnotations(aBuffer, aTech->mAnnotations);

			int aPassCount = aBuffer.ReadShort();
			for (int iPass=0; iPass<aPassCount; ++iPass)
			{
				aTech->mPasses.push_back(Pass());
				Pass* aPass = &aTech->mPasses.back();

				aPass->mPassName = aBuffer.ReadString();
				Local::LoadAnnotations(aBuffer, aPass->mAnnotations);

				int aStateCmdType = aBuffer.ReadByte();
				while (aStateCmdType != StateCommand::CMD_None)
				{
					aPass->mStateCommands.push_back(StateCommand());
					StateCommand* aCommand = &aPass->mStateCommands.back();

					aCommand->mType = (StateCommand::ECommandType)aStateCmdType;

					switch(aStateCmdType)
					{
					case StateCommand::CMD_SetRenderState:
						{
							aCommand->mSamplerOrTextureStage = 0;
							aCommand->mState = aBuffer.ReadLong();
							aCommand->mValue = aBuffer.ReadLong();
						}
						break;
					case StateCommand::CMD_SetSamplerState:
						{
							aCommand->mSamplerOrTextureStage = aBuffer.ReadByte();
							aCommand->mState = aBuffer.ReadLong();
							aCommand->mValue = aBuffer.ReadLong();
						}
						break;
					case StateCommand::CMD_SetTextureStageState:
						{
							aCommand->mSamplerOrTextureStage = aBuffer.ReadByte();
							aCommand->mState = aBuffer.ReadLong();
							aCommand->mValue = aBuffer.ReadLong();
						}
						break;
					default:
						{
							assert(false && "Invalid state command");
						}
						break;
					}

					aStateCmdType = aBuffer.ReadByte();
				}

				Local::LoadShader(aBuffer, aPass->mVertexShader);
				Local::LoadShader(aBuffer, aPass->mPixelShader);
			}
		}

		ulong aEndMagic = aBuffer.ReadLong();
		if (aEndMagic != 0xffff5678)
		{
			assert(false && "Xbox360RenderEffectDefInfo::Build: Invalid end-magic; check resource serialization code");
			return false;
		}

		return true;
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Xbox360RenderEffect : public RenderEffect
{
public:
	class Technique;
	typedef std::map<std::string, Technique*> TechniqueNameMap;

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
			ParamMap::iterator it = mParamMap.find(inName);
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

	class Pass
	{
	public:
		RenderEffect* mEffect;
		Xbox360RenderDevice* mInterface;
		Xbox360RenderEffectDefInfo::Pass* mDefinition;
		D3DVertexShader* mVertexShader;
		D3DPixelShader* mPixelShader;
		std::string mTextureRemapStr;
		bool mInProgress;

		Pass(RenderEffect* inEffect, Xbox360RenderDevice* inInterface, Xbox360RenderEffectDefInfo::Pass* inDefinition)
		: mEffect(inEffect)
		, mInterface(inInterface)
		, mDefinition(inDefinition)
		, mVertexShader(NULL)
		, mPixelShader(NULL)
		, mInProgress(false)
		{
			if (mDefinition->mVertexShader.mCode.size())
			{
				if (!SUCCEEDED(mInterface->mDevice->CreateVertexShader((DWORD*)&mDefinition->mVertexShader.mCode[0], &mVertexShader)))
					mVertexShader = NULL;
			}
			if (mDefinition->mPixelShader.mCode.size())
			{
				if (!SUCCEEDED(mInterface->mDevice->CreatePixelShader((DWORD*)&mDefinition->mPixelShader.mCode[0], &mPixelShader)))
					mPixelShader = NULL;
			}

			int aAnnotCount = mDefinition->mAnnotations.size();
			for (int iAnnot=0; iAnnot<aAnnotCount; ++iAnnot)
			{
				Xbox360RenderEffectDefInfo::Annotation* aAnnot = &mDefinition->mAnnotations[iAnnot];
				if (aAnnot->mType == Xbox360RenderEffectDefInfo::Annotation::AT_String)
				{
					if (aAnnot->mName == "rfx_pass_texture_remap")
					{
						mTextureRemapStr = aAnnot->GetString();
					}
				}
			}
		}
		~Pass()
		{
			if (mVertexShader)
			{
				mVertexShader->Release();
				mVertexShader = NULL;
			}
			if (mPixelShader)
			{
				mPixelShader->Release();
				mPixelShader = NULL;
			}
		}
static void SexyMatrixMultiply_Static(SexyMatrix4 *pOut, const SexyMatrix4 *pM1, const SexyMatrix4 *pM2)
{	
	pOut->m00 = pM1->m00*pM2->m00 + pM1->m01*pM2->m10 + pM1->m02*pM2->m20 + pM1->m03*pM2->m30;
	pOut->m01 = pM1->m00*pM2->m01 + pM1->m01*pM2->m11 + pM1->m02*pM2->m21 + pM1->m03*pM2->m31;
	pOut->m02 = pM1->m00*pM2->m02 + pM1->m01*pM2->m12 + pM1->m02*pM2->m22 + pM1->m03*pM2->m32;
	pOut->m03 = pM1->m00*pM2->m03 + pM1->m01*pM2->m13 + pM1->m02*pM2->m23 + pM1->m03*pM2->m33;
	pOut->m10 = pM1->m10*pM2->m00 + pM1->m11*pM2->m10 + pM1->m12*pM2->m20 + pM1->m13*pM2->m30;
	pOut->m11 = pM1->m10*pM2->m01 + pM1->m11*pM2->m11 + pM1->m12*pM2->m21 + pM1->m13*pM2->m31;
	pOut->m12 = pM1->m10*pM2->m02 + pM1->m11*pM2->m12 + pM1->m12*pM2->m22 + pM1->m13*pM2->m32;
	pOut->m13 = pM1->m10*pM2->m03 + pM1->m11*pM2->m13 + pM1->m12*pM2->m23 + pM1->m13*pM2->m33;
	pOut->m20 = pM1->m20*pM2->m00 + pM1->m21*pM2->m10 + pM1->m22*pM2->m20 + pM1->m23*pM2->m30;
	pOut->m21 = pM1->m20*pM2->m01 + pM1->m21*pM2->m11 + pM1->m22*pM2->m21 + pM1->m23*pM2->m31;
	pOut->m22 = pM1->m20*pM2->m02 + pM1->m21*pM2->m12 + pM1->m22*pM2->m22 + pM1->m23*pM2->m32;
	pOut->m23 = pM1->m20*pM2->m03 + pM1->m21*pM2->m13 + pM1->m22*pM2->m23 + pM1->m23*pM2->m33;
	pOut->m30 = pM1->m30*pM2->m00 + pM1->m31*pM2->m10 + pM1->m32*pM2->m20 + pM1->m33*pM2->m30;
	pOut->m31 = pM1->m30*pM2->m01 + pM1->m31*pM2->m11 + pM1->m32*pM2->m21 + pM1->m33*pM2->m31;
	pOut->m32 = pM1->m30*pM2->m02 + pM1->m31*pM2->m12 + pM1->m32*pM2->m22 + pM1->m33*pM2->m32;
	pOut->m33 = pM1->m30*pM2->m03 + pM1->m31*pM2->m13 + pM1->m32*pM2->m23 + pM1->m33*pM2->m33;
}
		static ParamData* MakeTempParamForSemantic(ParamData* inParam, Xbox360RenderDevice* inInterface, ulong inSemantic, ulong inDesiredRegisterCount)
		{
			if (inSemantic < 32)
			{

				// first 5 bits are transform flag semantics
				SexyMatrix4 m;

				if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Texture)
				{
					// texture transform
					inInterface->mStateMgr->GetTransform(SEXY3DTS_TEXTURE0 + (inSemantic & 7), &m);
				}
				else
				{
					// world/view/proj transform
					SexyMatrix4 aWorld, aView, aProj;
					if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_World)
						inInterface->mStateMgr->GetTransform(SEXY3DTS_WORLD, &aWorld);
					if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_View)
						inInterface->mStateMgr->GetTransform(SEXY3DTS_VIEW, &aView);
					if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Proj)
						inInterface->mStateMgr->GetTransform(SEXY3DTS_PROJECTION, &aProj);

					if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_World)
					{
						m = aWorld;
						if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_View)
						{
							SexyMatrix4 aResultMatrix;
							SexyMatrixMultiply_Static(&aResultMatrix, &m, &aView);
							m = aResultMatrix;
						}
						if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Proj)
						{
							SexyMatrix4 aResultMatrix;
							SexyMatrixMultiply_Static(&aResultMatrix, &m, &aProj);
							m = aResultMatrix;
						}
					}
					else if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_View)
					{
						m = aView;
						if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Proj)
						{
							SexyMatrix4 aResultMatrix;
							SexyMatrixMultiply_Static(&aResultMatrix, &m, &aProj);
							m = aResultMatrix;
						}
					}
					else if (inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Proj)
					{
						m = aProj;
					}
					else
					{
						assert(false && "Invalid standard constant semantic");
					}

				}

				// transpose; note that this is deliberately backwards, i.e. we transpose if we DON'T have the inv flag set, because shaders are column-based and the C++ is row-based
				if (!(inSemantic & Xbox360RenderEffectDefInfo::ShaderConstant::SCS_Transpose))
				{
					float mT[16] = 
					{
						m.m[0][0],m.m[1][0],m.m[2][0],m.m[3][0],
						m.m[0][1],m.m[1][1],m.m[2][1],m.m[3][1],
						m.m[0][2],m.m[1][2],m.m[2][2],m.m[3][2],
						m.m[0][3],m.m[1][3],m.m[2][3],m.m[3][3]
					};

					inParam->SetValue(&mT[0], 16);
				}
				else
				{
					inParam->SetValue(&m.m00, 16);
				}
			}
			else if ((inSemantic >= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LIGHTFIRST) && (inSemantic <= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LIGHTLAST))
			{
				// lighting semantics

				// each of these values is a single 4-float vector register, but in the effects
				// it can be an array, indicating more than one light.  So the number of lights we
				// need to provide depends on the number of registers being used.
				int aLightCount = inDesiredRegisterCount;
				inParam->mFloatData.resize(aLightCount * 4);

				Graphics3D::LightColors aLightColors;
				SexyVector3 aLightPos, aLightDir, aLightAttenuation;
				float aLightRange;

				switch(inSemantic)
				{
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightAmbient:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = (float)aLightColors.mAmbient.mRed / 255.f;
							inParam->mFloatData[iLight*4 + 1] = (float)aLightColors.mAmbient.mGreen / 255.f;
							inParam->mFloatData[iLight*4 + 2] = (float)aLightColors.mAmbient.mBlue / 255.f;
							inParam->mFloatData[iLight*4 + 3] = (float)aLightColors.mAmbient.mAlpha / 255.f;
						}
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightAttenuation:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = aLightAttenuation.x;
							inParam->mFloatData[iLight*4 + 1] = aLightAttenuation.y;
							inParam->mFloatData[iLight*4 + 2] = aLightAttenuation.z;
							inParam->mFloatData[iLight*4 + 3] = 0.f;
						}
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightDiffuse:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = (float)aLightColors.mDiffuse.mRed / 255.f;
							inParam->mFloatData[iLight*4 + 1] = (float)aLightColors.mDiffuse.mGreen / 255.f;
							inParam->mFloatData[iLight*4 + 2] = (float)aLightColors.mDiffuse.mBlue / 255.f;
							inParam->mFloatData[iLight*4 + 3] = (float)aLightColors.mDiffuse.mAlpha / 255.f;
						}
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightSpecular:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = (float)aLightColors.mSpecular.mRed / 255.f;
							inParam->mFloatData[iLight*4 + 1] = (float)aLightColors.mSpecular.mGreen / 255.f;
							inParam->mFloatData[iLight*4 + 2] = (float)aLightColors.mSpecular.mBlue / 255.f;
							inParam->mFloatData[iLight*4 + 3] = (float)aLightColors.mSpecular.mAlpha / 255.f;
						}
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightDirection:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = aLightDir.x;
							inParam->mFloatData[iLight*4 + 1] = aLightDir.y;
							inParam->mFloatData[iLight*4 + 2] = aLightDir.z;
							inParam->mFloatData[iLight*4 + 3] = 0.f;
						}
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightPosition:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = aLightPos.x;
							inParam->mFloatData[iLight*4 + 1] = aLightPos.y;
							inParam->mFloatData[iLight*4 + 2] = aLightPos.z;
							inParam->mFloatData[iLight*4 + 3] = 0.f;
						}
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_LightMisc:
					{
						for (int iLight=0; iLight<aLightCount; ++iLight)
						{
							inInterface->mStateMgr->GetLightInfo(iLight, aLightColors, aLightPos, aLightDir, aLightAttenuation, aLightRange);
							inParam->mFloatData[iLight*4 + 0] = aLightRange;
							inParam->mFloatData[iLight*4 + 1] = 1.f; // falloff
							inParam->mFloatData[iLight*4 + 2] = 0.f; // theta
							inParam->mFloatData[iLight*4 + 3] = SEXYMATH_PI; // phi
						}
					}
					break;
				default:
					{
						assert(false && "Invalid standard constant semantic");
					}
					break;
				}
			}
			else if ((inSemantic >= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MATERIALFIRST) && (inSemantic <= Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MATERIALLAST))
			{
				// materials
				Color aMatAmbient, aMatDiffuse, aMatSpecular, aMatEmissive;
				float aMatSpecularPower;

				inInterface->mStateMgr->GetMaterialInfo(aMatAmbient, aMatDiffuse, aMatSpecular, aMatEmissive, aMatSpecularPower);

				switch(inSemantic)
				{
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialAmbient:
					{
						inParam->mFloatData.resize(4);
						inParam->mFloatData[0] = (float)aMatAmbient.mRed / 255.f;
						inParam->mFloatData[1] = (float)aMatAmbient.mGreen / 255.f;
						inParam->mFloatData[2] = (float)aMatAmbient.mBlue / 255.f;
						inParam->mFloatData[3] = (float)aMatAmbient.mAlpha / 255.f;
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialDiffuse:
					{
						inParam->mFloatData.resize(4);
						inParam->mFloatData[0] = (float)aMatDiffuse.mRed / 255.f;
						inParam->mFloatData[1] = (float)aMatDiffuse.mGreen / 255.f;
						inParam->mFloatData[2] = (float)aMatDiffuse.mBlue / 255.f;
						inParam->mFloatData[3] = (float)aMatDiffuse.mAlpha / 255.f;
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialSpecular:
					{
						inParam->mFloatData.resize(4);
						inParam->mFloatData[0] = (float)aMatSpecular.mRed / 255.f;
						inParam->mFloatData[1] = (float)aMatSpecular.mGreen / 255.f;
						inParam->mFloatData[2] = (float)aMatSpecular.mBlue / 255.f;
						inParam->mFloatData[3] = (float)aMatSpecular.mAlpha / 255.f;
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialEmissive:
					{
						inParam->mFloatData.resize(4);
						inParam->mFloatData[0] = (float)aMatEmissive.mRed / 255.f;
						inParam->mFloatData[1] = (float)aMatEmissive.mGreen / 255.f;
						inParam->mFloatData[2] = (float)aMatEmissive.mBlue / 255.f;
						inParam->mFloatData[3] = (float)aMatEmissive.mAlpha / 255.f;
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_MaterialPower:
					{						
						inParam->SetValue(&aMatSpecularPower, 1);
					}
					break;
				default:
					{
						assert(false && "Invalid standard constant semantic");
					}
					break;
				}
			}
			else
			{
				// all other semantics

				switch(inSemantic)
				{
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_GlobalAmbient:
					{
						Color aGlobalAmbient = Color::FromInt(inInterface->mStateMgr->GetRenderState(SEXY3DRS_AMBIENT));
						
						inParam->mFloatData.resize(4);
						inParam->mFloatData[0] = (float)aGlobalAmbient.mRed / 255.f;
						inParam->mFloatData[1] = (float)aGlobalAmbient.mGreen / 255.f;
						inParam->mFloatData[2] = (float)aGlobalAmbient.mBlue / 255.f;
						inParam->mFloatData[3] = (float)aGlobalAmbient.mAlpha / 255.f;
					}
					break;
				case Xbox360RenderEffectDefInfo::ShaderConstant::SCS_TextureFactor:
					{
						Color aTextureFactor = Color::FromInt(inInterface->mStateMgr->GetRenderState(SEXY3DRS_TEXTUREFACTOR));
						
						inParam->mFloatData.resize(4);
						inParam->mFloatData[0] = (float)aTextureFactor.mRed / 255.f;
						inParam->mFloatData[1] = (float)aTextureFactor.mGreen / 255.f;
						inParam->mFloatData[2] = (float)aTextureFactor.mBlue / 255.f;
						inParam->mFloatData[3] = (float)aTextureFactor.mAlpha / 255.f;
					}
					break;
				default:
					{
						assert(false && "Invalid standard constant semantic");
					}
					break;
				}
			}

			return inParam;
		}

		void ApplyToDevice(ParamCollection* inParams, bool inApplyParamsOnly)
		{
			ParamData aTempParam;

			if (!inApplyParamsOnly)
			{
				// shaders
				mInterface->mStateMgr->SetVertexShader(mVertexShader);
				mInterface->mStateMgr->SetPixelShader(mPixelShader);
			
				// state commands
				int aStateCommandCount = mDefinition->mStateCommands.size();
				for (int iCommand=0; iCommand<aStateCommandCount; ++iCommand)
				{
					Xbox360RenderEffectDefInfo::StateCommand* aCommand = &mDefinition->mStateCommands[iCommand];
					switch(aCommand->mType)
					{
					case Xbox360RenderEffectDefInfo::StateCommand::CMD_SetRenderState:
						{
							mInterface->SetD3DRenderState((D3DRENDERSTATETYPE)aCommand->mState, aCommand->mValue);
						}
						break;
					case Xbox360RenderEffectDefInfo::StateCommand::CMD_SetSamplerState:
						{
							mInterface->SetSamplerState(aCommand->mSamplerOrTextureStage, aCommand->mState, aCommand->mValue);
						}
						break;
					case Xbox360RenderEffectDefInfo::StateCommand::CMD_SetTextureStageState:
						{
//							mInterface->SetTextureStageState(aCommand->mSamplerOrTextureStage, aCommand->mState, aCommand->mValue);
						}
						break;
					default:
						break;
					}
				}

				// texture remap
/*
				if (!mTextureRemapStr.empty())
				{
					int aSamplerCount = min(10, mTextureRemapStr.length());
					for (int i=0; i<aSamplerCount; ++i)
					{
						if ((mTextureRemapStr[i] >= '0') && (mTextureRemapStr[i] <= '9'))
						{
							int aPhysicalSampler = (mTextureRemapStr[i] - '0');
							mInterface->mStateMgr->SetTextureRemap(i, aPhysicalSampler);
						}
					}
				}
*/
			}

			// parameters

			if (mVertexShader)
			{
				int aConstantCount = mDefinition->mVertexShader.mConstants.size();
				for (int iConstant=0; iConstant<aConstantCount; ++iConstant)
				{
					Xbox360RenderEffectDefInfo::ShaderConstant* aConstant = &mDefinition->mVertexShader.mConstants[iConstant];
					if (aConstant->mType != Xbox360RenderEffectDefInfo::ShaderConstant::CT_Float)
						continue;
					
					ParamData* aParamData = inParams->GetParamNamed(aConstant->mConstantName, false);
					if (!aParamData && (aConstant->mStandardSemantic != Xbox360RenderEffectDefInfo::ShaderConstant::SCS_None))
						aParamData = MakeTempParamForSemantic(&aTempParam, mInterface, aConstant->mStandardSemantic, aConstant->mRegisterCount);
					if (aParamData)
					{
						int aMinFloatCount = min((int)aParamData->mFloatData.size(), aConstant->mRegisterCount*4);
						assert(!(aMinFloatCount & 3)); // all float data must be 4-float vector-sized by this point

						mInterface->mStateMgr->SetVertexShaderConstantF(aConstant->mRegisterIndex, &aParamData->mFloatData[0], aMinFloatCount >> 2);
					}
				}
			}
			if (mPixelShader)
			{
				int aConstantCount = mDefinition->mPixelShader.mConstants.size();
				for (int iConstant=0; iConstant<aConstantCount; ++iConstant)
				{
					Xbox360RenderEffectDefInfo::ShaderConstant* aConstant = &mDefinition->mPixelShader.mConstants[iConstant];
					if (aConstant->mType != Xbox360RenderEffectDefInfo::ShaderConstant::CT_Float)
						continue;
					
					ParamData* aParamData = inParams->GetParamNamed(aConstant->mConstantName, false);
					if (!aParamData && (aConstant->mStandardSemantic != Xbox360RenderEffectDefInfo::ShaderConstant::SCS_None))
						aParamData = MakeTempParamForSemantic(&aTempParam, mInterface, aConstant->mStandardSemantic, aConstant->mRegisterCount);
					if (aParamData)
					{
						int aMinFloatCount = min((int)aParamData->mFloatData.size(), aConstant->mRegisterCount*4);
						assert(!(aMinFloatCount & 3)); // all float data must be 4-float vector-sized by this point

						mInterface->mStateMgr->SetPixelShaderConstantF(aConstant->mRegisterIndex, &aParamData->mFloatData[0], aMinFloatCount >> 2);
					}
				}
			}
		}
	};

	class Technique
	{
	public:
		RenderEffect* mEffect;
		Xbox360RenderDevice* mInterface;
		Xbox360RenderEffectDefInfo::Technique* mDefinition;
		ParamCollection* mParams;
		std::vector<Pass*> mPasses;
		Technique* mValidTechnique;
		bool mValidated;
		std::string mCompatFallback;

		Technique(RenderEffect* inEffect, Xbox360RenderDevice* inInterface, Xbox360RenderEffectDefInfo::Technique* inDefinition, ulong inIndex, ParamCollection* inParams)
		: mEffect(inEffect)
		, mInterface(inInterface)
		, mDefinition(inDefinition)
		, mParams(inParams)
		, mValidTechnique(NULL)
		, mValidated(false)
		{
			int aPassCount = mDefinition->mPasses.size();
			for (int iPass=0; iPass<aPassCount; ++iPass)
			{
				mPasses.push_back(new Pass(mEffect, mInterface, &mDefinition->mPasses[iPass]));
			}
		}
		~Technique()
		{
			for (int i=0; i<(int)mPasses.size(); ++i)
				delete mPasses[i];
			mPasses.clear();
		}

		Technique* GetValidTechnique(TechniqueNameMap& inTechniqueNameMap)
		{
			if (!mValidated)
			{
				ulong aMinTextureStages = 0;
				bool aRequiresCubeMaps = false;
				bool aRequiresVolumeMaps = false;

				// identify fallback technique and compatibility fallback property, if any
				Technique* aFallbackTechnique = NULL;
				std::string aFallbackName;
				int aAnnotCount = mDefinition->mAnnotations.size();
				for (int iAnnot=0; iAnnot<aAnnotCount; ++iAnnot)
				{
					Xbox360RenderEffectDefInfo::Annotation* aAnnot = &mDefinition->mAnnotations[iAnnot];
					if (aAnnot->mType == Xbox360RenderEffectDefInfo::Annotation::AT_String)
					{
						if (aAnnot->mName == "rfx_fallback_technique")
						{
							aFallbackName = aAnnot->GetString();
						}
						else if (aAnnot->mName == "rfx_fallback_compat_property")
						{
							if (gSexyAppBase->mCompatCfgMachine)
							{
								std::string aPropertyName = aAnnot->GetString();
								mCompatFallback = SexyStringToString(gSexyAppBase->GetString(aPropertyName, _S("")));
							}
						}
					}
					else if (aAnnot->mType == Xbox360RenderEffectDefInfo::Annotation::AT_Int)
					{
						if (aAnnot->mName == "rfx_min_texture_stages")
						{
							aMinTextureStages = aAnnot->GetInt();
						}
					}
					else if (aAnnot->mType == Xbox360RenderEffectDefInfo::Annotation::AT_Bool)
					{
						if (aAnnot->mName == "rfx_requires_cubemaps")
						{
							aRequiresCubeMaps = aAnnot->GetBool();
						}
						else if (aAnnot->mName == "rfx_requires_volumemaps")
						{
							aRequiresVolumeMaps = aAnnot->GetBool();
						}
					}
				}

				if (!aFallbackName.empty())
				{
					TechniqueNameMap::iterator it = inTechniqueNameMap.find(aFallbackName);
					aFallbackTechnique = (it != inTechniqueNameMap.end()) ? it->second : NULL;
					assert((aFallbackTechnique != NULL) && "Fallback technique not found");
					aFallbackTechnique = aFallbackTechnique->GetValidTechnique(inTechniqueNameMap);
					assert((aFallbackTechnique != NULL) && "Broken fallback technique chain");
				}

				bool isValid = true;

				// do initial validation checks against any supplied annotations
				if ( (aMinTextureStages && (mInterface->GetMaxTextureStages() < aMinTextureStages))
				  || (aRequiresCubeMaps && !mInterface->SupportsCubeMaps())
				  || (aRequiresVolumeMaps && !mInterface->SupportsVolumeMaps())
				  )
				{
					isValid = false;
				}
				else
				{
					// validate this technique on the hardware, by setting up the state for all passes and testing if any of them fail

					int aPassCount = Begin();
					for (int iPass=0; iPass<aPassCount; ++iPass)
					{
						// initial check for whether vs/ps are supported at all
						if (mDefinition->mPasses[iPass].mVertexShader.mCode.size() && !mInterface->SupportsVertexShaders())
						{
							isValid = false;
							break;
						}
						if (mDefinition->mPasses[iPass].mPixelShader.mCode.size() && !mInterface->SupportsPixelShaders())
						{
							isValid = false;
							break;
						}
						
						/*
							At the moment we only call ValidateDevice for fixed-function pixel setups, because pixel
							shader validation seems to be randomly bitchy about things like current vertex declaration
							and render target and such, which we don't have configured right now but will be fine by the
							time we actually need to use the shader.  On the other hand, fixed-function pixel setups
							absolutely need validation because we have no other way of knowing whether the colorop/alphaop
							combiner arrangement will work on the current hardware.
						*/
						if (!mDefinition->mPasses[iPass].mPixelShader.mCode.size())
						{
							// commit the pass's state to the hardware and validate it
							GetEffect()->GetDevice()->PushState();
							BeginPass(iPass);

							if (!mInterface->mStateMgr->CommitState())
							{
								EndPass(iPass);
								GetEffect()->GetDevice()->PopState();
								isValid = false;
								break;
							}
							
/*							DWORD aValidateNumPasses = 0;
							if (FAILED(mInterface->mDevice->ValidateDevice(&aValidateNumPasses)))
							{
								EndPass(iPass);
								GetEffect()->GetDevice()->PopState();
								isValid = false;
								break;
							}
*/
							EndPass(iPass);
							GetEffect()->GetDevice()->PopState();
						}
					}
				}

				mValidTechnique = isValid ? this : aFallbackTechnique;
				//assert((mValidTechnique != NULL) && "Invalid technique without valid fallback");

				mValidated = true;
			}
			
			return mValidTechnique;
		}

		inline RenderEffect* GetEffect() { return mEffect; }
		inline std::string GetName() { return mDefinition->mTechniqueName; }

		int Begin()
		{
			return mPasses.size();
		}		
		void BeginPass(int inPass)
		{
			if (inPass < (int)mPasses.size())
			{
				Pass* p = mPasses[inPass];
				p->ApplyToDevice(mParams, false);
				p->mInProgress = true;
			}
		}
		void EndPass(int inPass)
		{
			if (inPass < (int)mPasses.size())
			{
				Pass* p = mPasses[inPass];
				assert(p->mInProgress == true);
				p->mInProgress = false;
			}
		}		
		void End()
		{
		}

		bool PassUsesVertexShader(int inPass)
		{
			if (inPass >= (int)mPasses.size())
				return false;
			Pass* p = mPasses[inPass];
			return p->mVertexShader != NULL;
		}
		bool PassUsesPixelShader(int inPass)
		{
			if (inPass >= (int)mPasses.size())
				return false;
			Pass* p = mPasses[inPass];
			return p->mPixelShader != NULL;
		}

		void ParametersChanged()
		{
			for (int i=0; i<(int)mPasses.size(); ++i)
			{
				Pass* p = mPasses[i];
				if (p->mInProgress)
				{
					p->ApplyToDevice(mParams, true);
				}
			}
		}
	};

	Xbox360RenderDevice* mInterface;
	Xbox360RenderEffectDefInfo* mDefInfo;
	ParamCollection mParams;
	std::vector<Technique*> mTechniques;
	TechniqueNameMap mTechniqueNameMap;
	Technique* mCurrentTechnique;
	int mBeginPassRefCount;

	Xbox360RenderEffect(Xbox360RenderDevice* inInterface, Xbox360RenderEffectDefInfo* inDefInfo)
	: mInterface(inInterface)
	, mDefInfo(inDefInfo)
	, mCurrentTechnique(NULL)
	, mBeginPassRefCount(0)
	{
		for (int i=0; i<(int)mDefInfo->mTechniques.size(); ++i)
		{
			Technique* aTech = new Technique(this, mInterface, &mDefInfo->mTechniques[i], i, &mParams);
			
			mTechniques.push_back(aTech);

			if (mTechniqueNameMap.find(aTech->mDefinition->mTechniqueName) != mTechniqueNameMap.end())
			{
				assert(false && "Duplicate technique names encountered");
			}
			mTechniqueNameMap[aTech->mDefinition->mTechniqueName] = aTech;
		}

		// force validation here so we trigger any assertions early
		for (int i=0; i<(int)mDefInfo->mTechniques.size(); ++i)
		{
			mTechniques[i]->GetValidTechnique(mTechniqueNameMap);
		}

		// see if there is any "Default" technique, and if so make it current
		std::string aDefaultTechniqueName = "Default";
		TechniqueNameMap::iterator it = mTechniqueNameMap.find(aDefaultTechniqueName);
		if (it != mTechniqueNameMap.end())
			SetCurrentTechnique(aDefaultTechniqueName);
	}
	~Xbox360RenderEffect()
	{
		for (int i=0; i<(int)mTechniques.size(); ++i)
			delete mTechniques[i];
		mTechniques.clear();
	}

	/*
		RenderEffect implementation
	*/
	virtual RenderDevice3D* GetDevice() override { return mInterface; }
	virtual RenderEffectDefinition* GetDefinition() override { return mDefInfo->mDefinition; }

	virtual void SetParameter(const std::string& inParamName, const float* inFloatData, ulong inFloatCount) override
	{
		ParamData* aParam = mParams.GetParamNamed(inParamName, true);
		aParam->SetValue(inFloatData, inFloatCount);

		if (mBeginPassRefCount)
		{
			// we're currently in a pass so we potentially need to commit this parameter
			if (mCurrentTechnique)
				mCurrentTechnique->ParametersChanged();
		}
	}

	virtual void GetParameterBySemantic(ulong/*EStandardConstantSemantic*/ inSemantic, float* outFloatData, ulong inMaxFloatCount) override
	{
		ParamData aTempParam;
		ParamData* aParamData = Pass::MakeTempParamForSemantic(&aTempParam, mInterface, inSemantic, inMaxFloatCount >> 2);
		int aFloatCount = min(inMaxFloatCount, aParamData->mFloatData.size());
		if (aFloatCount)
			memcpy(outFloatData, &aParamData->mFloatData[0], aFloatCount*sizeof(float));
	}

	virtual void SetCurrentTechnique(const std::string& inName, bool inCheckValid = true) override
	{
		TechniqueNameMap::iterator it = mTechniqueNameMap.find(inName);
		if (it != mTechniqueNameMap.end())
		{
			mCurrentTechnique = it->second;
			if (!mCurrentTechnique->mCompatFallback.empty())
				SetCurrentTechnique(mCurrentTechnique->mCompatFallback, inCheckValid);
			if (inCheckValid)
				mCurrentTechnique = mCurrentTechnique->GetValidTechnique(mTechniqueNameMap);
		}
		else
		{
			mCurrentTechnique = NULL;
		}
	}

	virtual std::string GetCurrentTechniqueName() override
	{
		return mCurrentTechnique ? mCurrentTechnique->GetName() : "";
	}

	virtual int Begin(HRunHandle& outRunHandle, const HRenderContext& inRenderContext = HRenderContext((void*)0)) override
	{
		HRenderContext aContext = inRenderContext;
		if (aContext.IsValid())
		{
			GetDevice()->SetCurrentContext(aContext);
		}
		else
		{
			aContext = GetDevice()->GetCurrentContext();
		}
		
		outRunHandle = aContext.GetPointer();

		return mCurrentTechnique ? mCurrentTechnique->Begin() : 1;
	}	
	virtual void BeginPass(const HRunHandle& inRunHandle, int inPass) override
	{
		GetDevice()->SetCurrentContext(HRenderContext(inRunHandle));

		++mBeginPassRefCount;
		GetDevice()->PushState();

		if (mCurrentTechnique)
			mCurrentTechnique->BeginPass(inPass);
	}
	virtual void EndPass(const HRunHandle& inRunHandle, int inPass) override
	{
		GetDevice()->SetCurrentContext(HRenderContext(inRunHandle));

		if (mCurrentTechnique)
			mCurrentTechnique->EndPass(inPass);

		GetDevice()->PopState();
		--mBeginPassRefCount;
	}	
	virtual void End(const HRunHandle& inRunHandle) override
	{
		GetDevice()->SetCurrentContext(HRenderContext(inRunHandle));

		if (mCurrentTechnique)
			mCurrentTechnique->End();
	}

	virtual bool PassUsesVertexShader(int inPass) override
	{
		return mCurrentTechnique ? mCurrentTechnique->PassUsesVertexShader(inPass) : false;
	}
	virtual bool PassUsesPixelShader(int inPass) override
	{
		return mCurrentTechnique ? mCurrentTechnique->PassUsesPixelShader(inPass) : false;
	}
};

}
#endif