//
//  ZombieToygun.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef ZombieToygun_h
#define ZombieToygun_h

#include "Zombie.h"
#include "ZombieAnimRig_PirateCaptain.h"

class ZombieAnimRig_Toygun : public ZombieAnimRig_PirateCaptain
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Toygun, ZombieAnimRig_PirateCaptain, RtClass);
    
    typedef RtReflectionDelegate<Delegate0> PowerAnimDoneReflectionDelegate;
    typedef RtReflectionDelegate<Delegate0> ShootAirbubbleReflectionDelegate;
    
    bool PlayPowerAnim(PowerAnimDoneReflectionDelegate i_onAnimDone, ShootAirbubbleReflectionDelegate i_airbubble);
    
protected:
    virtual void onAnimStopped() override;
    
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    
    virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
protected:
    PowerAnimDoneReflectionDelegate m_onAnimDone;
    ShootAirbubbleReflectionDelegate m_airbubble;
};

class ZombieToygun : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieToygun, Zombie, RtClass);
    
//    void OnParrotReturned();
    bool HasBird() { return m_airbubbleLaunching; }
    void OnAirbubbleLaunched();
    
    void startSpawnAnim();
    void onShoot();
    void onSpawnAnimDone();
    
protected:
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    virtual void onLostHead() override;
    virtual void onTakeFatalDamage(const DamageInfo& i_lastReceivedDamage) override;
    void onApplyCondition(ZombieConditions i_condition) override;
    
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Attack);
    
private:
    void checkForAirbubbleRelease();
    void TakeShoot(class Plant* i_targetPlant);
    class Plant* findPlantForAirbubbleToAttack();
    
private:
    bool        m_airbubbleLaunching;
    
    float       m_airbubbleHealth;
    pvztime_t   m_airbubbleLaunchTime;
    PlantPtr    m_target;
    ZombiePtr   m_airbubblePtr;
};

#endif /* ZombieToygun_h */
