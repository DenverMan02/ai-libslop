#ifndef __Load_Collector_H__
#define __Load_Collector_H__

#include <string>
#include "DNode/DValue.h"

#define SUPER_CLASS(name) typedef name super;
#define OUT_PARAM

class PublicBasicInfo
{
public:
    
    PublicBasicInfo();
    
    void                     setNeedUserID(bool iNeedUserID);
    
    virtual PublicBasicInfo& getBasicInfo(OUT_PARAM DValue & value);
    virtual PublicBasicInfo& getBehavior(OUT_PARAM DValue & value);
    virtual std::string      getTableName() {return "unknown";}
    virtual PublicBasicInfo& getResult(const std::string& result,OUT_PARAM DValue& value);
    
protected:
    std::string  getPCPID();
    std::string  getUserID();
    std::string  getCharacterID();
    std::string  getUniqueCharacterID();
    std::string  getClientTime();
    std::string  getVersionID();
    std::string  getChannelID();
    std::string  getSessionID();
    std::string  getProjectCode();
    std::string  getServerID();
    std::string  getOSVersion();
    std::string  getDeviceModel();
    std::string  getConnectType();
    std::string  getLocalIP();
    std::string  getPublicIP();
    
    std::string  getCPU();
    std::string  getGPUModel();
    std::string  getResolutionOfScreen();
    std::string  getMemory();
    std::string  getStorage();
    std::string  getProfileCreatedTime();
    std::string	 getDefineID();
    std::string	 getSignature();
    std::string	 getTargetPlatform();
    
    bool         bNeedUserID;
};

class Log_GameStart :public PublicBasicInfo
{
public:
    SUPER_CLASS(PublicBasicInfo)
    virtual Log_GameStart& getBasicInfo(OUT_PARAM DValue & value) override
    {
        super::getBasicInfo(value);
        
        return *this;
    }
    virtual Log_GameStart& getBehavior(OUT_PARAM DValue & value) override;
    virtual std::string    getTableName() override {return "GameStart";}
};


class Log_GameStart_Funnel :public PublicBasicInfo
{
public:
    SUPER_CLASS(PublicBasicInfo)
    
    virtual Log_GameStart_Funnel& getBasicInfo(OUT_PARAM DValue & value) override
    {
        super::getBasicInfo(value);
        
        return *this;
    }
    virtual Log_GameStart_Funnel& getBehavior(OUT_PARAM DValue & value) override{return *this;}
    virtual std::string           getTableName() override {return "GameStart_Funnel";}
    
    virtual Log_GameStart_Funnel& funnel(const std::string& behaviorID,OUT_PARAM DValue & value);
    virtual Log_GameStart_Funnel& funnelStart(const std::string& behaviorID,OUT_PARAM DValue & value);
    virtual Log_GameStart_Funnel& funnelEnd(const std::string& behaviorID,OUT_PARAM DValue & value);
    virtual Log_GameStart_Funnel& funnelEnd(const std::string& behaviorID,OUT_PARAM DValue & value,bool isSuccess);
    
private:
    static std::unordered_map<std::string, uint64> s_startTimeMap;
};

class Log_Register :public PublicBasicInfo
{
public:
    SUPER_CLASS(PublicBasicInfo)
    
    virtual std::string   getTableName() override {return "Register";}
    
    virtual Log_Register& getBasicInfo(OUT_PARAM DValue & value) override;
    virtual Log_Register& getBehavior(OUT_PARAM DValue & value) override;
};

class Log_Item_Login :public Log_Register
{
public:
    SUPER_CLASS(Log_Register)
    
    virtual Log_Item_Login& getBasicInfo(OUT_PARAM DValue & value) override
    {
        super::getBasicInfo(value);
        
        return *this;
    }
    
    virtual std::string     getTableName() override {return "Item_Login";}
    
    virtual Log_Item_Login& getBehavior(OUT_PARAM DValue & value) override;
    
    virtual Log_Item_Login& getItems(const std::string& items,OUT_PARAM DValue & value);
    
};

