//
//  ZombieLostCityImpPorter.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/23/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieImpPorter__
#define __PlantsVersusZombies2__ZombieImpPorter__

static const float kBounceTime = 0.5;
static const float kBounceHeight = 60.0;

#include "GravestoneAnimRig.h"
#include "GridItemGravestone.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"

namespace Message
{
	void GridItemTentSpawned(GridItem* i_target);
}

STATE_ENUM_CHILD_BEGIN(ZombieImpPorterState, ZombieState)
ZS_IP_SpawnTent,
STATE_ENUM_END(ZombieImpPorterState)

class ZombieImpPorterProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieImpPorterProps, ZombiePropertySheet, RtClass);
	float TentTargetingOffsetX = 0;
};

class ZombieImpPorter : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieImpPorter, Zombie, RtClass);
	
	void ShatterPackInstantly();
	
protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, SpawnTent);
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	bool willDieToShrinking() override { return true; }
	
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_IMP_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_IMP_ASH"; }
	
private:
	void spawnTent();
	void dropPack();
	Point getDefaultTentSpawnPosition();
	bool canSpawnTentOnTile();
	
	bool canSpawnTentAt(const Point& i_targetPosition) const;
	class GridItemTent* tryPlaceTent(const Point& i_gridPosition);
	
	void onSpawnTentAnimCompleted();
};

class ZombieAnimRig_ImpPorter : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ImpPorter, ZombieAnimRig, RtClass);
	
	bool PlaySpawnTent(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const bool getDieShouldBlend() override { return false; }
};

class GridItemTentProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemTentProps, GridItemGravestonePropertySheet, RtClass);
	ValueRange TimeBetweenSpawns = { 10.0f, 12.0f };
	std::vector<BasicZombieWeights> ZombieTypesToSpawn;
	int ZombieSpawnPointOffset = -80;
};

class GridItemTent : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemTent, GridItemGravestone, RtClass);
	
	void CalcDamageState();
	int	CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const override;
	pvztime_t GetNextSpawnTime() { return m_nextSpawnTime; }
	void SetNextSpawnTime(pvztime_t i_nextSpawnTime) { m_nextSpawnTime = i_nextSpawnTime; }
	void KillGridItem() override;
	
	bool ShouldBlockLevelCompletion() const override { return true; }
	
protected:
	void onTakeDamage(const DamageInfo& i_damage) override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	
private:
	void onDestroyAnimCompleted();
	std::string pickBasicZombie();
	pvztime_t m_nextSpawnTime = PVZ_EOT();
	bool m_hasPlayedDeathAnim = false;
};

class TentAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(TentAnimRig, GravestoneAnimRig, RtClass);
	
	TentAnimRig();
	
	void PlayStationary();
	void PlayDestroy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SetDamageState(int i_damageState, bool i_isAnimated) override;
	void onAnimStopped() override;
	
private:
	bool m_inIntroAnim;
	bool m_isDying;
};

class GridItemBackpack : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemBackpack, GridItemGravestone, RtClass);
	
	void CalcDamageState();
	PlantingReason GetCantPlantReason() const override;
	void KillGridItem() override;
	void SetInitialBounce(SexyVector3 i_startLoc);
	
protected:
	void onTakeDamage(const DamageInfo& i_damage) override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	SexyVector2	getRenderOffset() override;
	
private:
	void updateOffsetForBounce();
	void onDestroyAnimCompleted();
	bool m_hasPlayedDeathAnim = false;
	float m_bounceStartTime = PVZ_EOT();
	SexyVector3 m_offset;
	SexyVector3 m_velocity;
	SexyVector3 m_acceleration;
};

class BackpackAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(BackpackAnimRig, GravestoneAnimRig, RtClass);
	
	BackpackAnimRig();
	
	void PlayStationary();
	void PlayDestroy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SetDamageState(int i_damageState, bool i_isAnimated) override;
	void onAnimStopped() override;
	
private:
	bool m_inIntroAnim;
	bool m_isDying;
};

#endif /* defined(__PlantsVersusZombies2__ZombieImpPorter__) */
