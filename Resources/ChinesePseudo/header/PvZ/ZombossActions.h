//
//  ZombossActions.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/20/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombossActions__
#define __PlantsVersusZombies2__ZombossActions__

#include "GameObject.h"
#include "PropertySheetBase.h"
#include "Utils.h"
#include "Timeline.h"
#include "PVZTypes.h"
#include "ZombieAction.h"

enum ZombossWalkDirection
{
	ZombossWalkUp,
	ZombossWalkDown,
	ZombossWalkLeft,
	ZombossWalkRight
};

class ZombieZombossMech;
class ZombieWithActions;

#pragma mark Zomboss Walk Action

class ZombossWalkActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossWalkActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossWalkActionDefinition()
		: WalkVerticalChance(0.5f)
		, WalkPreferSquashChance(0.f)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	
	bool PickWalkTarget(class ZombieZombossMech* i_zomboss, Point& o_targetPosition, ZombossWalkDirection& o_walkDirection) const;

	float WalkVerticalChance;
	float WalkPreferSquashChance;
};

class ZombossWalkActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossWalkActionHandler, ZombieActionHandler, RtClass);
	
	ZombossWalkActionHandler()
	{}
	
	void SetWalkTarget(const Point& i_walkTarget, ZombossWalkDirection i_walkDirection);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void buildWalkCurve(const SexyVector3& i_startPosition, const SexyVector3& i_endPosition, pvztime_t i_startTime, pvztime_t i_walkDuration, CurveType i_curveType, CurveCollection_Float& i_movementCurves);

	Point m_walkTarget;
	ZombossWalkDirection m_walkDirection = ZombossWalkUp;
	CurveCollection_Float m_movementCurves;
};

#pragma mark Zomboss Jump Action

class ZombossJumpActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossJumpActionDefinition, ZombieActionDefinition, RtClass);

	ZombossJumpActionDefinition()
		: JumpHeight(200.f)
		, JumpHangTime(1.0f)
		, JumpAnimRateModifier(1.0f)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	
	float JumpHeight;
	float JumpHangTime;
	float JumpAnimRateModifier;
};

class ZombossJumpActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossJumpActionHandler, ZombieActionHandler, RtClass);
	
	ZombossJumpActionHandler()
		: m_jumpTarget(-1, -1)
		, m_jumpMidAir(false)
		, m_jumpLandStartTime(PVZ_EOT())
	{}
	
	void SetJumpTarget(const Point& i_jumpTarget);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	virtual void onLanding() {}

private:
	void onJumpStartAnimDone(const std::string& i_animName);

	void buildJumpCurve(const Sexy::SexyVector3& i_startPosition, const Sexy::SexyVector3& i_endPosition, float i_apexHeight, pvztime_t i_startTime, pvztime_t i_windupDuration, pvztime_t i_jumpDuration, pvztime_t i_landDuration, CurveCollection_Float& i_movementCurves) const;
	void appendJumpCurve(const Sexy::SexyVector3& i_startPosition, const Sexy::SexyVector3& i_endPosition, float i_apexHeight, pvztime_t i_windupDuration, pvztime_t i_jumpDuration, pvztime_t i_landDuration, CurveCollection_Float& i_movementCurves) const;

	CurveCollection_Float m_movementCurves;
	Point m_jumpTarget;
	bool m_jumpMidAir;
	pvztime_t m_jumpLandStartTime;
};

#pragma mark Zomboss Spawn Action
// Zomboss opens a portal in front of the mech and spawns zombies in
// own row, in contrast to "Summon" which brings zombies forth all over.

class ZombossSpawnActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSpawnActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossSpawnActionDefinition()
		: SpawnChargeTime(1.f)
		, SpawnCooldownTime(0.f)
		, SpawnWavesBetweenPlantFood(1.f, 1.f)
		, SpawnZombieWavePointRange(1500, 7500)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	RtWeakPtr<ZombossJumpActionDefinition> SpawnJumpAction;
	std::vector<std::string> SpawnZombieTypes;
	float SpawnChargeTime;
	float SpawnCooldownTime;
	ValueRange SpawnWavesBetweenPlantFood;
	ValueRange SpawnZombieWavePointRange;
};

class ZombossSpawnActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSpawnActionHandler, ZombieActionHandler, RtClass);
	
	ZombossSpawnActionHandler()
		: m_portalOpenedTime(PVZ_EOT())
		, m_spawnedZombie(false)
	{}

    void AddToRenderQueue(class RenderQueue* i_queue) override;

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

private:
	void pickZombiesForSpawn();
	class Zombie* spawnZombie();
	void drawZombieSpawnPortal(Sexy::Graphics* i_graphics);
	int pickPlantfoodSpawnDelay() const;
	bool waveHasPlantfoodCarryingZombie(const std::vector<ZombieTypePtr> i_zombies) const;
	bool isZombieValidForSpawnLocation(const ZombieTypePtr i_zombieType) const;
	
	void onPortalStartAnimDone(const std::string& i_animName);
	void onPortalStopAnimDone(const std::string& i_animName);
	void onZombiePortalOpenAnimDone(const std::string& i_animName);
	void onZombiePortalCloseAnimDone(const std::string& i_animName);
	
	std::vector<ZombieTypePtr> m_zombiesToSpawn;
	RtWeakPtr<class EffectAnimRig_ZombiePortal> m_zombiePortalAnim;
	pvztime_t m_portalOpenedTime;
	bool m_spawnedZombie;
};

#pragma mark Zomboss Summon Action
// Zomboss plays a single animation and summons zombies all over the board,
// in contrast to "Spawn" which brings zombies forth from a portal on the mech.

class ZombossSummonActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSummonActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossSummonActionDefinition()
	: SpawnDistanceVariance(150)
	, SpawnColumnOffset(0)
	, SpawnWavesBetweenPlantFood(1.f, 1.f)
	, SpawnStartTime(1.f)
	, SpawnEndTime(1.5f)
	, SpawnZombieWavePointRange(1500, 7500)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	int SpawnDistanceVariance;
	int SpawnColumnOffset;
	std::vector<std::string> SpawnZombieTypes;
	float SpawnStartTime;
	float SpawnEndTime;
	ValueRange SpawnWavesBetweenPlantFood;
	ValueRange SpawnZombieWavePointRange;
};

class ZombossSummonActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSummonActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
	virtual int getSpawningRow() const;
	virtual int getSpawningColumn() const;
	pvztime_t getStartSpawningTime() const;
	
private:
	void pickZombiesForSpawn();
	class Zombie* spawnZombie(ZombieTypePtr i_zombieType) const;
	int pickPlantfoodSpawnDelay() const;
	bool waveHasPlantfoodCarryingZombie(const std::vector<ZombieTypePtr> i_zombies) const;
	bool isZombieValidForSpawnLocation(const ZombieTypePtr i_zombieType) const;
	void onSummonAnimationEnd(const std::string& i_animLabel);
	std::vector<ZombieTypePtr> m_zombiesToSpawn;
	pvztime_t m_startSpawningTime = PVZ_EOT();
	int m_spawnedSoFar = 0;
};

#pragma mark Zomboss Rush Action

class ZombossRushActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRushActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossRushActionDefinition()
		: RushDamageToInterrupt(100.f)
		, RushTime(1.f)
		, RushLeadupTime(1.5f)
		, RushLeadupStartRate(1.f)
		, RushLeadupEndRate(1.f)
		, RushLeadupBackup(60)
		, RushStartRate(1.5f)
		, RushEndRate(8.f)
		, RushOvershoot(200.f)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	
	float RushDamageToInterrupt;
	float RushTime;
	float RushLeadupTime;
	float RushLeadupStartRate;
	float RushLeadupEndRate;
	float RushLeadupBackup;
	float RushStartRate;
	float RushEndRate;
	float RushOvershoot;
	std::string RushSound;
};

class ZombossRushActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRushActionHandler, ZombieActionHandler, RtClass);
	
	ZombossRushActionHandler()
		: m_rushStartedRushing(false)
	{}
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	void onRushStompAnimDone(const std::string& i_animName);
	
	virtual bool CheckRushingDone();

	bool m_rushStartedRushing;
	CurveSequence_Float m_rushAnimRateCurve;
	CurveCollection_Float m_movementCurves;

protected:
	void startRushForward();
};

#pragma mark Zomboss Fire Action

class ZombossFireActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossFireActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossFireActionDefinition()
		: FireMinColumn(0)
		, FireMaxColumn(5)
		, FireRowRange(5)
		, FireTargetEmptyWeight(1)
		, FireTargetPlantWeight(1)
		, FireTargetRailsWeight(0)
		, FireTargetTilesWeight(0)
		, FireRocketHitTime(3.f)
		, FireRocketSpeed(250.f)
		, FireRocketCount(1, 1)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;

protected:
	virtual bool pickRocketTargets(ZombieZombossMech *i_zomboss, std::vector<Point>& o_targetSquares) const;
	void getRocketTargetSquaresInRect(ZombieZombossMech* i_zomboss, const Rect& i_targetRect, std::vector<Point>& o_targetGridSquares, Delegate1wRet<bool, const Sexy::Point&> i_acceptSquare) const;
	bool pickRocketRailTargets(std::vector<Point> &o_targetSquares, Point i_railGridSquare) const;
	bool isCartGridSquare(const Point& i_searchSquare) const;
	
public:
	int FireMinColumn;
	int FireMaxColumn;
	int FireRowRange;
	int FireTargetPlantWeight;
	int FireTargetEmptyWeight;
	int FireTargetRailsWeight;
	int FireTargetTilesWeight;
	float FireRocketHitTime;
	float FireRocketSpeed;
	std::string FireRocketDropSound;
	ValueRange FireRocketCount;
};

class ZombossFireActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossFireActionHandler, ZombieActionHandler, RtClass);
	
	ZombossFireActionHandler()
		: m_canLeaveRocketState(false)
		, m_doneLaunching(false)
	{}
	
	void SetRocketTargets(const std::vector<Point>& i_targetPoints);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

private:
	void onRocketStartAnimDone(const std::string& i_animName);
	void onRocketLaunchAnimDone(const std::string& i_animName);
	
	std::vector<Point> m_targetPoints;
	bool m_canLeaveRocketState;
	bool m_doneLaunching;
};

class ZombossSpawnPortalActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSpawnPortalActionDefinition, ZombieActionDefinition, RtClass);
	ZombossSpawnPortalActionDefinition()
	:PortalZombieCountOverride(-1),
	PortalZombieRandomListStartOverride(-1),
	PortalZombieRandomListEndOverride(-1),
	PortalSpawnZombiesNum(-1),
	PortalSpawnSpace(-1),
	PortalRow(0),
	PortalColumn(0)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	int									PortalRow;
	int									PortalColumn;
	std::string							PortalType;
	int									PortalSpawnZombiesNum;
	float								PortalSpawnSpace;
	int									PortalZombieCountOverride;
	int									PortalZombieRandomListStartOverride;
	int									PortalZombieRandomListEndOverride;
};

#endif /* defined(__PlantsVersusZombies2__ZombossActions__) */
