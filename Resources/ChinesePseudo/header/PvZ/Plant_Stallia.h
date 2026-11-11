#ifndef __PLANT_STALLIA_H__
#define __PLANT_STALLIA_H__

#include <string>

#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ZombieEnums.h"

/*
==============================================================
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class PlantStallia : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantStallia, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

	bool HasShadow() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool IsInvincible() const override;
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	bool TryBlockZombossRush(Zombie* i_zomboss) override;
	bool TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

private:
	DamageInfo	createDamage(bool i_isPlantFood);
	void		explodeNormal();

	bool		m_exploded = false;
	ZombiePtr	m_forceTargetZombie;
};

class StalliaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(StalliaProps, PlantPropertySheet, RtClass);
	
	StalliaProps()
	{
		StallDuration = 10;
		PlantfoodStallDuration = 15;
        StunDuration = 3.f;
	}
	
	float StallDuration;
	float PlantfoodStallDuration;
    float StunDuration;
};

//
//  Anim rig
//

class PlantAnimRig_Stallia : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Stallia, PlantAnimRig, RtClass);
	
	bool PlayIdleLooped() override;
	
private:
	std::string getIdleAnimationName() override { return "idle"; }
	std::string getDamageIdleAnimationName() override { return "damage"; }
	
	void onFirstIdleCompleted(const std::string &i_animName);
	
	bool m_hasPlayedFirstIdle = false;
};

#endif //__PLANT_STALLIA_H__
