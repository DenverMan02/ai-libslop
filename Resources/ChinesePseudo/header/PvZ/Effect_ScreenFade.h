//
//  Effect_ScreenFade.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_ScreenFade_h
#define PlantsVersusZombies2_Effect_ScreenFade_h

#include "StandaloneEffect.h"
#include "Curve.h"

enum ScreenFadeDirection
{
	FadeIn,
	FadeOut,
	FadeConstant
};

struct SingleScreenFade
{
	SingleScreenFade() : Duration(0.f), Direction(FadeIn), Curve(CURVE_LINEAR), ValueStart(0.0f), ValueEnd(1.0f)
	{
        
    }
	
	ScreenFadeDirection 	Direction;
	Color					FadeColor;
	pvztime_t				Duration;
	CurveType				Curve;
    float                   ValueStart;
    float                   ValueEnd;
};


class Effect_ScreenFade : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_ScreenFade, StandaloneEffect, RtClass);
	
	static Effect_ScreenFade* Create();
	static Effect_ScreenFade* Create(ScreenFadeDirection i_dir, Color i_color, pvztime_t i_duration, CurveType i_curveType = CURVE_LINEAR);
	static Effect_ScreenFade* Create(Color i_fadeColor, pvztime_t i_fadeOutTime, pvztime_t i_fadeInTime, CurveType i_curveType = CURVE_LINEAR);
	
	void AddFade(ScreenFadeDirection i_dir,
                 Color i_color,
                 pvztime_t i_duration,
                 CurveType i_curveType = CURVE_LINEAR,
                 float i_value_start = 0.0f,
                 float i_value_end   = 1.0f);
    
protected:
	virtual void onInitialized() override;
	virtual void onUpdate() override;
	virtual void onDraw(Graphics* i_g) override;
	
private:
	void advanceSequence();
	Color calcColor(ScreenFadeDirection i_direction,
                    Color i_fadeColor,
                    CurveType i_curve,
                    pvztime_t i_duration,
                    pvztime_t i_currTime,
                    float i_value_start,
                    float i_value_end);
	
	std::vector<SingleScreenFade> m_screenFadeSequence;
	int m_currentFade = 0;
	pvztime_t m_currentFadeTimer = 0.f;
};

#endif
