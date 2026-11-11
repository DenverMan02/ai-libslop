//
//  Utils.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 5/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Utils_h
#define PlantsVersusZombies2_Utils_h

#include "Curve.h"
#include "SexyVector.h"
#include <algorithm>
#include <string>
#include "Rect.h"
#include <sstream>
#include "TimeMgr.h"



namespace Sexy {
    class Graphics;
    template <class _T> class TRect;
    
    template<class T>
    class SexyBox2
    {
    public:
        SexyBox2(const SexyVector2& vmin, const SexyVector2& vmax)
        {
            bounds[0] = vmin;
            bounds[1] = vmax;
        }
        
        SexyBox2(const TRect<T>& i_rect)
        {
            bounds[0] = {static_cast<float>(i_rect.mX), static_cast<float>(i_rect.mY)};
            bounds[1] = {static_cast<float>(i_rect.mX + i_rect.mWidth), static_cast<float>(i_rect.mY + i_rect.mHeight)};
        }
        
        SexyVector2 bounds[2];
    };
    
    class SexyBox3
    {
    public:
        SexyBox3(const SexyVector3& vmin, const SexyVector3& vmax)
        {
            bounds[0] = vmin;
            bounds[1] = vmax;
        }
        SexyVector3 bounds[2];
    };
    
    class SexyRay2
    {
    public:
        SexyRay2(const SexyVector2& i_origin, const SexyVector2& i_direction) :
        m_origin(i_origin),
        m_direction(i_direction)
        {
            m_invdir.x = 1.0f / m_direction.x;
            m_invdir.y = 1.0f / m_direction.y;
            
            m_sign[0] = (m_invdir.x < 0);
            m_sign[1] = (m_invdir.y < 0);
        }
        
        SexyVector2 m_origin;
        SexyVector2 m_direction;
        SexyVector2 m_invdir;
        int m_sign[2];
    };
    
    class SexyRay3
    {
    public:
        SexyRay3(const SexyVector3& i_origin, const SexyVector3& i_direction) :
        m_origin(i_origin),
        m_direction(i_direction)
        {
            m_invdir.x = 1.0f / m_direction.x;
            m_invdir.y = 1.0f / m_direction.y;
            m_invdir.z = 1.0f / m_direction.z;
            
            m_sign[0] = (m_invdir.x < 0);
            m_sign[1] = (m_invdir.y < 0);
            m_sign[2] = (m_invdir.z < 0);
        }
        
        SexyVector3 m_origin;
        SexyVector3 m_direction;
        SexyVector3 m_invdir;
        int m_sign[3];
    };
    
}  // namespace Sexy

inline Sexy::SexyVector3 CurveLerp(float i_startParam, float i_endParam, float i_param, const Sexy::SexyVector3& i_start, const Sexy::SexyVector3& i_end, CurveType i_curve)
{
    Sexy::SexyVector3 outVec; 
    
    outVec.x = CurveLerp(i_startParam, i_endParam, i_param, i_start.x, i_end.x, i_curve);
    outVec.y = CurveLerp(i_startParam, i_endParam, i_param, i_start.y, i_end.y, i_curve);
    outVec.z = CurveLerp(i_startParam, i_endParam, i_param, i_start.z, i_end.z, i_curve);
    
    return outVec;
}

void DrawRadialCooldown(Sexy::Graphics* i_g, float i_percent, float i_centerX, float i_centerY, float i_radius, Sexy::Color i_emptyColor, Sexy::Color i_fullColor);

// Samples a sin wave at a certain time with the given interval, peak and valley values
float SampleSinWave(float i_interval, float i_min, float i_max, float i_time);

template <class U, class V> void RemoveItem(U& io_vector, const V& i_item)
{
	typename U::iterator iItem = std::find(io_vector.begin(), io_vector.end(), i_item);
	if (iItem != io_vector.end())
	{
		io_vector.erase(iItem);	
	}
}

