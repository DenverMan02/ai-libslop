#ifndef BASEOPENGLSTATEMANAGER_H_INCLUDED
#define BASEOPENGLSTATEMANAGER_H_INCLUDED

#include "RenderStateManager.h"
#include "Graphics.h"
#include "DeviceStateConstants.h"
#include "Debug.h"
#include "GraphicsMetrics.h"

//when using this class you must include the proper OpenGL headers
// for your platform before instantiating the template

namespace Sexy 
{
	
	
	//version is an enum that enables/disables some features... 
	//primarily the templating exists so that two different versions
	//of the BaseOpenGLStateManager can exist with different opengl 
	//function linkages (because of the iPhone API)
	enum OPENGL_VERSION
	{ 
		VERSION_OPENGL_11,   //Macosx
		VERSION_OPENGLES_11, //iPhone 3G and earlier, Android-4?
		VERSION_OPENGLES_20, //iPhone 3GS and iPad, Android-5 & later
	};
	
	enum OPENGL_TRANSFORM
	{
		OGL_TRANSFORM_WORLD = 0,
		OGL_TRANSFORM_VIEW  = 1,
		OGL_TRANSFORM_PROJECTION = 2,
		OGL_TRANSFORM_TEXTURE0 = 3,
		OGL_TRANSFORM_TEXTURE1 = 4,
		OGL_TRANSFORM_TEXTURE2 = 5,
		OGL_TRANSFORM_TEXTURE3 = 6,
		OGL_TRANSFORM_TEXTURE4 = 7,
		OGL_TRANSFORM_TEXTURE5 = 8,
		OGL_TRANSFORM_TEXTURE6 = 9,
		OGL_TRANSFORM_TEXTURE7 = 10,
		
		OGL_TRANSFORM_ORTHOPROJ,
		
		OGL_TRANSFORM_COUNT,
	};
	
