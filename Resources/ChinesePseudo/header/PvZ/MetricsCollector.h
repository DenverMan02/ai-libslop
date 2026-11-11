//
//  MetricsCollector.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 8/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_MetricsCollector_h
#define PlantsVersusZombies2_MetricsCollector_h

#include "MetricsManager.h"
//#include "SeedBank.h"
#include "FakeHttpDriver.h"
#include "MagentoService.h"
#include "Wave.h"
//#include "NetworkData.h"

typedef struct S2C_BonusInfo S2CBonusInfo;
typedef struct S2C_CodeRewardPlantNum S2CCodeRewardPlantNum;
typedef struct DamageInfo Damage_Info;

class WaveDefinition;
class Plant;
class MapEventItem;
class FBOpenGraphAction;
class TreasurePool;
struct TreasureReward;
struct ArenaPlantPositionData;
struct ZombieRecord;
struct PvpPlantLostRecord;


struct LogItemInfo
{
    std::string type;
    std::string itemName;
    int         num = 1;
    int         lv = 1;
};

struct LogPurchaseInfo
{
    std::string costKind;
    std::string locationKind;
    std::string location;
    int         freeGemsCost = 0;
    int         cost = 0;
    std::vector<LogItemInfo> itemInfos;
};

struct LogGameItemData
{
public:
    LogGameItemData() {}
    LogGameItemData(int i_id, int i_num) : m_id(i_id), m_numChanged(i_num) {}
    int m_id = 0;
    int m_numChanged = 0;
    int m_level = 0;
    int m_freeNum = 0;
};

struct EventMetrics
{
	std::string objName;
	int		objCount;
    int		price;

    EventMetrics(std::string theName,int theCount, int thePrice)
	{
    	objName   = theName;
    	objCount = theCount;
    	price = thePrice;
	}
};

struct PlantPackage
{
	std::string plantName;
	int plantLevel;
	int buyAvatar;
	int plantLevelPrice;
	int plantLevelCost;
	int avatarPrice;
	int avatarCost;
};

struct PlantInfo
{
    PlantInfo():iPlantId(0),iLv(0),bAvatar(false)
    {
        
    }
    
    int  iPlantId;
    int  iLv;
    bool bAvatar;
};

enum TutorialEvent
{
	enter_newplayer_tutorial = 1,
	finish_newplayer_tutorial,
	enter_egypt1,
	egypt1_getplantfood,
	egypt1_speedup_prompt,
	egypt1_speedup_buttonclick,
	egypt1_finish,
	gacha_tutorial_start,
	gacha_tutorial_finish,
	enter_egypt2,
	egypt2_click_powerup_cuke,
	egypt2_finish,
	almanace_tutorial_start,
	almanace_tutorial_click,
	enter_egypt3,
	egypt3_buyplantfood,
	egypt3_finish,
	egyptchallenge01_tutorial_start,
	egyptchallenge01_gate_open,
	enter_egyptchallenge01,
	get_egypt_mower,
	star_plant_tutorial_start,
	get_iceburg,
	enter_egypt4,
	egypt4_buysun,
	bloomerange_tutorial_start,
	planttried_bloomerange_popup,
	get_freegems18,
	enter_egypt5,
	get_gravebuster_pieces,
	click_plant_levelup_button,
	get_gravebuster,
	dailychallenge_tutorial_start,
	dailychallenge_tutorial_finish,
	enter_egypt6,
	egypt6_finish,
	goldencan_tutorial1_start,
	get_sunflower_avatar,
	enter_egypt7,
	egypt7_finish,
	goldencan_tutorial2_start,
	peashoot_equipment_finish
};

enum TutorialType
{
    TutorialType_PVE,
    TutorialType_PVP,
};

enum TutorialEventNew
{
    Tutorial_enter_egypt1 = 1,
    Tutorial_pickup_sun = 2,
    Tutorial_pickup_plantfood = 3,
    Tutorial_use_plantfood_peashooter = 4,
    Tutorial_enter_egypt2 = 5,
    Tutorial_egypt2_click_powerup_cuke = 6,
    Tutorial_enter_egypt3 = 7,
    Tutorial_penny_talk1 = 8,
    Tutorial_get_slot_1 = 9,
    Tutorial_enter_egypt4 = 10,
    Tutorial_enter_egypt5 = 11,
    Tutorial_try_boomerang = 12,
    Tutorial_adventure_boomerang = 13,
    Tutorial_enter_egypt6 = 14,
    Tutorial_exchange_torchwood = 15,
    Tutorial_enter_egypt7 = 16,
    Tutorial_buy_plantfood = 17,
    Tutorial_buy_sun = 18,
    Tutorial_enter_egypt9 = 19,
    Tutorial_try_bonkchoy = 20,
    Tutorial_adventure_bonkchoy = 21,
    Tutorial_enter_egypt10 = 22,
    Tutorial_click_shop_icon = 23,
    Tutorial_enter_egypt11 = 24,
    Tutorial_click_free_gacha = 25,
    Tutorial_dave_penny_talk2 = 26,
    Tutorial_unlock_pirate_stargate = 27,
    Tutorial_clear_pirate2 = 28,
    Tutorial_click_pvp_icon = 29,
    Tutorial_click_training_zombie = 30,
    Tutorial_set_defense = 31,
    Tutorial_click_immediately_done = 32,
    Tutorial_click_pvp_stage = 33,
    Tutorial_plant_peashooter = 34,
    Tutorial_user_plantfood_cabbagepult = 35,
    Tutorial_enter_egypt8 = 36,
    Tutorial_check_in = 37,
};

