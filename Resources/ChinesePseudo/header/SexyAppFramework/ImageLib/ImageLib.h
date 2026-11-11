#ifndef __IMAGELIB_H__
#define __IMAGELIB_H__

#include <string>
#include "Common.h"
#include "Buffer.h"
#include "PakLib/PakInterface.h"

namespace ImageLib
{

class Image
{
public:
	int						mWidth;
	int						mHeight;
	uint32*					mBits;
	int 					mOriginalSizeBytes;

public:
	Image();
    Image( Image* );
	virtual ~Image();

	int						GetWidth();
	int						GetHeight();
	uint32*					GetBits();
};

class ImageLineDecoder
{
public:
	virtual ~ImageLineDecoder()
	{
	}

	virtual bool HadError() { return false; }
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void GetNextLine(ulong* theBitsOut) = 0;
};

bool WriteJPEGImage(const std::string& theFileName, Image* theImage, int theQuality = 80);
bool WritePNGImage(const std::string& theFileName, Image* theImage, int theDPI = 0);
bool WriteTGAImage(const std::string& theFileName, Image* theImage);

/* CDH temporarily commented out due to namespace conflicts for Buffer
bool CompressPNGImage( Sexy::Buffer &dstBuffer, Image *theImage, int theDPI = 0 );
*/

bool LoadGIFToTextureAlpha(PFILE* fp, int expected_width, int expected_height, uint8* pBits, uint32 Pitch);
bool LoadPNGToTextureAlpha(PFILE* fp, int expected_width, int expected_height, uint8* pBits, uint32 Pitch);

extern int gAlphaComposeColor;
extern bool gAutoLoadAlpha;
extern std::string gColorFileName;
extern std::string gAlphaFileName;

Image* GetImage(const std::string& theFileName, bool lookForAlphaImage = true, int thePakLibSearchOrder = -1);
Image* GetImage(const Sexy::Buffer* buffer);

/**
 * PTX is a super-lightweight texture format used for Xbox and PS3 (or any system
 * that can use textures straight from RAM).  This header info sits at the end of
 * the texture's bytes so that the texture can be more easily byte aligned to
 * system restrictions (4k on Xbox and PS3).  The PS3 data must be DMA'd into local memory
 */
struct PTXImageHeader
{
	int width;
	int height;
	int pitch;
	int type;
};

}

#endif //__IMAGELIB_H__
