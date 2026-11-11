//
//  ConveyorSeedBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 6/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Handles the display of and input on seed packets. Also generates an atlas that the
//  seed packets will use for their images while the game is running (we keep up to 10 plants
//  in memory for their seed packet images, instead of the full roster.
//

#ifndef __CONVEYORSEEDBANK_H__
#define __CONVEYORSEEDBANK_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "SeedBank.h"
#include "SeedPacket.h"
#include "ProbabilitySet.h"
#include "Wave.h"

class SeedPacket;
class WaveDefinition;
struct PlantListItem;

static const int CONVEYOR_PACKET_OFFSET_X = 51; 
static const int CONVEYOR_PACKET_MIN_OFFSET = 8;
static const int CONVEYOR_MAX_RECENT_ITEMS_FOR_WEIGHTING = 5;

class ConveyorSeedBank : public SeedBankNew
{
	
public:
	RT_CLASS_DEFINE(ConveyorSeedBank, SeedBankNew, RtClass);
	
	ConveyorSeedBank();
	virtual ~ConveyorSeedBank();
	
	// Public Interface (Inheritable)
	
	virtual void					Draw(Graphics* i_g) override;
	virtual void					InitializePacketTimers() override;
	virtual void					SetSeedBankProperties(RtWeakPtr<const class SeedBankProperties> i_propertySheet) override;
	
	// Public Interface (Core)
	const bool						GetIsInitialized();
	const int						GetCountOfTypeOnConveyorBelt(const struct ConveyorPlantEntry& i_plantListItem);
	void							AddSeedToConveyorSeedPool(const struct ConveyorPlantEntry& i_plantListItem);
	void							RemoveSeedFromConveyorSeedPool(const struct ConveyorPlantEntry& i_plantListItem);

	void							PauseBelt(bool i_isPaused);
	
	// used to get specific external control of the conveyor
	void							SetSeedPickTimer(pvztime_t i_time);
	void							PickAndAddSeedFromSeedPool();
	void							StartConveyor();
	void 							ForceSpawn(const std::string& i_objectType);

    bool                          HasPlant(const std::string& i_objectType) override;
	
protected:

	// Protected Interface (Inheritable)
	virtual void onVisibleStateChange(bool i_visible) override;

	
	OVERRIDE_STATE_UPDATE(WidgetState, Initializing);
	OVERRIDE_STATE_ONENTER(WidgetState, Ready);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
	virtual void					initialize(const uint8 i_packetCount = 0) override;
	virtual void					initLoadingResourcesGroupList() override;
	virtual void					registerForEvents() override;
	
	virtual void					onNewWave(int i_waveIndex, const WaveDefinition* i_currentDefinition) override;
    virtual void					onSeedPacketPlanted(SeedPacket* i_packet) override;
	virtual void					onLevelStart();
	virtual void					onLevelRewardDropped();
	virtual void					onPowerupDeactivated(class BasePowerup* i_powerup);
	
	virtual void					setPacketPositions() override;
	
	void onAddSeed(const class ConveyorAddSeedInstruction &i_instruction);
	void onRemoveSeed(const class ConveyorRemoveSeedInstruction &i_instruction);
	// Protected Interface (core)

	SeedPacketPtr					addItemToBelt(const std::string& i_objectType, bool i_isPushedToFront);
	SeedPacketPtr					addSeedToBelt(const PlantTypePtr i_seedType, bool i_isPushedToFront);
	SeedPacketPtr					addToolToBelt(const std::string& i_toolType, bool i_isPushedToFront);
	SeedPacketPtr					addPowerupToBelt(const std::string& i_powerupType, bool i_isPushedToFront);
	void							removeSeedFromBelt(const SeedPacketPtr i_seedPacket);

	void							pickAndAddSeedFromSeedPool();
	ProbabilitySet<int>				createSeedProbabilitySet();
	void							resetSeedPickTimer();
	void							resetConveyorSpeed();

	// Protected Members (serialized)

	int								m_maxConveyorItems;
	std::vector<float>				m_conveyorBeltOffsetX;
	std::vector<float>				m_conveyorBeltOffsetY;
	float							m_conveyorSpeed;
	pvztime_t						m_seedPickTime;

	std::vector<struct ConveyorPlantEntry>	m_conveyorSeedPool;

	// Protected Members (not serialized)

	float							m_conveyorOffset;
    int								m_defaultPacketOffsetX;

private:

	// Private Interface
	void							onGamePaused();
	void							onGameUnpaused();

	// Private Members (serialized)
	bool							m_isPaused;
	std::vector<int>				m_recentPicks;

	// Private Members (not serialized)

};

typedef RtWeakPtr<ConveyorSeedBank> ConveyorSeedBankPtr;

//
// ModifyConveyorWaveAction
// Adds or removes a seed packet to the conveyor's bank.
//
class ModifyConveyorWaveAction : public WaveAction
{
	RT_CLASS_DEFINE(ModifyConveyorWaveAction, WaveAction, RtClass);

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

public:
	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand &i_random) override;

protected:
	void registerForEvents() override;

private:
	void gatherSeedBankPlantTypes(std::set<PlantTypePtr>* io_plantTypes);
};

struct ConveyorAddSeedInstruction
{
	ConveyorAddSeedInstruction()
	: Weight(1000)
	, MaxCount(0)
	, MinCount(0)
	, MaxDelivered(-1)
	, MinWeightFactor(0.1f)
	, MaxWeightFactor(10.0f)
	, MaxCountCooldownSeconds(0)
    , iLevel(-1)
    , iAvatar(-1)
	{
		// Do nothing.
	}

	PlantTypePtr Type;
	std::string ToolType;
	int Weight;
	int MaxCount;
	int MinCount;
	int MaxDelivered;
	float MinWeightFactor;
	float MaxWeightFactor;
	float MaxCountCooldownSeconds;
    int iLevel; //-1 means use playerinfo's data, otherwise use the json's data
    int iAvatar; //-1 means use playerinfo's data, 0 means unenable, 1 means enable
};

struct ConveyorRemoveSeedInstruction
{
	PlantTypePtr Type;
	std::string ToolType;
};

class ModifyConveyorWaveActionProps : public WaveActionProperties
{
	RT_CLASS_DEFINE(ModifyConveyorWaveActionProps, WaveActionProperties, RtClass);
public:

	virtual RtClass *GetActionClass() const override
	{
		return ModifyConveyorWaveAction::StaticGetClass();
	}

	std::vector<ConveyorAddSeedInstruction> Add;
	std::vector<ConveyorRemoveSeedInstruction> Remove;
};


//
// Messages
//
namespace Message
{
	void ConveyorPickingSeed();
	void ConveyorAddSeed(const ConveyorAddSeedInstruction &i_instruction);
	void ConveyorRemoveSeed(const ConveyorRemoveSeedInstruction &i_instruction);
}

#endif // __CONVEYORSEEDBANK_H__
