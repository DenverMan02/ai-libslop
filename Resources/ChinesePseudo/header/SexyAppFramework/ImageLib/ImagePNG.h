
#pragma once
#include "ImageLib.h"

namespace ImageLib
{
	Image* GetPNGImage( const std::string& theFileName, int thePakLibSearchOrder );
	Image* GetPNGImage( const Sexy::Buffer* buffer );
	bool WritePNGImage(const std::string& theFileName, Image* theImage, int theQuality);
}
