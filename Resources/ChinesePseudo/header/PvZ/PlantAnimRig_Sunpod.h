//
//  PlantAnimRig_Sunpod.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/17/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Sunpod__
#define __PlantsVersusZombies2__PlantAnimRig_Sunpod__

#include "PlantAnimRig.h"
#include "PopAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_Sunpod : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Sunpod, PlantAnimRig, RtClass);
	
	PlantAnimRig_Sunpod();
	
	bool PlayIdleLooped() override;
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	
	void SetLevel(int level);
	
private:
	int m_level;
	AnimHandle m_attackHandle;
	PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Sunpod__) */
