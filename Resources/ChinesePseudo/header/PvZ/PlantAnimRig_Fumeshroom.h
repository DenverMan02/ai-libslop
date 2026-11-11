//
//  PlantAnimRig_Fumeshroom.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/23/2014
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Fumeshroom__
#define __PlantsVersusZombies2__PlantAnimRig_Fumeshroom__

#include "PlantAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_Fumeshroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Fumeshroom, PlantAnimRig, RtClass);
	
	PlantAnimRig_Fumeshroom();

	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;

	virtual bool playPlantFoodMain() override;
    
private:
	AnimHandle m_attackHandle;
	PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
    
protected:
	virtual void onPopAnimInitialized() override;
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Fumeshroom__) */
