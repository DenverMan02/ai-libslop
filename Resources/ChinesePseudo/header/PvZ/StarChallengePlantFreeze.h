//
//  StarChallengePlantFreeze.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-3-23.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengePlantFreeze__
#define __PlantsVersusZombies2__StarChallengePlantFreeze__

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengePlantFreeze : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengePlantFreeze, Challenge, RtClass);
    
    virtual void registerForEvents() override;
    
    StarChallengePlantFreeze();

	SexyString GetProgressDescription() const override;
    
private:
    void gameplayStarted();
    void gameplayEnded();
    void OnPlantIcecubed(class Plant* plant);
    
    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }
    
    RtWeakPtr<UIWidget> m_UI;
    int m_plantFrozenLeft;
};

class StarChallengePlantFreezeProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengePlantFreezeProps, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengePlantFreeze::StaticGetClass();
    }
    
    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_PLANT_FREEZE]"), _S("{COUNT}"), cast);
    }
    
    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PLANT_FREEZE_NAME]"));
    }
    
    StarChallengePlantFreezeProps()
    : Count(0)
    {}
    
    int Count;
};

class ChallengePlantFreezeUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(ChallengePlantFreezeUI, ChallengeUI, RtClass);
    
    ChallengePlantFreezeUI();
    void SetCount(int count);
protected:
    virtual SexyString getCountText() override;
    
private:
    int	m_count;
};

#endif /* defined(__PlantsVersusZombies2__StarChallengePlantFreeze__) */
