//
//  IntroPooyan.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/7/22.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroPooyan__
#define __PlantsVersusZombies2__IntroPooyan__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"
#include "Effect_BouncingArrow.h"

STATE_ENUM_BASE_BEGIN(PIState)
    PIState_GAMEINIT,
    PIState_TUTORIAL,
    PIState_InStage1,
    PIState_STARTGAME,
STATE_ENUM_END(PIState);

class PooyanIntro : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(PooyanIntro, StandardLevelIntro, RtClass);
    
    PooyanIntro();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
    virtual void	initializeModule() override;
    virtual void	registerForEvents() override;
    
    void OnIntroStarted();
    void OnUpdate();
    void OnLevelEnded();
    void OnGameplayStarted();
    void OnPooyanShooterChoosed();
    void OnNarrativePooyanZombieCompleted();
    void OnNarrativeCompleted();
    void OnNarrativeChoosedCompleted();
    void OnPooyanIntroHandleTouch();
    // void OnSnakeRunOutBorderWorning();
    
    DECLARE_STATE_FUNCTIONS(PIState, GAMEINIT);
    DECLARE_STATE_FUNCTIONS(PIState, TUTORIAL);
    DECLARE_STATE_FUNCTIONS(PIState, InStage1);
    DECLARE_STATE_FUNCTIONS(PIState, STARTGAME);
    
private:
    void setState(PIState i_newState);
    bool isInState(PIState i_state) const;
    
    void createGloveEffect();
    void StartPooyanGame();
    
    void ClearBouncingArrows();
    Effect_BouncingArrow * AddBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    
private:
    bool                                m_hasHinted;
    StateMachine<PIState>               m_PIState;
    RtWeakPtr<class Effect_PopAnim>     m_gloveEffect;
    pvztime_t                           m_closingGameMaskTime;
    pvztime_t                           m_startGameMaskTime;
    pvztime_t                           m_gloveStartTime;
    SexyVector3                         m_gloveStartPos;
    std::vector<StandaloneEffectPtr>    m_bouncingArrows;
};

class PooyanIntroProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(PooyanIntroProperties, StandardLevelIntroProperties, RtClass);
    
    PooyanIntroProperties()
    {
        PooyanStage = -1;
    }
    
    virtual RtClass* GetModuleClass() const override
    {
        return PooyanIntro::StaticGetClass();
    }
    
    int PooyanStage;
};

#endif /* defined(__PlantsVersusZombies2__IntroPooyan__) */
