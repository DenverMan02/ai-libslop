//
//  SeedBankModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SeedBankModule_h
#define PlantsVersusZombies2_SeedBankModule_h

#include "LevelModule.h"
#include "Seedbank.h"
#include "SeedChooser.h"

enum SeedBankSelectionMethod
{
	SEEDBANKSELECT_PRESET,
	SEEDBANKSELECT_CHOOSER,
	SEEDBANKSELECT_BEGHOULED,
	SEEDBANKSELECT_WORLDCUP,
};


/// Normal seed bank!

class SeedBankModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(SeedBankModule, LevelModule, RtClass);

	inline SeedBankPtr		GetSeedBank() const;
	inline SeedChooserPtr	GetSeedChooser() const;
	inline void				RemoveSeedChooser() const;
	
	virtual bool				UsesSeedChooser() const;
	int						GetNumSlotsAvailableForChooser() const;

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
	void ReplaceSeedPacket(std::string i_plantToRemove, std::string i_plantToReplace = "");

	SeedBankSelectionMethod GetSelectionMethod() { return m_selectionMethod; }

    std::vector<std::string> m_availableSeeds;
	
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
protected:
	virtual void			createSeedBank();
	virtual void			onLoadComplete();
	virtual void			onGameStarted();
	virtual void			onLevelEnded();
	int                     getSeedSlotsOverrideCount() const;
	
	SeedBankPtr				m_seedBank;
	SeedChooserPtr			m_seedChooser;
	bool					m_resourcesLoaded;

protected:
	SeedBankSelectionMethod	m_selectionMethod;
	
	//std::vector<std::string> m_availableSeeds;
};

SeedBankPtr SeedBankModule::GetSeedBank() const
{
	return m_seedBank;
}
SeedChooserPtr SeedBankModule::GetSeedChooser() const
{
	return m_seedChooser;
}

void SeedBankModule::RemoveSeedChooser() const
{
	if (m_seedChooser)
	{
		m_seedChooser->Destroy();
	}
}

class SeedBankProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SeedBankProperties, LevelModuleProperties, RtClass); 
	
	virtual RtClass* GetModuleClass() const override
	{
		return SeedBankModule::StaticGetClass();
	}
	
	virtual SeedBankType GetBankType() const
	{
		return SEEDBANK_NORMAL;
	}
	
	SeedBankProperties()
	{
		SelectionMethod = SEEDBANKSELECT_CHOOSER;
		AlwaysUseChooser = false;
        ZombieMode = false;
        GridItemMode = false;
        OverrideSeedSlotsCount = 0;
        GlobalLevel = -1;
	}
	
	SeedBankSelectionMethod		SelectionMethod;
	bool						AlwaysUseChooser;
    bool                        ZombieMode;
    bool                        GridItemMode;
    std::string                 SeedPacketType;
    std::string                 SpecialSeedPacketType;
    std::string                 SeedChooserType;
	
	// Used for preset
	std::vector<std::string>	PresetPlantList;
	
	// Used for Beghouled upgrade swaps
	std::vector<std::string>	BeghouledUpgradeList;

	// Used for auto and chooser
	std::vector<std::string>	PlantWhiteList;
	std::vector<std::string>	PlantBlackList;
	std::string					BlackListLiftedBy;

	int							OverrideSeedSlotsCount;
	int							GlobalLevel;
};

/// Conveyor belt!

struct ConveyorPlantEntry
{
	std::string PlantType;
	int Weight;
	int MinCount;
	float MinWeightFactor;
	int MaxCount;
	float MaxWeightFactor;
    int iLevel; //-1 means use playerinfo's data, otherwise use the json's data
    int iAvatar; //-1 means use playerinfo's data, 0 means unenable, 1 means enable
	
	ConveyorPlantEntry()
	{
		Weight = 1000;
		MinCount = 0;
		MinWeightFactor = 10.0f;
		MaxCount = 0;
		MaxWeightFactor = 0.1f;
        iLevel = -1;
        iAvatar = -1;
	}
};

struct ConveyorSpeedCondition
{
	int MaxPackets;
	float Speed;
	
	ConveyorSpeedCondition()
	{
		MaxPackets = 0;
		Speed = 25.f;
	}
};

struct ConveyorDropDelayCondition
{
	int MaxPackets;
	float Delay;
	
	ConveyorDropDelayCondition()
	{
		MaxPackets = 0;
		Delay = 5.f;
	}
};

class ConveyorSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(ConveyorSeedBankProperties, SeedBankProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return SeedBankModule::StaticGetClass();
	}
	
	virtual SeedBankType GetBankType() const override
	{
		return SEEDBANK_CONVEYOR;
	}
	
	ConveyorSeedBankProperties()
	{
		ManualPacketSpawning = false;
		SelectionMethod = SEEDBANKSELECT_PRESET;
	}
	
	bool ManualPacketSpawning;
	
	std::vector<ConveyorPlantEntry> InitialPlantList;
	
	std::vector<ConveyorSpeedCondition> SpeedConditions;
	std::vector<ConveyorDropDelayCondition> DropDelayConditions;
};

class BeghouledSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(BeghouledSeedBankProperties, SeedBankProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return SeedBankModule::StaticGetClass();
	}

	SeedBankType GetBankType() const override
	{
		return SEEDBANK_BEGHOULED;
	}

	BeghouledSeedBankProperties()
	{
		SelectionMethod = SEEDBANKSELECT_BEGHOULED;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class WorldCupSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(WorldCupSeedBankProperties, SeedBankProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return SeedBankModule::StaticGetClass();
	}

	virtual SeedBankType GetBankType() const override
	{
		return SEEDBANK_WORLDCUP;
	}

	WorldCupSeedBankProperties()
	{
		SelectionMethod = SEEDBANKSELECT_WORLDCUP;
	}
};

class RiftSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(RiftSeedBankProperties, SeedBankProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return SeedBankModule::StaticGetClass();
	}

	virtual SeedBankType GetBankType() const override
	{
		return SEEDBANK_RIFT;
	}

	RiftSeedBankProperties()
	{
		SelectionMethod = SEEDBANKSELECT_CHOOSER;
	}
};

#endif
