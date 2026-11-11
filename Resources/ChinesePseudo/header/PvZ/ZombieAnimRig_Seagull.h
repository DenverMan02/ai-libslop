//
//  ZombieAnimRig_Seagull.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Seagull_h
#define PlantsVersusZombies2_ZombieAnimRig_Seagull_h

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Seagull : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Seagull, ZombieAnimRig, RtClass);

	void HideBird();

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual void onNeedsToDie() override;
};

#endif
