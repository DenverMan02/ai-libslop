#ifndef BASEGLRESSTREAMSDRIVER_H_INCLUDED
#define BASEGLRESSTREAMSDRIVER_H_INCLUDED

#include "Common.h"
#include "drivers/resstreams/BaseResStreamsDriver.h"
#include "TextureRestitchBuffer.h"

#if defined HOST_ANDROID
#include <GLES2/gl2.h>
#elif defined HOST_IPHONEOS
#include <OpenGLES/ES2/gl.h>
#elif defined HOST_MACOSX
#include <OpenGL/gl.h>
#else
#error BaseGLResStreamsDriver.h not implemented for your platform
#endif

namespace Sexy 
{
    //
    // Contains GL-centric ResStreams code common across OpenGL platforms.
    //
    
	class BaseGLResStreamsDriver : public BaseResStreamsDriver
	{
    protected:
        virtual IGraphicsDriver* GetGraphicsDriver() = 0;
        uchar* ExtractAlphaTextureData(const uchar* pCompressAlphaData, int pixels);
        
    private:
        void ExtractPalletAlphaTextureData(const uchar* pCompressDataPtr, uchar palletSize, uchar* pAlphaDataPtr, int pixels);
        void ExtractNonPalletAlphaTextureData(const uchar* pCompressDataPtr, uchar* pAlphaDataPtr, int pixels);

	protected:
        void TextureArrayRegister(void* textures, int count) const;
        void TextureArrayUnregister(void* textures, int count) const;
        void GroupTexturesDeallocate(ResStreamsGroup* theGroup) const;
        GLuint GroupTexturesAllocateMultiAtIndex(ResStreamsGroup* theGroup, int index) const;
        
        bool DestroyPool(ResStreamsPool* thePool);
        
        // Multi Texture
        // Embedded additional texture within texture resource file
        void AllocateMultiTexture(ResStreamsGroup* theNewGroup, int index, ResStreamTextureDescriptor& theTextureDesc) const;
        void AllocateMultiTexture2(ResStreamsGroup* theNewGroup, int index, ResStreamTextureDescriptor& theTextureDesc) const;
        void LoadMultiTexture(int texID, void* data, ResStreamTextureDescriptor& theTextureDesc);
        void LoadMultiTexture2(int texID, uint aColorType, uint bytesTextureTotal, void* data, ResStreamTextureDescriptor& theTextureDesc) const;

        // Compressed Textures
        void PushCompressedTexture(ResStreamTextureDescriptor& textureDesc, uint aColorType, uint aTex, uint aMultiTex, uint bytesTextureTotal, uchar* buffer);
        void PushCompressedTextureMulti(ResStreamTextureDescriptor& textureDesc, uint aColorType, uint aTex, uint aMultiTex, uint bytesTextureTotal, uint bytesFileTotal, uchar* buffer);
        
        bool TestCompressedFormatAvailable(int rsbFormat) const;
        bool IsCompressedFormatAvailable(int rsbFormat) const;
        
    public:
        // Compressed Textures
        void DecodeCompressedTextureBlock(ResStreamTextureDescriptor& textureDesc, uint aColorType, uint aTex, uint aMultiTex, uchar* buffer, uint bytesToDecode, uint bytesTextureTotal, uint bytesFileTotal);
        void ClearCompressedTextureBuffer();
        
    private:
        uint mCurrentCompressedTextureID;
        TextureRestitchBuffer       mTextureRestitchBuffer;
	};
}

#endif
