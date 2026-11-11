//
//  EffectAnimRig_SodRoll.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/9/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_SodRoll__
#define __PlantsVersusZombies2__EffectAnimRig_SodRoll__

#include "PopAnimRig.h"
#include "WorldMap.h"

class EffectAnimRig_SodRoll : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_SodRoll, PopAnimRig, RtClass);
	
    EffectAnimRig_SodRoll();
	
	void		PlayAnimation();
	void		SetSodLane(SodLane* i_sodLane)
	{
		m_sodLane = i_sodLane;
	};
    
private:

	void		onAnimationFinished(const std::string& i_animName);
    
	SodLane*	m_sodLane;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_SodRoll__) */
