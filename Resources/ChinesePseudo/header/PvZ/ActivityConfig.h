//
//  ActivityConfig.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ActivityConfig__
#define __PlantsVersusZombies2__ActivityConfig__

#include "PVZDB.h"
#include "ProfileMgr.h"
#include "Color.h"
#include "UIHelper.h"

#define REMAIN_TIME_MAX 99*24*3600

enum ActivityTimeStatus
{
	ActivityTimeStatus_NotOpen,
	ActivityTimeStatus_Open,
	ActivityTimeStatus_Close
};

//-----------------------------------------------

struct ActivityDateData
{
    int iStartDate;
    int iEndDate;
    
    ActivityDateData()
    {
        iStartDate = 0;
        iEndDate = 0;
    }
};

struct MysteryCrystalDrop
{
	MysteryCrystalDrop()
	{
		NormalDropAmount = 0;
		HardDropAmount = 0;
	}

	int NormalDropAmount;
	int HardDropAmount;
};

struct GachaRewardItem
{
    int objectId;
    int Count;
    int Probability;
    
    GachaRewardItem ()
    {
        objectId = 0;
        Count = 0;
        Probability = 0;
    }
    
    inline bool operator==(const GachaRewardItem& p) const
	{
		return ((p.objectId == objectId) && (p.Count == Count) && (p.Probability == Probability));
	}
};

//-----------------------------------------------

struct DailyAchievementActivatedData
{
    int  iStartDate;
    int  iEndDate;
    bool bIsActivated;
    
    DailyAchievementActivatedData()
    {
        iStartDate = 0;
        iEndDate = 0;
        bIsActivated = true;
    }
};

//-----------------------------------------------

struct StoreGiftsActivatedData
{
    int  iStartDate;
    int  iEndDate;
    bool bIsActivated;
    
    StoreGiftsActivatedData()
    {
        iStartDate = 0;
        iEndDate = 0;
        bIsActivated = true;
    }
};

//-----------------------------------------------

struct LanternRiddlesActivatedData
{
    int  iStartDate;
    int  iEndDate;
    int	 iEntryCloseDate;
    bool bIsActivated;
    
    LanternRiddlesActivatedData()
    {
        iStartDate = 0;
        iEndDate = 0;
        iEntryCloseDate = 0;
        bIsActivated = true;
    }
};

//-----------------------------------------------

struct RedPackActivedData
{
    int  iStartDate;
    int  iEndDate;
    int	 iEntryCloseDate;
    bool bIsActivated;
    
    RedPackActivedData()
    {
        iStartDate = 0;
        iEndDate = 0;
        iEntryCloseDate = 0;
        bIsActivated = true;
    }
};

struct RedPackClosedData
{
    int  iStartDate;
    int  iEndDate;
    bool bIsActivated;
    
    RedPackClosedData()
    {
        iStartDate = 0;
        iEndDate = 0;
        bIsActivated = true;
    }
};

//-----------------------------------------------

struct ConsumptionActivedItem
{
    int  iStartDate;
    int  iEndDate;
    std::string strTopic;
    
    
    ConsumptionActivedItem()
    {
        iStartDate = 0;
        iEndDate = 0;
    }
};

struct ConsumptionActivedData
{
    bool bIsActivated;
    std::vector<ConsumptionActivedItem> vActItem;
    
    ConsumptionActivedData()
    {
        bIsActivated = true;
    }
};

//-----------------------------------------------

struct DangerRoomActivatedData
{
    int  iEventStartDate;
    int  iEventEndDate;
    int  iRewardStartDate;
    int  iRewardEndDate;
    bool bIsActivated;
    
    DangerRoomActivatedData()
    {
        iEventStartDate = 0;
        iEventEndDate = 0;
        iRewardStartDate = 0;
        iRewardEndDate = 0;
        bIsActivated = true;
    }
};

//-----------------------------------------------

struct NoticeContentData
{
    std::string sTitleBackGroundImage;
    std::string sTitleTextContent;
    std::string sNoticeTextContent;
    bool        bIsActivated;
    
    NoticeContentData()
    {
        sTitleBackGroundImage = "";
        sTitleTextContent = "";
        sNoticeTextContent = "";
        bIsActivated = true;
    }
};

//-----------------------------------------------

