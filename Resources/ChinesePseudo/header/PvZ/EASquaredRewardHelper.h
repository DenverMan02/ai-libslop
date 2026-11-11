//
//  EASquaredRewardHelper.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 7/30/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredRewardHelper__
#define __PlantsVersusZombies2__EASquaredRewardHelper__

#include "AwardsGranter.h"
#include "EASquared.h"
#include "PVZ2UIAwardScreen.h"
#include "Toggles.h"

class EASquaredRewardHelper
{
public:
	static const int kNormalNumCoinsToRewardForAd = 250;
	static const int kBoostedNumCoinsToRewardForAd = 500;
	
	static void ShowCoinRewardsForAdCompletion(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason, int i_rewardQuantity);
	
private:
	static void onCoinAwardScreenDismissed();
	static int sm_numCoinsToRewardForCompletion;
	static PVZ2UIAwardScreen* m_awardScreen;
};

#endif /* defined(__PlantsVersusZombies2__EASquaredRewardHelper__) */
