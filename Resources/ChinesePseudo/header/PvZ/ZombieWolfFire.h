//
//  ZombieWolfFire.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-18.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieWolfFire__
#define __PlantsVersusZombies2__ZombieWolfFire__

#include "ZombieTowerDefendBasic.h"
#include "ZombieAnimRig.h"

class ZombieWolfFire : public ZombieTowerDefendBasic
{
public:
	RT_CLASS_DEFINE(ZombieWolfFire, ZombieTowerDefendBasic, RtClass);
    
    Sexy::Rect CalcZombieAttackRect() override;
    
    void onApplyCondition(ZombieConditions i_condition) override;
    
protected:
    void onZombieInitialize() override;
	void onLostHead() override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    
    void onUpdate() override;
    
	void burnPlant(class Plant* targetPlant);
    void setIsTorchBurning(bool i_isBurning);
};

/////

class ZombieAnimRig_WolfFire : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_WolfFire, ZombieAnimRig, RtClass);
    
    void SetTorchLayers(const bool i_visible);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    
};

#endif /* defined(__PlantsVersusZombies2__ZombieWolfFire__) */
