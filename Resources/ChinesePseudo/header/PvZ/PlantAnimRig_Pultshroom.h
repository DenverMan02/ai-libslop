//
//  PlantAnimRig_Pultshroom.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 9/24/2013.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_PULTSHROOM_H__
#define __PLANTANIMRIG_PULTSHROOM_H__

#include <string>
#include <vector>

#include "PlantAnimRig.h"
#include "PlatformAutodetect.h"
#include "PopAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_Pultshroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Pultshroom, PlantAnimRig, RtClass);
	
	PlantAnimRig_Pultshroom();
	
	virtual bool PlayInitialFrame() override;
	virtual bool PlayIdleLooped() override;
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;

	void SetLevel(int level);

private:
	const std::vector<std::string>& getArmLayerNames();
	void updateLayerVisibility();
	
	int32 m_level;
	AnimHandle m_attackHandle;
	PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

#endif // __PLANTANIMRIG_PULTSHROOM_H__
