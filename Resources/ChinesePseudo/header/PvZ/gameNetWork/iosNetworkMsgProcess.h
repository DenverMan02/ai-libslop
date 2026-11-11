//
//  iosNetworkMsgProcess.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-2-20.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__iosNetworkMsgProcess__
#define __PlantsVersusZombies2__iosNetworkMsgProcess__

#include <iostream>
#include "NetworkMsgProcess.h"
#include "NetworkCacheQueue.h"
#include "NetworkHelper.h"

enum Scene_ID
{
    SI_STORE = 1,
    SI_LOTTERY,
    
    SI_COUNT = SI_LOTTERY
};

class iosNetworkMsgProcess : public INetworkMsgProcess
{
public:
    iosNetworkMsgProcess(){}
    virtual ~iosNetworkMsgProcess(){}
    virtual void Initialize() override;
    
    // ----------------icloud request ----------------------
    virtual bool ICloudRequstLogin(const std::string& defineId) override;
    virtual bool ICloudRequestUploadProfile(const std::string& profile,const std::string& md5,const std::string& sumary, bool wait) override;
    virtual bool ICloudRequestProfileList() override;
    
    virtual bool ICloudRequestSingleProfile(int profileId) override;
    virtual bool ICloudRequestSinglePlayerInfo() override;
    virtual bool ICloudRequestUploadFirstTime(const std::string& profile,const std::string& md5,const std::string& sumary, bool wait, class PlayerInfo* uploadProfile) override;
    // ----------------iflush request ----------------------
    virtual bool IFlushCacheRequestUpdateDatePlantFragments() override;
    virtual bool IFlushCacheRequestUpdateDateDressFragments() override;
    virtual bool IFlushCacheRequestUpdateDatePendantInfo() override;
    virtual bool IFlushCacheRequestUpdateAddFreeGem() override;
    virtual bool IRequestFlushCacheObjects() override;
    
    // ----------------endless request ---------------------
    virtual bool ICloudRequestGetEndlessRankAndLife(int i_offset) override;
    virtual bool ICloudRequestEndlessConsumeLife() override;
    virtual bool ICloudRequestEndlessUpdateScore(int i_score, int i_weight, int i_stage, int i_wave, int i_result, int i_levelTime, int i_levelScore) override;
    
    virtual bool ICloudRequestConsumeLeafs(int i_skuid) override;
    
    // ------------- 2015 New Year Charge Reward -------------
    virtual bool ICloudRequest2015NewTearChargeStat() override;
    virtual bool ICloudRequestGet2015NewTearChargeReward(int i_objectId) override;
    
    // -------------------- Pendant Gacha --------------------
    bool ICloudRequestPendantGacha(int i_actid) override;
    bool ICloudRequestGoldcanGacha(int i_actid) override;
    
    // --------------------- Plant Trail ---------------------
    bool ICloudRequestPlantTrial(int i_plantid, int i_gem, int i_toLevel, int n_sceneid) override;
    
    // ----------------- Consumption Reward ------------------
    bool ICloudRequestConsumptionRewardStat();
    
    // ----------------- Gem Return ----------------------------
    bool ICloudRequestGetGemReturnState();
    bool ICloudRequestGetGemReturnReward(int i_index);
    
    ///only for ios
    bool ICloudRequestCharge(const std::string& transaction, const std::string& transactionId, const std::string& sku, const int& objectId);

    bool ICloudRequestConfigFileVersionNumber();

    bool ICloudRequestSynchronizePlantInfo(const std::string& chipName, int addCount) override;
    bool ICloudRequestSynchronizeAvatarInfo(const std::string& chipName, int addCount) override;
    bool ICloudRequestSynchronizePendantInfo(const std::string& pendantName, int level, const std::string& chipName, int addCount);
    
    bool ICloudRequestSynchronizePlantInfo(const std::map<std::string, int> &plantChipList) override;
    bool ICloudRequestSynchronizeAvatarInfo(const std::map<std::string, int> &avatarChipList) override;
    bool ICloudRequestSynchronizePendantInfo(const std::map<std::string, int> &pendantList, const std::map<std::string, int> &pendantChipList);
    
    bool ICloudRequestSynchronizePendant(const std::map<std::string, int> &pendantList);
    bool ICloudRequestSynchronizePendantChip(const std::map<std::string, int> &pendantChipList);
    