enum EBarkType
{
    eBarkType_RandOneContent = 1,
    eBarkType_ListContent,
    eBarkType_Loop,
    eBarkType_Count
};

struct BarkPropertyData
{
    std::string sColorType;
    int iDisplayCount;
    float fScollSpeed;
    float fDelayTime;
    EBarkType eType;
    
    BarkPropertyData()
    {
        sColorType = "";
        iDisplayCount = 0;
        fScollSpeed = 0;
        fDelayTime = 0;
        eType = eBarkType_Count;
    }
};

struct ScrollBarBarkData
{
    bool bIsActivated;
    BarkPropertyData strBarkProperty;
    std::vector<std::string> BarkTextContent;
    
    ScrollBarBarkData()
    {
        bIsActivated = true;
        BarkTextContent.clear();
    }
};

//-----------------------------------------------

struct TipsPropertyData
{
    int iBaseIndex;
    std::string sColorType;
    
    TipsPropertyData()
    {
        iBaseIndex = 0;
        sColorType = "";
    }
};

struct TipsData
{
    bool bIsActivated;
    TipsPropertyData strTipsProperty;
    std::vector<std::string> TipsContent;
    std::vector<std::string> TipsImage;
    
    TipsData()
    {
        bIsActivated = true;
        TipsContent.clear();
        TipsImage.clear();
    }
};

//-----------------------------------------------

struct GeneralSaleProp
{
    bool bFirstAward;
    int iDate;
    float fDiscount;
    std::string sSku;
    std::string sImage;
    
    GeneralSaleProp()
    {
        bFirstAward = false;
        sSku = "";
        sImage = "";
        fDiscount = 0.0f;
        iDate = 0;
    }
};

//-----------------------------------------------

struct DiscountPlant
{
    int DiscountDate;
    std::string PlantName;
    bool IsAvatar;
    int Discount;
    std::string DiscountImage;
    
    DiscountPlant()
    {
        DiscountDate = 0;
        PlantName = "";
        IsAvatar = false;
        Discount = 0;
        DiscountImage = "";
    }
};

//-----------------------------------------------

enum EArrayType
{
    eArrayType_Normal = 0,
    eArrayType_Few,
    eArrayType_Rare,
    eArrayType_Count,
};

struct SpecialGameLevelRefreshData
{
    PurchaseType eType;
    int          iPrice;
    
    SpecialGameLevelRefreshData()
    {
        eType = PURCHASE_GEM;
        iPrice = 0;
    }
};

struct PlantNameArray
{
    FestivalGameLevel eModeLevel;
    int iPlantCount;
    int iNormalWeight;
    int iFewWeight;
    int iRareWeight;
    std::vector<std::string> ArrayNormal;
    std::vector<std::string> ArrayFew;
    std::vector<std::string> ArrayRare;
    
    PlantNameArray()
    {
        eModeLevel = FestivalGameLevel_Count;
        iPlantCount = 0;
        iNormalWeight = 0;
        iFewWeight = 0;
        iRareWeight = 0;
        ArrayNormal.clear();
        ArrayFew.clear();
        ArrayRare.clear();
    }
};

struct SpecialGameLevelGroup
{
    FestivalGameMode eGameMode;
    bool bIsAvatar;
    std::vector<PlantNameArray> plantNameArray;
    
    SpecialGameLevelGroup()
    {
        eGameMode = FestivalGameMode_None;
        bIsAvatar = false;
    }
};

//-----------------------------------------------

struct WeeklyGameModesCount
{
    FestivalGameMode eModeType;
    int             iCount;
    
    WeeklyGameModesCount()
    {
        eModeType = FestivalGameMode_None;
        iCount = 0;
    }
};

//-----------------------------------------------

struct PieceDropData
{
    std::string sPieceName;
    std::vector<float> PercentNormalArray;
    std::vector<float> PercentHardArray;
    std::vector<float> PercentLegendArray;
    
    int  iActicityCombat;
    int  iStartDate;
    int  iEndDate;
    int  iStartTime;
    int  iEndTime;
    
    PieceDropData()
    {
        sPieceName = "";
        PercentNormalArray.clear();
        PercentHardArray.clear();
        PercentLegendArray.clear();
        iActicityCombat = 1;
        iStartDate = 0;
        iEndDate = 0;
        iStartTime = 0;
        iEndTime = 0;
    }
};

