/*
 * CardGameUtils.h
 *
 *  Created on: 2022-5-27
 *      Author: admin
 */

#ifndef CARDGAMEUTILS_H_
#define CARDGAMEUTILS_H_

#include "MapEventItem.h"
//#include "PVZ1ModeNetworkMgr.h"
#include "CardGameNetworkMgr.h"

namespace CardGameUtils
{
	bool IsPlayingCardGame();

	// network request
    void SendPost_EndPlay(PVZ2UnchartedModeEndPlayParamData data);

    // Card
    const std::vector<CardGameCardInfo>& GetCardGameCardInfos();
    const std::vector<CardGameCardInfo>& GetCardGameSelectInfos();
    const std::vector<CardGameCardInfo>& GetCardGameCheckedSelectInfos();

	// show ui
	void ShowLevelSetupScreen(MapEventItem* i_event, const Delegate1<const std::string&>& i_onPlayLevelCallback);

	void GoToCardGameWorldMap(const std::string& i_prefixWorld, bool i_isHard);
	bool IsInQueuedCardGameWorldMap();
	bool IsInCardGameWorldMap();
	void GoToCardGameMainMenu();
	bool IsHardMode();
	void SetIsHardMode(bool hardMode);
	bool HasCompleteTutorial();
	void EnterTutorial();
	const std::string& GetCurrentWorldPrefix(bool i_hard);
	std::string GetPrefixWorld();
	std::string GetCurrentLevel();
	int GetWorldIndexOfLevel(std::string level);
	int GetCurrentWorldLevelIndex();
	int GetCurrentWorldLevelIndexByNetworkMgr();// use in board

	// get level data
    std::vector<CardGameLevelBonusData> GetCurrentLevelBonus(bool hard);
    std::vector<CardGameLevelBonusData> GetCurrentLevelFirstRewardBonus(bool hard);
    std::vector<CardGameLevelBonusData> GetCurrentLevelCardBonus(bool hard);
    bool IsCurrentLevelFirstReward();
    int GetCurrentLevelFirstReward(bool hard);

    // get level desc
    std::vector<int> GetChallengeStatus(int levelIndex, bool isHard = false);
    SexyString GetCurrentLevelChallengeDesc(int index);
    std::string GetChallengeListStr(std::vector<bool> list);
    int GetCurrentStarCount();

    // network request
	void SendGet_MainEntry(bool i_fromLevel = false);
	void SendPost_EndPlay(CardGameEndPlayParamData data);
	void SendPost_Play(CardGameStartPlayParamData data = {});
}

#endif /* CARDGAMEUTILS_H_ */
