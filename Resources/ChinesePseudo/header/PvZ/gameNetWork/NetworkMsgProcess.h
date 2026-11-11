/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 12
 ------------------------------------------------------------------------------------------------------------*/
#ifndef  NETWORKMSGPROCESS_H
#define  NETWORKMSGPROCESS_H

#include "HttpRequest.h"
#include "PacketID.h"
#include "NetWorkDef.h"
#include "NetworkCacheQueue.h"
#include "NetworkData.h"
#include "SocialInfo.h"
#include "HttpRequestNoErro.h"

#include <vector>
#include "DRef.h"

class ICloudRequestCallbackFunctionBase:public DRef
{
public:
    virtual void process(bool result){}
    virtual ~ICloudRequestCallbackFunctionBase(){}
};

template<typename ClassType,typename ParamType>
class ICloudRequestCallbackFunction : public ICloudRequestCallbackFunctionBase
{
    public :
    typedef void (ClassType::*callbackFunction)(const ParamType& param);
    ClassType*              m_pClass;
    callbackFunction        m_MemberFunction;
    
    ICloudRequestCallbackFunction( ClassType* pObject, callbackFunction pMemFunctor)
    {
        m_MemberFunction    = pMemFunctor;
        m_pClass            = pObject;
    }
    virtual void process(bool result) override
    {
        (m_pClass->*m_MemberFunction)(result);
    }
};

class ICloudRequestSTDCallbackFunction : public ICloudRequestCallbackFunctionBase
{
public:
    ICloudRequestSTDCallbackFunction(const std::function<void(bool)>& pStaticFunc)
    {
        m_staticFunc = pStaticFunc;
    }
    virtual void process(bool result) override
    {
        if(m_staticFunc)
        {
            m_staticFunc(result);
        }
    }
private:
    std::function<void(bool)> m_staticFunc;
};

class IRequestCall:public DRef
{
public:
    IRequestCall(INetworkData* data,const std::function<void(INetworkData*,bool)>& pStaticFunc)
    {
        m_data = data;
        m_staticFunc = pStaticFunc;
    }
    virtual void process(const NetWorkMsg& msg)
    {
        if(m_staticFunc && m_data)
        {
            if (msg.erro == 0)
            {
                m_data->SerializeJson(msg.msg);
                
                m_staticFunc(m_data,true);
            }
            else
            {
                m_staticFunc(m_data,false);
            }
        }
    }
protected:
    std::function<void(INetworkData*,bool)> m_staticFunc;
    DRefPtr<INetworkData> m_data;
};

class MsgResultInfo
{
public:
    int     m_errorID = 0;
    bool    m_bErrHandled = false;
};

enum ObjectType
{
    ObjectType_None,
    ObjectType_Plant,
    ObjectType_PlantChip,
    ObjectType_AvatarChip,
    ObjectType_Pendant,
    ObjectType_PendantChip,
};

enum RANKLIST_TYPE
{
	ENDLESS_RANK_LIST = 1,
	BATTLEZ_RANK_LIST = 2,
};

enum SHOP_TYPE
{
	CHRISTMAS_2018 = 1,
	PIGGY_BANK_2019 = 2,
    GROUPBUY_2019 = 3,
    GROUPBUY_VOUCHER_2019 = 4,
    RENAISSANCE_CHALLENGE = 5,
};

typedef std::vector<std::string> StringArray;
typedef StringArray::iterator StrIter;
typedef std::map < std::string  , PackMemberFunctionBase* >    HandleMap;

namespace Message
{
    void MsgError(int erroId);
    void MsgErrorRequest(int erroId, const std::string& i_reqID);
    
    void ServerMsgError(const std::string& i_reqID);

	void MsgBorrowFriendPlant(int32 i_userid);
    void FetchGameRank();

    void LoginiCloudServerFinish(bool i_success);
    void UploadFirstTimeFinish(bool i_success);
    void SyncPlayerInfoFinish(bool i_success);
    void SyncProfileSummaryFinish(bool i_success);
    void SyncProfileListFinish(bool i_success);
    void SyncProfileToServerFinish(bool i_success);
    void SyncProfileFromServerFinish(bool i_success);
    
    void ValidateChargeFinish(bool i_success);
    void UseGemFinish(bool i_success);
    void BuyItemFinish(class MsgResultInfo* io_result, const S2C_ICloud_GetConsumeGemInfo* pInfo, const S2C_PlayerInfo* pGemChanged);
    void SyncPlantFinish(bool i_success);
    void SyncAvatarFinish(bool i_success);
    void GetConfigVersionFinish(bool i_success);

    void DownloadMagentoFinish(bool i_success);
    
//    void ProcessLoginRewardResult(const S2C_LoginRewardList* i_loginRewardList);
    void ProcessSignRewardResult(const S2C_ICloud_DailySignInfo* i_signRewardList);
    
    void AddFreeGemFinish(bool i_success);

    void GetGachaInfo(S2C_GachaInfo* info);
    
    void ChangePlantSuccess(const std::string& i_plantName);
    void ChangeAvatarSuccess(const std::string& i_plantName);
    void PlantLevelUpSuccess();
    
    void BuyPlantGiftSuccess();
    void FinishedInitDangerRoom(bool i_success);
    void AcceptDangerRoomStart();
    void DangerRoomConfirmReward(bool i_success, int i_lastRank, bool i_setToFalse);
    void LeafsCost(bool i_success);
    void StartDangerRoomPlay(bool i_success);
    void DangerRoomLifeCost(bool i_success, bool i_noLife = false);
    void DangerRoomNewLifeCost(bool i_success);
    void DangerRoomScoreUpdated(bool i_success);
	void GetDangerRoomBonus(bool i_success);
    void GetDangerRoomSkippingBonus(bool i_success);
    
    void OpenPlantAdventure(bool i_success);
    void GotExploreTeamStatus(bool i_success);
    void GotExplorePlantStatus(int i_dungeonId, bool i_success);
    void StartExplore(bool i_success);
    void FreeExplore(int i_dungeonId, bool i_free);
    void StopExplore(int i_dungeonId, int i_newState, bool i_success);
    void GotExploreReward(bool i_success);
    void GotExploreSurprise(bool i_success);
    void NeedRecoverExplorePlant(int i_gemCost);
    void RecoverExplorePlant(bool i_success);
    
    void GotChristmasLottery(bool i_success,int32 i_chipid,int32 i_count);
    void GotChristmasProtect(bool i_success);
    void GotChristmasAccessoryStat(bool i_success);
    void RefreshChristmasAccessoryStat(bool i_success);
    void ChristmasAccessoryBought(bool i_success);
    void GotChristmasCheckRebate(S2C_ChristmasCheckRebate* pData);
    void GotChristmasRebate(S2C_ChristmasRebate* pData);
    
