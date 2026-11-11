#ifndef __SEXYVECTOR_H__
#define __SEXYVECTOR_H__

#include "SexyMath.h"

namespace Sexy
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyVector2
{
public:
	MATH_TYPE x,y;

public:
	SexyVector2() : x(0), y(0) { }
	SexyVector2(MATH_TYPE theX, MATH_TYPE theY) : x(theX), y(theY) { }

	MATH_TYPE Dot(const SexyVector2 &v) const { return x*v.x + y*v.y; }
	SexyVector2 operator+(const SexyVector2 &v) const { return SexyVector2(x+v.x, y+v.y); }
	SexyVector2 operator-(const SexyVector2 &v) const { return SexyVector2(x-v.x, y-v.y); }
	SexyVector2 operator-() const { return SexyVector2(-x, -y); }
	SexyVector2 operator*(MATH_TYPE t) const { return SexyVector2(t*x, t*y); }
	SexyVector2 operator/(MATH_TYPE t) const { return SexyVector2(x/t, y/t); }
	
	SexyVector2& operator+=(const SexyVector2 &v) { x+=v.x; y+=v.y; return *this; }
	SexyVector2& operator-=(const SexyVector2 &v) { x-=v.x; y-=v.y; return *this; }
	SexyVector2& operator*=(MATH_TYPE t) { x*=t; y*=t; return *this; }
	SexyVector2& operator/=(MATH_TYPE t) { x/=t; y/=t; return *this; }

	bool operator==(const SexyVector2 &v) { return x==v.x && y==v.y; }
	bool operator!=(const SexyVector2 &v) { return x!=v.x || y!=v.y; }

	inline MATH_TYPE Magnitude() const { return sqrtf(x*x + y*y); }
	inline MATH_TYPE MagnitudeSquared() const { return x*x+y*y; }

	SexyVector2 Normalize() const 
	{ 
		MATH_TYPE aMag = Magnitude();
		return aMag!=0 ? (*this)/aMag : *this;
	}

	SexyVector2 Perp() const
	{
		return SexyVector2(-y, x);
	}
	
	// Returns the shortest angle between the two vectors in radians
	// 	- The input vectors do not have to be normalized
	//	- The output is the absolute value of the difference, it will NOT be signed
	static float AngleBetween(const SexyVector2& i_a, const SexyVector2& i_b)
	{
		float theta = acos(i_a.Dot(i_b) / (i_a.Magnitude() * i_b.Magnitude()));
		return theta;
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyAxes3;
class SexyCoords3;

class SexyVector3
{
public:
	MATH_TYPE x,y,z;
public:
	SexyVector3() : x(0), y(0), z(0) { }
	SexyVector3(MATH_TYPE theX, MATH_TYPE theY, MATH_TYPE theZ) : x(theX), y(theY), z(theZ) { }

	MATH_TYPE Dot(const SexyVector3 &v) const { return x*v.x + y*v.y + z*v.z; }
	SexyVector3 Cross(const SexyVector3 &v) const { return SexyVector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }
	
	SexyVector3& operator=(const SexyVector3& v) { x=v.x; y=v.y; z=v.z; return *this; }
	SexyVector3& operator+=(const SexyVector3& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
	SexyVector3& operator-=(const SexyVector3& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
	SexyVector3& operator*=(MATH_TYPE t) { x*=t; y*=t; z*=t; return *this; }
	SexyVector3& operator*=(const SexyVector3& v) { x*=v.x; y*=v.y; z*=v.z; return *this; }
	SexyVector3& operator/=(MATH_TYPE t) { x/=t; y/=t; z/=t; return *this; }
	SexyVector3& operator/=(const SexyVector3& v) { x/=v.x; y/=v.y; z/=v.z; return *this; }

	SexyVector3 operator-() const { return SexyVector3(-x, -y, -z); }
	SexyVector3 operator+(const SexyVector3 &v) const { return SexyVector3(x+v.x, y+v.y, z+v.z); }
	SexyVector3 operator-(const SexyVector3 &v) const { return SexyVector3(x-v.x, y-v.y, z-v.z); }
	SexyVector3 operator*(MATH_TYPE t) const { return SexyVector3(t*x, t*y, t*z); }
	SexyVector3 operator*(const SexyVector3& v) const { return SexyVector3(x*v.x, y*v.y, z*v.z); }
	SexyVector3 operator/(MATH_TYPE t) const { return SexyVector3(x/t, y/t, z/t); }
	SexyVector3 operator/(const SexyVector3& v) const { return SexyVector3(x/v.x, y/v.y, z/v.z); }

	inline MATH_TYPE Magnitude() const { return sqrtf(x*x + y*y + z*z); }
	inline MATH_TYPE MagnitudeSquared() const { return (x*x + y*y + z*z); }

	SexyVector3 Normalize() const 
	{ 
		MATH_TYPE aMag = Magnitude();
		return aMag!=0 ? (*this)/aMag : *this;
	}

	bool ApproxEquals(const SexyVector3& inV, float inTol = SEXYMATH_EPSILON) const
	{ 
		return(SexyMath::ApproxEquals<float>(float(x), float(inV.x), inTol)
			&& SexyMath::ApproxEquals<float>(float(y), float(inV.y), inTol)
			&& SexyMath::ApproxEquals<float>(float(z), float(inV.z), inTol));
	}
	bool ApproxZero(float inTol = SEXYMATH_EPSILON) const
	{
		return ApproxEquals(SexyVector3(MATH_TYPE(0), MATH_TYPE(0), MATH_TYPE(0)), inTol);
	}

	// These methods are supplied in SexyCoords.h; include that header alongside this one if you wish to call these.
	inline SexyVector3 Enter(const SexyAxes3& inAxes) const;
	inline SexyVector3 Enter(const SexyCoords3& inCoords) const;
	inline SexyVector3 Leave(const SexyAxes3& inAxes) const;
	inline SexyVector3 Leave(const SexyCoords3& inCoords) const;
	
//	SexyVector3& operator>>= (const SexyAxes3& inA) { *this = Enter(inA); return *this; }
//	SexyVector3& operator>>= (const SexyCoords3& inC) { *this = Enter(inC); return *this; }
//	SexyVector3& operator<<= (const SexyAxes3& inA) { *this = Leave(inA); return *this; }
//	SexyVector3& operator<<= (const SexyCoords3& inC) { *this = Leave(inC); return *this; }
//	SexyVector3 operator>> (const SexyAxes3& inA) const { return Enter(inA); }
//	SexyVector3 operator>> (const SexyCoords3& inC) const { return Enter(inC); }
//	SexyVector3 operator<< (const SexyAxes3& inA) const { return Leave(inA); }
//	SexyVector3 operator<< (const SexyCoords3& inC) const { return Leave(inC); }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyVector4
{
public:
	MATH_TYPE x,y,z,w;
public:
	SexyVector4() : x(0), y(0), z(0), w(0) { }
	SexyVector4(MATH_TYPE theX, MATH_TYPE theY, MATH_TYPE theZ, MATH_TYPE theW) : x(theX), y(theY), z(theZ), w(theW) { }
};

};
#endif
