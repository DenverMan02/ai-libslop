//
//  UltraIOS.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UltraIOS__
#define __PlantsVersusZombies2__UltraIOS__

#include "Ultra.h"
#include "Singleton.h"
#import "../PvZ2/extern/Ultra/UltraSDK.framework/Headers/UltraManager.h"

@interface UltraDelegate : NSObject <UltraManagerProtocol> {
	Delegate0wRet<bool> mSupersonicHasAds;
	Delegate0 mShowSupersonic;
	UltraManager* mManager;
}
- (void)SetManager:(UltraManager*)i_manager;
- (void) SetSupersonicCallback:(Delegate0wRet<bool>)i_supersonicHasAds showDelegate:(Delegate0)i_showSupersonic;

@end

class UltraIOS : public Ultra, public LazySingleton<UltraIOS>
{
public:
	UltraIOS();
	~UltraIOS();
	void Show() override;
protected:
	void onInitialize(const std::string& i_obfuscatedUserId) override;
private:
	UltraManager* mManager;
	UltraDelegate* mDelegate;
};

#endif /* defined(__PlantsVersusZombies2__UltraIOS__) */