    void GotGoldenEggStat(bool i_success);
    void RefreshGoldenEggStat(bool i_success);
    void GoldenEggOpen(bool i_success);
    
	void RequestDangerRoomFinish(bool i_success, int i_rank);
    
    void RefreshLanternUIState();
    void CompeleteTodayLanternRiddles(const S2C_LanternRiddlesResult& result);
    void ProcessRedPackLeaderBoardInfo(const S2C_ICloud_RedPackLeaderBoard* i_info);
    
    void PendantGacha(bool i_success);
    void RedPackLeaderBoardReward(const S2C_ICloud_RedPackLeaderBoardReward* i_info);
    void Verify2015NewTearCharge(bool i_success);
    void Get2015NewTearChargeReward(bool i_success, bool i_neednext);
    void GotGemReturnState(bool i_success);
    void GotGemReturnReward(bool i_success);
	
	void ReceivedRankInfo(bool i_success);
    
    void BirthdayRewardGot();
    void PinataRewardGot();
    
    void GLLotteryResult(bool i_success);
    void StoneLotteryReward(const S2C_StoneLotteryReward& i_reward);
    void GLDeliverySend(bool i_success);
    
    void TGResultGot(bool i_success);

	void GL7DaysLoginReward(bool i_success, const S2C_7DaysLoginReward* pData);
    void GL7DaysLoginSpringReward(bool i_success, const S2C_7DaysLoginSpringReward* pData);
    void GLBuyPlantID(bool i_success, int plantID);
    void GLWorldCupBeginGame(bool i_success);
    void GLBuyWorldCupTicket(bool i_success);
    void GLUnlockWorldCupTeam(bool i_success);
    void GLBuyZMatchTicket(bool i_success);
	void CRChargeRewardPlantID(bool i_success);
    void ProcessDangerRoomLeaderBoardInfo(const S2C_ICloud_DangerRoomLeaderBoard* i_info, bool i_success);
    
    void SavePVPPlayerInfo(bool i_success, int i_errorCode);
    void GetPVPPlayerInfo(bool i_success, int i_errorCode);
    void PVPBattleEnding(bool i_success, int i_errorCode);
    void EditPlayerPlant(bool i_success, int i_errorCode);
    void BattleStart(bool i_success, int i_errorCode);
    void ApplyData(int i_errorCode);
    
    void NotifyBoardInfoList(const S2C_NoticeInfoList* pInfoList);
    void NotifyBoardInfoGetReward(const S2C_NoticeInfoGet* pData);
    
    //UUID Message
    void NotifyUUIDInit(bool i_success, const std::string& uuid, const std::string& access_token);
    void NotifyUUIDCheck(int result, const std::string& access_token);
    
    void NotifyUUIDBind(bool i_success);
    void NotifyUUIDLogin(bool i_success);
    
    // payment validation message
    void NotifyPurchaseInit(int i_errorCode, const std::string& i_orderId, const std::string& i_skuId);
    void NotifyPurchaseValidation(int i_errorCode, const std::string& i_skuId, int i_status);
    void NotifyLostPurchaseOrder(int i_errorCode, const S2C_Purchase_LostPurchaseOrder& i_order);

    // pvp message
    void PVPLogin(bool i_success);
    void PVPTrainingSellResult(bool i_success);
    void PVPTrainingZombieChanged(bool bPlayEffect);
    void PVPTrainingFinishGems(int i_gems);
    void PlaybackListRefresh(const std::vector<BattleID>& idList);
    void PlaybackDownloadResult(BattleID battle_id, bool i_success);
    void PVP_PingSuccess(bool timeout);
    void NotifyAchievementConfigChanged();
    void NotifyAchievementReward(int i_achid, int i_num);
    
    void NotifyPvpSubCoin(int i_leftCoin, int i_leftMetal);
    void PVPLabRefresh();
    void PVPCompensationReward(int i_resourceNum,int i_coinNum,int i_medalNum);
    void BeginPVPUpgradeSuccess();
    void GetPVPCompleteUpgradeGemSuccess(int gem);
    void GetPVPCompletePVPUpgrade(S2C_PVPCompleteUpgradeData* pData);
    
    // Sales
    void GotActActivityStates(bool i_success);
    void VerifiedSales(bool i_success);
    
    // LeveloftheDay
    void LevelofDayOpening(bool i_success);
    void LeveloftheDayReward(bool i_success);
    void GetChildrenDayReturn(const ChildrenDayStates* info);
    void RequestCharge(const std::string& sku, ParaMap* para);
    void ConfirmChildDayItem(const std::vector<ChildrenDayItem>& item);
    
    // compose plant
    void ComposePlant(bool i_success);
    
    void MonthlyCardBought(bool i_success);
    void MonthlyCardTrial();
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void NotifyRefreshActivityLevelEnd(int result, class S2C_VacationLevelEndData* pVacationData);
    void NotifySummeryLottery(int result, const S2C_SummeryLotteryData& data);
    void NotifySummeryLottery2018(int result, const S2C_SummeryLotteryData2018& data);
    void NotifyBossChallengeLevelEnd(int result, const S2C_BossChallengeLevelEndData* data);
	void NotifyMiniGameChallengeLevelEnd(int result, const S2C_MiniGameResult* data);
	void NotifyMiniGameRewardEnd(bool i_success);
    void NotifyBossChallengeReward(int result, const S2C_BossChallengteReward* data);
    void NotifySkipDangerRoom(int result, const S2C_DangerRoomSkipLevel* data, const S2C_PlayerInfo* pGemChanged);
    void NotifyDangerRoomEnd(int result, const S2C_DangerRoomEndLevel* data);
    void NotifyStaticConfig(int result, const S2C_StaticConfig* data);
    
    void FirstRechargePackageGot();
    void TotalRechargePackageGot(bool i_success, const S2C_ICloud_GetChargeRewardInfo* data);
    
    //ads
    void NotifyAdsReward(const S2C_ADSReward& reward);
    
    // New Gacha
    void NotifyNewGachaDrawResult(bool i_success);
    
    //daily sign with tw4399
    void NotifyDailySignWithTwResult(bool i_success, const S2C_DailySignWithTW* pData);
    
    void NotifyChallengeReward(const std::string& i_jsonStr);
    void NotifyCodeRewardResult(bool i_success, const S2C_CodeRewardResult* pData);

    //wechat reward for modern
    void NotifyWechatRewardResult(bool i_success, const S2C_WechatShareResult* pData);

