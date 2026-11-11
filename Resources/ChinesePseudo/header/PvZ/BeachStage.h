//
//  BeachStage.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 5/20/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BeachStage__
#define __PlantsVersusZombies2__BeachStage__

#include "StageModule.h"
#include "Effect_PopAnim.h"
#include "PlantType.h"
#include "BoardEnums.h"
#include "WaveActionSpawnZombies.h"

namespace Message
{
    void BeachWaveChangeColor(bool bFadeOut);
}

class BeachStage : public StageModule
{
public:
	RT_CLASS_DEFINE(BeachStage, StageModule, RtClass);
    
    BeachStage() : m_tLemonRainEffectRemainTime(0), m_iWaterAcidDamge(0), m_tDtTime(0) {}
    
    void SetLemonRainDelayTime(int iDelay);
    
    pvztime_t& GetLemonRainRemainTime() { return m_tLemonRainEffectRemainTime; }
    
    bool IsLemonRainEffectRuning() { return m_tLemonRainEffectRemainTime > 0;  }
    
    void UpdateLemonRainEffect();
    
    void SetWaterAcidDamge(float iDamage) { m_iWaterAcidDamge = iDamage; }
    
    void AddVortex(float iX, float iY, float iDelay);

protected:
	void registerForEvents() override;
    
private:
    void addForegroundToRenderQueue(RenderQueue* i_queue);
    void renderForeground(Graphics* i_g);
    
private:
    void onUpdate();
    
    void WaterDamge();
    
private:
    
    pvztime_t   m_tLemonRainEffectRemainTime;
    
    float       m_iWaterAcidDamge;
    
    pvztime_t   m_tDtTime;
};

class BeachStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(BeachStageProperties, StageModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return BeachStage::StaticGetClass();
	}

	BeachStageProperties()
	{
	}
};

/**
 ** Low Tide Stage Event
 **/

class BeachStageEventZombieSpawner : public ZombieSpawnerAction
{
	RT_CLASS_DEFINE(BeachStageEventZombieSpawner, ZombieSpawnerAction, RtClass);
public:
	BeachStageEventZombieSpawner()
	{
		// Do nothing.
	}

	virtual void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand &i_random) override;
	virtual void WaveUpdate(int i_waveNumber, MTRand &i_random) override;
	virtual void WaveEnd(int i_waveNumber, MTRand &i_random) override;

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	virtual void GetZombies(std::vector<const ZombieType*> &o_zombies) override;
	virtual void SetLoot(const std::vector<Loot> &i_loot) override;

private:
	virtual void initializeAction(MTRand &i_random, int i_waveNumber) override;
	void spawnZombies(int i_count, int i_waveNumber, MTRand &i_random);
	int calculateNextRowToSpawnIn();
	void spawnWaveEffect();

	std::vector<Loot> m_zombieLoot;
	pvztime_t m_nextGroupTime = PVZ_EOT();
	pvztime_t m_fullSpawnTime = PVZ_EOT();
	int m_zombiesSpawned = 0;
	int m_nextRowToSpawnIn = 0;
};

class BeachStageEventZombieSpawnerProps : public ZombieSpawnerActionProps
{
	RT_CLASS_DEFINE(BeachStageEventZombieSpawnerProps, ZombieSpawnerActionProps, RtClass);
public:

	BeachStageEventZombieSpawnerProps()
	: GroupSize(1)
	, ZombieCount(1)
	, TimeBetweenGroups(1.0f)
	, TimeBeforeFullSpawn(PVZ_EOT())
	, ColumnStart(5)
	, ColumnEnd(8)
	{
		WaveStartMessage = "[WARNING_LOW_TIDE]";
	}

	virtual RtClass* GetActionClass() const override
	{
		return BeachStageEventZombieSpawner::StaticGetClass();
	}

	virtual void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) override;

	std::string GetZombieName() const;
	SexyString GetWaveStartMessage() const;

	int GroupSize;
	int ZombieCount;
	pvztime_t TimeBetweenGroups;
	pvztime_t TimeBeforeFullSpawn;
	int ColumnStart;
	int ColumnEnd;
	std::string ZombieName;
	std::string WaveStartMessage;
};

#endif /* defined(__PlantsVersusZombies2__BeachStage__) */
