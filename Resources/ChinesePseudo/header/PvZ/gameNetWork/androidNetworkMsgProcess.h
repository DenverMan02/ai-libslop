//
//  androidNetworkMsgProcess.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-2-20.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__androidNetworkMsgProcess__
#define __PlantsVersusZombies2__androidNetworkMsgProcess__

#include <iostream>
#include "NetworkMsgProcess.h"

namespace Message {
void RequestRank();
void RequestACLog(S2C_ACLog& aclog);
}

enum SyncProfileResult
{
	E_SYNC_PROFILE_SUCCESS,
	E_SYNC_PROFILE_SK_INVALID,
	E_SYNC_PROFILE_PROFILE_ERROR,
};

class androidNetworkMsgProcess: public INetworkMsgProcess
{
public:
    androidNetworkMsgProcess();
    virtual ~androidNetworkMsgProcess();
    
	virtual void Initialize();

	void RequestRanks();
	void OnRequestRanks();

	virtual std::string GetDefineId() override;
	bool CheckACLogOpen(){ return !m_aclk.empty(); }
	bool CheckACLogFirstLogin() { return m_oaclk.empty(); }
	bool CheckUseACLogKey();

    // ======================= fake server ==============================
public:
	// ----------------- Explore -------------------------------
	virtual bool ICloudRequestGetExploreTeamStatus();
	virtual bool ICloudRequestGetExplorePlantStatus(int i_dungeonId);
	virtual bool ICloudRequestStartExplore(const std::vector<int>& i_plantList, int i_dungeonId, int i_isCost);
	virtual bool ICloudRequestStopExplore(int i_dungeonId, int i_flag);
	virtual bool ICloudRequestCalcExploreReward(int i_dungeonId, bool i_ad);
	virtual bool ICloudRequestOpenExploreSurpriseBox(int i_dungeonId);
	virtual bool ICloudRequestRecoverExplorePlant(int i_plantId, int i_flag);
        // ----------------- Explore -------------------------------
    void OnICloudRequestGetExploreTeamStatus(const NetWorkMsg& data);
    void OnICloudRequestGetExplorePlantStatus(const NetWorkMsg& data);
    void OnICloudRequestStartExplore(const NetWorkMsg& data);
    void OnICloudRequestStopExplore(const NetWorkMsg& data);
    void OnICloudRequestCalcExploreReward(const NetWorkMsg& data);
    void OnICloudRequestOpenExploreSurpriseBox(const NetWorkMsg& data);
    void OnICloudRequestRecoverExplorePlant(const NetWorkMsg& data);
    
    bool ICloudRequestChargeReward(int i_type, int i_index, int i_select_index) override;
    void OnICloudRequestChargeReward(const NetWorkMsg& data);
    
    // ----------------- Christmas -------------------------------
    virtual bool ICloudRequestGetAccessoryStat(int i_option);
    virtual bool ICloudRequestAccessoryStatBuy(int i_type);
    virtual bool ICloudRequestGetGoldenEggStat(int i_option);
    virtual bool ICloudRequestGoldenEggOpen(int i_index, int i_chipId);
    
    bool ICloudRequestSyncWithNameAndSource(const std::string& i_objectName, int i_quantity, std::string i_src, int i_level = 0);
	bool ICloudRequestSyncWithIdAndSource(const int i_objectId, int i_quantity, std::string i_src, int i_level = 0);
	bool ICloudRequestSyncObjectListWithSource(const std::vector<NetworkCacheObjects>& i_gemsList);
    virtual bool IRequestFlushCacheObjects() override;
    void OnICloudRequestSyncCachedObjects(const NetWorkMsg& data);

    std::string getObjectJsons(const std::vector<NetworkCacheObjects>& i_objectList);
    std::string getObjectJsons(const int i_objectId, int i_quantity, std::string i_src);

    // ======================= real server ==============================
public:
    // --------------------- http respose -----------------------------
    void OnRequestFriendList(const NetWorkMsg& data);
    void OnRequestFrindGiftList(const NetWorkMsg& data);
    void OnRequestFriedBorrowPlant(const NetWorkMsg& data);
    void OnRequestFriendBorrowedPlantList(const NetWorkMsg& data);
    void OnRequestFreshGems(const NetWorkMsg& data);
    void OnRequestSurportPlant(const NetWorkMsg& data);
    void OnRquestPlayerInfo(const NetWorkMsg& data);
    void OnRquestSendGift(const NetWorkMsg& data);
    void OnRequestLogin(const NetWorkMsg& data);
    void OnRequestHeartBeat(const NetWorkMsg& data);
    void OnRequestProfile(const NetWorkMsg& data);
    void OnRequestAcceptFriendGitf(const NetWorkMsg& data);
    void OnRequestUpdateProfile(const NetWorkMsg& data);
    void OnRequestUpdateLevelScore(const NetWorkMsg& data);
    void OnRequestFriendLeaderBoard(const NetWorkMsg& data);
    void OnRequestTodaySendGiftList(const NetWorkMsg& data);
    void OnRequestIncreaseGems(const NetWorkMsg& data);
    void OnRequestRandReward(const NetWorkMsg& data);
    void OnRequestSendTLog(const NetWorkMsg& data);
    void OnRequestAddFriendShip(const NetWorkMsg& data);
    void OnRequestLaunchSave(const NetWorkMsg& data);
    void OnRceivLocalmsg();
    void OnRequestTimeLevelList(const NetWorkMsg& data);
    void OnRequestStartTimeLevelCD(const NetWorkMsg& data);
    
