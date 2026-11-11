//
//  ZombieZombieMech_Dino.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 10/6/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombieMech_Dino__
#define __PlantsVersusZombies2__ZombieZombieMech_Dino__

#include <stdio.h>
#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"
#include "ZombieGargantuarMech.h"

#pragma mark - Custom Actions

#pragma mark Spawn Dino Action

class ZombossSpawnDinoActionDefinition : public ZombossSummonActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSpawnDinoActionDefinition, ZombossSummonActionDefinition, RtClass);
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	std::string SpawnDinoType;
};

class ZombossSpawnDinoActionHandler : public ZombossSummonActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSpawnDinoActionHandler, ZombossSummonActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	
	int getSpawningRow() const override;
	int getSpawningColumn() const override;
	
private:
	void setupDinoForSpawn();
	void onSummonDinosaurAnimationEnd(const std::string &i_animLabel);
	class Creature* spawnDino(CreatureTypePtr i_dinoType) const;
	
	CreatureTypePtr m_dinosaurToSpawn;
	bool m_hasSpawnedDino;
	int m_spawningRow;
	pvztime_t m_dinoSpawnTime;
};

#pragma mark Dino Walk Action

class ZombossDinoWalkActionDefinition : public ZombossWalkActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDinoWalkActionDefinition, ZombossWalkActionDefinition, RtClass);
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossDinoWalkActionHandler : public ZombossWalkActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDinoWalkActionHandler, ZombossWalkActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
private:
	pvztime_t m_nextStepTime;
};

#pragma mark Dino Laser Action

class ZombossDinoLaserActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossDinoLaserActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossDinoLaserActionDefinition()
	: FlameDuration(5.0f)
	, FlameFillRowTime(2.0)
	, PlantfoodDamageToInterrupt(100.f)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	float FlameDuration;
	float FlameFillRowTime;
	float PlantfoodDamageToInterrupt;
};

class ZombossDinoLaserActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossDinoLaserActionHandler, ZombieActionHandler, RtClass);
	
	ZombossDinoLaserActionHandler()
	: m_fireLastFilledColumn(10)
	, m_startedFire(false)
	{}
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void spawnLaserFireAt(Point i_location);
	
	void onLaserStartEnded(const std::string& i_animName);
	void onLaserEndEnded(const std::string& i_animName);
	
	void cleanup();
	
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	
	void initLaser();
	void drawLaser(class Graphics* i_graphics);
	float drawLaserFromTo(class Graphics* i_graphics, const SexyVector3& i_from, const SexyVector3& i_to);
	
	bool pickLaserTargets(SexyVector3& o_startLocBoard, SexyVector3& o_endLocBoard);
	void fireOnLaserTargets(SexyVector3 i_startLocBoard, SexyVector3 i_endLocBoard);
	
	void calculateLaserBeamStartPosition(Point &startPos);
	
	CurveCollection_Float m_fireRushCurves;
	int m_fireLastFilledColumn;
	bool m_startedFire;
	
	EyeLaserTracker m_laserState;
	RtWeakPtr<class Effect_PopAnim> m_scorchRig;
	RtWeakPtr<class Effect_PopAnim> m_beamRig;
};

#pragma mark - Props

class ZombieZombossMechDinoProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechDinoProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechDinoProps()
	: SplashRadius(1.0)
	, SplashDamage(50.0f)
	, EyeLaserWarmUpTime(0.1f)
	, EyeLaserSweepTime(1.0f)
	, LaserOffset(0, 0)
	, LaserMaxColumn(5)
	, LaserMinColumn(0)
	{}
	
	float SplashRadius;
	float SplashDamage;
	float EyeLaserWarmUpTime;
	float EyeLaserSweepTime;
	Point LaserOffset;
	int LaserMaxColumn;
	int LaserMinColumn;
};

#pragma mark - Zomboss

class ZombieZombossMech_Dino : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Dino, ZombieZombossMech, RtClass);
	
	ZombieZombossMech_Dino();
	
	void Retreat(ZombieState i_endState) override;
	void OnRocketHitGround(ZombossRocket* i_rocket) override;
	
	int CalcRenderOrder() const override;
	
protected:
	void onUpdate() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	bool isPlantAllowedUnderZomboss(const PlantType* i_plant) override;
};

#pragma mark - Anim Rig

class ZombieAnimRig_ZombossMech_Dino : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Dino, ZombieAnimRig_ZombossMech, RtClass);
	
	ZombieAnimRig_ZombossMech_Dino()
	: m_playingIdle(false)
	{}
	
	bool PlayDinosaurSummoning(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	bool PlayLaserStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLaserLoop();
	bool PlayLaserEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	bool PlayLobbedFireStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLobbedFireAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLobbedFireEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	void PlayIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	void PlayWalkForDirection(ZombossWalkDirection i_walkDir, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	
	const Sexy::FPoint getTeleportationEffectOffset() const override;
	
protected:
	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	const char* getSummoningAnimName() const override { return "summon_dinosaurs"; }
	const char* getDinosaurSummoningAnimName() const { return "summon_dinosaurs"; }
	
	void onPostPlayCalled() override;
	
	const char* getRocketStartAnimName() const override;
	const char* getRocketLaunchAnimName() const override;
	
private:
	bool m_playingIdle;
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombieMech_Dino__) */