struct LogCacheInfo
{
	std::string time;
	std::string buytime;

	LogCacheInfo()
	{
		time = "";
		buytime = "";
	}
};

struct PlantAdventureLogInfo
{
	int ObjectID;
	int ObjectCount;
	int coins;
	int gemscost;

	PlantAdventureLogInfo()
	{
		ObjectID = 0;
		ObjectCount = 0;
		coins = 0;
		gemscost = 0;
	}
};


struct PlantSalesUiReward
{
    std::string plantName = "";
    int objectCount = 0;
    int beforeCount = 0;
    int beforeLevel = -1;
    int afterLevel = -1;

};

struct PlantAdventureRewardInfo
{
    int              dungeonId;
    int              coinsReward;
    int              gemsCost;
    std::vector<S2CBonusInfo>  plantClip;
    std::vector<S2CBonusInfo>  plantSurpriseInfo;
};

struct TrackInfo
{
    std::string id;
    std::string d1;
    std::string d2;
    std::string d3;
    std::string d4;
    std::string re;
};

namespace Message
{
    void AddPlantSalesUiReward(const PlantSalesUiReward& i_reward);
    void LineUnlock(const MapEventItem*  interactingEvent,std::string& worldName,int freeCostGems);
    void ToturiIgnore(int ignore);
    void PlantUnlockFragment(const MagentoProductPropsPtr& prpduct,int costFreeGems);
    void CoinUse(int const, const std::string& objName);
    void MissionGemsUse(const MagentoProductPropsPtr& prpduct,bool bForSun,int costFreeGems);
    void GateUnLock(const MapEventItem* event,const std::string& worldName,int costFreeGems);
    void PlantUnLockByStar(int needStars,const std::string& plantName);
    void MissionUnlock(const std::string& missName);
    void Gift(const std::string& plant,const int coinCount);
    void Fake(const int fakeCode);
    void GetFreeGems(const std::string& typeId,const int getFreeGems);
    void GetRechargeGems(const int getGemsCount, const int costPrice);
    void ItemPurchase(const MagentoProductPropsPtr& prpduct,int costFreeGems);
    void EventPurchase(EventMetrics* metrics,int costFreeGems);
    void ItemCoinPurchase(const MagentoProductPropsPtr& prpduct);
    void ItemPurchaseInfo2(const MagentoProductPropsPtr& info,const std::string& location,int costFreeGems);
    void TmallClick();
    void CheckUpdateClick();
    void GetGachaReward(int price);
    void GetLimitedGachaReward(int price,bool isfirst);
    void GetNewGachaReward(int price);
    void PlantLevelUp(const std::string& type, int level);
    void GemCompensation(int gems);
    void RechargeRewardGot(int i_type, int i_rechargeNum, const std::map<int, int>& i_rewardContent);
    void RechargeBundleLog(const std::string& logType, int bundleId, const std::string& pushType);
    void GLLotteryReward(int i_chancecUsed, int i_gemsUsed, const std::map<int, int>& i_rewardContent);
    void TGCraft(int i_type, const std::map<int, int>& i_rewardContent);
    void TGTutorial(int i_step);
    void Jump(int i_fromId, int i_targetId);
    void DailySignReward(int iDailyNumber, int iRewardType);
    void StartNewVersionGame();
    void GameLoadStart();
    void GameLoadEnd(const std::string& i_loadTime);
    void GameReady();
    void ItemLogin();
    void NewAccountRegister();
    void MissionStart(const std::string& wldName,const std::string& missonName,int istars);
    void ItemExChange(const MagentoProductPropsPtr& prpduct,int cost,int costtype);
    void GoldCanOpen(const TreasurePool* pTreasurePool, std::vector<const TreasureReward*>& vecRewards);
    void DangerRoomFinish(std::vector<PlantInfo>& plantInfo,int iLevel, int iScore);
    void DangerRoomWaveFinish(int iWave,int iLevel);
    void DangerRoomWaveStart(int iWave,int iLevel);
    void DangerRoomAwardGet(int iLevel);
    void GetDangerRoomLootReward(int iWave,int iLevel,std::vector<PlantInfo>& plantInfo);
    void MissionGemUse(const std::string& name,int i_amont,int costFreeGems);
    void ChargePay(const std::string& reason,int iPrice);
    void OpenUI(const std::string& openUI);
    void GetReward(const std::string& strRewardType,const std::string& strRewardName);    
    void RedPackOpen(int i_openNum);
    void SpecificGoodsObtain(const std::string& i_objectName, int i_num);    
    void RiddlesCorrectPercent(int i_percent);
    void RiddlesParticipate();    
    void IfengfengClick();
    void InValidAccount();
    void Toturi(int i_type, int i_state);   // i_type: TutorialType; i_state: TutorialEventNew
    void PlantLevelUpOK(const std::string& type, int level);
	void SNSFlow();
    void PlayerStarFlow(int i_newAmount);
    void PlayerLogout();
    void NewerBagPay(int rmb, int type);
    
