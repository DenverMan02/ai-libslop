
#pragma once
#include "ImageLib.h"

namespace ImageLib
{
	Image* GetJPEGImage( const std::string& theFileName, int thePakLibSearchOrder );
	Image* GetJPEGImage( const Sexy::Buffer* buffer );
	bool WriteJPEGImage(const std::string& theFileName, Image* theImage, int theQuality);
}
