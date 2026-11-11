//
//  ProtectThePlantChallenge.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ProtectThePlantChallenge_h
#define PlantsVersusZombies2_ProtectThePlantChallenge_h

#include "ChallengeModule.h"
#include "LevelModule.h"
#include "Core.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "Plant.h"
#include "TodStringFile.h"

struct SpawnedPlant
{
	SpawnedPlant()
	{
		m_renderRig = NULL;
	}
	
	SpawnedPlant(PlantPtr i_plant, Sexy::Point i_gridLoc)
	{
		m_plant = i_plant;
		m_gridLoc = i_gridLoc;
		m_renderRig = NULL;
	}
	PlantPtr m_plant;
	Sexy::Point m_gridLoc;
	PopAnimRig* m_renderRig;

	void DrawTile(Graphics* i_g);
	void SyncTile();
};

class ProtectThePlantChallengeModule : public Challenge
{
public:
	RT_CLASS_DEFINE(ProtectThePlantChallengeModule, Challenge, RtClass);

    std::vector<SpawnedPlant> GetSpawnedPlants() { return m_spawnedPlants; }
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	SexyString GetProgressDescription() const override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
	bool isWaitingForLastStand();

private:
	void spawnPlants();
	bool hasFailed();
	void onLoadComplete();
    void onGameplayStarted();
    void onGameplayEnded();
	void onUpdate();
	bool checkWinCondition();
	void cleanUp();
	virtual void onPostLoad() override;
	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	
    void onPlantDied(Plant* i_plant);
    void onPlantConvertedToProjectile(Plant* i_plant);
    void failChallenge(Plant* i_plant);
    void handlePlantLoss(Plant* i_plant);

    void addToRenderQueue(class RenderQueue* i_queue);
	
	std::vector<SpawnedPlant> m_spawnedPlants;
	
	RtWeakPtr<class PopAnimRig> m_protectTileRig;
};

struct ProtectedPlantEntry
{
	ProtectedPlantEntry()
	{
		GridX = GridY = 0;
	}
	
	std::string PlantType;
	int GridX;
	int GridY;
};

class ProtectThePlantChallengeProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ProtectThePlantChallengeProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return ProtectThePlantChallengeModule::StaticGetClass();
	}
	
	SexyString GetDescription() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PROTECT_THE_PLANT]"));
	}

	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[STARCHALLENGE_PROTECT_THE_PLANT_NAME]"));
	}

	ProtectThePlantChallengeProperties()
	{
		MustProtectCount = 0; // Means 'all of them'
		IsPlantDefenceMode = false;
	}
	
	std::vector<ProtectedPlantEntry> Plants;
	int MustProtectCount;
	bool IsPlantDefenceMode;
};

#endif
