#ifndef __POINT_H__
#define __POINT_H__

#include "Common.h"

namespace Sexy
{

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4244)
#endif

template<class _T> class TPoint
{
public:
	_T						mX;
	_T						mY;

public:
	TPoint(_T theX, _T theY) : 
		mX(theX),
		mY(theY)
	{
	}

	TPoint(const TPoint<_T>& theTPoint) :
		mX(theTPoint.mX),
		mY(theTPoint.mY)
	{
	}

	TPoint() :
		mX(0),
		mY(0)
	{
	}

	inline bool operator==(const TPoint& p) const
	{
		return ((p.mX == mX) && (p.mY == mY));
	}

	inline bool operator!=(const TPoint& p) const
	{
		return ((p.mX != mX) || (p.mY != mY));
	}

	_T Magnitude() const
	{
		return (_T) sqrt((double)mX*mX+mY*mY);
	}

	TPoint operator+(const TPoint& p) const {return TPoint(mX+p.mX, mY+p.mY);}
	TPoint operator-(const TPoint& p) const {return TPoint(mX-p.mX, mY-p.mY);}
	TPoint operator*(const TPoint& p) const {return TPoint(mX*p.mX, mY*p.mY);}
	TPoint operator/(const TPoint& p) const {return TPoint(mX/p.mX, mY/p.mY);}
	TPoint& operator+=(const TPoint& p)  {mX+=p.mX; mY+=p.mY; return *this;}
	TPoint& operator-=(const TPoint& p)  {mX-=p.mX; mY-=p.mY; return *this;}
	TPoint& operator*=(const TPoint& p)  {mX*=p.mX; mY*=p.mY; return *this;}
	TPoint& operator/=(const TPoint& p)  {mX/=p.mX; mY/=p.mY; return *this;}
	TPoint operator*(float s) const {return TPoint(_T(mX*s), _T(mY*s));} 
	TPoint operator/(float s) const {return TPoint(_T(mX/s), _T(mY/s));}	
	TPoint operator*(double s) const {return TPoint(_T(mX*s), _T(mY*s));} 
	TPoint operator/(double s) const {return TPoint(_T(mX/s), _T(mY/s));}	
	TPoint operator*(int s) const {return TPoint(_T(mX*s), _T(mY*s));} 
	TPoint operator/(int s) const {return TPoint(_T(mX/s), _T(mY/s));} 
};

template<class _T>
inline TPoint<_T> operator*(double theNum, const TPoint<_T>& thePoint)
{
	return thePoint*theNum;
}

template<class _T>
inline TPoint<_T> operator*(int theNum, const TPoint<_T>& thePoint)
{
	return thePoint*theNum;
}

#ifdef WIN32
#pragma warning(pop)
#endif

class Point : public TPoint<int>
{
	typedef TPoint<int> super;

public:
	Point(int theX, int theY) : super(theX, theY) {}
	Point(const Point& thePoint) : super(thePoint) {}
	Point() : super() {}
	Point(const TPoint<int>& thePoint) : super(thePoint) {}
};

class FPoint : public TPoint<float>
{
	typedef TPoint<float> super;

public:
	FPoint(float theX, float theY) : super(theX, theY) {}
	FPoint(const FPoint& thePoint) : super(thePoint) {}
	FPoint() : super() {}
	FPoint(const TPoint<float>& thePoint) : super(thePoint) {}
};

class DPoint : public TPoint<double>
{
	typedef TPoint<double> super;

public:
	DPoint(double theX, double theY) : super(theX, theY) {}
	DPoint(const DPoint& thePoint) : super(thePoint) {}
	DPoint() : super() {}
	DPoint(const TPoint<double>& thePoint) : super(thePoint) {}
};

};

#endif //__POINT_H__
