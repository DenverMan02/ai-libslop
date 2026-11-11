//
//  Plant_Marigold.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 10/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Marigold__
#define __PlantsVersusZombies2__Plant_Marigold__

#include "PlantFramework.h"
#include "RtObject.h"
#include "GameSubSystem.h"


//
// Marigold
//

class PlantMarigold : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMarigold, PlantFramework, RtClass);
    
    virtual void Initialize() override;
    virtual void UpdateActions() override;
    virtual void ProduceSun(const PlantAction& i_fromAction) override;
    virtual bool CanApplyPlantfood() override;
    virtual void ApplyPlantfood() override;
    virtual void CancelPlantfood() override;
    
    void PutToSleep();
protected:
    bool isAsleep() const;
};
#endif /* defined(__PlantsVersusZombies2__Plant_Marigold__) */
