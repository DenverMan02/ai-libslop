
#pragma once

#include "ConsoleApp.h"
#include "Rect.h"

// widescreen offsets
#define WS_OFFSET 80
#define WS_OFFSET_FULL ( WS_OFFSET * 2 )

// Use these for clarity when you're dealing with screen res. Logical coords assumed everywhere else.
typedef int ScreenResInt;
typedef float ScreenResFloat;
typedef double ScreenResDouble;
#if USE_FIXED_POINT
typedef MATH_FIXED_POINT_TYPE ScreenResFixed;
#endif


class ScaledApp : public ConsoleApp
{
private:
    
    float	m_scaleAmount;
    int		m_scaleAmountInt;
    float	m_uIScaleAmount;
    int		m_uIScaleAmountInt;
#if USE_FIXED_POINT
    MATH_FIXED_POINT_TYPE m_scaleAmountFixed;
    MATH_FIXED_POINT_TYPE m_uIScaleAmountFixed;
#endif
	int		m_screenResolution;
	int		m_uIScreenResolution;
	int		m_baseScreenResolution;

public:

    ScaledApp()
    {
		m_baseScreenResolution = 600;

		SetResolution(1200);
    }

public:		

	void SetResolution(int i_screenResolution)
	{
		// Set resolution to use for scaling
		m_screenResolution = i_screenResolution;

		// Update cached scale amounts (Actual resolution / base resolution)
		m_scaleAmount = (float) m_screenResolution / (float) m_baseScreenResolution;
		m_scaleAmountInt = (int) ((float) m_screenResolution / (float) m_baseScreenResolution + 0.2f);
#if USE_FIXED_POINT
		m_scaleAmountFixed = MATH_FIXED_POINT_TYPE(m_scaleAmount);
#endif
	}

	void SetUIResolution(int i_screenResolution)
	{
		// Set resolution to use for scaling
		m_uIScreenResolution = i_screenResolution;
		
		// Update cached scale amounts (Actual resolution / base resolution)
		m_uIScaleAmount = (float) m_uIScreenResolution / (float) m_baseScreenResolution;
		m_uIScaleAmountInt = (int) ((float) m_uIScreenResolution / (float) m_baseScreenResolution + 0.2f);
#if USE_FIXED_POINT
		m_uIScaleAmountFixed = MATH_FIXED_POINT_TYPE(m_uIScaleAmount);
#endif
	}

    float GetScaleAmount() { return m_scaleAmount; }
    int   GetScaleAmountInt() { return m_scaleAmountInt; }
    int   GetScreenResolution() { return m_screenResolution;}

    float GetUIScaleAmount() { return m_uIScaleAmount; }
    int   GetUIScaleAmountInt() { return m_uIScaleAmountInt; }
    int   GetUIScreenResolution() { return m_uIScreenResolution;}

#if USE_FIXED_POINT
    MATH_FIXED_POINT_TYPE GetScaleAmountFixed() { return m_scaleAmountFixed; }
    MATH_FIXED_POINT_TYPE GetUIScaleAmountFixed() { return m_uIScaleAmountFixed; }
#endif
    
    ScreenResInt ScaleNum(int i_num)
    {
        return (int) (GetScaleAmount() * i_num); //GetScaleAmount()Int;
    }

    ScreenResFloat ScaleNum(float i_num)
    {
        return i_num * GetScaleAmount();
    }

    ScreenResDouble ScaleNum(double i_num)
    {
        return i_num * GetScaleAmount(); 
    }

    Sexy::Rect ScaleNum(const Sexy::Rect& i_rect)
    {
        return Sexy::Rect(i_rect.mX * GetScaleAmount(), i_rect.mY * GetScaleAmount(), i_rect.mWidth * GetScaleAmount(), i_rect.mHeight * GetScaleAmount());
    }

    int ScreenScaleNum(ScreenResInt i_num)
    {
        return (int) (i_num / GetScaleAmount()); //GetScaleAmount()Int;
    }

    float ScreenScaleNum(ScreenResFloat i_num)
    {
        return i_num / GetScaleAmount();
    }

    double ScreenScaleNum(ScreenResDouble i_num)
    {
        return i_num / GetScaleAmount();
    }

    Sexy::Rect ScreenScaleNum(const Sexy::Rect &i_rect)
    {
        return Sexy::Rect(ScreenScaleNum(i_rect.mX), ScreenScaleNum(i_rect.mY), ScreenScaleNum(i_rect.mWidth), ScreenScaleNum(i_rect.mHeight));
    }

	
    ScreenResInt UIScaleNum(int i_num)
    {
        return (int) (GetUIScaleAmount() * i_num); //GetScaleAmount()Int;
    }
	
