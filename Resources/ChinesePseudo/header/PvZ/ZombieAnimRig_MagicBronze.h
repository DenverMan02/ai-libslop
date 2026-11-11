//
//  ZombieAnimRig_MagicBronze.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_MagicBronze__
#define __PlantsVersusZombies2__ZombieAnimRig_MagicBronze__

#include "Precompile.h"
#include "ZombieAnimRig_Qigong.h"

class ZombieAnimRig_MagicBronze : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_MagicBronze, ZombieAnimRig, RtClass);

	bool PlaySummon(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayPull(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayDebut(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
    pvztime_t GetPullDuration();
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_MagicBronze__) */
