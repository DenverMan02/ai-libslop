//
//  Plant_Stunion.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 1/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PLANT_STUNION_H__
#define __PLANT_STUNION_H__

#include <string>

#include "DamageInfo.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ZombieEnums.h"
#include "Projectile.h"

class PlantStunion : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantStunion, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;

	bool IsInvincible() const override;
    virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	void DoSpecial(int i_extraParam) override;

	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	bool HasShadow() override;

private:
	void doPlantfoodEffect();
	void spawnGasProjectile(int i_column, int i_row);
    pvztime_t GetStunTimeAddedByLevel();
	bool m_hasShadow = true;
};

class PlantAnimRig_Stunion : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Stunion, PlantAnimRig, RtClass);
    void SetAdvanced(bool advanced) { m_advanced = advanced; }
    PlantAnimRig_Stunion();
protected:
    virtual std::string getAttackAnimationName() override;
    virtual std::string getPlantFoodOnAnimName() override;
    virtual std::string getPlantFoodMainAnimName() override;
private:
    bool m_advanced;
};

class StunionProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(StunionProps, PlantPropertySheet, RtClass);

    StunionProps()
    {
    	PlantfoodProjectileDistance = 4;
    }

    float PlantfoodProjectileDistance;
	SexyVector2 StaticGasCloudPAMOffset;
    std::vector<pvztime_t> StunTimeAddedByLevel;
};

class StunionGasProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(StunionGasProjectile, Projectile, RtClass);
	StunionGasProjectile();

	void SetTravelDistance(float i_distanceInGridSquares);
	void SetStunDuration(pvztime_t i_duration);

private:
	bool handleImpact(BoardEntity* i_entity) override;
	void onUpdate(pvztime_t i_dt) override;
	void onPostUpdate() override;

	float m_endPosition;
	pvztime_t m_stunDuration;
	std::vector<BoardEntityPtr> m_hitEntities;
};

class EffectAnimRig_StunionProjectile : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_StunionProjectile, PopAnimRig, RtClass);
	EffectAnimRig_StunionProjectile();

	void PlayIntro();
	void NotifyTimeRemaining(pvztime_t i_time);
    void SetAdvanced(bool advanced);
    void SetAvatar(bool avatar);
private:
    std::string GetAttackName();
	pvztime_t m_endingAnimationLength;
    bool m_advanced;
    bool m_avatar;
};

#endif

