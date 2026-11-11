//
//  Plant_Pineapple.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-7-30.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantPineapple_h
#define PlantsVersusZombies2_PlantPineapple_h

#include "PlantFramework.h"
#include "Projectile.h"

enum PINEAPPLEANIMSTATE
{
    PINEAPPLE_SLEEP_READY = PLANTANIM_USERDEFINED + 1,
    PINEAPPLE_SLEEP_LOOP,
    PINEAPPLE_SLEEP_END,
    PINEAPPLE_FIRE_READY,
    PINEAPPLE_FIRE_LOOP,
    PINEAPPLE_FIRE_END
};

struct PineappleProjectileTimer
{
    
public:
    
    PineappleProjectileTimer() {}
    
    PineappleProjectileTimer(ProjectilePtr ptr, pvztime_t t)
    : PineappleProjectile(ptr), ReturnTime(t) {}
    
    ProjectilePtr PineappleProjectile;
    
    pvztime_t ReturnTime;
    
};

class PlantPineapple : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPineapple, PlantFramework, RtClass);
    
    PlantPineapple() {}
    
    virtual ~PlantPineapple() {}
    
    const class PineapplePropertySheet* GetMyProps();
    
    void ClearStore();

protected:
    
	void Initialize() override;
    
	void ApplyPlantfood() override;
    
    bool CanEndPlantfood() override;
    
    bool CanApplyPlantfood() override;
    
    void CancelPlantfood() override;
    
    void UpdateActions() override;
    
    void UpdatePlantfood() override;
    
    bool OverrideProjectileCollision(Projectile* pProjectile) override;
    
    void DoEventCall(RealObject* pTarget) override;
    
private:
    
    bool CanIntercept(Projectile* pProjectile);
    
    bool InInterceptVector(Projectile* pProjectile);
    
    void StoreProjectile(Projectile* pProjectile);
    
    void PlantFoodStoreProjectile(Projectile* pProjectile, int iIndex);
    
    void LaunchProjectile(ProjectilePtr ptrProjectile);
    
    void CollectProjectile();
    
    bool CheckInTimer(ProjectilePtr ptrProjectile);
    
    bool IsSleeping();
    
    bool IsAttacking();
    
    void LaunchAvatarProjectile(ProjectilePtr ptrProjectile);
    
    void SetNewProjectileProp(ProjectilePtr ptrProjectile);
    
private:
    
    std::vector<PineappleProjectileTimer> m_vProjectileStore;
    std::vector<ProjectilePropertySheetPtr> m_InterceptProjectiles;
    
};


class PineapplePropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(PineapplePropertySheet, PlantPropertySheet, RtClass);
    
    PineapplePropertySheet()
    : LaunchDelay(0.5f)
    , NormalTime(3.0f)
    , SleepTime(5.0f) {}
    
    pvztime_t LaunchDelay;
    
    pvztime_t NormalTime;
    
    pvztime_t SleepTime;
    
    std::vector<ProjectilePropertySheetPtr> InterceptVector;
};


class PlantAnimRig_Pineapple : public PlantAnimRig
{
public:
    
    RT_CLASS_DEFINE(PlantAnimRig_Pineapple, PlantAnimRig, RtClass);
    
    PlantAnimRig_Pineapple() : m_iTimeFlag(PVZ_EOT()), m_nextSound(PVZ_EOT()) {}
    
    bool PlayAttackBegin();
    
    void SetObject(RtWeakPtr<RealObject> ptr) { m_ptrObject = ptr; }
    
    bool IsAttacking();
    
    bool IsSleeping();
    bool playPlantFoodMain() override;
protected:
    
    std::string getIdleAnimationName() override;
    
    void onAnimStopped() override;
    
    void onUpdate() override;
    
private:
    
    bool PlayOnceCommon(PINEAPPLEANIMSTATE pstate, const std::string& strLabel);
    
    void PlayLoopCommon(PINEAPPLEANIMSTATE pstate, const std::string& strLabel);
    
    bool PlaySleepBegin();
    
    void PlaySleepLoop();
    
    bool PlaySleepEnd();
    
    void PlayAttackLoop();
    
    bool PlayAttackEnd();
    
    pvztime_t GetNormalDamgeTime();
    
    pvztime_t GetSleepTime();
    
private:
    
    RtWeakPtr<RealObject> m_ptrObject;
    
    pvztime_t m_iTimeFlag;
    pvztime_t m_nextSound;
    
};

#endif
