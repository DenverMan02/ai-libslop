//
//  PlantAnimRig_Zoomshroom.h
//  PlantsVersusZombies2
//
//  Created by Albert Lai on 10/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Zoomshroom_h
#define PlantsVersusZombies2_PlantAnimRig_Zoomshroom_h

#include <string>
#include <vector>

#include "PlantAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_Zoomshroom : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Zoomshroom, PlantAnimRig, RtClass);
	
	void SetRemainingLifePercentage(float remainingTime);
	
private:
	const std::vector<std::string>& getOnLayerNames();
	const std::vector<std::string>& getOffLayerNames();
	void updateLayerVisibility();
	
	float m_elapsedLifePercentage;
};

#endif
