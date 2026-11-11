#ifndef __COLOR_H__
#define __COLOR_H__

#include "Common.h"

namespace Sexy
{
#ifdef HOST_AIRPLAY
	//no pragma pack on airplay. 
struct SexyRGBA {unsigned char b,g,r,a;};
#else
#pragma pack(push,1)
struct SexyRGBA {unsigned char b,g,r,a;};
#pragma pack(pop)
#endif

class Color
{
public:
	int mRed;
	int mGreen;
	int mBlue;
	int mAlpha;

	enum PredefinedColor
	{
		Invalid = -1,
		Black,
		White,
		Red,
		Orange,
		Yellow,
		Green,
		Blue,
		Purple,
		Cyan
	};

public:
	Color();
	Color(const Color& theColor);
	Color(int theColor);
	Color(int theColor, int theAlpha);
	Color(int theRed, int theGreen, int theBlue);
	Color(int theRed, int theGreen, int theBlue, int theAlpha);
	Color(const SexyRGBA &theColor);
	Color(const uchar* theElements);	
	Color(const int* theElements);
	Color(const PredefinedColor c);

	int						GetRed() const;
	int						GetGreen() const;
	int						GetBlue() const;
	int						GetAlpha() const;
	uint32					ToInt() const;	
	SexyRGBA				ToRGBA() const;
    bool                    IsInvalid() const;
    
	int&					operator[](int theIdx);
	int						operator[](int theIdx) const;	

	Color					operator*(const Color& theColor) const;
	Color					operator*(float theAlphaPct) const;

	static Color			FromInt(ulong theColor);
	static Color			FAlpha(float theAlpha);
	static Color			FromHSV(float i_h, float i_s, float i_v);

	RA_METAMETHOD_TOSTRING(ToString)
	{
		return StrFormat("(%d, %d, %d, %d)", mRed, mGreen, mBlue, mAlpha);
	}
};

bool operator==(const Color& theColor1, const Color& theColor2);
bool operator!=(const Color& theColor1, const Color& theColor2);
Color operator+(const Color& theColor1, const Color& theColor2);
Color operator-(const Color& theColor1, const Color& theColor2);

}

#endif //__COLOR_H__
