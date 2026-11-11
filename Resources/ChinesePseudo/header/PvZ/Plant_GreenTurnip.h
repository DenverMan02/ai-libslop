//
//  Plant_GreenTurnip.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-9-14.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_GreenTurnip__
#define __PlantsVersusZombies2__Plant_GreenTurnip__

#include "PlantFramework.h"
#include "Projectile.h"

class GreenTurnipProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(GreenTurnipProjectile, Projectile, RtClass);
    void					SetInitialLaunchValues(float i_height, float i_timeToTarget, int i_row);
    void                SetBounceCount(int count);
    GreenTurnipProjectile();
protected:
    void					onProjectileInitialized() override;
    bool                handleImpact(BoardEntity* i_impactedEntity) override;
private:
    void                PlayBounceHitEffect();
    BoardEntity*			findNextTarget();
    BoardEntity*			findNearestTargetType(BoardEntityTypeFlag i_flag);
    
    float					m_initialLobHeightThisBounce;
    float					m_initialTimeOfFlightThisBounce;
    float					m_targetingRadius;
    int						m_rowBeingFiredAt;
    int                     m_bounceCount;
    std::vector<BoardEntityPtr>	m_targetsAlreadyHit;
};

class GreenTurnipProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(GreenTurnipProjectileProps, ProjectilePropertySheet, RtClass);
    
    GreenTurnipProjectileProps()
    {
        ProjectileRetargetingRadius = 200.0f;
        PropertyReductionMultiplierPerBounce = 0.75;
    }

    float ProjectileRetargetingRadius;
    float PropertyReductionMultiplierPerBounce;
    std::string ImpactBrouceAnimationToPlay;
    std::string BounceSound;
};

class GreenTurnipPlantfoodProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(GreenTurnipPlantfoodProjectile, Projectile, RtClass);

    GreenTurnipPlantfoodProjectile();
    void SetAvatar(bool avatar);
protected:
    void radiateSplashDamage(BoardEntity* i_impactedEntity) override;
    void moveThroughTime(pvztime_t i_dt) override;
    void PlayExplodeEffect();
    virtual bool OnCollideRoof() override;
private:
    bool m_avatar;
    bool m_explode;
};

class GreenTurnipProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(GreenTurnipProps, PlantPropertySheet, RtClass);
    
    GreenTurnipProps()
    {
        RecoverTime = 0;
        ProjectileTimeOfFlight = 1.2f;
        ProjectileLobHeight = 350.f;
    }
    
    float RecoverTime;
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    std::vector<int> ProjectileBounceCount;
};

class PlantGreenTurnip : public PlantFramework
{
public:
    static const int MaxProjectileCount = 3;
public:
    RT_CLASS_DEFINE(PlantGreenTurnip, PlantFramework, RtClass);
    
    bool CanApplyPlantfood() override;
    void CancelPlantfood() override;
    void DoSpecial(int i_extraParam ) override;
    void UpdateActions() override;
    void ApplyPlantfood() override;
    void onAnimStoppedCallback(const std::string& i_animCommand) override;
    void Idle() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool	 CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    PlantGreenTurnip();
protected:
    void LaunchProjectileAt(GreenTurnipProjectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    void TakePlantfoodProjectileDropDamage();
private:
    int GetPlantAction(int projectileCount);
    int GetProjectileBounceCount();
    void SetProjectileCount(int count);
    void launchSpecialProjectile(SexyVector3 i_targetLoc, int i_row);
    void PlayImpactEffect(BoardEntity* target, const ProjectilePropertySheetPtr& props);
    Rect GetPlantfoodProjectileDropRect();
    BoardEntityPtr findBestTargetInRow(int i_row);
    BoardEntity* findLeftmostTargetType(BoardEntityTypeFlag i_flag, int i_row);
    PopAnimRig::AnimStoppedReflectionDelegate GetAnimationStopDelegate();

    int m_projectileLeft;
    pvztime_t m_recoverTime;
    std::vector<BoardEntityPtr> m_plantfoodHitTarget;
};

enum PlantAnimRigState_GreenTurnip
{
    PLANTANIM_GREENTURNIP_SLEEP = PLANTANIM_USERDEFINED,
    PLANTANIM_GREENTURNIP_RECOVER,
};

class PlantAnimRig_GreenTurnip : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_GreenTurnip, PlantAnimRig, RtClass);
    void SetProjectileCount( int count);
    void PlaySleep();
    void PLayRecover(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayIdleLooped() override;
    std::string GetRecoverLabel();
    PlantAnimRig_GreenTurnip();
protected:
    void onPopAnimInitialized() override;
    void onAnimStopped() override;
    void PlaySleepLooped();
    std::string getAttackAnimationName() override; 
private:
    std::string GetBeginSleepLabel();
private:
    int m_projectileCount;
};


#endif /* defined(__PlantsVersusZombies2__Plant_GreenTurnip__) */
