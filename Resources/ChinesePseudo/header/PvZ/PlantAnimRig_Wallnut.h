//
//  PlantAnimRig_Wallnut.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/5/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_WALLNUT_H__
#define __PLANTANIMRIG_WALLNUT_H__

#include "Precompile.h"
#include "PlantAnimRig_Shielded.h"
#include "RtObject.h"
#include "TimeMgr.h"

class PlantAnimRig_Wallnut : public PlantAnimRig_Shielded
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Wallnut, PlantAnimRig_Shielded, RtClass);
    
    pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
    bool PlayPlantFoodEnd() override;
    
    int GetArmorStateCount() override;
    void HideAllShieldLayer();
    void SetArmorStateIndex(int i_index) override;
    
    std::vector<std::string> GetArmorLayers();
    
    bool IsWallnutAnim(std::string i_animFix, std::string i_anim);
    bool IsShootAnim(std::string i_anim);
    
    std::string getRecoverAnim();
    void PlayRecover(AnimStoppedDelegate i_onStopDelegate);
    std::string getShootIceAnim();
    void PlayShootIce(AnimStoppedDelegate i_onStopDelegate);
    std::string getShootFireAnim();
    void PlayShootFire(AnimStoppedDelegate i_onStopDelegate);
    std::string getShootElectricAnim();
    void PlayShootElectric(AnimStoppedDelegate i_onStopDelegate);
    
protected:
    virtual const std::vector<std::string>& getArmorStateLayerNames() const;
    
private:
    void onPopAnimInitialized() override;
    virtual std::string getDamageIdleAnimationName() override;
};

#endif // __PLANTANIMRIG_WALLNUT_H__
