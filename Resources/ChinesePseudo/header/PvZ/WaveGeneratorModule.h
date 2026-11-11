//
//  WaveGeneratorModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WaveGeneratorModule_h
#define PlantsVersusZombies2_WaveGeneratorModule_h

#include "LevelModule.h"
#include "LevelDefinition.h"
#include "Core.h"
#include "Loot.h"
#include "GameNotify.h"
// WaveGenerator.h only included for enum RowSpawnType since we aren't using C++11 options
// for Apple's LLVM compiler
#include "WaveGenerator.h"

class WaveGeneratorModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(WaveGeneratorModule, LevelModule, RtClass);

	WaveGeneratorModule()
	{
		m_waveGenerator = NULL;
	}
	
	virtual void AddResourceRequirements(std::set<std::string> &io_resGroupNames) override;
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
	class WaveGenerator* GetWaveGenerator();
	virtual bool GetIsDoneSpawning();
	
	virtual bool Serialize(const Sexy::RtSerializeContext &inContext) override;
	
protected:
	void onLevelInit();
	virtual void onPostLoad() override;
	void onLoadComplete();
	void onGameplayStarted();
	void onUpdate();
	void onLevelEnded();
	void onZombieSpawned(class Zombie* i_zombie);
	void onSandStormSpawned(class Zombie* i_zombie);
	void onSandStormDestroyed(class Zombie* i_zombie);
	
private:
	class WaveGenerator* m_waveGenerator;
};

struct ZombieSpawnData
{
	RowSpawnType		Row;
	bool				HasPlantFood;
	Loot				LootDrop;
	int					Level;
	
	// this needs to be run through RtDb::GetDb()->ResolveNamedId()
	// in order for it to match ZombieTypePtrs from ZombieTypeMgr
	// FixupData does this, and should already be called.
	ZombieTypePtr		Type;
    
    int Rise_GridX;
	int Rise_GridY;
    
    int SunDrop;
    int BesiegeHit;
    float ZombieRate;
    float ZombieScale;
    
    pvztime_t TargetValidTime;
	
	ZombieSpawnData()
	{
		Row = ROWSPAWN_RANDOM;
		HasPlantFood = false;
		LootDrop = LOOT_None;
		Level = 1;
        
        Rise_GridX = 0;
        Rise_GridY = 0;
        
        SunDrop = 0;
        ZombieRate = 0.f;
        ZombieScale = 1.f;
        BesiegeHit = 1;
        
        TargetValidTime = 1.5f;
	}
	
	void FixupData();
};

struct ZombiePoolData
{
	int					Cost;
	int					Weight;
	bool				Overridden;

	// this needs to be run through RtDb::GetDb()->ResolveNamedId()
	// in order for it to match ZombieTypePtrs from ZombieTypeMgr
	// FixupData does this, and should already be called.
	ZombieTypePtr		Type;
	
	ZombiePoolData()
	{
		Cost = -1;
		Weight = -1;
		Overridden = false;
	}
	
	void FixupData();
};

struct WaveEventData
{
	bool							Enabled;
	int								Count;
	int								TimeSpread;
	int								Waves;
	
	WaveEventData()
	{
		Enabled = false;
		Count = -1;
		TimeSpread = 0;
		Waves = -1;
	}
};

struct PlantPoolData
{
	int             Weight;
	int             MaxCount;
	bool			MaxCountIncludesPlanted;
    int             iLevel; //-1 means use playerinfo's data, otherwise use the json's data
    int             iAvatar; //-1 means use playerinfo's data, 0 means unenable, 1 means enable
	
	// this needs to be run through RtDb::GetDb()->ResolveNamedId()
	// in order for it to match PlantTypePtrs from PlantTypeMgr
	// FixupData does this, and should already be called.
	PlantTypePtr	Type;
	
	PlantPoolData()
	{
		Weight = 1000;
		MaxCount = 0;
		MaxCountIncludesPlanted = false;
        iLevel = -1;
        iAvatar = -1;
	}
	
	void FixupData();
};

struct WaveDefinition
{
	bool							DisableRandomSpawns;
	bool							WaitUntilAllZombiesDie;
	
	int 							ColNumPlantIsDragged;
	int								SpawnColStart;
	int								SpawnColEnd;
	int								SpawnPlantFoodCount;
	
	int								WavePointStart;
	int								WavePointIncrement;
	bool							WavePointOverride;
    
    pvztime_t                       WaveSpawnTime;
	
	WaveEventData					Event;
	std::vector<ZombieSpawnData>	Zombies;
	std::vector<ZombiePoolData>		AddToZombiePool;
	std::vector<ZombiePoolData>		RemoveFromZombiePool;
	std::vector<PlantPoolData>		AddToSeedPool;
	std::vector<PlantPoolData>		RemoveFromSeedPool;
	
	WaveDefinition()
	{
		DisableRandomSpawns = false;
		WaitUntilAllZombiesDie = false;
		ColNumPlantIsDragged = 0;
		SpawnColStart = -1;
		SpawnColEnd = -1;
		SpawnPlantFoodCount = 0;
		WavePointStart = -1;
		WavePointIncrement = -1;
		WavePointOverride = false;
        WaveSpawnTime = 2.0f;
	}

	void FixupData();
};

class WaveGeneratorProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(WaveGeneratorProperties, LevelModuleProperties, RtClass);

	WaveGeneratorProperties()
	{
		//RtName defaultAlias(L"DefaultHeroLevelProps");
		//RtName defaultPackage(L"HeroTypes");
        
		FlagWaveInterval = -1;
		WaveCount = -1;
		WaveSpendingPointIncrement = -1;
		WaveSpendingPoints = -1;
		SpawnColStart = -1;
		SpawnColEnd = -1;
		IgnoreFlagCarriers = false;
        IsRiseFromGroundMode = false;
	}

	virtual RtClass* GetModuleClass() const override
	{
		return WaveGeneratorModule::StaticGetClass();
	}
	
	void FixupData();
    
	std::vector<WaveDefinition> Waves;
	std::vector<ZombiePoolData> ZombiePool;
	int FlagWaveInterval;
	int WaveCount;
	int WaveSpendingPointIncrement;
	int WaveSpendingPoints;
	int SpawnColStart;
	int SpawnColEnd;
	int SpawnCount;
	bool IgnoreFlagCarriers;
    bool IsRiseFromGroundMode;
};

#endif
