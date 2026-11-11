//
//  WorldMap_PlantTrialButton.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-4-02.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_PlantTrialButton__
#define __PlantsVersusZombies2__WorldMap_PlantTrialButton__

#include "UIEasyButtonWidget.h"

class WorldMap_PlantTrialButton : public UIEasyButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_PlantTrialButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_PlantTrialButton();
    virtual ~WorldMap_PlantTrialButton();
    
    virtual void		Draw(Graphics* i_g) override;
    
    void                SetButtonData(std::string& strPlantName) { m_strPlantName = strPlantName; }
    const std::string& GetPlant() { return m_strPlantName; }
    
private:
    void                DoPressPlantTrialButton();
    
private:
    
    std::string m_strPlantName;
    
    // Private Members (serialized)
    
    // Private Members (not serialized)
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_RedPackButton__) */
