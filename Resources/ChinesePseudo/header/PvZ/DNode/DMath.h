//
//  DMath.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DMath_h
#define DMath_h

#include "SexyMatrix.h"

#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)

#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_EPSILON                0.000001f

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

class DVec2
{
public:
    float x,y;
    inline DVec2()
    :x(0.0f)
    ,y(0.0f)
    {
    }
    inline DVec2(float _x,float _y) { set(_x,_y); }
    inline DVec2(const DVec2& p) { set(p); }
    
    inline void  add(const DVec2& p) { x += p.x;y += p.y;}
    inline void  sub(const DVec2& p) { x -= p.x;y -= p.y;}
    inline void  scale(float s) {x *= s; y *= s;}
    inline void  scale(const DVec2& scale){ x*= scale.x; y *= scale.y;}
    inline void  neg() {x = -x; y = -y;}
    inline float lengthSquared() const{ return x*x + y*y;}
    
    inline DVec2 lerp(const DVec2& other, float alpha) const
    {
        return *this * (1.f - alpha) + other * alpha;
    }
    
    inline DVec2 getPerp() const
    {
        return DVec2(-y, x);
    }
    
    DVec2& clamp(const DVec2& min, const DVec2& max);
    
    inline DVec2 project(const DVec2& other) const
    {
        return other * (dot(other)/other.dot(other));
    }
    
    inline DVec2 rotate(const DVec2& other) const
    {
        return DVec2(x*other.x - y*other.y, x*other.y + y*other.x);
    }
    
    static inline DVec2 forAngle(const float a)
    {
        return DVec2(cosf(a), sinf(a));
    }
    
    static float dot(const DVec2& v1, const DVec2& v2);
    
    inline DVec2 getMidpoint(const DVec2& v) const
    {
        return DVec2((x + v.x) * 0.5f, (y + v.y) * 0.5f);
    }
    
    inline float getDistance(const DVec2& other) const
    {
        return (*this - other).getLength();
    }
    
    inline float getAngle() const
    {
        return atan2f(y, x);
    }
    
    float getAngle(const DVec2& other) const;
    
    void  normalize();
    DVec2 getNormalized() const;
    
    inline void set(float _x,float _y) { x = _x; y = _y; }
    inline void set(const DVec2& p) { x = p.x; y = p.y; }
    
    inline void setZero() { x = y = 0.0f;}
    inline void setOne() { x = y = 1.0f;}
    
    inline void smooth(const DVec2& target, float elapsedTime, float responseTime)
    {
        if (elapsedTime > 0)
        {
            *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
        }
    }
    
    inline bool isZero() const
    {
        return x == 0.0f && y == 0.0f;
    }
    
    inline bool isOne() const
    {
        return x == 1.0f && y == 1.0f;
    }
    
    inline float dot(const DVec2& v) const
    {
        return x*v.x+y*v.y;
    }
    
    inline float cross(const DVec2& v) const
    {
        return x*v.y - y*v.x;
    }
    
    inline const DVec2 operator+(const DVec2& v) const
    {
        DVec2 result(*this);
        result.add(v);
        return result;
    }
    
    inline const DVec2 operator-(const DVec2& v) const
    {
        DVec2 result(*this);
        result.sub(v);
        return result;
    }
    
    inline const DVec2 operator*(const DVec2& v) const
    {
        DVec2 result(*this);
        result.scale(v);
        return result;
    }
    
    inline const DVec2 operator*(const float s) const
    {
        return DVec2(this->x * s, this->y * s);
    }
    
    inline const DVec2 operator/(const float s) const
    {
        return DVec2(this->x / s, this->y / s);
    }
    
    inline DVec2& operator += (const DVec2& p)
    {
        add(p);
        return *this;
    }
    
    inline DVec2& operator -= (const DVec2& p)
    {
        sub(p);
        return *this;
    }
    
    inline DVec2& operator *= (float s)
    {
        scale(s);
        return *this;
    }
    
    inline DVec2& operator *= (const DVec2& s)
    {
        scale(s);
        return *this;
    }
    
    inline const DVec2 operator-() const
    {
        DVec2 result(*this);
        result.neg();
        return result;
    }
    
    inline bool operator<(const DVec2& v) const
    {
        if (x == v.x)
        {
            return y < v.y;
        }
        return x < v.x;
    }
    
