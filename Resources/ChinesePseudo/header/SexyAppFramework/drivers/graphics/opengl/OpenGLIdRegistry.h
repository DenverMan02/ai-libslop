#ifndef OPENGLIDREGISTRY_H_INCLUDED
#define OPENGLIDREGISTRY_H_INCLUDED

/**
 * It's assumed that system OpenGL headers will be
 * included before this header.
 */
#include "SexyAppBase.h"

#include <map>

// TODO: Convert all this to regular unsigned ints and drop the this explicit OGL dependency
#if defined HOST_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined HOST_IPHONEOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif defined HOST_MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#endif

namespace Sexy
{


	struct OpenGLIdRegistry
	{
		private:
			static OpenGLIdRegistry * spGlobalRegistry;
		private:
			typedef std::vector<GLuint> RegistryType;
        
            // Textures
			RegistryType mTextureValidList;
			RegistryType mTextureInvalidList;

            // Shaders
            RegistryType mShaderValidList;
            RegistryType mShaderInvalidList;
            
            bool mFocusPending;
        
            

		public:
			OpenGLIdRegistry():mFocusPending(true)
			{}

			static void StaticStartup()
			{
				spGlobalRegistry = new OpenGLIdRegistry;
			}

			static void StaticShutdown()
			{
				delete spGlobalRegistry;
				spGlobalRegistry = NULL;
			}

			static void StaticValidateAllIds()
			{
				if (spGlobalRegistry)
				{
					spGlobalRegistry->ValidateAllIds();
				}
			}

            //
            // Textures
            //
			static bool StaticIsTextureIdValid( GLuint texId )
			{
				if (spGlobalRegistry)
				{
					return spGlobalRegistry->TextureIdIsValid( texId );
				}

				// if we're not intiaillized, then all asked-about textures are valid
				return true;
			}

			static void StaticRegisterIds( int numTexids, GLuint const * texIds )
			{
				if (spGlobalRegistry)
				{
					spGlobalRegistry->RegisterTextureIds( numTexids, texIds );
				}
			}

			static void StaticUnregisterIds( int numTexids, GLuint const * texIds )
			{
				if (spGlobalRegistry)
				{
					spGlobalRegistry->UnregisterTextureIds( numTexids, texIds );
				}
			}
        
            //
            // Shaders
            //
            static bool StaticIsShaderIdValid( GLuint texId )
            {
                if (spGlobalRegistry)
                {
                    return spGlobalRegistry->ShaderIdIsValid( texId );
                }
                
                // if we're not intiaillized, then all asked-about textures are valid
                return true;
            }
            
            static void StaticRegisterShaderIds( int numTexids, GLuint const * texIds )
            {
                if (spGlobalRegistry)
                {
                    spGlobalRegistry->RegisterShaderIds( numTexids, texIds );
                }
            }
            
            static void StaticUnregisterShaderIds( int numTexids, GLuint const * texIds )
            {
                if (spGlobalRegistry)
                {
                    spGlobalRegistry->UnregisterShaderIds( numTexids, texIds );
                }
            }
        
        
			static void StaticLostFocus( )
			{
				if (spGlobalRegistry)
				{
					spGlobalRegistry->LostFocus();
				}
			}
			static void StaticGotFocus( )
			{
				if (spGlobalRegistry)
				{
					spGlobalRegistry->GotFocus();
				}
			}

		private:
			void ValidateAllIds();
			bool TextureIdIsValid( GLuint texId );
            bool ShaderIdIsValid( GLuint texId );
			void RegisterTextureIds( int numTexids, GLuint const * texIds );
			void UnregisterTextureIds( int numTexIds, GLuint const * deadTexIdxs );
            void RegisterShaderIds( int numSurfaceids, GLuint const * surfaceIds );
            void UnregisterShaderIds( int numSurfaceIds, GLuint const * deadSurfaceIdxs );

			void LostFocus(){ mFocusPending = true;}
			void GotFocus(){mFocusPending = false;}

            void ValidateAllIds(RegistryType& validList, RegistryType& invalidList, GLboolean (*resourceTest)(GLuint id), std::string resourceName);
            bool TestIdIsValid(RegistryType& validList, RegistryType& invalidList, GLuint id, std::string resourceName);
            void RegisterIds(RegistryType &validList, RegistryType &invalidList, int numTexIds, GLuint const * texIds, std::string resourceName);
            void UnregisterIds(RegistryType &validList, RegistryType &invalidList, int numIds, GLuint const * deadIdArray, std::string resourceName );
        
            static const std::string mResourceNameTexture;// = "surface";
            static const std::string mResourceNameShader;// = "shader";

	};

}

#endif // OPENGLIDREGISTRY_H_INCLUDED
