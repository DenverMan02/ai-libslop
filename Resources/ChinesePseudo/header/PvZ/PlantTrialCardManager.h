#ifndef PlantTrialCardManager_H
#define PlantTrialCardManager_H

#include "Singleton.h"
#include "NetworkData.h"

struct TrialCardConfig
{
    TrialCardConfig()
    :ID(0),
    Type(0),
    PlantID(0),
    PlantLevel(0),
    DurationHours(0)
    {

    }

    int ID;
    int Type;
    int PlantID; //trial id
    int PlantLevel;
    int DurationHours;
    std::vector<S2C_BonusInfo> ExchangeList;
};

struct PlayerTrialCardInfo
{
    PlayerTrialCardInfo()
    :ID(0),
    Number(0)
    {

    }

    int ID;
    int Number;
};

struct PlayerTrialStatusInfo
{
    PlayerTrialStatusInfo()
    :ID(0),
    StartTime(0),
    EndTime(0)
    {

    }

    int ID;
    time_t StartTime;
    time_t EndTime;
};

class TrialSynchronizeData : public INetworkData
{
public:
	RT_CLASS_DEFINE(TrialSynchronizeData, INetworkData, RtClass);

    std::vector<TrialCardConfig>            TrialCardConfigList;
    std::vector<PlayerTrialCardInfo>        PlayerTrialCardList;
    std::vector<PlayerTrialStatusInfo>      PlayerTrialStatusList;

    std::vector<S2C_BonusInfo>              RewardList;

    void Clear();
};



class TrialCardManager : public LazySingleton<TrialCardManager>
{
public:
//trial card
    static bool ContainsId(int i_id);
    bool HasConfig(int i_id);

    void AddTrialCard(int i_cardId, int i_amount);
    void SubTrialCard(int i_cardId);

    TrialCardConfig GetTrialCardConfigByID(int i_cardId);
    PlayerTrialCardInfo GetPlayerTrialCardByID(int i_cardId);
    PlayerTrialStatusInfo GetPlayerTrialStatusByID(int i_cardId);

    std::vector<TrialCardConfig> GetTrialCardConfigList();
    std::vector<PlayerTrialCardInfo> GetPlayerTrialCardList();
    std::vector<PlayerTrialStatusInfo> GetPlayerTrialStatusList();

    SexyString GetTrialCardName(int i_id);
    SexyString GetTrialCardUse(int i_id);
    SexyString GetTrialCardGetWay(int i_id);
    
public:
//trial status
    bool IsTrialingPlant(int i_plantId);
    PlayerTrialStatusInfo GetBestTrialStatus(int i_plantId);
    TrialCardConfig GetConfigForBestTrialStatus(int i_plantId);
    std::vector<PlayerTrialStatusInfo> GetTrialStatusList(int i_plantId);


public:
//utils
    bool CanUseOnCurrentLevel();
    void SynchronizeTrialData();

    TrialSynchronizeData SynchronizeData;

public:
    void CheckTrial();
    bool BestThenRight(PlayerTrialStatusInfo& i_left, PlayerTrialStatusInfo& i_right);
};


#define gTrialCardManager (TrialCardManager::GetInstancePtr())


#endif