/*
 * DailyRewardConfig.h
 *
 *  Created on: Jul 30, 2014
 *      Author: lijie
 */

#ifndef DAILYREWARDCONFIG_H_
#define DAILYREWARDCONFIG_H_

#include "PVZDB.h"

enum DailyRewardType
{
	E_COINS_REWARD = 0,
	E_GEMS_REWARD,
	E_KEY_REWARD,
	E_PLANT_REWARD,
	E_AVATAR_REWARD,
	E_PLANT_PIECE_REWARD,
	E_AVATAR_PIECE_REWARD,
	E_ACCESSORY_REWARD,
	E_ACCESSORY_PIECE_REWARD,

	E_DAILYREWARD_COUNT,
};

struct DailyRewardData
{
	std::string rewardItem;
	DailyRewardType rewardType;
	int rewardAmount;
};

class DailyRewardConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(DailyRewardConfig, Sexy::RtObject, Sexy::RtClass);

	DailyRewardConfig();
	virtual ~DailyRewardConfig();

	static void CheckForUpdate();
	bool CheckDailyConfigValid(int iVersion);

	int GetVersion(){ return m_iVersion; }
	int GetStartYear(){ return m_iStartYear; }
	int GetStartMonth(){ return m_iStartMonth; }
	int GetStartDay(){ return m_iStartDay; }
	time_t GetStartTime();
	bool NeedRefreshDailySignSheet();

	const DailyRewardData* GetReward(int iDayCount);
	int GetDailyRewardCount(){ return static_cast<int>(m_DailyRewardList.size()); }

	static bool LoadDefaultDailyConfig();

private:
	int m_iVersion;
	int m_iStartYear;
	int m_iStartMonth;
	int m_iStartDay;
	std::vector<DailyRewardData> m_DailyRewardList;
};


#endif /* DAILYREWARDCONFIG_H_ */