    void DLCRecord(int type);
    void PlantPackageBuy(PlantPackage* pPackage);
	void PlantTrialBuy(int iType, const std::string& strTrialName);

    void WorldMapUnLock(int gems ,const std::string& worldName,int costFreeGems);
    
	// New Game Start Logs
	void GameBegin();
	void Decompress(int i_type);
	void GameLoad(int i_type);
	void GameReady();
	void GameEnd();
    void RealGameStart();
	// New charge log
    void Recharge(const std::string& sku,const int getGemsCount, const int costPrice);
	void GameCharge(const std::string& i_name, const std::string& i_description, const std::string& i_sku);
	void ChargeReward(const std::string& str_item);
	void GemsCostReward(int step);
	void LanternReward(int Level);
    void BlackPackageCharge(const std::string& sku);

    void GetGachaUseGems(int paidGems,int freeGems);
    
	void BuyTimeMetrics(std::vector<LogCacheInfo>& i_info);

    void RedPacketRewardGot(int i_type, int i_Num, const std::map<int, int>& i_rewardContent);

    void MissionDiamondUse(int levelId, const std::map<int, int>& propContent);
    void FiveYearsRushthrough(const std::vector<int>& params);;
    void FiveYearsCosmobonus(const std::vector<int>& rewardId);
    void FiveYearsExchange(const std::map<int, int>& exchangeNeed, int id);
    void NationalDayStoneLottery(int propid, int count);
    void NationalDayDailyReward(int day, const std::vector<int>& rewardId);
    void NationalDayChargeReward(const std::string& productId, const std::vector<int>& rewardId);
    void BattleShop(int coinCount, int propId);
    void BattleZ(const std::vector<int>& params, const std::vector<int>& ourPlantList, const std::vector<int>& theirPlantList);
    void BattleVictory(int winStreak, int rewardId);
    void BattleBuyTimes(const std::string& buyPatterns,int num, int propId);
    void BattleSettlement(int points, int rank, const std::map<int, int>& i_rewardContent);
    void LimitLotteryBuyCoin(int yuan, int coin);
    void LimitLotteryDraw(const std::vector<int>& params, const std::vector<int>& props);
    void LimitLotteryExchange(const std::vector<int>& params);

    void DoubleFestivalDailyReward(int i_day, const std::vector<int>& i_reward, std::vector<int>& i_before);
    void DoubleFestivalLotteryDraw(const std::vector<int>& i_data, const std::vector<int>& i_reward, const std::vector<int>& i_before);
    void DoubleFestivalRechargeReward(int level, const std::vector<int>& i_reward, const std::vector<int>& i_before);

    //double festivel buried point
    void CommonBuryInterface(int i_id, const TrackInfo& i_data, bool is_cache);

	// Update Log
	void ChooseUpdateResult(int i_type); // 0 is update immediately, 1 is update later
	void DownloadUpdateVersion(int i_type); // 0 is start, 1 is end
	void InstallUpdateVersion(int i_type); // 0 is start, 1 is end
	void GetUpdateReward();
	void TutorialFTUE(int event);
    
	// National Day log
	void DailyAchievement(int i_actId, int i_targetNum);
	void DangerRoomReward(int i_itemId);
	void NationalDayConsumeDimondsInLottery(const std::string& itemName, int iCount);
	void Charge10Reward(int i_plantId, int i_plantLv);
	void CheckBossFightRate(bool isWin);
//	void SendSeedBank(void* sendBankPtr);

	void OldUserBackReward(int i_rewardtype);
	void WechatShare();
	void BirthdayZReward(int i_rewardtype);
	void BirthdayZFinish(bool isWin);

	void PlantAdventure(int step, const PlantAdventureLogInfo& info);
    
