//
//  GridItemZombiePortal.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/22/15
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemZombiePortal__
#define __PlantsVersusZombies2__GridItemZombiePortal__

#include "ZombieType.h"
#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"
#include "PopAnimRig.h"

// NOTE: If we ever need a breakable version of this, consider refactoring this class into a component.
class ZombieWithActions;

enum GridItemZombieSpawnMethod
{
	PVZ_BEGIN_ENUM(GRIDITEMZOMBIESPAWNMETHOD_),
	GRIDITEMZOMBIESPAWNMETHOD_Random,
	GRIDITEMZOMBIESPAWNMETHOD_NonRandomInOrder,
	GRIDITEMZOMBIESPAWNMETHOD_NonRandomShuffled,
	PVZ_END_ENUM(GRIDITEMZOMBIESPAWNMETHOD_)
};

enum GridItemZombiePortalState
{
	PVZ_BEGIN_ENUM(PORTALSTATE_),
	PORTALSTATE_NEEDS_INITIALIZING,
	PORTALSTATE_OPEN,
	PORTALSTATE_IDLE,
	PORTALSTATE_CLOSE,
	PVZ_END_ENUM(PORTALSTATE_)
};

class GridItemZombiePortalProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemZombiePortalProps, GridItemAnimationProps, RtClass);
	
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames);
	
	ValueRange TimeBetweenSpawns = { 10.0f, 12.0f };
	std::vector<BasicZombieWeights> ZombieTypesToSpawn;
	int ZombiesToSpawn = 3;
	int ZombieSpawnPointOffset = -80;
	GridItemZombieSpawnMethod ZombieSpawnMethod = GRIDITEMZOMBIESPAWNMETHOD_Random;
	std::string SpawnAnimation;
	std::string CloseAnimation;
	std::string World;
	bool SuppressSpawn = false;
};

class GridItemZombiePortal : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemZombiePortal, GridItemAnimation, RtClass);
	
	GridItemZombiePortal()
	{
		m_zombiesToSpawn_Override = -1;
		m_zombieListRangeStart_Override = -1;
		m_zombieListRangeEnd_Override = -1;
		m_nSpawnZombiesNum = -1;
		m_nHasSpawnNum = 0;
		m_fSpawnSpace = -1;
	}
	
	int	CalcRenderOrder() const override;
	pvztime_t GetNextSpawnTime() { return m_nextSpawnTime; }
	void SetNextSpawnTime(pvztime_t i_nextSpawnTime) { m_nextSpawnTime = i_nextSpawnTime; }
	
	bool ShouldBlockLevelCompletion() const override { return true; }
	
	void setState(GridItemZombiePortalState i_state);
	GridItemZombiePortalState getState();
	void updateState();
	
	void SetZombiesToSpawn(int i_zombieCount) { m_zombiesToSpawn_Override = i_zombieCount; }
	void SetZombieRandomListRange(int i_start, int i_end) { m_zombieListRangeStart_Override = i_start; m_zombieListRangeEnd_Override = i_end; }
	
	void setSpawnZombiesNum(int spawnZombiesNum);
	int getSpawnZombiesNum() const;

	void setSpawnSpace(float spawnSpace);
	float getSpawnSpace() const;
	void setZomBoss(RtWeakPtr<ZombieWithActions> zomBoss);
protected:
	virtual void onGridItemInitialize() override;
	void onUpdate() override;
	void onOpenAnimCompleted();
	void onCloseAnimCompleted();
	void spawnNextZombie();
	void onZombiesExhausted();
	void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
private:
	int getZombieCountToSpawn() { return m_zombiesToSpawn_Override > -1 ? m_zombiesToSpawn_Override : GetProps<GridItemZombiePortalProps>()->ZombiesToSpawn; }
	void createZombieSpawnList();
	void createZombieSpawnList_InOrder();

	std::string pickRandomZombie();
	int GetSummonZombieLevel();
	pvztime_t m_nextSpawnTime = PVZ_EOT();
	
	std::vector<std::string> m_zombiesToSpawn;
	GridItemZombiePortalState m_state;
	
	int m_zombiesToSpawn_Override;
	int m_zombieListRangeStart_Override;
	int m_zombieListRangeEnd_Override;

	int m_nSpawnZombiesNum;
	int m_nHasSpawnNum;
	float m_fSpawnSpace;
	RtWeakPtr<ZombieWithActions> m_pZomBoss;
};

class GridItemZombossPortal : public GridItemZombiePortal
{
public:
	RT_CLASS_DEFINE(GridItemZombossPortal, GridItemZombiePortal, RtClass);

	GridItemZombossPortal()
	{
	}
	void setZomBoss(RtWeakPtr<ZombieWithActions> zomBoss);
protected:
	void onGridItemInitialize() override;
	void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
private:
	RtWeakPtr<ZombieWithActions> m_pZomBoss;
};

class GridItemZombiePortal_AnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemZombiePortal_AnimRig, PopAnimRig, RtClass);
	
	GridItemZombiePortal_AnimRig();
	
	void PlayOpen(std::string animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayIdle();
	void PlayClose(std::string animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void ShowPortalLayers(std::string i_portalType);
	
private:
	GridItemZombiePortalState m_state;
	std::string m_portalType;
};


#endif
