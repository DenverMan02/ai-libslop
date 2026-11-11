//
//  GridItemGravestoneZombieTimeSpawner.h
//  PlantsVersusZombies2
//
//  Created by Erik Rydeman on 29/08/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __GridItemGraveStoneZombieTimeSpawner_H__
#define __GridItemGraveStoneZombieTimeSpawner_H__

#include <string>

#include "DamageInfo.h"
#include "GridItemGravestone.h"
#include "GravestoneAnimRig.h"
#include "PVZTypes.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "TimeMgr.h"

class GridItemGravestoneZombieTimeSpawnerPropertySheet : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneZombieTimeSpawnerPropertySheet, GridItemGravestonePropertySheet, RtClass);
	
	GridItemGravestoneZombieTimeSpawnerPropertySheet()
	{
		MinInitialSpawnWaitSeconds = 0;
		MaxInitialSpawnWaitSeconds = 0;
		MinSpawnWaitSeconds = 0;
		MaxSpawnWaitSeconds = 0;
		ZombieTypeName = "";
		MinSelfDestructWaitSeconds = -1;
		MaxSelfDestructWaitSeconds = -1;
	}
	
	int32 MinInitialSpawnWaitSeconds;
	int32 MaxInitialSpawnWaitSeconds;
	int32 MinSpawnWaitSeconds;
	int32 MaxSpawnWaitSeconds;
	int32 MinSelfDestructWaitSeconds;
	int32 MaxSelfDestructWaitSeconds;
	std::string ZombieTypeName;
};

class GridItemGravestoneZombieTimeSpawner : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemGravestoneZombieTimeSpawner, GridItemGravestone, RtClass);
	
	GridItemGravestoneZombieTimeSpawner();
	
protected:
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onTakeDamage(const DamageInfo& i_damage) override;
	
private:
	pvztime_t getInitialRandomSpawnTimeDuration();
	pvztime_t getRandomSpawnTimeDuration();
	pvztime_t getSelfDestructTimeDuration();
	void spawnZombie();
	void spawnZombieFromExplosion(int gridOffsetY);
	ZombieTypePtr getZombieType();
	
	void onDeathAnimFinished(const std::string& i_animName);
	
	pvztime_t m_nextSpawnTime;
	pvztime_t m_selfDestructTime;
	AnimHandle m_animHandle;
};

class GravestoneAnimRig_ZombieTimeSpawner : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(GravestoneAnimRig_ZombieTimeSpawner, GravestoneAnimRig, RtClass);
	
	GravestoneAnimRig_ZombieTimeSpawner();
	
	virtual void onUpdate() override;
	virtual void SetDamageState(int i_damageState, bool i_isAnimated) override;
	
	void SetZombieHelmType(HelmType i_helmType);
	void SetOpenTime(pvztime_t i_openTime);
	void PlayDeathAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool IsDying() { return m_isDying; }
	
private:
	pvztime_t getNextRattleTime();
	const std::vector<std::string>& getConeLayerNames();
	const std::vector<std::string>& getBucketLayerNames();
	const std::vector<std::string>& getCrownLayerNames();
	void updateLayerVisibility(bool typeIsVisible, int damageState, const std::vector<std::string>& layerNames);
	
	AnimHandle m_animHandle;
	HelmType m_helmType;
	pvztime_t m_nextRattleTime;
	pvztime_t m_openTime;
	bool m_isOpen;
	bool m_isDying;
};

#endif
