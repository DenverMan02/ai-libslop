#ifndef __NATIVEDISPLAY_H__
#define __NATIVEDISPLAY_H__
#include "Common.h"

namespace Sexy
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class NativeDisplay
{
public:
	int						mRGBBits;
	uint32_t				mRedMask;
	uint32_t				mGreenMask;
	uint32_t				mBlueMask;
	int						mRedBits;
	int						mGreenBits;
	int						mBlueBits;
	int						mRedShift;
	int						mGreenShift;
	int						mBlueShift;

	int*					mRedAddTable;
	int*					mGreenAddTable;
	int*					mBlueAddTable;

	uint32_t				mRedConvTable[256];
	uint32_t				mGreenConvTable[256];
	uint32_t				mBlueConvTable[256];
public:
	NativeDisplay();

};

};


#endif