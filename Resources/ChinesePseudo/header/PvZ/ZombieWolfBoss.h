//
//  ZombieWolfBoss.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-19.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieWolfBoss__
#define __PlantsVersusZombies2__ZombieWolfBoss__

#include "ZombieTowerDefendBasic.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieWolfBossState, ZombieTowerDefendBasicState)
    ZS_WOLFBOSS_INTRO,
    ZS_WOLFBOSS_FIRE,
    ZS_WOLFBOSS_BLOW,
STATE_ENUM_END(ZombieWolfBossState)

class ZombieWolfBoss : public ZombieTowerDefendBasic
{
public:
	RT_CLASS_DEFINE(ZombieWolfBoss, ZombieTowerDefendBasic, RtClass);
    
    Sexy::Rect CalcZombieAttackRect() override;
    
protected:
    
    void onZombieInitialize() override;
    void onUpdate() override;
    
    bool NotifyCanTakeSkill(ZombieState i_toState) override;
    
    float GetTrackOffset() const override;
    
    DECLARE_STATE_FUNCTIONS(ZombieState, WolfBossIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, WolfBossFire);
	DECLARE_STATE_FUNCTIONS(ZombieState, WolfBossBlow);
    
private:
    
    void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;
    
    void onIntroCompleted(const std::string&);
    void onFireCompleted(const std::string&);
    void onBlowCompleted(const std::string&);
    
    void burnPlant(Plant * targetPlant);
    void blowPlant(Plant * i_plant);
    
private:
    
    pvztime_t   m_nextSkillTime;
    bool        m_canTakeSkill;
    ZombieState m_toState;
    
    std::vector<std::string> m_skills;
};

/////

enum ZombieAnimRigState_WolfBoss
{
	ZOMBIEANIM_WOLFBOSS_START = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_WOLFBOSS_INTRO,
	ZOMBIEANIM_WOLFBOSS_FIRE,
    ZOMBIEANIM_WOLFBOSS_BLOW
};

class ZombieAnimRig_WolfBoss : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_WolfBoss, ZombieAnimRig, RtClass);
    
    void PlayIntro(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayFire(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayBlow(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieWolfBoss__) */
