//
//  CollectablePlantUpgrade.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-5-7.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CollectablePlantUpgrade__
#define __PlantsVersusZombies2__CollectablePlantUpgrade__

#include "Collectable.h"

class CollectablePlantUpgradeType : public CollectableType
{
	RT_CLASS_DEFINE(CollectablePlantUpgradeType, CollectableType, RtClass);
};


class CollectablePlantUpgrade : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectablePlantUpgrade, Collectable, RtClass);
    
    void SetSeedName(const std::string& i_seedName);
    
    std::string GetSeedName();
    
protected:
	virtual void onFinishMotion() override;
    
private:
    std::string  m_seedName;
};

#endif /* defined(__PlantsVersusZombies2__CollectablePlantUpgrade__) */