    void ActiveProtectFinish(int i_result,int i_rewardnum);
    void ActiveNewYearFinish(int i_type,const std::string& i_rewardcontent);
    void DailyAccessoryBonusFinish(int i_costtype);
    // 1.0 yuan Log
    void IOSGemsReturn(int iStep);
    
    void LaunchCuke(bool success, int i_gemCost, int freeGem);
    void LimitedSalesBought(int i_gemCost, int i_pieceCount);
    void LoginRewardInfo(int i_loginId,int itemid,int mount);
    void FestivalEntrance(int mode,int level,const std::string& itemName);

    void PinataParty(const std::string& activeLevelName);
    
    void AndroidSDKInit(int isEnd,int state);
    void AndroidSDKLogin(int isEnd,int state);
    
    void RechargeLog(const MagentoProductPropsPtr& info);
    void RechargeLogWithSalesUiReward(const MagentoProductPropsPtr& product);
    void RechargeLogWithSalesUiReward2();
    void JoinActivity(const std::string& activityName);
    void SummerActivity(const std::string& activityName);
    
    void EASquareReward(const std::string& placement,const std::vector<S2CBonusInfo>& rewards);
    
    void RechargeForCukePackage(const MagentoProductPropsPtr& product);
    
    void CodeReward(const std::string& codeInfo,const std::string& channelId, const std::vector<S2CCodeRewardPlantNum>&  rewardInfo);

    void AndroidSDKQueryOrder(const std::string& codeId, int resultCode);
}

struct GameplayMetrics
{
	GameplayMetrics()
	{
		GameStartTime = 0.0f;
		SunSpawned = 0;
		SunCollected = 0;
		SunSpent = 0;
		PlantFoodSpawned = 0;
		PlantFoodSpawnedWhenFull = 0;
		PlantFoodGrabsWhenFull = 0;
		PlantFoodPurchased = 0;
		PlantFoodCollected = 0;
		PlantFoodSpent = 0;
		WavesGenerated = 0;
		MowersTriggered = 0;
		PlantsPlanted = 0;
		PlantsLost = 0;
		TotalPlantDamage = 0;
		CoinsSpawned = 0;
		CoinsCollected = 0;
		PinchPowerupUses = 0;
		FlickPowerupUses = 0;
		WizardFingerPowerupUses = 0;
//PVZ2_CHINESE_START
		TacticalCukePowerupUses = 0;
        SnakeRevives = 0;
        SnakeMowers = 0;
        OakShooters = 0;
//PVZ2_CHINESE_END
        RevealVasePowerupUses = 0;
		ButterZombiePowerupUses = 0;
		MoveVasePowerupUses = 0;
		CoinsSpentOnPowerups = 0;
		CoinsSpentOnPlantfood = 0;
		KeysCollected = 0;
		YetiSpawned = 0;
		YetiDefeated = 0;
        
        //PVZ2_CHINESE_BEGIN
        SunShoveUsedCount = 0;
        //PVZ2_CHINSE_END
	}
	
	// NOTE -- If you add variables here, expose them in BoardSaveState::StaticClassInit()
	// or they will be wiped out if the user saves and loads a game

	pvztime_t GameStartTime;
	int SunSpawned;
	int SunCollected;
	int SunSpent;
	int PlantFoodSpawned;
	int PlantFoodSpawnedWhenFull;
	int PlantFoodGrabsWhenFull;
	int PlantFoodPurchased;
	int PlantFoodCollected;
	int PlantFoodSpent;
	int WavesGenerated;
	int MowersTriggered;
	int PlantsPlanted;
	int PlantsLost;
	int TotalPlantDamage;
	int CoinsSpawned;
	int CoinsCollected;
	int PinchPowerupUses;
	int FlickPowerupUses;
	int WizardFingerPowerupUses;
//PVZ2_CHINESE_START
	int TacticalCukePowerupUses;
    int SnakeRevives;
    int SnakeMowers;
    int OakShooters;
    int SpringGiftCharge;
//PVZ2_CHINESE_END
    int RevealVasePowerupUses;
	int ButterZombiePowerupUses;
	int MoveVasePowerupUses;   
	int CoinsSpentOnPowerups;
	int CoinsSpentOnPlantfood;
	int KeysCollected;
	int YetiSpawned;
	int YetiDefeated;
    
    //PVZ2_CHINESE_BEGIN
    int SunShoveUsedCount;
    //PVZ2_CHINSE_END
};

//Data structure for individual plants that were placed in a level
struct PlantMetrics {
	PlantMetrics()
	{
		UseCount = 0;
		TimesFoodUsed = 0;
	}
	std::string PlantName;
	int UseCount;
	int TimesFoodUsed;
};

