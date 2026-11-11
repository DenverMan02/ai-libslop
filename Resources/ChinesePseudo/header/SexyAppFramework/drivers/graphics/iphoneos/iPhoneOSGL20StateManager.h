#ifndef IPHONEOSGL20STATEMANGER_H_INCLUDED
#define IPHONEOSGL20STATEMANGER_H_INCLUDED


#define SUPPORT_GLSL_SHADERS

#include "drivers/Graphics/opengl/BaseOpenGLStateManager.h"
#include "SexyMatrix.h"

namespace Sexy 
{
	struct ShaderInfo 
	{
		enum {
			ATTRIB_POSITION = 0,
			ATTRIB_COLOR = 1,
			ATTRIB_TEXCOORD0 =2,
			ATTRIB_TEXCOORD1 =3,
			ATTRIB_NORMAL =4,
			NUM_ATTRIBUTES
		};
        
		
		struct ShaderLayout
		{
			GLuint mProgram;
			GLuint mScreenMatrixLoc;
			uint32 mScreenMatrixRev;
			
			ShaderLayout()
			{
				mProgram = 0;
				mScreenMatrixLoc = 0;
				mScreenMatrixRev = 0;
			}
		};
		
		ShaderLayout mPacked; //for DrawPrimitive;
		ShaderLayout mUnpacked;
		ShaderLayout m3D;
		
		
		ShaderInfo()
		{
			
		}
	};
	
	class iPhoneOSGL20StateManager : public BaseOpenGLStateManager<VERSION_OPENGLES_20>
	{
	public:
		typedef BaseOpenGLStateManager<VERSION_OPENGLES_20> super;
	public:
		
		
		const static int SG_GL20 = 100;
		
		enum EGL20State
		{
			// single states
			ST_GL20_ORTHOMATRIX,
			ST_GL20_SHADERPROGRAM_ORTHO, // (GLuint) [0] 
			ST_GL20_SHADERPROGRAM_3D, // (GLuint) [0] 
			
			
			ST_COUNT_GL20,
		};
		
		std::vector<super::StateVector> mGL20States;
		
		iPhoneOSGL20StateManager();
		virtual ~iPhoneOSGL20StateManager();
		
		virtual void Init() override;
		virtual void Reset() override;
		
		virtual void InitStates() override;
		virtual void ResetStates() override;
		
		virtual void	SetTexture(int theStage, GLuint theTexture, GLuint theSrc) override;
		
		void InvalidateShader();
		
		static bool DoCommitGL20State(RenderStateManager::State* inState);
		static bool DoCommitTexGL20State(RenderStateManager::State* inState);
		
		virtual State::FCommitFunc GetCommitFunc(State* inState) override;
		//note: none of the interface is final. I'm just testing out some ideas
		// to get a hang of opengl es 2.0
		
		virtual void	SetOrthoProjection(const SexyMatrix4* matrix) override;
		
        virtual bool    IsDefaultShader();
		ShaderInfo*     GetShader();
		virtual void	SetShader(ShaderInfo* theShader);
		
		virtual void SetDefaultShader() override
        {
			SetShader(&mDefaultShader);
		}
		
        virtual void SetDefaultMultiShader() override
        {
			SetShader(&mDefaultShaderMultiTex);
        }
        
	public:
		
		
		ShaderInfo mDefaultShader;
		ShaderInfo mDefaultShaderMultiTex;
		//ShaderInfo mDefaultShaderNoTex;
		
		ShaderInfo*	mCurShader;
		
		SexyMatrix4 mScreenMatrix;
		uint32		mScreenMatrixRev;
		
		GLuint		mWhiteTex;
	};
	
}

#endif