    //limit lottery
    void NotifyLimitLotteryReward(bool i_success, const S2C_LimitLotteryReward* pData);
    void NotifyLimitLotteryBuyCrystalFinish(bool i_success, const S2C_LimitLotteryCrystalBuy* pData);
    void NotifyLimitLotteryBuyCupShopFinish(bool i_success, const S2C_S2C_LimitLotteryCupShop* pData);

    //unlock New Avatar
    void NotifyUnlockNewAvatar(bool i_success, int i_newAvatarId);

    //billing reward
    void NotifyBillingReward(bool i_success, const S2C_BillingReward* pData);
    void NotifyLevelupBook(bool i_success);

    //equip collection
    void NotifyEquipCollection(int i_collectionId, int i_state);

    // platform gift
    void NotifyPlatformGiftList(bool success, const S2C_PlatformGiftData* pData);

    void NotifyBattleZRankListEffect(const std::vector<int>& playerIdList);

    void NotifyShopBuyFinish(bool success, int shop);
    void NotifyShopBuyFinishDetails(bool success, const S2C_ShopItemPurchaseInfo* pData);

    void NotifySecretAreaRewardDetails(bool success,const New_S2C_BuySecretAreaReward* pData);

    void NotifySpringOutingConsumeAndReceive(bool i_success, const S2C_PiggyBankReward* pData);
    //
}

class INetworkMsgProcess
{
public:
	INetworkMsgProcess();
	virtual ~INetworkMsgProcess(void);
	virtual void  Initialize() = 0;
    void RegisterCommonMessages();

    static HandleMap G_msgFunMap;

    const PacketID& getPacketID() const {return m_pktID;}
    void  _processMsg(const std::string& msgId,const NetWorkMsg& data);
    bool  requestMsg(const std::string& msgId,ParaMap& params,const std::function<void(const std::string&)>& response,bool wait = true,
    		bool requestPid=true, const std::string& i_hint = "[NET_CONNECTING]");
    void  removeRequestMsg(const std::string& msgId);
    
	virtual void ProcessMsg(unsigned char * buff,unsigned int bufLen);

    virtual AString GetPlayUserId() { return m_UserId; }
    virtual bool  IsLogined(){ return m_UserId.size()>0;}
	
	// PVZ2_START_shicheng
	enum ICloudState
	{
		INIT,
		Send_Request,
		Response_Error,
		Response_Success,
	};
	virtual ICloudState GetICloudState()  const	{ return m_ICIoudState; }
	virtual void  SetICloudState(const ICloudState& state)  { m_ICIoudState = state; }
    // PVZ2_END
	
	bool  isNewAccount() {return m_isNewAccount;}
    void  setNewAccountFlag(bool flag) {m_isNewAccount = flag;}
    bool  needPurge(){return m_needPurge != 0;}
    bool  needWaitPurgeResponse(){ return m_waitingPurgeResponse;}
    bool  needWaitPVPResponse(){ return m_waitingPVPResponse;}

    void  UpdatePlayerSupportPlant();

    void setUserID(AString id){ m_UserId = id; }
    AString getUserID(){ return m_UserId; }
    AString getSessionKey(){ return m_sk; }
    bool isSessionKeyValid();

    NetworkCacheQueue * GetNetworkCacheQueue();
    void LoadCache();
	void SaveCache();
    void flushCache();
    
    ParaMap GenCommonParaMap(const std::string& strId);

    //  ------------------- http request ------------------------------
    virtual void SendHttpRequest(ParaMap& params,bool bWait=false, const std::string& i_hint = "[NET_CONNECTING]", bool bPause = false, bool bFlush = false);
    virtual void SendHttpRequest(std::string & req,const std::string& msg,bool bWait=false,bool bPause = false, bool bFlush = false);
    void SendHttpRequestNoErro(ParaMap& params);


    // ----------------icloud request----------------------
    virtual bool ICloudRequstLogin(const std::string& defineId){return true;}
    virtual bool ICloudRequestUploadProfile(const std::string& profile,const std::string& md5,const std::string& sumary, bool wait){return true;}
    virtual bool ICloudRequestProfileList(){return true;}

    virtual bool ICloudRequestChargeReward(int i_type, int i_index, int i_select_index){return true;}
    virtual bool ICloudRequestSingleProfile(int profileId){return true;}
    virtual bool ICloudRequestSinglePlayerInfo();
    virtual bool ICloudRequestUploadFirstTime(const std::string& profile,const std::string& md5,const std::string& sumary, bool wait,PlayerInfo* uploadProfile){return true;}
    virtual bool ICloudRequestDoGacha(int actid, const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback) { return true; }

    // ----------------iflush request ----------------------
    virtual bool IFlushCacheRequestUpdateDatePlantFragments() {return true;}
    //virtual bool IFlushCacheRequestUpdateDatePlants() {return true;};
    virtual bool IFlushCacheRequestUpdateDateDressFragments() {return true;}
    virtual bool IFlushCacheRequestUpdateDatePendantInfo() {return true;}
    virtual bool IFlushCacheRequestUpdateAddFreeGem() {return true;}
    virtual bool IRequestFlushCacheObjects() {return true;}

    // ----------------endless request ---------------------
	virtual bool ICloudRequestGetEndlessRankAndLife(int i_offset) {return true;}
    virtual bool ICloudRequestGetEndlessRankAndLife() {return true;}
    virtual bool ICloudRequestEndlessConsumeLife() {return true;}
    virtual bool ICloudRequestEndlessUpdateScore(int i_score, int i_weight, int i_stage, int i_wave, int i_result, int i_levelTime, int i_levelScore) {return true;}
    
    virtual bool ICloudRequestConsumeLeafs(int i_skuid) {return true;}

    // ------------- 2015 New Year Charge Reward -------------
	virtual bool ICloudRequest2015NewTearChargeStat();
    virtual bool ICloudRequestGet2015NewTearChargeReward(int i_objectId) {return true;}

    // -------------------- Pendant Gacha --------------------
    virtual bool ICloudRequestPendantGacha(int i_actid) {return true;}
    virtual bool ICloudRequestGoldcanGacha(int i_actid) {return true;}
    
    // ----------------- Explore -------------------------------
    virtual bool ICloudRequestGetExploreTeamStatus();
    virtual bool ICloudRequestGetExplorePlantStatus(int i_dungeonId);
    virtual bool ICloudRequestStartExplore(const std::vector<int>& i_plantList, int i_dungeonId, int i_isCost);
    virtual bool ICloudRequestStopExplore(int i_dungeonId, int i_flag);
    virtual bool ICloudRequestCalcExploreReward(int i_dungeonId, bool i_ad);
    virtual bool ICloudRequestOpenExploreSurpriseBox(int i_dungeonId);
    virtual bool ICloudRequestRecoverExplorePlant(int i_plantId, int i_flag);

