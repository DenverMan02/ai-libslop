//
//  PennyPerkMineIsYours
//  PlantsVersusZombies2Framework
//
//  Created by Jason Emery on 1/27/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef PennyPerkMineIsYours_h
#define PennyPerkMineIsYours_h

#include "BasicPerks.h"

///Mine Is Yours
/// Launches Potato Mines

class PennyPerkMineIsYoursProperties : public PennyPerkProperties
{
    RT_CLASS_DEFINE(PennyPerkMineIsYoursProperties, PennyPerkProperties, RtClass);
    
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
    std::vector<int> SpawnCount;
    std::vector<int> TimesBetweenApplications;
    int MinColumnToTarget;
    int MaxColumnToTarget;
    std::string PlantTypeToSpawn;

    SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkMineIsYours : public PennyPerkTimedEffect
{
public:
    RT_CLASS_DEFINE(PennyPerkMineIsYours, PennyPerkTimedEffect, RtClass);
    
protected:
    void onUpdate() override;
    
private:
    pvztime_t calcNextUpdateTime() override;
    
    void applyCondition();
};

#endif
