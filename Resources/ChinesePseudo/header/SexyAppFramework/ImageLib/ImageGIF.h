
#pragma once
#include "ImageLib.h"

namespace ImageLib
{
	Image* GetGIFImage(const std::string& theFileName, int thePakLibSearchOrder);
	Image* GetGIFImage(const Sexy::Buffer* buffer);
}
