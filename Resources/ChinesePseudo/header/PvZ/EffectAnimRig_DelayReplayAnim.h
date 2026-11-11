//
//  EffectAnimRig_DelayReplayAnim.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_DelayReplayAnim__
#define __PlantsVersusZombies2__EffectAnimRig_DelayReplayAnim__

#include "PopAnimRig.h"

class EffectAnimRig_DelayReplayAnim : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_DelayReplayAnim, PopAnimRig, RtClass);
	
    EffectAnimRig_DelayReplayAnim();

	void PlayAnimation(std::string i_animName);
	void SetReplayTime(const pvztime_t i_timeMin, const pvztime_t i_timeMax)
	{
		m_timeMin = i_timeMin;
		m_timeMax = i_timeMax;
	};

	void GetReplayTime(pvztime_t& o_timeMin, pvztime_t& o_timeMax)
	{
		o_timeMin = m_timeMin;
		o_timeMax = m_timeMax;
	};
	
protected:

	virtual void onUpdate() override;
    
private:

	void		onAnimationFinished(const std::string& i_animName);

    pvztime_t	m_timeMin;
	pvztime_t	m_timeMax;
	pvztime_t	m_timeTillNextPlay;
	std::string	m_animName;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_DelayReplayAnim__) */
