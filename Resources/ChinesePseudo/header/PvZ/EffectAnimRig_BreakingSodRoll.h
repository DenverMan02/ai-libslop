//
//  EffectAnimRig_BreakingSodRoll.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 5/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_BreakingSodRoll__
#define __PlantsVersusZombies2__EffectAnimRig_BreakingSodRoll__

#include "PopAnimRig.h"
#include "WorldMap.h"

class EffectAnimRig_BreakingSodRoll : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_BreakingSodRoll, PopAnimRig, RtClass);
	
    EffectAnimRig_BreakingSodRoll();
	
	virtual void onUpdate() override;
	
	void		PlayAnimation();
	void		SetSodLane(SodLane* i_sodLane)
	{
		m_sodLane = i_sodLane;
	};
	
	bool		IsActive() {return m_active;}
    
private:

	void		onAnimationFinished(const std::string& i_animName);
	
	void		startNextExplosion();
    
	SodLane*	m_sodLane;
	pvztime_t   m_startTime;
	pvztime_t	m_animLength;
	bool		m_kickedOffNext;
	bool		m_active;
	int			m_sodPiece;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_BreakingSodRoll__) */
