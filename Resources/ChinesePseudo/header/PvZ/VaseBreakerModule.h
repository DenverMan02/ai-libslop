//
//  VaseBreakerModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/24/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__VaseBreakerModule__
#define __PlantsVersusZombies2__VaseBreakerModule__

#include "LevelModule.h"
#include "PVZTypes.h"
#include "ObjectTypeDescriptor.h"
#include "Curve.h"
#include "VictoryOutro.h"
#include "NetworkData.h"

class VaseBreakerModule;

class VaseBreakerProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(VaseBreakerProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	virtual void ConfigureModule(VaseBreakerModule* i_module) const
	{
		// Must be implemented by a derived class
		DBG_HALT();
	}

	virtual bool UseEndlessFlow() const
	{
		return false;
	}

	VaseBreakerProperties()
	{}
};

struct VaseContentProperties
{
	VaseContentProperties()
		: Count(1)
	{}

	std::string ZombieTypeName;
	std::string PlantTypeName;
	std::string CollectableTypeName;
	int Count;
};

class VaseBreakerPresetProperties : public VaseBreakerProperties
{
public:
	RT_CLASS_DEFINE(VaseBreakerPresetProperties, VaseBreakerProperties, RtClass);

	VaseBreakerPresetProperties()
		: MinColumnIndex(5)
		, MaxColumnIndex(8)
		, NumColoredPlantVases(0)
		, NumColoredZombieVases(0)
	{
        PowerUpTutorial = "";
    }

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void ConfigureModule(VaseBreakerModule* i_module) const override;

	int MinColumnIndex;
	int MaxColumnIndex;

	std::vector<VaseContentProperties> Vases;

	int NumColoredPlantVases;
	int NumColoredZombieVases;
	
	std::vector<Point> GridSquareBlacklist;
    
    std::string        PowerUpTutorial;
};

struct VaseBreakerEndlessStarZombiePlantPair
{
	std::string ZombieType;
	std::string PlantType;
};

struct VaseBreakerEndlessEntityAndCountPair
{
	std::string Type;
	int Count;
};

struct VaseBreakerEndlessStage
{
	VaseBreakerEndlessStage()
		: StartingLevel(-1)
		, EscalationRate(0)
		, MinColumnIndex(0)
		, MaxColumnIndex(0)
		, NumberOfColoredPlants(0)
	{}

	int StartingLevel;

	// Number of completed levels between escalations
	int EscalationRate;

	// Min/Max column count
	int MinColumnIndex;
	int MaxColumnIndex;

	// Colorization
	int NumberOfColoredPlants;

	std::vector<VaseBreakerEndlessEntityAndCountPair> PlantTypes;
	std::vector<VaseBreakerEndlessEntityAndCountPair> CollectableTypes;
	std::vector<VaseBreakerEndlessEntityAndCountPair> FixedZombieTypes;
	std::vector<VaseBreakerEndlessEntityAndCountPair> EscalatingZombieTypes;

	void GetZombieTypesForEscalationCount(int i_escalations, std::vector<std::string>& o_zombieTypeNames) const;
};

class VaseBreakerEndlessProperties : public VaseBreakerProperties
{
public:
	RT_CLASS_DEFINE(VaseBreakerEndlessProperties, VaseBreakerProperties, RtClass);

	VaseBreakerEndlessProperties()
		: TestEndlessLevel(0)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	void ConfigureModule(VaseBreakerModule* i_module) const override;

	bool UseEndlessFlow() const override;

	// For testing purposes, if this is set we pretend we are at this level
	int TestEndlessLevel;

	// Only one of these right now, eventually they will be picked from a list every X levels
	VaseBreakerEndlessStarZombiePlantPair StarZombieAndPlantPair;

	std::vector<VaseBreakerEndlessStage> Stages;

private:
	const VaseBreakerEndlessStage& getStageForLevel(int i_level) const;
	int getEscalationCountForLevel(int i_level) const;
};


struct VaseConfiguration
{
	VaseConfiguration()
		: ColorByContentType(false)
	{}

	VaseConfiguration(RtWeakPtr<ObjectTypeDescriptor> i_contentType, bool i_colorByContentType)
		: Contents(i_contentType)
		, ColorByContentType(i_colorByContentType)
	{}

	RtWeakPtr<ObjectTypeDescriptor> Contents;
	bool ColorByContentType;
};

struct New_S2C_Reward
{
    int32 itemId = 0;
    int32 amount = 0;
};

class New_S2C_GiftBoxReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_GiftBoxReward, INetworkData, RtClass);

    std::vector<New_S2C_Reward>   m_rewardInfos;
};

class VaseBreakerVictoryOutroModule : public VictoryOutroModule
{
public:
    RT_CLASS_DEFINE(VaseBreakerVictoryOutroModule, VictoryOutroModule, RtClass);

protected:
    virtual void registerForEvents() override;
    void onCollectableFinishCollected(class Collectable* i_collectable) override;
private:
    void requestGiftBoxReward();
    void onResultClosed();
};

class VaseBreakerVictoryOutroProperties : public VictoryOutroProperties
{
public:
    RT_CLASS_DEFINE(VaseBreakerVictoryOutroProperties, VictoryOutroProperties, RtClass);

	RtClass* GetModuleClass() const override
    {
        return VaseBreakerVictoryOutroModule::StaticGetClass();
    }
};

class VaseBreakerModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(VaseBreakerModule, LevelModule, RtClass);

	VaseBreakerModule();

	void GatherDependentModulePropertySheets(std::vector<LevelModulePropertiesPtr>& io_dependent) override;
    
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	int GetCurrentEndlessWave() const;
	bool ForceStartEndlessAtWave(int i_wave);

	void ConfigureVasesFromPropertySheet();
	void SpawnVases();

	void StartVaseBreakerGameplay();

	void SetVaseSpawnInfo(int i_minIndex, int i_maxIndex, const std::vector<Point>& i_gridSquareBlacklist);
	void AddVase(const VaseConfiguration& i_config);
	class GridItemVase* SpawnVaseImmediately(const VaseConfiguration& i_config, const Point& i_gridLoc);

	void RevealAllContents();
	void HideAllContents();

	const std::vector<RtWeakPtr<class GridItemVase> > &GetVases() const;

    std::string GetPowerUpTutorial();
    
protected:
	void registerForEvents() override;
	void postInitialize() override;

private:
	class GridItemVase* spawnVase(const Point& i_gridLoc) const;
	void onUpdate();
	void onClearBoard();
	void onLoadComplete();
    void gameplayStarted();
	bool checkWinCondition();
	bool checkPreventSave();
	bool isCurrentWaveComplete();
    
    void bringUpPowerupChooser();
    bool checkWhetherCukeShouldBeUnlocked() const;

	// Vase configuration
	int m_minColumnIndex;
	int m_maxColumnIndex;
	std::vector<VaseConfiguration> m_vaseConfigurations;

	// Runtime state
	std::vector<RtWeakPtr<class GridItemVase> > m_vases;
	RtWeakPtr<class VaseBreakerFlowModule> m_flowModule;
	RtWeakPtr<class VaseBreakerArcadeModule> m_arcadeModule;
	bool m_betweenEndlessWaves;
	bool m_haveStartedEndless;
	std::vector<Point> m_gridSquareBlacklist;
};

namespace Message
{
	void VaseBreakerEndlessWaveComplete();
}

#endif /* defined(__PlantsVersusZombies2__VaseBreakerModule__) */