class DString;
namespace MetricsCollectorNameSpace
{
    DString GetMissionName(const std::string& missionName);
}

class MetricsCollector
{   
public:
	MetricsCollector();
	virtual ~MetricsCollector();

	void Init();
	void Term();
	
	const GameplayMetrics& GetGameplayMetrics() const;
	void SetGameplayMetrics(const GameplayMetrics& i_metrics);
	
	void SetEnabled(bool i_enabled) { m_enabled = i_enabled; }
    
    void ResetPvpBattleLogNumber();
    void LogPvpBattleArray(const std::string& battleID, int battleType, int defenderID, const std::vector<ArenaPlantPositionData>& plant, const std::string& zombieInfos);
    void LogPvpZombiePlace(const std::string& battleID, const std::string& zombie, int level, int row, time_t time);
    void LogPvpSkillUse(const std::string& battleID, const std::string& skillName, int skillLevel, const Sexy::Point& pos, time_t time);
    void LogPvpBrainDie(const std::string& battleID, int row, time_t time);
    void LogPvpRecycleZombie(const std::string& battleID, const std::string& zombie, int level, time_t time);
    void LogPvpPlantfoodZombie(const std::string& battleID, const std::string& zombie, int level, bool killed, time_t killTime);
    void LogPvpBattleReslut(const std::string& battleID,
                            int defenderID,
                            time_t battleTime,
                            bool timeout,
                            bool allZombieLost,
                            bool surrender,
                            int star,
                            const std::vector<ZombieRecord>& lostZombie,
                            const std::vector<PvpPlantLostRecord>& lostPlant,
                            int lostZombieCost,
                            int flagLeft);
    void LogPvpLogin(time_t time);
    void LogPvpLoadTime(const std::string& device, time_t time);
    void LogPvpGuideComplete(int step);
    void LogPvpNetError(time_t time);
    void LogPvpBuyItem(int id, int medalCount);
    void LogPvpRefreshStore(int cost);
    void LogItemPurChase3(const std::string& itemName, int gemCost, int freeGem);
    std::string GetPCPID();
    std::string	GetProductVersion();
    std::string	GetPackageName();
    
    void SendBattleResultVolcanoSnow(class S2C_VacationLevelEndData* pVacationData);
    std::string	 GetGameItemChangedLog(const std::vector<LogGameItemData>& i_itemList);
    void SendBattleResultWithDinosuarDanger(const std::vector<S2CBonusInfo>&  materialInfo);
private:
    void AppendLogHead(const std::string& table);
	void setMetricsManager();
	void setGameID(const std::string& i_userID);
	void setSessionID(const std::string& i_sessionID);
	void registerEventsWithLawnApp();
	void flushCashedEvents();
	void resetSession();
	void resetGameData();
    //PVZ2_CHINESE_BEGIN
    void  OnEnterBack();
    //PVZ2_CHINESE_END

    void onAddPlantSalesUiReward(const PlantSalesUiReward& i_reward);
    
    void onRecharge(const std::string& sku,const int getGemsCount, const int costPrice);
    
	// ECOMM
	void onStorePurchase(class MagentoProductProps* i_props);
	
	// CART INSTANCE
	void onCartInstance(MagentoProductProps* i_props);
	
	// FUNNEL
	void onFunnelEvent(uint64 i_funnelEvent);
    void onTutori(int i_type, int i_state);
	// GAMEPLAY
    void OnLuaNotify(const std::string& rStrEvent);
    void onRechargeLog(const MagentoProductPropsPtr& info);
    void onRechargeLogWithSalesUiReward(const MagentoProductPropsPtr& product);
    void onRechargeLogWithSalesUiReward2();
    void onItemPurchaseInfo2(const MagentoProductPropsPtr& product,const std::string& location,int costFreeGems);
    void onItemPurchaseInfo(const LogPurchaseInfo& info);
    void onItemLogin();
	void reportGameplayMetrics();
	void onLevelStart();
	void onLevelEnd();
	void onSunSpawned(class CollectableSun* i_sun);
	void onSunClicked(class CollectableSun* i_sun, SunCurrency i_upcomingAmount);
	void onSunSpent(int i_amount);
	void onSunProducedByShovel(int i_amount);
	void onPlantfoodSpawned(class CollectablePlantfood* i_plantfood);
	void onPlantfoodGrabbed(class CollectablePlantfood* i_plantfood);
	void onPlantfoodGrabbedWhenFull(class CollectablePlantfood* i_plantfood);
	void onPlantfoodPurchased(const std::string& name,int i_amont,int costFreeGems);//PVZ2_CHINESE_START
 	void onMissinGemUse(const std::string& name,int i_amont,int costFreeGems);//PVZ2_CHINESE_START
	void onNewWaveStarted(const WaveDefinition* i_wave);
    void onWaveStarted(int i_wave, WaveType::WaveType i_type, bool i_isFinal);
	void onMowerTriggered(class LawnMower* i_mower);
	void onPlantPlanted(class Plant* i_plant);
	void onPlantDied(class Plant* i_plant);
	void onPlantDamageTaken(Plant* i_plant, Damage_Info& i_damageRemaining);
	void onCoinSpawned(class CollectableCoin* i_coin);
	void onCoinClicked(class Collectable* i_collectable);
	void onPowerupActivated(class BasePowerup* i_powerup, int i_coinCost,int costFreeGems);
	void onKeyClicked(class Collectable* i_collectable);
	void onPowerupEquipped(const std::string& i_powerupName);
	void onYetiSpawned();
	void onYetiDefeated();
    void OnGift(const std::string& plant, const int coinCount);
    void OnFake(int fakCode);
    void OnGetFreeGems(const std::string& typeId,const int getFreeGems);
    void OnGetRechargeGems(const int getGemsCount, const int costPrice);
    void OnLoginReward(int i_loginId);
    void onChargePay(const std::string& strReason,int iPrice);
    void onOpenUI(const std::string& strUI);
    void onGetReward(const std::string& strRewardType,const std::string& strRewardName);
    void onPlantLevelUpOK(const std::string& type, int level);
    //PVZ2_CHINESE_START TLog
	void onSNSFlow();
    void onPlayerStarFlow(int i_newAmount);
    //PVZ2_CHINESE_END
	
