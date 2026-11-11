//
//  DamageLifetime.h
//  PlantsVersusZombies2
//
//  Created by JEmery on 11/17/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

//
//  Data-Driving Damage States
//
//  Defines a sequence of damage phases that allow an object
//  to transition to different visual and other states as it
//  is damaged.
//
//  Future:
//	If we needed to add timelines or other non-instant features
//  to the system this should generate an Action which can be
//  attached to the object.  This is, assuming, we formalize
//	an action system for all types.
//

#ifndef PlantsVersusZombies2_DamageLifetime_h
#define PlantsVersusZombies2_DamageLifetime_h

#include "Precompile.h"

struct DamagePhase : public Sexy::RtObject
{
	RT_CLASS_DEFINE(DamagePhase, RtObject, RtClass);
	
	virtual ~DamagePhase()
	{}
	
	float StartAtHealthPercent;
	
	std::string Animation;
	std::vector<std::string> Layers;
};

class DamageLifetime : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(DamageLifetime, RtObject, RtClass);
	
	virtual ~DamageLifetime()
	{}
	
public:
	std::vector<DamagePhase> Phases;

	int OnHealthChanged(float i_health, float i_healthMax, class PopAnimRig* i_animRig, int i_lastPhase) const;
	
	// Update anim rig outside of health change event
	void SetAnimRigToPhase(int i_phase, PopAnimRig* i_animRig) const;

private:
	int getDamagePhase(float i_health, float i_healthMax) const;
	void switchToPhase(int i_phase, PopAnimRig* i_animRig) const;
	
};

#endif
