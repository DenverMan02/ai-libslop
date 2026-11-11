//
//  IntroBesiege.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/8/20.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroBesiege__
#define __PlantsVersusZombies2__IntroBesiege__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"
#include "BesiegeModule.h"
#include "Effect_BouncingArrow.h"

STATE_ENUM_BASE_BEGIN(BIState)
    BIState_GAMEINIT,
    BIState_STARTGAME,
STATE_ENUM_END(BIState);

class BesiegeIntro : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(BesiegeIntro, StandardLevelIntro, RtClass);
    
    BesiegeIntro();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
    virtual void	initializeModule() override;
    virtual void	registerForEvents() override;
    
    void OnIntroStarted();
    void OnUpdate();
    void OnLevelEnded();
    void OnGameplayStarted();
    void OnNarrativeTutorialCompleted();
    void OnNarrativeBoxCompleted();
    void OnNarrativeBoxShoveledCompleted();
    void OnNarrativeBoxPlantedCompleted();
    void OnNarrationPlantUpgrade();
    void OnNarrationGameStart();
//    void OnBesiegeIntroHandleTouch();
    void OnUseShovel();
    void OnProgressMeterSetFlagCount(int i_flagCount);
    void OnCursorAdded(BaseCursor* i_cursor);
    void OnGridItemPlanted(GridItem* i_gridItem);
    void OnPlantUpgrade();
    void OnShoveledBesiegeBox();
    
    DECLARE_STATE_FUNCTIONS(BIState, GAMEINIT);
    DECLARE_STATE_FUNCTIONS(BIState, STARTGAME);
    
private:
    void setState(BIState i_newState);
    bool isInState(BIState i_state) const;
    
    void OnShovelTutorial();
    void StartBesiegeGame();
    void ClearBouncingArrows();
    Effect_BouncingArrow * AddBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    
private:
    bool                                m_shovelTutorial;
    StateMachine<BIState>               m_BIState;
    std::vector<StandaloneEffectPtr>    m_bouncingArrows;
};

class BesiegeIntroProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(BesiegeIntroProperties, StandardLevelIntroProperties, RtClass);
    
    BesiegeIntroProperties()
    {
        BesiegeStage = -1;
    }
    
    virtual RtClass* GetModuleClass() const override
    {
        return BesiegeIntro::StaticGetClass();
    }
    
    int BesiegeStage;
};

#endif /* defined(__PlantsVersusZombies2__IntroBesiege__) */
