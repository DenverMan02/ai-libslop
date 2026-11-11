//
//  EASquared.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/11/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquared__
#define __PlantsVersusZombies2__EASquared__

#include "Singleton.h"
#include "TimeMgr.h"

class EASquaredPropertySheet;
class IPVZStoreProduct;
class Ultra;

namespace EASquaredAdFinishedReason
{
	enum EASquaredAdFinishedReason
	{
		Completed,
		Success,
		Clicked,
		Closed,
		Canceled
	};
}
namespace Sexy
{
    RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(EASquaredAdFinishedReason::EASquaredAdFinishedReason);
}

typedef Delegate1<EASquaredAdFinishedReason::EASquaredAdFinishedReason> EASquaredAdCompletedCallback;

enum ViewPositionType
{
	VIEW_POSITION_INIT = 1,
	VIEW_POSITION_PAUSE = 2,
	VIEW_POSITION_RESULT = 3,
	VIEW_POSITION_EXIT = 4,
	VIEW_POSITION_DOUBLE_COIN = 57,
	VIEW_POSITION_FREE_CHEST_GACHA = 58,
	//VIEW_POSITION_PLANT_ADVENTURE_SKIP = 59,
	VIEW_POSITION_BATTLE_START = 60,
	VIEW_POSITION_WORLD_SELECT = 61,
	VIEW_POSITION_BATTLE_STATEMENT = 62,
	VIEW_POSITION_CHALLENGE = 10903,
	VIEW_POSITION_DAILYSIGN = 10904,
	VIEW_POSITION_THEATERSHOP = 10905,
	VIEW_POSITION_DANGERROOM_SHOP_REFRESH = 10906,
	VIEW_POSITION_DANGERROOM_CHALLENGE_RESET = 10907,
	VIEW_POSITION_WORLDMAP_LOTTERY = 10908,
#ifdef HOST_ANDROID
	VIEW_POSITION_COIN = 64,
	VIEW_POSITION_GEM = 63,
	VIEW_POSITION_MYSTERY = 66,
	VIEW_POSITION_GACHA = 65,
	VIEW_POSITION_ZTICKET = 68,
	VIEW_POSITION_FUEL = 67,
	VIEW_POSITION_CUSTOM_LEVEL_MOWER = 71,
	VIEW_POSITION_CUSTOM_LEVEL_PLANTFOOD = 72,
	VIEW_POSITION_CUSTOM_LEVEL_SUN = 74,
	VIEW_POSITION_SUN = 76,
	VIEW_POSITION_JOUST_STORE = 77,
	VIEW_POSITION_RIFT_STORE = 78,
	VIEW_POSITION_DANGERROOM_STORE = 10906,
	VIEW_POSITION_PLANT_FAMILY = 79,
	VIEW_POSITION_DAILY_SIGN = 75,
	VIEW_POSITION_TRANSGENOSIS_PLANT = 80,
	VIEW_POSITION_TRANSGENOSIS_AVATAR = 81,
	VIEW_POSITION_MOWER = 82,
	VIEW_POSITION_FESTIVAL_MODE = 83,
	VIEW_POSITION_PLANT_ADVENTURE_SKIP = 84,
	VIEW_POSITION_PLANT_ADVENTURE_BONUS_COUNT = 85,
	VIEW_POSITION_PLANT_ADVENTURE_BONUS_REWARD = 86,
	VIEW_POSITION_WISH_REFRESH = 87,
	VIEW_POSITION_WISH_GARGANTUARCRISIS_BONUS_COUNT = 88,
	VIEW_POSITION_WISH_DEVILINVADE_BONUS_COUNT = 89,
	VIEW_POSITION_WISH_CRAZYYETI_BONUS_COUNT = 90
#else
	VIEW_POSITION_COIN = 5,
	VIEW_POSITION_GEM = 6,
	VIEW_POSITION_MYSTERY = 7,
	VIEW_POSITION_GACHA = 8,
	VIEW_POSITION_ZTICKET = 9,
	VIEW_POSITION_FUEL = 10,
	VIEW_POSITION_CUSTOM_LEVEL_MOWER = 11,
	VIEW_POSITION_CUSTOM_LEVEL_PLANTFOOD = 12,
	VIEW_POSITION_CUSTOM_LEVEL_SUN = 13,
	VIEW_POSITION_SUN = 14,
	VIEW_POSITION_JOUST_STORE = 15,
	VIEW_POSITION_RIFT_STORE = 16,
	VIEW_POSITION_DANGERROOM_STORE = 17,
	VIEW_POSITION_PLANT_FAMILY = 18,
	VIEW_POSITION_DAILY_SIGN = 19,
	VIEW_POSITION_TRANSGENOSIS_PLANT = 20,
	VIEW_POSITION_TRANSGENOSIS_AVATAR = 21,
	VIEW_POSITION_MOWER = 22,
	VIEW_POSITION_FESTIVAL_MODE = 23,
	VIEW_POSITION_PLANT_ADVENTURE_SKIP = 24,
	VIEW_POSITION_PLANT_ADVENTURE_BONUS_COUNT = 25,
	VIEW_POSITION_PLANT_ADVENTURE_BONUS_REWARD = 26,
	VIEW_POSITION_WISH_REFRESH = 27,
	VIEW_POSITION_WISH_GARGANTUARCRISIS_BONUS_COUNT = 28,
	VIEW_POSITION_WISH_DEVILINVADE_BONUS_COUNT = 29,
	VIEW_POSITION_WISH_CRAZYYETI_BONUS_COUNT = 30
#endif
};

