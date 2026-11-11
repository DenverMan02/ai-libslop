//
//  RiftUtils.hpp
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 5/30/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef RiftUtils_h
#define RiftUtils_h

#include "Award.hpp"
//#include "FamilyResistanceSubSystem.h"
#include "PVZTypes.h"
#include "RiftConfigFile.h"
#include "RiftSchedule.h"
#include "RiftZombossRewards.h"
//#include "RiftDataPacket.h"

class MapEventItem;
class RiftLeaderboardData;
enum class RiftAPINetworkIssue;
enum class RiftAPIContext;
typedef struct RiftDifficultyInfo DifficultyInfo;
typedef struct RiftBonusInfo BonusInfo;
typedef struct RiftPostEndPlay EndInfo;
typedef struct RiftPlayerData PlayerData;
typedef struct RiftAwardInfo AwardRiftInfo;
typedef struct RiftLocalPlayerData LocalPlayerData;
typedef struct RiftAPIResponseLeagueChange APIResponseLeagueChange;

namespace Message
    {
    void RiftNarrativeComplete();
    void RiftEndOfMatch(bool i_victory);
    void RiftNetworkResponseReceived(int i_context, int i_status);
    }

struct LevelModuleDifficultyEntry
{
    RtWeakPtr<LevelModuleDifficultyProps> DifficultyProps;
    RtWeakPtr<LevelModuleDifficultyUIProps> DifficultyUIProps;
};

//struct LevelModuleResistanceEntry
//{
//    PlantFamilyResistance ResistanceProps;
//    SexyString Description;
//};

struct RiftLevelDifficultyData
{
    std::vector<LevelModuleDifficultyEntry> DifficultyEntries;
    //std::vector<LevelModuleResistanceEntry> ResistanceEntries;
};

class RiftIncompleteMatchData : public Sexy::RtObject
{
    RT_CLASS_DEFINE(RiftIncompleteMatchData, Sexy::RtObject, Sexy::RtClass);
    
    enum RiftIncompleteLevelType
    {
        RIFTLEVELTYPE_ZOMBOSS
    };

    RiftIncompleteMatchData()
    {}
    
    RiftIncompleteMatchData(RiftIncompleteLevelType i_levelType, std::string& i_levelName, serializable_time_t i_riftEventID, int i_attemptIndex)
    {
        ZombossAttempt = i_attemptIndex;    // If we ever have to support conventional levels we'd need to store the difficulty like this.
        LevelType = i_levelType;
        LevelName = i_levelName;
        RiftEventID = i_riftEventID;
    }

    int ZombossAttempt;
    serializable_time_t RiftEventID;
    std::string LevelName;
    RiftIncompleteLevelType   LevelType;
};

enum LevelType
{
	LevelType_Normal,
	LevelType_TimeLimited,
	LevelType_RiftTimed,
	LevelType_Boss
};

namespace RiftUtils {

    // Global
    int         GetPlantCountNeededToPlay();
    bool        IsPlayerReadyForRift();
    void        ShowHowToPlayScreen();
    bool        ShouldAutoPopHowToPlay();
    void        SetHasSeenHowToPlay();
    bool        IsRiftHidden();
    bool        IsRiftDownForMaintenance();
	bool		IsRiftCurrentlyAvailable();
    bool        IsInRiftWorldMap();
    bool        IsInQueuedRiftWorldMap();

    // Level
    void        SetLevelOverride(std::string i_levelName);
    const std::string GetLevelOverride();
    bool        IsPlayingRiftLevel();
    bool        IsPlayingMostRecentRiftLevel();
    bool        IsPlayingZombossLevel();
    bool        IsZombossLevelVictory();
    void        CheatForceZombossLevelVictory();
    void        SetDifficultyForNextLevel(int i_difficulty);
    int			GetDifficultyForNextLevel();
    int         GetMaxLevelDifficulty();
    int         GetLevelVersionForNextLevel();                          // Intended currently for the Zomboss iteration
    int         GetPennyFuelCostForLevelNode(int i_nodeIndex);          // Note: Probably will need to figure out how to handle Zomboss, so these might become cascading functions pointing to a shared core.
    RiftLevelDifficultyData GetLevelDifficultyDataForLevelNode(std::string i_levelName);
	void		MarkCurrentRiftLevelComplete();
    MapEventSubType GetCurrentMapEventSubType();

