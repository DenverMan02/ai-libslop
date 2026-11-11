//
//  BombModule.h
//  PlantsVersusZombies2
//
//  Created by hanj on 12/04/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

//PVZ2_CHINESE_BEGIN

#ifndef PlantsVersusZombies2_BombModule_h
#define PlantsVersusZombies2_BombModule_h

#include "LevelModule.h"

class BombModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(BombModule, LevelModule, RtClass);

    float GetPaveTime() const;

    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:
    virtual void registerForEvents() override;
    void onReadyForBombs() const;

};

class BombProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(BombProperties, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return BombModule::StaticGetClass();
    }

    std::vector<int> 			m_fuseLengthsByGrid;
    float 						m_flameSpeed;
    int							m_flameInitialBlood;
};

#endif


//PVZ2_CHINESE_END
