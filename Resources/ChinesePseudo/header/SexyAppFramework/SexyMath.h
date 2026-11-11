#pragma once
#ifndef __SEXYMATH_H__
#define __SEXYMATH_H__
//****************************************************************************
//**
//**  File     :  SEXYMATH.H
//**  Summary  :  Header - Math utilities
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include <math.h>
#include <vector>

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
const float SEXYMATH_PI			= 3.14159265f;
const float SEXYMATH_2PI		= 6.2831853f;
const float SEXYMATH_E			= 2.71828f;
const float SEXYMATH_PHI		= 1.618033989f; // Golden ratio
const float SEXYMATH_INVPHI		= 0.618033989f; // Inverse golden ratio
const float SEXYMATH_EPSILON	= 0.001f; // small epsilon for imprecise comparisons
const float SEXYMATH_EPSILONSQ	= 0.000001f; // square of small epsilon

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
/*
	SexyMath
*/
class SexyMath
{
public:
	// absolute value
	inline static float Fabs(float inX)
	{
	#ifdef _M_IX86
		unsigned long i = *((unsigned long*)&inX) & 0x7fffffff; // utilize IEEE 754 single-precision float format (where bit 31 is sign bit)
		return (*((float*)&i));
	#else
		return (float)fabs(inX);
	#endif
	}
	inline static double Fabs(double inX) { return fabs(inX); } // double-precision form just for template purposes (in ApproxEquals etc)

	// degree/radian conversions
	inline static float DegToRad(float inX) { return (inX * SEXYMATH_PI) / 180.0f; }
	inline static float RadToDeg(float inX) { return (inX * 180.0f) / SEXYMATH_PI; }

	// approximate equality within a given tolerance
	template<class T> inline static bool ApproxEquals(const T& inL, const T& inR, const T& inTol)
	{
		return (Fabs(inL-inR) <= inTol);
	}

	// linear interpolation between A and B, using a given 0-1 alpha
	template<class T> inline static T Lerp(const T& inA, const T& inB, float inAlpha)
	{
		return  (T)(inA + ((inB-inA) * inAlpha));
	}
	template<class T> inline static T Lerp(const T& inA, const T& inB, double inAlpha)
	{
		return  (T)(inA + ((inB-inA) * inAlpha));
	}

	// whether a given unsigned integer is a power of two
	inline static bool IsPowerOfTwo(unsigned long inX)
	{
		return(inX && !(inX & (inX - 1)));
	}
    
    // Solves for the two real solutions for x of the quadratic equation 'a*x^2 + b*x + c = 0'.
	// Returns 'false' if there are no solutions, the parameters do not specify a quadratic equation,
	// or the solutions are complex.
	static bool QuadraticFormula(float i_a, float i_b, float i_c, float &o_rootA, float& o_rootB)
	{
		if (i_a == 0.f)
		{
			// Not a quadratic equation
			return false;
		}
		const float det = i_b * i_b - 4 * i_a * i_c;
		if (det < 0.f)
		{
			// Complex solutions
			return false;
		}
		const float sqrtDet = sqrtf(det);
		o_rootA = ((-i_b) + sqrtDet) / (2 * i_a);
		o_rootB = ((-i_b) - sqrtDet) / (2 * i_a);
		return true;
	}
};

/*
	SexyMathHermite - Piecewise hermite interpolation polynomial class
	See "Numerical Analysis" (by Burden & Faires) Algorithm 3.3 (p 128) for more information.
*/
class SexyMathHermite
{
public:
	struct SPoint
	{
		float mX; // x
		float mFx; // f(x)
		float mFxPrime; // f'(x)

		SPoint() {}
		
		SPoint(float inX, float inFx, float inFxPrime)
		: mX(inX), mFx(inFx), mFxPrime(inFxPrime)
		{}
	};
	std::vector<SPoint> mPoints;

	SexyMathHermite()
	: mIsBuilt(false)
	{}

	inline void Rebuild()
	{
		mIsBuilt = false;
	}
	float Evaluate(float inX)
	{
		if (!mIsBuilt)
		{
			if (!BuildCurve())
				return(0.f);
			mIsBuilt = true;
		}

		// find the appropriate piece
		unsigned int pieceCount = (unsigned int)mPieces.size();
		for (unsigned int i=0;i<pieceCount;i++)
		{
			if (inX < mPoints[i+1].mX)
				return(EvaluatePiece(inX, &mPoints[i], &mPieces[i]));
		}
		return mPoints[mPoints.size()-1].mFx;
	}

protected:
	struct SPiece
	{
		float mCoeffs[4];
	};
	std::vector<SPiece> mPieces;
	bool mIsBuilt;

