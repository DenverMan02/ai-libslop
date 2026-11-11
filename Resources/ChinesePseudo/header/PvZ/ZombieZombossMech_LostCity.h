//
//  ZombieZombossMech_LostCity.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/19/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_LostCity__
#define __PlantsVersusZombies2__ZombieZombossMech_LostCity__

#include "ComponentBase.h"
#include "GridItemZombieConditionTarget.h"
#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"

class ZombossRocket;

#pragma mark - Zomboss

class ZombieZombossMechLostCityProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechLostCityProps, ZombieZombossMechProps, RtClass);
	
	RtWeakPtr<ZombieActionDefinition> SpawnZombieAction;
	RtWeakPtr<ZombieActionDefinition> DropSandbagAction;
};

class ZombieZombossMech_LostCity : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_LostCity, ZombieZombossMech, RtClass);
	
	int CalcRenderOrder() const override;
	SexyVector2 GetShadowScaling() const override;
	
	void OnRocketHitGround(ZombossRocket* i_rocket) override;
	
protected:
	void onZombieInitialize() override;
	
	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) override {}
};

#pragma mark - AnimRig

class ZombieAnimRig_ZombossMech_LostCity : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_LostCity, ZombieAnimRig_ZombossMech, RtClass);
	
	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	
	void PlayStartZombieDrop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayLoopZombieDrop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayEndZombieDrop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	void PlaySandBagDrop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	const char* getPreIntroAnimName() const override;
	const char* getStunEndAnimName() const override;
	const char* getIntroAnimName() const override;
	const char* getIdleAnimName() const override;
	const char* getStunAnimName() const override;
	const char* getStunLoopAnimName() const override;
	const char* getJumpStartAnimName() const override;
	const char* getJumpLandAnimName() const override;
	const char* getZombossDieAnimName() const override;
};


#pragma mark - ZombossDropZombieAction

class ZombossDropZombieActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDropZombieActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossDropZombieActionDefinition()
	{
		NumberOfRowsToSpawnDown = 1;
		ZombieDropSpeed = 100.0f;
		SpawnCooldownTime = 1.0f;
		MovementCurveType = CURVE_LINEAR;
		MovementSpeed = 160.0f;
	}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	RtWeakPtr<ZombossJumpActionDefinition>	SpawnJumpAction;
	std::vector<std::string>				SpawnZombieTypes;
	ValueRange								SpawnWavesBetweenPlantFood;
	ValueRange								SpawnZombieWavePointRange;
	Rect									ValidSpawningRegion;
	int32_t									NumberOfRowsToSpawnDown;
	float									ZombieDropSpeed;
	float									SpawnCooldownTime;
	CurveType								MovementCurveType;
	float									MovementSpeed;
};

class ZombossDropZombieActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDropZombieActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void pickZombiesForSpawn();
	void spawnZombie();
	Zombie* createNextZombie();
	Point calcNewSpawningPoint() const;
	bool waveHasPlantfoodCarryingZombie(const std::vector<ZombieTypePtr> i_zombies) const;
	int pickPlantfoodSpawnDelay() const;
	
	void onSpawnAnimationEnd(const std::string& i_animLabel);
	
	std::vector<ZombieTypePtr>	m_zombiesToSpawn;
	Point						m_lastDropPoint;
	CurveCollection_Float		m_movementCurves;
	pvztime_t					m_nextZombieSpawnTime = PVZ_EOT();
	int32_t						m_currentState = 0;
};


#pragma mark - ZombossDropSandbagAction

class ZombossDropSandbagActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDropSandbagActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossDropSandbagActionDefinition()
	{
		MovementCurveType = CURVE_LINEAR;
		MovementSpeed = 160.0f;
	}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	ProjectilePropertySheetPtr	ProjectileTypeToSpawn;
	SexyVector3					ProjectileOffset;
	Rect						ValidDroppingRegion;
	SexyVector3					DroppingOffset;
	CurveType					MovementCurveType;
	float						MovementSpeed;
};

class GridItemTriggerTile;

class ZombossDropSandbagActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDropSandbagActionHandler, ZombieActionHandler, RtClass);
	
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	
private:
	void findValidTargets(std::vector<BoardEntity*>& i_validTargets);
	
	void onTriggerAnimationEnd(const std::string& i_animLabel);
	
	CurveCollection_Float			m_movementCurves;
	int32_t							m_currentState = 0;
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_LostCity__) */
