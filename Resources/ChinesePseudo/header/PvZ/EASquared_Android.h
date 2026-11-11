/*
 * EASquared_Android.h
 *
 *  Created on: 2016-11-9
 *      Author: jianglc
 */

#ifndef EASQUARED_ANDROID_H_
#define EASQUARED_ANDROID_H_

#include "EASquared.h"
#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"

class EASquared_Android : public EASquared, public LazySingleton<EASquared_Android>, public JavaBound< EASquared_Android > {
public:
	enum AdType {
		AD_SCREEN_VIEW = 0,
		AD_MEDIA
	};

	enum AdResultCode {
		AD_RESULT_SUCCESS = 0,
		AD_RESULT_FAILED,
		AD_RESULT_CLOSED,
		AD_RESULT_CLICKED,
		AD_RESULT_FINISHED
	};

	EASquared_Android();
	virtual ~EASquared_Android();

	void Initialize(const std::string& i_userId) override;
	void ShowAdvertisement(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback, bool i_suppressRewardScreen, ViewType i_type, ViewPositionType i_viewPosition) override;
	bool IsBannerLoaded(AdBannerType ad_id) override;
	void ShowBanner(AdBannerType ad_id) override;
	void CloseBanner(AdBannerType type) override;
	static void WatchAdHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jint type, jint resultCode );
	static void BannerLoad( JNIEnv* env, jobject javaObject, bool success, jint ad_id);

	void Update() override {}
	void OfferToShowAdvertisements(const std::string& i_placementOrigin, const EASquaredAdCompletedCallback& i_postFlowCallback) override {}
	void CancelAdvertisementCallback() override {}
	bool IsEnabledForUser() override { return false; }
	bool HasAdsAvailable() override;
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
	bool IsMediaAvailable(ViewPositionType i_position) const override;
	int GetActivityInfos(std::map<int, int>& i_infos) override;
	void CheckActivityInfos() override;

protected:
	void showAdvertisement(const EASquaredAdCompletedCallback &i_postFlowCallback, bool i_suppressRewardScreen) override {}

private:
	virtual void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
	virtual void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );

	static void onFlowEnded(EASquared_Android* i_self, AdType i_type, AdResultCode i_result);
	void finalizeResult(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);

	bool CheckCustomBanner(AdBannerType id);

	static JavaMethod<void>	JavaInitializeSDK;
	static JavaMethod<void>	JavaShowScreenView;
	static JavaMethod<void> JavaShowMedia;
	static JavaMethod<void> JavaShowMediaParam;
	static JavaMethod<void>	JavaLoadBanner;
	static JavaMethod<void>	JavaShowBanner;
	static JavaMethod<void>	JavaShowCustomBanner;
	static JavaMethod<void>	JavaCloseBanner;
	static JavaMethod<jboolean>	JavaIsMediaAvailable;
	static JavaMethod<jint> JavaGetActivityInfos;
	static JavaMethod<void> JavaCheckActivityInfos;


	EASquaredAdCompletedCallback mPostFlowCallback;
	bool mIsInitialized;

	static std::map<AdBannerType, bool> mBannerLoaded;
};


#endif /* EASQUARED_ANDROID_H_ */