//-----------------------------------------------

struct StorePlantGiftsActivatedData
{
    int  iStartDate;
    int  iEndDate;
    bool bIsActivated;
    
    StorePlantGiftsActivatedData()
    {
        iStartDate = 0;
        iEndDate = 0;
        bIsActivated = true;
    }
};

struct LevelGem
{
    int     iLevel;
    float   fDiscount;
    std::string sDiscoutImage;
    
    LevelGem()
    {
        iLevel      = 0;
        fDiscount   = 0.0f;
        sDiscoutImage = "";
    }
};

struct PlantGiftData
{
    std::string sSku;
    std::string sPlantName;
    std::string sImage;
    int actid;
    int TimeIndex;
    
    std::vector<LevelGem> ExpensesData;
    
    PlantGiftData()
    {
        sSku = "";
        sPlantName = "";
        sImage = "";
        actid = 0;
        TimeIndex = 0;
        ExpensesData.clear();
    }
};

//-----------------------------------------------

struct ActivityRechargePlantPieceData
{
    bool bValid;
    std::string sTextContent;
    std::string sImage;
    std::string sPlantName;
    int iPieceCount;
    
    ActivityRechargePlantPieceData()
    {
        bValid = false;
        sTextContent = "";
        sImage = "";
        sPlantName = "";
        iPieceCount = 0;
    }
};

//-----------------------------------------------

struct WorldMapActivityPieceLevelData
{
    std::string sLevelName;
    bool bValid;
    
    WorldMapActivityPieceLevelData()
    {
        sLevelName = "";
        bValid = false;
    }
};
//-----------------------------------------------

struct SpringBossActivatedData
{
    int  iEventStartDate;
    int  iEventEndDate;
    int  iMaxTimesPerDay;
    int  iRate;
    
    
    std::vector<RtWeakPtr<const ZombieType> >    veczombiesType;
    std::vector<std::string> veclevelName;
    
    SpringBossActivatedData()
    {
        iEventStartDate = 0;
        iEventEndDate = 0;
        iMaxTimesPerDay = 0;
        iRate = 0;
    }
};

//-----------------------------------------------

//-----------------------------------------------

struct SSpringRewardInfo
{
    RtWeakPtr<const PlantType>  plantType;
    int gem;
};

struct SpringGiftActivatedData
{
    int  iEventStartDate;
    int  iEventEndDate;
    int  iAndroidCost;
    int  iIosCost;
    
    std::vector<SSpringRewardInfo>    vecrewards;
    
    SpringGiftActivatedData()
    {
        iEventStartDate = 0;
        iEventEndDate = 0;
        iAndroidCost = 0;
        iIosCost = 0;
    }
};

struct GoldenEggProbility
{
    int quantity;
    int probility;
    bool refresh;
    
    GoldenEggProbility()
    {
        quantity = 0;
        probility = 0;
        refresh = false;
    }
};

struct GoldenEggData
{
    int eventStartDate;
    int eventEndDate;
    int rewardRequstRMB;
    int rewardHammerQuantity;
    int HammerStorageMax;
    int dailyHammerMax;
    int eggOpenGemCost;
    
    std::vector<int> vecGoldenEggBonus;
    std::vector<GoldenEggProbility> vecProbilityList;
    
    GoldenEggData()
    {
        eventStartDate = 0;
        eventEndDate = 0;
        rewardRequstRMB = 0;
        rewardHammerQuantity = 0;
        HammerStorageMax = 0;
        dailyHammerMax = 0;
        eggOpenGemCost = 0;
        
        vecGoldenEggBonus.clear();
        vecProbilityList.clear();
    }
};

struct ChristmasProtectData
{
    int eventStartDate;
    int eventEndDate;
    int maxPlayCount;
    std::vector<GachaRewardItem> christmasTreeRewardList;
    
    ChristmasProtectData()
    {
        eventStartDate = 0;
        eventEndDate   = 0;
        maxPlayCount   = 3;
        
        christmasTreeRewardList.clear();
    }
};

struct ChristmasLotteryData
{
    int eventStartDate;
    int eventEndDate;
    int christmasLotteryCost;
    int christmasLotterySpecialChanceCommon;
    