    // this is only for iOS(Higher than 1.8.0)
    std::string getObjectJsons(const std::vector<NetworkCacheObjects>& i_objectList);
    std::string getObjectJsons(const int i_objectId, int i_quantity, std::string i_src);
    
    bool ICloudRequestSyncWithNameAndSource(const std::string& i_objectName, int i_quantity, std::string i_src, int i_level = 0);
    bool ICloudRequestSyncWithIdAndSource(const int i_objectId, int i_quantity, std::string i_src, int i_level = 0);
    bool ICloudRequestSyncObjectListWithSource(const std::vector<NetworkCacheObjects>& i_gemsList);
        
//    bool ICloudRequestTotalLoginRewardInfo();
//    bool ICloudRequestGetLoginReward(int dayId);
    
    bool ICloudRequestAddFreeGem(int actid, int count);
    bool ICloudRequestCompensation(std::string code);
    bool ICloudRequestChargeReward(int i_type, int i_index, int i_select_index) override;
    bool ICloudRequestDoGacha(int actid, const DRefPtr<ICloudRequestCallbackFunctionBase>& fCallback) override;
    bool ICloudRequestGetGachaInfo();
    
    bool ICloudRequestChangePlant(int i_plantChipId) override;
    bool ICloudRequestChangeAvatar(int i_avatarChipId) override;
    bool ICloudRequestPlantLevelUp(int i_plantChipId) override;
    
    bool ICloudRequestDailySignRewardInfo(int i_typeId);
    bool ICloudRequestGetDailySignReward(const std::vector<int>& i_bonusList);
    
    void ICloudRequestRelogin(const std::string& defineId);
    
    bool ICloudRequestBuyPlantGift(int i_costGem, int i_packageId, int i_plantChip, int i_avatarChip, int i_toLevel);
    
    bool ICloudRequestTimeLevelList(int i_id);
    bool ICloudRequestStartTimeLevelCD(int i_id, int i_failCoolDown);
    bool ICloudRequestUnlockTimeLevel(int i_id, int i_gem);
    bool ICloudRequestGetRiddleInfo();
    bool ICloudRequestGetRiddleRedPack(int i_score);
    bool ICloudRequestGetRiddlePrize();
    bool ICloudRequestExchangePendant(int i_skuid) override;
    bool ICloudRequestSoldPendant(int64 i_accid, int64 i_skuid) override;
    
    bool ICloudRequestOpenRedPack(int i_openNum);
    bool ICloudRequestGetRedPackInfo();
    bool ICloudRequestGetRedPackLeaderBoard();
    bool ICloudRequestGetRedPackLeaderBoardReward();
    bool ICloudRequestGetRedPack(int i_count);
    
    // ----------------- Daily Achieve Reward ------------------
    bool ICloudRequestGetDailyAchieveInfo();
    bool ICloudRequestGetDailyAchieveBonus();
    
    // ----------------- Wechat Share Reward -------------------
    bool ICloudRequestGetWechatShareReward();
    
    // ----------------- Birthday Reward -----------------------
    bool ICloudRequestGetBirthdayReward(int i_objectId);
    
    // ----------------- Level of The Day -------------------------
    bool ICloudRequestGetPinataReward() override;
    
    // ----------------- Explore -------------------------------
    bool ICloudRequestGetExploreTeamStatus() override;
    bool ICloudRequestGetExplorePlantStatus(int i_dungeonId) override;
    bool ICloudRequestStartExplore(const std::vector<int>& i_plantList, int i_dungeonId, int i_isCost) override;
    bool ICloudRequestStopExplore(int i_dungeonId, int i_flag) override;
    bool ICloudRequestCalcExploreReward(int i_dungeonId, bool i_ad) override;
    bool ICloudRequestOpenExploreSurpriseBox(int i_dungeonId) override;
    bool ICloudRequestRecoverExplorePlant(int i_plantId, int i_flag) override;
    