	template <OPENGL_VERSION version> class BaseOpenGLStateManager : public RenderStateManager
	{
	public:
		
		typedef BaseOpenGLStateManager<version> THIS_CLASS;
		
		
		
		enum EStateGroup
		{
			SG_RS, // [D3DRS] (uses SetRenderState)
			SG_TSS, // [D3DTSS][stage index] (uses SetTextureStageState)
			SG_SS, // [D3DSAMP][sampler index] (uses SetSamplerState)
			SG_LIGHT, // [ELightState][light index] (uses LightEnable and SetLight)
			SG_MATERIAL, // [EMaterialState] (uses SetMaterial)
			SG_STREAM, // [EStreamState][stream number] (uses SetStreamSource and SetStreamSourceFreq)
			SG_TRANSFORM, // [D3DTS][row number 0-3] (uses SetTransform)
			SG_VIEWPORT, // [EViewportState] (uses SetViewport)
			SG_MISC, // [EMiscState][variable, see individual state]
			SG_SCISSOR,
			
			SG_COUNT
		};
		
		enum
		{
			ST_COUNT_RS = 256, // (dword)
			ST_COUNT_TSS = 48, // (dword)
			ST_COUNT_SS = 16, // (dword)
			ST_COUNT_TRANSFORM = OGL_TRANSFORM_COUNT // (vector) 
		};
		
		enum ELightState
		{
			ST_LIGHT_ENABLED, // (dword bool)
			ST_LIGHT_TYPE, // (dword D3DLIGHT_)
			ST_LIGHT_DIFFUSE, // (vector RGBA)
			ST_LIGHT_SPECULAR, // (vector RGBA)
			ST_LIGHT_AMBIENT, // (vector RGBA)
			ST_LIGHT_POSITION, // (vector XYZ)
			ST_LIGHT_DIRECTION, // (vector XYZ)
			ST_LIGHT_RANGE, // (float)
			ST_LIGHT_FALLOFF, // (float)
			ST_LIGHT_ATTENUATION, // (vector Atten0 Atten1 Atten2)
			ST_LIGHT_ANGLES, // (vector Theta Phi)
			
			ST_COUNT_LIGHT
		};
		enum EMaterialState
		{
			ST_MAT_DIFFUSE, // (vector RGBA)
			ST_MAT_AMBIENT, // (vector RGBA)
			ST_MAT_SPECULAR, // (vector RGBA)
			ST_MAT_EMISSIVE, // (vector RGBA)
			ST_MAT_POWER, // (float)
			
			ST_COUNT_MAT
		};
		enum EStreamState
		{
			ST_STREAM_DATA, // (ptr)
			ST_STREAM_OFFSET, // (dword)
			ST_STREAM_STRIDE, // (dword)
			ST_STREAM_FREQ, // (dword)
			
			ST_COUNT_STREAM
		};
		enum EViewportState
		{
			ST_VIEWPORT_X, // (dword)
			ST_VIEWPORT_Y, // (dword)
			ST_VIEWPORT_WIDTH, // (dword)
			ST_VIEWPORT_HEIGHT, // (dword)
			ST_VIEWPORT_MINZ, // (float)
			ST_VIEWPORT_MAXZ, // (float)
			
			ST_COUNT_VIEWPORT
		};
		enum EScissorState
		{
			ST_SCISSOR_ENABLE, // (dword bool)
			ST_SCISSOR_X, // (dword)
			ST_SCISSOR_Y, // (dword)
			ST_SCISSOR_WIDTH, // (dword)
			ST_SCISSOR_HEIGHT, // (dword)
			ST_COUNT_SCISSOR
		};
		enum EMiscState
		{
			// single states
			ST_MISC_VERTEXFORMAT, // (dword) [0] (uses SetFVF)
			ST_MISC_VERTEXSIZE, // (dword) [0] (internal; automatically updated when FVF is set)
			ST_MISC_INDICES, // (ptr) [0] (uses SetIndices)
			ST_MISC_SHADERPROGRAM_ORTHO, // (GLuint) [0] 
			ST_MISC_SHADERPROGRAM_3D, // (GLuint) [0] 
			ST_MISC_TEXTUREPALETTE, // (dword) [0] (uses SetCurrentTexturePalette)
			ST_MISC_SCISSORRECT, // (vector left top right bottom) [0] (uses SetScissorRect)
			ST_MISC_NPATCHMODE, // (float) [0] (uses SetNPatchMode)
			//ST_MISC_VERTEXDECL, // (ptr) [0] (uses SetVertexDeclaration) // commented out; not using non-fvf vertex declarations, for compat reasons
			ST_MISC_SRCBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_DESTBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_BLTDEPTH, // (float) [0] (internal; depth buffer value used for 2D blt functions)
			ST_MISC_3DMODE, // (dword bool) [0] (internal, switches between managed ortho project and user set projection/model mats)
			ST_MISC_CULLMODE, //(dword)
			
			ST_MISC_USE_TEXSCALE,
			
			// array states
			ST_MISC_TEXTURE, // (dword) [sampler number] (uses SetTexture)
			ST_MISC_TEXTURE_SRC, //(dword) [sampler number]
			ST_MISC_TEXTURE_WRAP_S, // (dword) [sampler number)
			ST_MISC_TEXTURE_WRAP_T, // (dword) [sampler number)
			ST_MISC_TEXTURE_MIN_FILTER, // (dword) [sampler number)
			ST_MISC_TEXTURE_MAG_FILTER, // (dword) [sampler number)
			ST_MISC_TEXSCALE, //hardware scaling for texture coords in textures are pow2. may be temp until atlases work
			ST_MISC_PIXELSHADERCONST, // (vector) [register] (uses SetPixelShaderConstantF)
			ST_MISC_VERTEXSHADERCONST, // (vector) [register] (uses SetVertexShaderConstantF)
			ST_MISC_CLIPPLANE, // (vector) [clip plane index] (uses SetClipPlane)
			ST_MISC_TEXTUREREMAP, // (int) [sampler number] (internal; index of logical texture state that is actually used for this physical sampler)
			
			ST_MISC_ATLASENABLEDANDBASE, // (vector) [sampler number] (internal; x = 1.0 for atlas enabled or 0.0 for disabled, y = unused, z = base.x, w = base.y)
			ST_MISC_ATLASUV, // (vector) [sampler number] (internal; atlasing vectors, u.x, u.y, v.x, v.y)
			
			ST_COUNT_MISC,
			ST_COUNT_MISC_SINGLE = ST_MISC_TEXTURE // first of the array states
		};
		
		typedef std::vector<State> StateVector;
		std::vector<State> mRenderStates;
		std::vector<StateVector> mTextureStageStates;
		std::vector<StateVector> mSamplerStates;
		std::vector<StateVector> mLightStates;
		std::vector<State> mMaterialStates;
		std::vector<StateVector> mStreamStates;
		std::vector<StateVector> mTransformStates;
		std::vector<State> mViewportStates;
		std::vector<StateVector> mMiscStates;
		std::vector<State> mScissorStates;

		void InitRenderState(uint32_t inIndex, const std::string& inStateName, uint32_t inHardwareDefaultValue, bool inHasContextDefault=false, uint32_t inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitRenderStateFloat(uint32_t inIndex, const std::string& inStateName, float inDefaultValue);
		void InitTextureStageState(uint32_t inFirstStage, uint32_t inLastStage, uint32_t inIndex, const std::string& inStateName, uint32_t inDefaultValue, bool inHasContextDefault=false, uint32_t inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitTextureStageStateFloat(uint32_t inFirstStage, uint32_t inLastStage, uint32_t inIndex, const std::string& inStateName, float inDefaultValue);
		void InitSamplerState(uint32_t inFirstStage, uint32_t inLastStage, uint32_t inIndex, const std::string& inStateName, uint32_t inDefaultValue, bool inHasContextDefault=false, uint32_t inContextDefaultValue=0, const char* inValueEnumName=0);

		virtual void InitStates()
		{
			mTextureUVScale = SexyVector2(1, 1);

			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glFrontFace(GL_CW);
						
			for (uint32 i=0; i<ST_COUNT_RS; ++i)
			{
				mRenderStates.push_back(State(this,SG_RS, i));
			}

			mRenderStates[SEXY3DRS_ZENABLE].Init((uint32_t)1,(uint32_t)0,"ZENABLE","");
			mRenderStates[SEXY3DRS_ZWRITEENABLE].Init((uint32_t)1,(uint32_t)0,"ZWRITEENABLE","");
			mRenderStates[SEXY3DRS_ALPHATESTENABLE].Init((uint32_t)0,(uint32_t)0,"ALPHATESTENABLE","");
			mRenderStates[SEXY3DRS_ZFUNC].Init((uint32_t)Graphics3D::COMPARE_LESSEQUAL,"ZFUNC","");
			mRenderStates[SEXY3DRS_ALPHAREF].Init((uint32_t)0,(uint32_t)0,"ALPHAREF","");
			mRenderStates[SEXY3DRS_ALPHAFUNC].Init((uint32_t)Graphics3D::COMPARE_ALWAYS,(uint32_t)Graphics3D::COMPARE_ALWAYS,"ALPHAFUNC","");
			//mRenderStates[SEXY3DRS_SRCBLEND].Init((uint32_t)Graphics3D::BLEND_ONE,(uint32_t)Graphics3D::BLEND_SRCALPHA,"SRCBLEND","Sexy::Graphics3D::EBlendMode");
			//mRenderStates[SEXY3DRS_DESTBLEND].Init((uint32_t)Graphics3D::BLEND_ZERO,(uint32_t)Graphics3D::BLEND_INVSRCALPHA,"DESTBLEND","Sexy::Graphics3D::EBlendMode");
			mRenderStates[SEXY3DRS_SRCBLEND].Init((uint32_t)Graphics3D::BLEND_ZERO,"SRCBLEND","Sexy::Graphics3D::EBlendMode");
			mRenderStates[SEXY3DRS_DESTBLEND].Init((uint32_t)Graphics3D::BLEND_ZERO,"DESTBLEND","Sexy::Graphics3D::EBlendMode");
			mRenderStates[SEXY3DRS_COLORWRITEENABLE].Init((uint32_t)0xF,"COLORWRITE","");

			for (uint32 i=0; i<ST_COUNT_TRANSFORM; ++i)
			{
				mTransformStates.push_back(StateVector());
			}
			
			for (uint32 i=0; i<ST_COUNT_TRANSFORM; ++i)
			{
				for (uint32 j=0; j<4; ++j)
				{
					mTransformStates[i].push_back(State(this, SG_TRANSFORM, i, j));
				}
			}
			
			for (uint32 i=0; i<ST_COUNT_TRANSFORM; ++i)
			{
				std::string aName;
				if (i == OGL_TRANSFORM_WORLD) aName = "WORLD";
				else if (i == OGL_TRANSFORM_VIEW) aName = "VIEW";
				else if (i == OGL_TRANSFORM_PROJECTION) aName = "PROJECTION";
				else if (i == OGL_TRANSFORM_ORTHOPROJ) aName = "ORTHOPROJECTION";
				else if ((i >= OGL_TRANSFORM_TEXTURE0) && (i <= OGL_TRANSFORM_TEXTURE7)) aName = StrFormat("TEXTURE%d", i - OGL_TRANSFORM_TEXTURE0);
				else aName = StrFormat("%d",i);
				
				for (uint32 j=0; j<4; ++j)
				{
					mTransformStates[i][j].Init(StateValue(0.0f,0.0f,0.0f,0.0f), StrFormat("TRANSFORM:%s[%d]",aName.c_str(), j));
					
				}
			}
			
			for (uint32 i=0; i<ST_COUNT_VIEWPORT; ++i)
			{
				mViewportStates.push_back(State(this,SG_VIEWPORT,i));
			}

			mViewportStates[ST_VIEWPORT_X].Init((uint32_t)0, "VIEWPORT:X");
			mViewportStates[ST_VIEWPORT_Y].Init((uint32_t)0, "VIEWPORT:Y");
			mViewportStates[ST_VIEWPORT_WIDTH].Init((uint32_t)800, "VIEWPORT:WIDTH");
			mViewportStates[ST_VIEWPORT_HEIGHT].Init((uint32_t)600, "VIEWPORT:HEIGHT");
			mViewportStates[ST_VIEWPORT_MINZ].Init(0.0f,"VIEWPORT_MINZ");
			mViewportStates[ST_VIEWPORT_MAXZ].Init(1.0f,"VIEWPORT_MAXZ");
			
			for (uint32 i=0; i<ST_COUNT_SCISSOR; ++i)
			{
				mScissorStates.push_back(State(this,SG_SCISSOR,i));
			}

			mScissorStates[ST_SCISSOR_X].Init((uint32_t)0, "SCISSOR:X");
			mScissorStates[ST_SCISSOR_Y].Init((uint32_t)0, "SCISSOR:Y");
			mScissorStates[ST_SCISSOR_WIDTH].Init((uint32_t)800, "SCISSOR:WIDTH");
			mScissorStates[ST_SCISSOR_HEIGHT].Init((uint32_t)600, "SCISSOR:HEIGHT");
			mScissorStates[ST_SCISSOR_ENABLE].Init((uint32_t)0,"SCISSOR:ENABLED");

			const uint32 kSamplerStages = 8;
			
			for (uint32 i=0; i<ST_COUNT_MISC; ++i)
			{
				mMiscStates.push_back(StateVector());
			}
			
			for (uint32 i=0; i<ST_COUNT_MISC_SINGLE; ++i)
			{
				mMiscStates[i].push_back(State(this, SG_MISC, i));
			}


			mMiscStates[ST_MISC_VERTEXFORMAT][0].Init((uint32_t)0,"MISC:VERTEXFORMAT");
			mMiscStates[ST_MISC_VERTEXSIZE][0].Init((uint32_t)0,"MISC:VERTEXSIZE");
			mMiscStates[ST_MISC_SHADERPROGRAM_ORTHO][0].Init((uint32_t)0,"MISC:SHADERPROGRAM_ORTHO");
			mMiscStates[ST_MISC_SHADERPROGRAM_3D][0].Init((uint32_t)0,"MISC:SHADERPROGRAM_3D");
			mMiscStates[ST_MISC_BLTDEPTH][0].Init(0.0f,0.5f,"MISC:BLTDEPTH");
			mMiscStates[ST_MISC_3DMODE][0].Init((uint32_t)0,"MISC:3DMODE");
			mMiscStates[ST_MISC_CULLMODE][0].Init((uint32_t)0,"MISC:CULLMODE");

			mMiscStates[ST_MISC_SRCBLENDOVERRIDE][0].Init((uint32_t)Graphics3D::BLEND_DEFAULT,"MISC:SRCBLENDOVERRIDE","Sexy::Graphics3D::EBlendMode");
			mMiscStates[ST_MISC_DESTBLENDOVERRIDE][0].Init((uint32_t)Graphics3D::BLEND_DEFAULT,"MISC:DESTBLENDOVERRIDE","Sexy::Graphics3D::EBlendMode");
			mMiscStates[ST_MISC_BLTDEPTH][0].Init(0.0f,"MISC:BLTDEPTH");

			mMiscStates[ST_MISC_USE_TEXSCALE][0].Init((uint32_t)0,"MISC:USE_TEXSCALE");


			const uint32 kNumTextures = kSamplerStages;
			
			for (uint32 i=0; i<kNumTextures; ++i) 
			{
				mMiscStates[ST_MISC_TEXTURE].push_back(State(this, SG_MISC, ST_MISC_TEXTURE, i)); 
				mMiscStates[ST_MISC_TEXTURE_SRC].push_back(State(this, SG_MISC, ST_MISC_TEXTURE_SRC, i));
				mMiscStates[ST_MISC_TEXTURE_WRAP_S].push_back(State(this, SG_MISC, ST_MISC_TEXTURE_WRAP_S, i)); 
				mMiscStates[ST_MISC_TEXTURE_WRAP_T].push_back(State(this, SG_MISC, ST_MISC_TEXTURE_WRAP_T, i)); 
				mMiscStates[ST_MISC_TEXTURE_MAG_FILTER].push_back(State(this, SG_MISC, ST_MISC_TEXTURE_MAG_FILTER, i)); 
				mMiscStates[ST_MISC_TEXTURE_MIN_FILTER].push_back(State(this, SG_MISC, ST_MISC_TEXTURE_MIN_FILTER, i)); 
				mMiscStates[ST_MISC_TEXSCALE].push_back(State(this, SG_MISC, ST_MISC_TEXSCALE, i)); 
			}
			
			for (uint32 i=0; i<kNumTextures; ++i)
			{
				mMiscStates[ST_MISC_TEXTURE][i].Init((uint32_t)0,StrFormat("MISC:TEXTURE[%d]",i));
				mMiscStates[ST_MISC_TEXTURE_SRC][i].Init((uint32_t)0,StrFormat("MISC:TEXTURE_SRC[%d]",i));
				mMiscStates[ST_MISC_TEXTURE_WRAP_S][i].Init((uint32_t)GL_CLAMP_TO_EDGE,StrFormat("MISC:TEXTURE_WRAP_S[%d]",i));
				mMiscStates[ST_MISC_TEXTURE_WRAP_T][i].Init((uint32_t)GL_CLAMP_TO_EDGE,StrFormat("MISC:TEXTURE_WRAP_T[%d]",i));
				mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][i].Init((uint32_t)GL_LINEAR,StrFormat("MISC:TEXTURE_MIN_FILTER[%d]",i));
				mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][i].Init((uint32_t)GL_LINEAR,StrFormat("MISC:TEXTURE_MAG_FILTER[%d]",i));
				mMiscStates[ST_MISC_TEXSCALE][i].Init(StateValue(1.0f,1.0f,1.0f,1.0f),StrFormat("MISC:TEXSCALE[%d]",i));
			}

			for (uint32_t i=0; i<kNumTextures; ++i)
			{
				mMiscStates[ST_MISC_ATLASENABLEDANDBASE].push_back(State(this, SG_MISC, ST_MISC_ATLASENABLEDANDBASE, i));
				mMiscStates[ST_MISC_ATLASUV].push_back(State(this, SG_MISC, ST_MISC_ATLASUV, i));
			}
			for (uint32_t i=0; i<kNumTextures; ++i)
			{
				mMiscStates[ST_MISC_ATLASENABLEDANDBASE][i].Init(StateValue(0.f, 0.f, 0.f, 0.f), StrFormat("MISC:ATLASENABLEDANDBASE[%d]", i));
				mMiscStates[ST_MISC_ATLASUV][i].Init(StateValue(0.f, 0.f, 1.f, 1.f), StrFormat("MISC:ATLASUV[%d]", i));
			}
		}
		

		virtual void ResetStates()
		{
#define RESET_STATES(xName) \
		{ \
			ulong iCount = xName.size(); \
			for (ulong i=0; i<iCount; ++i) \
			{ \
				xName[i].Reset(); \
			} \
		}

#define RESET_STATEVECTORS(xName) \
		{ \
			ulong iCount = xName.size(); \
			for (ulong i=0; i<iCount; ++i) \
			{ \
				ulong jCount = xName[i].size(); \
				for (ulong j=0; j<jCount; ++j) \
				{ \
					xName[i][j].Reset(); \
				} \
			} \
		}
			
			RESET_STATES(mRenderStates);
			RESET_STATES(mViewportStates);
			RESET_STATES(mScissorStates);
			RESET_STATEVECTORS(mMiscStates);
		}
		
		
		static GLuint GetGLCompareFunc(Graphics3D::ECompareFunc theCompareMode)
		{
			switch (theCompareMode) 
			{
				default:
				case Graphics3D::COMPARE_ALWAYS:
					return GL_ALWAYS;
				case Graphics3D::COMPARE_LESS:
					return GL_LESS;
				case Graphics3D::COMPARE_LESSEQUAL:
					return GL_LEQUAL;
				case Graphics3D::COMPARE_GREATER:
					return GL_GREATER;
				case Graphics3D::COMPARE_GREATEREQUAL:
					return GL_GEQUAL;
				case Graphics3D::COMPARE_NEVER:
					return GL_NEVER;
				case Graphics3D::COMPARE_NOTEQUAL:
					return GL_NOTEQUAL;

			}
            
		}
        
		static bool DoCommitRenderState(RenderStateManager::State* inState)
		{
			DBG_ASSERT(inState->mContext[0] == SG_RS);
			THIS_CLASS* m = (THIS_CLASS*)inState->mManager;
			
			SEXY3DRSS stateId = (SEXY3DRSS)inState->mContext[1];
			
			switch (stateId)
			{
				case SEXY3DRS_ZENABLE:
					if (inState->GetDword() != 0)
					{
						glEnable(GL_DEPTH_TEST);
					}
					else
					{
						glDisable(GL_DEPTH_TEST);
					}
					inState->ClearDirty();

					break;
				case SEXY3DRS_ZWRITEENABLE:
					if (inState->GetDword() != 0)
					{
						glDepthMask(GL_TRUE);
					}
					else
					{
						glDepthMask(GL_FALSE);
					}
					inState->ClearDirty();
					
					break;
				case SEXY3DRS_ZFUNC:
					glDepthFunc(GetGLCompareFunc((Graphics3D::ECompareFunc)inState->GetDword()));
					inState->ClearDirty();
					
					break;
				case SEXY3DRS_ALPHATESTENABLE:
					//jvw todo: opengl es2 needs to do this in a shader
#ifndef OPENGLES2
					if (inState->GetDword() != 0)
					{
						glEnable(GL_ALPHA_TEST);
					}
					else 
					{
						glDisable(GL_ALPHA_TEST);
					}
#endif
					inState->ClearDirty();
					
					break;
				case SEXY3DRS_ALPHAREF:
				case SEXY3DRS_ALPHAFUNC:
				{
#ifndef OPENGLES2
					uint32 anAlphaRefInt = m->mRenderStates[SEXY3DRS_ALPHAREF].GetDword();
					float anAlphaRef = (float)anAlphaRefInt / 255.0f;
					
					glAlphaFunc(GetGLCompareFunc((Graphics3D::ECompareFunc)m->mRenderStates[SEXY3DRS_ALPHAFUNC].GetDword()), anAlphaRef);
					m->mRenderStates[SEXY3DRS_ALPHAFUNC].ClearDirty(true);
					m->mRenderStates[SEXY3DRS_ALPHAREF].ClearDirty(true);
#endif
				}
					break;
				case SEXY3DRS_SRCBLEND:
				case SEXY3DRS_DESTBLEND:
					SetGLBlendState(m->mRenderStates[SEXY3DRS_SRCBLEND].GetDword(),m->mRenderStates[SEXY3DRS_DESTBLEND].GetDword());
					
					m->mRenderStates[SEXY3DRS_SRCBLEND].ClearDirty(true);
					m->mRenderStates[SEXY3DRS_DESTBLEND].ClearDirty(true);
					
					break;
				case SEXY3DRS_COLORWRITEENABLE:
				{
					auto channels = inState->GetDword();
					glColorMask((channels&0x8)!=0,
								(channels&0x4)!=0, 
								(channels&0x2)!=0, (channels&0x1)!=0);
					inState->ClearDirty();
				}
					break;
                    
				default:
					inState->ClearDirty();
					break;
			}
			return true;
		}
		
		static bool DoCommitTransformState(RenderStateManager::State* inState)
		{
			DBG_ASSERT(inState->mContext[0] == SG_TRANSFORM);
			THIS_CLASS* m = (THIS_CLASS*)inState->mManager;
			
			//get the current 3D mode. Transforms can only be committed in 3D mode
			OPENGL_TRANSFORM stateId = (OPENGL_TRANSFORM)inState->mContext[1];
			
			if (m->mMiscStates[ST_MISC_3DMODE][0].GetDword() == 0 && stateId!=OGL_TRANSFORM_ORTHOPROJ) 
			{
				inState->ClearDirty();
				return true;
			}
			
			
			
			SexyMatrix4 mat;
			State* s;
			s = &m->mTransformStates[stateId][0]; s->GetVector(mat.m00, mat.m01, mat.m02, mat.m03); s->ClearDirty(true);
			s = &m->mTransformStates[stateId][1]; s->GetVector(mat.m10, mat.m11, mat.m12, mat.m13); s->ClearDirty(true);
			s = &m->mTransformStates[stateId][2]; s->GetVector(mat.m20, mat.m21, mat.m22, mat.m23); s->ClearDirty(true);
			s = &m->mTransformStates[stateId][3]; s->GetVector(mat.m30, mat.m31, mat.m32, mat.m33); s->ClearDirty(true);
			
			//on GL20 these will need to be set to the shader constant fields
#ifndef OPENGLES2
			switch (stateId) {
				case OGL_TRANSFORM_WORLD:
				case OGL_TRANSFORM_VIEW:
				{
					glMatrixMode(GL_MODELVIEW);
					//get the matrix for the view and clear it's dirty flag
			
					OPENGL_TRANSFORM anOtherState = OGL_TRANSFORM_VIEW;
					if (stateId == OGL_TRANSFORM_VIEW)
					{
						anOtherState = OGL_TRANSFORM_WORLD;
					}
					SexyMatrix4 anOtherMat;
					s = &m->mTransformStates[anOtherState][0]; s->GetVector(anOtherMat.m00, anOtherMat.m01, anOtherMat.m02, anOtherMat.m03); s->ClearDirty(true);
					s = &m->mTransformStates[anOtherState][1]; s->GetVector(anOtherMat.m10, anOtherMat.m11, anOtherMat.m12, anOtherMat.m13); s->ClearDirty(true);
					s = &m->mTransformStates[anOtherState][2]; s->GetVector(anOtherMat.m20, anOtherMat.m21, anOtherMat.m22, anOtherMat.m23); s->ClearDirty(true);
					s = &m->mTransformStates[anOtherState][3]; s->GetVector(anOtherMat.m30, anOtherMat.m31, anOtherMat.m32, anOtherMat.m33); s->ClearDirty(true);
					
					if (stateId == OGL_TRANSFORM_VIEW)
					{
						mat = anOtherMat * mat;
					}
					else 
					{
						mat = mat * anOtherMat;
					}
#if USE_FIXED_POINT
					float m[] =
					{
						mat.m00,mat.m01,mat.m02,mat.m03,
						mat.m10,mat.m11,mat.m12,mat.m13,
						mat.m20,mat.m21,mat.m22,mat.m23,
						mat.m30,mat.m31,mat.m32,mat.m33
					};
					glLoadMatrixf((GLfloat*)m);
#else //#if USE_FIXED_POINT
					glLoadMatrixf((GLfloat*)mat.m);
#endif//#if USE_FIXED_POINT

				}
					break;
				case OGL_TRANSFORM_PROJECTION:
				{
					glMatrixMode(GL_PROJECTION);
					
                    mat.m11 = -mat.m11;
#if USE_FIXED_POINT
                    float m[] =
					{
						mat.m00,mat.m01,mat.m02,mat.m03,
						mat.m10,mat.m11,mat.m12,mat.m13,
						mat.m20,mat.m21,mat.m22,mat.m23,
						mat.m30,mat.m31,mat.m32,mat.m33
					};
					glLoadMatrixf((GLfloat*)m);
#else//#if USE_FIXED_POINT
					glLoadMatrixf((GLfloat*)mat.m);
#endif//#if USE_FIXED_POINT
					
				}
					break;
				case OGL_TRANSFORM_TEXTURE0: //only 0 is supported for now
				{
					glMatrixMode(GL_TEXTURE);
#if USE_FIXED_POINT
					float m[] =
					{
						mat.m00,mat.m01,mat.m02,mat.m03,
						mat.m10,mat.m11,mat.m12,mat.m13,
						mat.m20,mat.m21,mat.m22,mat.m23,
						mat.m30,mat.m31,mat.m32,mat.m33
					};
					glLoadMatrixf((GLfloat*)m);
#else //#if USE_FIXED_POINT
					glLoadMatrixf((GLfloat*)mat.m);
#endif//#if USE_FIXED_POINT
				}
					break;
				case OGL_TRANSFORM_ORTHOPROJ:
				{
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
#if USE_FIXED_POINT
					float m[] =
					{
						mat.m00,mat.m01,mat.m02,mat.m03,
						mat.m10,mat.m11,mat.m12,mat.m13,
						mat.m20,mat.m21,mat.m22,mat.m23,
						mat.m30,mat.m31,mat.m32,mat.m33
					};
					glLoadMatrixf((GLfloat*)m);
#else //#if USE_FIXED_POINT
					glLoadMatrixf((GLfloat*)mat.m);
#endif //#if USE_FIXED_POINT
				}
					break;
				default:
					break;
			}
			
#endif //ifndef OPENGLES2
			
			return true;
		}
		
		static bool DoCommitViewportState(RenderStateManager::State* inState)
		{
			DBG_ASSERT(inState->mContext[0] == SG_VIEWPORT);
			THIS_CLASS* m = (THIS_CLASS*)inState->mManager;
			
			int x;
			int y;
			int width;
			int height;
			float minZ;
			float maxZ;
			
			State* s;
			
			s = &m->mViewportStates[ST_VIEWPORT_X]; x = s->GetDword(); s->ClearDirty(true);
			s = &m->mViewportStates[ST_VIEWPORT_Y]; y = s->GetDword(); s->ClearDirty(true);
			s = &m->mViewportStates[ST_VIEWPORT_WIDTH]; width = s->GetDword(); s->ClearDirty(true);
			s = &m->mViewportStates[ST_VIEWPORT_HEIGHT]; height = s->GetDword(); s->ClearDirty(true);
			s = &m->mViewportStates[ST_VIEWPORT_MINZ]; minZ = s->GetFloat(); s->ClearDirty(true);
			s = &m->mViewportStates[ST_VIEWPORT_MAXZ]; maxZ = s->GetFloat(); s->ClearDirty(true);

			
			glViewport(x, y, width, height);
			glDepthRangef(minZ, maxZ);
			
			return true;
		}
		
		static bool DoCommitScissorState(RenderStateManager::State* inState)
		{
			DBG_ASSERT(inState->mContext[0] == SG_SCISSOR);
			THIS_CLASS* m = (THIS_CLASS*)inState->mManager;
			
			int enabled;
			int x;
			int y;
			int width;
			int height;

			State* s;
			
			s = &m->mScissorStates[ST_SCISSOR_X]; x = s->GetDword(); s->ClearDirty(true);
			s = &m->mScissorStates[ST_SCISSOR_Y]; y = s->GetDword(); s->ClearDirty(true);
			s = &m->mScissorStates[ST_SCISSOR_WIDTH]; width = s->GetDword(); s->ClearDirty(true);
			s = &m->mScissorStates[ST_SCISSOR_HEIGHT]; height = s->GetDword(); s->ClearDirty(true);
			s = &m->mScissorStates[ST_SCISSOR_ENABLE]; enabled = s->GetDword(); s->ClearDirty(true);
			
			
			if (enabled)
				glEnable(GL_SCISSOR_TEST);
			else 
				glDisable(GL_SCISSOR_TEST);

			glScissor(x, y, width, height);
			
			
			return true;
		}
		
		static bool DoGLState(RenderStateManager::State* inState)
		{
			/*assert(inState->mContext[0] == SG_RS);
			 D3DStateManager9* m = (D3DStateManager9*)inState->mManager;
			 
			 bool result = !D3DInterface::CheckDXError(
			 m->mDevice->SetRenderState((D3DRENDERSTATETYPE)inState->mContext[1], inState->GetDword())
			 , "SetRenderState");
			 inState->ClearDirty();*/
			
			return true;
		}
		
		static bool DoCommitMiscState(RenderStateManager::State* inState)
		{
			DBG_ASSERT(inState->mContext[0] == SG_MISC);
			THIS_CLASS* m = (THIS_CLASS*)inState->mManager;

			auto stateId = inState->mContext[1];
			auto subIndex = inState->mContext[2];

			switch (stateId)
			{
				case ST_MISC_VERTEXFORMAT:
					inState->ClearDirty();
					break;
				case ST_MISC_VERTEXSIZE:
				{
					inState->ClearDirty();
				}
					break;
				case ST_MISC_SHADERPROGRAM_3D:
					if (m->mMiscStates[ST_MISC_3DMODE][0].GetDword() == 1)
					{
#ifdef SUPPORT_GLSL_SHADERS
						glUseProgram((GLuint)inState->GetDword());
#endif
					}
					inState->ClearDirty();
					break;
				case ST_MISC_SHADERPROGRAM_ORTHO:
					if (m->mMiscStates[ST_MISC_3DMODE][0].GetDword() == 0)
					{
#ifdef SUPPORT_GLSL_SHADERS
						if ((GLuint)inState->GetDword()==0)
						{
							m->SetDefaultShader();
						}
						else
						{
							glUseProgram((GLuint)inState->GetDword());
						}
#endif
					}					
					inState->ClearDirty();
					break;
				case ST_MISC_3DMODE:
					
					
					if (m->mMiscStates[ST_MISC_3DMODE][0].GetDword() == 1)
					{
						m->mTransformStates[OGL_TRANSFORM_WORLD][0].SetDirty();
						m->mTransformStates[OGL_TRANSFORM_VIEW][0].SetDirty();
						m->mTransformStates[OGL_TRANSFORM_PROJECTION][0].SetDirty();
						
						m->mMiscStates[ST_MISC_SHADERPROGRAM_3D][0].SetDirty();
						
						//force commit the state
						DoCommitTransformState(&m->mTransformStates[OGL_TRANSFORM_WORLD][0]);
						DoCommitTransformState(&m->mTransformStates[OGL_TRANSFORM_PROJECTION][0]);
					}
					else 
					{
						m->mMiscStates[ST_MISC_SHADERPROGRAM_ORTHO][0].SetDirty();
						m->mTransformStates[OGL_TRANSFORM_ORTHOPROJ][0].SetDirty();
						DoCommitTransformState(&m->mTransformStates[OGL_TRANSFORM_ORTHOPROJ][0]);
						//m->mMiscStates[ST_MISC_ORTHOPROJECTION][0].SetDirty();
						//DoCommitMiscState(&m->mMiscStates[ST_MISC_ORTHOPROJECTION][0]);
					}

					
					m->mMiscStates[ST_MISC_3DMODE][0].ClearDirty();
					break;
				case ST_MISC_CULLMODE:
				{
					auto value = inState->GetDword();
					if (value == 0)
					{
						glDisable(GL_CULL_FACE);
					}
					else 
					{
						glEnable(GL_CULL_FACE);
						if (value & 0x01)
						{
							if (value & 0x02)
							{
								glCullFace(GL_FRONT_AND_BACK);
							}
							else 
							{
								glCullFace(GL_FRONT);
							}

							
						}
						else 
						{
							glCullFace(GL_BACK);
						}

						
					}

					
					m->mMiscStates[ST_MISC_CULLMODE][0].ClearDirty();
				}
					break;
				case ST_MISC_TEXTURE:
					
#ifndef RELEASEFINAL
					if (m->mMetrics!=NULL)
					{
						m->mMetrics->GetCounter(GraphicsMetrics::CT_SetTextureCalls)++;
					}
#endif
					
					if (inState->GetDword() == 0)
					{
						glActiveTexture(GL_TEXTURE0 + subIndex);
						
						//might need to set other srcs to null here as well
						glBindTexture(GL_TEXTURE_2D, 0);
#ifndef OPENGLES2
                        //CN - GL_TEXTURE_2D deprecated in ES 2.0 as there's no fixed function
                        //     pipeline, samplers are declared in fragment shaders
						glDisable(GL_TEXTURE_2D);
#endif
					}
					else 
					{
						GLuint aTex = inState->GetDword();
						glActiveTexture(GL_TEXTURE0 + subIndex);
						
						GLuint aSrc = m->mMiscStates[ST_MISC_TEXTURE_SRC][subIndex].GetDword();
						glBindTexture(aSrc, aTex);

#ifndef OPENGLES2
                        //CN - GL_TEXTURE_2D deprecated in ES 2.0 as there's no fixed function
                        //     pipeline, samplers are declared in fragment shaders
						glEnable(aSrc);
#endif
						
						glTexParameteri(aSrc, GL_TEXTURE_WRAP_S, m->mMiscStates[ST_MISC_TEXTURE_WRAP_S][subIndex].GetDword());
						glTexParameteri(aSrc, GL_TEXTURE_WRAP_T, m->mMiscStates[ST_MISC_TEXTURE_WRAP_T][subIndex].GetDword());
						glTexParameteri(aSrc, GL_TEXTURE_MAG_FILTER, m->mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][subIndex].GetDword());
						glTexParameteri(aSrc, GL_TEXTURE_MIN_FILTER, m->mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][subIndex].GetDword());
						m->mMiscStates[ST_MISC_TEXTURE_WRAP_S][subIndex].ClearDirty(true);
						m->mMiscStates[ST_MISC_TEXTURE_WRAP_T][subIndex].ClearDirty(true);
						m->mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][subIndex].ClearDirty(true);
						m->mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][subIndex].ClearDirty(true);
						
#ifndef OPENGLES2
						if (subIndex==0)
							glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

#endif
						
					}
					inState->ClearDirty();
					break;
				case ST_MISC_TEXTURE_WRAP_S:
				{
					GLuint aSrc = m->mMiscStates[ST_MISC_TEXTURE_SRC][subIndex].GetDword();
					glActiveTexture(GL_TEXTURE0 + subIndex);
					
					glTexParameteri(aSrc, GL_TEXTURE_WRAP_S, inState->GetDword());
					inState->ClearDirty();
				}
					break;
				case ST_MISC_TEXTURE_WRAP_T:
				{
					GLuint aSrc = m->mMiscStates[ST_MISC_TEXTURE_SRC][subIndex].GetDword();
					glActiveTexture(GL_TEXTURE0 + subIndex);
					glTexParameteri(aSrc, GL_TEXTURE_WRAP_T, inState->GetDword());
					inState->ClearDirty();
				}
					break;
				case ST_MISC_TEXTURE_MAG_FILTER:
				{
					GLuint aSrc = m->mMiscStates[ST_MISC_TEXTURE_SRC][subIndex].GetDword();
					glActiveTexture(GL_TEXTURE0 + subIndex);
					glTexParameteri(aSrc, GL_TEXTURE_MAG_FILTER, inState->GetDword());
					inState->ClearDirty();
				}
					break;
				case ST_MISC_TEXTURE_MIN_FILTER:
				{
					GLuint aSrc = m->mMiscStates[ST_MISC_TEXTURE_SRC][subIndex].GetDword();
					glActiveTexture(GL_TEXTURE0 + subIndex);
					glTexParameteri(aSrc, GL_TEXTURE_MIN_FILTER, inState->GetDword());
					inState->ClearDirty();
				}
					break;
				case ST_MISC_USE_TEXSCALE:
					/*glMatrixMode(GL_TEXTURE);
					glLoadIdentity();

					if (inState->GetDword() == 1)
					{
						float scale_x, scale_y, scale_z, scale_w;
						m->mMiscStates[ST_MISC_TEXSCALE][0].GetVector(scale_x,scale_y,scale_z,scale_w);
						glScalef(scale_x, scale_y, 1.0f);
					}
					
					glMatrixMode(GL_MODELVIEW);*/
					inState->ClearDirty();
					break;
						
				default:
					inState->ClearDirty();
					break;
			}
			
			
			return true;
		}

		
		virtual State::FCommitFunc GetCommitFunc(State* inState) override
		{
			switch (inState->mContext[0]) 
			{
				case SG_RS:
					return DoCommitRenderState;
				case SG_MISC:
                {
                    if (inState->mContext[1]==ST_MISC_ATLASENABLEDANDBASE || 
                        inState->mContext[1]==ST_MISC_ATLASUV)
                        return NULL;
					return DoCommitMiscState;
                }
				case SG_TRANSFORM:
					return DoCommitTransformState;
				case SG_VIEWPORT:
					return DoCommitViewportState;
				case SG_SCISSOR:
					return DoCommitScissorState;
				default:
					return DoGLState;
			}
			
		}
		
	public:
		BaseOpenGLStateManager()
		{
#ifndef RELEASEFINAL
			mMetrics = NULL;
#endif
		}
		
		virtual void Init() override
		{
			InitStates();
		}
		virtual void Reset() override
		{
			ResetStates();
		}
		
		void SetBlendOverride(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend)
		{
			mMiscStates[ST_MISC_SRCBLENDOVERRIDE][0].SetValue((uint32_t)inSrcBlend);
			mMiscStates[ST_MISC_DESTBLENDOVERRIDE][0].SetValue((uint32_t)inDestBlend);
		}
		
		void SetBltDepth(float inDepth)
		{
			 mMiscStates[ST_MISC_BLTDEPTH][0].SetValue(inDepth);
		}

		void GetBlendOverride(Graphics3D::EBlendMode& outSrcBlend, Graphics3D::EBlendMode& outDestBlend)
		{
			outSrcBlend = (Graphics3D::EBlendMode)mMiscStates[ST_MISC_SRCBLENDOVERRIDE][0].GetDword();
			outDestBlend = (Graphics3D::EBlendMode)mMiscStates[ST_MISC_DESTBLENDOVERRIDE][0].GetDword();
		}
		

		
		inline float GetBltDepth()
		{
			return mMiscStates[ST_MISC_BLTDEPTH][0].GetFloat();
		}
		
		
		
		uint32 GetRenderState(uint32 theRenderState)
		{
			return mRenderStates[theRenderState].GetDword();
			/*switch (theRenderState) 
			{
				case SEXY3DRS_SRCBLEND:
					return mSrcBlendState;
				case SEXY3DRS_DESTBLEND:
					return mDstBlendState;
				default:
					return 0;
			}*/
		}
		
		
		static void SetGLBlendState(uint32 theSrcBlend, uint32 theDstBlend)
		{
			GLenum sfactor;
			GLenum dfactor;
			switch (theSrcBlend) 
			{
				case Graphics3D::BLEND_SRCALPHA:
					sfactor = GL_SRC_ALPHA;
					break;
				case Graphics3D::BLEND_INVSRCALPHA:
					sfactor = GL_ONE_MINUS_SRC_ALPHA;
					break;
				case Graphics3D::BLEND_ONE:
					sfactor = GL_ONE;
					break;
				case Graphics3D::BLEND_ZERO:
					sfactor = GL_ZERO;
					break;
				case Graphics3D::BLEND_SRCCOLOR:
					sfactor = GL_SRC_COLOR;
					break;
				case Graphics3D::BLEND_INVSRCCOLOR:
					sfactor = GL_ONE_MINUS_SRC_COLOR;
					break;
				case Graphics3D::BLEND_DESTCOLOR:
					sfactor = GL_DST_COLOR;
					break;
				case Graphics3D::BLEND_INVDESTCOLOR:
					sfactor = GL_ONE_MINUS_DST_COLOR;
					break;
				case Graphics3D::BLEND_SRCALPHASAT:
					sfactor = GL_SRC_ALPHA_SATURATE;
					break;
				default:
					sfactor = GL_ONE;
					break;
			}
			
			switch (theDstBlend) 
			{
				case Graphics3D::BLEND_SRCALPHA:
					dfactor = GL_SRC_ALPHA;
					break;
				case Graphics3D::BLEND_INVSRCALPHA:
					dfactor = GL_ONE_MINUS_SRC_ALPHA;
					break;
				case Graphics3D::BLEND_ONE:
					dfactor = GL_ONE;
					break;
				case Graphics3D::BLEND_ZERO:
					dfactor = GL_ZERO;
					break;
				case Graphics3D::BLEND_SRCCOLOR:
					dfactor = GL_SRC_COLOR;
					break;
				case Graphics3D::BLEND_INVSRCCOLOR:
					dfactor = GL_ONE_MINUS_SRC_COLOR;
					break;
				case Graphics3D::BLEND_DESTCOLOR:
					dfactor = GL_DST_COLOR;
					break;
				case Graphics3D::BLEND_INVDESTCOLOR:
					dfactor = GL_ONE_MINUS_DST_COLOR;
					break;
				case Graphics3D::BLEND_SRCALPHASAT:
					dfactor = GL_SRC_ALPHA_SATURATE;
					break;
				default:
					dfactor = GL_ONE;
					break;
			}
			glBlendFunc(sfactor,dfactor);
			
			if (sfactor==GL_ONE && dfactor==GL_ZERO)
			{
				glDisable(GL_BLEND);
			}
			else 
			{
				glEnable(GL_BLEND);
			}

		}
		
		void SetRenderState(uint32 theRenderState, uint32 theValue)
		{
			mRenderStates[theRenderState].SetValue((uint32_t)theValue);
			//SetGLBlendState(mRenderStates[SEXY3DRS_SRCBLEND].GetDword(),mRenderStates[SEXY3DRS_DESTBLEND].GetDword());
		}
		
		GLuint	GetTexture(int theStage)
		{
			return mMiscStates[ST_MISC_TEXTURE][theStage].GetDword();
		}
		
		virtual void	SetTexture(int theStage, GLuint theTexture, GLuint theSrc)
		{
			mMiscStates[ST_MISC_TEXTURE][theStage].SetValue((uint32_t)theTexture);
			mMiscStates[ST_MISC_TEXTURE_SRC][theStage].SetValue((uint32_t)theSrc);

		}

		virtual void GetViewport(uint32_t& outX, uint32_t& outY, uint32_t& outWidth, uint32_t& outHeight)
		{
			outX = mViewportStates[ST_VIEWPORT_X].GetDword();
			outY = mViewportStates[ST_VIEWPORT_Y].GetDword();
			outWidth = mViewportStates[ST_VIEWPORT_WIDTH].GetDword();
			outHeight = mViewportStates[ST_VIEWPORT_HEIGHT].GetDword();
		}

		virtual void SetViewport(uint32_t inX, uint32_t inY, uint32_t inWidth, uint32_t inHeight, float minZ, float maxZ)
		{
			mViewportStates[ST_VIEWPORT_X].SetDirty();
			mViewportStates[ST_VIEWPORT_Y].SetDirty();
			mViewportStates[ST_VIEWPORT_WIDTH].SetDirty();
			mViewportStates[ST_VIEWPORT_HEIGHT].SetDirty();
			mViewportStates[ST_VIEWPORT_MINZ].SetDirty();
			mViewportStates[ST_VIEWPORT_MAXZ].SetDirty();
			
			
			
			mViewportStates[ST_VIEWPORT_X].SetValue(inX);
			mViewportStates[ST_VIEWPORT_Y].SetValue(inY);
			mViewportStates[ST_VIEWPORT_WIDTH].SetValue(inWidth);
			mViewportStates[ST_VIEWPORT_HEIGHT].SetValue(inHeight);
			mViewportStates[ST_VIEWPORT_MINZ].SetValue(minZ);
			mViewportStates[ST_VIEWPORT_MAXZ].SetValue(maxZ);
		}

		virtual void SetScissorRect(uint32_t inX, uint32_t inY, uint32_t inWidth, uint32_t inHeight, uint32_t inEnabled)
		{
			mScissorStates[ST_SCISSOR_X].SetValue(inX);
			mScissorStates[ST_SCISSOR_Y].SetValue(inY);
			mScissorStates[ST_SCISSOR_WIDTH].SetValue(inWidth);
			mScissorStates[ST_SCISSOR_HEIGHT].SetValue(inHeight);
			mScissorStates[ST_SCISSOR_ENABLE].SetValue(inEnabled);
		}
		
		void SetScissorRectToViewportRect()
		{
			mScissorStates[ST_SCISSOR_X].SetValue(mViewportStates[ST_VIEWPORT_X].GetDword());
			mScissorStates[ST_SCISSOR_Y].SetValue(mViewportStates[ST_VIEWPORT_Y].GetDword());
			mScissorStates[ST_SCISSOR_WIDTH].SetValue(mViewportStates[ST_VIEWPORT_WIDTH].GetDword());
			mScissorStates[ST_SCISSOR_HEIGHT].SetValue(mViewportStates[ST_VIEWPORT_HEIGHT].GetDword());
			mScissorStates[ST_SCISSOR_ENABLE].SetValue((uint32_t)1);
		}
		
		SexyVector2 GetTextureScale(int theStage)
		{
			MATH_TYPE junkz,junkw;
			SexyVector2 vec;
			mMiscStates[ST_MISC_TEXSCALE][theStage].GetVector(vec.x,vec.y,junkz,junkw);
			return vec;
		}
		
		void SetTextureScaling(bool inOn)
		{
			mMiscStates[ST_MISC_USE_TEXSCALE][0].SetValue((uint32_t)(inOn?1:0));
		}

		void SetTextureScale(int theStage, SexyVector2 inUV)
		{
			mMiscStates[ST_MISC_TEXSCALE][theStage].SetValue(StateValue(inUV.x,inUV.y,MATH_TYPE(1),MATH_TYPE(1)));
		}

		void Set3DMode(bool in3DMode)
		{
			mMiscStates[ST_MISC_3DMODE][0].SetValue((uint32_t)(in3DMode?1:0));
		}

		void GetTransform(uint32_t inTS, SexyMatrix4* inMatrix) const
		{
			mTransformStates[inTS][0].GetVector(inMatrix->m00, inMatrix->m01, inMatrix->m02, inMatrix->m03);
			mTransformStates[inTS][1].GetVector(inMatrix->m10, inMatrix->m11, inMatrix->m12, inMatrix->m13);
			mTransformStates[inTS][2].GetVector(inMatrix->m20, inMatrix->m21, inMatrix->m22, inMatrix->m23);
			mTransformStates[inTS][3].GetVector(inMatrix->m30, inMatrix->m31, inMatrix->m32, inMatrix->m33);
		}

		void SetTransform(uint32_t inTS, const SexyMatrix4* inMatrix)
		{
			
			//hacky change to the projection matrix to conform to DX
			if (inTS == OGL_TRANSFORM_PROJECTION)
			{
				mTransformStates[inTS][0].SetValue(StateValue(inMatrix->m00, inMatrix->m01, inMatrix->m02, inMatrix->m03));
				mTransformStates[inTS][1].SetValue(StateValue(inMatrix->m10, inMatrix->m11, inMatrix->m12, inMatrix->m13));
				mTransformStates[inTS][2].SetValue(StateValue(inMatrix->m20, inMatrix->m21, inMatrix->m22, inMatrix->m23));
				mTransformStates[inTS][3].SetValue(StateValue(inMatrix->m30, inMatrix->m31, inMatrix->m32, inMatrix->m33));				
			}
			else
			{
				mTransformStates[inTS][0].SetValue(StateValue(inMatrix->m00, inMatrix->m01, inMatrix->m02, inMatrix->m03));
				mTransformStates[inTS][1].SetValue(StateValue(inMatrix->m10, inMatrix->m11, inMatrix->m12, inMatrix->m13));
				mTransformStates[inTS][2].SetValue(StateValue(inMatrix->m20, inMatrix->m21, inMatrix->m22, inMatrix->m23));
				mTransformStates[inTS][3].SetValue(StateValue(inMatrix->m30, inMatrix->m31, inMatrix->m32, inMatrix->m33));
			}

			
			
		}
		
		virtual void SetOrthoProjection(const SexyMatrix4* inMatrix)
		{
			SetTransform(OGL_TRANSFORM_ORTHOPROJ, inMatrix);
		}
		
		uint32 GetVertexFormat()
		{
			return mMiscStates[ST_MISC_VERTEXFORMAT][0].GetDword();
		}
		
		uint32 GetVertexSize()
		{
			return mMiscStates[ST_MISC_VERTEXSIZE][0].GetDword();
		}
		
		/*static uint32 MakeVertexSize(uint32 theVertexFormat)
		{
			int aVertexSize = 0;
			if (theVertexFormat & SexyVF_XYZ)
				aVertexSize += 12;
			if (theVertexFormat & SexyVF_XYZRHW)
				aVertexSize += 16;
			if (theVertexFormat & SexyVF_Normal)
				aVertexSize += 12;
			if (theVertexFormat & SexyVF_Diffuse)
				aVertexSize += 4;
			if (theVertexFormat & SexyVF_Specular)
				aVertexSize += 4;

			if (theVertexFormat & SexyVF_Tex2)
				aVertexSize += 16;
			else if (theVertexFormat & SexyVF_Tex1)
				aVertexSize += 8; //always just 2 floats?
		
			return aVertexSize;
		}*/
		
		void SetVertexFormat(uint32 inVertexFormat, uint32 theVertexSize)
		{
			if (mMiscStates[ST_MISC_VERTEXFORMAT][0].GetDword() != inVertexFormat)
			{
				mMiscStates[ST_MISC_VERTEXFORMAT][0].SetValue((uint32_t)inVertexFormat);
			}
			if (mMiscStates[ST_MISC_VERTEXSIZE][0].GetDword() != theVertexSize)
			{
				mMiscStates[ST_MISC_VERTEXSIZE][0].SetValue((uint32_t)theVertexSize);
			}
		}
		
		void SetShaderPrograms(GLuint the3DProgram, GLuint theOrthoProgram)
		{
			mMiscStates[ST_MISC_SHADERPROGRAM_3D][0].SetValue((uint32_t)the3DProgram);
			mMiscStates[ST_MISC_SHADERPROGRAM_ORTHO][0].SetValue((uint32_t)theOrthoProgram);
		}
		
		void SetBackfaceCulling(bool inCullClockwise, bool inCullCounterClockwise)
		{
			mMiscStates[ST_MISC_CULLMODE][0].SetValue((uint32_t)((inCullClockwise?0x02:0x00) | (inCullCounterClockwise?0x01:0x00)));
		}
		
		bool GetTextureUWrap(int inTextureIndex)
		{
			return mMiscStates[ST_MISC_TEXTURE_WRAP_S][inTextureIndex].GetDword() == GL_REPEAT;
		}
		
		bool GetTextureVWrap(int inTextureIndex)
		{
			return mMiscStates[ST_MISC_TEXTURE_WRAP_T][inTextureIndex].GetDword() == GL_REPEAT;
		}
													  
		void SetTextureUWrap(int inTextureIndex, bool inWrapU)
		{
			if (inWrapU)
				mMiscStates[ST_MISC_TEXTURE_WRAP_S][inTextureIndex].SetValue((uint32_t)GL_REPEAT);
			else
				mMiscStates[ST_MISC_TEXTURE_WRAP_S][inTextureIndex].SetValue((uint32_t)GL_CLAMP_TO_EDGE);
		}
		
		void SetTextureVWrap(int inTextureIndex, bool inWrapV)
		{
			if (inWrapV)
				mMiscStates[ST_MISC_TEXTURE_WRAP_T][inTextureIndex].SetValue((uint32_t)GL_REPEAT);
			else
				mMiscStates[ST_MISC_TEXTURE_WRAP_T][inTextureIndex].SetValue((uint32_t)GL_CLAMP_TO_EDGE);
		}
		
		
		bool GetTextureMinFilter(int inTextureIndex)
		{
			return mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][inTextureIndex].GetDword() == GL_LINEAR;
		}
		
		void SetTextureMinFilter(int inTextureIndex, bool inLinear)
		{
			if (inLinear)
				mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][inTextureIndex].SetValue((uint32_t)GL_LINEAR);
			else
				mMiscStates[ST_MISC_TEXTURE_MIN_FILTER][inTextureIndex].SetValue((uint32_t)GL_NEAREST);
		}
		
		bool GetTextureMagFilter(int inTextureIndex)
		{
			return mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][inTextureIndex].GetDword() == GL_LINEAR;
		}
		
		void SetTextureMagFilter(int inTextureIndex, bool inLinear)
		{
			if (inLinear)
				mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][inTextureIndex].SetValue((uint32_t)GL_LINEAR);
			else
				mMiscStates[ST_MISC_TEXTURE_MAG_FILTER][inTextureIndex].SetValue((uint32_t)GL_NEAREST);
		}

		void SetAtlasState(uint32_t inSampler, bool inEnabled, const SexyVector2* inBase = NULL, const SexyVector2* inU = NULL, const SexyVector2* inV = NULL)
		{
			if (!inEnabled)
			{
				mMiscStates[ST_MISC_ATLASENABLEDANDBASE][inSampler].SetValue((MATH_TYPE)0, (MATH_TYPE)0, (MATH_TYPE)0, (MATH_TYPE)0);
			}
			else
			{
				mMiscStates[ST_MISC_ATLASENABLEDANDBASE][inSampler].SetValue((MATH_TYPE)1, (MATH_TYPE)0, inBase->x, inBase->y);
				mMiscStates[ST_MISC_ATLASUV][inSampler].SetValue(StateValue(inU->x, inU->y, inV->x, inV->y));
			}
		}

		bool GetAtlasState(uint32_t inSampler, SexyVector2& outBase, SexyVector2& outU, SexyVector2& outV)
		{
			MATH_TYPE enabled, unused;
			mMiscStates[ST_MISC_ATLASENABLEDANDBASE][inSampler].GetVector(enabled, unused, outBase.x, outBase.y);
			if (enabled < 0.5f)
				return false;
			mMiscStates[ST_MISC_ATLASUV][inSampler].GetVector(outU.x, outU.y, outV.x, outV.y);
			return true;
		}
		
        bool IsDefaultShader()
        {
            return true;
        }
        
		virtual void SetDefaultShader()
		{
#ifdef SUPPORT_GLSL_SHADERS
            glUseProgram(0);
#endif
		}
        
        virtual void SetDefaultMultiShader()
        {
#ifdef SUPPORT_GLSL_SHADERS
            glUseProgram(0);
#endif
        }
														  
#ifndef RELEASEFINAL
		void SetMetrics(GraphicsMetrics* theMetrics)
		{
			mMetrics = theMetrics;
		}
#endif
		
		SexyVector2 mTextureUVScale;  // texture UV scale
		
#ifndef RELEASEFINAL
		GraphicsMetrics* mMetrics;
#endif
	};
}

#endif
