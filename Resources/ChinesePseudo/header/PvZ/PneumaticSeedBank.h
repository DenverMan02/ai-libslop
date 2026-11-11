//
//  PneumaticSeedBank.h
//  PlantsVersusZombies2
//
//  Created by David Siems 1/24/13
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PNEUMATICSEEDBANK_H__
#define __PNEUMATICSEEDBANK_H__

#include "SeedBank.h"
#include "SeedBankModule.h"
#include "Effect_PopAnim.h"
#include "TimeLine.h"

class WaveDefinition;

struct PacketInterpolation
{
	float StartY;
	SeedPacketPtr Packet;
	pvztime_t T;
};

class PneumaticSeedBank : public SeedBankNew
{
public:
	RT_CLASS_DEFINE(PneumaticSeedBank, SeedBankNew, RtClass);

	PneumaticSeedBank();
	virtual ~PneumaticSeedBank();

	virtual void Draw(Graphics* i_g) override;
	virtual void InitializePacketTimers() override;
	virtual void SetSeedBankProperties(RtWeakPtr<const class SeedBankProperties> i_propertySheet) override;
	virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

	bool IsInitialized() const;
	void AddSeedToSeedPool(const struct PneumaticPlantEntry& i_plantEntry);
	void RemoveSeedFromSeedPool(const std::string& i_plantTypeName);

	void SetPause(bool i_paused);

	void SpawnSeedPacket();
	void SetSeedTimer(pvztime_t i_time);
	void Start();

	void ForceSpawn(const std::string& i_objectType);
	
protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

private:

	OVERRIDE_STATE_UPDATE(WidgetState, Initializing);
	OVERRIDE_STATE_ONENTER(WidgetState, Ready);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	virtual void onNewWave(int i_waveIndex, const WaveDefinition *i_currentDefinition) override;
    virtual void onSeedPacketPlanted(class SeedPacket* i_packet) override;
    
	void onLevelStart();
	void onLevelEnd();
	void onPowerupDeactivated(class BasePowerup* i_powerup);
	void onLevelRewardDropped();
	void onValveCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params);

	void onDrawBack(Graphics* i_g);
	void onDrawValve(Graphics* i_g);
	void onDrawFront(Graphics* i_g);

	void cancelEffectCompletion(StandaloneEffect* i_effect);

	const std::string& pickSeed();
	void spawnSeedPacket(const std::string& i_item);
	void resetSeedTimer();
	int getCountOfTypeSpawned(const std::string& i_seedType);

	void addItem(const std::string &i_objectType);
	void addSeed(const PlantTypePtr i_seedType);
	void addTool(const std::string& i_toolType);
	void addPowerup(const std::string& i_powerupType);

	/// Serialized
	
	pvztime_t m_seedPickTime;
	std::vector<struct PneumaticPlantEntry>	m_seedPool;
	std::vector<int> m_recentPicks;

	std::vector<PacketInterpolation> m_packetInterpolation;
	RtWeakPtr<Effect_PopAnim> m_front;
	RtWeakPtr<Effect_PopAnim> m_back;
	RtWeakPtr<Effect_PopAnim> m_valve;
	
	std::string m_packetAwaitingLaunch;

	bool m_paused;

	/// Transient
	
	TimeLineTrack<float> m_settleTrack;
};

struct PneumaticPlantEntry
{
	std::string PlantType;
	int Weight;
	int MinCount;
	float MinWeightFactor;
	int MaxCount;
	float MaxWeightFactor;
	
	PneumaticPlantEntry()
	{
		Weight = 1000;
		MinCount = 0;
		MinWeightFactor = 10.0f;
		MaxCount = 0;
		MaxWeightFactor = 0.1f;
	}
};

struct PneumaticDelayCondition
{
	int MaxPackets;
	float Delay;
	
	PneumaticDelayCondition()
	{
		MaxPackets = 0;
		Delay = 5.0f;
	}
};

class PneumaticSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(PneumaticSeedBankProperties, SeedBankProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return SeedBankModule::StaticGetClass();
	}
	
	virtual SeedBankType GetBankType() const override
	{
		return SEEDBANK_PNEUMATIC;
	}
	
	PneumaticSeedBankProperties()
	{
		ManualPacketSpawning = false;
		SelectionMethod = SEEDBANKSELECT_PRESET;
	}
	
	bool ManualPacketSpawning;
	
	std::vector<PneumaticPlantEntry> InitialPlantList;	
	std::vector<PneumaticDelayCondition> DelayConditions;
};

namespace Message
{
	void ConveyorPickingSeed();
}

#endif
