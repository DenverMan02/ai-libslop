//
//  StarChallengePlantsSurvive.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-3-26.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengePlantsSurvive__
#define __PlantsVersusZombies2__StarChallengePlantsSurvive__

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengePlantsSurvive : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengePlantsSurvive, Challenge, RtClass);
    
    virtual void registerForEvents() override;
    
    StarChallengePlantsSurvive();

	SexyString GetProgressDescription() const override;
    
private:
    void gameplayStarted();
    void gameplayEnded();
    void onPlantLost(class Plant* i_plant);
    void onPlantAdded(class Plant* i_plant);
    void onPlantUpgraded(Plant* i_plant, int i_level);
    void onLilyPadDied(class GridItemLilyPad* i_lilyPad);
    void onFlowerPotDied(class GridItemFlowerPot* i_flowerPot);
    int GetPlantCount();
    
    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }
    
    RtWeakPtr<UIWidget> m_UI;
    int m_plantCount;
};

class StarChallengePlantsSurviveProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengePlantsSurviveProps, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengePlantsSurvive::StaticGetClass();
    }
    
    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_PLANT_SURVIVE]"), _S("{COUNT}"), cast);
    }
    
    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PLANT_SURVIVE_NAME]"));
    }
    
    StarChallengePlantsSurviveProps()
    : Count(0)
    {}
    
    int Count;
};

class ChallengePlantSurviveUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(ChallengePlantSurviveUI, ChallengeUI, RtClass);
    
    ChallengePlantSurviveUI();
    void SetCurrent(int count);
    void SetTarget(int target);
protected:
    virtual SexyString getCountText() override;
    
private:
    int	m_current;
    int m_target;
};

#endif /* defined(__PlantsVersusZombies2__StarChallengePlantsSurvive__) */
