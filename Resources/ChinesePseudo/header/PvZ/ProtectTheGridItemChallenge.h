//
//  ProtectTheGridItemChallenge.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ProtectTheGridItemChallenge_h
#define PlantsVersusZombies2_ProtectTheGridItemChallenge_h

#include "ChallengeModule.h"
#include "LevelModule.h"
#include "Core.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "Plant.h"
#include "GridItem.h"
#include "TodStringFile.h"

struct SpawnedGridItem
{
	SpawnedGridItem()
	{
		m_renderRig = NULL;
	}

	SpawnedGridItem(GridItemPtr i_gridItem, Sexy::Point i_gridLoc)
	{
		m_gridItem = i_gridItem;
		m_gridLoc = i_gridLoc;
		m_renderRig = NULL;
	}
	GridItemPtr m_gridItem;
	Sexy::Point m_gridLoc;
	PopAnimRig* m_renderRig;

	void DrawTile(Graphics* i_g);
	void SyncTile();
};

class ProtectTheGridItemChallengeModule : public Challenge
{
public:
	RT_CLASS_DEFINE(ProtectTheGridItemChallengeModule, Challenge, RtClass);

    std::vector<SpawnedGridItem> GetSpawnedGridItems() { return m_spawnedGridItems; }
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	SexyString GetProgressDescription() const override;

protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;

	bool isWaitingForLastStand();

private:
	void spawnGridItems();
	bool hasFailed();
	void onLoadComplete();
    void onGameplayStarted();
    void onGameplayEnded();
	void onUpdate();
	bool checkWinCondition();
	void cleanUp();
	virtual void onPostLoad() override;
//	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);

	void onGridItemDestroyed(const std::string& i_gridItemType);
//    void onPlantConvertedToProjectile(Plant* i_plant);
//    void failChallenge(GridItem* i_gridItem);
    void handleGridItemLoss(const std::string& i_gridItemType);

    void addToRenderQueue(class RenderQueue* i_queue);

	std::vector<SpawnedGridItem> m_spawnedGridItems;

	RtWeakPtr<class PopAnimRig> m_protectTileRig;
};

struct ProtectedGridItemEntry
{
	ProtectedGridItemEntry()
	{
		GridX = GridY = 0;
	}

	std::string GridItemType;
	int GridX;
	int GridY;
};

class ProtectTheGridItemChallengeProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ProtectTheGridItemChallengeProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ProtectTheGridItemChallengeModule::StaticGetClass();
	}

	SexyString GetDescription() const override
	{
		return TodStringTranslate(StringToSexyStringFast(Description));
	}

	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(StringToSexyStringFast(DescriptiveName));
	}

	ProtectTheGridItemChallengeProperties()
	{
		MustProtectCount = 0; // Means 'all of them'
//		IsPlantDefenceMode = false;
		Description = "Description";
		DescriptiveName = "DescriptiveName";
	}

	std::vector<ProtectedGridItemEntry> GridItems;
	int MustProtectCount;
	std::string Description;
	std::string DescriptiveName;
//	bool IsPlantDefenceMode;
};

#endif
