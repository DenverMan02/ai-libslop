//
//  StarChallengePlantFoodNonuse.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-3-30.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengePlantFoodNonuse__
#define __PlantsVersusZombies2__StarChallengePlantFoodNonuse__

#include "ChallengeModule.h"
#include "TodStringFile.h"

class StarChallengePlantFoodNonuse : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengePlantFoodNonuse, Challenge, RtClass);
    
    virtual void registerForEvents() override;
    
    StarChallengePlantFoodNonuse();
protected:
    virtual void onPostLoad() override;
private:
    void gameplayStarted();
    void gameplayEnded();
    void onToolAppliedPlantFood(class PlantGroup* i_plant);
    bool onPlantfoodTouched();
    void ShowTip();
    void CancelTip();
    void NotShowTipAgain();
    bool m_showTip;
};

class StarChallengePlantFoodNonuseProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengePlantFoodNonuseProps, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengePlantFoodNonuse::StaticGetClass();
    }
    
    virtual SexyString GetDescription() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PLANTFOOD_NONUSE]"));
    }
    
    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PLANTFOOD_NONUSE_NAME]"));
    }
};

#endif /* defined(__PlantsVersusZombies2__StarChallengePlantFoodNonuse__) */
