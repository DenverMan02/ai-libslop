//
//  PlantAnimRig_Puffshroom.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 4/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Puffshroom__
#define __PlantsVersusZombies2__PlantAnimRig_Puffshroom__

#include "PlantAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_Puffshroom : public PlantAnimRig
{
public:
	static int NUMBER_OF_DECAY_STAGES;
	
	RT_CLASS_DEFINE(PlantAnimRig_Puffshroom, PlantAnimRig, RtClass);
	
	PlantAnimRig_Puffshroom();

	bool PlayInitialFrame() override;
	bool PlayIdleLooped() override;
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
    bool Vanish(PopAnimRig::AnimStoppedReflectionDelegate i_onVanished = PopAnimRig::AnimStoppedReflectionDelegate());
    std::string GetPriviewAnim();

	void SetLevel(int level);
	
private:
	int m_level;
	AnimHandle m_attackHandle;
	PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Puffshroom__) */
