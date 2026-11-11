//
//  EffectAnimRig_SpikeweedSaws.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/23/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __EFFECTANIMRIG_SPIKEWEEDSAW_H__
#define __EFFECTANIMRIG_SPIKEWEEDSAW_H__

#include "Precompile.h"
#include "PopAnimRig.h"

class EffectAnimRig_SpikeweedSaw : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_SpikeweedSaw, PopAnimRig, RtClass);
	
	bool PlayRise();
	bool PlayIdle();
	bool PlayDeath();
	
protected:
	enum SpikeweedSawState
	{
		SAW_RISING,
		SAW_IDLE,
		SAW_DYING,
		SAW_DEAD
	};
	
	virtual void onPopAnimInitialized() override;
	virtual void onAnimStopped() override;
	
	SpikeweedSawState m_playState;
};

class EffectAnimRig_SpikeweedSpikes : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_SpikeweedSpikes, PopAnimRig, RtClass) {}
	
	bool PlayEffectLooped();
	bool PlayEffectAndStop(AnimStoppedReflectionDelegate i_onAnimStopped);
};

#endif // __EFFECTANIMRIG_SPIKEWEEDSAW_H__
