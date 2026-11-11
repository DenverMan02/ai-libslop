#ifndef MACOSGRAPHICSDRIVER_H_INCLUDED
#define MACOSGRAPHICSDRIVER_H_INCLUDED

#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/OpenGL.h>
#include "RenderEffect.h"
#include "drivers/graphics/PopFXFormat.h"
#include <drivers/graphics/opengl/OpenGLIdRegistry.h>

using namespace PopFXFormat;

//OpenGL ES has a few functions that require the type-initial (f, x, i) that
// differ from OpenGL. For the sake of not having to have a different codepath,
// the normal OpenGL versions are mapped here.
#define glClearDepthf glClearDepth
#define glDepthRangef glDepthRange
#define glOrthof glOrtho

#define SUPPORT_GLSL_SHADERS 1

#include "drivers/graphics/opengl/BaseOpenGLStateManager.h"
#include "drivers/graphics/opengl/BaseOpenGLRenderDevice.h"

#include "ResStreamsFormat.h"

#define SEXYGL_ARGB(a,r,g,b) \
((uint32)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define SEXYGL_RGBA(r,g,b,a) SEXYGL_ARGB(a,b,g,r)
#define SEXYGL_XRGB(r,g,b)   SEXYGL_ARGB(0xff,r,g,b)

#define SEXYGL_GETALPHA(color)		((color >> 24) & 0xFF)
#define SEXYGL_GETRED(color)			((color >> 16) & 0xFF)
#define SEXYGL_GETGREEN(color)		((color >>  8) & 0xFF)
#define SEXYGL_GETBLUE(color)			((color      ) & 0xFF)


namespace Sexy
{
	class SexyAppBase;
	class MacosxAppDriver;
	class MacosxGraphicsDriver;
	
	struct SexyVertex2DList;
	
	
	
	
	struct MacosxGLVertex : public SexyVertex2D
	{
		MacosxGLVertex()
		{
		}
		
		MacosxGLVertex(float theX, float theY, float theZ, float theU, float theV, uint32 theColor)
		{
			x = theX;
			y = theY;
			z = theZ;
			u = theU;
			v = theV;
			color = theColor;
		}
		
		static inline float GetCoord(const MacosxGLVertex& theVertex, int theCoord)
		{
			switch (theCoord)
			{
				case 0: return theVertex.x;
				case 1: return theVertex.y;
				case 2: return theVertex.z;
				case 3: return theVertex.u;
				case 4: return theVertex.v;
				default: return 0;
			}
		}
		
		static inline MacosxGLVertex Interpolate(const MacosxGLVertex &v1, const MacosxGLVertex &v2, float t)
		{
			MacosxGLVertex aVertex = v1;
			aVertex.x = v1.x + t*(v2.x-v1.x);
			aVertex.y = v1.y + t*(v2.y-v1.y);
			aVertex.u = v1.u + t*(v2.u-v1.u);
			aVertex.v = v1.v + t*(v2.v-v1.v);
			if (v1.color!=v2.color)
			{
				int r = (int)SexyMath::Lerp((float)SEXYGL_GETRED(v1.color), (float)SEXYGL_GETRED(v2.color), t);
				int g = (int)SexyMath::Lerp((float)SEXYGL_GETGREEN(v1.color), (float)SEXYGL_GETGREEN(v2.color), t);
				int b = (int)SexyMath::Lerp((float)SEXYGL_GETBLUE(v1.color), (float)SEXYGL_GETBLUE(v2.color), t);
				int a = (int)SexyMath::Lerp((float)SEXYGL_GETALPHA(v1.color), (float)SEXYGL_GETALPHA(v2.color), t);
				
				aVertex.color = SEXYGL_RGBA(r,g,b,a);
			}
			
			return aVertex;
		}
		
		inline void SetPosition(float theX, float theY, float theZ)
		{
			x = theX;
			y = theY;
			z = theZ;
		}
		
		static inline uint32 PackColor(int theRed, int theGreen, int theBlue, int theAlpha)
		{
			return SEXYGL_RGBA(theRed, theGreen, theBlue, theAlpha);
		}
		
		static inline uint32 TexCoordOffset()
		{
			return 24;
		}
		
		
	};
    
    struct SemanticParam
    {
        uint32 mSemantic; // EStandardConstantSemantic
        std::string mParamName;
        GLuint mProgramLocation; // valid only after program is linked
        
        SemanticParam(uint32 inSemantic, const std::string& inParamName)
        : mSemantic(inSemantic)
        , mParamName(inParamName)
        , mProgramLocation(-1)
        {}
    };
	
    typedef std::vector<SemanticParam> SemanticParamCollection;
	
	//this is a thin container to hold platform specific info for a technique/pass
	struct RenderEffectPass
	{
		GLuint mProgram;
		//attrib binding info
        SemanticParamCollection mSemanticParams;
	};
	
	typedef std::vector<RenderEffectPass> RenderEffectPassList;
	
	struct RenderEffectTechnique
	{
		RenderEffectPassList mPasses;
		bool mIsValid; //for now based on if the shaders compile
	};
	
	typedef std::vector<RenderEffectTechnique> RenderEffectTechniqueList;
	
	
	/**
	 * Large portions of this Render Effect code will be moved to a common PopFX RenderEffect area
	 * because the PopFX container format can work with most platforms to provide the info we need
	 */
	class MacosxRenderEffect : public RenderEffect
	{
	public:
        enum EStandardConstantSemantic
        {
            // CDH FIXME$$ these are largely cut&pasted from D3DInterface.cpp in the Windows drivers;
            // once the Windows stuff is moved underneath the PopFX umbrella, hoist these out as part
            // of the PopFX interface itself.  Note that the sampler semantics are new and don't
            // yet exist in D3DInterface (we need these since we don't have "register(s0)" information
            // available in PopFX, and adding that to the parser would be a bit of a PITA).
            
            SCS_None=0,
            
            // Values 0-31 = flag-based transform semantics
            //   0-15 = world/view/proj/inv flagged
            //  16-31 = texture transform, index in low 3 bits, only inv flag is used
            SCS_World       = (1 << 0),
            SCS_View        = (1 << 1),
            SCS_Proj        = (1 << 2),
            SCS_Transpose   = (1 << 3),
            SCS_Texture     = (1 << 4),
            
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
            
            // Samplers (we use a 1-to-1 mapping so they're synonymous for us)
            SCS_Sampler0 = 64,
            SCS_Sampler1,
            SCS_Sampler2,
            SCS_Sampler3,
            SCS_Sampler4,
            SCS_Sampler5,
            SCS_Sampler6,
            SCS_Sampler7,
            
            // Markers
            SCS_LIGHTFIRST = SCS_LightAmbient,
            SCS_LIGHTLAST = SCS_LightMisc,
            SCS_MATERIALFIRST = SCS_MaterialAmbient,
            SCS_MATERIALLAST = SCS_MaterialPower,
            SCS_SAMPLERFIRST = SCS_Sampler0,
            SCS_SAMPLERLAST = SCS_Sampler7
        };
        
		class ParamData
		{
		public:
			std::vector<float> mFloatData;
            bool mTreatAsInt;
            
            ParamData()
            : mTreatAsInt(false)
            {}

			void SetValue(const float* inFloatData, uint32 inFloatCount)
			{
				mFloatData.resize(inFloatCount);
				memcpy(&mFloatData[0], inFloatData, inFloatCount*sizeof(float));
				assert(mFloatData.size() == inFloatCount);
				while (mFloatData.size() & 3)
					mFloatData.push_back(0.f); // pad out zeros to 4-float vector length
			}
            void SetIntValue(int inInt)
            {
                float aTempFloat = (float)inInt;
                SetValue(&aTempFloat, 1);
                mTreatAsInt = true;
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
					return nullptr;
				}
			}
		};
		
		MacosxRenderEffect(RenderDevice3D* theDevice, RenderEffectDefinition* theDefinition);
		
		bool Initialize();
		
		// General effect information
		virtual RenderDevice3D* GetDevice();
		
		virtual RenderEffectDefinition* GetDefinition();

		virtual void SetParameter(const std::string& inParamName, const float* inFloatData, uint32 inFloatCount);

		virtual void SetMatrix(const std::string& inParamName, const float* inValue);

		virtual void GetParameterBySemantic(uint32/*EStandardConstantSemantic*/ inSemantic, float* outFloatData, uint32 inMaxFloatCount);

		virtual void SetCurrentTechnique(const std::string& inName, bool inCheckValid = true);
		
		virtual std::string GetCurrentTechniqueName();
		
		virtual int Begin(HRunHandle& outRunHandle, const HRenderContext& inRenderContext = HRenderContext((void*)0));
		
		virtual void BeginPass(const HRunHandle& inRunHandle, int inPass);
		
		virtual void EndPass(const HRunHandle& inRunHandle, int inPass);
		
		virtual void End(const HRunHandle& inRunHandle);
		virtual bool PassUsesVertexShader(int inPass);
		virtual bool PassUsesPixelShader(int inPass);
		
		
	protected:
		bool InitializeTechnique(PopFXTechnique* theTechnique);
		bool InitializePass(PopFXPass* thePass, RenderEffectTechnique& theTechData);
		
        ParamData* MakeTempParamForSemantic(ParamData* inParam, uint32 inSemantic, uint32 inDesiredRegisterCount);
		void UpdateParams();
		
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
        
        inline PopFXAnnotation* GetPopFXAnnotation(int theIndex)
        {
            return (PopFXAnnotation*)(mBuffer + mHeader->annotation_table + theIndex * mHeader->annotation_size);
        }
        
        inline PopFXValue* GetPopFXValue(int theIndex)
        {
            return (PopFXValue*)(mBuffer + mHeader->value_table + theIndex * mHeader->value_size);
        }
		
		inline const char* GetPopFXString(int theIndex)
		{
			PopFXString* aString = (PopFXString*)(mBuffer + mHeader->string_table + theIndex * mHeader->string_size);
			//assert on format (should only be 0 for this function) ??
			return (const char*)(mBuffer + mHeader->string_data_offset + aString->offset);
		}
		
	private:
		
		RenderDevice3D* mDevice;
		RenderEffectDefinition* mDefinition;
		PopFXTechnique* mCurrentTechnique;
		
		uint8* mBuffer;
		PopFXHeader* mHeader;
		
		bool mIsValid;
		
		RenderEffectTechniqueList mTechniques;
		
		int mBeginPassRefCount;
		ParamCollection mParams;
		int mCurrentPass;
	};
	
	
	
	
	class MacosxRenderDevice : public BaseOpenGLRenderDevice<MacosxGLVertex,BaseOpenGLStateManager<VERSION_OPENGL_11>,MacosxRenderDevice>
	{
	public:
		static const bool SUPPORT_HW_CLIP = false; 
		static const bool SUPPORT_TRI_REP = true;
		
		bool mHasPixelShaders;
		bool mHasVertexShaders;
		
		typedef BaseOpenGLRenderDevice<MacosxGLVertex,BaseOpenGLStateManager<VERSION_OPENGL_11>,MacosxRenderDevice> SuperOpenGLRenderDevice;
		
		typedef std::map<RenderEffectDefinition*, MacosxRenderEffect*> RenderEffectMap;
		RenderEffectMap			mRenderEffects;
		
		MacosxRenderDevice(IGraphicsDriver* theDriver) : SuperOpenGLRenderDevice(theDriver)
		{
			mHasPixelShaders = false;
			mHasVertexShaders = false;
			mStateMgr = new BaseOpenGLStateManager<VERSION_OPENGL_11>();
			mStateMgr->Init();
		}
		
		~MacosxRenderDevice()
		{
			for (RenderEffectMap::iterator it = mRenderEffects.begin(); it != mRenderEffects.end(); ++it)
			{
				MacosxRenderEffect* aRenderEffect = it->second;
				delete aRenderEffect;
			}
			mRenderEffects.clear();
		}

//		virtual int GetCapsFlags()
        virtual uint32 GetCapsFlags()  //xiaoyl
		{
			return	RenderDevice3D::CAPF_ImageRenderTargets | 
					(mHasPixelShaders?RenderDevice3D::CAPF_PixelShaders:0) |
					(mHasVertexShaders?RenderDevice3D::CAPF_VertexShaders:0);
		}
		
		virtual std::string GetInfoString(RenderDevice3D::EInfoString theInfoString)
		{
			//this should all be handled by the platform drivers
			switch (theInfoString) {
				case RenderDevice3D::INFOSTRING_BackBuffer:
					break;
				default:
					break;
			}
			return SuperOpenGLRenderDevice::GetInfoString(theInfoString);
		}
		
		bool CheckFrameBufferStatus()
		{
			GLenum status; 
			status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT); 
			switch(status) { 
				case GL_FRAMEBUFFER_COMPLETE_EXT: 
					return true; 
				case GL_FRAMEBUFFER_UNSUPPORTED_EXT: 
					/* choose different formats */ 
					DBG_ASSERT("Unsupported EXT"==0);
					return false; 
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
					DBG_ASSERT("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT"==0);
					return false;
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
					DBG_ASSERT("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT"==0);
					return false;
				case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
					DBG_ASSERT("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT"==0);
					return false;
				case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
					DBG_ASSERT("GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT"==0);
					return false;
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
					DBG_ASSERT("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT"==0);
					return false;
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
					DBG_ASSERT("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT"==0);
					return false;
				default: 
					/* programming error; will fail on all hardware */ 
					DBG_ASSERT("Unsupported EXT"==0);
					return false; 
			}
		}
		
		GLTexHolder CreateTextureSurface(int theWidth, int theHeight, PixelFormat theFormat, bool renderTarget, class super::TextureData* theTexData, class super::TextureDataPiece* theTexDataPiece)
		{
			//this flushes the triangle buffers and unsets the cur tex, since 
			// we will be altering that below
			SetTextureSingle(0, 0);
			
			
			//JVW - if a GL texture fails to be created is there anything that can be done?
			// I'm not aware of any vram flushing mechanisms
			GLTexHolder aTex;
			
			glGenTextures(1, &aTex.tex);
			OpenGLIdRegistry::StaticRegisterIds( 1, &aTex.tex );

			aTex.src = GL_TEXTURE_2D;
			
			GLenum theGLFormat = GL_RGBA;
			
			if (theFormat == PixelFormat_X8R8G8B8)
			{
				theGLFormat = GL_RGB;
			}
			
			if (theTexDataPiece!=NULL)
			{
				theTexDataPiece->mTexFormat = theGLFormat;
			}
			
			if (renderTarget)
			{
				glGenFramebuffersEXT(1, &theTexData->mExtraData.mFBO);
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, theTexData->mExtraData.mFBO);
				glActiveTexture(GL_TEXTURE0);
				
				GLuint where = GL_TEXTURE_2D;
				aTex.src = where;
				glEnable(where);
				glBindTexture(where, aTex.tex);
				glTexImage2D(where, 0, theGLFormat, theWidth, theHeight, 0, GL_RGBA, GL_BYTE, NULL);
				glTexParameteri( where, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri( where, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri( where, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri( where, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				
				glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, where, aTex.tex, 0);
				
				//would be nice to know if the images don't need z.
				// ImageFlag?
				//if (!(m_other_canvas_flags & GAS_CANVAS_NO_Z))
				{
					glGenRenderbuffersEXT(1, &theTexData->mExtraData.mDepth);
					glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, theTexData->mExtraData.mDepth);
					glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, theWidth, theHeight);
					
					//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, theTexData->mExtraData.mDepth, 0);
					glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, theTexData->mExtraData.mDepth);
				}
				
				if (!CheckFrameBufferStatus())
				{
					glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
					glBindTexture(where, 0);

					//cleanup this mess and return. might want to set a flag that the rendertarget is unusable.
					//this should be a fatal error (but I want this to return with no issues so that compat can be tested
					
					if ( OpenGLIdRegistry::StaticIsTextureIdValid( (GLuint) &aTex.tex ) )
					{
						glDeleteTextures(1,&aTex.tex);
					}
					OpenGLIdRegistry::StaticUnregisterIds(  1, &aTex.tex );
					aTex.tex = 0;

					return 0;
				}

				
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
				glBindTexture(where, 0);
			}
			
			
			
			return aTex;
			
		}
		
		void ReleaseExtraRenderDataInfo(class super::TextureData* theTexData, GLExtraRenderDataInfo& theInfo)
		{
			if (theInfo.mFBO != 0)
			{
				glDeleteFramebuffersEXT(1,&theInfo.mFBO);
				theInfo.mFBO = 0;
			}
			
			if (theInfo.mDepth != 0)
			{
				if ( OpenGLIdRegistry::StaticIsTextureIdValid( (GLuint) &theInfo.mDepth ) )
				{
					//glDeleteTextures(1, &theInfo.mDepth);
					glDeleteRenderbuffersEXT(1, &theInfo.mDepth);
				}
				OpenGLIdRegistry::StaticUnregisterIds(  1, &theInfo.mDepth );
				theInfo.mDepth = 0;
			}
		}
		
		virtual bool SetRenderTargetFBO(GLuint fbo)
		{
			if (!PreDraw())
				return false;
			
			if (fbo == mCurRenderTargetFBO)
			{
				return true;
			}
			
			super::FlushBufferedTriangles();
			
			mCurRenderTargetImage = NULL;
			
			if (fbo == 0)
			{
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
				glDrawBuffer(GL_BACK);
			}
			else 
			{
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
				glDrawBuffer(GL_BACK);
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo); 
				GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT};
				glDrawBuffers(1, buffers);
				
				//for debugging only. don't do this.
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
			}
			
			mCurRenderTargetFBO = fbo;
			
			return true;
		}
		

		inline void SetOrthoMatrix(Image* theImage)
		{
			int aWidth;
			int aHeight;
			if (theImage == mSysImage || theImage == NULL)
			{
				aWidth = mWidth;
				aHeight = mHeight;
			}
			else if (theImage!=NULL)
			{
				aWidth = theImage->mWidth;				
				aHeight = theImage->mHeight;
				
			}
			SexyMatrix4 aProj;
			
			memset(&aProj.m00,0,16*sizeof(float));
			
			aProj.m00 = 2.0f / (float)aWidth;
			aProj.m11 = 2.0f / (float)aHeight;
			aProj.m22 = 1.0f;
			aProj.m32 = 0.0f;
			aProj.m33 = 1.0f;
			
			aProj.m30 = -1.0f;
			aProj.m31 = -1.0f;
			//aProj.m32 = -1.0f;
			mStateMgr->SetViewport(1,1,1,1,0.1f,0.2f);
			mStateMgr->SetViewport(0,0,aWidth,aHeight,0.0f,1.0f);
			mStateMgr->SetOrthoProjection(&aProj);
		}
		
		
		virtual RenderEffect* GetEffect(RenderEffectDefinition* inDefinition)
		{
			RenderEffectMap::iterator it = mRenderEffects.find(inDefinition);
			if (it != mRenderEffects.end())
				return it->second;
			
			MacosxRenderEffect* aEffect = new MacosxRenderEffect(this, inDefinition);
			mRenderEffects[inDefinition] = aEffect;
			return aEffect;
		}
        
        inline void AdjustVertsForAtlas(int inTextureIndex, void* inVerts, int inVertCount, uint32 inVertFormat, int inStride, int inTexUVOfs)
		{
			SexyVector2 aBase, aU, aV;
			if (!mStateMgr->GetAtlasState(inTextureIndex, aBase, aU, aV))
				return;
			
			char* ptr = &((char*)inVerts)[inTexUVOfs];
			for (int i=0; i<inVertCount; ++i, ptr += inStride)
			{
				float* uv = (float*)ptr;
				SexyVector2 p = aBase + aU*uv[0] + aV*uv[1];
				uv[0] = p.x;
				uv[1] = p.y;
			}
		}
		
	};
	
	class MacosxGraphicsDriver : public IGraphicsDriver, protected NativeDisplay
	{
	public:
		MacosxRenderDevice mRenderDevice;
		
		MacosxGraphicsDriver(MacosxAppDriver*,SexyAppBase*);
		virtual ~MacosxGraphicsDriver();
		
		bool					Is3D();
		
		int						GetVersion();

		virtual uint32					GetRenderModeFlags();

		virtual void					SetRenderModeFlags(uint32);

		virtual ERenderMode				GetRenderMode();
		
		virtual void					SetRenderMode(ERenderMode inRenderMode);

		virtual std::string				GetRenderModeString(ERenderMode inRenderMode,
															uint32 inRenderModeFlags,
															bool inIgnoreMode=false,
															bool inIgnoreFlags=false);
		
		virtual void					AddDeviceImage(DeviceImage* theDDImage);
		
		virtual void					RemoveDeviceImage(DeviceImage* theDDImage);
		
		virtual void					Remove3DData(MemoryImage* theImage); 
		
		virtual DeviceImage*			GetScreenImage();
				
		virtual void					WindowResize(int theWidth, int theHeight);	
		
		virtual void					ResizeAfterScreenModeSwitch();
		
		virtual bool					Redraw(Rect* theClipRect = NULL);		
		
		virtual void					RemapMouse(int& theX, int& theY);
		
		virtual bool					SetCursorImage(Image* theImage);
		
		virtual void					SetCursorPos(int theCursorX, int theCursorY);
		
		virtual void					RemoveShader(const void* theShader);

		virtual RenderEffectDefinition*	CreateRenderEffectDefinition(uint32 theDataLen, const void* theData, const char* theSrc);

		virtual DeviceSurface*			CreateDeviceSurface();
		
		virtual NativeDisplay*			GetNativeDisplayInfo();
		
		virtual RenderDevice*			GetRenderDevice();
		
		virtual RenderDevice3D*			GetRenderDevice3D();
		
		virtual Ratio					GetAspectRatio();
		
		virtual int						GetDisplayWidth();
		
		virtual	int						GetDisplayHeight();
		
		virtual CritSect&				GetCritSect();
		
		virtual Mesh*					LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);
		
		virtual void					AddMesh(Mesh* theMesh) {};
		
		virtual void					RemoveMesh(Mesh* theMesh) {};
		
