//
//  PlantAnimRig_CoconutCannon.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_CoconutCannon_h
#define PlantsVersusZombies2_PlantAnimRig_CoconutCannon_h

#include "Precompile.h"
#include "PlantAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_CoconutCannon : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_CoconutCannon, PlantAnimRig, RtClass);
	
	/// Overrides
	
	virtual bool PlayIdleLooped() override;
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	virtual bool PlayPlantFoodEnd() override;
	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;

	/// Custom functionality
	
	bool PlayRecoverLooped();
	bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

private:
	std::string m_lastUsedIdleAnim;
};

#endif
