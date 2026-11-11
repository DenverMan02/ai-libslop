/*
 * PVZ1ModeNetworkMgr.h
 *
 *  Created on: 2021-7-30
 *      Author: zhousen
 */

#ifndef PVZ1MODENETWORKMGR_H_
#define PVZ1MODENETWORKMGR_H_


#include "Core.h"
#include "NetworkServiceManager.h"
#include "NetworkData.h"
#include "PVZ1ModeDataPacket.h"

///
/// Main Entry Network Data
///
class PVZ1ModeMainEntryData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PVZ1ModeMainEntryData, Sexy::RtObject, Sexy::RtClass);

public:
    std::string CurrentWorldPrefix;
    std::string CurrentHardLevelWorldPrefix;
    bool CanPlay;
    int CurrentTheme;
    std::vector<int> CurrentThemes;
    int CurrentFuel;
    std::vector<PVZ1ModeLevelBonusNetworkData> BonusDataListNormal;
    std::vector<PVZ1ModeLevelBonusNetworkData> BonusDataListHard;
    int CurrentWeek;
	int CurrentStage;
	int LeftTime;
    int ThemeLeftTime;
    bool HasLeagueChangeEvent;
    bool HasSeasonChangeEvent;
	int HardModuleUnlocked;
	std::vector<std::vector<int> > ChallengeStatusList;// for easy mode challenge complete status, 0 = not complete 1 = complete
	std::vector<std::vector<int> > HardLevelThemes;
	int Pvz1HardEliteLevelNumber;// for task PvZ1PassAllHardEliteListener
};

///
/// Start Of Play Network Data
///
class PVZ1ModeStartOfPlayData : public INetworkData
{
public:
	RT_CLASS_DEFINE(PVZ1ModeStartOfPlayData, INetworkData, RtClass);

public:
	int CurrentFuel;
	std::string ArtifactOrderId;
};

///
/// End Of Play Network Data
///
class PVZ1ModeEndOfPlayData : public INetworkData
{
public:
	RT_CLASS_DEFINE(PVZ1ModeEndOfPlayData, INetworkData, RtClass);

public:
	std::vector<S2C_BonusInfo> BonusList;
	bool WinResult;
	int ResultType;
};

///
/// Start Of Play Data for Parameters
///
struct PVZ1ModeStartPlayParamData
{
	bool HardMode = false;// 1 : normal mode , 2 : hard mode
	int Level = 0;// level number from 1...
};

///
/// End Of Play Data for Parameters
///
struct PVZ1ModeEndPlayParamData
{
	bool HardMode = false;// 1 : normal mode , 2 : hard mode
	bool WinResult = false;// win or lose
	int Level = 0;// level number from 1...
	std::string ChooseListStr = "";// choose string
	int ResultType = 0;// result type : PVZ1ModeResultType
};


///
/// PVZ1Mode Network Mgr
///
class PVZ1ModeNetworkMgr : public LazySingleton<PVZ1ModeNetworkMgr>
{
public:
	PVZ1ModeNetworkMgr();
	~ PVZ1ModeNetworkMgr();

	const PVZ1ModeMainEntryData& GetMainEntryInfo() { return m_MainEntryData; }
	const PVZ1ModeStartOfPlayData& GetPlayInfo() { return m_StartOfPlayData; }
	const PVZ1ModeEndOfPlayData& GetEndPlayInfo() { return m_EndOfPlayData; }

	void RequestGetMainEntryData(bool i_fromLevel);
	void RequestStartPlayData(PVZ1ModeStartPlayParamData data);
	void RequestEndPlayData(PVZ1ModeEndPlayParamData data);

	void initTestData();
	void SetIsHardMode(bool i_hard) { m_hardLevel = i_hard; }
	bool GetIsHardMode() { return m_hardLevel; }
	void AddTimeEnergy(int energy);
	std::vector<bool>& GetChooseChallengeList();
	void SetCurrentLevel(std::string level);
	std::string GetCurrentLevel() const { return m_currentLevel; }
	void SetCurrentLevelIndex(int index);
	int GetCurrentLevelIndex() const { return m_currentLevelIndex; }
	void SetStartBoardTime(pvztime_t time) { m_startBoardTime = time; }
	void SetElapseTime(pvztime_t time) { m_elapseTime = time; }
	pvztime_t GetElapseTime() const { return m_elapseTime - m_startBoardTime; }

	std::vector<PVZ1ModeLevelBonusData> GetLevelBonus(bool hard, int levelIndex);
	std::vector<PVZ1ModeLevelBonusData> GetLevelFirstRewardBonus(bool hard, int levelIndex);
	std::vector<std::vector<S2C_BonusInfo> > GetCurrentLevelChallengeBonus(bool hard, int levelIndex);
	std::vector<int> GetChallengeStatus(int levelIndex);
	int GetCurrentLevelFuel(bool hard, int levelIndex);
	int GetCurrentLevelFirstReward(bool hard, int levelIndex);
	bool GetIsFromLevel() { return m_fromLevel; }
	void SetLevelEnd(bool end) { m_levelEnd = end; }
	bool GetLevelEnd() { return m_levelEnd; }
	void SetCheatWin(bool win) { m_cheatWin = win; }
	bool GetCheatWin() { return m_cheatWin; }
	void SetFromTutorial(bool i_fromTutorial) { m_fromTutorial = i_fromTutorial; }
	bool IsFromTutorial() { return m_fromTutorial; }
	std::vector<int> GetHardLevelTheme(int i_levelIndex);
	int GetHardEliteLevelNumber();

private:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void syncMainEntryInfo();
	void syncWorldMapInfo(const PVZ1ModeMainEntryData& i_data);

	PVZ1ModeMainEntryData m_MainEntryData;
	PVZ1ModeStartOfPlayData m_StartOfPlayData;
	PVZ1ModeEndOfPlayData m_EndOfPlayData;
	bool m_requested;

	std::vector<bool> m_chooseChallengeList;
	std::string m_currentLevel;
	int m_currentLevelIndex;
	bool m_fromLevel;
	bool m_hardLevel;
	pvztime_t m_startBoardTime;
	pvztime_t m_elapseTime;
	bool m_levelEnd;
	bool m_cheatWin;
	bool m_fromTutorial;
};


#endif /* PVZ1MODENETWORKMGR_H_ */
