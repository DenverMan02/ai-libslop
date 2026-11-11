//
//  ZombieBeachShell.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-1-6.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieBeachShell__
#define __PlantsVersusZombies2__ZombieBeachShell__

#include <stdio.h>
#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieBeachShellState, ZombieState)
    ZS_BeachShell_LostShell,
    ZS_BeachShell_TransformPosture,
STATE_ENUM_END(ZombieBeachShellState)

class ZombieBeachShell : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieBeachShell, Zombie, RtClass);
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    virtual Sexy::Rect calcCollisionRect() override;
    virtual Sexy::Rect CalcZombieAttackRect() override;
protected:
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    virtual ZombieParticle* onHelmDropped(HelmType i_oldHelmType, int i_helmHitpoints) override;
    virtual void OnGroundEffectChange(GroundEffectType from, GroundEffectType to) override;
    virtual DamageTypeFlags getEatingDamageType() const override;
    virtual float GetBaseEatDPS() override;
    virtual bool canAttack() override;
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
    virtual std::vector<BoardEntityPtr> findAttackTargets() override;
private:
    DECLARE_STATE_FUNCTIONS(ZombieState, LostShell);
    DECLARE_STATE_FUNCTIONS(ZombieState, TransformPosture);
    void OnLostShellDone(const std::string& i_animLabel);
    void OnTransformPostureDone(const std::string& i_animLabel);
    bool HasShell() const;
};

class ZombieBeachShellProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieBeachShellProps, ZombiePropertySheet, RtClass);
    
    ZombieBeachShellProps()
    {
        SpeedLostShell = 0.75;
        EatDPSLostShell = 100;
        SizeTypeLostShell = ZOMBIE_SIZE_SMALL;
    }
    float SpeedLostShell;
    float EatDPSLostShell;
    Rect HitRectLostShell;
    Rect AttackRectLostShell;
    ZombieSizeType SizeTypeLostShell;
};

class ZombieAnimRig_BeachShell : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_BeachShell, ZombieAnimRig, RtClass);
    virtual bool PlayEat() override;
    bool PlayLostShell(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayGoAshore(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayEnterWater(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool HasShell();
    bool IsInWater() { return m_inWater; }
    void SetIsInWater(bool value) { m_inWater = value; }
    void SetShellDamageIndex(int index);
    ZombieAnimRig_BeachShell();
protected:
    virtual void onPopAnimInitialized() override;
    virtual const std::string getIdleAnimationName() override;
	virtual const std::string getEatAnimationName() override;
    virtual const std::string getWalkAnimationName() override;
    virtual const std::string getStunAnimationName() override;
    virtual const std::string getAttackAnimationName() override;
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
private:
    void UpdateShellLayerVisibility();
    const std::vector<std::string>& GetShellLayerNames();
    int GetNoShellIndex();
private:
    bool m_inWater;
    int m_shellDamageIndex;
};

#endif /* defined(__PlantsVersusZombies2__ZombieBeachShell__) */