	// PLANTS
	void reportPlantMetrics();
	PlantMetrics& GetOrCreatePlantMetrics(const std::string& plantTypeName);
    void ClearPlantMetricsUsedTimes();
	
	// SESSION
	void onWorldmapLoaded();
	void onSessionStart();
    
    void onGetGachaUseGems(int paidGems,int freeGems);
    
    void onLaunchCuke(bool success, int i_gemCost, int freeGem);
    void onLimitedSalesBought(int i_gemCost, int i_pieceCount);
    void onLoginRewardInfo(int i_loginId,int itemid,int mount);
    
    void onFestivalEntrance(int mode,int level,const std::string& itemName);
    void onFestivalBuyTimes(int i_mode, int times, int cost);
    
    //PVZ2_CHINESE_BEGIN
    void onLineUnlock(const MapEventItem*  interactingEvent,std::string& worldName,int costFreeGems);
    void onTutoriGuidIgnore(int ignore);
    void onPlantUnlockFragment(const MagentoProductPropsPtr& prpduct,int costFreeGems);
    void onAvatarUnlockFragment(const MagentoProductPropsPtr& prpduct, int costFreeGems);
    void onGameStart();
    void onCoinsuse(int cost,const std::string& objName);
    void onMissionGemsUse(const MagentoProductPropsPtr& prpduct,bool bForSun,int costFreeGems);
    void onPlantFoodMissionGemsUse(const MagentoProductPropsPtr& prpduct,int times);
    void onWorldMapUnLock(int gems ,const std::string& worldName,int costFreeGems);
    void onGateUnLock(const MapEventItem*	 event,const std::string& worldName,int costFreeGems);
    void onPlantUnlockStar(int needStarNum,const std::string& plantName);
    void OnMissionUnlock(const std::string& missioName);
    void onWishItem(const std::string& itemName);
    void onItemPurchase(const MagentoProductPropsPtr& prpduct,int costFreeGems);
    void onEventPurchase(EventMetrics* metrics,int costFreeGems);
    void onNewerBagPay(int rmb, int type);
    void onItemCoinPurchase(const MagentoProductPropsPtr& prpduct);
    void onTmallClick();
    void onCheckUpdateClick();
    void onGetGachaReward(int price);
    void onGetLimitedGachaReward(int price,bool isfirst);
    void onGetNewGachaReward(int price);
    void onPlantLevelUp(const std::string& type, int level);
    void onGemCompensation(int gems);
    void onRechargeRewardGot(int i_type, int i_rechargeNum, const std::map<int, int>& i_rewardContent);
    void onRechargeBundleLog(const std::string& logType, int bundleId, const std::string& pushType);
    void OnGLLotteryReward(int i_type, int i_rechargeNum, const std::map<int, int>& i_rewardContent);
    void OnTGCraft(int i_type, const std::map<int, int>& i_rewardContent);
    void OnTGTutorial(int i_step);
    void OnJump(int i_fromId, int i_targetId);
    void onDailySignReward(int iDailyNumber, int iRewardType);
    void onStartNewVersionGame();
    void onGameLoadStart();
    void onGameLoadEnd(const std::string& i_loadTime);
    void onGameReady();
    void onStartMission(const std::string& wldName,const std::string& missionName,int istars);
    void onItemExchange(const MagentoProductPropsPtr& prpduct,int cost,int costtype);
    void onGoldCanOpen(const class TreasurePool* pTreasurePool, std::vector<const struct TreasureReward*>& vecRewards);
    void onDangerRoomFinish(std::vector<PlantInfo>& plants,int iLevel, int iScore);
    void onDangerRoomWaveFinish(int iWave,int iLevel);
    void onDangerRoomWaveStart(int iWave,int iLevel);
    void onDangerRoomAwardGet(int iLevel);
    void onGetDangerRoomLoot(int iWave,int iLevel,std::vector<PlantInfo>& plants);
    void onLoadingComplete();
    void onGameBegin();
    void onRealGameStart();
    void onDecompress(int i_type);
    void onGameLoad(int i_type);
//    void onGameReady();
    void onGameLogin(bool i_success);
    void onGameEnd();
    void onNewAccountRegister();
    void onGameCharge(const std::string& i_name, const std::string& i_description, const std::string& i_sku);
    void onChargeReward(const std::string& str_item);
    void onGemsCostReward(int step);
    void onLanternReward(int Level);
    void onBlackPackageCharge(const std::string& sku);