    std::vector<int>             christmasLotterySpecialChance;
    std::vector<GachaRewardItem> christmasGachaRewardList;
    std::vector<GachaRewardItem> christmasGachaRewardSpecial;
    
    ChristmasLotteryData()
    {
        eventStartDate = 0;
        eventEndDate   = 0;
        christmasLotteryCost = 99;
        christmasLotterySpecialChanceCommon = 5;
        
        christmasLotterySpecialChance.clear();
        christmasGachaRewardList.clear();
        christmasGachaRewardSpecial.clear();
    }
};

struct ChristmasAccessoryBonus
{
    int index;
    int objectId;
    int quantity;
    int probility;
    
    ChristmasAccessoryBonus ()
    {
        index = 0;
        objectId = 0;
        quantity = 0;
        probility = 0;
    }
};

struct ChristmasAccessoryData
{
    int eventStartDate;
    int eventEndDate;
    int coinsPrice;
    int gemsPrice;
    int freeMaxTime;
    int coinMaxTime;
    int gemMaxTime;
    
    std::vector<ChristmasAccessoryBonus> vecFreeIds;
    std::vector<ChristmasAccessoryBonus> vecCoinIds;
    std::vector<ChristmasAccessoryBonus> vecGemIds;
    
    ChristmasAccessoryData()
    {
        eventStartDate = 0;
        eventEndDate = 0;
        coinsPrice = 0;
        gemsPrice = 0;
        freeMaxTime = 0;
        coinMaxTime = 0;
        gemMaxTime = 0;
    }
};

struct BossLevel
{
    std::string WorldName;
    std::string LevelName;
    
    BossLevel()
    {
        WorldName = "";
        LevelName = "";
    }
};

struct BossFightBonus
{
    std::string bonus;
    int         pieceMin;
    int         pieceMax;
    
    BossFightBonus()
    {
        bonus = "";
        pieceMin = 0;
        pieceMax = 0;
    }
};

struct BossFightActivateData
{
    int EventStartDate;
    int EventEndDate;
    std::vector<BossLevel>      BossLevels;
    std::vector<BossFightBonus> BonusAccessories;
    
    BossFightActivateData()
    {
        EventStartDate = 0;
        EventEndDate = 0;
    }
};

struct CommonActivateData
{
    int EventStartDate;
    int EventEndDate;
    
    CommonActivateData()
    {
        EventStartDate = 0;
        EventEndDate = 0;
    }
};

//-----------------------------------------------


class ActivityConfig : public Sexy::RtObject
{
public:
    
	RT_CLASS_DEFINE(ActivityConfig, Sexy::RtObject, Sexy::RtClass);
    
    bool IsDayFirstRewardActDays();
    bool IsActivityDays();
    bool IsActivityCentreDays();
    bool IsActivityNoticeOnce();
    
    bool HaveGameModeToday(FestivalGameMode i_mode);
    bool IsPlantOnSale(std::string& plantName);
	bool IsAvatarOnSale(std::string& plantAvatarName);
    bool IsGeneralSale(std::string& Sku);
    bool IsGeneralSaleOnDay(std::string& Sku);
    bool IsStoreGiftsActivated();
    bool IsDailyAchievementActivated();    
    bool IsRedPacksEntryActivated();
    bool IsDangerRoomActivated(bool i_checkReward);
    bool IsLanternRiddlesActivated();
    bool HasLanternRiddlesStarted();
    bool IsRedPackActivated();
    bool HasRedPackStarted();
    bool IsSpringBossActivated();
    bool IsSpringGiftActivated();
	bool IsSpringGiftActivatedAtTime(const tm i_time);
    
    bool IsChristmasAccessoryActived();
    int RollChristmasAccessoryIndex(int i_type);
    ChristmasAccessoryBonus GetChristmasAccessoryIdByIndex(int i_type, int i_index);
    int GetChristmasAccessoryMaxChances(int i_type);
    int GetChristmasAccessoryPrice(int i_type);
    
    bool IsGoldenEggActived();
    int GetGoldenEggRewardRequstRMB();
    int GetGoldenEggRewardHammerQuantity();
    int GetGoldenEggDailyHammerMax();
    int GetGoldenEggHammerStorageMax();
    int GetGoldenEggEggOpenGemCost();
    GoldenEggProbility RollGoldenEggPieceCount();
    std::vector<int> GetGoldenEggList();
    
