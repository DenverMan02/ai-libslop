#ifndef VitaSTATEMANAGER_H_INCLUDED
#define VitaSTATEMANAGER_H_INCLUDED

#include "RenderStateManager.h"
#include "Graphics.h"

#include <gxm.h>



extern const SceGxmProgram _binary_clear_v_gxp_start;
extern const SceGxmProgram _binary_clear_f_gxp_start;;
extern const SceGxmProgram _binary_basic_v_gxp_start;
extern const SceGxmProgram _binary_basic_v_packed_gxp_start;
extern const SceGxmProgram _binary_basic_f_gxp_start;
extern const SceGxmProgram _binary_basic_f_notex_gxp_start;


namespace Sexy 
{
	class VitaRenderDevice;
	class VitaGraphicsDriver;
	class VitaRenderEffect;

	struct _VitaVertexShaderKey
	{
		SceGxmShaderPatcherId	mId;
		uint32					mFVF;

		bool operator < (const _VitaVertexShaderKey& other) const
		{
			if (mId < other.mId) return true;
			if (mId == other.mId)
			{
				return (mFVF < other.mFVF);
			}
			return false;
		}
	};
	typedef std::map<_VitaVertexShaderKey,SceGxmVertexProgram*> VitaVertexShaderMap;

	struct _VitaFragmentShaderKey
	{
		SceGxmShaderPatcherId	mId;
		SceGxmShaderPatcherId	mVertexId;
		uint32					mBlendInfo; //cast version of SceBlendInfo (0 == no blending)

		bool operator < (const _VitaFragmentShaderKey& other) const
		{
			//TODO rewrite with less branching...
			if (mId < other.mId) return true;
			if (mId == other.mId)
			{
				if (mVertexId < other.mVertexId) return true;
				if (mVertexId == other.mVertexId)
				{
					return (mBlendInfo < other.mBlendInfo);
				}
			}
			return false;
		}
	};
	typedef std::map<_VitaFragmentShaderKey,SceGxmFragmentProgram*> VitaFragmentShaderMap;
	
	enum VITA_TRANSFORM
	{
		VITA_TRANSFORM_WORLD = 0,
		VITA_TRANSFORM_VIEW  = 1,
		VITA_TRANSFORM_PROJECTION = 2,
		VITA_TRANSFORM_TEXTURE0 = 3,
		VITA_TRANSFORM_TEXTURE1 = 4,
		VITA_TRANSFORM_TEXTURE2 = 5,
		VITA_TRANSFORM_TEXTURE3 = 6,
		VITA_TRANSFORM_TEXTURE4 = 7,
		VITA_TRANSFORM_TEXTURE5 = 8,
		VITA_TRANSFORM_TEXTURE6 = 9,
		VITA_TRANSFORM_TEXTURE7 = 10,
		
		VITA_TRANSFORM_ORTHOPROJ,
		
		VITA_TRANSFORM_COUNT,
	};
	
	class VitaStateManager : public RenderStateManager
	{
	protected:
		enum EStateGroup
		{
//			SG_RS, // [D3DRS] (uses SetRenderState)
//			SG_TSS, // [D3DTSS][stage index] (uses SetTextureStageState)
//			SG_SS, // [D3DSAMP][sampler index] (uses SetSamplerState)
//			SG_LIGHT, // [ELightState][light index] (uses LightEnable and SetLight)
//			SG_MATERIAL, // [EMaterialState] (uses SetMaterial)
//			SG_STREAM, // [EStreamState][stream number] (uses SetStreamSource and SetStreamSourceFreq)
			SG_TRANSFORM, // [D3DTS][row number 0-3] (uses SetTransform)
			SG_BLEND, // [EBlendState] (uses cellGcmSetBlend*)
			SG_VIEWPORT, // [EViewportState] (uses cellGcmSetViewport)
			SG_MISC, // [EMiscState][variable, see individual state]
			
			SG_COUNT
		};
		