	//First Clear Rewards
    LevelOfTheDay_RewardItemType* GetFirstClearReward(int i_nodeIndex, int i_difficulty);
    LevelOfTheDay_RewardItemType* GetFirstClearRewardForCurrentLevel();
    bool        HasEarnedFirstClearReward(MapEventItem* i_event, int i_difficulty);
	bool		HasEarnedAllFirstClearRewards(MapEventItem* i_event);
	bool		ShouldGiveFirstClearRewards();
    void		GiveFirstClearRewards();

    // Incomplete Matches
    void        AddIncompleteMatch();
    void        ClearIncompleteMatches();
    bool        HasIncompleteMatch();
    const RiftIncompleteMatchData* GetNextIncompleteMatch();

    // Penny Fuel
    int         GetCurrentPennyFuel();
    int 		GetPennyFuelCap();
    void 		UpdatePennyFuel();
    time_t      GetTimeToNextPennyFuelUpdate();
    time_t      GetTimeToPennyFuelFull();

    // ZPS
    bool		IsZombossUnlocked();
    bool		TestWillUnlockZomboss(int i_updatedZPS);
    void		UpdateZombossSignal();
    time_t      GetZombossUnlockedTimeRemaining();
    int			GetZombossUnlockingThreshold();
    void		ResetZombossSignalWithAdditionalValue(ZombossSignalCurrency i_additionalSignal); //Resets signal to input value, plus the overflow the player currently has
    void		FullyResetZombossSignal(); //Completely resets the signal to 0
    int 		GetZombossSignalResetValue();
    time_t      GetTimeToNextZPSUpdate();
    int         CalcZPSSignalGained(int i_difficulty);
	bool		ShouldUseZPSBackupReward();
	bool		EventHasZPSBackupReward();
	LevelOfTheDay_RewardItemType* GetZPSBackupReward();
	void		GiveZPSBackupReward();

    // Zomboss
    int         GetMaxZombossAttempts();
    int         GetZombossAttemptsMade();
    void        AddZombossWinLossRecord(bool i_win, int i_difficulty);
    void        ClearZombossWinLossRecord();
    void        GetZombossWinLossData(int i_attempt, bool& o_played, bool& o_win, int& o_difficulty);
    int			GetZombossWins();
    bool        HasZombossUnawardedProgress();
    bool        HasCompletedZombossAttempt();
    bool        ShouldAutoPopZombossLevelSelect();
	void		FlagZombossCompletion();
	void		ClearZombossCompletionFlag();
	bool		TestZombossCompletionFlag();
	bool		ZombossFightsPerCycleExceeded();
	time_t		GetNextZombossCycleStart();
	void		UpdateZombossFights();
    void        CheatResetZombossFightCount();
    void        CheatAddZombossFightCount();
    time_t		GetTimeUntilZombossRefresh();
    void		SetZombossRewardRatio(float value);
    float 		GetZombossRewardRatio();

    // Zomboss Rewards
	GeneralAwardSet CalcZombossTotalAwardSet(int i_attempt, bool i_win, int i_difficulty);
    GeneralAwardSet CalcZombossBaseAwardSet(int i_attempt, bool i_win, int i_difficulty);
	GeneralAwardSet CalcZombossVictoryAwardSet(int i_attempt, bool i_win, int i_difficulty);
    GeneralAwardSet CalcZombossFlattenedBaseAwardSet(int i_attempt, bool i_win, int i_difficulty);
	GeneralAwardSet CalcZombossFlattenedVictoryAwardSet(int i_attempt, bool i_win, int i_difficulty);
    GeneralAwardSet ConvertZombossRewardSetToAwardSet(const RiftZombossRewardDifficultyEntry* i_entry);
    const RiftZombossRewardDifficultyEntry CalcCurrentZombossEventEndPrize();
    const RiftZombossRewardDifficultyEntry* GetZombossPrizeWinReward(int i_attempt, int i_difficulty);
    const RiftZombossRewardDifficultySet* GetZombossPrizeWinRewardData_Internal(int i_attempt);
    const RiftZombossRewardDifficultyEntry* GetZombossPrizeDefaultReward(int i_attempt);
    const std::string& GetPinataTypeForZombossGrandPrizeOpeningSequence();

    // Utils
    void 		UpdateRiftValues();
    void        ResetRift();
	const char*		GetMetricsID();
	int			GetZombossPOLCount();
	void		ResetZombossPOLCount();
	pvztime_t	GetZombossPOLCumulativeExtraTime();
	int			GetZombossPOLCumulativeGemCost();

