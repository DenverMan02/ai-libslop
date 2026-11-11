//
//  Plant_Melonpult.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Melonpult_h
#define PlantsVersusZombies2_Plant_Melonpult_h

#include "PlantFramework.h"

class PlantMelonpult : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMelonpult, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void DoSpecial(int i_extraParam) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;

protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, PlantWeapon i_plantWeapon);
	
	virtual void playFireSound();
	virtual void playPlantfoodLaunchSound();
    
    Projectile * normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    Projectile * avatarFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);

    void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);
	void BoostProjectile(Projectile* i_projectile);

protected:

	std::vector<BoardEntityPtr> m_targettedBoardEntities;
	int m_timesSpecialFired;
	bool m_level5;
	float m_newAvatarExtraRate1;
	float m_directDamageRate;
	float m_splashDamageRate;
};

class PlantAnimRig_Melonpult : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Melonpult, PlantAnimRig, RtClass);
	PlantAnimRig_Melonpult();

	void SetAttackAnim(const std::string& label);
private:
	std::string getAttackAnimationName() override;
private:
	std::string m_defaultAttack;
};

#endif
