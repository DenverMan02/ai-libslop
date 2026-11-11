//
//  Plant_BowlingBulb.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 6/17/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __Plant_BowlingBulb_H__
#define __Plant_BowlingBulb_H__

#include "PlantFramework.h"
#include "BoardEnums.h"
#include "Projectile.h"
#include "Loot.h"

enum BowlingBulbState
{
    BOWLING_BULB_STATE_RELOAD = STATE_FRAMEWORK_BEGIN,
    BOWLING_BULB_STATE_SUPER_SKILL,
    BOWLING_BULB_STATE_SUPER_SKILL_RELOAD,
};

enum BowlingBulbOwned
{
	BOWLING_BULB_NONE,
	BOWLING_BULB_PLAIN,
	BOWLING_BULB_SUPER,
};

class PlantBowlingBulb : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBowlingBulb, PlantFramework, RtClass);

	void Initialize() override;

	bool HasShadow() override { return true; }

    bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	void	UpdateActions() override;
    
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
	void	DoSpecial(int i_extraParam = 0) override;

    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void onAnimStoppedCallback(const std::string& i_animName) override;
	void setHasPlantfoodedBulbs(bool plantfooded);
	
	float GetLaunchDelayMultiplier() override;
	
	void		PlayAttackAnimation() override;
	bool		IsInvincible() const override;

private:

	std::vector<std::string> getLayerName(int i);
	
	void addACoconut();
	void updateCoconutLayers();
	int getCountCoconutsOwned();
	int pickBestCoconutToFire();
	int getCountCoconutsSuper() const;
	int pickEmptySlot();

	pvztime_t m_lastCoconutCreation = PVZ_EOT();
	
	std::vector<BowlingBulbOwned> m_coconutOwned;
	bool m_isSuperSkillFired;
	bool m_hasPlantfoodBulbs;
};

class BowlingBulbProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BowlingBulbProjectileProps, ProjectilePropertySheet, RtClass);
	
	BowlingBulbProjectileProps()
	{
		BounceAngleInRadians = SexyMath::DegToRad(45.0f);
		BounceOutwardTendency = 0.5f;
		HitsUntilFirstAward = INT_MAX;
		HitsUntilRepeatAward = INT_MAX;
		LootAwardOnHits = LOOT_None;
	}
	
	float BounceAngleInRadians;
	float BounceOutwardTendency;
	int HitsUntilFirstAward;
	int HitsUntilRepeatAward;
	Loot LootAwardOnHits;
};

class BowlingBulbSuperProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BowlingBulbSuperProjectileProps, ProjectilePropertySheet, RtClass);

	BowlingBulbSuperProjectileProps()
	{

	}

	std::vector<RtWeakPtr<ProjectilePropertySheet> > splitBullets;
};

class BowlingBulbProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BowlingBulbProjectile, Projectile, RtClass);

	BowlingBulbProjectile()
	{
		m_lastRowHit = -1.0f;
		m_enemyHitsUntilAward = INT_MAX;
		SetShouldKeepRoofZ(true);
	}
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool ShouldClipWithWater() const override { return true; }
	int  GetEnemyHitCount() { return m_enemyHitsUntilAward; }
protected:
	void moveThroughTime(pvztime_t i_dt) override;
	void onProjectileInitialized() override;
    void onSplashDamageHitEntity(class BoardEntity* i_hitEntity) override;
    void incrementZombieDeathCountAndCheckForAchievement();
	virtual void dropLoot(BoardEntity* i_impactedEntity);
	
private:
	float determineBounceDirection(float i_upChance);
	
	int m_lastRowHit;
	int m_enemyHitsUntilAward;
	int m_enemyKills;
};

class BowlingBulbSuperProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BowlingBulbSuperProjectile, Projectile, RtClass);

	BowlingBulbSuperProjectile(): m_bCollided(false)
	{
		SetShouldKeepRoofZ(true);
	}
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool ShouldClipWithWater() const override { return true; }

protected:
	void onSplitAnimaFinish();

	bool m_bCollided;
};

class PlantAnimRig_BowlingBulb : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_BowlingBulb, PlantAnimRig, RtClass);
	
	bool PlayBulbAttack(int bulbIndex, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayBulbRecharge(int bulbIndex, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayBulbSuperSkill(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayIdleLooped() override;
	
	bool m_plantfoodBulbs = false;
private:
	std::string getPlantFoodMainAnimName() override { return "plantfood_idle"; }
};

#endif // __Plant_BowlingBulb_H__
