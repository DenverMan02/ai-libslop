#ifndef WIISTATEMANAGER_H_INCLUDED
#define WIISTATEMANAGER_H_INCLUDED

#include "RenderStateManager.h"
#include "Graphics.h"

namespace Sexy 
{
	
	
	class WiiStateManager : public RenderStateManager
	{
	protected:
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
			
			SG_COUNT
		};
		
		enum
		{
			ST_COUNT_RS = 256, // (dword)
			ST_COUNT_TSS = 48, // (dword)
			ST_COUNT_SS = 16, // (dword)
			ST_COUNT_TRANSFORM = 512 // (vector) accounts for the up to 256 D3DTS_WORLDMATRIX(index) transforms
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
		enum EMiscState
		{
			// single states
			ST_MISC_FVF, // (dword) [0] (uses SetFVF)
			ST_MISC_FVFSIZE, // (dword) [0] (internal; automatically updated when FVF is set)
			ST_MISC_INDICES, // (ptr) [0] (uses SetIndices)
			ST_MISC_PIXELSHADER, // (ptr) [0] (uses SetPixelShader)
			ST_MISC_VERTEXSHADER, // (ptr) [0] (uses SetVertexShader)
			ST_MISC_TEXTUREPALETTE, // (dword) [0] (uses SetCurrentTexturePalette)
			ST_MISC_SCISSORRECT, // (vector left top right bottom) [0] (uses SetScissorRect)
			ST_MISC_NPATCHMODE, // (float) [0] (uses SetNPatchMode)
			//ST_MISC_VERTEXDECL, // (ptr) [0] (uses SetVertexDeclaration) // commented out; not using non-fvf vertex declarations, for compat reasons
			ST_MISC_SRCBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_DESTBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_BLTDEPTH, // (float) [0] (internal; depth buffer value used for 2D blt functions)
			
			// array states
			ST_MISC_TEXTURE, // (ptr) [sampler number] (uses SetTexture)
			ST_MISC_PIXELSHADERCONST, // (vector) [register] (uses SetPixelShaderConstantF)
			ST_MISC_VERTEXSHADERCONST, // (vector) [register] (uses SetVertexShaderConstantF)
			ST_MISC_CLIPPLANE, // (vector) [clip plane index] (uses SetClipPlane)
			ST_MISC_TEXTUREREMAP, // (int) [sampler number] (internal; index of logical texture state that is actually used for this physical sampler)
			
			ST_COUNT_MISC,
			ST_COUNT_MISC_SINGLE = ST_MISC_TEXTURE // first of the array states
		};
		
		typedef std::vector<State> StateVector;
//		std::vector<State> mRenderStates;
//		std::vector<StateVector> mTextureStageStates;
//		std::vector<StateVector> mSamplerStates;
//		std::vector<StateVector> mLightStates;
//		std::vector<State> mMaterialStates;
//		std::vector<StateVector> mStreamStates;
//		std::vector<StateVector> mTransformStates;
		std::vector<State> mViewportStates;
//		std::vector<StateVector> mMiscStates;
		
		void InitRenderState(ulong inIndex, const std::string& inStateName, ulong inHardwareDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitRenderStateFloat(ulong inIndex, const std::string& inStateName, float inDefaultValue);
		void InitTextureStageState(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, ulong inDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitTextureStageStateFloat(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, float inDefaultValue);
		void InitSamplerState(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, ulong inDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		
		void InitStates();
		void ResetStates();
		
		State::FCommitFunc GetCommitFunc(State* inState);
	public:
		WiiStateManager();
		
		virtual void Init() override
		{
			InitStates();
		}

		virtual void Reset() override
		{
			ResetStates();
		}
		
		void SetBlendOverride(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend);
		void SetBltDepth(float inDepth);
		void GetBlendOverride(Graphics3D::EBlendMode& outSrcBlend, Graphics3D::EBlendMode& outDestBlend);

		float GetBltDepth();

		uint32 GetRenderState(uint32 theRenderState);
		void SetRenderState(uint32 theRenderState, uint32 theValue);

		GXTexObj*				GetTexture(int theStage);
		void					SetTexture(int theStage, GXTexObj* theTexture);

	private:

		GXTexObj* mTexture[GX_MAX_TEXMAP];

		uint32 mSrcBlendState;
		uint32 mDstBlendState;
		uint32 mAlphaBlendEnable;

	};
}

#endif