    virtual bool ICloudRequestComposePlant(int i_objectId, int i_quantity, int i_level);
    virtual void OnICloudRequestComposePlant(const NetWorkMsg& data);
    
    // ----------------- Consumption -------------------------------
    virtual bool ICloudRequestGetConsumptionReward();

	//----------------- StoneLottery------------------------------ -
	virtual bool ICloudRequestGetStoneLottery();

	//----------------- 7DaysLoginReward ------------------------------ -
	virtual bool ICloudRequestGet7DaysLoginReward();

	//----------------- ChristmasLoginReward ------------------------------ -
//	virtual bool ICloudRequestGetChristmasLoginReward(ActivityTypeID activityID);
	virtual bool ICloudRequestGetChristmasLoginReward(int activityID);

    //----------------- firstChargeSucceed ------------------------------ -
	virtual bool ICloudRequestfirstChargeSucceed(int price);

    //----------------- SpringLoginReward ------------------------------ -
//	virtual bool ICloudRequestGetSpringLoginReward(ActivityTypeID activityID, const std::vector<int>& fullChipPlants, int i_index);
	virtual bool ICloudRequestGetSpringLoginReward(int activityID, const std::vector<int>& fullChipPlants, int i_index);

    // ----------------- SpringBuyPlant ------------------
//	virtual bool ICloudRequestGetSpringBuyPlant(ActivityTypeID activityID, int nPlantID, int num);
	virtual bool ICloudRequestGetSpringBuyPlant(int activityID, int nPlantID, int num);

    // ----------------- worldCupbeginGame ------------------
	virtual bool ICloudRequestGetWorldCupBeginGame(int teamID);

    // ----------------- buyWorldCupTicket ------------------
	virtual bool ICloudRequestGetbuyWorldCupTicket(int useGemNum);

    // ----------------- ZMatchShopData ------------------
    virtual bool ICloudRequestGetZMatchShopData(bool isRefresh, int consume = 0, bool i_ad = false);

    // -------------------- LimitLottery ---------------------
    virtual bool ICloudRequestGetLimitLottery(int times);
    virtual bool ICloudRequestBuyLimitLotteryCrystal(int num);
    virtual bool ICloudRequestBuyLimitLotteryCupShop(int id, int num);

    virtual bool ICloudRequestUnlockNewAvatar(int i_newAvatarId);

    virtual bool ICloudRequestBillingPoint(std::string des, int actionId, int socre);
    virtual bool ICloudRequestLevelUpByPlantBook(int plantId);

    virtual bool ICloudRequestAuthReward();

    virtual bool ICloudRequestTravelLogIntegralChest(int i_select);
    virtual bool ICloudRequestTravelLogWorldChest(int i_param1, int i_param2);
    virtual bool ICloudRequestNoviceSevenDaysTrigger();

    //ArborDay
    virtual bool ICloudRequestArborDayWater(int i_times);

    //Carnival
    virtual bool ICloudRequestCarnivalBundle(int i_type, int i_bundleID);

    //encourage link modbile number
    virtual bool ICloudRequestEncourageLinkMobile(const std::string& i_number, const std::string& i_code);

    // -------------------- Artifact ---------------------
    virtual bool ICloudRequestArtifactLevelUp(int i_artifactId);
    virtual bool ICloudRequestArtifactRankUp(int i_artifactId);
    virtual bool ICloudRequestToggleArtifactEquip(int i_artifactId, int i_state);

    //collection
    virtual bool ICloudRequestToggleCollectionEquip(int i_collectionId, int i_state);

    // --------------------- Platform Gift -------------------
    virtual bool ICloudRequestPlatformGift(int platformID);

    // ----------------- ConsumeAndReceive -------------------
    virtual bool ICloudRequestConsumeAndReceive(int i_index);

    virtual bool ICloudRequestWeeklyRechargeReward(int level);

    //----------------- BuyZMatchBuyItem ------------------
    virtual bool ICloudRequestBuyItem(int objectId, int quantity);

    // ----------------- BuyZMatchTicket ------------------
	virtual bool ICloudRequestBuyZMatchTicket(int type, int ticketNum, int gemNum);

    // ----------------- unlockWorldCupTeam ------------------
	virtual bool ICloudRequestGetUnlockWorldCupTeam(int teamID, int gem);

    // ----------------- clearworldCupdata ------------------
	virtual bool ICloudRequestClearworldCupdata();

	//----------------- ChristmasLoginReward ------------------------------ -
//	virtual bool ICloudRequestChargeRewardID(ActivityTypeID activityID, int plantID);
	virtual bool ICloudRequestChargeRewardID(int activityID, int plantID);

	//----------------- ChristmasChargeReward -------------------------------
//	virtual bool ICloudRequestGetChristmasChargeReward(ActivityTypeID activityID, std::vector<S2C_WechatReward>& vecAward, int index, int amount);
	virtual bool ICloudRequestGetChristmasChargeReward(int activityID, std::vector<S2C_WechatReward>& vecAward, int index, int amount);

	//----------------- rechargeReward ------------------------------ -
	virtual bool ICloudRequestGetRechargeReward(int amount);

    // ----------------- delivery -------------------------------
    virtual bool ICloudRequestPlayerDeliveryInfo(std::string i_email, std::string i_tel, std::string i_addr, int i_age, int i_sex);
    
    // ----------------- TransGenosis ------------------
    virtual bool ICloudRequestTGResult(int i_type, std::vector<int> i_list, bool i_ad = false);

    virtual bool ICloudRequestTGAvatarResult(int i_type, std::vector<int> i_list, bool i_ad = false);

    // ----------------- Christmas -------------------------------
    virtual bool ICloudRequestChristmasLottery() {return true;}
    virtual bool ICloudRequestChristmasProtect(int i_reward) {return true;}
    virtual bool ICloudRequestGetAccessoryStat(int i_option) {return true;}
    virtual bool ICloudRequestAccessoryStatBuy(int i_type) {return true;}
    virtual bool ICloudRequestGetGoldenEggStat(int i_option) {return true;}
    virtual bool ICloudRequestGoldenEggOpen(int i_index, int i_chipId) {return true;}
    virtual bool ICloudRequestCheckRebate() {return true;}
    virtual bool ICloudRequestRebate(int iObjectId) {return true;}
//    virtual bool ICloudRequestInstanceStatus(int i_instanceId, int i_queryStatus, const std::map<std::string, int> &objectList, ObjectType i_type) { return true; }
    
    virtual bool ICloudRequestProfileMd5() {return true;}