enum ViewType
{
	VIEW_TYPE_SCREEN,
	VIEW_TYPE_MEDIA,
	VIEW_TYPE_BANNER,
	VIEW_TYPE_MEDIA_PARAM,
};

enum AdBannerType {
	BANNER_SELECT_LEVEL = 1,
	BANNER_BOARD_TOP = 2,
	BANNER_FIGHT_FINISH = 3,
	BANNER_H5_LEFT = 4,
	BANNER_H5_RIGHT = 5,
	BANNER_AD_BOX = 6,
	BANNER_AD_WORLD_SELECT = 61,
	BANNER_AD_BATTLE_STATEMENT = 62,
};

class EASquared
{
public:
	virtual ~EASquared() {}

	static EASquared& Instance();
	static EASquaredPropertySheet* GetProperties();

	virtual void Initialize(const std::string& i_userId) = 0;
	virtual void Update() = 0;
	virtual void OfferToShowAdvertisements(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback) = 0;
	virtual void ShowAdvertisement(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback, bool i_suppressRewardScreen, ViewType i_type, ViewPositionType i_viewPosition) = 0;
	virtual bool IsBannerLoaded(AdBannerType ad_id) = 0;
	virtual void ShowBanner(AdBannerType ad_id) = 0;
	virtual void CloseBanner(AdBannerType type) = 0;
    virtual void CancelAdvertisementCallback() = 0;
	virtual bool IsEnabledForUser() = 0;
    virtual bool HasAdsAvailable() = 0;
	virtual bool IsShowingAds() = 0;
	virtual bool IsAwardingAds() = 0;
    virtual const std::string GetUnavailableReason() const = 0;
    virtual int GetAdInventoryCount() const = 0;
	virtual bool PlayerHasTooManyCoins() const = 0;
	virtual bool PlayerInstalledRecently() const = 0;
	virtual bool PlayerInSelectedMonetizationGroup() const = 0;
	virtual bool PlayerMeetsMemoryRequirements() const = 0;
	virtual int GetMaxCoinBalance() const = 0;
	virtual int GetMinimumDaysSinceInstall() const = 0;
	virtual const std::string GetDesiredMonetizerType() const = 0;
	virtual bool IsMediaAvailable(ViewPositionType i_position) const = 0;
	virtual int GetActivityInfos(std::map<int, int>& i_infos) = 0;
	virtual void CheckActivityInfos() = 0;

protected:
	virtual void showAdvertisement(const EASquaredAdCompletedCallback &i_postFlowCallback, bool i_suppressRewardScreen) = 0;

};

class EASquaredImpl : public EASquared, public LazySingleton<EASquaredImpl>
{
public:
	static std::string GetObfuscatedUserId(const std::string& i_userId);

	EASquaredImpl();
	virtual ~EASquaredImpl();

