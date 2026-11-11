#ifndef __SEXYMATRIX_H__
#define __SEXYMATRIX_H__

#include "SexyVector.h"
#include "Point.h"

namespace Sexy
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SimpleMatrix
{
public:
	MATH_TYPE a;
	MATH_TYPE b;
	MATH_TYPE c;
	MATH_TYPE d;
	MATH_TYPE tx;
	MATH_TYPE ty;

public:
	SimpleMatrix(MATH_TYPE _a = 1, MATH_TYPE _b = 0, MATH_TYPE _c = 0, MATH_TYPE _d = 1, MATH_TYPE _tx = 0, MATH_TYPE _ty = 0)
	{
		a = _a;
		b = _b;
		c = _c;
		d = _d;
		tx = _tx;
		ty = _ty;
	}

	inline void Identity()
    {
        tx = 0;
        ty = 0;
        a = 1;
        b = 0;
        c = 0;
        d = 1;
    }

	inline void Translate(MATH_TYPE theX, MATH_TYPE theY)
    {
        tx += theX;
        ty += theY;
    }

    inline void Scale(MATH_TYPE theScaleX, MATH_TYPE theScaleY)
    {
        a *= theScaleX;
        b *= theScaleY;
        c *= theScaleX;
        d *= theScaleY;
        tx *= theScaleX;
        ty *= theScaleY;
    }

    inline void RotateRad(float theAngle)
    {
    	MATH_TYPE _a = a;
    	MATH_TYPE _b = b;
    	MATH_TYPE _c = c;
    	MATH_TYPE _d = d;
    	MATH_TYPE _tx = tx;
    	MATH_TYPE _ty = ty;

    	MATH_TYPE sin = MATH_TYPE(sinf(theAngle));
    	MATH_TYPE cos = MATH_TYPE(cosf(theAngle));

        a = _a * cos - _b * sin;
        b = _a * sin + _b * cos;
        c = _c * cos - _d * sin;
        d = _c * sin + _d * cos;
        tx = _tx * cos - _ty * sin;
        ty = _tx * sin + _ty * cos;
    }

	inline void RotateRadAndScale(float theAngle, MATH_TYPE theScaleX, MATH_TYPE theScaleY)
    {
		MATH_TYPE _a = a;
		MATH_TYPE _b = b;
		MATH_TYPE _c = c;
		MATH_TYPE _d = d;
        MATH_TYPE _tx = tx;
        MATH_TYPE _ty = ty;

        MATH_TYPE sin = MATH_TYPE(sinf(theAngle));
        MATH_TYPE cos = MATH_TYPE(cosf(theAngle));

        a = (_a * cos - _b * sin) * theScaleX;
        b = (_a * sin + _b * cos) * theScaleY;
        c = (_c * cos - _d * sin) * theScaleX;
        d = (_c * sin + _d * cos) * theScaleY;
        tx = (_tx * cos - _ty * sin) * theScaleX;
        ty = (_tx * sin + _ty * cos) * theScaleY;
    }

    inline void Concat(const SimpleMatrix& theMat2)
    {
    	MATH_TYPE _a = a;
    	MATH_TYPE _b = b;
    	MATH_TYPE _c = c;
    	MATH_TYPE _d = d;
    	MATH_TYPE _tx = tx;
    	MATH_TYPE _ty = ty;

        a = _a * theMat2.a + _b * theMat2.c;
        b = _a * theMat2.b + _b * theMat2.d;
        c = _c * theMat2.a + _d * theMat2.c;
        d = _c * theMat2.b + _d * theMat2.d;

        tx = _tx * theMat2.a + _ty * theMat2.c + theMat2.tx;
        ty = _tx * theMat2.b + _ty * theMat2.d + theMat2.ty;
    }

    inline void Invert()
    {
    	MATH_TYPE _a = a;
    	MATH_TYPE _b = b;
    	MATH_TYPE _c = c;
    	MATH_TYPE _d = d;
    	MATH_TYPE _tx = tx;
    	MATH_TYPE _ty = ty;

    	MATH_TYPE den = a * d - b * c;

        a = _d / den;
        b = -_b / den;
        c = -_c / den;
        d = _a / den;
        tx = (_c * _ty - _d * _tx) / den;
        ty = -(_a * _ty - _b * _tx) / den;
    }

	FPoint TransformPoint(const FPoint& thePoint)
    {
        return FPoint(tx + a*thePoint.mX + c*thePoint.mY, ty + b*thePoint.mX + d*thePoint.mY);
    }

    FPoint DeltaTransformPoint(const FPoint& thePoint)
    {
        return FPoint(a * thePoint.mX + c * thePoint.mY, b * thePoint.mX + d * thePoint.mY);
    }
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SexyMatrix3
{
public:
#if USE_FIXED_POINT
	MATH_TYPE m00, m01, m02;
	MATH_TYPE m10, m11, m12;
	MATH_TYPE m20, m21, m22;
#else //USE_FIXED_POINT
	union
    {
        float m[3][3];
        struct
        {
            float m00, m01, m02;
            float m10, m11, m12;
            float m20, m21, m22;
        };
    };
#endif //USE_FIXED_POINT

public:
	SexyMatrix3(){};
	inline SexyMatrix3(const SimpleMatrix& theSimpleMatrix)
	{
		m00 = theSimpleMatrix.a;
		m01 = theSimpleMatrix.c;
		m10 = theSimpleMatrix.b;
		m11 = theSimpleMatrix.d;
		m02 = theSimpleMatrix.tx;
		m12 = theSimpleMatrix.ty;
		m20 = 0;
		m21 = 0;
		m22 = 1;
	}

	void ZeroMatrix();
	void LoadIdentity();

	SexyVector2 operator*(const SexyVector2 &theVec) const;
	SexyVector3 operator*(const SexyVector3 &theVec) const;
	
	//jvw -- inlining this could cause some code bloat... use the Static Multiply version for speed
	SexyMatrix3 operator*(const SexyMatrix3 &theMat) const;
	
	const SexyMatrix3& operator*=(const SexyMatrix3 &theMat);
	
	// pOut == pM1 * pM2
	inline static void Multiply(SexyMatrix3 *pOut, const SexyMatrix3 *pM1, const SexyMatrix3 *pM2)
	{	
        //		pOut->m00 = pM1->m00*pM2->m00 + pM1->m01*pM2->m10 + pM1->m02*pM2->m20;
        //		pOut->m01 = pM1->m00*pM2->m01 + pM1->m01*pM2->m11 + pM1->m02*pM2->m21;
        //		pOut->m02 = pM1->m00*pM2->m02 + pM1->m01*pM2->m12 + pM1->m02*pM2->m22;
        //		pOut->m10 = pM1->m10*pM2->m00 + pM1->m11*pM2->m10 + pM1->m12*pM2->m20;
        //		pOut->m11 = pM1->m10*pM2->m01 + pM1->m11*pM2->m11 + pM1->m12*pM2->m21;
        //		pOut->m12 = pM1->m10*pM2->m02 + pM1->m11*pM2->m12 + pM1->m12*pM2->m22;
        //		pOut->m20 = pM1->m20*pM2->m00 + pM1->m21*pM2->m10 + pM1->m22*pM2->m20;
        //		pOut->m21 = pM1->m20*pM2->m01 + pM1->m21*pM2->m11 + pM1->m22*pM2->m21;
        //		pOut->m22 = pM1->m20*pM2->m02 + pM1->m21*pM2->m12 + pM1->m22*pM2->m22;
        
        ///zxy optimize, m20,m21 in matrix always are zero.
        pOut->m00 = pM1->m00*pM2->m00 + pM1->m01*pM2->m10;
		pOut->m01 = pM1->m00*pM2->m01 + pM1->m01*pM2->m11;
		pOut->m02 = pM1->m00*pM2->m02 + pM1->m01*pM2->m12 + pM1->m02*pM2->m22;
		pOut->m10 = pM1->m10*pM2->m00 + pM1->m11*pM2->m10;
		pOut->m11 = pM1->m10*pM2->m01 + pM1->m11*pM2->m11;
		pOut->m12 = pM1->m10*pM2->m02 + pM1->m11*pM2->m12 + pM1->m12*pM2->m22;
		pOut->m20 = 0;
		pOut->m21 = 0;
		pOut->m22 = pM1->m20*pM2->m02 + pM1->m21*pM2->m12 + pM1->m22*pM2->m22;
	}
	
    SexyMatrix3 Inverse() const
    {
        ///zxy optimize, m20,m21 in matrix always are zero.
        
        //float det = m00 * (m11 * m22 - m12 * m21) - m01 * (m10 * m22 - m12 * m20) + m02 * (m10 * m21 - m11 * m20);
    	MATH_TYPE det = m00 * (m11 * m22) - m01 * (m10 * m22);
        
        SexyMatrix3 ret;

//        ret.m00 = (m11 * m22 - m12 * m21) * invDet;
//        ret.m01 = (m02 * m21 - m01 * m22) * invDet;
//        ret.m02 = (m01 * m12 - m02 * m11) * invDet;
//        ret.m10 = (m12 * m20 - m10 * m22) * invDet;
//        ret.m11 = (m00 * m22 - m02 * m20) * invDet;
//        ret.m12 = (m02 * m10 - m00 * m12) * invDet;
//        ret.m20 = (m10 * m21 - m11 * m20) * invDet;
//        ret.m21 = (m01 * m20 - m00 * m21) * invDet;
//        ret.m22 = (m00 * m11 - m01 * m10) * invDet;
        

        // Since we used 22:10 fixed point, invDet will lose value because of the low precision of decimal part. Use div det directly.
        ret.m00 = (m11 * m22 - m12 * m21) / det;
        ret.m01 = (m02 * m21 - m01 * m22) / det;
        ret.m02 = (m01 * m12 - m02 * m11) / det;
        ret.m10 = (m12 * m20 - m10 * m22) / det;
        ret.m11 = (m00 * m22 - m02 * m20) / det;
        ret.m12 = (m02 * m10 - m00 * m12) / det;
        ret.m20 = 0;
        ret.m21 = 0;
        ret.m22 = (m00 * m11 - m01 * m10) / det;
        
        return ret;
    }
};

//////////////////////////////////////////////////////////////////////////

class SexyMatrix4
{
public:
#if USE_FIXED_POINT
	MATH_TYPE m00, m01, m02, m03;
	MATH_TYPE m10, m11, m12, m13;
	MATH_TYPE m20, m21, m22, m23;
	MATH_TYPE m30, m31, m32, m33;
#else//#if USE_FIXED_POINT
	union
	{
		float m[4][4];
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
	};
#endif //#if USE_FIXED_POINT
public:	
	SexyMatrix4() {}
	SexyMatrix4(MATH_TYPE in00, MATH_TYPE in01, MATH_TYPE in02, MATH_TYPE in03,
                MATH_TYPE in10, MATH_TYPE in11, MATH_TYPE in12, MATH_TYPE in13,
				MATH_TYPE in20, MATH_TYPE in21, MATH_TYPE in22, MATH_TYPE in23,
				MATH_TYPE in30, MATH_TYPE in31, MATH_TYPE in32, MATH_TYPE in33);

	void LoadIdentity();

	SexyVector3 operator*(const SexyVector2 &theVec) const;
	SexyVector3 operator*(const SexyVector3 &theVec) const;
	//SexyMatrix4 operator*(const SexyMatrix3 &theMat) const; // CDH: commented out for now; unused and extremely unintuitive anyway
	SexyMatrix4 operator*(const SexyMatrix4 &theMat) const;
	SexyMatrix4& operator*=(const SexyMatrix4 &theMat);
};

/*
	3D transformation class, in row-major style (where translation is the bottom row,
	and projection is the right-most column).  Standard outbound affine transformations
	for objects go in scale-rotate-translate order; use this when passing the matrix
	on to something requiring a world transform, such as Render3DObject).
*/
class SexyTransform3D : public SexyMatrix4
{
public:
	SexyTransform3D();
	SexyTransform3D(bool loadIdentity);
	SexyTransform3D(const SexyMatrix4& theMatrix);
	SexyTransform3D& operator=(const SexyMatrix4 &theMat);
	void Translate(MATH_TYPE tx, MATH_TYPE ty, MATH_TYPE tz);

	// rotations are counterclockwise about the given axis
	void RotateRadX(float rot);
	void RotateRadY(float rot);
	void RotateRadZ(float rot);

	void Scale(MATH_TYPE sx, MATH_TYPE sy, MATH_TYPE sz);

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyTransform2D : public SexyMatrix3
{
public:
	SexyTransform2D();
	SexyTransform2D(bool loadIdentity);
	SexyTransform2D(const SexyMatrix3& theMatrix);
    inline SexyTransform2D(const SimpleMatrix& theSimpleMatrix)
    :SexyMatrix3(theSimpleMatrix)
    {}
    
	const SexyTransform2D& operator=(const SexyMatrix3 &theMat);
	bool operator==(const SexyTransform2D& i_other);

		inline void Translate(MATH_TYPE tx, MATH_TYPE ty)
	{
		m02 += tx;
		m12 += ty;
	}

	// Rotate has been replaced by RotateRad.  
	// NOTE:  If you had Rotate(angle) you should now use RotateRad(-angle).  
	// This is to make positive rotations go counter-clockwise when using screen coordinates.
	inline void RotateRad(float rot)
	{
		SexyMatrix3 aMat;
		//aMat.LoadIdentity();
		
		MATH_TYPE sinRot = MATH_TYPE(sinf(rot));
		MATH_TYPE cosRot = MATH_TYPE(cosf(rot));
		
		
		aMat.m00 = cosRot;
		aMat.m01 = sinRot;
		aMat.m02 = 0.0f;
		aMat.m10 = -sinRot;
		aMat.m11 = cosRot;
		aMat.m12 = 0.0f;
		aMat.m20 = 0.0f;
		aMat.m21 = 0.0f;
		aMat.m22 = 1.0f;
		
		SexyMatrix3 aTemp;
		Multiply(&aTemp, &aMat,this);
		*this = aTemp;
	}
	
	inline void RotateDeg(float rot)
	{
		RotateRad(3.1415926535897932384626433832795028841971f * rot / 180.0f);
	}


	inline void Scale(MATH_TYPE sx, MATH_TYPE sy)
	{
		m00 *= sx;
		m01 *= sx;
		m02 *= sx;
		m10 *= sy;
		m11 *= sy;
		m12 *= sy;
	}

	void SkewRad(float sx, float sy);
	
	// Utility functions for generating useful transformation matrices
	static SexyTransform2D CreateTranslation(const SexyVector2& i_translation);
	static SexyTransform2D CreateRotation(float i_rotationRads);
	static SexyTransform2D CreateRotationWithPivot(float i_rotationRads, const SexyVector2& i_pivotPoint, bool i_leaveAtPivot = false);
	static SexyTransform2D CreateScale(const SexyVector2& i_scale);
	static SexyTransform2D CreateScale(float i_scale);
	static SexyTransform2D CreateTransform(const SexyVector2& i_translation, float i_rotationRads, float i_scale);
	static SexyTransform2D CreateTransform(const SexyVector2& i_translation, float i_rotationRads, const SexyVector2& i_scale);
	static SexyTransform2D CreateTransformWithPivot(const SexyVector2& i_translation, float i_rotationRads, float i_scale, const SexyVector2& i_pivotPoint, bool i_leaveAtPivot = false);
	static SexyTransform2D CreateTransformWithPivot(const SexyVector2& i_translation, float i_rotationRads, const SexyVector2& i_scale, const SexyVector2& i_pivotPoint, bool i_leaveAtPivot = false);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Transform
{
protected:
	mutable SexyTransform2D mMatrix;
	mutable bool mNeedCalcMatrix;
	void MakeComplex();
	void CalcMatrix() const;

public:
	bool mComplex, mHaveRot, mHaveScale;
	MATH_TYPE mTransX1, mTransY1, mTransX2, mTransY2;
	MATH_TYPE mScaleX, mScaleY;
	MATH_TYPE mRot;

public:
	Transform();

	void Reset();

	void Translate(MATH_TYPE tx, MATH_TYPE ty);
	void RotateRad(MATH_TYPE rot);
	void RotateDeg(MATH_TYPE rot);
	void Scale(MATH_TYPE sx, MATH_TYPE sy);
	const SexyTransform2D& GetMatrix() const;
	void SetMatrix(const SexyTransform2D& mat);	
};


} // namespace Sexy

#endif
