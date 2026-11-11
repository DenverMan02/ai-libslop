//
//  LevelOfTheDay_RewardData.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelOfTheDay_RewardData__
#define __PlantsVersusZombies2__LevelOfTheDay_RewardData__

#include <string>

#include "AwardEnums.h"
#include "ObjectTypeDescriptor.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyString.h"

typedef RtWeakPtr<class LevelOfTheDay_RewardItemType> LevelOfTheDay_RewardItemTypePtr;

// TODO: Now used by more than LOD. Rename!
class LevelOfTheDay_RewardItemType : public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(LevelOfTheDay_RewardItemType, ObjectTypeDescriptor, RtClass);
    
    LevelOfTheDay_RewardItemType()
    {
        Award = AWARD_None;
        AwardParam = "";
        SubObject = "";
        AwardQuantity = 0;
        Probability = 0;
        Category = "";
        AwardId = 0;
    }
    
    AwardType   Award;
    std::string AwardParam;
    std::string SubObject;
    int AwardQuantity;
    int Probability;
    std::string Category;		// TODO -- Why is this a string? It should be an enum.
    int AwardId;
    
    SexyString GetDisplayText() const;
    bool IsCommonReward() const;
    const char* ToString() const;
    
    std::string GetAwardSoundForCategory() const;
};

#endif /* defined(__PlantsVersusZombies2__LevelOfTheDay_RewardData__) */
