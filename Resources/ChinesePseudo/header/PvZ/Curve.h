//
//  Curve.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 5/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Curve_h
#define PlantsVersusZombies2_Curve_h

#include "SexyMath.h"
#include "TodCommon.h"
#include "TodDebug.h"
#include <cmath>

#include <utility>

//
// Various interpolators. 
//
enum CurveType
{
	CURVE_CONSTANT,
	CURVE_LINEAR,
	CURVE_EASE_IN,
	CURVE_EASE_OUT,
	CURVE_EASE_IN_OUT,
	CURVE_EASE_IN_OUT_WEAK,
	CURVE_FAST_IN_OUT,
	CURVE_FAST_IN_OUT_WEAK,
	CURVE_BOUNCE,
	CURVE_BOUNCE_FAST_MIDDLE,
	CURVE_BOUNCE_SLOW_MIDDLE,
	CURVE_TOSS,
	CURVE_SIN_WAVE,
	CURVE_EASE_SIN_WAVE,
	CURVE_SIN_WAVE_NORMALIZED,
};

// Bicubic bit of a curve. 
float CurveS(float i_time);
float CurveQuad(float i_time);
float CurveInvQuad(float i_time);
float CurveQuadS(float i_time);
float CurveInvQuadS(float i_time);
float CurveCubic(float i_time);
float CurveInvCubic(float i_time);
float CurveCubicS(float i_time);
float CurvePoly(float i_time, float i_poly);
float CurveInvPoly(float i_time, float i_poly);
float CurvePolyS(float i_time, float i_poly);
float CurveCircle(float i_time);
float CurveInvCircle(float i_time);
float CurveBounce(float i_time);
float CurveToss(float i_time);

float warpTimeForCurve(float i_time, CurveType i_curve);

template<typename T>
static T curveEvaluate(float i_time, const T& i_positionStart, const T& i_positionEnd, CurveType i_curve)
{
	float warpedTime = warpTimeForCurve(i_time, i_curve);
	return Sexy::SexyMath::Lerp<T>(i_positionStart, i_positionEnd, warpedTime);
}

template<typename T>
T CurveEvaluateClamped(float i_time, const T& i_positionStart, const T& i_positionEnd,  CurveType i_curve)
{
	if (i_time <= 0.0f)
	{
		return i_positionStart;
	}
	else if (i_time >= 1.0f)
	{
		if (i_curve == CURVE_BOUNCE ||
			i_curve == CURVE_BOUNCE_SLOW_MIDDLE ||
			i_curve == CURVE_BOUNCE_FAST_MIDDLE ||
			i_curve == CURVE_SIN_WAVE ||
			i_curve == CURVE_EASE_SIN_WAVE ||
			i_curve == CURVE_SIN_WAVE_NORMALIZED)
		{
			return i_positionStart;
		}
		else
		{
			return i_positionEnd;
		}
	}
	else
	{
		return curveEvaluate<T>(i_time, i_positionStart, i_positionEnd, i_curve);
	}
}


// 
// we want our public interface to clamp. 
//
template<typename T>
T CurveEvaluate(float i_time, const T& i_valueStart, const T& i_valueEnd, CurveType i_curveType)
{
    return CurveEvaluateClamped<T>(i_time, i_valueStart, i_valueEnd, i_curveType);
}

template<typename T>
T CurveLerp(float i_paramStart, float i_paramEnd, float i_param, const T& i_valueStart, const T& i_valueEnd, CurveType i_curve)
{
    DBG_ASSERT(i_paramStart <= i_paramEnd);
	const float elapsed = i_param - i_paramStart;
	const float range   = i_paramEnd - i_paramStart;
    float param = 1.0f;
    
    if (!Sexy::IsNearZero(range))
    {
        param = elapsed / range;   
    }
    
	return CurveEvaluateClamped<T>(param, i_valueStart, i_valueEnd, i_curve);
}

template <typename T>
struct Curve
{
	Curve();
	Curve(float i_paramStart, float i_paramEnd, T i_valueStart, T i_valueEnd, CurveType i_type);
	
	T GetAt(float i_param) const;
	T operator[](float i_param) const;
	
	float ParamStart;
	float ParamEnd;
	T ValueStart;
	T ValueEnd;
	CurveType Type;
};

