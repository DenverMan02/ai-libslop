//
//  Plant_BashoPult.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-5-25.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_BashoPult__
#define __PlantsVersusZombies2__Plant_BashoPult__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "Projectile.h"
#include "Plant_TangleKelp.h"

class BashoPultProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(BashoPultProjectileProps, ProjectilePropertySheet, RtClass);
    
    BashoPultProjectileProps();
    
    float CatchBallDistance;
    float ProjectileLobHeight;
    pvztime_t ProjectileTimeOfFlight;
};

class BashoPultProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BashoPultProjectile, Projectile, RtClass);
    
    bool OnCollideGround() override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    void SetReturnPosition(const SexyVector3& pos);
    void SetRepulseZombie(bool repulse);
protected:
    void onUpdate(pvztime_t i_dt) override;
protected:
    void onInitialized() override;
    void onDeflection(class BoardEntity* i_deflector) override;
private:
    void Return();
private:
    bool m_deflected;
    bool m_collideEntity;
    bool m_repulseZombie;
    SexyVector3 m_returnPos;
    ZombieRepulseSystem m_repulseSystem;
};

class BashoPultProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(BashoPultProps, PlantPropertySheet, RtClass);
    
    BashoPultProps();

    std::vector<float> AdvancedProjectileProbability;
};

class PlantBashoPult : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantBashoPult, PlantFramework, RtClass);
    bool	 CanApplyPlantfood() override;
    bool	 FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool OverrideProjectileCollision(class Projectile* i_projectile) override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void	 UpdateActions() override;
private:
    bool TriggerAdvancedAttack();
    void SetReturnToSelf(BashoPultProjectile* projectile);
    void SetReturnRandomly(BashoPultProjectile* projectile);
    BashoPultProjectile* FireProjectile(int actionIndex);
private:
    ProjectilePtr m_ball;
};

class PlantAnimRig_BashoPult : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_BashoPult, PlantAnimRig, RtClass);
    bool PlayAdvancedAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayCatchBallLooped();
};

#endif /* defined(__PlantsVersusZombies2__Plant_BashoPult__) */