		enum
		{
			ST_COUNT_RS = 256, // (dword)
			ST_COUNT_TSS = 48, // (dword)
			ST_COUNT_SS = 16, // (dword)
			ST_COUNT_TRANSFORM = VITA_TRANSFORM_COUNT // (vector) 
		};
		//enum
		//{
		//	ST_COUNT_RS = 256, // (dword)
		//	ST_COUNT_TSS = 48, // (dword)
		//	ST_COUNT_SS = 16, // (dword)
		//	ST_COUNT_TRANSFORM = 512 // (vector) accounts for the up to 256 D3DTS_WORLDMATRIX(index) transforms
		//};
		//
		//enum ELightState
		//{
		//	ST_LIGHT_ENABLED, // (dword bool)
		//	ST_LIGHT_TYPE, // (dword D3DLIGHT_)
		//	ST_LIGHT_DIFFUSE, // (vector RGBA)
		//	ST_LIGHT_SPECULAR, // (vector RGBA)
		//	ST_LIGHT_AMBIENT, // (vector RGBA)
		//	ST_LIGHT_POSITION, // (vector XYZ)
		//	ST_LIGHT_DIRECTION, // (vector XYZ)
		//	ST_LIGHT_RANGE, // (float)
		//	ST_LIGHT_FALLOFF, // (float)
		//	ST_LIGHT_ATTENUATION, // (vector Atten0 Atten1 Atten2)
		//	ST_LIGHT_ANGLES, // (vector Theta Phi)
		//	
		//	ST_COUNT_LIGHT
		//};
		//enum EMaterialState
		//{
		//	ST_MAT_DIFFUSE, // (vector RGBA)
		//	ST_MAT_AMBIENT, // (vector RGBA)
		//	ST_MAT_SPECULAR, // (vector RGBA)
		//	ST_MAT_EMISSIVE, // (vector RGBA)
		//	ST_MAT_POWER, // (float)
		//	
		//	ST_COUNT_MAT
		//};
		//enum EStreamState
		//{
		//	ST_STREAM_DATA, // (ptr)
		//	ST_STREAM_OFFSET, // (dword)
		//	ST_STREAM_STRIDE, // (dword)
		//	ST_STREAM_FREQ, // (dword)
		//	
		//	ST_COUNT_STREAM
		//};

		enum EBlendState
		{
			ST_BLEND_ENABLE, //(dword)
			ST_BLEND_COLOR, // (dword)
			ST_BLEND_EQUATION_COLOR, // (dword)
			ST_BLEND_EQUATION_ALPHA, // (dword)
			ST_BLEND_FUNC_COLOR_SRC, // (dword)
			ST_BLEND_FUNC_COLOR_DST, // (dword)
			ST_BLEND_FUNC_ALPHA_SRC, // (dword)
			ST_BLEND_FUNC_ALPHA_DST, // (dword)
			ST_BLEND_OPTIMIZATION, // (dword)

			ST_COUNT_BLEND,
		};
		enum EViewportState
		{
			ST_VIEWPORT_X, // (dword)
			ST_VIEWPORT_Y, // (dword)
			ST_VIEWPORT_WIDTH, // (dword)
			ST_VIEWPORT_HEIGHT, // (dword)
			ST_VIEWPORT_MINZ, // (float)
			ST_VIEWPORT_MAXZ, // (float)
			ST_VIEWPORT_SCALE, // (vector)
			ST_VIEWPORT_OFFSET, // (vector)
			
			ST_COUNT_VIEWPORT
		};

		enum EMiscState
		{
			// single states
			ST_MISC_VERTEXFORMAT, // (dword) [0] ()
			ST_MISC_VERTEXSIZE, // (dword) [0] (internal; automatically updated when VertexFormat is set)
//			ST_MISC_INDICES, // (ptr) [0] (uses SetIndices)
			ST_MISC_VERTEXSHADER, // (ptr) [0] (uses SetVertexShader)
			ST_MISC_PIXELSHADER, // (ptr) [0] (uses SetPixelShader)
			ST_MISC_RENDEREFFECT, // (ptr) to the current render effect, used for updating uniform buffers
//			ST_MISC_TEXTUREPALETTE, // (dword) [0] (uses SetCurrentTexturePalette)
			ST_MISC_SCISSORRECT, // (vector left top right bottom) [0] (uses SetScissorRect)
//			ST_MISC_NPATCHMODE, // (float) [0] (uses SetNPatchMode)
//			ST_MISC_VERTEXDECL, // (ptr) [0] (uses SetVertexDeclaration) // commented out; not using non-fvf vertex declarations, for compat reasons
			ST_MISC_SRCBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_DESTBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_BLTDEPTH, // (float) [0] (internal; depth buffer value used for 2D blt functions)
			
			// array states
			ST_MISC_TEXTURE, // (ptr) [sampler number] (uses cellGcmSetTexture)
			ST_MISC_VERTEXSHADERCONST, // (vector) (parameter index) (uses cellGcmSetVertexProgramConstants)
//			ST_MISC_PIXELSHADERCONST, // (vector) (parameter index) (uses SetPixelShaderConstantF)
//			ST_MISC_CLIPPLANE, // (vector) [clip plane index] (uses SetClipPlane)
//			ST_MISC_TEXTUREREMAP, // (int) [sampler number] (internal; index of logical texture state that is actually used for this physical sampler)

			ST_MISC_ATLASENABLEDANDBASE, // (vector) [sampler number] (internal; x = 1.0 for atlas enabled or 0.0 for disabled, y = unused, z = base.x, w = base.y)
			ST_MISC_ATLASUV, // (vector) [sampler number] (internal; atlasing vectors, u.x, u.y, v.x, v.y)
			
