//
//  SlidingWidget.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SlidingWidget__
#define __PlantsVersusZombies2__SlidingWidget__

#include "UIWidget.h"
#include "Curve.h"

class SlidingWidget : public UIWidget
{
public:
	RT_CLASS_DEFINE(SlidingWidget, UIWidget, RtClass);	

	enum SlidingState
	{
		STATE_INVALID,
		SELF_STATE_IDLE,
		STATE_SLIDING_IN,
		STATE_SLIDING_OUT,
		STATE_OFFSCREEN,
	};
	
	SlidingWidget();
	virtual ~SlidingWidget();
	
	// Public Interface (Core)
	
	void					SlideIn();
	void					SlideOut();
	void					SetupSlideInfo(const pvztime_t i_duration, const SexyVector2& i_offscreenPosition,
										   const std::string i_audioOnSlideIn = "", const std::string i_audioOnSlideOut = "",
										   const CurveType i_slideInCurve = CURVE_EASE_OUT, const CurveType i_slideOutCurve = CURVE_EASE_IN);
	inline const bool		IsSliding() const;
	
protected:	

	// Protected Interface (Inheritable)

	virtual void			onUpdate() override;
	virtual void			onVisibleStateChange(bool i_visible) override;
	virtual void			onSlideInFinished() {};
	virtual void			onSlideOutFinished() {};
	
private:	

	// Private Interface
	
	// Private member (serialized)
	
	pvztime_t				m_slideTimeStart;
	pvztime_t				m_slideTimeDuration;
	SlidingState			m_slidingState;
	CurveType				m_slideInCurve;
	CurveType				m_slideOutCurve;
	SexyVector2				m_originalPosition;
	SexyVector2				m_offscreenPosition;
	std::string				m_audioOnSlideIn;
	std::string				m_audioOnSlideOut;
	bool					m_slideEnabled;
};

inline const bool SlidingWidget::IsSliding() const
{
	return (m_slidingState == STATE_SLIDING_IN || m_slidingState == STATE_SLIDING_OUT);
}

#endif /* defined(__PlantsVersusZombies2__SlidingWidget__) */