	void CreatePiece(SPoint* inPoints, SPiece* outPiece)
	{
		const unsigned int dim = 4;

		// Build temporary Q 2D array and Z array
		float qbuf[dim*dim];
		float* q[dim];
		for (unsigned int i=0;i<dim;i++)
			q[i] = &qbuf[i*dim];
		float z[dim];

		// Construct Z and Q
		for (unsigned int i=0;i<=1;i++)
		{
			unsigned int i2 = 2*i;
			z[i2] = inPoints[i].mX;
			z[i2+1] = inPoints[i].mX;
			q[i2][0] = inPoints[i].mFx;
			q[i2+1][0] = inPoints[i].mFx;
			q[i2+1][1] = inPoints[i].mFxPrime;
			if (i)
			{
				q[i2][1] = (q[i2][0] - q[i2-1][0]) / (z[i2] - z[i2-1]);
			}
		}
		for (unsigned int i=2;i<dim;i++)
		{
			for (unsigned int j=2;j<=i;j++)
				q[i][j] = (q[i][j-1] - q[i-1][j-1]) / (z[i] - z[i-j]);
		}

		// Output coefficients are the diagonal of Q
		for (unsigned int i=0;i<dim;i++)
			outPiece->mCoeffs[i] = q[i][i];
	}

	float EvaluatePiece(float inX, SPoint* inPoints, SPiece* inPiece)
	{
		const unsigned int dim = 4;

		// compute x - x[n] array
		float xSub[2];
		xSub[0] = inX - inPoints[0].mX;
		xSub[1] = inX - inPoints[1].mX;

		// compute H(x)
		float f = 1.0f;
		float h = inPiece->mCoeffs[0];
		for (unsigned int i=1;i<dim;i++)
		{
			f *= xSub[(i-1)/2];
			h += f * inPiece->mCoeffs[i];
		}
		return h;
	}

	bool BuildCurve()
	{
		mPieces.clear();
		unsigned int pointCount = (unsigned int)mPoints.size();
		if (pointCount < 2)
			return(0); // need at least two points
		unsigned int pieceCount = pointCount - 1;
		mPieces.reserve(pieceCount);
		mPieces.resize(pieceCount);
		for (unsigned int i=0;i<pieceCount;i++)
			CreatePiece(&mPoints[i], &mPieces[i]);
		return true;
	}
};

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================

// These return true if they did have to clamp (useful for doing a SEXY_WARN if necessary)

template <typename T, typename U>
inline bool ClampToMin( T& ioVal, const U& inMinVal )
{
	if (ioVal < inMinVal)
	{
		ioVal = inMinVal;
		return true;
	}
	return false;
}

template <typename T, typename U>
inline bool ClampToMax( T& ioVal, const U& inMaxVal )
{
	if (ioVal > inMaxVal)
	{
		ioVal = inMaxVal;
		return true;
	}
	return false;
}

template <typename T, typename U, typename V>
inline bool ClampToMinMax( T& ioVal, const U& inMinVal, const V& inMaxVal )
{
	if (ioVal < inMinVal)
	{
		ioVal = inMinVal;
		return true;
	}
	else if (ioVal > inMaxVal)
	{
		ioVal = inMaxVal;
		return true;
	}
	return false;
}


inline bool IsNear(float inG0, float inG1, float inEpsilon = SEXYMATH_EPSILON) 
{
	return fabs(inG0 - inG1) < inEpsilon; 
}

inline bool IsNearZero(float inG0, float inEpsilon = SEXYMATH_EPSILON) 
{
	return IsNear(inG0, 0.0f, inEpsilon); 
}

static inline int GetClosestPowerOf2Above(int theNum)
{
    int aPower2 = 1;
    while (aPower2 < theNum)
        aPower2<<=1;
    
    return aPower2;
}

static inline bool IsPowerOf2(int theNum)
{
    return ( theNum != 0 ) && !( theNum & (theNum-1) );
}

//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

};
//****************************************************************************
//**
//**    END HEADER SEXYMATH.H
//**
//****************************************************************************

//#if OPTIMIZE_ANIM_DRAW
//#define USE_FIXED_POINT 1
//#endif
//remove USE_FIXED_POINT, please fix precision for some popanim
#define USE_FIXED_POINT 0

#if USE_FIXED_POINT
#include "SexyFixedPoint.h"
#define MATH_FIXED_POINT_TYPE fixed_t
#define MATH_TYPE MATH_FIXED_POINT_TYPE
//This is used to scale the screen matrix since we are using 22:10 fixed point which doesn't have enough precision for decimal part.
#define MATH_TYPE_RENDER_MATRIX_SCALE (MATH_TYPE(1024))
#else
#define MATH_TYPE float
#define MATH_TYPE_RENDER_MATRIX_SCALE (1.0f)
#endif


#endif // __SEXYMATH_H__
