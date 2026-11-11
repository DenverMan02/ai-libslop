#ifndef __TRectANGLE_H__
#define __TRectANGLE_H__

#include "Common.h"
#include "Point.h"
#include "SexyMath.h"
#include "SexyVector.h"

#include <list>

namespace Sexy
{

template<class _T> class TRect
{
public:
	_T mX;
	_T mY;
	_T mWidth;
	_T mHeight;

public:
#ifdef HOST_WINDOWS
	TRect(const RECT& theRect) :
		mX(theRect.left), mY(theRect.top), mWidth(theRect.right - theRect.left), mHeight(theRect.bottom - theRect.top)
	{
	}
#endif

	TRect(_T theX, _T theY, _T theWidth, _T theHeight) :
	  mX(theX), mY(theY), mWidth(theWidth), mHeight(theHeight)
	{
	}
	
	TRect(const TRect<_T>& theTRect) :
	  mX(theTRect.mX), mY(theTRect.mY), mWidth(theTRect.mWidth), mHeight(theTRect.mHeight)
	{
	}

	TRect() :
	  mX(0), mY(0), mWidth(0), mHeight(0)
	{
	}

	bool					Intersects(const TRect<_T>& theTRect) const
	{
		return !((theTRect.mX + theTRect.mWidth <= mX) ||
			(theTRect.mY + theTRect.mHeight <= mY) ||
			(theTRect.mX >= mX + mWidth) ||
			(theTRect.mY >= mY + mHeight));
	}

	TRect<_T>				Intersection(const TRect<_T>& theTRect)	const
	{
		_T x1 = max(mX, theTRect.mX);
		_T x2 = min(mX + mWidth, theTRect.mX + theTRect.mWidth);
		_T y1 = max(mY, theTRect.mY);
		_T y2 = min(mY + mHeight, theTRect.mY + theTRect.mHeight);
		if (((x2 - x1) < 0) || ((y2 - y1) < 0))
			return TRect<_T>(0,0,0,0);
		else
			return TRect<_T>(x1, y1, x2 - x1, y2 - y1);
	}

	TRect<_T>				Union(const TRect<_T>& theTRect)	
	{
		_T x1 = min(mX, theTRect.mX);
		_T x2 = max(mX + mWidth, theTRect.mX + theTRect.mWidth);
		_T y1 = min(mY, theTRect.mY);
		_T y2 = max(mY + mHeight, theTRect.mY + theTRect.mHeight);
			return TRect<_T>(x1, y1, x2 - x1, y2 - y1);
	}

	bool					Contains(_T theX, _T theY) const
	{
		return ((theX >= mX) && (theX < mX + mWidth) &&
			(theY >= mY) && (theY < mY + mHeight));
	}

	bool					Contains(const TPoint<_T>& thePoint) const
	{
		return ((thePoint.mX >= mX) && (thePoint.mX < mX + mWidth) &&
			(thePoint.mY >= mY) && (thePoint.mY < mY + mHeight));
	}

	void					Offset(_T theX, _T theY)
	{
		mX += theX;
		mY += theY;
	}

	void					Offset(const TPoint<_T>& thePoint)
	{
		mX += thePoint.mX;
		mY += thePoint.mY;
	}

	TRect					Inflate(_T theX, _T theY)
	{
		mX -= theX;
		mWidth += theX*2;
		mY -= theY;
		mHeight += theY*2;

		return *this;
	}

	void					ExpandToContain(_T theX, _T theY)
	{
		_T x1 = min(mX, theX);
		_T x2 = max(mX + mWidth, theX);
		_T y1 = min(mY, theY);
		_T y2 = max(mY + mHeight, theY);
		mX = x1;
		mY = y1;
		mWidth = x2 - x1;
		mHeight = y2 - y1;
	}

	void					Scale(double theScaleX, double theScaleY)
	{
		mX = (_T)(mX * theScaleX);
		mY = (_T)(mY * theScaleY);
		mWidth = (_T)(mWidth * theScaleX);
		mHeight = (_T)(mHeight * theScaleY);
	}

	void					Scale(double theScaleX, double theScaleY, _T theCenterX, _T theCenterY)
	{
		Offset(-theCenterX, -theCenterY);
		Scale(theScaleX, theScaleY);
		Offset(theCenterX, theCenterY);
	}

	bool operator==(const TRect<_T>& theRect) const
	{
		return (mX == theRect.mX) && (mY == theRect.mY) && (mWidth == theRect.mWidth) && (mHeight == theRect.mHeight);
	}

	bool operator!=(const TRect<_T>& theRect) const
	{
		return (mX != theRect.mX) || (mY != theRect.mY) || (mWidth != theRect.mWidth) || (mHeight != theRect.mHeight);
	}

	inline bool Clamp(_T& ioX, _T& ioY,
					  _T inHorzInset = 0.0f, _T inVertInset = 0.0f)
	{
		bool didClamp = ClampToMinMax(ioX, mX + inHorzInset, mX + mWidth - inHorzInset);
		didClamp = ClampToMinMax(ioY, mY + inVertInset, mY + mHeight - inVertInset) || didClamp;
		return didClamp;
	}

	inline bool Clamp(SexyVector2& ioPos, _T inHorzInset = 0.0f, _T inVertInset = 0.0f)
	{
		return Clamp(ioPos.x, ioPos.y, inHorzInset, inVertInset);
	}

// [PVZ CHANGE BEGIN] - Adding a 'GetCenter' function
	inline TPoint<_T> GetCenter() const
	{
		return TPoint<_T>(mX + mWidth / 2, mY + mHeight / 2);
	}
// [PVZ CHANGE END]
	
#ifdef HOST_WINDOWS
	RECT					ToRECT() const
	{
		RECT aRect = {mX, mY, mX + mWidth, mY + mHeight};
		return aRect;
	}
#endif
};

typedef TRect<int> Rect;
typedef TRect<MATH_TYPE> FRect;
typedef TRect<double> DRect;



}

#endif //__TRectANGLE_H__
