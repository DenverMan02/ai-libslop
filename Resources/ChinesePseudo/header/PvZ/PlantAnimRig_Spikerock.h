//
//  PlantAnimRig_Spikerock.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Spikerock_h
#define PlantsVersusZombies2_PlantAnimRig_Spikerock_h

#include "PlantAnimRig.h"

class PlantAnimRig_Spikerock : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Spikerock, PlantAnimRig, RtClass);
	
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	virtual bool PlayPlantFoodEnd() override;
	
	void SetLostHornCount(int i_newLostHorns);
	
protected:
	virtual void onPopAnimInitialized() override;
	
private:
	void setHornVisibility();
	
	int m_lostHorns = 0;
};

#endif
