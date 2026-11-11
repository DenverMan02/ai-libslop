// TodCommon.h

#ifndef __TODCOMMON_H__
#define __TODCOMMON_H__

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/Rect.h"
#include <math.h>
#include "SexyAppFramework/MTRand.h"

namespace Sexy
{
	class Graphics;
	class Font;
	class Color;
	class Image;
	class SexyMatrix3;
	class SharedImageRef;
	class ResourceManager;
	class SexyVector2;
    class PrimeTypeface;
}

struct TodAllocator;

#define EPSILON (0.000001f)
#define PI (3.141592653f)
#define CIRCLE_FULL (PI * 2.0f)
#define CIRCLE_HALF (PI)
#define CIRCLE_QUARTER (PI * 0.50f)
#define CIRCLE_SIXTH (PI * 0.333333333f)
#define CIRCLE_EIGHTH (PI * 0.25f)
#define SECONDS_PER_UPDATE 0.01f
#define TICKS_PER_SECOND 100

const int D3DImageFlag_NeedsSanding = 0x1000;

inline int ClampInt(int num, int minNum, int maxNum)
{
	if (num <= minNum)
	{
		return minNum;
	}
	else if (num >= maxNum)
	{
		return maxNum;
	}
	else
	{
		return num;
	}
}

inline float ClampFloat(float num, float minNum, float maxNum)
{
	if (num <= minNum)
	{
		return minNum;
	}
	else if (num >= maxNum)
	{
		return maxNum;
	}
	else
	{
		return num;
	}
}

inline int FloatRoundToInt(float i_floatValue)
{
	if (i_floatValue > 0.0f)
	{
		return (int)(i_floatValue + 0.5f);
	}
	else
	{
		return (int)(i_floatValue - 0.5f);
	}
}

