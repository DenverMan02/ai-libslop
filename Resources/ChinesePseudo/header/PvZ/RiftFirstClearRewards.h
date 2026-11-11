//
//  RiftFirstClearRewards.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 10/28/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef RiftFirstClearRewards_h
#define RiftFirstClearRewards_h

#include "LevelOfTheDay_RewardData.h"
#include "PropertySheetBase.h"

class RiftFirstClearRewardsDefinition
{
public:
	RiftFirstClearRewardsDefinition()
	{
		
	}
	
	std::vector<LevelOfTheDay_RewardItemType> FirstClearRewards; //Index by difficulty number
};

class RiftFirstClearRewards : PropertySheetBase
{
	RT_CLASS_DEFINE(RiftFirstClearRewards, PropertySheetBase, RtClass);
	
	RiftFirstClearRewards()
	{
		
	}
	
	std::vector<RiftFirstClearRewardsDefinition> LevelClearRewards;
	RiftFirstClearRewardsDefinition DefaultLevelClearRewards;
	
	static RiftFirstClearRewards* GetFirstClearRewards(const std::string &i_rewardKey);
};

#endif /* RiftFirstClearRewards_h */
