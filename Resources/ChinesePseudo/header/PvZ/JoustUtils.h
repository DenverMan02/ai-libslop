//
//  JoustUtils.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/28/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustUtils_hpp
#define JoustUtils_hpp

#include "JoustDataPackets.h"
#include "RtObject.h"

class LevelScoringSubsystem;
class LevelRecordSubsystem;
class LevelReplaySubsystem;
class JoustLeaderboardData;
class LevelOfTheDay_RewardItemType;
class JoustGameModule;
//class LevelDifficultyScalingSubsystem;
struct PredefinedLoadoutEntry;

const int k_chest_reward_id = 23029;

namespace Sexy
{
	class INetworkStatusListener;
}

namespace Message
{
	// Note: JoustAPIContext, JoustAPIResponseStatus
	void JoustNetworkResponseReceived(int i_context, int i_status);
	
	void JoustEndOfMatch(int i_crownsAwarded);
	void JoustStartOfMatch();
	
	void JoustTournamentEndRewarded();
	void JoustLossDecision(bool i_continued, bool i_watchedAd, int i_gemsSpent);
	
	void JoustNarrativeComplete();
}

namespace JoustUtils
{
	// Main
	void		DoFirstInit();
	bool		IsPlayerReadyForJoust();
	bool		IsJoustCurrentlyAvailable();	// Use externally to determine if Joust can be entered.
	bool		IsFreePlaySystemAvailable();
	bool		IsServerTimeSet();
	int			GetPlantCountNeededToPlayJoust();

	// Connection
	bool		IsConnected();
	void		AddConnectionListener( INetworkStatusListener* listener );
	void		RemoveConnectionListener( INetworkStatusListener* listener );

	// Free Play
	bool		PlayerHasFreePlay();
	void		PlayerUseFreePlay();
	time_t		PlayerGetNextFreePlayDate();
	time_t		PlayerGetNextFreePlayTimeRemaining();
	void		CheatPlayerFreePlayForceAvailable();
	
	// Can Play
	bool		PlayerCanPlay();

	// Tournament
	bool		PlayerNeedsFirstTimeTournamentRegistration();
	time_t		GetTournamentEventTimeRemaining();
	bool		HasCurrentTournamentDefinition();
	bool		HasCurrentTournamentEnded();
	const JoustAPIResponseLeagueChange& GetTournamentEndedData();
	void 		ClearCurrentTournamentEndedFlag();
	const JoustTournamentDefinition* GetCurrentTournamentDefinition();
	const std::string GetProgressiveRewardKey(int i_league);
	const std::string GetTournamentRewardKey(int i_league);
	const JoustTournamentDefinition* GetCurrentTournamentDefinition();

	// Leagues
	int			GetLeagueCount();
	const std::string GetLeagueName(int i_league);
	const std::string GetLeagueNameShort(int i_league);
	const std::string GetLeagueIcon(int i_league);

	// Level
	const std::string GetLevelToPlay();
	void		CheatCreateDummyMatch();
	void		ClearCurrentMatch();
	bool		HasCurrentMatch();
	const JoustAPIResponseMatch* GetCurrentMatch();
	bool		HasLevelHumanReplay();
	const Buffer		GetLevelHumanReplay();
	
	// Level End
	void		RecordJoustLevelEnd(bool i_victory);
	void		SaveReplayData();
	bool		HasLevelEndAward();
	int			GetLevelEndCrownAward();
	void		ClearLevelEndAward();
	const std::vector<LevelOfTheDay_RewardItemType> GetLevelEndStreakRewards();

	// Level End Extensions
	void		ClearLevelEndExtensionCount();
	int 		GetLevelEndExtensionCount();
	void 		AddLevelEndExtension();
	
	// Incomplete Matches
	const JoustIncompleteMatchData* GetNextIncompleteMatch();
	bool		HasIncompleteMatches();
	void		ClearIncompleteMatches();

	// Local Player
	const JoustLocalPlayerData& GetLocalPlayerData();
	const SexyString PlayerGetName();
	int			PlayerGetLeague();
	std::string	PlayerGetPCPID();
	void 		CheatPlayerOverridePCPID(const std::string& i_override);
	bool		PlayerHasTicket();
	void		PlayerSpendTicket();

	// Crowns
	int			PlayerGetCrowns();
	void		CheatPlayerAddCrowns(int i_crowns);
	void		CheatPlayerResetCrowns();
	
