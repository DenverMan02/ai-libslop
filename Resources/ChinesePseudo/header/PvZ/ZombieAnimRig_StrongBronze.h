//
//  ZombieAnimRig_StrongBronze.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-30.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_StrongBronze__
#define __PlantsVersusZombies2__ZombieAnimRig_StrongBronze__

#include "ZombieAnimRig.h"

class ZombieAnimRig_StrongBronze : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_StrongBronze, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_StrongBronze();
    
    bool becomeCrazy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool recover(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayDebut(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	//virtual const std::vector<std::string>& getArmLayerNames();
	//virtual const std::vector<std::string>& getArmReplacementPairNames();
    
    bool m_bCrazy;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_StrongBronze__) */