    virtual void RequestGetRedPackLeaderBoard() {}
    virtual void RequestUpdateLevelScore(int lvlId, int lvlStar, unsigned long time,const std::string& formationData) {}
    virtual bool ICloudRequestGetProfile() {return true; }
    virtual bool ICloudRequestUpLoadProfile(const std::string& profile,const std::string& md5,const std::string& sumary, bool wait) {return true;}
    virtual void RequestTimeLevelList(int iID = -1) {}
    virtual void RequestStartTimeLevelCD(int iID) {}
    virtual void UploadDangerRoomRank(int score, int weight, int currentLevel, int currentWave, int result, int levelTime, int currentScore) {}
    virtual void RequestDangerRoomRank(int i_preRank) {}
    virtual void RequestSendTLog(const std::string& jsonText) {}
    virtual void HeartBeat() {}
    virtual void HttpReqFriends() {}
    virtual void RequestFrindGiftList() {}
    virtual void SendGift(int giftType,int receverId) {}

    // New functions
    virtual void RequestRanks() {}
    
    virtual void RequestDoNewGacha(int i_type, int i_num, int i_free, int nLotteryType, bool i_ad = false);
    
    virtual void RequestDailySignWithTw(const std::string& code);
    virtual void RequestCodeReward(const std::string& packageName, const std::string& code);

    virtual void RequestWechatReward();

    virtual void RequestDailySignRewardList(int i_typeId);

    virtual void RequestRankListEffect(RANKLIST_TYPE rankListType);

    virtual void RequestBuyShopItem(int i_shop, int i_item, int amount, int i_currency, int cost);

    virtual void RequestPiggyBankGems(int day);

    void RequestDisplayID(const std::string& defineId, const std::string& uuid);

protected:
    virtual void ShowLogoScreen();
    
public:
    
    // -------------------- ThirdPartPlatform Bind --------------------
    void ICloudRequestGetStateThirdPartPlatforms();
    //void ICloudRequestLoginThirdPartPlatforms(const std::string& token, int platform_id);
    void ICloudRequestBindingThirdPartPlatforms(const std::string& token, const std::string& appid, int platform_id);
    void ICloudRequestUnboundThirdPartPlatforms(const std::string& token, const std::string& appid, int platform_id);
    void ICloudRequestTransferThirdPartPlatforms(const std::string& token, const std::string& appid, int platform_id);
    void ICloudRequestClearNotifyThirdPartPlatforms();

    bool RequestDoGacha(int actid, const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback);
    
    bool RequestUserInfo(const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback);
    
    bool RequestUserName(const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback);
    
    bool RequestUserHeadshot(const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback);
    
    bool RequestDoSecretGacha(int i_type, const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback);

    // zhousen rift shop protocal
    virtual bool ICloudRequestGetRiftShopData(bool isRefresh, int consume = 0, bool i_ad = false);
    void OnICloudRequestGetRiftShopData(const NetWorkMsg& data);

    virtual bool ICloudRequestGetPVZ1ModeShopData(bool isRefresh, int consume = 0);
    void OnICloudRequestGetPVZ1ModeShopData(const NetWorkMsg& data);

    virtual bool ICloudRequestGetNewPVPShopData(bool isRefresh, int consume = 0);
    void OnICloudRequestGetNewPVPShopData(const NetWorkMsg& data);

    void RequestSecretAreaReward(const std::string& world, int index);

protected:

    void OnRequestDailySignWithTW(const NetWorkMsg& data);
    void onRequestGacha(const NetWorkMsg& data);
    void onRequestDoSecretGacha(const NetWorkMsg& data);
    void onRequestUserInfo(const NetWorkMsg& data);
    void onRequestUserHeadshot(const NetWorkMsg& data);
    void onRequestUserName(const NetWorkMsg& data);
    
    void onRequestNewGacha(const NetWorkMsg& data);
    
    void OnRequestCodeReward(const NetWorkMsg& data);
    
    void OnRequestWechatReward(const NetWorkMsg& data);

    virtual void OnICloudRequestSinglePlayerInfo(const NetWorkMsg& data);
    // -------------------- ThirdPartPlatform Bind --------------------
    void OnICloudRequestGetStateThirdPartPlatforms(const NetWorkMsg &data);
    //void OnICloudRequestLoginThirdPartPlatforms(const NetWorkMsg& data);
    void OnICloudRequestBindingThirdPartPlatforms(const NetWorkMsg& data);
    void OnICloudRequestUnboundThirdPartPlatforms(const NetWorkMsg& data);
    void OnICloudRequestTransferThirdPartPlatforms(const NetWorkMsg& data);
    void OnICloudRequestClearNotifyThirdPartPlatforms(const NetWorkMsg& data);
    
    void OnRequestDisplayID(const NetWorkMsg& data);

public:
    // -------------------- PVE request both for android & ios --------------------
    void RequestBoardInfoList();
    void RequestBoardInfoGet(int i_id, int i_type);
    bool ICloudRequestInstanceStatus(int i_instanceId, int i_queryStatus, const std::map<std::string, int> &objectList, ObjectType i_type, bool i_ad = false);
	bool RequestActivityList(const std::vector<std::pair<int, int>>& i_idList, int i_client_status, bool i_wait = false);
	bool RequestActivityListWithWorldName(const std::vector<std::pair<int, int>>& i_idList, std::string worldName, int i_client_status, bool i_wait = false);
    bool RequestActivityLevelEnd(int bossType, int levelIndex);
    bool RequestSummeryLottery(int material, int times = 1);
	bool RequestSummerPlantComposit(int i_num);
    bool RequestBossChallengeLevelEnd(std::vector<class BossKillTimeChallengeInfo>& info);
    bool RequestBossChallengeReward();
    
    bool ICloudRequestGetServiceStatus();
    bool ICloudRequestUseGem(int actid, int count,const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback, int sceneId, bool wait);
    bool RequestRankList(int i_type, int i_offset);
    bool RequestDangerRoomStartData(int i_level);
    bool RequestSkipDangerRoom(int destLevel, int type = 0);// type is for skip mode.
    bool RequestStaticConfig();
    bool RequestDangerRoomEndLevel(bool i_win, int i_wave, S2C_DangerRoomConsumeData& consume, bool isCheating);
    bool RequestChallengeReward(const std::string& i_msgID);
    bool RequestDinosaurDanger(int op);
    
