//
//  PlantAnimRig_Peapod.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_PEAPOD_H__
#define __PLANTANIMRIG_PEAPOD_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Peapod : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Peapod, PlantAnimRig, RtClass);
	
	PlantAnimRig_Peapod();

	virtual bool PlayIdleLooped() override;
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;

	void SetLevel(int level);

private:
	int m_level;
	AnimHandle m_attackHandle;
	PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

#endif // __PLANTANIMRIG_PEAPOD_H__
