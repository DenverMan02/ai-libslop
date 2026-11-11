//
//  ProfileUtils.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ProfileUtils_h
#define PlantsVersusZombies2_ProfileUtils_h

//#include "PlayerInfo.h"
#include "ProfileMgr.h"

#include "PVZTypes.h"

class LevelDefinition;
class ChallengeModule;

namespace ProfileUtils
{
	void DeleteAndRecreatePlayerInfo(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());

	void ResetPlayerInfo(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	void CompleteAllLevels(bool i_hard = false,PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	
	void CompleteLevelsForWorld(const std::string& i_worldName, bool i_completeStarChallenges, bool i_hard = false, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	
    bool HasCompletedCurrentNormalLevel(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	bool HasCompletedCurrentLevel(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	bool HasCompletedLevel(const std::string& i_levelName, bool i_hard = false, PlayerInfo *i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	
	bool IsPlantUnlocked(PlantTypePtr i_plantType, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());

	time_t PlayTimeSeconds(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());

	PlayerInfo *Profile(void);

	bool ChallengesUnlockedForCurrentStage(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	bool ChallengesUnlockedForStage(const LevelDefinition *i_levelDefinition, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());

	int CompletedLevelCount(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	int CompletedLevelCount(const std::string& i_forWorld, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
    int CompletedNodeCount(const std::string& i_forWorld, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	int UnlockedWorldCount(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());

	bool HasUnlockedWorld(const std::string& i_worldName, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
    
    // Returns 'true' iff the world exists and has been unlocked for this profile
    bool IsWorldUnlocked(const std::string& i_worldName, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
    bool IsLevelClearedInSecondUnlockedWorld(int levelID);
	
	int TotalGamesPlayedForWorld(const std::string& i_world, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	int TotalGamesPlayedForLevel(const std::string& i_level, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	int TotalGamesPlayed(PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	
    PlayerInfoPtr CreateProfile(const SexyString& i_profileName, SexyString& o_errorString);
	PlayerInfoPtr CreateProfile(const SexyString& i_profileName, SexyString& o_errorString, const std::vector<SexyString>& i_nameList);
	bool ChangeProfileName(const SexyString& i_previousName, const SexyString& i_newName, SexyString& o_errorString, const std::vector<SexyString>& i_nameList);
	bool CheckValidUserName(const SexyString& i_name, const std::vector<SexyString>& i_nameList);
	
	struct ChallengeStatusHolder
	{
		ChallengeStatusHolder()
        : Discovered(false)
        , Completed(false)
        , Active(false)
        , CompletedThisPlay(false)
		{
            // Do nothing.
		}

        std::vector<SexyString> ChallengeDescriptions;
        std::vector<bool> ChallengeFailureStates;
        std::vector<pvztime_t> ChallengeFailureTimes;
        std::vector<bool> ChallengeCompletionStates;
		bool Discovered;
		bool Active;
		bool Completed;
		bool CompletedThisPlay;
	};
	void GetChallengeStatusForCurrentLevel(std::vector<ChallengeStatusHolder>& o_challengeStatus);
	void GetChallengeStatusForCurrentLevel(std::vector<ChallengeStatusHolder>& o_challengeStatus, std::vector<ChallengeStatusHolder>& o_bonusChallengeStatus, bool i_special = false);
	void GetChallengeStatusForCurrentLevelByChoose(std::vector<ChallengeStatusHolder>& o_challengeStatus, std::vector<bool> chooseList, int level);
	void GetChallengeStatusForCurrentLevelByChoose(const std::string& i_levelName, std::vector<ChallengeStatusHolder>& o_challengeStatus, std::vector<bool> chooseList, int level);
	void GetChallengeStatusForLevel(const std::string& i_levelName, std::vector<ChallengeStatusHolder>& o_challengeStatus, bool i_special = false);
	void GetBonusChallengeStatusForLevel(const std::string& i_levelName, std::vector<ChallengeStatusHolder> &o_challengeStatus);
	void ConstructChallengeStatus(std::vector<ChallengeStatusHolder> &o_challengeStatus, ChallengeModule* i_challengeModule, bool i_inGameplay);

	void GetStarCountsForWorld(const std::string& i_worldName, int& o_totalStars, int& o_completedStars);

	bool HasPassed50MBContentThreshold();
	
	void TriggerTutorialFunnelEventForCurrentProfile(FunnelEvent i_funnelEvent);
	uint64 GetCurrentProfileLastTutorialFunnelEventCompletionTime();
    
    int CompleteMainSpineForWorld(const std::string& i_worldName, PlayerInfo* i_info);
    
	void CompleteEvent(const std::string& eventItem, bool i_completeStarChallenges, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
	void CompleteEvent(MapEventItem const & eventItem, bool i_completeStarChallenges, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());

//	void CompleteToEvent(std::string const & i_eventName, bool i_completeStarChallenges, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
    
    void CompleteToEventFloodFill(const std::string& i_eventName, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
    int CompleteToEvent(std::string const & i_eventName, bool i_hard, bool i_completeThisEventToo, PlayerInfo* i_info = ProfileMgr::GetInstance().GetCurrentProfile());
    
    // Returns 'true' if any rewards were given to the player that they should be notified of
    bool ConvertOldProfileToNewMap(PlayerInfo* i_profile);
    
	long CalculateDangerRoomRandomSeed(const DangerRoomInfo* i_dangerRoomInfo = NULL);
    long CalculateDangerRoomRepickSeed();
	
	// except egypt world's check
	bool HasCompletedSecondWorldLevel(const int i_levelNumber, bool i_hard = false, PlayerInfo *i_info = ProfileMgr::GetInstance().GetCurrentProfile());
};

#endif