    bool RequestFamilyUnlockProperty(int familyID);
    bool RequestFamilyRefreshProperty(int familyID, int familyLevel, int isFree, std::string lockMD5, bool i_ad = false);
    bool RequestFamilyReplaceProperty(int familyID);
    bool RequestFamilyGetInfo();
protected:
    // -------------------- PVE receive both for android & ios --------------------
    void onRequestBoardInfoList(const NetWorkMsg& data);
    void onRequestBoardInfoGet(const NetWorkMsg& data);
    void OnICloudRequestInstanceStatus(const NetWorkMsg& data);
    void onRequestActivityList(const NetWorkMsg& data);
    void onRequestActivityLevelEnd(const NetWorkMsg &data);
    void onRequestSummeryLottery(const NetWorkMsg &data);
    void onRequestSummerPlantComposit(const NetWorkMsg& data);
    void onRequestBossChallengeLevelEnd(const NetWorkMsg& data);
    void onRequestBossChallengeReward(const NetWorkMsg& data);
    void OnICloudRequestGetServiceStatus(const NetWorkMsg& data);
    void OnICloudRequestUseGem(const NetWorkMsg& data);
    void OnRequestRankList(const NetWorkMsg& data);
    void OnRequestDangerRoomStartData(const NetWorkMsg& data);
    void OnRequestSkipDangerRoom(const NetWorkMsg& data);
    void OnRequestStaticConfig(const NetWorkMsg& data);
    void OnRequestDangerRoomBoostEnd(const NetWorkMsg& data);
    void OnRequestDangerRoomEndLevel(const NetWorkMsg& data);
    void OnRequestChallengeReward(const NetWorkMsg& data);
    void OnRequestDinosaurDanger(const NetWorkMsg& data);
	void OnRequestMiniGameChallengeLevelEnd(const NetWorkMsg& data);
	void OnRequestMiniGameRewardEnd(const NetWorkMsg& data);
	void OnRequestLanternRiddlesCompelete(const NetWorkMsg& data);
	void OnRequestYuanBaoReward(const NetWorkMsg& data);
	void OnRequestDailySignRewardList(const NetWorkMsg& data);
	void OnRequestBuyShopItem(const NetWorkMsg& data);
	void OnRequestPiggyBankGems(const NetWorkMsg& data);
	void OnRequestSecretAreaReward(const NetWorkMsg& data);
public:
    // -------------------- ADS request --------------------
    virtual bool RequestADSReward() {return false;}
    
protected:
    // -------------------- ADS receive --------------------
    virtual void onRequestADSReward(const NetWorkMsg& data) {}
    
public:
    // -------------------- UUID request --------------------
    virtual void RequestUUIDBind()  {}
    virtual void RequestUUIDLogin() {}
    
    virtual void RequestUUIDInit()  {}
    virtual void RequestUUIDCheck() {}

public:
    // -------------------- payment validation --------------------
    virtual void InitPurchaseOrder(const std::string& i_sku) {}

public:
    enum ApplyDataErrorType
    {
        MD5_CHECK_FAIL = 1,
        COMPRESS_FAIL = 2,
        DECOMPRESS_FAIL = 3
    };
    static const int ErrorCodeCompress     = 20001;
    static const int ErrorCodeDecompress   = 20002;
    
    // -------------------- error message --------------------
    static bool ShowPVPErrorMessage(INetworkErrorData errorData);
    static void ShowPvpDialog(const SexyString& title, const SexyString& detail);
    static bool ShowErrorMessage(INetworkErrorData errorData);
    
    //------------------------------------------------------
    // -------------------- PVP request --------------------
    //------------------------------------------------------
    bool RequestPVPCompensationNoticeInfos(int type);// type = 1.请求补偿奖励, 2.领取补偿奖励
    bool RequestPVPLogin();
    bool RequestPVPTrainingInfos();
    bool RequestPVPTrainingSell(std::vector<C2S_PVP_ZombieNum>& sellList);
    bool RequestPVPTrainingZombie(const std::string& i_name, int num);
    bool RequestPVPTrainingFinishAtOnce();
    bool RequestPVPTrainingFinishGems();
    bool RequestPVPEntry();
    bool RequestPVPMapInfo();
    bool RequestPVPAchieve(int64 occupyId);
    bool RequestPVPUnlock(int zoneId);
    bool RequestPVPChangeEnemy(int64 occupyId, int type);
	bool RequestPVPPlantInfos(const std::string& i_info, int i_occupyId, int i_type);
    bool RequestGetPVPPlantInfos(int i_occupyId, int i_type, int i_defender, BattleID i_revengeID);
    bool RequestPVPBattleEnding(const std::string& logArenaID, int i_cid, int i_result, int i_occupyId, int i_type, const std::string& i_info, BattleID i_revengeID);
    bool RequestEditPlant(int i_cid, int i_occupyId, int i_type);
    bool RequestChangePlayer(int i_cid);
    bool RequestPVPRank(int i_type, int startIdx, int count);
    bool RequestOthersZbList(int64 profileId);
    
    bool RequestPlaybackList();
    bool RequestPlaybackDownload(int i_type, BattleID battle_id);
    bool RequestPlaybackUpload(ParaMap& params);
    bool SendPVP_Ping(int i_cid, int i_occupyId, int i_type, int state);
    bool RequestBuyPvpCoin(int item);
    bool RequestBeginPVPUpgrade(int id1, int id2);
    bool RequestCompletePVPUpgrade();
    bool RequestPvPUpgradeCompleteGem();
    bool RequestPVPUpgradeCancel(int i_labID, int i_objID);
    bool RequestAchievementConfig();
    bool RequestAchievementReward(int i_id, int i_num ,int i_dropCount);
    
    bool RequestSubPvpCoin(int type, int count);
    bool RequestPVPLabEnter();
    
    // ----------------- PVP request to IOS Server -------------------------------
    bool RequestPvpShop(bool isRefresh);
    bool RequestBuyPvpShopObject(int64 objId);
    
    // ----------------- Sales -----------------------------------
    bool VerifySalesReward(int i_objectId, int i_quantity, int i_unlock);
    bool RequestActiveActivityStates(int i_typeId);
    
    // ----------------- LevelOfTheDay -------------------------------
    virtual bool ICloudRequestGetPinataReward() {return true;}
    bool ICloudRequestLeveloftheDayReward(int activityID);
    
    bool RequestGeneral(std::string& strMsgType, const std::string& rStrJson, bool i_wait = true, bool i_addQuote = true);
    bool RequestLuaGeneral(int nType, const std::string& rStrJson, bool i_wait = true);

	virtual void RequestUpdateChargeInfo(const std::string& productId, bool isRestore, int objectId) {}

	virtual void RequestLostPurchaseOrder() {}

	// ----------------- MiniGameActivity -------------------------------
	bool RequestMiniGameChallengeLevelEnd(bool isPass, int score, int passTime, int  passStage);
	bool RequestMiniGameRewardEnd(std::string& strPeriod, int miniCoinNum);

	// ----------------- Lantern Riddles --------------------------------
	bool RequestLanternRiddlesCompelete(int correctNum);

	// ----------------- YuanBao ----------------------------------------
	bool RequestYuanBaoReward(int yuanBaoNum);

	// ----------------- Soccer -----------------------------------------
	bool RequestSoccerEndReward(int levelIndex, int fight_result, int teamID);

