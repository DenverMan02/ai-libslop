//
//  LevelOfTheDay.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 9/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelOfTheDay_h
#define PlantsVersusZombies2_LevelOfTheDay_h

#include <string>
#include <vector>

#include "LevelOfTheDay_RewardData.h"
#include "PinataStyleChooserFactory.h"
#include "PVZTypes.h"
#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Singleton.h"
#include "sys/types.h"
#include "ActivityManager.h"

class LevelOfTheDayPropertySheet;
class LevelOfTheDaySchedule;
class LevelOfTheDaySystem;
class PlayerInfo;
class TimeMgr;
class ZombieType;

// Public namespace for helper functions and system accessor

enum LevelOfTheDay_AcitivityType
{
	LevelOfTheDay_No,
	LevelOfTheDay_ChildrenDay,
	LevelOfTheDay_SummerEvent,
	LevelOfTheDay_TimeTravel,
	LevelOfTheDay_PlantDefence,
	LevelOfTheDay_YuanBaoDefence,
	LevelOfTheDay_ChildrenDay2018,
	LevelOfTheDay_FestivalGame2019,
	LevelOfTheDay_ChildrenDay2019,
	LevelOfTheDay_countNum
};

enum CurGameLevel
{
	GameLevel_No,
	GameLevel_Normal,
	GameLevel_Hard,
	GameLevel_Legend
};

namespace LevelOfTheDay
{
	bool IsEnabled();
	bool IsUnlockedByPlayer();

	LevelOfTheDaySystem& GetSystem();
	LevelOfTheDayPropertySheet* GetProperties();
};

// Holds global state for the LevelOfTheDay mechanic
class LevelOfTheDaySystem : public LazySingleton<LevelOfTheDaySystem>
{
public:
	LevelOfTheDaySystem();
	void Initialize();
	void ValidateData();

	// Checks to see if the active level for the profile has expired.
	// Output values are to detect edges for player-facing messaging.
	void UpdateActiveLevelForProfile(PlayerInfo *i_profile, bool &o_activeLODExpired) const;
	int GetSenorPinataInterval();
	int GetConsecutiveDaysCompletedIndex();
	bool WasLevelJustCompletedASenorPinataLevel();
	int GetReplayCostCoins() const;
	int GetTotalNumDiscountedReplays() const;
	const int GetNumReplaysForCurrentLOD();

	const class LevelOfTheDaySchedule *GetCurrentScheduleForProfile(const PlayerInfo* i_profile) const;
	const class LevelOfTheDaySchedule* GetNextScheduleForProfile(const PlayerInfo* i_profile) const;

	const class LevelOfTheDaySchedule* GetCurrentSchedule() const;
	const std::string GetCurrentHoliday() const;
	const LevelOfTheDaySchedule* GetFinalSchedule() const;

	// Returns 'true' and fills out o_levelName iff there exists any level that this profile can play
	bool PickLevelNameForProfile(std::string& o_levelName, PlayerInfo* i_profile) const;

	// Returns 'true' if the given zombie type is available to the current profile
	bool CanSpawnZombie(ZombieTypePtr i_zombieType) const;

	void MarkActiveLevelAsAttemptedForProfile(PlayerInfo *i_profile) const;
	void CompleteActiveLevelForProfile(PlayerInfo *i_profile) const;
    bool ActiveLevelHasBeenAttemptedByProfile(PlayerInfo *i_profile) const;
    bool ProfileHasActiveLOD(PlayerInfo *i_profile, bool i_TestUpcoming) const;
    
    bool AttemptStartLOD();
    
	// Cheating
	bool IsCheatScheduleActive() const;
	const LevelOfTheDaySchedule* CheatScheduleNextLOD();
	const LevelOfTheDaySchedule* CheatSchedulePrevLOD();
	const LevelOfTheDaySchedule* CheatScheduleTodayLOD();

	time_t GetInterpolatedServerLocalTime() const;
	time_t GetInterpolatedServerTimeUTC() const; 
	
	const HolidayEventProperties* GetHolidayEventProps(const std::string& i_eventName);
	
	static int calculateNewSenorPinataOffset(const int i_consecutivePlays, const int i_oldInterval, const int i_newInterval);
	static int calculateSenorPinataProgressIndex(const int i_consecutivePlays, const int i_interval);