    time_t DateMKTime(int i_Date);
    
    bool IsTwoYearActivated();
    
    int GetBossFightConfigLevelsCount();
    bool IsBossFightActivated();
    bool IsBossFightActivatedAtTime(const tm i_time);
    std::vector<BossLevel>& GetAllBossLevelInfo();
    BossLevel GetBossLevelInfoByIndex(int i_index);
    int GetBossFightBonusCount();
    std::string GetBossFightBonusSkuID(int i_index);
    int GetBossFightBonusPieceCount(int i_index);
    
    bool IsPlantBonusActivated();
    bool IsAvatarBonusActivated();
    
    std::string GetPlantImageOnSale(std::string& plantName);
    std::string GetAvatarImageOnSale(std::string& plantAvatarName);
    std::string GetGeneralSale(std::string& Sku);
    bool IsGeneralSaleFirstAward(std::string& Sku);
    
    float GetGeneralSaleDiscountOnDay(std::string& Sku);
    int GetRemainTime(FestivalGameMode i_mode);
	int GetActivityPrice(std::string& productName, bool bAvatar, int iPrice);
    int GetWeeklyGameModeCount(FestivalGameMode eType) const;
    
    Sexy::Color::PredefinedColor GetActivityTextColor(std::string sColor) const;
    
    void GetTodayDiscountPlant(DiscountPlant &i_discountPlant);
    SexyString GetTodayDiscountPlantName();
    
    //New Const Functions for protecting datas
    bool IsNoticeBoardActivated() const { return m_strNoticeContent.bIsActivated; }
    const NoticeContentData & GetNoticeContentData() { return m_strNoticeContent; }
    
    bool IsScrollBarBarkActivated() const { return m_strScrollBarBark.bIsActivated; }
    const ScrollBarBarkData & GetScrollBarBarData() { return m_strScrollBarBark; }
    int GetScrollBarBarkContentIndex();
    
    bool IsTipsActivated() const { return m_strTips.bIsActivated; }
    const TipsData & GetTipsData() { return m_strTips; }
    Image * GetTipsImage();
    
    bool IsFirstRechargeAward();
    bool IsAutoSunCollect() const { return m_bAutoSunCollect; }
    bool IsDoubleCoin() const { return m_bDoubleCoin; }
    
    int GetFirstRechargeAwardMultiple() const { return m_iFirstRechargeAwardMultiple; }
    
    std::vector<float> GetCurrentPieceDropPercentArray(const std::string & sPieceName, FestivalGameLevel eLevel) const;
    int GetCurrentPieceDropActivityCombat(const std::string & sPieceName) const;
    
    std::string GetActivityStoreBannerImageS() const { return m_sActivityStoreBannerImage; }

    std::string GetActivityTopic() const { return m_sActivityTopic; }
    int GetMaxCoinSpecialCollected() const;
    const MysteryCrystalDrop& GetMysteryCrystalDropData() { return m_mysteryCrystalDropData; }
    int GetCukePackageAddCount() const { return m_cukePackageAddCount; }
    FestivalGameMode GetCurrentPlantPieceComeFrom(const std::string & sPlantPiece, bool IsAvatar = false);
    
    const SpecialGameLevelRefreshData & GetRefreshPlantsPurchaseData() { return m_strRefreshData; }
    bool GetGetWeeklyGameModesPlantArray(FestivalGameMode eModeType, FestivalGameLevel eModeLevel, EArrayType eArrayType, std::vector<std::string>& Array);
    bool IsWeeklyGameModesPlantArrayAvatar(FestivalGameMode eModeType, bool & IsAvatar);
    int  GetGetWeeklyGameModesPlantCount(FestivalGameMode eModeType, FestivalGameLevel eModeLevel) const;
    float GetCurrentPlantListDrowWeight(FestivalGameMode eModeType, FestivalGameLevel eModeLevel, EArrayType eArrayType) const;
    
