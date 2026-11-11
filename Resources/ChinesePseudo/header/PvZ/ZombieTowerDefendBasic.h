//
//  ZombieTowerDefendBasic.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-12.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieTowerDefendBasic__
#define __PlantsVersusZombies2__ZombieTowerDefendBasic__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"

STATE_ENUM_CHILD_BEGIN(ZombieTowerDefendBasicState, ZombieState)
    ZS_TOWERDEFENDBASIC_TowerDefendUp,
    ZS_TOWERDEFENDBASIC_TowerDefendDown,
    ZS_TOWERDEFENDBASIC_TowerDefendLeft,
    ZS_TOWERDEFENDBASIC_TowerDefendRight,
STATE_ENUM_END(ZombieTowerDefendBasicState)

class ZombieTowerDefendBasic : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieTowerDefendBasic, Zombie, RtClass);
    
    void SetWalkUpValue(bool bWalkUp, pvztime_t tWalkUpTime, float iAppendPercent);
    
    bool CanBeMowed() const override
    {
        return false;
	}
    
	bool CanBeBlovered() const override
    {
        return false;
	}
    
    bool CanBeFlickedOff() const override
	{
        return false;
	}
    
    bool CanBeStabbed() const override
    {
        return false;
    }
    
    bool CanBePoisoned() const override
    {
        return false;
    }
    
protected:
	virtual void onZombieInitialize() override;
    virtual void onUpdate() override;
    virtual void onPlaceOnBoard() override;
    
    virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
    
    virtual bool NotifyCanTakeSkill(ZombieState i_toState);
    
    virtual float GetTrackOffset() const;

    OVERRIDE_STATE_UPDATE(ZombieState,   Walk);
    OVERRIDE_STATE_ONENTER(ZombieState,  BleedingOut);
    
	DECLARE_STATE_FUNCTIONS(ZombieState, TowerDefendUp);
	DECLARE_STATE_FUNCTIONS(ZombieState, TowerDefendDown);
	DECLARE_STATE_FUNCTIONS(ZombieState, TowerDefendLeft);
    DECLARE_STATE_FUNCTIONS(ZombieState, TowerDefendRight);
    
private:
    
    bool CheckTurnToDirection();
    bool CheckIsTurnToUp();
    bool CheckIsTurnToDown();
    bool CheckIsTurnToLeft();
    bool CheckIsTurnToRight();
    
private:
    
    float m_LastPos;
    
    pvztime_t m_tWalkUpTime;
    bool      m_bIsWalkUp;
    
    int       m_helmDamageIndex;
};

#endif /* defined(__PlantsVersusZombies2__ZombieTowerDefendBasic__) */