    // Schedule
    const RiftEventDefinition* CalcCurrentScheduledEvent();
    const RiftSubEventDefinition* CalcCurrentScheduledSubEvent();
    serializable_time_t CalcCurrentScheduledSubEventTime();
    void        DoEventRollover();
    void        DoSubEventRollover();

    // Event
    bool        IsPlayerOnActiveEvent();
    const RiftEventDefinition* GetCurrentEventProps();
    const RiftSubEventProperties* GetCurrentSubEventProps();
    RiftConfigSheet* GetCurrentRiftConfig();
    RiftConfigSheet* GetGlobalRiftConfig();
    time_t      GetCurrentRiftEventTimeRemaining();
    time_t      GetCurrentSubEventTimeRemaining();
    SexyString GetCurrentRiftEventTitle();
    SexyString GetCurrentRiftDescription();
    std::string GetCurrentEventStartDateFormatted();
    std::string GetCurrentEventEndDateFormatted();
	std::string GetCurrentRiftWorld();

    // Notifications
    time_t      GetEndOfEventLocalNoteDelay();
    pvztime_t   GetTimeToNextLevelUnlock();
    time_t      GetZombossEndLocalNoteEarly();

    // Perks
    std::vector<PerkProgressionReward> GetCurrentEventPerkProgression();
    int			GetPennyTechRewardForCurrentLevel();
    bool		ShouldShowPerkOutroScreen();
    std::vector<PerkData> GetAllCurrentPerkData();
	bool		PlayerHasCompletedPerkProgression();
    int         GetCurrentPennyTech();
    int         GetMaxPennyTech();

    // World
    std::string GetCurrentLandingLevel();
    void        GoToRiftWorldMap();
    bool        IsNodeUnlocked(int i_index);
    time_t      GetNodeUnlockedTime(int i_index);
    SexyString  GetNodeUnlockedTimeText(int i_index);
    ImagePtr    GetNodeSubTypeIcon(MapEventSubType i_type);
    int         GetRiftWorldIndexOfLevel(const std::string& i_levelName);
    std::string GetRiftWorldNameOfLevel(int i_index);
    std::string GetMostRecentRiftLevel();

    void        ShowLevelSetupScreen(MapEventItem* i_event, const Delegate1<const std::string&>& i_onPlayLevelCallback);
    void        ShowZombossLevelSetupScreen(const std::string& i_event, const Delegate1<const std::string&>& i_onPlayLevelCallback);

    // FUE
    bool 		IsFUENeeded();
    bool		IsFUENarrativeSeen();
    bool		TryShowFUE();
    void		SetFUEAsSeen();
    void 		CheatClearFUEAsSeen();
    bool		DoesUnlockAnimNeedToPlay();
    void		SetUnlockAnimAsSeen();
    void		CheatClearUnlockAnimAsSeen();

    // Chinese Ver.
    int			GetCurrentZPS();
    int			GetCurrentTheme();
    int 		GetLimitedPlantId();
    int			GetSeasonLeftTime();
    int			GetThemeLeftTime();
    int			GetBossStartTime();
    int			GetBossRewardRatio();
    int			GetCurrentFuel();
    void		AddFuel(int i_amount);
    int			GetFuelToPlay();
    bool		PlayerCanPlay();
    int			GetCurrentScore();
    int			GetCurrentLeague();
    int			GetCurrentRank();
    int			GetCurrentPlantId();
    int			GetBossAttemptCount();
    time_t		GetCurrentSeasonTimeRemaining();
    time_t 		GetCurrentThemeTimeRemaining();
    time_t 		GetCurrentZombossTimeRemaining();
    const std::string& GetCurrentWorld();
    const DifficultyInfo& GetTargetLevelReward(int i_levelIndex, int i_difficulty);
    const std::vector<BonusInfo>& GetBossReward(int i_phaseIndex);
    const std::vector<BonusInfo>& GetBossNormalReward();
    std::string GetNetworkIssueLocalizedString(RiftAPINetworkIssue i_error, RiftAPIContext i_context);
    void 		ShowRiftNetworkIssuePopup(RiftAPINetworkIssue i_error, RiftAPIContext i_context);
    int			GetZombieLevel();
    const std::vector<ZombieLevelStat>* GetCurrentLevelZombieStats();
    const std::vector<ZombieLevelStat>* GetGlobalLevelZombieStats();
    int			GetTargetLevelMaxScore(int i_levelIndex, int i_difficulty);
    int			GetBossLevelMaxScore(int i_phaseIndex);
    const std::vector<int>& GetRiftTimedEventThemes();
    SexyString GetRiftTimedThemeName(int i_index);
    SexyString GetRiftTimedThemeDescription(int i_index);