			ST_COUNT_MISC,
			ST_COUNT_MISC_SINGLE_END = ST_MISC_TEXTURE // first of the array states
		};
		
		typedef std::vector<State> StateVector;

//		std::vector<State> mRenderStates;
//		std::vector<StateVector> mTextureStageStates;
//		std::vector<StateVector> mSamplerStates;
//		std::vector<StateVector> mLightStates;
//		std::vector<State> mMaterialStates;
//		std::vector<StateVector> mStreamStates;
		std::vector<StateVector> mTransformStates;
		std::vector<State> mBlendStates;
		std::vector<State> mViewportStates;
		std::vector<StateVector> mMiscStates;

//		void InitRenderState(ulong inIndex, const std::string& inStateName, ulong inHardwareDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
//		void InitRenderStateFloat(ulong inIndex, const std::string& inStateName, float inDefaultValue);
//		void InitTextureStageState(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, ulong inDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
//		void InitTextureStageStateFloat(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, float inDefaultValue);
//		void InitSamplerState(ulong inFirstStage, ulong inLastStage, ulong inIndex, const std::string& inStateName, ulong inDefaultValue, bool inHasContextDefault=false, ulong inContextDefaultValue=0, const char* inValueEnumName=0);
		
		void InitStates();
		void ResetStates();
		
		void SetPixelShaderDirect( SceGxmShaderPatcherId inShader );
		void SetVertexShaderDirect( SceGxmShaderPatcherId inShader );

		State::FCommitFunc GetCommitFunc(State* inState);
/*		static bool DoCommitRenderState(RenderStateManager::State *inState);
		static bool DoCommitSamplerState(RenderStateManager::State *inState);
		static bool DoCommitLightState(RenderStateManager::State *inState);
		static bool DoCommitMaterialState(RenderStateManager::State *inState);
		static bool DoCommitStreamState(RenderStateManager::State *inState);*/
		static bool DoCommitTransformState(RenderStateManager::State *inState);
		static bool DoCommitBlendState(RenderStateManager::State *inState);
		static bool DoCommitViewportState(RenderStateManager::State *inState);
		static bool DoCommitMiscState(RenderStateManager::State *inState);

	public:
		VitaStateManager(VitaRenderDevice* theRenderDevice);
		
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

		void SetBlendEnable( bool enable );

		//cellGcmSetBlendEquation
		void SetBlendEquation( uint16_t color, uint16_t alpha);

		//cellGcmSetBlendFunc
		void GetBlendFunc( uint16_t &srcColor, uint16_t &dstColor, uint16_t &srcAlpha, uint16_t &dstAlpha);
		void SetBlendFunc( uint16_t srcColor, uint16_t dstColor, uint16_t srcAlpha, uint16_t dstAlpha);

		//cellGcmSetBlendColor
		void SetBlendColor( uint32_t color, uint32_t color2);

		//cellGcmSetTexture
		void SetTexture(int theStage, SceGxmTexture* theTexture);
		SceGxmTexture*	GetTexture(int theStage);

		//register byte code for a shader... get an id back
		SceGxmShaderPatcherId RegisterPixelShader( const SceGxmProgram * );
		void SetPixelShader( SceGxmShaderPatcherId inShader );
		SceGxmShaderPatcherId GetPixelShader();

		void SetRenderEffect(VitaRenderEffect* theRenderEffect);


		//these will precache the patched shaders... use these for combinations that are
		// well known before starting drawing.
		const SceGxmProgram* GetProgramFromPatcher(SceGxmShaderPatcherId theId);
		SceGxmVertexProgram* PreparePatchedVertexShader(SceGxmShaderPatcherId theId, uint32 theFVF);
		SceGxmFragmentProgram* PreparePatchedPixelShader(SceGxmShaderPatcherId theId, SceGxmShaderPatcherId theVertexShaderId, SceGxmBlendInfo* theBlendInfo);

		SceGxmShaderPatcherId RegisterVertexShader( const SceGxmProgram * );
		void SetVertexShader( SceGxmShaderPatcherId inShader );
		SceGxmShaderPatcherId GetVertexShader();

		void SetVertexShaderConstantF(ulong inStartRegister, const float* inConstantData, ulong inVector4fCount);

		void SetViewport( uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max, float scale[4], float offset[4] );
		void GetViewport( uint16_t &x, uint16_t &y, uint16_t &width, uint16_t &height, float &min, float &max, float *scale, float *offset );

		void SetScissorRect( uint16_t x, uint16_t y, uint16_t width, uint16_t height );

		SceGxmShaderPatcherId GetDefaultVertexShader(){ return mDefaultVertexShader; };
		SceGxmShaderPatcherId GetDefaultPixelShader(){ return mDefaultPixelShader; };


