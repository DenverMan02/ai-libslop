//
//  ZombieChicken.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_CHICKEN_H__
#define __ZOMBIE_CHICKEN_H__

#include "Zombie.h"

class ZombieChicken : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieChicken, Zombie, RtClass);

    virtual void CreateZombieLevelEffect(bool i_street) override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

	virtual std::string getElectrocutePAMName() const override;
    virtual float GetAmberScale() override;
protected:
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
	virtual void onTurnedToAsh() override;
    virtual void playBirdLossAnimation(bool i_shockBird);
    void onElectrocuted() override;
    bool willDieToShrinking() override { return true; }
};

class ZombieWeasel : public ZombieChicken
{
public:
    RT_CLASS_DEFINE(ZombieWeasel, ZombieChicken, RtClass);
    
protected:
    void playBirdLossAnimation(bool i_shockBird) override;
    void onTurnedToAsh() override;
    void onElectrocuted() override;

protected:
    std::string GetElectrocutName();
};

class ZombieWeaselElite : public ZombieWeasel
{
public:
    RT_CLASS_DEFINE(ZombieWeaselElite, ZombieWeasel, RtClass);

protected:
    bool willDieToShrinking() override { return false; }
};


class ZombieChickenProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieChickenProps, ZombiePropertySheet, RtClass);
    
    ZombieChickenProps()
    {
        BucketPercentage = 0.50f;
        AffectedBySliders = true;
    }
    
    float BucketPercentage;
    std::string ElectrocutePAMName;
    bool AffectedBySliders;
};

#endif