#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
#endif
		void Init();
		
		DeviceImage*					GetImageFromResStream(const std::string& theFileName, 
															  void* theTextureBacking,
															  ResStreamFileGPULocationInfo* theLocationInfo);
		
		const Rect&			GetPresentationRect() { return mPresentationRect; }
	protected:
		friend class		MacosxAppDriver;
		friend class		MacosxRenderDevice;
		friend class		GLStateManager;
		friend class		GLTextureData;
		
		ERenderMode			mRenderMode;
		uint32				mRenderModeFlags;
#ifndef RELEASEFINAL
		GraphicsMetrics		mGraphicsMetrics;
#endif
		MacosxAppDriver*	mAppDriver;
		SexyAppBase*		mApp;
		
		int					mWidth;
		int					mHeight;
		Ratio				mAspect;
		int					mDesktopWidth;
		int					mDesktopHeight;
		Ratio				mDesktopAspect;
		int					mDisplayWidth;
		int					mDisplayHeight;
		Ratio				mDisplayAspect;
		bool				mIsWidescreen;
		bool				mIsWindowed;
		
		
		int					mCursorX;
		int					mCursorY;
	
		CritSect			mCritSect;
		Rect				mPresentationRect;
		
		HRenderContext		mCurrentContext;
		
		DeviceImage*		mScreenImage;
		
		int					mWindowSizeWidth;
		int					mWindowSizeHeight;
		
	};
	
	
};

#endif
