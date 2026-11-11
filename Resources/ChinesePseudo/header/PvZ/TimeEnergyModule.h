/*
 * TimeEnergyModule.h
 *
 *  Created on: 2021-8-18
 *      Author: zhousen
 */

#ifndef TIMEENERGYMODULE_H_
#define TIMEENERGYMODULE_H_

#include "LevelModuleManager.h"
#include "ProfileUtils.h"
#include "ReflectionBuilder.h"
#include "SpawnGravestonesWaveAction.h"
#include "Utils.h"

class UISpacetimeEnergy;

namespace Message
{
	void TimeEnergyTrigger(int triggerType);
}


enum TimeEnergyTriggerType
{
	TimeEnergyTrigger_Invalid = -1,
	TimeEnergyTrigger_WormHole,
	TimeEnergyTrigger_Portal,
	TimeEnergyTrigger_BlackHole,
	TimeEnergyTrigger_Max,
};

struct TimeEnergyWormHoleTriggerData : public ObjectTypeDescriptor
{
	RT_CLASS_DEFINE(TimeEnergyWormHoleTriggerData, ObjectTypeDescriptor, RtClass);

	TimeEnergyWormHoleTriggerData() {}
};

struct TimeEnergyPortalTriggerData : public ObjectTypeDescriptor
{
	RT_CLASS_DEFINE(TimeEnergyPortalTriggerData, ObjectTypeDescriptor, RtClass);

	TimeEnergyPortalTriggerData() {
		PortalType = "";
		SpawnEffectAnimID = "";
		SpawnSoundID = "";
		PortalPos.clear();
	}

	std::vector<Sexy::SexyVector2>		PortalPos;
	std::string							PortalType;
	std::string							SpawnEffectAnimID;
	std::string							SpawnSoundID;
};

struct TimeEnergyBlackHoleTriggerData : public ObjectTypeDescriptor
{
	RT_CLASS_DEFINE(TimeEnergyBlackHoleTriggerData, ObjectTypeDescriptor, RtClass);

	TimeEnergyBlackHoleTriggerData() {
		ColNumsPlantIsDrag = -1;
		BlackHoleAnim = "";
	}

	int ColNumsPlantIsDrag;// how many columns plants will be dragged.
	std::string BlackHoleAnim;// black hole anim name
};

struct TimeEnergyTriggerData : public ObjectTypeDescriptor
{
	RT_CLASS_DEFINE(TimeEnergyTriggerData, ObjectTypeDescriptor, RtClass);

	bool IsInTrigger(float value) {
		return value >= TriggerRange.Min && value <= TriggerRange.Max;
	}

	ValueRange  TriggerRange;// the value within range will trigger
	pvztime_t Cooldown;// the cool down time between trigger
	TimeEnergyTriggerType TriggerType;// trigger type
	TimeEnergyWormHoleTriggerData WormHoleProperty;// worm hole
	TimeEnergyPortalTriggerData PortalProperty;// portal
	TimeEnergyBlackHoleTriggerData BlackHoleProperty;// black hole
};

class TimeEnergyModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(TimeEnergyModule, LevelModule, RtClass);

	TimeEnergyModule();
	virtual ~TimeEnergyModule();

	//for achievement
	bool CheckAchievement();
	bool BeatEliteZombie();

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;
	void postInitialize() override;
	void onUpdate();
	void onLoadComplete();
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	void TimeEnergyTriggerCheckUpdate(float ratio);
	void DoTimeEnergyTrigger(TimeEnergyTriggerData data);
	void TriggerWormHole(TimeEnergyWormHoleTriggerData data);
	void TriggerPortal(TimeEnergyPortalTriggerData data);
	void TriggerBlackHole(TimeEnergyBlackHoleTriggerData data);
	void spawnGridItem(Point i_gridLocation, GridItemTypePtr i_type, std::string i_spawnAnimationID, std::string i_spawnSoundID);

	void ReadyGoFinish();
	void SendPost_EndPlay();

	void onPVZ1ModeNetworkResponse(int i_context, int i_status);

	//for achievement
	void achievementOnPlantLost(class Plant* i_plant);
    void achievementOnLilyPadDied(class GridItemLilyPad* i_lilyPad);
	void achievementOnFlowerPotDied(class GridItemFlowerPot* i_flowerPot);
	void achievementHandlePlantDied();
	void achievementZombieDied(class Zombie* i_zombie, const class DamageInfo* i_deathBlow);

private:
	pvztime_t m_triggerCooldownEndTime;
	UISpacetimeEnergy* m_timeEnergyUI;
	std::vector<TimeEnergyTriggerData> m_triggerDataList;
	BlackHolePtr m_blackHole;
	bool m_triggerLose;// check if trigger lose
	std::map<TimeEnergyTriggerType, bool> m_TriggerMap;// trigger animation check.

	//for achievement
	int m_achievementPlantsLostNumber;
	bool m_achievementBeatEliteZombie;
};

class TimeEnergyModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(TimeEnergyModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return TimeEnergyModule::StaticGetClass();
	}

	TimeEnergyModuleProperties() {
		TimeEnergyTriggers.clear();
		TimeEnergyValueMax = 150.0f;
	}

	std::vector<TimeEnergyTriggerData> TimeEnergyTriggers;// time energy event
	float TimeEnergyValueMax;// max value of time energy
};

#endif /* TIMEENERGYMODULE_H_ */
