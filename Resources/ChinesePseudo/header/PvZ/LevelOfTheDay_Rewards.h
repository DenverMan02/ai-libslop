//
//  LevelOfTheDay_Rewards.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelOfTheDay_Rewards__
#define __PlantsVersusZombies2__LevelOfTheDay_Rewards__

#include <string>
#include <vector>
#include "LevelOfTheDayConfigInfo.h"
#include "StandaloneEffectFactory.h"

class PlayerInfo;
class StandaloneEffect;


typedef std::vector<const TheDayRewardItem*> RewardSet;
class LevelOfTheDay_Rewards
{
public:

    static const TheDayRewardItem* Pick_RandomReward(RewardSet& rewards);
	
	static StandaloneEffect* CreateStandaloneEffectForReward(StandaloneEffectFactory& i_effectFactory, const TheDayRewardItem* i_reward);
	
	static class Effect_FloatingText* CreateFloatingRewardText(const TheDayRewardItem* i_reward, SexyVector2 i_position);
	
private:
	
    typedef std::vector<const TheDayRewardItem*>::iterator RewardSetIterator;
};

void AddRewardsToRewardSet(const std::vector<TheDayRewardItem>& i_rewardList, const std::string& i_category, int i_queryFlags, int i_param, RewardSet& o_rewardSet);
#endif /* defined(__PlantsVersusZombies2__LevelOfTheDay_Rewards__) */