    ScreenResFloat UIScaleNum(float i_num)
    {
        return i_num * GetUIScaleAmount();
    }
	
    ScreenResDouble UIScaleNum(double i_num)
    {
        return i_num * GetUIScaleAmount(); 
    }
	
    Sexy::Rect UIScaleNum(const Sexy::Rect& i_rect)
    {
        return Sexy::Rect(i_rect.mX * GetUIScaleAmount(), i_rect.mY * GetUIScaleAmount(), i_rect.mWidth * GetUIScaleAmount(), i_rect.mHeight * GetUIScaleAmount());
    }
	
    int UIScreenScaleNum(ScreenResInt i_num)
    {
        return (int) (i_num / GetUIScaleAmount()); //GetScaleAmount()Int;
    }
	
    float UIScreenScaleNum(ScreenResFloat i_num)
    {
        return i_num / GetUIScaleAmount();
    }
	
    double UIScreenScaleNum(ScreenResDouble i_num)
    {
        return i_num / GetUIScaleAmount();
    }
	
    Sexy::Rect UIScreenScaleNum(const Sexy::Rect &i_rect)
    {
        return Sexy::Rect(UIScreenScaleNum(i_rect.mX), UIScreenScaleNum(i_rect.mY), UIScreenScaleNum(i_rect.mWidth), UIScreenScaleNum(i_rect.mHeight));
    }	
	
	
    int UltraScreenScaleNum(ScreenResInt i_num)
    {
        return i_num / 2;  // div by 1200/600 to get from ultra to normal
    }

    float UltraScreenScaleNum(ScreenResFloat i_num)
    {
        return i_num / 2.f;  // div by 1200/600 to get from ultra to normal
    }

    double UltraScreenScaleNum(ScreenResDouble i_num)
    {
        return i_num / 2.0;  // div by 1200/600 to get from ultra to normal
    }
#if USE_FIXED_POINT
    ScreenResFixed ScaleNum(MATH_FIXED_POINT_TYPE i_num)
    {
    	return i_num * GetScaleAmountFixed();
    }

    MATH_FIXED_POINT_TYPE ScreenScaleNum(ScreenResFixed i_num)
	{
		return (MATH_FIXED_POINT_TYPE) ((float)i_num / GetScaleAmount()); //GetScaleAmount()Int;
	}

    ScreenResFixed UIScaleNum(MATH_FIXED_POINT_TYPE i_num)
	{
		return i_num * GetUIScaleAmountFixed();
	}

    MATH_FIXED_POINT_TYPE UIScreenScaleNum(ScreenResFixed i_num)
	{
		return (float)i_num / GetUIScaleAmount();
	}

    MATH_FIXED_POINT_TYPE UltraScreenScaleNum(ScreenResFixed i_num)
    {
        return i_num / 2;  // div by 1200/600 to get from ultra to normal
    }
#endif
};

template <typename T>
static T S( T i_val )     
{ 
    return ((ScaledApp*)Sexy::gSexyApp)->ScaleNum( i_val ); 
}

// prefer INV_S() since ScreenScale sounds like you're scaling >to< the screen res, rather than an inverse scale.
template <typename T>
static T INV_S( T i_val )     
{ 
    return ((ScaledApp*)Sexy::gSexyApp)->ScreenScaleNum( i_val ); 
}

template <typename T>
static T UI_S( T i_val )     
{ 
    return ((ScaledApp*)Sexy::gSexyApp)->UIScaleNum( i_val ); 
}

// prefer INV_S() since ScreenScale sounds like you're scaling >to< the screen res, rather than an inverse scale.
template <typename T>
static T INV_UI_S( T i_val )     
{ 
    return ((ScaledApp*)Sexy::gSexyApp)->UIScreenScaleNum( i_val ); 
}

// for use with ImgXOfs()/ImgYOfs(), as those values are in ultra def
template <typename T>
static T U_INV_S( T i_val )     
{ 
    return ((ScaledApp*)Sexy::gSexyApp)->UltraScreenScaleNum( i_val ); 
}

// for use with ImgXOfs()/ImgYOfs(), as those values are in ultra def
template <typename T>
static T U_RS( T i_val )     
{ 
    return S( U_INV_S( i_val ) ); 
}

// retain old func
#define SS(num) INV_S(num)
#define DS(num) INV_S(num)
#ifdef HOST_ANDROID
#define MS(num) S(M(num))
#define M(num)  (num)
#else
#define MS(num) S(num)
#define M(num)  (num)
#endif