    // ----------------- Christmas -------------------------------
    bool ICloudRequestChristmasLottery() override;
    bool ICloudRequestChristmasProtect(int i_reward) override;
    bool ICloudRequestGetAccessoryStat(int i_option) override;
    bool ICloudRequestAccessoryStatBuy(int i_type) override;
    bool ICloudRequestGetGoldenEggStat(int i_option) override;
    bool ICloudRequestGoldenEggOpen(int i_index, int i_chipId) override;
    bool ICloudRequestCheckRebate() override;
    bool ICloudRequestRebate(int iObjectId) override;
    
    // ----------------- Compose Plant -------------------------------
    bool ICloudRequestComposePlant(int i_objectId, int i_quantity, int i_level) override;
    
    // -------------------- UUID request --------------------
    void RequestUUIDBind() override;
    void RequestUUIDLogin() override;
    void RequestUUIDInit() override;
    void RequestUUIDCheck() override;
	
	 // identification check
    void UploadIdentification(const std::string& idcard, const std::string& name, bool logStatus = false);
    
protected:
    // ----------------icloud respond---------------
    void OnICloudRequestProfileList(const NetWorkMsg& data);
    void OnICloudRequstLogin(const NetWorkMsg& data);
    void OnICloudRequestUploadProfile(const NetWorkMsg& data);
    void OnICloudRequestSingleProfile(const NetWorkMsg& data);
    void OnICloudRequestUploadFirstTime(const NetWorkMsg& data);
   
    void OnICloudRequestCharge(const NetWorkMsg& data);

    void OnICloudRequestSynchronizePlantInfo(const NetWorkMsg& data) override;
    void OnICloudRequestSynchronizeAvatarInfo(const NetWorkMsg& data) override;
    void OnICloudRequestSynchronizePendantInfo(const NetWorkMsg& data);
    void OnICloudRequestConfigVersionNumber(const NetWorkMsg& data);
    
    void OnICloudRequestSyncCachedObjects(const NetWorkMsg& data);
    
//    void OnICloudRequestTotalLoginRewardInfo(const NetWorkMsg& data);
//    void OnICloudRequestGetLoginReward(const NetWorkMsg& data);
    
    void OnICloudRequestCompensation(const NetWorkMsg& data);
    void OnICloudRequestAddFreeGem(const NetWorkMsg& data);
    void OnICloudRequestChargeReward(const NetWorkMsg& data);
    void OnICloudRequestChangePlant(const NetWorkMsg& data) override;
    void OnICloudRequestChangeAvatar(const NetWorkMsg& data) override;
    void OnICloudRequestPlantLevelUp(const NetWorkMsg& data) override;
    
    void OnDisconnectWarningDialogClosed();
    void onFreeGemDisconnectWarningDialogClosed();
    
    void OnICloudRequestGacha(const NetWorkMsg& data);
    void OnICloudRequestGetGachaInfo(const NetWorkMsg& data);
    
    void OnICloudRequestDailySignRewardInfo(const NetWorkMsg& data);
    void OnICloudRequestGetDailySignReward(const NetWorkMsg& data);
    
    void OnICloudRequestRelogin(const NetWorkMsg& data);
    void OnICloudRequestBuyPlantGift(const NetWorkMsg& data);
    
    void OnICloudRequestTimeLevelList(const NetWorkMsg& data);
    void OnICloudRequestStartTimeLevelCD(const NetWorkMsg& data);
    void OnICloudRequestUnlockTimeLevel(const NetWorkMsg& data);
    
    // ----------------endless request ---------------------
    void OnICloudRequestEndlessUpdateScore(const NetWorkMsg& data);
    void OnICloudRequestEndlessConsumeLife(const NetWorkMsg& data);
    
    void OnICloudRequestConsumeLeafs(const NetWorkMsg& data);
    void OnICloudRequestGetRiddleInfo(const NetWorkMsg& data);
    void OnICloudRequestGetRiddleRedPack(const NetWorkMsg& data);
    void OnICloudRequestGetRiddlePrize(const NetWorkMsg& data);
    void OnICloudRequestExchangePendant(const NetWorkMsg& data) override;
    void OnICloudRequestSoldPendant(const NetWorkMsg& data) override;
    
    void OnICloudRequestOpenRedPack(const NetWorkMsg& data);
    void OnICloudRequestGetRedPackInfo(const NetWorkMsg& data);
    void OnICloudRequestGetRedPackLeaderBoard(const NetWorkMsg& data);
    void OnICloudRequestGetRedPackLeaderBoardReward(const NetWorkMsg& data);
    void OnICloudRequestGetRedPack(const NetWorkMsg& data);
    