template<typename T>
Curve<T>::Curve()
{}
template<typename T>
Curve<T>::Curve(float i_paramStart, float i_paramEnd, T i_valueStart, T i_valueEnd, CurveType i_type)
	: ParamStart{i_paramStart}, ParamEnd{i_paramEnd}, ValueStart{i_valueStart}, ValueEnd{i_valueEnd}, Type{i_type}
{}

template<typename T>
T Curve<T>::GetAt(float i_param) const
{
	return CurveLerp<T>(ParamStart, ParamEnd, i_param, ValueStart, ValueEnd, Type);
}
template<typename T>
T Curve<T>::operator[](float i_param) const
{
	return GetAt(i_param);
}

typedef Curve<float> FloatCurve;
typedef Curve<int> IntCurve;

// This is a dummy class to ensure that these values are exposed to the serialization system
class CurveReflectionExposer : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(CurveReflectionExposer, Sexy::RtObject, Sexy::RtClass);
};


template <typename T>
class CurveEvaluator
{
public:
	CurveEvaluator(const float i_paramLength,
				   const T& i_valueStart,
				   const T& i_valueEnd,
				   const CurveType i_curve);
	
	CurveEvaluator(const float i_paramLength,
				   T&& i_valueStart,
				   T&& i_valueEnd,
				   const CurveType i_curve);
				
	CurveEvaluator(const Curve<T>& i_curve);
	
	// Users should call one of these two functions before evaluating
	void SetParamBegin(const float i_param);
	void SetParamEnd(const float i_param);
	float GetParamLength() const;
	
	// Specify the value to blend towards. Must be one of the two values that were passed
	// to the constructor
	void SetValueGoal(const T& i_goal, const float i_param);
	
	// ReverseDirection: swaps valueStart & valueEnd leaving i_param
	void ReverseDirection(const float i_param);
	
	T operator()(const float i_param) const;
	
private:
	Curve<T> m_curve;
};

template <typename T>
CurveEvaluator<T>::CurveEvaluator(const float i_paramLength,
								  const T& i_valueStart,
								  const T& i_valueEnd,
								  const CurveType i_curve)
	: m_curve{0.f, i_paramLength, i_valueStart, i_valueEnd, i_curve}
{
}

template <typename T>
CurveEvaluator<T>::CurveEvaluator(const float i_paramLength,
								  T&& i_valueStart,
								  T&& i_valueEnd,
								  const CurveType i_curve)
	: m_curve{0.f, i_paramLength, std::forward<T>(i_valueStart), std::forward<T>(i_valueEnd), i_curve}
{
}

template <typename T>
void CurveEvaluator<T>::SetParamBegin(const float i_param)
{
	const float length = GetParamLength();
	m_curve.ParamStart = i_param;
	m_curve.ParamEnd = i_param + length;
}

template <typename T>
void CurveEvaluator<T>::SetParamEnd(const float i_param)
{
	const float length = GetParamLength();
	m_curve.ParamStart = i_param - length;
	m_curve.ParamEnd = i_param;
}

template <typename T>
float CurveEvaluator<T>::GetParamLength() const
{
	return m_curve.ParamEnd - m_curve.ParamStart;
}

template <typename T>
void CurveEvaluator<T>::SetValueGoal(const T& i_goal, const float i_param)
{
	DBG_ASSERT_MSG((i_goal == m_curve.ValueStart) || (i_goal == m_curve.ValueEnd),
				   "Invalid value passed to CurveEvaluator::SetValueGoal!"
				   "Must be one of the values passed to the object's constructor");
	if (i_goal != m_curve.ValueEnd)
	{
		ReverseDirection(i_param);
	}
}

template <typename T>
void CurveEvaluator<T>::ReverseDirection(const float i_param)
{
	const auto elapsed = i_param - m_curve.ParamStart;
	const auto length = GetParamLength();
	float percentComplete = 1.0f;
    if (!Sexy::IsNearZero(length))
    {
        percentComplete = elapsed / length;
    }
	percentComplete = 1.0f - max(0.0f, min(1.0f, percentComplete));
	
	m_curve.ParamStart = i_param - percentComplete * length;
	m_curve.ParamEnd = m_curve.ParamStart + length;
	
	T tmp{std::move(m_curve.ValueStart)};
	m_curve.ValueStart = std::move(m_curve.ValueEnd);
	m_curve.ValueEnd = std::move(tmp);
}

template <typename T>
T CurveEvaluator<T>::operator()(const float i_param) const
{
	return m_curve[i_param];
}

#endif