    bool IsStorePlantGiftsActivated();
    const StorePlantGiftsActivatedData & GetStorePlantGiftsActivatedData() { return m_strStorePlantGiftsActivatedData; }
    bool IsCurrStorePlantGiftActivated(std::string sku);
    //const StorePlantGiftsActivatedData & GetStorePlantGiftsActivatedData() { return m_strStorePlantGiftsActivatedData; }
    
    //-----functions of store gift --------------
    bool GetStorePlantGiftImageBySku(const std::string & sSku, std::string & sImage);
    
    float GetStorePlantGiftLevelDiscountBySku(const std::string & sSku, int iLevel) const;
    float GetStorePlantGiftLevelDiscountByPlantName(const std::string & sPlantName, int iLevel) const;
    
    int GetStorePlantGiftLevelActidByPlantName(const std::string& sPlantName);
    
    bool GetStorePlantGiftLevelDiscountImageSBySku(const std::string & sSku, int iLevel, std::string & sImageId);
    bool GetStorePlantGiftLevelDiscountImageSByPlantName(const std::string & sPlantName, int iLevel, std::string & sImageId);
    //-----functions of store gift --------------
    
    //-----function of checking world map activity level --------------
    bool IsCurrentWorldMapActivityLevelValid(const std::string & sLevelName);
    bool CheckCurrentLevelIsActivityLevel(const std::string & sLevelName) const;
    int  GetLeftActivityDays();
    //-----function of checking world map activity level --------------
    
    //-----functions of activity recharge plant pieces data--------------
    const ActivityRechargePlantPieceData & GetRechargePlantPieceData() { return m_strActivityRechargePlantPieceData; }
    bool IsRechargePlantPieceValid();
    const std::string & GetRechargePlantPieceTextContent() { return m_strActivityRechargePlantPieceData.sTextContent; }
    const std::string & GetRechargePiecePlantName() { return m_strActivityRechargePlantPieceData.sPlantName; }
    Image * GetRechargeImage();
    int GetRechargePlantPieceCount() const { return m_strActivityRechargePlantPieceData.iPieceCount; }
    //-----functions of activity recharge plant pieces data--------------
    
    const std::vector< std::vector<FestivalGameMode> >& GetWeeklyGameModes() { return WeeklyGameModes; }
    const std::vector<GeneralSaleProp>& GetGeneralSaleObjectList() { return GeneralSaleObjectList; }
    const std::vector<DiscountPlant>& GetDiscountPlantList() { return DiscountPlantList; }
    const std::vector<SpecialGameLevelGroup>& GetSpecialGameLevelGroupList() { return SpecialGameLevelGroupList; }
    const std::vector<WeeklyGameModesCount>& GetWeeklyGameModesCountList() { return WeeklyGameModesCountList; }
    const std::vector<PieceDropData>& GetPieceDropDataList() { return PieceDropDataList; }
    const std::vector<PlantGiftData>& GetPlantGiftDataList() { return PlantGiftDataList; }
    const std::vector<WorldMapActivityPieceLevelData>& GetWorldMapActivityPieceLevelList() { return WorldMapActivityPieceLevelList; }
    
    const DangerRoomActivatedData& GetDangerRoomActivatedData() { return m_strDangerRoomActivatedData; }
    const LanternRiddlesActivatedData& GetLanternRiddlesActivatedData() { return m_strLanternRiddlesActivatedData; }
    const RedPackActivedData& GetRedPackActivatedData() { return m_strRedPackActivatedData; }
    const SpringBossActivatedData& GetSpringBossActivatedData() { return m_stSpringBossActivatedData; }
    const SpringGiftActivatedData& GetSpringGiftActivatedData() { return m_stSpringGiftActivatedData; }
    const ChristmasAccessoryData& GetChristmasAccessoryData() { return m_stChristmasAccessoryData; }
    const GoldenEggData& GetGoldenEggData() { return m_stGoldenEggData; }
    const ChristmasProtectData& GetChristmasProtectData() { return m_stChristmasProtectData; }
    const ChristmasLotteryData& GetChristmasLotteryData() { return m_stChristmasLotteryData; }
    const BossFightActivateData& GetBossFightActivateData() { return m_stBossFightActivateData; }
    int  GetLeftDangerRoomDays(bool i_reward);
    bool IsTargetTimeInDangerRoomPeriod(time_t i_prevTime);
    
    //consumption reward
    
