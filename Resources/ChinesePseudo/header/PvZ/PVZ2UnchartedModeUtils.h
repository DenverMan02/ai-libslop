/*
 * PVZ2UnchartedModeUtils.h
 *
 *  Created on: 2022-3-14
 *      Author: zhousen
 */

#ifndef PVZ2UNCHARTEDMODEUTILS_H_
#define PVZ2UNCHARTEDMODEUTILS_H_

#include "PVZ1ModeNetworkMgr.h"
#include "PVZ2UnchartedModeNetworkMgr.h"


namespace PVZ2UnchartedModeUtils
{

    void GoToUnchartedModeWorldMap(const std::string& i_prefixWorld, bool i_isHard);
    bool IsInUnchartedModeWorldMap();


	// global
	bool IsPlayingPVZ2UnchartedModeLevel();

	bool HasCompleteTutorial();
	bool IsInPVZ2UnchartedModeWorldMap();
	bool IsInQueuedPVZ2UnchartedModeWorldMap();
	bool IsHardMode();
	void SetIsHardMode(bool hardMode);
	bool IsTimeLimitWorld();
    std::vector<int> GetCurrentThemeList();
    UnchartedModeBoardRecord GetCurrentBoardRecord();
    void SetCurrentBoardRecord(UnchartedModeBoardRecord data);
    UnchartedModeBoostData GetCurrentBoost();
    bool IsLastLevel();
    int GetSpringFestival2024CurrentLevelIndex();

	bool IsUnchartedBirthday();
    bool IsUnchartedBirthday(const std::string& i_worldName);
    bool IsAnniversarySelectLevel();
    bool IsAnniversarySelectLevel(const std::string& i_worldName);
    bool IsNormalSelectLevelWithHardmode();
    bool IsNormalSelectLevelWithHardmode(const std::string& i_worldName);
    UnchartedWorldType GetUnchartedWorldType();
    UnchartedWorldType GetUnchartedWorldType(const std::string& i_worldName);
    bool IsTutorialWorld();
    bool IsTutorialWorld(const std::string worldName);

	// level desc
    SexyString GetCurrentThemeName(int index);
    SexyString GetCurrentThemeDescription(int index);
    std::vector<int> GetChallengeStatus(int levelIndex);
    SexyString GetCurrentLevelChallengeDesc(int index);

    // materials
    int GetCurrentKeyCount();
    int GetCurrentStarCount();
    int GetCurrentMaxStarNumber();
	int GetCurrentKeyNumber();
	int GetMaxKeyNumber();

    int GetCurrentLevelStarNumber();
    int GetCurrentLevelMaxStarNumber();

    // get level data
    std::vector<UnchartedModeLevelBonusData> GetCurrentLevelBonus(bool hard);
    std::vector<UnchartedModeLevelBonusData> GetCurrentLevelFirstRewardBonus(bool hard);
    std::vector<UnchartedModeLevelBonusData> GetCurrentLevelPreviewBonus(bool hard);
    bool IsCurrentLevelFirstReward();
    int GetCurrentLevelFirstReward(bool hard);

    // world map level
    const std::string& GetCurrentWorldPrefix(bool i_hard);
    std::string GetCurrentPVZ2UnchartedModeWorld(bool i_hard);
    std::string GetCurrentWorldResourcePrefix();
    std::string GetCurrentLandingLevel(bool i_hard);
    void GoToPVZ2UnchartedModeWorldMap(bool i_hard);
    void GoToPVZ2UnchartedModeMainMenu();
    bool IsNodeUnlocked(int i_index);
    std::string GetCurrentLevel();
    std::string GetPrefixWorld();
    int GetWorldIndexOfLevel(std::string level);
    int GetCurrentWorldLevelIndex();// use in worldmap
    int GetCurrentWorldLevelIndexByNetworkMgr();// use in board
    int GetCurrentPrefixWorldIndex();
    std::string GetChallengeListStr(std::vector<bool> list);

    int GetBirthdayCurrentEarnedStars();
    int GetBirthdayMaxEarnedStars();
    int GetBirthdayCurrentLevelSelectedStars();
    bool HasSelectedCollection(const std::string& i_aliasName);

    // network request
    void SendGet_MainEntry(bool i_fromLevel = false);
    void SendPost_EndPlay(PVZ2UnchartedModeEndPlayParamData data);
    void SendPost_Play(PVZ2UnchartedModeStartPlayParamData data = {});

    // show ui
    void ShowTips();
    void ShowKeyTips();
    void ShowLevelSetupScreen(MapEventItem* i_event, const Delegate1<const std::string&>& i_onPlayLevelCallback);
    void ShowTipsDialog(std::string title, std::string desc);

    // tips
    int GetWorldCount();
    bool HasLockedHardLevel();
    bool CheckShowTips();
    bool CheckShowNotice();

    SexyString GetCurrentUnchartedBirthdayDescription();
    int GetCurrentUnchartedBirthdayHeadshotPrizeId();

    bool IsThemeDisabled(const std::string& i_levelName);
    bool IsThemeDisabled(int i_type, const std::string& i_levelName);

    void ShowHowToPlay();
}


#endif /* PVZ2UNCHARTEDMODEUTILS_H_ */