	// ----------------- Lottery 2018 -----------------------------------
	bool RequestSummeryLottery2018(int actionId, int times);

protected:
    //------------------------------------------------------
    // -------------------- PVP receive --------------------
    //------------------------------------------------------
    void onRequestPVPCompensationNoticeInfos(const NetWorkMsg& data);
    void onRequestPVPLogin(const NetWorkMsg& data);
    void onRequestPVPTrainingInfos(const NetWorkMsg& data);
    
    void onRequestPVPPlantInfos(const NetWorkMsg& data);
    void onRequestGetPVPPlantInfos(const NetWorkMsg& data);
    void onRequestPVPBattleEnding(const NetWorkMsg& data);
    void onRequestEditPlant(const NetWorkMsg& data);
    void onRequestChangePlayer(const NetWorkMsg& data);
    
    void onRequestPVPTrainingSell(const NetWorkMsg& data);
    void onRequestPVPTrainingZombie(const NetWorkMsg& data);
    void onRequestPVPTrainingFinishAtOnce(const NetWorkMsg& data);
    void onRequestPVPTrainingFinishGems(const NetWorkMsg& data);
    void onRequestPVPEntry(const NetWorkMsg& data);
    void onRequestPVPMapInfo(const NetWorkMsg& data);
    void onRequestPVPAchieve(const NetWorkMsg& data);
    void onRequestPVPUnlock(const NetWorkMsg& data);
    void onRequestPVPChangeEnemy(const NetWorkMsg& data);
    void onRequestPVPRank(const NetWorkMsg& data);
    void onRequestOtherZbList(const NetWorkMsg& data);
    
    void onRequestPlaybackList(const NetWorkMsg& data);
    void onRequestPlaybackDownload(const NetWorkMsg& data);
    void onRequestPlaybackUpload(const NetWorkMsg& data);

    void onSendPVP_Ping(const NetWorkMsg& data);
    void onRequestBuyPvpCoin(const NetWorkMsg& data);
    void onRequestBeginPVPUpgrade(const NetWorkMsg& data);
    void onRequestCompletePVPUpgrade(const NetWorkMsg& data);
    void onRequestPvPUpgradeCompleteGem(const NetWorkMsg& data);
    void onRequestPVPUpgradeCancel(const NetWorkMsg& data);
    void onRequestAchievementConfig(const NetWorkMsg& data);
    void onRequestAchievementReward(const NetWorkMsg& data);
    
    void onRequestPvpShop(const NetWorkMsg& data);
    void onRequestBuyPvpShopObject(const NetWorkMsg& data);
    
    void onRequestSubPvpCoin(const NetWorkMsg& data);
    void onRequestPVPLabEnter(const NetWorkMsg& data);
    
    // ----------------- Sales -----------------------------------
    void OnVerifySalesReward(const NetWorkMsg& data);
    void OnRequestActiveActivityStates(const NetWorkMsg& data);
    
    // ----------------- LevelOfTheDay -------------------------------
    virtual void OnICloudRequestGetPinataReward(const NetWorkMsg& data) {};
    void OnRequestLeveloftheDayReward(const NetWorkMsg& data);
    
    // ----------------- Consumption Reward ------------------
    void OnICloudRequestGetConsumptionReward(const NetWorkMsg& data);
    
	// ----------------- stone lottery ------------------
	void OnICloudRequestGetStoneLottery(const NetWorkMsg& data);

	// ----------------- 7DaysLoginReward ------------------
	void OnICloudRequestGet7DaysLoginReward(const NetWorkMsg& data);

	// ----------------- ChristmasLoginReward ------------------
	void OnICloudRequestGetChristmasLoginReward(const NetWorkMsg& data);

    // ----------------- firstChargeSucceed ------------------
	void OnICloudRequestfirstChargeSucceed(const NetWorkMsg& data);

    // ----------------- SpringLoginReward ------------------
	void OnICloudRequestGetSpringLoginReward(const NetWorkMsg& data);

    // ----------------- SpringBuyPlant ------------------
	void OnICloudRequestGetSpringBuyPlant(const NetWorkMsg& data);

    // ----------------- worldCupbeginGame ------------------
	void OnICloudRequestGetWorldCupBeginGame(const NetWorkMsg& data);
    
    // ----------------- ZMatchShopData ------------------
    void OnICloudRequestGetZMatchShopData(const NetWorkMsg& data);

    // ----------------- LimitLottery -------------------
    void OnICloudRequestGetLimitLottery(const NetWorkMsg& data);
    void OnICloudRequestBuyLimitLotteryCrystal(const NetWorkMsg& data);
    void OnICloudRequestBuyLimitLotteryCupShop(const NetWorkMsg& data);

    void OnICloudRequestUnlockNewAvatar(const NetWorkMsg& data);

    void OnICloudRequestBillingPoint(const NetWorkMsg& data);
    void OnICloudRequestLevelUpByPlantBook(const NetWorkMsg& data);

    void OnICloudRequestAuthReward(const NetWorkMsg& data);

    void OnICloudRequestTravelLogIntegralChest(const NetWorkMsg& data);
    void OnICloudRequestTravelLogWorldChest(const NetWorkMsg& data);
    void OnICloudRequestNoviceSevenDaysTrigger(const NetWorkMsg& data);

    void OnICloudRequestArborDayWater(const NetWorkMsg& data);
    void OnICloudRequestEncourageLinkMobile(const NetWorkMsg& data);

    void OnICloudRequestCarnivalBundle(const NetWorkMsg& data);

    // -------------------- Artifact ---------------------
    void OnICloudRequestArtifactLevelUp(const NetWorkMsg& data);
    void OnICloudRequestArtifactRankUp(const NetWorkMsg& data);
    void OnICloudRequestArtifactEquip(const NetWorkMsg& data);

    // -------------------- Artifact ---------------------
    void OnICloudRequestCollectionEquip(const NetWorkMsg& data);

    // ------------------ Platform Gift -------------------
    void OnICloudRequestPlatformGift(const NetWorkMsg& data);

    // ----------------- ConsumeAndReceive -------------------
    void OnICloudRequestConsumeAndReceive(const NetWorkMsg& data);

    void OnICloudRequestWeeklyRechargeReward(const NetWorkMsg& data);

    //----------------- BuyZMatchBuyItem ------------------
    void OnICloudRequestBuyItem(const NetWorkMsg& data);

    // ----------------- BuyZMatchTicket ------------------
	void OnICloudRequestBuyZMatchTicket(const NetWorkMsg& data);

    //----------------- WorldCupTicket ------------------
    void OnICloudRequestGetbuyWorldCupTicket(const NetWorkMsg& data);

