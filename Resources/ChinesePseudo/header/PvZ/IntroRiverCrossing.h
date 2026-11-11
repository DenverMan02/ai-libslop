//
//  IntroRiverCrossing.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/4/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroRiverCrossing__
#define __PlantsVersusZombies2__IntroRiverCrossing__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"

STATE_ENUM_BASE_BEGIN(RCIState)
    RCIState_GAMEINIT,
    RCIState_TUTORIAL,
    RCIState_InStage1,
    RCIState_InStage2,
    RCIState_InStage3,
    RCIState_InStage4,
    RCIState_STARTGAME,
STATE_ENUM_END(RCIState);

class RiverCrossingIntro : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(RiverCrossingIntro, StandardLevelIntro, RtClass);
    
    RiverCrossingIntro();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    std::string GetTargetAdvice(int i_index);

protected:
    virtual void	initializeModule() override;
    virtual void	registerForEvents() override;
    
    void			OnIntroStarted();
    void 			OnUpdate();
    void 			OnLevelEnded();
    void            OnGameplayStarted();
    
    void            OnDodoRiderRunOutBorderWorning();
    void            OnRiverCrossingHandleTouch(int i_step);
    void            OnDodoRiderDiedForIntro();
    // void            OnSnakeRunOutBorderWorning();
    
    
    DECLARE_STATE_FUNCTIONS(RCIState, GAMEINIT);
    DECLARE_STATE_FUNCTIONS(RCIState, TUTORIAL);
    DECLARE_STATE_FUNCTIONS(RCIState, InStage1);
    DECLARE_STATE_FUNCTIONS(RCIState, InStage2);
    DECLARE_STATE_FUNCTIONS(RCIState, InStage3);
    DECLARE_STATE_FUNCTIONS(RCIState, InStage4);
    DECLARE_STATE_FUNCTIONS(RCIState, STARTGAME);
    
    
private:
    
    void        setState(RCIState i_newState);
    bool        isInState(RCIState i_state) const;
    
    void        createGloveEffect(int i_step);
    
    void        ShowReady();
    void        ShowSet();
    void        ShowBreak();
private:
    StateMachine<RCIState>      m_RCIState;
    
    int                                 m_moveTutorialStep;
    pvztime_t                           m_startTime;
    float                               m_readyTime;
    float                               m_setTime;
    float                               m_breakTime;
    float                               m_goTime;
    bool                                m_readyShown;
    bool                                m_setShown;
    bool                                m_breakShown;
    bool                                m_started;
    bool                                m_hasHinted;
    RtWeakPtr<class Effect_PopAnim>     m_gloveEffect;
    pvztime_t                           m_gloveStartTime;
    SexyVector3                         m_gloveStartPos;
};

class RiverCrossingIntroProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(RiverCrossingIntroProperties, StandardLevelIntroProperties, RtClass);
    
    RiverCrossingIntroProperties()
    {
        RiverCrossingStage = -1;
    }
    
    virtual RtClass* GetModuleClass() const override
    {
        return RiverCrossingIntro::StaticGetClass();
    }
    
    int RiverCrossingStage;
    std::vector<std::string> DisplayAdvices;
};

#endif /* defined(__PlantsVersusZombies2__IntroRiverCrossing__) */