    //---------------------------------------------icloud---------------------
    void OnICloudRequstLogin(const NetWorkMsg& data);
    void OnICloudRequestGetProfile(const NetWorkMsg& data);
    void OnICloudRequestUpLoadProfile(const NetWorkMsg& data);
    void OnICloudRequestProfileMd5(const NetWorkMsg& data);
    
    // -------------------- UUID receive --------------------
    void onRequestUUIDBind(const NetWorkMsg& data);
    void onRequestUUIDLogin(const NetWorkMsg& data);
    
    void onRequestUUIDInit(const NetWorkMsg& data);
    void onRequestUUIDCheck(const NetWorkMsg& data);
    
    // Danger room
    void OnUploadDangerRoomRank(const NetWorkMsg& data);
    void OnRequestDangerRoomRank(const NetWorkMsg& data);
    
    //redpack
    void OnRequestGetRedPackLeaderBoard(const NetWorkMsg& data);    
    
    // -------------------- payment validation --------------------
	void onInitPurchaseOrder(const NetWorkMsg& data);
	void OnRequestUpdateChargeInfo(const NetWorkMsg& data);
	void OnRequestLostPurchaseOrder(const NetWorkMsg& data);

	// -------------------- ac log --------------------------------
	void onRequestACLog(const NetWorkMsg& data);
	void onRequestSyncPlayerData(const NetWorkMsg& data);
	void onRequestDownloadPlayerData(const NetWorkMsg& data);

    //  ------------------- http request ------------------------------
    void SendHttpRequest(ParaMap& params, bool bWait = false, const std::string& i_hint = "[NET_CONNECTING]", bool bPause =
                         false, bool bFlush = false);
    void SendHttpRequestNoErro(ParaMap& params);
    void HttpReqFriends();
    void BorrowFriendPlant(unsigned int friendId);
    void RequestBorrowedPlantList();
    void FreshGems(int gemsCount, const std::string& pf,
                   const std::string& pfkey);
    void RequestPlayInfo();
    void SendGift(int giftType, int receverId);
    void Login(const std::string& token, const std::string& defineId,
               int plantFormId, const std::string& refreshToken);
    void HeartBeat();
    void RequestFrindGiftList();
    void RequestProfile();
    void RequestAcceptFriendGitf(const std::string& senderIdArray);
    void RequestUpdateProfile(const std::string& profile,
                              const std::string& md5);
    void RequestUpdateLevelScore(int lvlId, int lvlStar, unsigned long time,
                                 const std::string& formationData);
    void RequestFriendLeaderBoard(int lvlId);
    void RequestTodaySendGiftList();
    void RequestIncreaseGems(int wayId);
    void RequestRandReward();
    void RequestSendTLog(const std::string& jsonText);
    void RequestAddFriendShip();
    void RequestLaunchSave(const std::string& pf, const std::string& pfkey);
    void RequestTimeLevelList(int iID = -1);
    void RequestStartTimeLevelCD(int iID);
    
    // -------------------- UUID request --------------------
    void RequestUUIDBind();
    void RequestUUIDLogin();
    
    void RequestUUIDInit();
    void RequestUUIDCheck();
    
    // ----------------icloud ----------------------
    bool ICloudRequstLogin(const std::string& defineId);
    bool ICloudRequestGetProfile();
    bool ICloudRequestUpLoadProfile(const std::string& profile,
                                    const std::string& md5, const std::string& sumary, bool wait);
    bool ICloudRequestProfileMd5();
    
    // DangerRoom
    void UploadDangerRoomRank(int score, int weight, int currentLevel,
                              int currentWave, int result, int levelTime, int currentScore);
    void RequestDangerRoomRank(int i_preRank);
    
    //redpack
    void RequestGetRedPackLeaderBoard();
    
    // -------------------- payment validation --------------------
	void InitPurchaseOrder(const std::string& i_sku);
	void RequestUpdateChargeInfo(const std::string& productId, bool isRestore, int objectId);
	void RequestLostPurchaseOrder();

	// -------------------- ac log --------------------------------
	void RequestACLog(S2C_ACLog& acLog);
	SyncProfileResult RequestSyncPlayerData();
	bool RequestDownloadPlayerData();

    // -------------------- ADS request --------------------
    bool RequestADSReward() override;

    // identification check
    void UploadIdentification(const std::string& idcard, const std::string& name, bool logStatus = false);

    bool ICloudRequestChristmasLottery() override;
    void OnICloudRequestChristmasLottery(const NetWorkMsg& data);

    // -------------------- Bind Unique ID --------------------
    void ICloudRequestBindingUniqueID(const std::string& platform_id, const std::string& uniqueID);
    void OnICloudRequestBindingUniqueID(const NetWorkMsg& data);
    bool EnableBindUniqueID();
    bool EnableBindForUUID();

protected:
    // -------------------- ADS receive --------------------
    void onRequestADSReward(const NetWorkMsg& data) override;

    template<typename T>
    std::string getArrayByVector(const std::vector<T>& i_list);

private:
    void InitAfterLogin() override;
    
    void ShowClearProfileHint();
    void DoContinuedLoginV202ClearProfile(class UIMessageBox* box, int buttonID);
    void DoContinuedLoginV202();

private:
    bool m_bCanUpLoadProfile;
    std::string m_aclk;
    std::string m_oaclk;
    uint8 m_downloadProfileRetry;
    const uint8 m_retryRequestTimes;
    uint8 m_syncProfileRetry;
    const uint8 m_retrySyncProfileTimes;
    bool m_useACLogKey;
    bool isNetworkBusy;
    bool m_bShouldBindUniqueID;// zhousen if should bind unique id.
    bool m_bBindForUUID;
};

#endif /* defined(__PlantsVersusZombies2__androidNetworkMsgProcess__) */
