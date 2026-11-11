#ifndef XBOX360STATEMANAGER_H_INCLUDED
#define XBOX360STATEMANAGER_H_INCLUDED

#include "RenderStateManager.h"
#include "Graphics.h"

namespace Sexy 
{
	// FVF is only available for legacy support on Xbox360 and has performance penalties
	// Uncomment this define for legacy FVF support.
	// otherwise FVFs will need to be converted into Vertex Declarations
	#define SUPPORT_D3D_FVF

	class Xbox360StateManager : public RenderStateManager
	{
	protected:
		enum EStateGroup
		{
			SG_RS, // [D3DRS] (uses SetRenderState)
//			SG_TSS, // [D3DTSS][stage index] (uses SetTextureStageState)
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
			ST_COUNT_RS = D3DRS_MAX, // (dword)
			ST_COUNT_TSS = 48, // (dword)
			ST_COUNT_SS = D3DSAMP_MAX, // (dword)
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
//			ST_STREAM_FREQ, // (dword)
			
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
#ifdef SUPPORT_D3D_FVF
			ST_MISC_FVF, // (dword) [0] (uses SetFVF)
			ST_MISC_FVFSIZE, // (dword) [0] (internal; automatically updated when FVF is set)
#endif
			ST_MISC_INDICES, // (ptr) [0] (uses SetIndices)
			ST_MISC_PIXELSHADER, // (ptr) [0] (uses SetPixelShader)
			ST_MISC_VERTEXSHADER, // (ptr) [0] (uses SetVertexShader)
//			ST_MISC_TEXTUREPALETTE, // (dword) [0] (uses SetCurrentTexturePalette)
			ST_MISC_SCISSORRECT, // (vector left top right bottom) [0] (uses SetScissorRect)
//			ST_MISC_NPATCHMODE, // (float) [0] (uses SetNPatchMode)
			ST_MISC_VERTEXDECL, // (ptr) [0] (uses SetVertexDeclaration)
			ST_MISC_SRCBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_DESTBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_BLTDEPTH, // (float) [0] (internal; depth buffer value used for 2D blt functions)
			ST_MISC_3DMODE, // (dword bool) [0] (internal; switches between managed ortho project and user set projection/model mats)
			
			// array states
			ST_MISC_TEXTURE, // (ptr) [sampler number] (uses SetTexture)
			ST_MISC_PIXELSHADERCONST, // (vector) [register] (uses SetPixelShaderConstantF)
			ST_MISC_VERTEXSHADERCONST, // (vector) [register] (uses SetVertexShaderConstantF)
//			ST_MISC_CLIPPLANE, // (vector) [clip plane index] (uses SetClipPlane)
//			ST_MISC_TEXTUREREMAP, // (int) [sampler number] (internal; index of logical texture state that is actually used for this physical sampler)

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
		
		void InitRenderState(ulong inIndex, const std::string& inStateName, ulong inHardwareDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitRenderStateFloat(ulong inIndex, const std::string& inStateName, float inDefaultValue);

		void InitTextureStageState(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, ulong inDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitTextureStageStateFloat(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, float inDefaultValue);

		void InitSamplerState(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, ulong inDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		void InitSamplerStateFloat(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, float inDefaultValue);


		void InitStates();
		void ResetStates();

		State::FCommitFunc GetCommitFunc(State* inState);
		static bool DoCommitRenderState(RenderStateManager::State *inState);
		static bool DoCommitSamplerState(RenderStateManager::State *inState);
		static bool DoCommitLightState(RenderStateManager::State *inState);
		static bool DoCommitMaterialState(RenderStateManager::State *inState);
		static bool DoCommitStreamState(RenderStateManager::State *inState);
		static bool DoCommitTransformState(RenderStateManager::State *inState);
		static bool DoCommitViewportState(RenderStateManager::State *inState);
		static bool DoCommitMiscState(RenderStateManager::State *inState);

	public:
		Xbox360StateManager(IDirect3DDevice9* theDevice);
		
		virtual void Init() override
		{
			InitStates();
		}
		virtual void Reset() override
		{
			ResetStates();
		}

		void SetRenderState(D3DRENDERSTATETYPE inRS, ulong inValue);
		void SetSamplerState(ulong inSampler, ulong inSS, ulong inValue);
		void SetLightEnabled(ulong inLightIndex, bool inEnabled);
		void SetPointLight(int inLightIndex, const SexyVector3& inPos, const Graphics3D::LightColors& inColors, float inRange, const SexyVector3& inAttenuation);
		void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const Graphics3D::LightColors& inColors);
		void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1);
		void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1);
		void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f);
		void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1);
		void SetTransform(ulong inTS, const SexyMatrix4* inMatrix);
		void SetViewport(ulong inX, ulong inY, ulong inWidth, ulong inHeight, float inMinZ, float inMaxZ);
		void SetBlendOverride(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend);
		void SetBltDepth(float inDepth);
		void SetTexture(int theStage, IDirect3DBaseTexture9* theTexture);

