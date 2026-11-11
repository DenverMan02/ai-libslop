#ifndef PS3STATEMANAGER_H_INCLUDED
#define PS3STATEMANAGER_H_INCLUDED

#include "RenderStateManager.h"
#include "Graphics.h"

#include <cell/gcm.h>


//ppu-lv2-nm.exe *.ppu.o
/*
BuiltinShaders_vs.ppu.o:
00000000000002d0 D _binary_BuiltinShaders_vs_vpo_end
00000000000002d0 A _binary_BuiltinShaders_vs_vpo_size
0000000000000000 D _binary_BuiltinShaders_vs_vpo_start

BuiltinShaders_notex_ps.ppu.o:
00000000000000d0 D _binary_BuiltinShaders_notex_ps_fpo_end
00000000000000d0 A _binary_BuiltinShaders_notex_ps_fpo_size
0000000000000000 D _binary_BuiltinShaders_notex_ps_fpo_start

BuiltinShaders_ps.ppu.o:
0000000000000170 D _binary_BuiltinShaders_ps_fpo_end
0000000000000170 A _binary_BuiltinShaders_ps_fpo_size
0000000000000000 D _binary_BuiltinShaders_ps_fpo_start
*/
extern uint32_t _binary_BuiltinShaders_vs_vpo_start;
extern uint32_t _binary_BuiltinShaders_notex_ps_fpo_start;
extern uint32_t _binary_BuiltinShaders_ps_fpo_start;

namespace Sexy 
{
	
	
	class PS3StateManager : public RenderStateManager
	{
	protected:
		enum EStateGroup
		{
			SG_TRANSFORM, // [D3DTS][row number 0-3] (uses SetTransform)
			SG_BLEND, // [EBlendState] (uses cellGcmSetBlend*)
			SG_VIEWPORT, // [EViewportState] (uses cellGcmSetViewport)
			SG_TEXTURE, // [ETextureState] 
			SG_MISC, // [EMiscState][variable, see individual state]

			SG_COUNT
		};
		
		enum
		{
		//	ST_COUNT_RS = 256, // (dword)
		//	ST_COUNT_TSS = 48, // (dword)
		//	ST_COUNT_SS = 16, // (dword)
			ST_COUNT_TRANSFORM = 512 // (vector) accounts for the up to 256 D3DTS_WORLDMATRIX(index) transforms
		};

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

		enum ETextureState
		{
			ST_TEXTURE,
			ST_TEXTURE_FILTER,
			ST_TEXTURE_WRAP,
			ST_COUNT_TEXTURE
		};

		enum EMiscState
		{
			// single states
//			ST_MISC_FVF, // (dword) [0] (uses SetFVF)
//			ST_MISC_FVFSIZE, // (dword) [0] (internal; automatically updated when FVF is set)
//			ST_MISC_INDICES, // (ptr) [0] (uses SetIndices)
			ST_MISC_VERTEXSHADER, // (ptr) [0] (uses SetVertexShader)
			ST_MISC_PIXELSHADER, // (ptr) [0] (uses SetPixelShader)
//			ST_MISC_TEXTUREPALETTE, // (dword) [0] (uses SetCurrentTexturePalette)
			ST_MISC_SCISSORRECT, // (vector left top right bottom) [0] (uses SetScissorRect)
//			ST_MISC_NPATCHMODE, // (float) [0] (uses SetNPatchMode)
//			ST_MISC_VERTEXDECL, // (ptr) [0] (uses SetVertexDeclaration) // commented out; not using non-fvf vertex declarations, for compat reasons
			ST_MISC_SRCBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_DESTBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
			ST_MISC_BLTDEPTH, // (float) [0] (internal; depth buffer value used for 2D blt functions)
			ST_MISC_3DMODE, // (dword bool) [0] (internal; switches between managed ortho project and user set projection/model mats)
			ST_MISC_FRONTFACE,
			ST_MISC_CULLFACE,
			ST_MISC_DEPTHWRITE,
			ST_MISC_DEPTHTEST,
			ST_MISC_DEPTHFUNC,
			ST_MISC_ALPHATEST,
			ST_MISC_ALPHAFUNC,
			ST_MISC_ALPHAREF,