	// Win Streak
	int			GetCurrentWinStreak();
	void		CheatIncrementWinStreak();
	void		CheatResetWinStreak();
	const LevelOfTheDay_RewardItemType* GetWinStreakReward(int i_league, int i_streakIndex);
	int			GetWinStreakCrownReward(int i_streakIndex);
	const LevelOfTheDay_RewardItemType GetNetworkWinStreakReward(int i_streakIndex);
	
	// Leaderboard
	const JoustLeaderboardData& GetLeaderboardData();
	const JoustPlayerData& GetLocalPlayerLeaderboardData();
	int			GetLocalPlayerLeaderboardIndex();
	int 		GetLeaderboardMaxPlacementCount();
	int			GetPlacementChangeForLeaderboardIndex(int i_index);
	std::string	GetBadgeImageForLeaderboardIndex(int i_index);
	const std::vector<LevelOfTheDay_RewardItemType>* GetLeaderboardPlacementReward(int i_league, int i_placementIndex);
	
	AwardInfo GetAwardInfoByActId(int i_actId);
	const std::vector<LevelOfTheDay_RewardItemType> GetLeaderboardBestPlacementReward(int i_league);
	const std::vector<LevelOfTheDay_RewardItemType> GetLeaderboardPlayerPlacementReward(int i_league, int i_placementIndex);

	// Players
	JoustPlayerData	CreateFakeOpponent();
	void		CreateFakeLeaderboadPlayer();
	void		CreateNewLocalPlayer();
	int			ClampAvatarIconValue(int i_iconID);
	int			ClampAvatarNameValue(int i_nameID);

	// Avatar
	int			AvatarCalcRandomIndex();
	ImagePtr	AvatarGetImagePtr(int i_index);
	ImagePtr	AvatarGetFrameImagePtr(int i_index);
	ImagePtr	AvatarGetBottomImagePtr(int i_index);
	
	// Names
	int			NameCalcRandomIndex();
	const SexyString	NameGetFromIndex(int i_index);

	// Gameplay
	bool		IsPlayingJoustLevel();
	LevelScoringSubsystem* GetScoringSystem();
	LevelRecordSubsystem* GetCurrentLevelRecording();
	LevelReplaySubsystem* GetOpponentReplay();
	//LevelDifficultyScalingSubsystem* GetDifficultyScalingSystem();
	const JoustPlayerLoadoutData*	GetOpponentLoadout();
	int			GetOpponentFinalScore();
	int			GetOpponentScore();
	JoustGameModule* GetJoustGameModule();
    int GetPredefinedLoadoutCount();
    std::vector<PredefinedLoadoutEntry> GetPredefinedLoadout(int i_index);
	
	// FUE
	bool 		IsFUENeeded();
	bool		TryShowFUE();
	void		SetFUEAsSeen();
	void 		CheatClearFUEAsSeen();
	bool		DoesUnlockAnimNeedToPlay();
	void		SetUnlockAnimAsSeen();
	void		CheatClearUnlockAnimAsSeen();
	
	// Networking
	bool		CheckDashboardInfo();
	void		RequestPostMatch();

	void		SetAPIEnvironment(JoustAPINetworkEnvironments i_environment);
	void		SetAPIRequestTimeout(float i_timeoutSeconds);
	std::string GetAPICurrentBaseURL();
	JoustAPIResponseStatus GetResponseStatus(JoustAPIContext i_context);
	void		CheatSendBadRequest();
	void 		CancelCurrentAPIRequest();
	void		SendAPIGetDashboard();
	void 		SendAPIPostAvatar(const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void		SendAPIGetFirstMatch(const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void		SendAPIGetNextMatch(const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void		SendAPIPostCompleteMatch(const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void 		SendAPIPostIncompleteMatch(const JoustIncompleteMatchData& i_incompleteMatch);
	void 		SendAPIRegisterForTournament(const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);

	void		ApplyAPIResponseDashboard(JoustAPIResponseDashboard& i_response);
	void		ApplyAPIMatchResponse(JoustAPIResponseMatch& response);
	void 		ApplyAPIMatchCompleteResponse(JoustAPIResponseMatchComplete& response);

	std::string ConvertContextToString(JoustAPIContext i_context);
	std::string GetNetworkIssueLocalizedString(JoustAPINetworkIssue i_error, JoustAPIContext i_context);
	std::string ConvertResponseStatusToString(JoustAPIResponseStatus i_response);

	void 		ShowJoustNetworkIssuePopup(JoustAPINetworkIssue i_error, JoustAPIContext i_context); 	// Response is Message::JoustNetworkIssueDecision
}

#endif
