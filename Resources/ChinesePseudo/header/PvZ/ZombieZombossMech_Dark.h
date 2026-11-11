//
//  ZombieZombossMech_Dark.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/14/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Dark__
#define __PlantsVersusZombies2__ZombieZombossMech_Dark__

#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"

#pragma mark - Custom Actions

#pragma mark Dark Spawn Action

class ZombossDarkSpawnActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDarkSpawnActionDefinition, ZombieActionDefinition, RtClass);

	ZombossDarkSpawnActionDefinition()
		: SpawnDistanceVariance(150)
		, SpawnWavesBetweenPlantFood(1.f, 1.f)
		, SpawnStartTime(1.f)
		, SpawnEndTime(1.5f)
		, SpawnZombieWavePointRange(1500, 7500)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	int SpawnDistanceVariance;
	std::vector<std::string> SpawnZombieTypes;
	float SpawnStartTime;
	float SpawnEndTime;
	ValueRange SpawnWavesBetweenPlantFood;
	ValueRange SpawnZombieWavePointRange;
};

class ZombossDarkSpawnActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDarkSpawnActionHandler, ZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

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

#pragma mark Dark Walk Action

class ZombossDarkWalkActionDefinition : public ZombossWalkActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDarkWalkActionDefinition, ZombossWalkActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossDarkWalkActionHandler : public ZombossWalkActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDarkWalkActionHandler, ZombossWalkActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
private:
	pvztime_t m_nextStepTime = PVZ_EOT();
};

#pragma mark Dark Fire Breath Action

class ZombossDarkFireBreathActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDarkFireBreathActionDefinition, ZombieActionDefinition, RtClass);

	ZombossDarkFireBreathActionDefinition()
		: FlameDuration(5.0f)
		, FlameFillRowTime(2.0)
		, PlantfoodDamageToInterrupt(100.f)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;

	float FlameDuration;
	float FlameFillRowTime;
	float PlantfoodDamageToInterrupt;
};

class ZombossDarkFireBreathActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDarkFireBreathActionHandler, ZombieActionHandler, RtClass);

	ZombossDarkFireBreathActionHandler()
		: m_fireLastFilledColumn(10)
		, m_startedFire(false)
		, m_startedOutro(false)
	{}

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

private:
	void spawnFireAt(Point i_location);

	void onFireBreathStartEnded(const std::string& i_animName);
	void onFireBreathEndEnded(const std::string& i_animName);

	CurveCollection_Float m_fireRushCurves;
	int m_fireLastFilledColumn;
	bool m_startedFire;
	bool m_startedOutro;
};

#pragma mark Dark Lob Fireballs Action

class ZombossDarkLobFireballsActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDarkLobFireballsActionDefinition, ZombieActionDefinition, RtClass);

	ZombossDarkLobFireballsActionDefinition()
		: LobbedFlameCount(5, 5)
		, DragonImpCount(0, 0)
		, LobbedFlameDelay(2.f)
		, LobbedFlameDuration(5.f)
		, PlantfoodDamageToInterrupt(100)
		, MinColumn(2)
		, TargetMagnetshroomChance(0.75)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;

	ValueRange LobbedFlameCount;
	ValueRange DragonImpCount;
	
	int MinColumn;
	
	float LobbedFlameDelay;
	float LobbedFlameDuration;
	float PlantfoodDamageToInterrupt;
	float TargetMagnetshroomChance;
};

class ZombossDarkLobFireballsActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDarkLobFireballsActionHandler, ZombieActionHandler, RtClass);

	ZombossDarkLobFireballsActionHandler()
	{}

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

private:
	void lobFireball(const Point& i_fireballSpot, bool i_fireballSpawnsDragon) const;
	void pickFireballSpots(std::vector<Point>& o_fireballsToLob, int i_numSpots) const;
	void onFireLobStartEnded(const std::string& i_animName);
	void onFireLobActionEnded(const std::string& i_animName);
	void onFireLobEndEnded(const std::string& i_animName);

	std::vector<Point> m_fireballsToLob;
	std::vector<int> m_fireballSpawnsDragon;
};

#pragma mark - Props

class ZombieZombossMechDarkProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechDarkProps, ZombieZombossMechProps, RtClass);

	ZombieZombossMechDarkProps()
		: MagnetStunDuration(3.0)
	{}

	float MagnetStunDuration;
};

#pragma mark - Zomboss

STATE_ENUM_CHILD_BEGIN(ZombossDarkMechState, ZombossMechState)
	ZombossDarkMagnetStun,
STATE_ENUM_END(ZombossDarkMechState);


class ZombieZombossMech_Dark : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Dark, ZombieZombossMech, RtClass);

	ZombieZombossMech_Dark();

	void Retreat(ZombieState i_endState) override;

protected:
	void onUpdate() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	bool isPlantAllowedUnderZomboss(const PlantType* i_plant) override;

	DECLARE_STATE_FUNCTIONS(ZombieState, MagnetStun);

private:
	bool canBeMagnetStunned();
	void onMagnetStunAnimDone(const std::string& i_animLabel);
	void onMagnetStunEndAnimDone(const std::string& i_animLabel);

	bool m_playingMagnetStunStart;
	bool m_playingMagnetStunEnd;
};

#pragma mark - Anim Rig

class ZombieAnimRig_ZombossMech_Dark : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Dark, ZombieAnimRig_ZombossMech, RtClass);

	ZombieAnimRig_ZombossMech_Dark()
		: m_playingIdle(false)
	{}

	bool PlayFireBreathStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayFireBreathLoop();
	bool PlayFireBreathEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	bool PlayLobbedFireStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLobbedFireAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLobbedFireEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	bool PlayMagnettedStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayMagnettedLoop();
	bool PlayMagnettedEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

    void PlayIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	void PlayWalkForDirection(ZombossWalkDirection i_walkDir, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	
	const Sexy::FPoint getTeleportationEffectOffset() const override;
	
protected:
	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
    const char* getSummoningAnimName() const override { return "summoning"; }
	void onPostPlayCalled() override;
private:
	bool m_playingIdle;
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Dark__) */