// CalculateTossVelocity
//	- Given a start and end position (in Board-space), an apex height, and a time of flight,
//	calculate and return a velocity and acceleration that we should travel along
inline void CalculateTossVelocity(const SexyVector3& i_startPosition, const SexyVector3& i_endPosition, float i_apexHeight, pvztime_t i_hangTime, SexyVector3& o_velocity, SexyVector3& o_acceleration)
{
    // x and y are trivial :D
    const SexyVector3 toTarget = i_endPosition - i_startPosition;
    const SexyVector3 toTargetVelocity = toTarget / i_hangTime;
	o_velocity = toTargetVelocity;

    // z is not trivial D: Z is used as the height differential in this. y = y + z;
    // This math will give us the acceleration and initial velocity of a projectile
    // that travels to the given height over the given time span.
	const float peakDiff = min(i_apexHeight - i_startPosition.z, i_apexHeight - i_endPosition.z);
    const float gravity = -fabs(peakDiff / (i_hangTime * 0.5f - i_hangTime * i_hangTime * 0.125f));
    const float velInit = -(gravity * i_hangTime) * 0.5f;
	o_velocity.z += velInit;
	o_acceleration = SexyVector3(0, 0, gravity);
}


extern "C"
{
#ifdef WIN32
#include <Rpc.h>
#else
    #ifdef HOST_IPHONEOS
    #include <uuid/uuid.h>
    #else
    // TODO: ANDROID COMPILE HACK
    #endif
#endif
}

inline std::string GenerateUUID()
{
#ifdef WIN32
    UUID uuid;
    UuidCreate ( &uuid );
    
    unsigned char * str;
    UuidToStringA ( &uuid, &str );
    
    std::string s( ( char* ) str );
    
    RpcStringFreeA ( &str );
#else
#ifdef HOST_IPHONEOS
    uuid_t uuid;
    uuid_generate_random ( uuid );
    char s[37];
    uuid_unparse ( uuid, s );
#else
    // TOOD: ANDROID COMPILE HACK
    char s[37];
#endif
#endif    
    return s;
}

// Intersection tests
template <class T>
bool RectRayIntersection(const TRect<T> &i_rect, const SexyRay2 &i_ray)
{
    SexyBox2<T> box{i_rect};
    
    if (i_ray.m_direction.x == 0)
    {
        bool xBetween = ((i_ray.m_origin.x >= box.bounds[0].x) && (i_ray.m_origin.x <= box.bounds[1].x));
        if (i_ray.m_direction.y <= 0)
        {
            return (xBetween && (i_ray.m_origin.y >= box.bounds[0].y));
        }
        if (i_ray.m_direction.y > 0)
        {
            return (xBetween && (i_ray.m_origin.y <= box.bounds[1].y));
        }
    }
    
    if (i_ray.m_direction.y == 0)
    {
        bool yBetween = ((i_ray.m_origin.y >= box.bounds[0].y) && (i_ray.m_origin.y <= box.bounds[1].y));
        if (i_ray.m_direction.x <= 0)
        {
            return (yBetween && (i_ray.m_origin.x >= box.bounds[0].x));
        }
        if (i_ray.m_direction.x > 0)
        {
            return (yBetween && (i_ray.m_origin.x <= box.bounds[1].x));
        }
    }
    
    T txmin = (box.bounds[0].x - i_ray.m_origin.x) / i_ray.m_direction.x;
    T txmax = (box.bounds[1].x - i_ray.m_origin.x) / i_ray.m_direction.x;
    if (txmin > txmax)
    {
        std::swap(txmin, txmax);
    }
    
    T tymin = (box.bounds[0].y - i_ray.m_origin.y) / i_ray.m_direction.y;
    T tymax = (box.bounds[1].y - i_ray.m_origin.y) / i_ray.m_direction.y;
    if (tymin > tymax)
    {
        std::swap(tymin, tymax);
    }
    
    if ((txmin > tymax) || (tymin > txmax))
    {
        return false;
    }
    
    if ((txmax < 0) || (tymax < 0))
    {
        return false;
    }
    
    return true;
}

template <class T>
bool RectCircleIntersection(const Sexy::TRect<T> &i_rect, const Sexy::SexyVector2 &i_circlePos, const float i_circleRadius)
{
    float xDist = fabs(i_rect.mX + i_rect.mWidth / 2.0f - i_circlePos.x);
    float yDist = fabs(i_rect.mY + i_rect.mHeight / 2.0f - i_circlePos.y);

    // test to see if we're outside of the rectangle completely
    if (xDist > i_rect.mWidth / 2.0f + i_circleRadius || yDist > i_rect.mHeight / 2.0f + i_circleRadius)
        return false;

    // test to see whether we're inside the rectangle
    if (xDist <= i_rect.mWidth / 2.0f || yDist <= i_rect.mHeight / 2.0f)
        return true;

    // do the last corner case test to see if we're intersection with the corner or not
    float distSqrd = (xDist - i_rect.mWidth / 2.0f) * (xDist - i_rect.mWidth / 2.0f) +
                     (yDist - i_rect.mHeight / 2.0f) * (yDist - i_rect.mHeight / 2.0f);

    return (distSqrd <= i_circleRadius * i_circleRadius);
}

