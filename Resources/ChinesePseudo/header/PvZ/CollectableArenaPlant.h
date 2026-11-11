//
//  CollectableArenaPlant.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 16/2/15.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef CollectableArenaPlant_hpp
#define CollectableArenaPlant_hpp

#include "CollectableArenaZombie.h"

class CollectableArenaPlant : public CollectableArenaZombie
{
public:
    
    RT_CLASS_DEFINE(CollectableArenaPlant, CollectableArenaZombie, RtClass);
    
    void SetPlantSeedType(PlantTypePtr i_PlantType);
    
    CollectableArenaPlant();
    
protected:
    
    void drawToBuffer() override;
    
    void onFinishMotion() override;
    
    void StartMoving() override;
    
private:
    
    PlantTypePtr m_seedPlantType;
    
};

#endif /* CollectableArenaPlant_h */
