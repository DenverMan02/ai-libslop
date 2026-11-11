//
//  TrainingType.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.29
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __TrainingType_H__
#define __TrainingType_H__

#include <set>
#include <string>

#include "RtDb.h"
#include "RtObject.h"
#include "ObjectTypeDirectory.h"
#include "ObjectTypeDescriptor.h"
#include "LawnAppEnums.h"

//-----------------------------------------------------------------------------
enum enumTrainingObjectType
{
    Training_Zombie,
    Training_Plant,
};

//-----------------------------------------------------------------------------
class TrainingType: public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(TrainingType, ObjectTypeDescriptor, RtClass);
    
    TrainingType();
    
    ObjectTypeDescriptorPtr     GetObject();
    
    static int                  GetCountByUnlockWorld();
public:
    enumTrainingObjectType      ObjectType;
    int                         CostPVPCoin;
    int                         SpaceSize;
    float                       TrainingTime;
    int                         NeedHomeLevel;
    std::string                 NeedWorldName;
    mutable uint32              ShowOrder;   // not write to json
};


#define gTrainingTypeMgr (ObjectTypeDirectory<TrainingType>::GetInstancePtr())
typedef ObjectTypeDirectory<TrainingType>::Iterator				TrainingTypeIter;
typedef ObjectTypeDirectory<TrainingType>::ObjectTypePtr           TrainingTypePtr;

#endif // __TrainingType_H__
