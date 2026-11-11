//
//  ClassBucketFilter.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/25/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ClassBucketFilter__
#define __PlantsVersusZombies2__ClassBucketFilter__

#include "ComponentBase.h"
#include "RestrictionSet.h"

class ClassBucketFilter : public RtObject
{
public:
    RT_CLASS_DEFINE(ClassBucketFilter, RtObject, RtClass);

    int GetBucket(const BoardEntity* gameObject);
    std::vector<std::vector<BoardEntityPtr>> FilterToBuckets(const std::vector<BoardEntityPtr>& i_incomingList);
    std::vector<BoardEntityPtr> FilterToList(const std::vector<BoardEntityPtr>& i_incomingList, bool i_shuffleBuckets);

    int size() { return (int) Buckets.size(); }

private:
    std::vector<ClassRestrictionSet> Buckets;
    
};

#endif