	void Initialize(const std::string& i_userId) override;
	void Update() override;
	void OfferToShowAdvertisements(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback) override;
	void ShowAdvertisement(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback, bool i_suppressRewardScreen, ViewType i_type, ViewPositionType i_viewPosition) override;
	bool IsBannerLoaded(AdBannerType ad_id) override { return false; }
	void ShowBanner(AdBannerType ad_id) override {}
	void CloseBanner(AdBannerType type) override;
    void CancelAdvertisementCallback() override;
	bool IsEnabledForUser() override;
    bool HasAdsAvailable() override;
	bool IsShowingAds() override { return mEaSquaredAdShowing; }
	bool IsAwardingAds() override { return mAwardingAds; }
    const std::string GetUnavailableReason() const override;
    int GetAdInventoryCount() const override;
	bool PlayerHasTooManyCoins() const override;
	bool PlayerInstalledRecently() const override;
	bool PlayerInSelectedMonetizationGroup() const override;
	bool PlayerMeetsMemoryRequirements() const override;
	int GetMaxCoinBalance() const override;
	int GetMinimumDaysSinceInstall() const override;
	const std::string GetDesiredMonetizerType() const override;
	bool IsMediaAvailable(ViewPositionType i_position) const override;
	int GetActivityInfos(std::map<int, int>& i_infos) override;
	void CheckActivityInfos() override;

protected:
	void showAdvertisement(const EASquaredAdCompletedCallback &i_postFlowCallback, bool i_suppressRewardScreen) override;
	
private:
	void showNoAdsAvailableDialog();
	void onItemPurchasedFromStore(class MagentoProductProps* i_props);
	void onCancelButtonPress();
	void onShowButtonPress();
	void addNumRewardsReceived(int i_numRewardsReceived, int i_videosWatched);
	void onAdvertisementsClosed();
	void onFlowEnded(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
	
	bool isAdReadyForFinalization() const;
	void doAdFinalize();
	
	void clearAndLogBasicInfo();
	void clearAndLogEndOfFlow(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
	
	pvztime_t mAdClosedDelayUntilTime;
	std::string mPlacementOrigin;
	bool mIsInitialized;
	bool mShowAdNextFrame;
	Ultra& mUltra;
	int mNumberOfRewardsToBeGrantedAfterAds;
	int mVideosWatched;
	EASquaredAdCompletedCallback mPostFlowCallback;
	bool mSuppressRewardScreen;
	bool mEaSquaredAdShowing;
	bool mAwardingAds;
};

class EASquaredNullImpl : public EASquared, public LazySingleton<EASquaredNullImpl>
{
public:
	void Initialize(const std::string& i_userId) override {}
	void Update() override {}
	void OfferToShowAdvertisements(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback) override {}
	void ShowAdvertisement(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback, bool i_suppressRewardScreen, ViewType i_type, ViewPositionType i_viewPosition) override {}
	bool IsBannerLoaded(AdBannerType ad_id) override { return false; }
	void ShowBanner(AdBannerType ad_id) override {}
	void CloseBanner(AdBannerType type) override {}
    void CancelAdvertisementCallback() override {}
	bool IsEnabledForUser() override { return false; }
    bool HasAdsAvailable() override { return false; }
	bool IsShowingAds() override { return false; }
	bool IsAwardingAds() override { return false; }
    const std::string GetUnavailableReason() const override { return "NullImpl"; }
    int GetAdInventoryCount() const override { return 0; }
	bool PlayerHasTooManyCoins() const override {return true; }
	bool PlayerInstalledRecently() const override {return true;}
	bool PlayerInSelectedMonetizationGroup() const override {return false;}
	bool PlayerMeetsMemoryRequirements() const override { return true; }
	int GetMaxCoinBalance() const override {return 0;}
	int GetMinimumDaysSinceInstall() const override {return 0;}
	const std::string GetDesiredMonetizerType() const override {return "none"; }
	bool IsMediaAvailable(ViewPositionType i_position) const override { return false; }
	int GetActivityInfos(std::map<int, int>& i_infos) override {return 0;}
	void CheckActivityInfos() override {}
	
protected:
	void showAdvertisement(const EASquaredAdCompletedCallback &i_postFlowCallback, bool i_suppressRewardScreen) override {}
};

#endif /* defined(__PlantsVersusZombies2__EASquared__) */
