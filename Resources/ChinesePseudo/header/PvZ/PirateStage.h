//
//  PirateStage.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PirateStage_h
#define PlantsVersusZombies2_PirateStage_h

#include "StageModule.h"
#include "WaveActionSpawnZombies.h"
#include "Zombie.h"
#include "BoardRegion.h"

class PirateStage : public StageModule
{
public:
	RT_CLASS_DEFINE(PirateStage, StageModule, RtClass);
    
    bool CanGraveStoneSpawnAt(int i_gridX, int i_gridY) override;
	bool CanZombieSpawnInRow(int i_row, ZombieTypePtr i_type) override;

    void InitPlanks(const std::vector<int>& i_plankLocations);
	bool IsPlankOnRow(int i_row);
    void ShowGuides(bool i_show);
    
    int GetPlankStartGridColumn() const;
	void DropZombieInOcean(ZombiePtr i_zombie);
	void SpawnWaterSplashEffect(SexyVector2 i_splashPoint, int i_renderOrder);

protected:
    
    void initializeModule() override;
    void registerForEvents() override;
    void renderBackground(Graphics* i_g) override;
    
	virtual void onZombieTypeCountChange(ZombieTypePtr i_type, int i_from, int i_to) override;
	virtual void stopZombieGroans() override;

private:
	void onLoadComplete();
	void onUpdate();
	void onLevelEnded();
    
    void onGameplayStart();
    void onGameplayEnd();
    void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	
	void generatePlanks();
	
	std::vector<int32> m_planks;
	
	PopAnimRigPtr m_foamRightAnim;
	PopAnimRigPtr m_foamLeftAnim;
	
	PopAnimRigPtr m_breakerRightAnim;
	pvztime_t	m_nextRightBreaker;
	SexyVector2 m_currRightBreakerPos;
	
	PopAnimRigPtr m_breakerLeftAnim;
	pvztime_t	m_nextLeftBreaker;
	SexyVector2 m_currLeftBreakerPos;
	
	bool		m_showingGuides;
    
    // AUDIO
    bool        m_playingCaptainAudio;
};

class PirateStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(PirateStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PirateStage::StaticGetClass();
	}
	
	PirateStageProperties()
	{
		BreakerInterval = 5.f;
	}
	
    float BreakerInterval;
    PlantRestrictionSet PlantsWhichCannotBePlantedOnPlanks;
};

class BoardRegionDeepWater : public BoardRegion
{
public:
	RT_CLASS_DEFINE(BoardRegionDeepWater, BoardRegion, RtClass);
    
	BoardRegionDeepWater();
    
	// For the Pirate stage, anything that falls in to the water near the left or right
	// boundaries should have its splash effect offset a little bit away from the edge.
	// This keeps the splash animation from overlapping with the deck of the pirate ship.
	void SetSplashHorizontalMinDistances(float i_leftSplashMinDistance, float i_rightSplashMinDistance);
    
	void DoEntityEnteredEffects(const SexyVector3& i_boardLocation, class BoardEntity* i_enteringEntity) override;
    
private:
	float m_leftSplashMinDistance;
	float m_rightSplashMinDistance;
};

class RaidingPartyZombieSpawner : public ZombieSpawnerAction
{
	RT_CLASS_DEFINE(RaidingPartyZombieSpawner, ZombieSpawnerAction, RtClass);
public:
	RaidingPartyZombieSpawner()
	: m_swashbucklersSpawned(0)
	, m_nextGroupTime(PVZ_EOT())
	, m_fullSpawnTime(PVZ_EOT())
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
	void createZombies(int i_waveNumber, MTRand &i_random, int i_startIndex, int i_stopIndex);
	void spawnGroup(int i_count, int i_waveNumber, MTRand &i_random);
	void spawnAllTheThings(int i_waveNumber, MTRand &i_random);
    
	std::vector<Loot> m_zombieLoot;
	std::vector<Sexy::Point> m_swashbucklerTargets;
	int m_swashbucklersSpawned;
	pvztime_t m_nextGroupTime;
	pvztime_t m_fullSpawnTime;
};

class RaidingPartyZombieSpawnerProps : public ZombieSpawnerActionProps
{
	RT_CLASS_DEFINE(RaidingPartyZombieSpawnerProps, ZombieSpawnerActionProps, RtClass);
public:
    
	RaidingPartyZombieSpawnerProps()
	: SwashbucklerCount(0)
	, GroupSize(1)
	, TimeBetweenGroups(1.0f)
	, TimeBeforeFullSpawn(PVZ_EOT())
	{
		// Do nothing.
	}
    
	virtual RtClass* GetActionClass() const override
	{
		return RaidingPartyZombieSpawner::StaticGetClass();
	}
    
	virtual void GatherSpawnedZombieTypes(std::set<const class ZombieType*> &o_zombies) override;
    
	int SwashbucklerCount;
	int GroupSize;
	pvztime_t TimeBetweenGroups;
	pvztime_t TimeBeforeFullSpawn;
};

namespace Message
{
	void ZombieInOcean(Zombie* i_zombie);
	void ZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
}

#endif
