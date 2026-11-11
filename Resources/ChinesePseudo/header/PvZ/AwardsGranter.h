//
//  AwardsGranter.h
//  PlantsVersusZombies2
//
//  Contains helper functions for dealing with awards in
//  order to break out game logic from dialogs / etc.
//
//  Created by Jason Emery on 9/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Awards__
#define __PlantsVersusZombies2__Awards__

#include <string>
#include <vector>

#include "AwardEnums.h"
#include "LevelOfTheDay_RewardData.h"
#include "PropertySheetBase.h"
#include "RtObject.h"

typedef struct _EpicQuestRewardInfo
{
	std::string uniqueID;
	std::string type;
	std::string subtype;
	int amount;
} EpicQuestRewardInfo;

namespace Message
{
	void AwardGiven(int i_context, const char* i_param, int i_count);
	void EpicQuestRewarded(const EpicQuestRewardInfo *info);
}

class AwardsGranter
{
public:
    
    static bool IsOwned(AwardType awardType, std::string awardParam, bool i_checkGlobalSaveToo);
    
    static void GiveAward(AwardType	i_awardType, std::string i_awardParam, int i_awardCount, AWARD_Context i_awardContext, bool i_applyToGlobalSaveDataToo);
    static void GiveAward(AwardType	i_awardType, std::string i_awardParam, int i_awardCount, AWARD_Context i_awardContext, bool i_applyToGlobalSaveDataToo, std::string i_metricsSource, std::string i_metricsSubtype);
	
	static const char* AwardTypeToString(AwardType i_awardType);

};

class AwardConfigPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(AwardConfigPropertySheet, PropertySheetBase, RtClass);
	
	AwardConfigPropertySheet()
	{}
	
	std::vector<LevelOfTheDay_RewardItemType> FacebookInviteRewards;
	std::vector<LevelOfTheDay_RewardItemType> GiftBoxRewards;
};
#endif
