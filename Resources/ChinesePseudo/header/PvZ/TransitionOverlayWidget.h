//
//  TransitionOverlayWidget.h
//  PlantsVersusZombies2
//
//  Created by jsola on 7/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TransitionOverlayWidget_h
#define PlantsVersusZombies2_TransitionOverlayWidget_h

#include "core.h"

enum TransitionStyle
{
	PVZ_BEGIN_ENUM(TRANSITION_),
	TRANSITION_NONE,
	TRANSITION_FADE_OUT,
	TRANSITION_FADE_IN,
	PVZ_END_ENUM(TRANSITION_)
};

enum FadeTransitionType
{
	PVZ_BEGIN_ENUM(TRANSITION_TYPE_),
	TRANSITION_TYPE_COLOR,
	TRANSITION_TYPE_SPIRAL,
	TRANSITION_TYPE_GRASS,
	PVZ_END_ENUM(TRANSITION_TYPE_)
};

class TransitionOverlayWidget : public Widget
{
	
public:
	TransitionOverlayWidget();
	
	// Public access
	void				QueueScreenFadeOut(FadeTransitionType i_type, Color i_color, pvztime_t i_duration, bool i_deactivateOnCompletion);
	void				QueueScreenFadeIn(FadeTransitionType i_type, Color i_color, pvztime_t i_duration, bool i_deactivateOnCompletion);
	
    void                WillStopTransition();
	void				StartTransition();
	void				StopTransition();
	
	// Pauses (or un-pauses the transition) at its currently time setting
	void				SetPaused(bool i_paused);
	
	bool				IsTransitionComplete();
	
	// Inherited interface
	virtual void		Draw(Graphics* i_g);
	virtual void		Update();
	
	void				SetRenderActive(bool i_active) { m_renderActive = i_active; }

private:
	void				drawFullscreenOverlay(Graphics* i_g, Color i_color);
	void				drawSpiralOverlay(Graphics* i_g, Color i_color);
	void				drawGrassOverlay(Graphics* i_g, Color i_color);

	TransitionStyle		m_style;
	FadeTransitionType	m_type;
	pvztime_t			m_screenFadeDuration;
	Color				m_color;
	
	pvztime_t			m_duration;
	pvztime_t			m_startTime;
	
	pvztime_t			m_elapsedTimeWhenPaused;
	
	bool				m_active;
	bool				m_deactivateOnCompletion;
	bool				m_renderActive;
};

#endif