    void onBuyTimeMetrics(std::vector<LogCacheInfo>& i_info);
    void onChooseUpdateResult(int i_type); // 0 is update immediately, 1 is update later
	void onDownloadUpdateVersion(int i_type); // 0 is start, 1 is end
	void onInstallUpdateVersion(int i_type); // 0 is start, 1 is end
	void onGetUpdateReward();
	void onTutorialFTUE(int event);

    void onRedPackOpen(int i_openNum);
    void onSpecificGoodsObtain(const std::string& i_objectName, int i_num);
    
    void onRiddlesCorrectPercent(int i_percent);
    void onRiddlesParticipate();
    void onIfengfengClick();
    void onInvalidAccount();
    
    void onCodeReward(const std::string& codeInfo,const std::string& channelId, const std::vector<S2CCodeRewardPlantNum>&  rewardInfo);
    //PVZ2_CHINESE_END
    
    // DLC
    void onDLCRecord(int type);
    
    // plant package
    void onPlantPackageBuy(PlantPackage* pPackage);
	void onPlantTrialBuy(int iType, const std::string& strSku);

	// CURRENCY
	void reportCoinsEarned();
	void reportKeysEarned();
	void reportStarsEarned();
	void onCurrencyPlantfoodPurchased(int i_amont);//PVZ2_CHINESE_START
	void onCurrencyPowerupActivated(class BasePowerup* i_powerup, int i_coinCost);
	void onKeyGatePurchased(const MapEventItem* i_gate);
	void onStarGatePurchased(const MapEventItem* i_gate);
    
	void onDailyAchievement(int i_actId, int i_targetNum);
	void onDangerRoomReward(int i_itemId);
	void onNationalDayConsumeDimondsInLottery(const std::string& itemName, int iCount);
	void onCharge10Reward(int i_plantId, int i_plantLv);
	void onCheckBossFightRate(bool isWin);
//	void onSendSeedBank(void* sendBankPtr);

	void onOldUserBackReward(int i_rewardtype);
	void onWechatShare();
	void onBirthdayZReward(int i_rewardtype);
	void onBirthdayZFinish(bool isWin);
    void SendBattleResult(const std::string& title);
    void SendBattleResultNew(const std::string& strResult);
    
    bool NeedPlantTrialLog(const std::string& level);
    
    
    void onPlantAdventureRewardLogStep1(int              dungeonId,
                                      int              coinsReward,
                                      int              gemsCost,
                                      const std::vector<S2CBonusInfo>&  plantClip,
                                      const std::vector<S2CBonusInfo>&  plantSurpriseInfo);
    
    void onPlantAdventureRewardLogStep2(int              dungeonId,
                                      int              coinsReward,
                                      int              gemsCost,
                                      const std::vector<S2CBonusInfo>&  plantClip,
                                      const std::vector<S2CBonusInfo>&  plantSurpriseInfo);
    
    void onPlantAdventure(int step, const PlantAdventureLogInfo& info);
    
    void onActiveProtectFinish(int i_result,int i_rewardnum);
    void onActiveNewYearFinish(int i_type,const std::string& i_rewardcontent);
    void onDailyAccessoryBonusFinish(int i_costtype);

    void OnPinataParty(const std::string& activeLevelName);
    void onSummerActivity(const std::string& activityName);
    
    void onAdsOpen(const std::string& placement);
    void onAdsReward(const std::string& placement,const std::vector<S2CBonusInfo>& rewards);
    
    void onAndroidSDKInit(int isEnd,int state);
    void onAndroidSDKLogin(int isEnd,int state);
    
    void onRechargeForCukePackage(const MagentoProductPropsPtr& productPtr);
    
