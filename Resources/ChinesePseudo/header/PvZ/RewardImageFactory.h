//
//  RewardImageFactory.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 9/18/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef RewardImageFactory_h
#define RewardImageFactory_h

#include "LevelOfTheDay_RewardData.h"

class RewardImageFactory
{
public:
	ImagePtr GetImageForReward(const LevelOfTheDay_RewardItemType& i_reward);
	ImagePtr GetImageForReward(AwardType i_awardType, const std::string& i_awardParam, int i_quantity, int i_id);
	ImagePtr GetImageForReward(AwardType i_awardType, int i_id);
	
	static const int k_GemsSmall = 2;
	static const int k_GemsMedium = 10;
};

#endif