			// array states
//			ST_MISC_TEXTURE, // (ptr) [sampler number] (uses cellGcmSetTexture)
			ST_MISC_VERTEXSHADERCONST, // (vector) (parameter index) (uses cellGcmSetVertexProgramConstants)
//			ST_MISC_PIXELSHADERCONST, // (vector) (parameter index) (uses SetPixelShaderConstantF)
//			ST_MISC_CLIPPLANE, // (vector) [clip plane index] (uses SetClipPlane)
//			ST_MISC_TEXTUREREMAP, // (int) [sampler number] (internal; index of logical texture state that is actually used for this physical sampler)

			ST_MISC_ATLASENABLEDANDBASE, // (vector) [sampler number] (internal; x = 1.0 for atlas enabled or 0.0 for disabled, y = unused, z = base.x, w = base.y)
			ST_MISC_ATLASUV, // (vector) [sampler number] (internal; atlasing vectors, u.x, u.y, v.x, v.y)
			
			ST_COUNT_MISC,
			ST_COUNT_MISC_SINGLE_END = ST_MISC_VERTEXSHADERCONST // first of the array states
		};
		
		typedef std::vector<State> StateVector;

		std::vector<StateVector> mTransformStates;
		std::vector<State> mBlendStates;
		std::vector<State> mViewportStates;
		std::vector<StateVector> mTextureStates;
		std::vector<StateVector> mMiscStates;

		void InitStates();
		void ResetStates();
		
		void SetPixelShaderDirect( CGprogram inShader );
		void SetVertexShaderDirect( CGprogram inShader );

		State::FCommitFunc GetCommitFunc(State* inState);

		static bool DoCommitTransformState(RenderStateManager::State *inState);
		static bool DoCommitBlendState(RenderStateManager::State *inState);
		static bool DoCommitViewportState(RenderStateManager::State *inState);
		static bool	DoCommitTextureState(RenderStateManager::State *inState);
		static bool DoCommitMiscState(RenderStateManager::State *inState);

	public:
		PS3StateManager();
		
		virtual void Init() override;
		virtual void Reset() override;
		
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
		void SetTexture(int theStage, CellGcmTexture* theTexture);
		CellGcmTexture*	GetTexture(int theStage);

		void GetTextureFilter( int theStage, uint8_t &min, uint8_t &mag, uint8_t &conv );
		void SetTextureFilter( int theStage, uint8_t min, uint8_t mag, uint8_t conv );

		void SetTextureAddress( int theStage, uint8_t wrapU, uint8_t wrapV );

		//cellGcmSetFragmentProgram
		void SetPixelShader( CGprogram inShader );
		CGprogram GetPixelShader();

		//cellGcmSetVertexProgram
		void SetVertexShader( CGprogram inShader );
		CGprogram GetVertexShader();

		void SetVertexShaderConstantF(ulong inStartRegister, const float* inConstantData, ulong inVector4fCount);

		void SetViewport( uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max, float scale[4], float offset[4] );
		void GetViewport( uint16_t &x, uint16_t &y, uint16_t &width, uint16_t &height, float &min, float &max, float *scale, float *offset );

		void SetTransform(ulong inTS, const SexyMatrix4* inMatrix);
		void GetTransform(ulong inTS, SexyMatrix4* inMatrix) const;

		void SetScissorRect( uint16_t x, uint16_t y, uint16_t width, uint16_t height );

		CGprogram GetDefaultVertexShader(){ return mDefaultVertexShader; };

		bool GetShaderMicrocodeOffset( CGprogram shader, uint32_t &offset );

		void SetAtlasState(ulong inSampler, bool inEnabled, const SexyVector2* inBase = NULL, const SexyVector2* inU = NULL, const SexyVector2* inV = NULL);
		bool GetAtlasState(ulong inSampler, SexyVector2& outBase, SexyVector2& outU, SexyVector2& outV);

		void Set3DMode(bool in3dMode);
		bool Is3DMode();

		void SetCullFace( uint32_t cullFace );

		void SetDepthWriteEnabled( bool enable );

		void SetDepthTestEnabled( bool enable );
		void SetDepthFunc( uint32_t func );

		void SetAlphaTestEnabled( bool enable );
		void SetAlphaFunc( uint32_t func, uint32_t ref );

	private:
		friend class PS3RenderDevice;

		//default vertex/pixel shaders for falling back
		CGprogram mDefaultVertexShader;
		CGprogram mDefaultPixelShader;

		CellGcmTexture mNullTexture;

		//A map for keeping track of shader microcode that
		//has alredy been uploaded to local memory.  This should be something faster...
		std::map<CGprogram,void *> mShaderMicrocodeMap;
	};
}

#endif
