//
//  ZombieWolfImp.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-18.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieWolfImp__
#define __PlantsVersusZombies2__ZombieWolfImp__

#include "ZombieTowerDefendBasic.h"
#include "ZombieAnimRig.h"

class ZombieWolfImp : public ZombieTowerDefendBasic
{
public:
	RT_CLASS_DEFINE(ZombieWolfImp, ZombieTowerDefendBasic, RtClass);
    
    virtual float GetAmberScale() override;
};

/////

class ZombieAnimRig_WolfImp : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_WolfImp, ZombieAnimRig, RtClass);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    
};

#endif /* defined(__PlantsVersusZombies2__ZombieWolfImp__) */
