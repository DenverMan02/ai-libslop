//
//  Plant_Dusklobber.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 12/14/15.
//  Copyright © 2015 PopCap Games. All rights reserved.
//

#ifndef Plant_Dusklobber_h
#define Plant_Dusklobber_h

#include <stdio.h>

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "AnimRigLayerSet.h"
#include "GridItemAnimation.h"

enum DuskLobber_plantWeapon
{
	plantWeapon_LevelTwo = 3,
	plantWeapon_LevelTwoStun
};

class DusklobberProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(DusklobberProps, PlantPropertySheet, RtClass);
	
	DusklobberProps()
	{
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
		PlantfoodProjectilesToFire = 4;
	}
	
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
	int PlantfoodProjectilesToFire;
};

class PlantDusklobber : public PlantFramework
{
public:
	static const std::string k_boostedOffLayerSetName;
	static const std::string k_boostedOnLayerSetName;
	
public:
	RT_CLASS_DEFINE(PlantDusklobber, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	bool CanApplyPlantfood() override;
	void DoSpecial(int i_extraParam = 0) override;
	//Projectile*	Fire(Zombie* i_targetZombie, PlantWeapon i_plantWeapon) override;
	Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void CancelPlantfood() override;
	void ApplyPlantfood() override;
	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	bool isStunByPossibility();
protected:
	BoardEntityPtr getTargetInRow(int rowOffset);
	void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	std::multimap<int, Point> getPFTargetLocs();
	Point getNextPFTarget(std::multimap<int, Point> i_targetLocs);
private:
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
	void launchSpecialAvatarProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
	bool isBoosted();
	void updateRigLayers();
	
	int m_timesSpecialFired;
	float m_extraRate;
};

class PlantAnimRig_Dusklobber : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Dusklobber, PlantAnimRig, RtClass);
	
	PlantAnimRig_Dusklobber();
	
	bool PlayIdleLooped() override { return playIdleAnimation(); }
	
	void AddBoostedLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowBoostedLayerSet(std::string setName);
	
	bool PlayZenGardenIdleAnim() override;
	bool PlayPreviewAnim(bool bHideLayer = false) override;

protected:
	void onPopAnimInitialized() override;
	
private:
	bool playIdleAnimation();
	
	std::string m_lastPlayedIdleAnim;
	AnimRigLayerSet m_boostedLayerSet;
	
private:
};

enum GridItemDusklobberFlowerState
{
	PVZ_BEGIN_ENUM(DUSKLOBBERFLOWERSTATE_),
	DUSKLOBBERFLOWERSTATE_UNKNOWN,
	DUSKLOBBERFLOWERSTATE_DORMANT,
	DUSKLOBBERFLOWERSTATE_PROJECTILE_ASCENDING,
	DUSKLOBBERFLOWERSTATE_PROJECTILE_DESCENDING,
	DUSKLOBBERFLOWERSTATE_GROW,
	DUSKLOBBERFLOWERSTATE_EXPLODE,
	DUSKLOBBERFLOWERSTATE_SHRAPNEL,
	DUSKLOBBERFLOWERSTATE_DEAD,
	PVZ_END_ENUM(DUSKLOBBERFLOWERSTATE_)
};

class GridItemDusklobberFlower : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemDusklobberFlower, GridItemAnimation, RtClass);
	
	GridItemDusklobberFlower()
	: m_state(DUSKLOBBERFLOWERSTATE_UNKNOWN)
	{ JoinTeam(TEAM_PLANTS); }
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	
	int	CalcRenderOrder() const override;
	void StartGrowing();
	void SetSplashDamageProps(float i_splashDamage, float i_splashRadius);
	void SetShrapnelProps(float i_shrapnelRadius, float i_shrapnelDamage);
	void SetPauseBeforeStartFlower(pvztime_t i_pause);
	
	void setPlantWeapon(PlantWeapon i_plantWeapon);
	PlantWeapon getPlantWeapon() const;

	void setIsAvatarEnable(bool isEnable);
	bool getIsAvatarEnable() const;
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
	GridItemDusklobberFlowerState getState() { return m_state; }
	void setState(GridItemDusklobberFlowerState i_state);
	void launchDescendingProjectile();
	void launchDescendingAvatarProjectile();
	
	void doDamage(int i_damage, float i_radius);
	void radiateSplashDamage();
	void doShrapnelDamage();
	
	void onGrowFinished(const std::string &i_animName);
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
	void launchProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	
private:
	GridItemDusklobberFlowerState m_state;
	pvztime_t m_pauseBeforeStartFlower;

	bool shouldStun(BoardEntity* i_impactedEntity);
	void stunZombie(BoardEntity* i_impactedEntity);
	
	// props gotten from pfProjectile and DusklobberProps
	// note that we could just put these in flower props instead
	float m_splashDamage;
	float m_splashRadius;
	
	float m_shrapnelDamage;
	float m_shrapnelRadius;
	bool m_bIsAvatarEnable;
	PlantWeapon m_plantWeapon;
	float m_stunnedRate = 1.0f;
};

class GridItemDusklobberFlowerProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemDusklobberFlowerProps, GridItemAnimationProps, RtClass);
	GridItemDusklobberFlowerProps()
	: Lifetime(5.0)
	, BombProjectile("DusklobberPlantfoodSecondary"),
	  AvatarBombProjectile("DusklobberPlantfoodAvatar")
	{}
	
	pvztime_t Lifetime;
	std::string BombProjectile;
	std::string AvatarBombProjectile;
};

enum SeedState
{
    PVZ_BEGIN_ENUM(SEEDSTATE_),
    SEEDSTATE_UNKNOWN,
    SEEDSTATE_BIRTH,
    SEEDSTATE_IDLE,
    SEEDSTATE_ATTACK,
    SEEDSTATE_BINDED,
    SEEDSTATE_BINDED_DEATH,
    PVZ_END_ENUM(SEEDSTATE_)
};

class GridItemDuskSeed : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemDuskSeed, GridItemAnimation, RtClass);

	GridItemDuskSeed()
	: m_state(SEEDSTATE_UNKNOWN)
	{}

	void setState(SeedState i_state);
	SeedState getState();
	void updateState();
	int	CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onKilled() override;
	virtual void onTakeDamage(const DamageInfo& i_damage) override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

private:
	ZombiePtr m_bindedZombie;
	SeedState m_state;
	int m_damageStates;
	int m_currDamageState;
	void onBirthAnimDone(const std::string& i_animLabelName);
	void onAttackAnimDone(const std::string& i_animLabelName);
	void tryFindZombie();
	void setBindZombie(ZombiePtr i_zombie) { m_bindedZombie = i_zombie; }
	void bindZombie();
	void unbindZombie();
	void onZombieDeath(Zombie* zombie, const DamageInfo* i_deathBlow);
	bool IsInState(uint32 state) const { return m_state == state; }
	int calcDamageState();
	int CalcDamageStateCount();
};

class GridItemDuskSeedAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemDuskSeedAnimRig, PopAnimRig, RtClass) {}

    GridItemDuskSeedAnimRig();

    void PlayIdle(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayBinded();
    int CalcDamageStateCount();
};

class DusklobberProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(DusklobberProjectile, Projectile, RtClass);
	DusklobberProjectile() : m_plantLevel(0), m_bIsStun(false){}
	int GetPlantLevel() const;
	void SetPlantLevel(int m_plantLevel);
	void setIsStun(bool stun);
	bool getIsStun() const;
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool shouldStun(BoardEntity* i_impactedEntity);
	void stunZombie(BoardEntity* i_impactedEntity);
	int m_plantLevel;
	bool m_bIsStun;
};

class DusklobberSuperProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(DusklobberSuperProjectile, Projectile, RtClass) {}

private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void MarkCenterTarget(BoardEntity* i_entity);
	void DoSplashDamage(int i_sourceCol, int i_sourceRow);
};

class DusklobberSuperProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(DusklobberSuperProjectileProps, ProjectilePropertySheet, RtClass);

	DusklobberSuperProjectileProps()
	{
		ImpactDamage = 300.0f;
		SeedRate = 1.0f;
	};

	float ImpactDamage;
	float SeedRate;
};

class DusklobberPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(DusklobberPlantfoodProjectile, Projectile, RtClass);
	
	GridItemDusklobberFlower *GetFlower();
	void SetFlower(GridItemDusklobberFlower *flower);

protected:
	void onUpdate(pvztime_t i_dt) override;
	
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	
	RtWeakPtr<GridItemDusklobberFlower> m_flower;
};

class DusklobberPlantfoodProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(DusklobberPlantfoodProjectileProps, ProjectilePropertySheet, RtClass);
	
	DusklobberPlantfoodProjectileProps()
	{
		SplashRadius = 2.07;
		SplashDamage = 300;
		
		ShrapnelRadius = 2.0;
		ShrapnelDamage = 50;
		
		PauseBeforeStartingFlower = 1.0;

	};
	
	float ShrapnelDamage;
	float ShrapnelRadius;
	
	float SplashRadius;
	float SplashDamage;
	
	pvztime_t PauseBeforeStartingFlower;
};

class DusklobberPlantfoodProjectileBomb : public Projectile
{
public:
	RT_CLASS_DEFINE(DusklobberPlantfoodProjectileBomb, Projectile, RtClass);
	
	GridItemDusklobberFlower *GetFlower();
	void SetFlower(GridItemDusklobberFlower *flower);
	
protected:
	void onProjectileInitialized() override;
	
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	
	RtWeakPtr<GridItemDusklobberFlower> m_flower;
};

class DusklobberPlantfoodProjectileAvatar : public Projectile
{
public:
	RT_CLASS_DEFINE(DusklobberPlantfoodProjectileAvatar, Projectile, RtClass);

	GridItemDusklobberFlower *GetFlower();
	void SetFlower(GridItemDusklobberFlower *flower);
protected:
	void onProjectileInitialized() override;
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	RtWeakPtr<GridItemDusklobberFlower> m_flower;
};


#endif /* Plant_Dusklobber_h */