struct RechargeInfo
{
    RechargeInfo()
    :isSuccess(true)
    ,paySN("unknown")
    ,SKU_ID("unknown")
    ,unit_price("unknown")
    ,pay_source("unknown")
    ,platform("unknown")
    ,return_code("unknown")
    ,level(0)
    ,beforeLevel(0)
    ,afterLevel(0)
    {
    }
    bool        isSuccess;
    std::string paySN;
    std::string SKU_ID;
    std::string unit_price;
    std::string pay_source;
    std::string platform;
    std::string return_code;
    int         level;
    int         beforeLevel;
    int         afterLevel;
};

class Log_Recharge :public Log_Register
{
public:
    
    SUPER_CLASS(Log_Register)
    
    virtual Log_Recharge& getBasicInfo(OUT_PARAM DValue & value) override
    {
        super::getBasicInfo(value);
        
        return *this;
    }
    
    virtual std::string   getTableName() override {return "Recharge_Info";}
    
    virtual Log_Recharge& getBehavior(OUT_PARAM DValue & value) override {return *this;}
    
    virtual Log_Recharge& getRechargeInfo(const RechargeInfo& rechargeInfo,OUT_PARAM DValue& value);

};

class Log_Ingame_Behavior :public Log_Register
{
public:
    SUPER_CLASS(Log_Register)
    
    virtual std::string   getTableName() override {return "Ingame_Behavior";}
    
    virtual Log_Ingame_Behavior& getBasicInfo(OUT_PARAM DValue & value) override
    {
        super::getBasicInfo(value);
        
        return *this;
    }
    
    virtual Log_Ingame_Behavior& getBehavior(OUT_PARAM DValue & value) override {return *this;}
    
    virtual Log_Ingame_Behavior& getBehaviorInfo(const std::string& behaviorID,const std::vector<std::string>& otherParams,OUT_PARAM DValue& value);
};

class Log_TGA :public PublicBasicInfo
{
public:
    SUPER_CLASS(PublicBasicInfo)

    virtual Log_TGA& getLogInfo(const std::string& i_logId, OUT_PARAM DValue & value);
    virtual Log_TGA& getBasicInfo(OUT_PARAM DValue & value) override;
    virtual Log_TGA& getBasicInfoForLogin(OUT_PARAM DValue & value);
    virtual Log_TGA& getOtherInfo(const std::vector<std::string>& otherParams,OUT_PARAM DValue& value);
};

class BehaviorLog
{
public:
    static void resume();
    static void pause();
    static void gameStart();
    static void gameEnd();
    static void funnel(const std::string& behaviorID);
    static void funnelStart(const std::string& behaviorID);
    static void funnelEnd(const std::string& behaviorID);
    static void funnelEnd(const std::string& behaviorID,bool isSuccess);
    static void gameRegister();
    static void itemLogin(const std::string& items);
    static void recharge(const RechargeInfo& rechargeInfo,const std::string& result);
    static void inGameBehavior(const std::string& behaviorID,const std::vector<std::string>& otherParams,const std::string& result);
    static void event(const std::string& eventName,const std::vector<std::string>& otherParams,const std::string& result);
    static void itemPurchase(const std::string& location,const std::string& locationName,const std::string& result);
    static void itemPurchaseEx(const std::string& location,const std::string& locationName,const std::string& other1,const std::string& other2,const std::string& result);
    static void missionStart(const std::string& missionName,int lv,int missionTimes);
    static void missionEnd(const std::string& missionName,bool isFinished,const std::string& otherParam1,const std::string& otherParam2,const std::string& result, const std::string& expPlantInfo);
    static void missionEvent(const std::string& eventName,const std::string& missionName,const std::string& param,const std::string& result);
    static void missionPurchase(const std::string& location,const std::string& missionName,const std::string& result);
    static void missionPurchaseEx(const std::string& location,const std::string& missionName,const std::string& other,const std::string& result);
    static void missionPay(const std::string& levelName,const std::string& itemName,const std::string& result);
    
    static void sendLog(const std::string& tableName,const DValue& info);
    static void needRefreshSession();
    static std::string getModeString();
};

#endif
