//
//  RiftSchedule.hpp
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/5/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef RiftSchedule_h
#define RiftSchedule_h

#include "PennyPerkMgr.h"
#include "PropertySheetBase.h"
#include "RiftFirstClearRewards.h"

class PerkProgressionReward
{
public:
	PerkProgressionReward()
	{
		Perk = "";
		Level = 0;
		Threshold = 0;
	}
	
	std::string Perk;
	int Level;
	int Threshold;
};

class PerkProgressionProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PerkProgressionProperties, PropertySheetBase, RtClass);
	PerkProgressionProperties()
	{
		
	}
	
	std::vector<PerkProgressionReward> PerkProgressionRewards;
	
	static PerkProgressionProperties* GetProperties(const std::string& i_perkProgressionKey);
};

class RiftLevelDefinition
{
public:
	RiftLevelDefinition()
	{
		UnlockDaysFromStart = 0;
		LockDaysFromStart = 0;
	}
	
	int16 UnlockDaysFromStart;
	int16 LockDaysFromStart;
};

class RiftSubEventProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(RiftSubEventProperties, PropertySheetBase, RtClass);
	RiftSubEventProperties()
	{
		PennyTechPerBonusObjective = 1;
	}
	
    std::string Description;
	std::string FeaturedPlant;
	int PennyTechPerBonusObjective;
	std::vector<RtId> AddedLevelModules;
    
	std::string ToString() const;
	
	static RiftSubEventProperties* GetProperties(const std::string& i_subEventKey);
};

class RiftSubEventDefinition
{
public:
	RiftSubEventDefinition()
	{
		StartDeltaDays = 0;
		EndDeltaDays = 0;
	}
	
	serializable_time_t StartDeltaDays;
	serializable_time_t EndDeltaDays;
	std::string SubEventPropertyKey;
	
	std::string ToString() const;
};

class RiftLevelUnlocksProperties : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(RiftLevelUnlocksProperties, PropertySheetBase, RtClass);
    RiftLevelUnlocksProperties()
    {
        RiftLevelUnlocksKey = "DefaultConfig";
    }
    
    std::string RiftLevelUnlocksKey;
    std::vector<RiftLevelDefinition> LevelUnlockSequence;
    
    static RiftLevelUnlocksProperties* GetProperties(const std::string& i_subEventKey);
};

class RiftEventDefinition
{
public:
	RiftEventDefinition()
	{
		StartDate = 0;
		EndDate = 0;
		RiftConfigKey = "DefaultConfig";
	}
	
	serializable_time_t StartDate;
	serializable_time_t EndDate;
	std::string PerkProgressionKey;
	std::vector<RiftSubEventDefinition> SubEvents;
	std::string RiftConfigKey;
    std::string RiftWorld;
    std::string RiftLevelUnlocksKey;
	std::string RiftLevelFirstClearRewardsKey;
    std::string ZombossLevel;
    std::string ZombossRewards;
    std::string TitleText;

	const RiftSubEventDefinition* GetCurrentRiftSubEvent(long i_currentTime) const;
	const RiftSubEventDefinition* GetCurrentRiftSubEvent() const;
	const RiftSubEventDefinition* GetRiftSubEventDefinition(long i_subEventStartTime) const;
	const RiftSubEventDefinition* GetRiftSubEventDefinitionFromIndex(int i_index) const;
    int FindActiveRiftSubEventDefinition(long i_currentTime, time_t& o_startTime, time_t& o_endTime) const;
	int FindRiftSubEventDefinition(long i_subEventStartTime) const;
    std::vector<int> GetMostRecentNodeUnlockedList(pvztime_t i_currentTime) const;
    pvztime_t GetNextNodeUnlockTime(pvztime_t i_currentTime) const;
    pvztime_t GetLastNodeUnlockTime(pvztime_t i_currentTime) const;
    std::vector<std::string> GetMostRecentNodeUnlockedList() const;
    bool IsLevelNodeUnlocked(int i_index) const;
    pvztime_t GetNodeUnlockedAbsoluteTime(int i_index) const;
    pvztime_t GetNodeUnlockedTime(int i_index) const;
    int GetNodeUnlockedEntries() const;
    const std::vector<RiftLevelDefinition>& GetLevelUnlockSequence() const;

	std::string ToString() const;
};

class RiftSchedule : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(RiftSchedule, PropertySheetBase, RtClass);
	
	RiftSchedule() {}
	
	std::vector<RiftEventDefinition> Events;
	
	const RiftEventDefinition* GetCurrentRiftEvent(long i_currentTime);
	const RiftEventDefinition* GetRiftEventDefinition(long i_eventStartTime);
	const RiftEventDefinition* GetRiftEventDefinitionFromIndex(int i_index);
	const RiftEventDefinition* GetRiftEventDefinitionFromWorld(const std::string& i_world);
	int FindActiveRiftEventDefinition(long i_currentTime);
	int FindRiftEventDefinition(long i_eventStartTime);
	
	long CalculateEpochTimeFromCurrentEventDelta(long i_deltaDaysFromEventStartDate, long i_currentTime);
	
	static RiftSchedule* GetSchedule();
};

#endif /* RiftSchedule_h */