    std::string GetConsumptionValidTopic();
    
    bool IsAnyConsumptionTopicValid() { return !GetConsumptionValidTopic().empty(); }
    
    ActivityTimeStatus GetCurrentActivityTimeStatus(int iStartDate, int iEndDate);
    
private:
    
    //---------------------------------------------------------------------------------------
    //only this way can get Unicode string to show it right in game
    void GetNoticeContent(std::wstring & sNoticeContent);
    bool GetScrollBarBarTextContent(int nIndex, std::wstring & sScrollBarTextContent);
    bool GetTipsTextContent(int nIndex, std::wstring & sTipsTextContent);
    
    
    bool HasCurrentActivityTimeStarted(int iStartDate);
    
    bool IsCurrentActivityLocalTimeValid(int iStartDate, int iEndDate);
    bool HasCurrentActivityLocalTimeStarted(int iStartDate);
    
    //---------------------------------------------------------------------------------------
    
    //Specuial function just be used to translate from utf8 chinese string to unicode chinese string
    void UTF8ChStringToUnicodeChString(std::string & UTF8ChString, std::wstring & UnicodeChString);
    FestivalGameMode _GetCurrentPlantPieceComeFrom(const std::string & sPlantPiece, bool IsAvatar = false) const;
    
    int                             m_maxCoinSpecialCollected = 0;
    int                             m_cukePackageAddCount = 5;
    MysteryCrystalDrop				m_mysteryCrystalDropData;
    std::string                     m_sActivityTopic;
    
    ActivityDateData                ActivityDate;
    ActivityDateData                ActivityCentreDate;
	ActivityDateData                m_stDayFirstPayRewardData;
    ActivityDateData                m_stTwoYearData;
    NoticeContentData               m_strNoticeContent;
    ScrollBarBarkData               m_strScrollBarBark;
    TipsData                        m_strTips;
    DailyAchievementActivatedData   m_strDailyAchievementActivatedData;
    StoreGiftsActivatedData         m_strStoreGiftsActivatedData;
    DangerRoomActivatedData         m_strDangerRoomActivatedData;
    SpringBossActivatedData         m_stSpringBossActivatedData;
    SpringGiftActivatedData         m_stSpringGiftActivatedData;
    ChristmasAccessoryData          m_stChristmasAccessoryData;
    GoldenEggData                   m_stGoldenEggData;
    ChristmasProtectData            m_stChristmasProtectData;
    ChristmasLotteryData            m_stChristmasLotteryData;
    BossFightActivateData           m_stBossFightActivateData;
    CommonActivateData              m_stPlantBonusActivateData;
    CommonActivateData              m_stAvatarBonusActivateData;
    SpecialGameLevelRefreshData     m_strRefreshData;
    StorePlantGiftsActivatedData    m_strStorePlantGiftsActivatedData;
    std::vector<StorePlantGiftsActivatedData>    m_strStorePlantGiftsActivatedDataList;
    LanternRiddlesActivatedData     m_strLanternRiddlesActivatedData;
    RedPackActivedData              m_strRedPackActivatedData;
    RedPackClosedData               m_strRedPackClosedData;
    ActivityRechargePlantPieceData  m_strActivityRechargePlantPieceData;
    ConsumptionActivedData          m_stConsumptionActivedData;
    
    std::string                     m_sActivityStoreBannerImage;
    
    bool m_bFirstRechargeAward = false;
    bool m_bAutoSunCollect = false;
    bool m_bDoubleCoin = false;
    
    int  m_iFirstRechargeAwardMultiple = 0;

    std::vector< std::vector<FestivalGameMode> > WeeklyGameModes;
    std::vector<GeneralSaleProp> GeneralSaleObjectList;
    std::vector<DiscountPlant> DiscountPlantList;
    std::vector<SpecialGameLevelGroup>  SpecialGameLevelGroupList;
    std::vector<WeeklyGameModesCount> WeeklyGameModesCountList;
    std::vector<PieceDropData> PieceDropDataList;
    std::vector<PlantGiftData> PlantGiftDataList;
    std::vector<WorldMapActivityPieceLevelData>   WorldMapActivityPieceLevelList;
};

#endif /* defined(__PlantsVersusZombies2__ActivityConfig__) */