    inline bool operator>(const DVec2& v) const
    {
        if (x == v.x)
        {
            return y > v.y;
        }
        return x > v.x;
    }
    
    inline bool operator==(const DVec2& v) const
    {
        return x==v.x && y==v.y;
    }
    
    inline bool operator!=(const DVec2& v) const
    {
        return x!=v.x || y!=v.y;
    }
    
    float getLength() const;
    
    inline float distanceSquared(const DVec2& p) const
    {
        float dx = p.x - x;
        float dy = p.y - y;
        return (dx * dx + dy * dy);
    }
    
    static const DVec2 ZERO;
    static const DVec2 ONE;
    static const DVec2 UNIT_X;
    static const DVec2 UNIT_Y;
    static const DVec2 ANCHOR_MIDDLE;
    static const DVec2 ANCHOR_BOTTOM_LEFT;
    static const DVec2 ANCHOR_TOP_LEFT;
    static const DVec2 ANCHOR_BOTTOM_RIGHT;
    static const DVec2 ANCHOR_TOP_RIGHT;
    static const DVec2 ANCHOR_MIDDLE_RIGHT;
    static const DVec2 ANCHOR_MIDDLE_LEFT;
    static const DVec2 ANCHOR_MIDDLE_TOP;
    static const DVec2 ANCHOR_MIDDLE_BOTTOM;
};

inline const DVec2 operator*(float s, const DVec2& v)
{
    return DVec2(v.x * s, v.y * s);
}

class DVec3
{
public:
    float x,y,z;
    inline DVec3()
    :x(0.0f)
    ,y(0.0f)
    ,z(0.0f)
    {
    }
    inline DVec3(float _x,float _y,float _z) { set(_x,_y,_z); }
    inline DVec3(const DVec3& p) { set(p); }
    
    inline void set(float _x,float _y,float _z) { x = _x; y = _y; z = _z; }
    inline void set(const DVec3& p) { x = p.x; y = p.y; z = p.z;}
    
    inline void setZero() { x = y = z = 0.0f;}
    inline void setOne() { x = y = z = 1.0f;}
    inline void neg() {x = -x; y = -y; z = -z;}
    inline float lengthSquared() const{ return x*x + y*y + z*z;}
    
    void  normalize();
    DVec3 getNormalized() const;
    
    inline void  add(const DVec3& p) { x += p.x;y += p.y; z += p.z;}
    inline void  sub(const DVec3& p) { x -= p.x;y -= p.y; z -= p.z;}
    inline void  scale(float s) {x *= s; y *= s;z *= s;}
    inline void  scale(const DVec3& scale){ x*= scale.x; y *= scale.y; z *= scale.z;}
    inline DVec3 getMidpoint(const DVec3& v) const
    {
        return DVec3((x + v.x) * 0.5f, (y + v.y) * 0.5f ,(z + v.z) * 0.5f);
    }
    float getLength() const;
    
    inline float getDistance(const DVec3& other) const
    {
        return (*this - other).getLength();
    }
    
    inline const DVec3 operator+(const DVec3& v) const
    {
        DVec3 result(*this);
        result.add(v);
        return result;
    }
    
    inline const DVec3 operator-(const DVec3& v) const
    {
        DVec3 result(*this);
        result.sub(v);
        return result;
    }
    
    inline const DVec3 operator*(const DVec3& v) const
    {
        DVec3 result(*this);
        result.scale(v);
        return result;
    }
    
    inline const DVec3 operator*(const float s) const
    {
        return DVec3(this->x * s, this->y * s, this->z * s);
    }
    
    inline const DVec3 operator/(const float s) const
    {
        return DVec3(this->x / s, this->y / s, this->z / s);
    }
    
    inline DVec3& operator += (const DVec3& p)
    {
        add(p);
        return *this;
    }
    
    inline DVec3& operator -= (const DVec3& p)
    {
        sub(p);
        return *this;
    }
    
    inline DVec3& operator *= (float s)
    {
        scale(s);
        return *this;
    }
    
    inline DVec3& operator *= (const DVec3& s)
    {
        scale(s);
        return *this;
    }
    
    inline const DVec3 operator-() const
    {
        DVec3 result(*this);
        result.neg();
        return result;
    }
    
    inline bool operator<(const DVec2& v) const
    {
        if (x == v.x)
        {
            return y < v.y;
        }
        return x < v.x;
    }
    
