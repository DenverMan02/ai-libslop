//
//  ZombieEightiesBass.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/8/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef ZombieEightiesBass_h
#define ZombieEightiesBass_h

#include "ZombieEnums.h"
#include "Zombie.h"
#include "GridItem.h"

STATE_ENUM_CHILD_BEGIN(ZombieBassState, ZombieState)
ZS_Bass_Falling,
ZS_Bass_Dancing,
ZS_Bass_WreckingBass,
STATE_ENUM_END(ZombieBassState)

class ZombieEightiesBassProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieEightiesBassProps, ZombiePropertySheet, RtClass);
    
    SexyVector2 ShockWaveSpawnOffset;
    float ShockWaveSpawnInterval = 5.f;
    
};

class ZombieEightiesBass : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieEightiesBass, Zombie, RtClass);
    
    void onZombieInitialize() override;
    void onPlaceOnBoard() override;
    void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    void doFallFromSky(const SexyVector3& i_destination);
    
protected:
    DECLARE_STATE_FUNCTIONS(ZombieState, Falling);
    DECLARE_STATE_FUNCTIONS(ZombieState, Dancing);
    DECLARE_STATE_FUNCTIONS(ZombieState, WreckingBass);
    
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onAnimStopped(const std::string& i_animLabel);
    
    
private:
    void createShockWave();
    SexyVector2 calcShockWaveSpawnPosition();
    
    GridItemPtr m_speaker;
    pvztime_t m_shockWaveTimer = PVZ_EOT();
};

class ZombieAnimRig_EightiesBass : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_EightiesBass, ZombieAnimRig, RtClass);
    ZombieAnimRig_EightiesBass()
    {
        m_hasBass = true;
    }

    void PlayFalling(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayDancing(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
    void PlayWreckAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void SetBassStatus(bool i_hasBass) { m_hasBass = i_hasBass; }
    
protected:
    const std::string getDieAnimationName() override;
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
    
private:
    bool m_hasBass;
};


#endif /* ZombieEightiesBass_h */
