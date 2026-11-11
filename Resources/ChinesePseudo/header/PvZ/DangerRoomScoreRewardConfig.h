//
//  DangerRoomScoreRewardConfig.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomScoreRewardConfig__
#define __PlantsVersusZombies2__DangerRoomScoreRewardConfig__

#include "PropertySheetBase.h"

enum DangerRoomPrizeType
{
    DRPT_COINS_REWARD = 0,
    DRPT_GEMS_REWARD,
    DRPT_KEY_REWARD,
    DRPT_PLANT_REWARD,
    DRPT_AVATAR_REWARD,
    DRPT_PLANT_PIECE_REWARD,
    DRPT_AVATAR_PIECE_REWARD,
    DRPT_ACCESSORY_REWARD,
    DRPT_ACCESSORY_PIECE_REWARD,
    DRPT_COUNT,
};

struct DangerRoomRewardData
{
    std::string rewardItem;
    DangerRoomPrizeType rewardType;
    int rewardAmount;
};

struct ScoreItem
{
    ScoreItem()
    {
        Score = 0;
    }
    
    int                          Score;
#ifdef HOST_ANDROID
    std::vector<DailyRewardData> ScoreRewardList;
#else
    std::vector<DangerRoomRewardData> ScoreRewardList;
#endif
};

class DangerRoomScoreRewardConfig : public PropertySheetBase
{
public:
    
	RT_CLASS_DEFINE(DangerRoomScoreRewardConfig, PropertySheetBase, RtClass);
    
    static const DangerRoomScoreRewardConfig& Get();
    
    static bool  CanGetDangerRoomScoreReward(int i_score);
    
    int                    Version;
    std::vector<ScoreItem> ScoreList;
};

#endif /* defined(__PlantsVersusZombies2__DangerRoomScoreRewardConfig__) */
