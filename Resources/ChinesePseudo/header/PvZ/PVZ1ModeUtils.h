/*
 * PVZ1ModeUtils.h
 *
 *  Created on: 2021-7-16
 *      Author: zhousen
 */

#ifndef PVZ1MODEUTILS_H_
#define PVZ1MODEUTILS_H_

#include "PVZ1ModeNetworkMgr.h"

//namespace Message
//{
//	void PVZ1NetworkResponseReceived(int i_context, int i_status);
//}


namespace PVZ1ModeUtils
{
	// global
    bool IsPlayingPVZ1Level();
    bool IsPlayingPVZ1Tutorial();
    bool HasCompleteTutorial();
    void CompleteTutorial();
    void EnterTutorial();
    bool IsInPVZ1WorldMap();
    bool IsInQueuedPVZ1WorldMap();
    bool HasLeagueChangeEvent();
    bool HasSeasonChangeEvent();
    void ResetPVZ1Mode(bool i_hard);
    bool IsThemeDisabled(const std::string& i_levelName);
    bool IsThemeDisabled(int i_type, const std::string& i_levelName);
    bool IsHardMode();
    void SetIsHardMode(bool i_hard);
    void SetFromTutorial(bool i_fromTutorial);
    bool IsFromTutorial();
    void GetPlantBannedList(std::vector<int>& i_list);
    void GetPlantBannedList(std::vector<std::string>& i_list);
    void GetPvZ1PlantList(std::vector<std::string>& i_list);
    int GetCurrentWeekIndex();
    const std::string& GetCurrentWorldPrefix(bool i_hard);
    bool PlayerCanPlay();
    int		   GetCurrentTheme();
    int        GetCurrentStage();
    std::vector<int> GetCurrentThemeList();
    SexyString GetCurrentThemeName(int index);
    SexyString GetCurrentThemeDescription(int index);
    SexyString GetCurrentThemeName();
    SexyString GetCurrentThemeDescription();
    int	 GetCurrentFuel();
    int  GetCurrentCoin(bool isHard = false);
    void AddTimeEnergy(int energy);
    bool IsCurrentLevelFirstReward();
    std::vector<bool> GetLevelChallengeChoose();
    void TryCompleteLevel(const std::string& i_level);
    void MarkCurrentPVZ1LevelComplete(const std::string& i_level);
    int GetNormalLevelNumber();
	int GetPvz1HardEliteLevelNumber();

    // get description and theme
    SexyString GetMainModeText(int modeIndex, bool hard);
    SexyString GetMainModeDesc(int modeIndex, bool hard);

    int GetMainThemeIndex();
    SexyString GetMainThemeText(int themeIndex);
    SexyString GetMainThemeDesc(int themeIndex);
    SexyString GetCurrentLevelChallengeDesc(int index);
    std::vector<PVZ1ModeChallengeProperty> GetLevelChallengePropertys(int level);

    // get level data
    std::vector<PVZ1ModeLevelBonusData> GetCurrentLevelBonus(bool hard);
    std::vector<PVZ1ModeLevelBonusData> GetCurrentLevelFirstRewardBonus(bool hard);
    std::vector<std::vector<S2C_BonusInfo> > GetCurrentLevelChallengeBonus(bool hard);
    std::vector<S2C_BonusInfo> GetCurrentLevelFinalBonus(bool hard, bool firstReward);
    int GetCurrentLevelFuel(bool hard);
    int GetCurrentLevelFirstReward(bool hard);
    std::string GetChooseListStr();
    std::vector<int> GetChallengeStatus(int levelIndex);
    std::vector<int> GetHardLevelTheme(int i_levelIndex);

    // world map level
    std::string GetCurrentPVZ1World(bool i_hard);
    std::string GetCurrentLandingLevel(bool i_hard);
    void GoToPVZ1WorldMap(bool i_hard);
    void GoToPVZ1MainMenu();
    bool IsNodeUnlocked(int i_index);
    bool IsZombossLevel(const MapEventItem* i_event);
    std::string GetCurrentLevel();
    int GetWorldIndexOfLevel(std::string level);
    int GetCurrentWorldLevelIndex();// use in worldmap
    int GetCurrentWorldLevelIndexByNetworkMgr();// use in board
    bool GetIsFromLevel();

    // network request
    void SendGet_MainEntry(bool i_fromLevel = false);
    void SendPost_EndPlay(PVZ1ModeEndPlayParamData data);
    void SendPost_Play(PVZ1ModeStartPlayParamData data = {});

    // show ui
    void ShowHowToPlay(PVZ1_HOW_TO_PLAY_TYPE type);
    void ShowCreditsTipsUI();
    void ShowTips(SexyString desc);
    void ShowLevelSetupScreen(MapEventItem* i_event, const Delegate1<const std::string&>& i_onPlayLevelCallback);

    float GetRemainingEnergy();
    void TakeTimeEnergy(float i_energy);

    bool IsPoolStage();
}


#endif /* PVZ1MODEUTILS_H_ */
