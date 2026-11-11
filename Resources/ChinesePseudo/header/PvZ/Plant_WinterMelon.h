//
//  Plant_WinterMelon.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_WinterMelon_h
#define PlantsVersusZombies2_Plant_WinterMelon_h

#include "Plant_Melonpult.h"
#include "Projectile.h"

class PlantWinterMelon : public PlantMelonpult
{
public:
	RT_CLASS_DEFINE(PlantWinterMelon, PlantMelonpult, RtClass);

	PlantWinterMelon();
	virtual void Initialize() override;

	virtual void DoSpecial(int i_extraParam) override;
	virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	// No additional functionality is needed for the WinterMelon.
	// This stub class is mostly around for inspection / debugging and resource group
	// definition purposes.
	
    void LaunchProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, PlantWeapon i_plantWeapon);
    
protected:
	virtual void playFireSound() override;
	virtual void playPlantfoodLaunchSound() override;
private:
	void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);
	bool m_level5;
	float BoostFreezeValue;
};

class PlantAnimRig_WinterMelon : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_WinterMelon, PlantAnimRig, RtClass);
	PlantAnimRig_WinterMelon();

	void SetAttackAnim(const std::string& label);
private:
	std::string getAttackAnimationName() override;
private:
	std::string m_defaultAttack;
};

class WinterMelonProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(WinterMelonProjectile, Projectile, RtClass);

	WinterMelonProjectile();

	void SetBoostFreezeValue(float i_val);

protected:
	virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
private:
	float BoostFreezeValue;
};

class WinterMelonLevel5Projectile : Projectile
{
public:
	RT_CLASS_DEFINE(WinterMelonLevel5Projectile, Projectile, RtClass);
	
	WinterMelonLevel5Projectile();

	bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
	float _chillDuration;
};

#endif
