//
//  TLog.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-7-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TLog__
#define __PlantsVersusZombies2__TLog__

//#if SEXY_IS_WECHAT_ENABLED
//    #define SUPPORT_TLOG
//#endif

#include "Precompile.h"
#include "NetworkMgr.h"
#include "TLogCache.h"
#include "TimeMgr.h"

#define GAME_SERVER_ID ("GameSvrId")        //Not Sure GameSvrId

#define GAME_APP_ID    ("GameAppID")        //Not Sure GameAppID

#define REG_CHANNEL    ("001")              //Not Sure RegChannel

#define LOGIN_CHANNEL  ("001")              //Not Sure LoginChannel

//Not Implement CpuHardware
//Not Implement GLRender

//////////////////TMoney//////////////////////
enum TMoneyType
{
    T_MONEY    = 0,
    T_DIAMOND  = 1,
    T_FRIENDLY = 2
};

enum TMoneyAddOrReduce
{
    T_MONEY_ADD     = 0,
    T_MONEY_REDUCE  = 1
};

enum TMoneyReasonType
{
    T_MoneyReason_Money_BuyPlant = 0,
    T_MoneyReason_Money_PlayYeti,
    
    T_MoneyReason_Diamond_BuyCoins,
    T_MoneyReason_Diamond_UsePowerup,
    T_MoneyReason_Diamond_BuyPlantfood,
    T_MoneyReason_Diamond_BuySun,
    T_MoneyReason_Diamond_BuyPlant,
    T_MoneyReason_Diamond_UnLockKeyGate,
    T_MoneyReason_Diamond_UnLockStarGate
    
};

struct TMoney
{
    TMoney()
    {
        m_moneytype = T_MONEY;
        m_addorreduce = T_MONEY_ADD;
        m_reasontype = T_MoneyReason_Money_BuyPlant;
        
        m_aftermoney = 0;
        m_moneynum = 0;
    }
    TMoneyType m_moneytype;
    TMoneyAddOrReduce m_addorreduce;
    TMoneyReasonType m_reasontype;
    
    int m_aftermoney;
    int m_moneynum;
};
//////////////////////////////////////////////

/////////////////TItem////////////////////////
enum TItemAddOrReduce
{
    T_ITEM_ADD     = 0,
    T_ITEM_REDUCE  = 1
};

enum TItemType
{
    T_ITEM_TYPE_KEY   = 0,
    T_ITEM_TYPE_PLANT = 1
};

struct TItem
{
    TItem()
    {
        m_addorreduce = T_ITEM_ADD;
        m_itemType    = T_ITEM_TYPE_KEY;
        
        m_itemId     = 0;
        m_aftercount = 0;
        m_count      = 0;
    }
    
    TItemAddOrReduce m_addorreduce;
    TItemType        m_itemType;
    
    int m_itemId;
    int m_aftercount;
    int m_count;
};
//////////////////////////////////////////////

/////////////////TItemMoney///////////////////
struct TItemMoney
{
    TItemMoney()
    {
        m_moneytype = T_MONEY;
        m_itemType  = T_ITEM_TYPE_KEY;
        
        m_itemId = 0;
        m_money  = 0;
        m_count  = 0;
    }
    
    TMoneyType m_moneytype;
    TItemType  m_itemType;
    
    int m_itemId;
    int m_money;
    int m_count;
};
//////////////////////////////////////////////

/////////////////TPlayerStar//////////////////
struct TPlayerStar
{
    TPlayerStar()
    {
        m_starchange = 0;
        m_beforestar = 0;
        m_afterstar  = 0;
        m_time       = 0;
    }
    int m_starchange;
    int m_beforestar;
    int m_afterstar;
    int m_time;
};
//////////////////////////////////////////////

/////////////////TSNSType/////////////////////
enum TSNSType
{
    T_SNSTYPE_SHOWOFF = 0,
    T_SNSTYPE_SHARE,
    T_SNSTYPE_SENDSUNSHINE,
    T_SNSTYPE_RECEIVESUNSHINE,
    T_SNSTYPE_SENDPROVOKE,
    T_SNSTYPE_RECEIVEPROVOKE,
    T_SNSTYPE_OTHER
};
//////////////////////////////////////////////

/////////////////TRound///////////////////////
enum TBATTLETYPE
{
    BATTLE_0STAR = 0,
    BATTLE_1STAR,
    BATTLE_2STAR,
    BATTLE_3STAR,
    BATTLE_YETI
};

enum TBATTLERESULT
{
    TBATTLERESULT_NONE     = -1,
    TBATTLERESULT_WON      = 1,
    TBATTLERESULT_RESTART  = 2,
    TBATTLERESULT_LOST     = 3,
    TBATTLERESULT_QUIT     = 4,
    TBATTLERESULT_QUIT_APP = 5
};

struct TRound
{
    TRound()
    {
        m_battle_id = 0;
        m_battle_type = 0;
        m_round_time = 0;
        m_result = 0;
        m_rank = 0;
        m_gold = 0;
    }
    int m_battle_id;
    int m_battle_type;
    int m_round_time;
    int m_result;
    int m_rank;
    int m_gold;
};
//////////////////////////////////////////////

class TLog
{
public:
    TLog();
    virtual ~TLog();
    
    void Initialize();
    
    void Update();
    
    // Log Interface
    
    void PlayerRegister();
    
    void PlayerLogin();
    
    void PlayerLogout();
    
    void MoneyFlow(TMoney & tmoney);
    
    void ItemFlow(TItem & titem);
    
    void ItemMoneyFlow(TItemMoney & titemMoney);
    
    void PlayerStarFlow(TPlayerStar & star);
    
    void SnsFlow( int RecNum, int Count, TSNSType type );
    
    void RoundFlow(TRound & round);
    
    // Cache Interface
    
    void LoadCache();
	void SaveCache();
    
private:
	std::string GetMobileStrByType(int i_type);
    std::string getCacheFilename();
    
    TLogCache * GetTLogCache();
    
    void OutPutDebugLog(ParaMap& params);
    
    int GetTotalStarNum();
    
private:
    bool m_bIsEnable;
    
    time_t m_TimeStart;
    
    pvztime_t   m_lastSendCacheTime;
    
    std::string m_game_server_id;
    std::string m_game_app_id;
    std::string m_plat_id;
    std::string m_client_version;
    std::string m_system_software;
    std::string m_system_hardware;
    std::string m_telecom_oper;
    std::string m_network_state;
    std::string m_screen_width;
    std::string m_screen_hight;
    std::string m_density;
    std::string m_reg_channel;
    std::string m_login_channel;
    std::string m_uuid;
    std::string m_memory;
    std::string m_device_id;
    std::string m_gl_version;
    
};

extern TLog * gTLog;

#endif /* defined(__PlantsVersusZombies2__TLog__) */