    void onRedPacketRewardGot(int i_type, int i_Num, const std::map<int, int>& i_rewardContent);

    void onMissionDiamondUse(int levelId, const std::map<int, int>& propContent);
    void onFiveYearsRushthrough(const std::vector<int>& params);//int levelId, float time, bool pass, int crystalCount
    void onFiveYearsCosmobonus(const std::vector<int>& rewardId);
    void onFiveYearsExchange(const std::map<int, int>& exchangeNeed, int id);
    void onNationalDayStoneLottery(int propid, int count);
    void onNationalDayDailyReward(int day, const std::vector<int>& rewardId);
    void onNationalDayChargeReward(const std::string& productId, const std::vector<int>& rewardId);
    void onBattleShop(int coinCount, int propId);
    void onBattleZ(const std::vector<int>& params, const std::vector<int>& ourPlantList, const std::vector<int>& theirPlantList);//bool isWin, int ourPoints, int theirPoint,, int pointBefore, int pointAfter
    void onBattleVictory(int winStreak, int rewardId);
    void onBattleBuyTimes(const std::string& buyPatterns,int num, int propId);
    void onBattleSettlement(int points, int rank, const std::map<int, int>& i_rewardContent);
    void onLimitLotteryBuyCoin(int yuan, int coin);
    void onLimitLotteryDraw(const std::vector<int>& params, const std::vector<int>& props);
    void onLimitLotteryExchange(const std::vector<int>& params);
    
    void onDoubleFestivalDailyReward(int i_day, const std::vector<int>& i_reward, std::vector<int>& i_before);
    void onDoubleFestivalLotteryDraw(const std::vector<int>& i_data, const std::vector<int>& i_reward, const std::vector<int>& i_before);
    void onDoubleFestivalRechargeReward(int level, const std::vector<int>& i_reward, const std::vector<int>& i_before);

    void onCommonBuryInterface(int i_id, const TrackInfo& i_data, bool is_cache);
	// DATA
	Sexy::MetricsManager* m_metricsManager;
	FakeHttpDriver* m_HttpDriverForTest;

	uint64 m_startTime;
	std::string m_gameID;
	std::string m_sessionID;

	std::string m_environment;
	GameplayMetrics m_gameplayMetrics;

    std::string m_wldName;
    bool m_tacticalCukeUsed = false;
	bool m_enabled;
	bool m_sessionNeedsReporting;
	int m_numberOfGamesPlayedThisSession;
	uint64 m_rawSessionTime;
	std::vector<PlantMetrics> m_plantMetrics;
    //PVZ2_CHINESE_BEGIN
    std::map<std::string,int> m_PlantedPlants;
    std::string				  m_ProductVersion;
    //PVZ_CHINISE_END
    int m_pvpBattleLogNumber;
    
    PlantAdventureRewardInfo        m_plantAdventureReward;
    
    int m_gachaUseFreeGems = 0;
    int m_gachaUsePaidGems = 0;
    
    std::vector<PlantSalesUiReward> m_plantSalesRewards;
    MagentoProductProps m_tempMagento;
};

class MetricsRecordInserter {
public:
	MetricsRecordInserter& Add(const std::string& i_fieldName, int i_value);
	MetricsRecordInserter& Add(const std::string& i_fieldName, uint64 i_value);
	MetricsRecordInserter& Add(const std::string& i_fieldName, double i_value);
	MetricsRecordInserter& Add(const std::string& i_fieldName, bool i_value);
	MetricsRecordInserter& Add(const std::string& i_fieldName, const std::string& i_value);
	MetricsRecordInserter& Add(const std::string& i_fieldName, const char *i_value) { return Add(i_fieldName, std::string(i_value)); }
    
protected:
	MetricsRecordInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_tableName, const std::string& i_metricsVersion);
	virtual ~MetricsRecordInserter();

	Sexy::MetricsManager* m_metricsManager;
};

class ECommTableInserter : public MetricsRecordInserter {
public:
	ECommTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class GameplayTableInserter : public MetricsRecordInserter {
public:
	GameplayTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class SessionTableInserter : public MetricsRecordInserter {
public:
	SessionTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class CurrencyTableInserter : public MetricsRecordInserter {
public:
	CurrencyTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class PlantsTableInserter : public MetricsRecordInserter {
public:
	PlantsTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class CartInstanceTableInserter : public MetricsRecordInserter {
public:
	CartInstanceTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class FunnelTableInserter : public MetricsRecordInserter {
public:
	FunnelTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};

class ViralTableInserter : public MetricsRecordInserter {
public:
	ViralTableInserter(Sexy::MetricsManager* i_metricsManager, const std::string& i_environment, const std::string& i_sessionID, const std::string& i_gameID);
};
#endif