	void setCurSelectSummerLevel(CurGameLevel summerLevel);
	CurGameLevel getCurSelectSummerLevel() const;

	void setCurLotdAcType(LevelOfTheDay_AcitivityType type);
	LevelOfTheDay_AcitivityType getCurLotdAcType() const;
	ActivityTypeID getCurActivityTypeID() const;
private:
	void initializeMembers();

	const class LevelOfTheDaySchedule* getScheduleThatStartsAfter(time_t i_time) const;

	const LevelOfTheDaySchedule *getScheduleFromUID(int i_uid) const;
	bool isScheduleValid(const LevelOfTheDaySchedule* i_schedule) const;

	bool isLevelAvailableToProfile(const std::string& i_levelName, PlayerInfo* i_profile) const;
	bool isLevelScheduleCurrent(const class LevelOfTheDaySchedule *i_schedule) const;
	bool isLevelPresent(const std::string &i_levelName) const;

	time_t getDeviceUTCTime() const;

	void unlockLevelOfDayFeatureIfReady() const;
	
	void incrementLODProgress(PlayerInfo* i_profile) const;
	void resetLODProgress(PlayerInfo* i_profile) const;
	
	void checkForNewSenorPinataInterval(PlayerInfo* i_profile) const;
	void changeSenorPinataInterval(int i_oldInterval, int i_newInterval, PlayerInfo* i_profile) const;
    
    bool attemptPurchaseLODReplay();
    void onReplayForCoinsDialogClosed();
    void startLoDLevel();
    
	TimeMgr& mTimeMgr;

	// Cheat!
	time_t m_cheatServerTime;

	CurGameLevel m_curSelectSummerLevel;
	LevelOfTheDay_AcitivityType m_curLotdAcType;
};

class LevelOfTheDayPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelOfTheDayPropertySheet, PropertySheetBase, RtClass);

	LevelOfTheDayPropertySheet()
	{
	}

	std::vector<RtWeakPtr<ZombieType> > KilledZombieBlacklist;
	std::string FirstTimeNarrative;
	int SenorPinataInterval;
	int ReplayLevelCostCoins;
	std::vector<LevelOfTheDaySchedule> Schedules;
	std::vector<LevelOfTheDay_RewardItemType> Rewards;
	std::vector<HolidayEventProperties> HolidayEvents;
	std::vector<std::string> AndroidBlacklist;
	std::string ConsecutiveCostumeRewardConsolationCategory;
	std::string HolidayDefault;
	std::string SoonestIntroLevel;
};

class LevelOfTheDaySchedule : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelOfTheDaySchedule, PropertySheetBase, RtClass);

	LevelOfTheDaySchedule();

	time_t AvailableTimeInSeconds() const;

	const bool StartsBefore(time_t i_time) const { return StartDate < i_time; }
	const bool StartsAfter(time_t i_time) const { return StartDate > i_time; }
	void OverrideStartDate(time_t i_time) { StartDate = i_time; }

	time_t CalculateUTCEndTime() const;

	unsigned UID;					// Unique id for tracking event completion.
	time_t StartDate;				// UTC date that the event should be made available to the player.
	time_t NotificationStartOffset;	// Offset in seconds to fire off notification of new LOD ready.
	std::string PrimaryLevelName;	// Used unless the player hasn't seen the mechanics.
	std::string SecondaryLevelName; // Used as a backup if the player hasn't seen mechanics from the primary level.
	bool		EnableLocalNotifications;	// Turn on/off all local notices with this event
	std::string Holiday;
    std::string HolidayBannerName = "Default";
	std::string LocalNoteDailyMessageOverride;
	std::string LootCommonPinata;
	std::string LootValuablePinata;
	std::string LootMegaPinata;
	int			ReplayLevelCostCoins;
	int			NumReplaysAtDiscountedCost;

	std::string ToCheatString(time_t i_currentTime);

private:
	unsigned NumberOfDaysAvailable;	// Number of days the 'level of the day' is available for after it's been scheduled.
};

namespace Message
{
	void LevelOfTheDayReplayPurchased(int i_replayCost, const std::string& i_context);
}

#endif
