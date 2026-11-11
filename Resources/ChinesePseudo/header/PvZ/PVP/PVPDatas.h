//
//  PVPDatas.hpp
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/11/24.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef __PVPDatas_h_
#define __PVPDatas_h_

#include "GameObject.h"
#include "PVZTypes.h"
// do not include more here!!!

//-----------------------------------------------------------
// do nothing, just for data reflection
class PVPData : public GameObject
{
public:
    RT_CLASS_DEFINE(PVPData, GameObject, RtClass);
};

//-----------------------------------------------------------
class PVPZombieData
{
public:
    PVPZombieData()
    {}
    
public:
    std::string     m_zombieType;
    int             m_level = 0;
    bool            m_canUpgrade = true;
    
    int             m_awakenLevel = 0;
    bool            m_canAwaken = true;
};
typedef PVPZombieData PVPSkillData;
typedef std::map<std::string, PVPZombieData> MapZombieDatas;
typedef std::vector<PVPZombieData> VecZombieDatas;
typedef MapZombieDatas MapSkillDatas;
typedef VecZombieDatas VecSkillDatas;

//-----------------------------------------------------------
// Arena plants position data
struct ArenaPlantPositionData
{
    int PlantId;
    int Row;
    int Col;
    ArenaPlantPositionData()
    {
        PlantId = -1;
        Row = 0;
        Col = 0;
    }
};

//-----------------------------------------------------------
// Arena plants info
struct ArenaPlantInfoData
{
    int PlantId;
    int Level;
    int Avatar;
    std::string AccessoryType;
    ArenaPlantInfoData()
    {
        PlantId = -1;
        Level = 1;
        Avatar = 0;
        AccessoryType = "";
    }
};

//-----------------------------------------------------------
// Arena Defender Info
struct DefenderInfo
{
    DefenderInfo()
    {
        m_name = L"";
        m_profileId = 0;
        m_winCup = 0;
        m_lostCup = 0;
        m_winCurrency = 0;
    }
    
    std::wstring  m_name;
    int32         m_profileId;
    int32         m_winCup;
    int32         m_lostCup;
    int32         m_winCurrency;
};

//-----------------------------------------------------------
class PlayerPlantData : public RtObject
{
public:
    RT_CLASS_DEFINE(PlayerPlantData, RtObject, RtClass);
    PlayerPlantData();
public:
    std::vector<ArenaPlantPositionData> m_positionInfos;
    std::vector<ArenaPlantInfoData> m_plantInfos;
    int m_version;
    std::string m_levelName;
    std::string m_editLevelName;
    
    bool SerializeJson(const std::string &i_json);
    std::string SerializeObj();
};

//-----------------------------------------------------------
struct PVPCurrencyData
{
    int m_PVPCoin = 0;
    int m_PVPMedal = 0;
    int m_PVPCup = 0;
};

//-----------------------------------------------------------
// match server id, do not change!!!
enum PVPLabItemType
{
    LabItem_None = 0,
    LabItem_Base = 1,
    LabItem_Sun = 2,
    LabItem_Army = 3,
    LabItem_Zombie = 4,
    LabItem_AwakenZombie = 5,
    LabItem_AwakenPlant = 6,
    LabItem_Skill = 7,
};
class PVPLabData
{
public:
    PVPLabData();
    int             GetLabItemLevel(PVPLabItemType i_type);
    void            SetLabItemLevel(PVPLabItemType i_type, int i_level);
    
    void            SetUpgradeItem(PVPLabItemType i_type, int i_objID, int remainTime);
    PVPLabItemType  GetUpgradeItem() { return m_upgradeType; }
    int             GetUpgradeObjectID() { return m_objectID; }
    float           GetUpgradeEndTime() { return m_upgradeEndTime; }
protected:
    std::map<PVPLabItemType, int> m_MapLevel;
    PVPLabItemType     m_upgradeType;
    int     m_objectID;
    float   m_upgradeEndTime;
};

class PVPUpgradeData : public Sexy::RtObject
{
public:
    struct PVPBaseUpgradeData
    {
    public:
        int coin;
        int medal;
        int coinLimit;
        int medalLimit;
        int cost;
        float time;
        std::vector<std::string> unlockZombie;
        PVPBaseUpgradeData();
    };
    
    struct PVPLimitCostData
    {
    public:
        int limit;
        int cost;
        float time;
        PVPLimitCostData();
    };
    
    typedef PVPBaseUpgradeData Base;
    typedef PVPLimitCostData LimitCost;
public:
    RT_CLASS_DEFINE(PVPUpgradeData, Sexy::RtObject, Sexy::RtClass);
    
    PVPUpgradeData();
    virtual ~PVPUpgradeData();
    
    std::vector<Base> base;
    std::vector<LimitCost> sunLimit;
    std::vector<LimitCost> zombieLimit;
private:
};

//-----------------------------------------------------------
class S2C_PVP_BigMapPVPInfo
{
public:
    enum
    {
        STATUS_NONE = 0,
        STATUS_NORMAL = 1,
        STATUS_ATK_SUC = 2,
        STATUS_ATK_FAIL = 3,
        STATUS_EVIL_DAVID = 4,
    };
public:
    int     GetHouseID();
    bool    IsEvilDavid();
    bool    CheckTime();
    
public:
    int64 occupyId = 0;
    std::wstring occupyname;
    int level = 0;
    int cupNum = 0;
    int cupGain = 0;
    int goldGain = 0;
    int zoneId = 0;
    int zonePos = 0;
    int status = 0;
    int time = 0;
    int iDavidCompleteCount = -1;
    int iDavidMaxCompleteCount = -1;
    int iAttackWinMedal = 0;
    int attackPrice = 0;
};

class S2C_PVP_BigMapInfo
{
public:
    int     GetHouseID();
public:
    int64 occupyId = 0;
    int64 profileId = 0;
    std::wstring occupyname;
    int level = 0;
    int cupNum = 0;
    int cupMaxNum = 0;
    int goldNum = 0;
    int goldMaxNum = 0;
    int cupproducespeed = 0;
    int goldProduceSpeed = 0;
    int zoneId = 0;
    int zonePos = 0;
    int attackPrice = 0;
};

//-----------------------------------------------------------
class PvPRankMonthReward
{
public:
    int32 oldCup = 0;
    int32 newCup = 0;
    int32 rewardCoin = 0;
    
    int32 rankOrder = -1;
    int32 rewardMedal = 0;
};

#endif

