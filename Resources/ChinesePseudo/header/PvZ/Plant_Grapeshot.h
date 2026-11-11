//
//  Plant_Grapeshot.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 9/10/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Grapeshot__
#define __PlantsVersusZombies2__Plant_Grapeshot__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"
#include "ZombieEnums.h"

class PlantGrapeshot : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantGrapeshot, PlantFramework, RtClass) {}
    
    void	Initialize() override;
    void	UpdateActions() override;
    
    void	Explode();
    void	SpawnProjectiles();
    void    AddMucus();
    CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    
    bool CanBeShoveled()		override { return false; }
    bool CanBeTargeted()		override { return false; }
    bool IsInvincible() const	override { return true; }
    void TakeSmashAttack(ZombiePtr i_srcZombie) override {}
    
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
};

class GrapeshotProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(GrapeshotProjectileProps, ProjectilePropertySheet, RtClass);
    
    GrapeshotProjectileProps()
    {
        BounceAngleInRadians = SexyMath::DegToRad(45.0f);
        BounceOutwardTendency = 0.5f;
        BouncesUntilSelfDestruct = 5;
        Bounces4SecondLevel = 6;
        Bounces4ThirdLevel = 7;
        EndingPAM = "POPANIM_EFFECTS_GRAPESHOT_HIT";
    }
    
    float BounceAngleInRadians;
    float BounceOutwardTendency;
    int BouncesUntilSelfDestruct;
    int Bounces4SecondLevel;
    int Bounces4ThirdLevel;
    std::string EndingPAM;
};

class GrapeshotProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(GrapeshotProjectile, Projectile, RtClass);
    
    GrapeshotProjectile()
    {
        m_lastRowHit = -1.0f;
        m_numberOfTimesBounced = 0;
    }
    bool OnCollideRoof() override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool ShouldClipWithWater() const override { return true; }
    void SetProjectileAnimation();
    
protected:
    void moveThroughTime(pvztime_t i_dt) override;
    
private:
    float	determineBounceDirection(float i_upChance);
    bool	handleBounceAndReportConsumption();
    void	showHitExplosion(float explosionX, float explosionY);
    
    int m_lastRowHit;
    int m_numberOfTimesBounced;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Grapeshot__) */