    // Theme
    template<typename T> T* GetThemeByClass()
	{
		for (RtDbTable::Iterator iter = PVZDB::GetInstance().GetObjectIteratorForTable(PVZDB::TABLE_THEMES); (iter); ++(iter))
		{
			RtWeakPtr<RtObject> object = *iter;
			if (object.Get()->IsA(T::StaticGetClass()))
			{
				return object->Cast<T>();
			}
		}

		return nullptr;
	}

    SexyString GetCurrentThemeName();
    SexyString GetCurrentThemeDescription();

    int GetCurrentMode();
    SexyString GetCurrentModeName();
    SexyString GetCurrentModeDescription();

    // Rift Timed level
    bool 		IsRiftTimedLevel();
    bool 		IsRiftTimedLevel(MapEventItem* i_event);
    bool		IsRiftTimedLevel(const std::string& i_levelName);
    int			GetMaxNextWaveUseTime();

    // Level End
    int			GetLevelEndZPS();
    const std::vector<RiftPerkData>& GetLevelEndDrawPerks();
    const std::vector<RiftBonusInfo>& GetLevelEndRewards();
    const std::vector<RiftBonusInfo>& GetLevelEndBonusRewards();
    const std::vector<RiftBonusInfo>& GetLevelEndFirstClearRewards();
    int			GetCurrentLevelScore(float i_time);
    int			GetMaxScore(LevelType i_type, int i_difficulty = 0);
    int			GetCurrentLevelMaxScore();
    int			GetCurrentTotalScore();
    void		SetEndLevelScore(int i_score);
    int			GetEndLevelScore();
    void		SetLevelTime(pvztime_t i_time);
    pvztime_t	GetLevelTime();
    void		SetBossLevelTime(pvztime_t i_time);
    pvztime_t	GetBossLevelTime();

    // Leagues
    int			GetLeagueCount();
    const LocalPlayerData& GetLocalPlayerData();
	int			PlayerGetLeague();
	const std::string GetLeagueName(int i_league);
	const std::string GetLeagueNameShort(int i_league);
	const std::string GetLeagueIcon(int i_league);
	const std::string GetLeagueSmallIcon(int i_league);
	LeagueFrameType GetLeagueFrameType(int i_league, int i_place);
	int GetNextLeague(int i_league, int i_place);
	const std::vector<LeagueFrameRange>& GetLeagueFrameRangeByLeague(int i_league);

	// Screens
	void ShowLeaderBoardScreen();

	// Leaderboard
	const RiftLeaderboardData& GetLeaderboardData();
	const PlayerData& GetLocalPlayerLeaderboardData();
	int			GetLocalPlayerLeaderboardIndex();
	std::string	GetBadgeImageForLeaderboardIndex(int i_index);
	//const std::vector<LevelOfTheDay_RewardItemType>* GetLeaderboardPlacementReward(int i_league, int i_placementIndex);

	AwardRiftInfo GetAwardInfoByActId(int i_actId);
//	const std::vector<LevelOfTheDay_RewardItemType> GetLeaderboardBestPlacementReward(int i_league);
	const std::vector<LevelOfTheDay_RewardItemType> GetLeaderboardPlayerPlacementReward(int i_league, int i_placementIndex);
	const std::vector<int>& GetLeaderboardLeagueRewards();

	// Avatar
	ImagePtr	AvatarGetImagePtr(int i_index);
	ImagePtr	AvatarGetFrameImagePtr(int i_index);
	ImagePtr	AvatarGetBottomImagePtr(int i_index);

	// Tournament
	bool		HasCurrentTournamentEnded();
	bool 		HasCurrentSeasonEnded();
	const APIResponseLeagueChange& GetTournamentEndedData();
	void 		ClearCurrentTournamentEndedFlag();
	bool		HasPromotedReward();
	int			GetPromotedReward();

	// Common
	bool		IsWorldMapButtonsEnabled();

    // Network apis
    void SendGet_MainEntry();
    void SendPost_EndPlay(EndInfo i_info);
    void SendPost_Play(bool i_bossLevel);
    void SendGet_LeaderboardEntry();
}

#endif
