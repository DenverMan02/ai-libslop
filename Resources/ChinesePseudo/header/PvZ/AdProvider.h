//
//  AdProvider.h
//  PlantsVersusZombies2
//
//  Created by Ross Baker on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_AdProvider_h
#define PlantsVersusZombies2_AdProvider_h

#include <string>
#include "RtDelegate.h"
#include "Singleton.h"

class AdProvider
{
public:
	virtual ~AdProvider() {}
	AdProvider();
	
	virtual void Initialize(const std::string& i_obfuscatedUserId) = 0;
	
	virtual bool HasAdvertisements() const;
	void ShowAdvertisements(const ::Sexy::Delegate2<int, int>& i_coinsAwardedCallback, const ::Sexy::Delegate0& i_onAdsClosedCallback = ::Sexy::Delegate0());
    int GetNumAdvertisementsAvailable() const;
    
protected:
	virtual void doShowAdvertisements() = 0;
	
	void awardRewards(int i_rewardQuantity, int i_videosWatched);
	void onClose();
	void setAdsAreAvailable(bool i_adsAreAvailable, int adInventory);
	
private:
	bool mAdsAreAvailable;
    int mInventoryCountAvailble;
	::Sexy::Delegate2<int, int> mCoinsAwardedCallback;
	::Sexy::Delegate0 mAdsClosedCallback;
};

class AdProviderNullImpl : public AdProvider, public LazySingleton<AdProviderNullImpl>
{
public:
	void Initialize(const std::string& i_obfuscatedUserId) override {}
protected:
	void doShowAdvertisements() override {}
};

#endif