template <class T>
bool RectLineSegmentIntersection(const Sexy::TRect<T> &i_rect, const Sexy::SexyVector2 &i_lineStartPosition, const Sexy::SexyVector2 &i_lineEndPosition)
{
    int rectMaxX = i_rect.mX + i_rect.mWidth;
	int rectMaxY = i_rect.mY + i_rect.mHeight;
	
    // Find min and max X for the segment
    double minX = i_lineStartPosition.x;
    double maxX = i_lineEndPosition.x;
	
    if (i_lineStartPosition.x > i_lineEndPosition.x)
    {
		minX = i_lineEndPosition.x;
		maxX = i_lineStartPosition.x;
    }
	
    // Find the intersection of the segment's and rectangle's x-projections
    if (maxX > rectMaxX)
    {
		maxX = rectMaxX;
    }
	
    if (minX < i_rect.mX)
    {
		minX = i_rect.mX;
    }
	
	// If their projections do not intersect return false
    if (minX > maxX)
    {
		return false;
    }
	
    // Find corresponding min and max Y for min and max X we found before
    double minY = i_lineStartPosition.y;
    double maxY = i_lineEndPosition.y;
	
    double dx = i_lineEndPosition.x - i_lineStartPosition.x;
	
    if (abs(dx) > 0.0000001)
    {
		double a = (i_lineEndPosition.y - i_lineStartPosition.y) / dx;
		double b = i_lineStartPosition.y - a * i_lineStartPosition.x;
		minY = a * minX + b;
		maxY = a * maxX + b;
    }
	
    if (minY > maxY)
    {
		double tmp = maxY;
		maxY = minY;
		minY = tmp;
    }
	
    // Find the intersection of the segment's and rectangle's y-projections
    if (maxY > rectMaxY)
    {
		maxY = rectMaxY;
    }
	
    if (minY < i_rect.mY)
    {
		minY = i_rect.mY;
    }
	
	// If Y-projections do not intersect return false
    if (minY > maxY)
    {
		return false;
    }
	
    return true;
}

float WedgeProduct(const SexyVector2 &i_lhs, const SexyVector2 &i_rhs);
bool LineLineIntersect(const SexyVector2 &i_aPoint, const SexyVector2 &i_aDir, const SexyVector2 &i_bPoint, const SexyVector2 &i_bDir, float *o_aCoefficient, float *o_bCoefficient, float i_parallelEpsilon = 1e-4f);

inline std::vector<std::string> SplitString( std::string i_str, const char i_delm )
{
    std::string parsedstr;
    std::stringstream stream( i_str );
    std::vector<std::string> retArgs;
    
    while( getline( stream, parsedstr, i_delm ) )
    {
        retArgs.push_back( parsedstr );
    }
    
    return retArgs;
}

struct ValueRange
{
	float Min;
	float Max;
	
	ValueRange() 
	{
		Min = 0.0f;
		Max = 0.0f;
	}
	
	ValueRange(float i_min, float i_max)
	{
		SetRange(i_min, i_max);
	}
	
	void SetConstant(float i_val)
	{
		SetRange(i_val, i_val);
	}
	
	void SetRange(float i_min, float i_max)
	{
		Min = i_min;
		Max = i_max;
	}
	
	// Returns a random value in the range [min, max)
	float GetRandomValue() const
	{
		float a = Sexy::Rand(1.0f);
		float range = Max - Min;
		float result = Min + range * a;
		return result;
	}
	
	float GetRandomValue(class Sexy::MTRand* i_rand) const
	{
		float a = i_rand->Next(1.0f);//Sexy::Rand(1.0f);
		float range = Max - Min;
		float result = Min + range * a;
		return result;
	}

	float GetInterpValue(float i_interpolator, CurveType i_curve) const
	{
		return CurveEvaluate(i_interpolator, Min, Max, i_curve);
	}
	float GetTimeForValue(float i_value) const
	{
		return (i_value - Min) / (Max - Min);
	}
};



#endif
