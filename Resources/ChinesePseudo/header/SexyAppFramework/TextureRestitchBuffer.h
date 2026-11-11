//
//  TextureRestitchBuffer.h
//  SexyAppFramework Prime
//
//  This buffer is necessary to piece together compressed textures as various formats
//  (such as PVRTC) do not support loading in pieces.  OpenGL returns attempts to use
//  SubTexture loading as INVALID and documentation supports this issue.
//
//  Unless we find a workaround, reconstructing the image before loading is necessary.
//
//  TextureID is intended to be a unique ID value to allow for error detection of
//  overlapping writes.  This should theoretically not happen in the resource system
//  but it is good to be sure.
//
//  Note: It is currently intentional that we do not release the buffer.  This is
//  to avoid fragmentation issues with a large late allocation.
//
//  Created by Jason Emery on 3/8/13.
//
//

#ifndef SexyAppFramework_Prime_TextureRestitchBuffer_h
#define SexyAppFramework_Prime_TextureRestitchBuffer_h

class TextureRestitchBuffer
{
public:
    TextureRestitchBuffer();
	~TextureRestitchBuffer();
	
    // Ensure we have bufferSize bytes in the buffer
    void Initialize(uint bufferSize);
    
    // Add data to the texture buffer
    void Add(int textureID, const uchar* buffer, int bytesToAdd);
    
    // Call when texture done
    void Clear(bool i_okToClearBuffer);
    
    bool IsTextureInProgress() { return textureInProgress; }
    int GetBytesInBuffer() { return bytesInBuffer; }
    uchar* GetTextureBuffer() { return textureBuffer; }
    
private:
    void allocBuffer(uint bufferSize);
    void freeBuffer();
    
    bool isInitialized;     // Lazy initialization of buffer when needed
    bool textureInProgress;
    uchar* textureBuffer;
    uint textureBufferSize;
    int textureIDInProgress;
    int bytesInBuffer;
};

#endif
