//
//  ZombiePvpWizard.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 10/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePvpWizard_h
#define PlantsVersusZombies2_ZombiePvpWizard_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "RestrictionSet.h"

class BoardEntity;
class Effect_PopAnim;
class Plant;

STATE_ENUM_CHILD_BEGIN(ZombieState_DarkWizard, ZombieState)
    ZS_DARKWIZARD_Casting,
    ZS_DARKWIZARD_BigCasting,
STATE_ENUM_END(ZombieState_DarkWizard)

class ZombiePvpWizardProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePvpWizardProps, ZombiePropertySheet, RtClass);
    
    ZombiePvpWizardProps()
    {
        SoundOnSpellActivate = "Play_RaZombie_WandActivate";
        SkillSpanTime = 0.0f;
    }
    std::string SheepPopAnim;
    Sexy::Point SheepOffset;
    
    std::string SoundOnSpellActivate;
    ValueRange TimeBeforeFirstCasting;
    ValueRange TimeBetweenCasting;
    std::string ProjectilePopAnim;
    
    PlantRestrictionSet TargetablePlantTypes;
    
    float   SkillSpanTime;
};

class ZombiePvpWizard : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombiePvpWizard, Zombie, RtClass);
    
    virtual void ApplyZombieFood() override;
    virtual void CancelZombieFood() override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, Casting);
    DECLARE_STATE_FUNCTIONS(ZombieState, BigCasting);

private:
    void onZombieInitialize() override;
    virtual void onUpdate() override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	void onMowedDown() override;
	void onDestroy() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	bool isValidSpellTarget(Plant* plant);
	Plant* getValidSpellTarget();
    void onAnimationDone(const std::string& i_animName);
	void onSpellImpact(BoardEntity* i_impactedEntity);

	pvztime_t m_nextCastTime = PVZ_EOT();
    float     m_skillTime = 0;
};

#endif
