//
//  PlantAnimRig_Tallnut.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Tallnut_h
#define PlantsVersusZombies2_PlantAnimRig_Tallnut_h

#include "PlantAnimRig_Wallnut.h"

class PlantAnimRig_Tallnut : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Tallnut, PlantAnimRig, RtClass);
    
    virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
    virtual bool PlayPlantFoodEnd() override;
    
    virtual int GetArmorStateCount();
    virtual void SetArmorStateIndex(int i_index);
    void SetWillDie(bool i_willDie);
    virtual bool PlayIdleLooped() override;
    
    std::vector<std::string> GetArmorLayers();
    
private:
    virtual void onPopAnimInitialized() override;

	void  HideAllShieldLayer();

	bool m_willDie = false;
};

#endif
