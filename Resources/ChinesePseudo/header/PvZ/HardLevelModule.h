//
//  HardLevelModule.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/5/6.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_HardLevelModule_h
#define PlantsVersusZombies2_HardLevelModule_h

#include "LevelModule.h"
#include "Core.h"
#include "HardLevelConfig.h"

class HardLevelModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(HardLevelModule, LevelModule, RtClass);
    
    HardLevelModule();
    
    int GetZombieLevel();
    float GetDifficult();
    
protected:
    virtual void registerForEvents() override;
    
private:
    void onInit();
    
    ZombieLevelCreater m_creater;
};


class HardLevelProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(HardLevelProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return HardLevelModule::StaticGetClass();
    }
    
    HardLevelProperties()
    {
    }
};

#endif /* HardLevelModule_h */