    inline bool operator>(const DVec3& v) const
    {
        if (x == v.x)
        {
            if (y == v.y)
            {
                return z > v.z;
            }
            return y > v.y;
        }
        return x > v.x;
    }
    
    inline bool operator==(const DVec3& v) const
    {
        return x==v.x && y==v.y && z == v.z;
    }
    
    inline bool operator!=(const DVec3& v) const
    {
        return x!=v.x || y!=v.y || z != v.z;
    }
    
    DVec3& clamp(const DVec3& min,const DVec3& max);
    
    inline float distanceSquared(const DVec3& p) const
    {
        float dx = p.x - x;
        float dy = p.y - y;
        float dz = p.z - z;
        return (dx * dx + dy * dy + dz * dz);
    }
    inline DVec3 lerp(const DVec3& other, float alpha) const
    {
        return *this * (1.f - alpha) + other * alpha;
    }
    
    inline void smooth(const DVec3& target, float elapsedTime, float responseTime)
    {
        if (elapsedTime > 0)
        {
            *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
        }
    }
    
    static const DVec3 ZERO;
    static const DVec3 ONE;
};

inline const DVec3 operator*(float s, const DVec3& v)
{
    return DVec3(v.x * s, v.y * s, v.z * s);
}

class DMatrix:public Sexy::SimpleMatrix
{
public:
    DMatrix()
    {
        tx = 0;
        ty = 0;
        a = 1;
        b = 0;
        c = 0;
        d = 1;
    }
    
    DMatrix(const DMatrix& other)
    {
        tx = other.tx;
        ty = other.ty;
        a = other.a;
        b = other.b;
        c = other.c;
        d = other.d;
    }
    
    inline void SetMatrix(MATH_TYPE theX,MATH_TYPE theY,float theAngle = 0.0f,MATH_TYPE scaleX = 1,MATH_TYPE scaleY = 1)
    {
        MATH_TYPE sin = MATH_TYPE(sinf(theAngle));
        MATH_TYPE cos = MATH_TYPE(cosf(theAngle));
        
        a = cos * scaleX;
        b = sin * scaleX;
        c = - sin * scaleY;
        d = cos * scaleY;
        tx = theX;
        ty = theY;
    }
    
    inline void Translate2(MATH_TYPE theX, MATH_TYPE theY)
    {
        tx += a*theX + c*theY;
        ty += b*theX + d*theY;
    }
    
    inline void Scale2(MATH_TYPE theScaleX, MATH_TYPE theScaleY)
    {
        a *= theScaleX;
        b *= theScaleX;
        c *= theScaleY;
        d *= theScaleY;
    }
    
    inline void RotateRad2(float theAngle)
    {
        MATH_TYPE _a = a;
        MATH_TYPE _b = b;
        MATH_TYPE _c = c;
        MATH_TYPE _d = d;
        
        MATH_TYPE sin = MATH_TYPE(sinf(theAngle));
        MATH_TYPE cos = MATH_TYPE(cosf(theAngle));
        
        a = _a * cos + _c * sin;
        b = _b * cos + _d * sin;
        c = _c * cos - _a * sin;
        d = _d * cos - _b * sin;
    }
    
    inline void Concat2(const SimpleMatrix& theMat2)
    {
        MATH_TYPE _a = a;
        MATH_TYPE _b = b;
        MATH_TYPE _c = c;
        MATH_TYPE _d = d;
        MATH_TYPE _tx = tx;
        MATH_TYPE _ty = ty;
        MATH_TYPE _a2 = theMat2.a;
        MATH_TYPE _b2 = theMat2.b;
        MATH_TYPE _c2 = theMat2.c;
        MATH_TYPE _d2 = theMat2.d;
        MATH_TYPE _tx2 = theMat2.tx;
        MATH_TYPE _ty2 = theMat2.ty;
        
        a = _a * _a2 + _c * _b2;
        c = _a * _c2 + _c * _d2;
        b = _b * _a2 + _d * _b2;
        d = _b * _c2 + _d * _d2;
        
        tx = _a * _tx2 + _c * _ty2 + _tx;
        ty = _b * _tx2 + _d * _ty2 + _ty;
    }
    
    inline const DMatrix operator * (const DMatrix& other) const
    {
        DMatrix s(*this);
        
        s.Concat2(other);
        
        return s;
    }
};

#endif
