//
//  RiftZombossRewards.h
//  PlantsVersusZombies2Framework
//
//  Created by Jason Emery on 9/17/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef RiftZombossRewards_h
#define RiftZombossRewards_h

#include "LevelOfTheDay_RewardData.h"
#include "PropertySheetBase.h"

class RiftZombossRewardDifficultyEntry
{
public:
    RiftZombossRewardDifficultyEntry()
    {
    }
    
    std::vector<LevelOfTheDay_RewardItemType> Rewards;
    
    void Combine(const RiftZombossRewardDifficultyEntry* i_entry);
    void Combine(const LevelOfTheDay_RewardItemType& i_reward);
    const LevelOfTheDay_RewardItemType* Find(AwardType i_awardType, std::string i_awardParam) const;
};

class RiftZombossRewardDifficultySet
{
public:
	RiftZombossRewardDifficultySet()
	{
	}
	
    int Attempt;
    std::vector<RiftZombossRewardDifficultyEntry> DifficultyList;
};

class RiftZombossRewards : public PropertySheetBase
{
public:
	RiftZombossRewards()
	{
        PinataTypeForOpeningSequence = "free";
	}
    
    RT_CLASS_DEFINE(RiftZombossRewards, PropertySheetBase, RtClass);

    std::string PinataTypeForOpeningSequence;
    std::vector<RiftZombossRewardDifficultySet> ProgressionRewards;
    
	std::string ToString() const;
    
    static RiftZombossRewards* GetRewards(const std::string &i_rewardKey);
};

#endif
