//
//  StarChallengeProtectPlant.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-3-31.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengeProtectPlant__
#define __PlantsVersusZombies2__StarChallengeProtectPlant__

#include "ChallengeModule.h"
#include "TodStringFile.h"
#include "ProtectThePlantChallenge.h"

class StarChallengeProtectPlant : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeProtectPlant, Challenge, RtClass);
    
    virtual void registerForEvents() override;
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    StarChallengeProtectPlant();

private:
    void gameplayEnded();
    void onPlantDied(class Plant* i_plant);
    void SpawnPlants();
    void onLoadComplete();
    void addToRenderQueue(class RenderQueue* i_queue);
    void RenderMark(Sexy::Graphics *i_g);
    std::vector<PlantPtr> m_plants;
	ImagePtr m_mark;
};

class StarChallengeProtectPlantProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeProtectPlantProps, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeProtectPlant::StaticGetClass();
    }
    
    virtual SexyString GetDescription() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PROTECT_PLANT]"));
    }
    
    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PROTECT_PLANT]"));
    }
    std::vector<ProtectedPlantEntry> Plants;
};

#endif /* defined(__PlantsVersusZombies2__StarChallengeProtectPlant__) */
