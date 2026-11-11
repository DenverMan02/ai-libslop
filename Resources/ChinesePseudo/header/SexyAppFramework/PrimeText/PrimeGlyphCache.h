//
//  PrimeGlyphCache.h
//  SexyAppFramework Prime
//
//  Created by Jason Emery on 3/28/13.
//
//

#ifndef __SexyAppFramework_Prime__PrimeGlyphCache__
#define __SexyAppFramework_Prime__PrimeGlyphCache__

#include "Prime_EATech_Bridge.h"
#include "SexyAppBase.h"

namespace Sexy
{

///////////////////////////////////////////////////////////////////////////////
// EAMTEXT_INTERNAL_CACHED_GLYPH_COUNT_MAX
//
// Maximum number of glyph to cache in an internal buffer that will be sent
// individually at the end of the update.  If more glyph than that or the glyph
// exceed the buffer size, the object will stop to cache them and will send
// the whole texture that contain every glyph at the end of the update.  The
// purpose of this is to reduce the time spent by the cpu to update the glyph
// cache on the GPU
//
#define EAMTEXT_INTERNAL_CACHED_GLYPH_COUNT_MAX (8)

///////////////////////////////////////////////////////////////////////////////
// EAMTEXT_INTERNAL_CACHED_GLYPH_SIZE
//
// Average size of a cached glyph.
//
#define EAMTEXT_INTERNAL_CACHED_GLYPH_SIZE (64)

///////////////////////////////////////////////////////////////////////////////
// EAMTEXT_INTERNAL_CACHED_GLYPH_BPP
//
// Number of bytes per pixel a glyph has.
//
#define EAMTEXT_INTERNAL_CACHED_GLYPH_BPP (4)

///////////////////////////////////////////////////////////////////////////////
// EAMTEXT_INTERNAL_CACHE_SIZE
//
// Internal buffer that contain glyph to send individually on the GPU.  The size
// correspond to EAMTEXT_CACHED_GLYPH_COUNT_MAX * (EAMTEXT_CACHED_GLYPH_SIZE)^2 * (bytes per pixels)
//
#define EAMTEXT_INTERNAL_CACHE_SIZE (EAMTEXT_INTERNAL_CACHED_GLYPH_COUNT_MAX*EAMTEXT_INTERNAL_CACHED_GLYPH_SIZE*EAMTEXT_INTERNAL_CACHED_GLYPH_SIZE*EAMTEXT_INTERNAL_CACHED_GLYPH_BPP)

//This structure is also used by external renderer to bind or manipulate the texture data.
struct PrimeGlyphCacheTextureInfo
{
    uint32_t*             mpTextureData;              ///< Container for the texture data filled by EAText
    Sexy::DeviceImage*    mImage;                 ///< OpenGL textureId.
};

////////////////////////////////////////////////////////////////////////////////
/// Implements a glyph cache specialized for EAMGraphic OpenGL ES
////////////////////////////////////////////////////////////////////////////////
class PrimeGlyphCache : public EA::Text::GlyphCache
{
public:
    /// Constructor.
    PrimeGlyphCache(EA::Allocator::ICoreAllocator* allocator, Sexy::SexyAppBase* appPointer, int textureSize);
    
    /// Create an OpenGl texture based on the textureInfo specifications and
    /// attach it to textureInfo.
    virtual uintptr_t CreateTexture(EA::Text::TextureInfo* textureInfo);
    
    /// Destroy the texture attached the texture info.
    virtual bool DestroyTexture(EA::Text::TextureInfo* textureInfo);
    
    /// The texture is about to be updated. Perform startup task.
    virtual bool BeginUpdate(EA::Text::TextureInfo* textureInfo);
    
    /// The texture is ready to be written, write data to it.
    virtual bool EndUpdate(EA::Text::TextureInfo* textureInfo);
    
    /// Keep information on the written area and call the function on the EAText GlyphCache
    virtual bool WriteTextureArea(EA::Text::TextureInfo* pTextureInfo, uint32_t nDestPositionX, uint32_t nDestPositionY,
                                  const void* pSourceData, uint32_t nSourceSizeX, uint32_t nSourceSizeY,
                                  uint32_t sourceStride, uint32_t nSourceFormat);
    
    virtual void WriteTextureArea(void* pDest, uint32_t nDestPositionX, uint32_t nDestPositionY,
                                  uint32_t nDestStride, uint32_t nDestFormat,
                                  const void* pSourceData, uint32_t nSourceSizeX, uint32_t nSourceSizeY,
                                  uint32_t nSourceStride, uint32_t nSourceFormat);
    
    // Clear the glyph cache entirely
    void Clear();
    
    void DebugDrawCache(Sexy::Graphics* g, int x, int y);
    
    void SetGlyphPadding(int padding) { mnGlyphPadding = padding; }
    
private:
    /// Hidden copy constructor.
    PrimeGlyphCache(const PrimeGlyphCache&);
    
    /// Hidden assignment operator.
    void operator=(const PrimeGlyphCache&);
    
    /// Gets and ensures DeviceImage is ready for receiving glyphs
    Sexy::DeviceImage* PrepareGlyphImage(EA::Text::TextureInfo* textureInfo);
    
    Sexy::DeviceImage* GetGlyphImage(EA::Text::TextureInfo* textureInfo);

    void CopyEntireGlyphImage(EA::Text::TextureInfo* textureInfo);

private:
    /// Track texture handle and associated system memory.
    struct InternalGlyphInfo
    {
        int32_t miDestX;
        int32_t miDestY;
        int32_t miSizeX;
        int32_t miSizeY;
        int32_t miOffset;
    };
    
    //This structure is also used by UTFWin in the graphic driver.
    InternalGlyphInfo	mInternalGlyphInfo[EAMTEXT_INTERNAL_CACHED_GLYPH_COUNT_MAX];	///< Contain info of internally cached glyph
    uint32_t			miInternalGlyphCount;											///< Contain the number of cached glyph
    int32_t			    miInternalOffset;												///< Cursor into the internal buffer to know from where we can continue to write.
    uint8_t				mpInternalCache[EAMTEXT_INTERNAL_CACHE_SIZE];					///< Container for the sub texture data filled by EAText
    bool				mbIsCachingInternaly;											///< Used to know if we are caching the glyph internaly
    bool                mbFullCopyOnNextUpdate;                                         ///< Redraw entire texture on next glyph update
    
    //Used to check if the user is trying to update more than one texture glyph at the time.  This is not supported since
    //using multiple texture to draw the text is not efficient.
    EA::Text::TextureInfo* mCurrentTextureInfo;
    
    //
    Sexy::SexyAppBase* mAppPointer;
};
    
} // namespace Sexy
    
#endif /* defined(__SexyAppFramework_Prime__PrimeGlyphCache__) */




