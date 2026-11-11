//
//  SuperSonicAdProviderIOS.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 5/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SuperSonicAdProviderIOS__
#define __PlantsVersusZombies2__SuperSonicAdProviderIOS__

#include "AdProvider.h"
#include "Singleton.h"
#import "Supersonic/Supersonic.h"
#import "Supersonic/SupersonicLOGDelegate.h"
#import "Supersonic/SupersonicRVDelegate.h"
#import "UIKit/UIKit.h"

@interface SuperSonicLOGDelegateImp : NSObject<SupersonicLogDelegate>
@end

@interface SuperSonicRVDelegateImp : NSObject<SupersonicRVDelegate>
{
	Delegate2<bool, int> mSetAdsAvailable;
	Delegate2<int, int> mAwardCoins;
	Delegate0 mOnClose;
}

- (id)initWithSetAdsAvailableCallback:(Delegate2<bool, int>&)setAdsAvailableCallback
				   awardCoinsCallback:(Delegate2<int, int>&)awardCoinsCallback
					  onCloseCallback:(Delegate0&)onCloseCallback;
@end

class SuperSonicAdProviderIOS : public AdProvider, public LazySingleton<SuperSonicAdProviderIOS>
{
public:
	SuperSonicAdProviderIOS();
	~SuperSonicAdProviderIOS();
	void Initialize(const std::string& i_obfuscatedUserId) override;
	bool HasAdvertisements() const override;
protected:
	void doShowAdvertisements() override;
	
private:
	Supersonic*					mSupersonic;
	SuperSonicLOGDelegateImp*	mLoggingDelegate;
	SuperSonicRVDelegateImp*	mDelegate;
};

#endif /* defined(__PlantsVersusZombies2__SuperSonicAdProviderIOS__) */