    // ----------------- unlockWorldCupTeam ------------------
	void OnICloudRequestGetUnlockWorldCupTeam(const NetWorkMsg& data);

    // ----------------- clearworldcupdata ------------------
	void OnICloudRequestClearworldcupdata(const NetWorkMsg& data);

	//----------------- ChargeReward ------------------
	void OnICloudRequestChargeRewardID(const NetWorkMsg& data);

	// ----------------- ChristmasChargeReward ------------------
	void OnICloudRequestGetChristmasChargeReward(const NetWorkMsg& data);

	// ----------------- rechageReward ------------------
	void OnICloudRequestGetRechageReward(const NetWorkMsg& data);

    // ----------------- TransGenosis ------------------
    void OnICloudRequestTGResult(const NetWorkMsg& data);

    void OnICloudRequestTGAvatarResult(const NetWorkMsg& data);
    
    void OnRequestLuaGeneral(const NetWorkMsg& data);
	//void OnRequestUpdateChargeInfo(const NetWorkMsg& data);
    
    void OnRequestSoccerEndReward(const NetWorkMsg& data);

    void OnRequestRankListEffect(const NetWorkMsg& data);

    void onRequestSummeryLottery2018(const NetWorkMsg &data);

protected:
    std::string getOwnPlantList();
    
    std::string getCacheDressFragmentList();
    std::string getCachePlantFragmentList();
    std::string getCachePendantFragmentList();
    std::string getCachePendantList();
    
    std::string getOwnFragmentList(const std::string& plantName, int addCount);
    std::string getOwnFragmentList(const std::map<std::string, int> &plantChipList);
    std::string getAvatarChipList(const std::string& avatarName, int addCount);
    std::string getAvatarChipList(const std::map<std::string, int> &avatarChipList);
    std::string getPendantChipList(const std::string& pendantName, int addCount);
    std::string getPendantChipList(const std::map<std::string, int> &pendantChipList);
    std::string getPendantList(const std::string& pendantName, int level);
    std::string getPendantList(const std::map<std::string, int> &pendantList);
    
    std::string getDangerRoomUnobtainedBonus();
    std::string getAvatarList();
    std::string getConstraintIdList();
    
    std::string getDailyRewardList(const std::vector<int>& i_bonusList);
    
protected:
	// PVZ2_START  shicheng
	ICloudState m_ICIoudState;
	// PVZ2_END

    virtual std::string GetDefineId() = 0;

    std::string GetClientSignature(const std::string& i_definedId);
    std::string GetServerSignature();

    virtual long   GetRandom();
    virtual void  InitAfterLogin() {};
    int   GetMsgID(const std::string & strMsgID);
    void  OnError(int erroId, const std::string & reqID);
	void  ProcessMsg(int id);
    bool  IsJsonObj(const std::string& strText);
    ParaMap StructuredData2ParaMap(const Sexy::StructuredData::Value* root, bool i_addQuote = true);

	AString         m_UserId;
    AString         m_sk;
    int32           m_isNewAccount;
    bool            m_waitingPurgeResponse;
    int32           m_needPurge;
    Sexy::Buffer    m_MsgBuff;
    bool            m_waitingPVPResponse;
    
    int             m_nCloudLoginCount;
    
    Sexy::StructuredData    i_networkData;
    HttpRequest*            m_pHttpRequest;
    PacketID                m_pktID;
    NetWorkMsg              m_NetworkMsg;
    long                    m_random;
    
    
    std::unordered_map<std::string,std::function<void(const std::string&)>> m_msgMgr;
    
    DRefPtr<ICloudRequestCallbackFunctionBase> m_useGemCallback;
    DRefPtr<ICloudRequestCallbackFunctionBase> m_requestUserInfoCallback;
    DRefPtr<ICloudRequestCallbackFunctionBase> m_requestUserHeadshotCallback;
    DRefPtr<ICloudRequestCallbackFunctionBase> m_requestUserNameCallback;
private:
    
    void ShowMainMenu();
    S2C_PlayerInfo SubtractGems(const S2C_PlayerInfo& src);

// for android convert ios
public:
    virtual bool ICloudRequestSynchronizePlantInfo(const std::string& chipName, int addCount);
    virtual bool ICloudRequestSynchronizeAvatarInfo(const std::string& chipName, int addCount);
    // virtual bool ICloudRequestSynchronizePendantInfo(const std::string& pendantName, int level, const std::string& chipName, int addCount);
    
    virtual bool ICloudRequestSynchronizePlantInfo(const std::map<std::string, int> &plantChipList);
    virtual bool ICloudRequestSynchronizeAvatarInfo(const std::map<std::string, int> &avatarChipList);
    // virtual bool ICloudRequestSynchronizePendantInfo(const std::map<std::string, int> &pendantList, const std::map<std::string, int> &pendantChipList);
    
    // virtual bool ICloudRequestSynchronizePendant(const std::map<std::string, int> &pendantList);
    // virtual bool ICloudRequestSynchronizePendantChip(const std::map<std::string, int> &pendantChipList);

    virtual void OnICloudRequestSynchronizePlantInfo(const NetWorkMsg& data);
    virtual void OnICloudRequestSynchronizeAvatarInfo(const NetWorkMsg& data);
    // virtual void OnICloudRequestSynchronizePendantInfo(const NetWorkMsg& data);

    
    virtual bool ICloudRequestPlantLevelUp(int i_plantChipId);
    virtual void OnICloudRequestPlantLevelUp(const NetWorkMsg& data);
    
    virtual bool ICloudRequestChangePlant(int i_plantChipId);
    virtual bool ICloudRequestChangeAvatar(int i_avatarChipId);
    virtual void OnICloudRequestChangePlant(const NetWorkMsg& data);
    virtual void OnICloudRequestChangeAvatar(const NetWorkMsg& data);
    
    virtual bool ICloudRequestSoldPendant(int64 i_accid, int64 i_skuid);
    virtual void OnICloudRequestSoldPendant(const NetWorkMsg& data);
    virtual bool ICloudRequestExchangePendant(int i_skuid);
    virtual void OnICloudRequestExchangePendant(const NetWorkMsg& data);
    virtual bool ICloudRequestSteadyPendant(int64 i_skuid);
    virtual void OnICloudRequestSteadyPendant(const NetWorkMsg& data);
    virtual bool ICloudRequestResetPendant(int64 i_skuid);
    virtual void OnICloudRequestResetPendant(const NetWorkMsg& data);

    // --------------------- Plant Trial ---------------------
    virtual bool ICloudRequestPlantTrial(int i_plantid, int i_gem, int i_toLevel, int n_sceneid);
    virtual void OnICloudRequestPlantTrial(const NetWorkMsg& data);
};
#endif
