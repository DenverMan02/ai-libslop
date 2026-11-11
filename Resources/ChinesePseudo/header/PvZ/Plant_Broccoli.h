//
//  Plant_Broccoli.h
//  PlantsVersusZombies2
//
//  Created by mao xingxing 10/21/2014.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_BROCCOLI_H__
#define __PLANT_BROCCOLI_H__

#include "PlantFramework.h"

enum BroccoliState
{
	BROCCOLI_STATE_IDLE = STATE_FRAMEWORK_BEGIN,
    BROCCOLI_STATE_FIND_TARGET,
    BROCCOLI_STATE_PUSH_TARGET,
    BROCCOLI_STATE_PULL_FAIL,
    BROCCOLI_STATE_PULL_REST,
    BROCCOLI_STATE_PULL_TARGET,
	BROCCOLI_STATE_ATTACK,
    BROCCOLI_STATE_ATTACK_FINISH,
    BROCCOLI_STATE_ATTACK_THROW,
    BROCCOLI_STATE_REST,
	BROCCOLI_STATE_PLANTFOOD,
};

class PlantBroccoli : public PlantFramework
{
public:
    
    PlantBroccoli();
    virtual ~PlantBroccoli();
    
	RT_CLASS_DEFINE(PlantBroccoli, PlantFramework, RtClass);

	virtual void Initialize() override;
    virtual void onKilled(bool i_instantKill) override;
	virtual void UpdateActions() override;
//	virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon);
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual int CalcRenderOrder() override;
    virtual bool CanBeShoveled() override;
    bool HandleDamageStateChanged() override;
    void onAnimStoppedCallback(const std::string& i_animCommand) override;
    
protected:
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
private:
    void Idle() override;
    void Rest();
    void BeginPullTarget();
    void BeginPushTarget();
    void BeginPullFail();
    void EndPullFail();
    void EndPrimaryAttack(bool pullSuccess);
    void BeginThrowTargetBack();
    void ThrowTargetAway(ZombiePtr target);
    void PrimaryHit(bool bBackHit);
    void UpdateTargetPosition();
    void UpdateTargetPositionAndRotation();
    void UpdatePullTarget();
    void UpdatePullTargetFail();
    void UpdatePushTarget();
    void UpdateFindTarget();
    void UpdateHitTargetBack();
    void UpdateRest();
    void OnAttackAnimationHitBack();
    void OnAttackAnimationHitBackMiddle();
    void OnAttackAnimationHitFrontMiddle();
    void FixTarget(ZombiePtr target, bool bFix);
    void DamageTargetInRect(const Rect& rect, Zombie* ignoreTarget, const DamageInfo& damage);
    bool IsBetterTargetWithPrimaryWeapon(Zombie* one, Zombie* other);
    bool TargetIsControlledByOhter(ZombiePtr target);
    ZombiePtr GetBestTargetWithPrimaryWeapon();
    pvztime_t GetRestTime();
    int GetAttackCountBeforeRest();
    float GetAdvancedPrimaryAttackProbility(int level);
    
    void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
    
    //plantfood
    void SetZombieInPlantFoodControl(Zombie * i_zombie);
    void FindPlantFoodTarget();
    
    
private:
    
    bool m_targetFixedBySelf;
    int m_primaryAttackCount;
    pvztime_t m_restTime;
    Sexy::SexyVector3 m_startPosition;
    Sexy::SexyVector3 m_endPosition;
    int m_animationTotalFrame;
    pvztime_t m_elapsedTime;
    ZombiePtr m_targetZombie;
    ZombiePtr m_plantfoodTargetZombie;
    
    SexyVector3 m_attackStartPos;
    float m_startZombieRotation;
    float m_endZombieRotation;
    
    bool  m_takeAroundDamage;
};

#endif