    // ------------- 2015 New Year Charge Reward -------------
    void OnICloudRequest2015NewTearChargeStat(const NetWorkMsg& data);
    void OnICloudRequestGet2015NewTearChargeReward(const NetWorkMsg& data);
    
    // -------------------- Goldcan Gacha --------------------
    void OnICloudRequestPendantGacha(const NetWorkMsg& data);
    void OnICloudRequestGoldcanGacha(const NetWorkMsg& data);
    
    // --------------------- Plant Trial ---------------------
    void OnICloudRequestPlantTrial(const NetWorkMsg& data) override;
    
    // ----------------- Consumption Reward ------------------
    void OnICloudRequestConsumptionRewardStat(const NetWorkMsg& data);
    
    // ----------------- Daily Achieve Reward ------------------
    void OnICloudRequestGetDailyAchieveInfo(const NetWorkMsg& data);
    void OnICloudRequestGetDailyAchieveBonus(const NetWorkMsg& data);
    
    // ----------------- Wechat Share Reward -------------------
    void OnICloudRequestGetWechatShareReward(const NetWorkMsg& data);
    
    // ----------------- Birthday Reward -----------------------
    void OnICloudRequestGetBirthdayReward(const NetWorkMsg& data);
    
    // ----------------- Level of the Day -------------------------
    void OnICloudRequestGetPinataReward(const NetWorkMsg& data) override;
    
    // ----------------- Explore -------------------------------
    void OnICloudRequestGetExploreTeamStatus(const NetWorkMsg& data);
    void OnICloudRequestGetExplorePlantStatus(const NetWorkMsg& data);
    void OnICloudRequestStartExplore(const NetWorkMsg& data);
    void OnICloudRequestStopExplore(const NetWorkMsg& data);
    void OnICloudRequestCalcExploreReward(const NetWorkMsg& data);
    void OnICloudRequestOpenExploreSurpriseBox(const NetWorkMsg& data);
    void OnICloudRequestRecoverExplorePlant(const NetWorkMsg& data);
    
    // ----------------- Christmas -------------------------------
    void OnICloudRequestChristmasLottery(const NetWorkMsg& data);
    void OnICloudRequestChristmasProtect(const NetWorkMsg& data);
    void OnICloudRequestGotAccessoryStat(const NetWorkMsg& data);
    void OnICloudRequestAccessoryStatBought(const NetWorkMsg& data);
    void OnICloudRequestGetGoldenEggStat(const NetWorkMsg& data);
    void OnICloudRequestGoldenEggOpen(const NetWorkMsg& data);
    void OnICloudRequestRebate(const NetWorkMsg& data);
    void OnICloudRequestCheckRebate(const NetWorkMsg& data);
    
    // ----------------- Compose Plant -------------------------------
    void OnICloudRequestComposePlant(const NetWorkMsg& data) override;
    
	// ----------------- Gem Return ----------------------------
    void OnICloudRequestGetGemReturnState(const NetWorkMsg& data);
    void OnICloudRequestGetGemReturnReward(const NetWorkMsg& data);
    
    // -------------------- UUID receive --------------------
    void onRequestUUIDBind(const NetWorkMsg& data);
    void onRequestUUIDLogin(const NetWorkMsg& data);
    void onRequestUUIDInit(const NetWorkMsg& data);
    void onRequestUUIDCheck(const NetWorkMsg& data);
    
public:
    // -------------------- ADS request --------------------
    bool RequestADSReward() override;
    
protected:
    // -------------------- ADS receive --------------------
    void onRequestADSReward(const NetWorkMsg& data) override;
    
public:
    void OnDownloadMagentoFinished(bool result);
private:
    void ShowMainMenu();
    
    
protected:
    virtual void ShowLogoScreen() override;
    
    virtual std::string GetDefineId() override;
    
    template<typename T>
    std::string getArrayByVector(const std::vector<T>& i_list);
    
    bool        isNetworkBusy;
    int         magentoVersion;

    class PlayerInfo* uploadProfile;
    
    bool        m_isOnRelogin;
    int         m_currentProfileID;
};

#endif /* defined(__PlantsVersusZombies2__iosNetworkMsgProcess__) */
