//
//  Plant_MeteorFlower.h
//  PlantsVersusZombies2
//
//  Created by Sudheer, Alma on 08/04/22.
//  Copyright 漏 2022 PopCap Games. All rights reserved.
//

#ifndef Plant_MeteorFlower_h
#define Plant_MeteorFlower_h

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "ComponentWarmingRadius.h"
#include "Plant_LavaGuava.h"

enum MeteorFlowerState
{
    METEORFLOWER_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
    METEORFLOWER_STATE_PF_FIRING,
    METEORFLOWER_STATE_RECOVERING,
    METEORFLOWER_STATE_RECOVERING_END,
};

enum MeteorFlowerProjectileType
{
	MeteorFlowerProjectileType_Normal,
	MeteorFlowerProjectileType_Advanced,
	MeteorFlowerProjectileType_Super
};

struct PlanetMeteorInfo
{
	PlanetMeteorInfo(bool i_planetMeteor, const Point& i_location)
	: IsPlanetMeteor(i_planetMeteor)
	, Location(i_location)
	{

	}

	PlanetMeteorInfo()
	: IsPlanetMeteor(false)
	{

	}

	bool IsPlanetMeteor;
	Point Location;
};

class MeteorFlowerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(MeteorFlowerProps, PlantPropertySheet, RtClass);

    SexyVector2 TargetOffset;
    ComponentWarmingRadiusProps NormalWarmingRadius;
    ComponentWarmingRadiusProps PlantfoodWarmingRadius;
    ClassRestrictionSet ZombiesExcludeList;
    float TargetingDelay = 0.1f;
    float DelayBetweenShots = 2.5f;
    int MeteorStrikeCount = 2;
    int MeteorShowerCount = 5;
    float MoltenPoolDuration = 5.f;
    //int MoltenPoolDamage = 5;
    std::vector<int> MoltenPoolDamages;
    float ActionDamageRadius = 1.5f;
    float ActionDamagePFRadius = 2.f;
    int RepeatTargetedTileChance = 10;
    float Level2AttackRate;
    float ImprovedLevel2Rate;
    float Level5AttackRate;
    float Level5MinorAttackRate;
    std::vector<float> SplashDamages;
};


class PlantMeteorFlower : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMeteorFlower, PlantFramework, RtClass);

    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;//bool CanTargetZombie(const Zombie* i_zombie) const override;
    void UpdatePowerUpStats();
    Projectile*    Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;//Projectile*    Fire(Zombie* targetZombie, PlantWeapon i_plantWeapon) override;
    void onApplyCondition(PlantConditions i_condition) override;

    void FireMeteors(const std::vector<BoardEntity*> i_targets, int i_meteorCount);
private:
    void onAnimStoppedCallback(const std::string& i_animName) override;
    void setState(const int i_newState);
    void queueShot(pvztime_t i_launchTime, const Point& i_targetLocation);
    void findTargets(std::vector<BoardEntity*> *o_targets);
    void filterTargets(std::vector<BoardEntity*>& i_entities, std::vector<BoardEntity*> *o_targets, BoardEntityTypeFlag i_entityType);
    SexyVector3 getFuturePosition(BoardEntity* i_entity, pvztime_t i_time);
    void createMoltenPoolTile(SexyVector2 i_position);
    void scareAwayDinos();
    void doPlantfoodMeteor();
    void spawnPlantfoodMeteor(const PlanetMeteorInfo& i_info);

    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;

};

class MeteorProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(MeteorProjectile, Projectile, RtClass);
    bool OnCollideGround() override;
    
    void SetMoltenProps(float i_moltenDuration, float i_moltenDamage){ m_moltenDuration = i_moltenDuration; m_moltenDamage = i_moltenDamage;}

protected:
    float m_moltenDuration = 0;
    float m_moltenDamage = 0;

private:

    void createMoltenPool();
    bool canPlaceMoltenPool(Sexy::Point i_gridPosition);
};

class MeteorAdvancedProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(MeteorAdvancedProjectileProps, ProjectilePropertySheet, RtClass);

	MeteorAdvancedProjectileProps()
	: CanKnockbackZombie(false)
	{

	}

	bool CanKnockbackZombie;
};

class MeteorAdvancedProjectile : public MeteorProjectile
{
public:
	RT_CLASS_DEFINE(MeteorAdvancedProjectile, MeteorProjectile, RtClass);

	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool shouldKnockback(Zombie* i_zombie);
	void knockbackZombie(BoardEntity* i_impactedEntity);
};

class MeteorSuperProjectileProps : public MeteorAdvancedProjectileProps
{
public:
	RT_CLASS_DEFINE(MeteorSuperProjectileProps, MeteorAdvancedProjectileProps, RtClass);

	MeteorSuperProjectileProps()
	: PlanetMeteorMoveDistance(0)
	, PlanetMeteorAliases("")
	{

	}

	int PlanetMeteorMoveDistance;
	std::string PlanetMeteorAliases;
	std::vector<float> SplashDamages;
};

class MeteorSuperProjectile : public MeteorAdvancedProjectile
{
public:
	RT_CLASS_DEFINE(MeteorSuperProjectile, MeteorAdvancedProjectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

private:
	void createPlanetMeteor(const SexyVector3& i_position);
	bool canCreatePlanetMeteor(const SexyVector3& i_position);
};

class PlanetMeteorProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PlanetMeteorProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;

	void SetEndCol(int i_col);
	void SetMoltenProps(float i_moltenDuration, float i_moltenDamage){ m_moltenDuration = i_moltenDuration; m_moltenDamage = i_moltenDamage;}

protected:
	virtual void onInitialized() override;
	virtual void moveThroughTime(pvztime_t i_dt) override;

private:
	void doExplosion();
	bool canPushZombie(BoardEntityPtr i_entity);
	void createMoltenPool();
	bool canPlaceMoltenPool(Sexy::Point i_gridPosition);
	bool isInvalidRegion(const SexyVector3& i_position);

	std::vector<ZombiePtr> m_pushedZombies;
	int m_previousCol;
	float m_moltenDuration;
	float m_moltenDamage;
	int m_endCol;
};

class PlantAnimRig_MeteorFlower : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_MeteorFlower, PlantAnimRig, RtClass) {}
    bool PlayRecoverStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayRecoverLoop();
    bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayAttack(MeteorFlowerProjectileType i_type, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;

    std::string getPlantFoodMainAnimName() override;
};

class GridItemMoltenPool : public GridItemLava
{
public:
    RT_CLASS_DEFINE(GridItemMoltenPool, GridItemLava, RtClass);
    
    void SetOverrideMoltenProps(float i_moltenDuration, float i_moltenDamage)
    { m_lifeTime = i_moltenDuration; m_damagePerSecond = i_moltenDamage;}

protected:
    void onCauseDamage(class Zombie* i_zombie) override;
};


class GridItemMoltenPoolProps : public GridItemLavaProps
{
public:
    RT_CLASS_DEFINE(GridItemMoltenPoolProps, GridItemLavaProps, RtClass);

};

#endif /* Plant_MeteorFlower_h */


