		SceGxmShaderPatcherId GetClearVertexShader(){ return mClearVertexShader; };
		SceGxmShaderPatcherId GetClearPixelShader(){ return mClearPixelShader; };

		//SceGxmShaderPatcherId GetDefaultPixelShaderNoTex(){ return mDefaultPixelShaderNoTex; };

		

		void SetAtlasState(ulong inSampler, bool inEnabled, const SexyVector2* inBase = NULL, const SexyVector2* inU = NULL, const SexyVector2* inV = NULL);
		bool GetAtlasState(ulong inSampler, SexyVector2& outBase, SexyVector2& outU, SexyVector2& outV);

		static uint32 MakeVertexSize(uint32 inFVF)
		{
			ulong result = 0;
			if (inFVF & SexyVF_XYZ)
				result += sizeof(float)*3;
			else if (inFVF & SexyVF_XYZRHW)
			{
				if (inFVF & SexyVF_PackedFormat)
					result += sizeof(int16)*2;
				else
					result += sizeof(float)*4;
			}
			if (inFVF & SexyVF_Normal)
				result += sizeof(float)*3;
			if (inFVF & SexyVF_Diffuse)
				result += sizeof(uint32);
			if (inFVF & SexyVF_Specular)
				result += sizeof(uint32);

			int aNumTexCoords = ((inFVF >> 8) & 15);

			int aTexCoordElementSize = sizeof(float);
			if (inFVF & SexyVF_PackedFormat)
			{
				aTexCoordElementSize = sizeof(int16);
			}
			for (int iTexCoord=0; iTexCoord<aNumTexCoords; ++iTexCoord)
			{
				int aFlagTcs1 = SexyVF_TexCoordSize1(iTexCoord);
				int aFlagTcs3 = SexyVF_TexCoordSize3(iTexCoord);
				int aFlagTcs4 = SexyVF_TexCoordSize4(iTexCoord);

				if ((inFVF & aFlagTcs1) == aFlagTcs1)
					result += aTexCoordElementSize;
				else if ((inFVF & aFlagTcs3) == aFlagTcs3)
					result += aTexCoordElementSize*3;
				else if ((inFVF & aFlagTcs4) == aFlagTcs4)
					result += aTexCoordElementSize*4;
				else
					result += aTexCoordElementSize*2;
			}

			return result;
		}

		uint32 GetVertexFormat()
		{
			return mMiscStates[ST_MISC_VERTEXFORMAT][0].GetDword();
		}
		
		uint32 GetVertexSize()
		{
			return mMiscStates[ST_MISC_VERTEXSIZE][0].GetDword();
		}

		void SetVertexFormat(uint32 inVertexFormat)
		{
			if (mMiscStates[ST_MISC_VERTEXFORMAT][0].GetDword() != inVertexFormat)
			{
				mMiscStates[ST_MISC_VERTEXFORMAT][0].SetValue((ulong)inVertexFormat);
				mMiscStates[ST_MISC_VERTEXSIZE][0].SetValue((ulong)MakeVertexSize(inVertexFormat));
			}
		}

		void GetTransform(ulong inTS, SexyMatrix4* inMatrix) const;
		void SetTransform(ulong inTS, const SexyMatrix4* inMatrix);
		void SetOrthoProjection(const SexyMatrix4* inMatrix);


		void InvalidateVertexShader();
		void InvalidatePixelShader();
		void DeferredPrepareUniformBuffer();

		SceGxmTexture* mWhiteTex;
	private:
		friend class VitaRenderDevice;
		friend class VitaGraphicsDriver;
		VitaRenderDevice* mRenderDevice;
		VitaGraphicsDriver* mGraphicsDriver;

		SceGxmShaderPatcher* mShaderPatcher;

		//default vertex/pixel shaders for falling back
		SceGxmShaderPatcherId mDefaultVertexShader;
		SceGxmShaderPatcherId mDefaultPackedVertexShader;
		SceGxmShaderPatcherId mDefaultPixelShader;
		//SceGxmShaderPatcherId mDefaultPixelShaderNoTex;

		SceGxmShaderPatcherId mClearVertexShader;
		SceGxmShaderPatcherId mClearPixelShader;

		//this is the actual hardware state since we can't query it.
		SceGxmShaderPatcherId mCurrentPixelShader;

		const SceGxmProgramParameter* mOrthoProjParameter;
		void*					mUniformDataSpace;

		//A map for keeping track of shaders that have already been
		// patched (keyed from shader id, vert format, and blend mode)
		VitaVertexShaderMap mPatchedVertexShaderMap;
		VitaFragmentShaderMap mPatchedFragmentShaderMap;

		bool mDeferredUniformBufferCreateRequested;

		void* mWhiteTexData;
		
	};
}

#endif
