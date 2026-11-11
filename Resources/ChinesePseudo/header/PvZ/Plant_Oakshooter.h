//
//  Plant_Oakshooter.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-8-21.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Oakshooter__
#define __PlantsVersusZombies2__Plant_Oakshooter__

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"

class OakProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(OakProjectile, Projectile, RtClass);
    
    OakProjectile()
    {
        b_Hitted = false;
    }
    
    bool OnCollideEntity(BoardEntity* i_entity) override;
    void OnHeadShot(BoardEntity* i_entity) override;

protected:
    
    void onDestroy() override;
    
private:
    bool b_Hitted;
};

class OakProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(OakProps, PlantPropertySheet, RtClass);

	OakProps()
	{
		SuperAttackRate = 1.0f;
	}

	float SuperAttackRate;
};

class PlantOakshooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantOakshooter, PlantFramework, RtClass);
    
    PlantOakshooter();
    virtual ~PlantOakshooter();
    
    void UpdateActions() override;
    
    void Initialize() override;
    
    bool			CanApplyPlantfood() override;
	void			ApplyPlantfood() override;
	void			CancelPlantfood() override;
    
    Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool            OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void            RegisterOakTrainModule();
    
    bool            CanTouchShoot();
    
    void            ChangeArrowType(const int i_type);
    void            SetShootTime(pvztime_t    i_time);
    void            Idle() override;
protected:
    
    void            onOakShootTouch(const Sexy::Point& i_atLocation);
    void            onOakArrowHitted(const int i_target_type, const int i_count);
    
private:
    Projectile*		FireSpecial();
	Projectile* 	FireProjectile(int i_actionIndex, int i_index, ProjectilePropertySheetPtr i_projectileType, int i_pierceCount = 0);
    Projectile* 	FireProjectileSpecial(int i_actionIndex, int i_index, ProjectilePropertySheetPtr i_projectileType, float i_initialDegree);
    //ZombiePtr       FindClosetZombie(PlantWeapon i_plantWeapon);
    
    ZombiePtr       FindClosetZombie(PlantWeapon i_plantWeapon);
    
    void            ManualFire();
    bool 			TriggerSuperAttack();
    
private:
    
    OakshooterPlantfood m_plantfood;
    
    Point               m_manualShootLocation;
    
    bool                m_bCanShoot;
    pvztime_t           m_shootInterval;
    pvztime_t           m_shoot_time;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Oakshooter__) */