		void SetIndices(void* inIndexBuffer);
		void SetStreamSource(ulong inStreamIndex, void* inVertexBuffer, ulong inOffset, ulong inStride);


		void SetPixelShader(IDirect3DPixelShader9* theShader);
		void SetVertexShader(IDirect3DVertexShader9* theShader);
		void SetVertexDecl(IDirect3DVertexDeclaration9* theDecl);
		void SetPixelShaderConstantF(ulong inStartRegister, const float* inConstantData, ulong inVector4fCount);
		void SetVertexShaderConstantF(ulong inStartRegister, const float* inConstantData, ulong inVector4fCount);

		void Set3DMode(bool in3dMode);
		bool Is3DMode();

		ulong GetRenderState(ulong inRS) const;
		ulong GetSamplerState(ulong inSampler, ulong inSS) const;
		void GetLightInfo(int inLightIndex, Graphics3D::LightColors& outColors, SexyVector3& outPos, SexyVector3& outDir, SexyVector3& outAttenuation, float& outRange);
		void GetMaterialInfo(Color& outAmbient, Color& outDiffuse, Color& outSpecular, Color& outEmissive, float& outSpecularPower);
		void GetTransform(ulong inTS, SexyMatrix4* inMatrix) const;
		void GetBlendOverride(Graphics3D::EBlendMode& outSrcBlend, Graphics3D::EBlendMode& outDestBlend);
		float GetBltDepth();

		IDirect3DBaseTexture9*			GetTexture(int theStage) const;
		IDirect3DPixelShader9*			GetPixelShader();
		IDirect3DVertexShader9*			GetVertexShader();
		IDirect3DVertexDeclaration9*	GetVertexDecl();

		void SetAtlasState(ulong inSampler, bool inEnabled, const SexyVector2* inBase = NULL, const SexyVector2* inU = NULL, const SexyVector2* inV = NULL);
		bool GetAtlasState(ulong inSampler, SexyVector2& outBase, SexyVector2& outU, SexyVector2& outV);

		static StateValue MakeLightColorStateValue(const Color& inColor, float inAutoScale);
		static Color MakeStateValueLightColor(const State& inState);
#ifdef SUPPORT_D3D_FVF
		static ulong MakeFVFSize( ulong inFVF );
		ulong GetFVF() const;
		ulong GetFVFSize() const;

		void SetFVF( ulong inFVF );
#endif

		inline IDirect3DDevice9 *GetDevice(){ return mDevice; }

	private:
		friend class Xbox360RenderDevice;
		IDirect3DDevice9* mDevice;

		//defaults to fall back to in certain conditions
		IDirect3DVertexDeclaration9*	mDefaultVertexDecl;

		IDirect3DVertexShader9* mDefaultVertexShader;
//		IDirect3DVertexShader9* mDefaultVertexShader3D;

		IDirect3DPixelShader9* mDefaultPixelShaderNoTex;
		IDirect3DPixelShader9* mDefaultPixelShader;
	};
}

#endif
