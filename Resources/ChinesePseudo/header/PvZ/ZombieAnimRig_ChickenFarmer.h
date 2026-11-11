//
//  ZombieAnimRig_ChickenFarmer.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_CHICKEN_FARMER_H__
#define __ZOMBIEANIMRIG_CHICKEN_FARMER_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieChickenFarmer.h"

class ZombieAnimRig_ChickenFarmer : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ChickenFarmer, ZombieAnimRig, RtClass);

	ZombieAnimRig_ChickenFarmer();

	void SetHasChickens(bool i_hasChickens);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::string getWalkAnimationName() override;
    virtual const std::string getStunAnimationName() override;
    
    bool hasChickens() { return m_hasChickens; }

private:
	
	bool m_hasChickens;
};

class ZombieAnimRig_WeaselHoarder : public ZombieAnimRig_ChickenFarmer
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_WeaselHoarder, ZombieAnimRig_ChickenFarmer, RtClass);
    
    void PlayWeaselAttack(AnimStoppedDelegate i_onAnimStopped);
    void PlayWeaselAttackSpecial(AnimStoppedDelegate i_onAnimStopped);

    void SetZombie(RtWeakPtr<ZombieChickenFarmer> zombie);
    virtual bool PlayResilienceBreak(const std::string& i_animLabel, AnimStoppedReflectionDelegate i_onAnimStopped) override;
    virtual bool PlayResilienceStandstill(const std::string& i_animLabel) override;
    virtual bool PlayResilienceRecover(const std::string& i_animLabel, AnimStoppedReflectionDelegate i_onAnimStopped) override;
    
protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
    const std::string getWalkAnimationName() override;
    const std::string getIdleAnimationName() override;
    const std::string getEatAnimationName() override;
    void onChickeningEnd(const std::string&);

    RtWeakPtr<ZombieChickenFarmer> m_zombiePtr;
};

#endif