inline int FloatApproxEqual(float i_floatValue1, float i_floatValue2)
{
	if (fabsf(i_floatValue1 - i_floatValue2) < EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
inline float FloatLerp(float i_zeroValue, float i_oneValue, float i_time)
{
	return i_zeroValue + ((i_oneValue - i_zeroValue) * i_time);
}
*/
// macro'd this so it's faster in debug mode
#define FloatLerp(i_zeroValue, i_oneValue, i_time) (i_zeroValue) + (((i_oneValue) - (i_zeroValue)) * (i_time))

inline float Distance2D(float x1, float y1, float x2, float y2)
{
	return sqrtf( ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

//inline float DegToRad(float i_angle)
//{
//	return i_angle * (CIRCLE_FULL / 360.0f);
//}

inline float RadToDeg(float i_angle)
{
	return i_angle * (360.0f / CIRCLE_FULL);
}

class TodWeightedGridArray
{
public:
	int m_x;
	int m_y;
	int m_weight;
};

TodWeightedGridArray* TodPickFromWeightedGridArray(TodWeightedGridArray *i_array, int i_count);

class TodSmoothArray
{
public:
	int m_item;
	float m_weight;
	float m_lastPicked;
	float m_secondLastPicked;
};

int TodPickFromSmoothArray(TodSmoothArray *i_array, int i_count, Sexy::MTRand *i_optionalRandom = NULL);
void TodUpdateSmoothArrayPick(TodSmoothArray *i_array, int i_count, int i_pickIndex);

int TodSnprintf(char *i_buffer, int i_size, const char *i_format, ...);
int TodVsnprintf(char *i_buffer, int i_size, const char *i_format, va_list i_argList);

float RandRangeFloat(float i_min, float i_max);
int RandRangeInt(int i_min, int i_max);
int RandRangeInt(int i_min, int i_max, class Sexy::MTRand* i_rand);

enum DrawStringJustification
{
	DS_ALIGN_LEFT,
	DS_ALIGN_RIGHT,
	DS_ALIGN_CENTER,
	DS_ALIGN_LEFT_VERTICAL_MIDDLE,
	DS_ALIGN_RIGHT_VERTICAL_MIDDLE,
	DS_ALIGN_CENTER_VERTICAL_MIDDLE,
};


// PrimeText Change
void TodDrawString(Sexy::Graphics *g, const SexyString& i_text, int i_posX, int i_posY, Sexy::PrimeTypeface *i_font, Sexy::Color i_color, DrawStringJustification i_justification);
//void TodDrawStringMatrix(Sexy::Graphics* g, Sexy::PrimeTypeface *i_font, const Sexy::SexyMatrix3 &i_matrix, const SexyString& i_string, const Sexy::Color& i_color);
void TodDrawString(Sexy::Graphics *g, const SexyString& i_text, int i_posX, int i_posY, Sexy::Font *i_font, Sexy::Color i_color, DrawStringJustification i_justification);
//void TodDrawStringMatrix(Sexy::Graphics* g, Sexy::Font *i_font, const Sexy::SexyMatrix3 &i_matrix, const SexyString& i_string, const Sexy::Color& i_color);

void TodDrawImageCelScaled(Sexy::Graphics *g, Sexy::Image *i_imageStrip, int i_posX, int i_posY, int i_celCol, int i_celRow, float i_scaleX, float i_scaleY);
void TodDrawImageCelF(Sexy::Graphics *g, Sexy::Image *i_imageStrip, float i_posX, float i_posY, int i_celCol, int i_celRow);
void TodDrawImageCelScaledF(Sexy::Graphics *g, Sexy::Image *i_imageStrip, float i_posX, float i_posY, int i_celCol, int i_celRow, float i_scaleX, float i_scaleY);
void TodDrawImageCelCenterScaledF(Sexy::Graphics *g, Sexy::Image *i_imageStrip, float i_posX, float i_posY, int i_celCol, float i_scaleX, float i_scaleY);
void TodDrawImageScaledF(Sexy::Graphics *g, Sexy::Image *i_image, float i_posX, float i_posY, float i_scaleX, float i_scaleY);
void TodDrawImageCenterScaledF(Sexy::Graphics *g, Sexy::Image *i_image, float i_posX, float i_posY, float i_scaleX, float i_scaleY);
void TodBltMatrix(Sexy::Graphics *g, Sexy::Image *i_image, const Sexy::SexyMatrix3 &i_transform, const Sexy::Rect& i_clipRect, const Sexy::Color& i_color, int i_drawMode, const Sexy::Rect &i_srcRect);

namespace Sexy {
    Color ColorLerp(Color i_color1, Color i_color2, float i_t);    
}


enum EJustification
{
    JUST_CENTERX=1<<0,
    JUST_CENTERY=1<<1,
    JUST_BOTTOM=1<<2,
    JUST_TOP=1<<3,
    JUST_RIGHT=1<<4,
    JUST_LEFT=1<<5,
};


// like Tod's utility, but does conditional transformation based on scaling input
void DrawImageCentered(Sexy::Graphics *g, Sexy::Image* i_image, float i_cX, float i_cY, float i_scaleX, float i_scaleY);
void DrawImageCentered(Sexy::Graphics* g, Sexy::Image* i_image, float i_x, float i_y, int i_just=JUST_CENTERX|JUST_CENTERY, float i_scaleX=1.f, float i_scaleY=1.f);


#ifdef _USE_WIDE_STRING
#define sexystrncpy			wcsncpy
#define sexystrcspn			wcscspn
#define sexystrspn			wcsspn
#define sexystrchr			wcschr
#define sexystrlen			wcslen
#define sexystricmp			_wcsicmp
//#define sexystrnicmp		_wcsnicmp
#define sexystrstr			wcsstr 
#define sexyisalnum			iswalnum
#else // _USE_WIDE_STRING
#define sexystrncpy			strncpy
#define sexystrcspn			strcspn
#define sexystrspn			strspn
#define sexystrchr			strchr
#define sexystrlen			strlen
#undef sexystricmp
#define sexystricmp			_stricmp // fix warning: warning C4996: 'stricmp': The POSIX name for this item is deprecated.
//#define sexystrnicmp		_strnicmp
#define sexystrstr			strstr
#define sexyisalnum			isalnum
#endif // _USE_WIDE_STRING

std::string TodReplaceString(const std::string& i_sourceText, const std::string& i_findText, const std::string& i_substitution);
SexyString TodReplaceString(const SexyString &i_text, const SexyChar *i_stringToFind, const SexyString &i_stringToSubstitute);
SexyString TodReplaceNumberString(const SexyString &i_text, const SexyChar *i_stringToFind, int i_number);

void FixPixelsOnAlphaEdgeForBlending(Sexy::Image *i_image);
void TodMarkImageForSanding(Sexy::Image *i_image);
void TodSandImageIfNeeded(Sexy::Image *i_image);
void SexyMatrix3Inverse(const Sexy::SexyMatrix3 &m, Sexy::SexyMatrix3 &r);
void SexyMatrix3Transpose(const Sexy::SexyMatrix3 &m, Sexy::SexyMatrix3 &r);
void SexyMatrix3Translation(Sexy::SexyMatrix3 &m, MATH_TYPE x, MATH_TYPE y);
void SexyMatrix3Multiply(Sexy::SexyMatrix3 &m, const Sexy::SexyMatrix3 &l, const Sexy::SexyMatrix3 &r);
void TodScaleTransformMatrix(Sexy::SexyMatrix3 &m, MATH_TYPE x, MATH_TYPE y, MATH_TYPE i_scaleX, MATH_TYPE i_scaleY);
void TodScaleRotateTransformMatrix(Sexy::SexyMatrix3 &m, MATH_TYPE x, MATH_TYPE y, MATH_TYPE rad, MATH_TYPE i_scaleX, MATH_TYPE i_scaleY);

Sexy::Color GetFlashingColor(int i_counter, int i_flashTime);
Sexy::Color ColorAdd(const Sexy::Color &i_color1, const Sexy::Color &d);
Sexy::Color ColorsMultiply(const Sexy::Color &i_color1, const Sexy::Color &i_color2);
int ColorComponentMultiply(int i_color1, int i_color2);

bool TodFindImagePath(Sexy::Image *i_image, std::string &i_path);
void TodADeviceImageToMap(Sexy::SharedImageRef *i_image, const std::string &i_path);


void Tod_SWTri_AddAllDrawTriFuncs();

TodAllocator* FindGlobalAllocator(int size);
void FreeGlobalAllocators();

extern bool (*gAppCloseRequest)();



extern float gCurrentZBufferValue;
void TodZBufferValueClear(Sexy::Graphics *g);
void TodZBufferValueIncrement();

bool TodIsPointInPolygon(Sexy::SexyVector2 *i_polygonPoint, int i_numberPolygonPoints, const Sexy::SexyVector2 &i_checkPoint);

#endif // __TODCOMMON_H__
