/*
 * ADManager.h
 *
 *  Created on: 2022-4-19
 *      Author: admin
 */

#ifndef ADMANAGER_H_
#define ADMANAGER_H_

#include "Singleton.h"
#include "LawnAppEnums.h"
#include "EASquared.h"
#include "NetworkData.h"

namespace Message
{
    void NotifyADWatchFinish(int i_type);
}

enum ADType
{
    ADType_None,
    ADType_Reward_Coin = 5,
    ADType_Reward_Gem = 6,
    ADType_Reward_Mystery = 7,
    ADType_Reward_Gacha = 8,
    ADType_Reward_ZTicket = 9,
    ADType_Reward_Fuel = 10,
    ADType_CustomLevel_Mower = 11,
    ADType_CustomLevel_Plantfood = 12,
    ADType_CustomLevel_Sun = 13,
    ADType_Reward_Sun = 14,
    ADType_Joust_Store = 15,
    ADType_Rift_Store = 16,
    ADType_DangerRoom_Store = 17,
    ADType_PlantFamily = 18,
    ADType_DailySign = 19,
    ADType_TransGenosisPlant = 20,
    ADType_TransGenosisAvatar = 21,
    ADType_Mower = 22,
    ADType_FestivalMode = 23,
    ADType_PlantAdventureSkip = 24,
    ADType_PlantAdventureBonusCount = 25,
    ADType_PlantAdventureBonusReward = 26,
    ADType_WishRefresh = 27,
    ADType_WishBonusCountGargantuarCrisis = 28,
    ADType_WishBonusCountDevilInvade = 29,
    ADType_WishBonusCountCrazyYeti = 30,
    ADType_DangerRoom_Refresh = 31
};

struct ADServerInfo
{
    ADServerInfo()
    : WatchedTimes(0)
    , MaxTimes(0)
    {

    }

    ADServerInfo(int i_watchedTimes, int i_maxTimes)
    : WatchedTimes(i_watchedTimes)
    , MaxTimes(i_maxTimes)
    {

    }

    int WatchedTimes;
    int MaxTimes;
};

struct ADRewardBonusInfo
{
    ADRewardBonusInfo()
    {
        Id = 0;
        Quantity = 0;
    }
    int Id;
    int Quantity;
};

class ADRewardData : public INetworkData
{
public:
    RT_CLASS_DEFINE(ADRewardData, INetworkData, Sexy::RtClass);

public:
    int Id;
    int WatchedTimes;
    std::vector<ADRewardBonusInfo> Rewards;
};

class ADManager : public LazySingleton <ADManager>
{
public:
    ADManager();
    ~ADManager();

    void onADFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    void SetCurrentADType(ADType i_type) { m_currentADType = i_type; }
    void ShowAD(ADType i_type);
    //ViewPositionType GetPositionTypeByADType(ADType i_type);
    void InitDefaultADMaps();
    int GetLeftADWatchCount(ADType i_type);
    int GetADWatchCount(ADType i_type);
    bool CanWatchAD(ADType i_type);
    bool CanWatchAD(const std::string& i_type);
    void SetADWatchCount(ADType i_type, int i_count);
    void TryRequestReward();
    void RequestReward();
    void RequestLocalReward();
    void InitADMaps(const std::vector<S2C_AdInfo>& i_infos);
    bool HasADReward();

private:
    bool isLocalReward(ADType i_type);
    bool isCustomLevelAD(ADType i_type);
    int LocalIdToServerId(ADType i_type);
    ADType ServerIdToLocalId(int i_id);
    ViewPositionType ToViewPositionType(ADType i_type);

    ADType m_currentADType;
    std::map<ADType, ADServerInfo> m_adMaps;
};

#define gADMgr ADManager::GetInstancePtr()


#endif /* ADMANAGER_H_ */
