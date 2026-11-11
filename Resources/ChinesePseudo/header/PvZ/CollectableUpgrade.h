//
//  CollectableUpgrade.h
//  PlantsVersusZombies2
//
//  Created by jsola on 2/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableUpgrade_h
#define PlantsVersusZombies2_CollectableUpgrade_h

#include "Collectable.h"

class CollectableUpgrade : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableUpgrade, Collectable, RtClass) {}
};

class CollectableUpgradeType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableUpgradeType, CollectableType, RtClass);
	
	CollectableUpgradeType()
	{
	}
	
	std::string		Upgrade;
};


//PVZ2_CHINESE_BEGIN
class CollectableBonus : public Collectable
{
public:
    RT_CLASS_DEFINE(CollectableBonus, Collectable, RtClass) {}
    
};

class CollectableBonusType : public CollectableType
{
public:
    RT_CLASS_DEFINE(CollectableBonusType, CollectableType, RtClass);
    
    CollectableBonusType()
    {
    }
    
    std::string     Bonus;
};
//PVZ2_CHINESE_END
#endif
