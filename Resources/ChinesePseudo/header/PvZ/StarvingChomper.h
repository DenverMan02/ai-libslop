//
//  StarvingChomper.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/4/7.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarvingChomper__
#define __PlantsVersusZombies2__StarvingChomper__

#include "BoardEntity.h"
#include "StateMachine.h"
#include <queue>

STATE_ENUM_BASE_BEGIN(StarvingChomperState)
    StarvingChomperState_INIT,
    StarvingChomperState_STARVING,
    StarvingChomperState_EATING,
STATE_ENUM_END(StarvingChomperState);

enum ChomperBiteStep
{
    ChomperBiteStep_IDLE,
    ChomperBiteStep_BITE,
    ChomperBiteStep_CATCH,
    ChomperBiteStep_CHEW
};

class StarvingChomper : public BoardEntity
{
public:
    RT_CLASS_DEFINE(StarvingChomper, BoardEntity, RtClass);
    
    StarvingChomper();
    virtual ~StarvingChomper();
    
    void StarvingChomperInitialize(PopAnim* i_popAnim, PopAnim* i_popAnimEmoji, bool i_hint = true);
    
    virtual int CalcRenderOrder() const override;
    
    bool isInState(StarvingChomperState i_state) const;
    void setState(StarvingChomperState i_newState);
    StarvingChomperState getState();
    
    void onChomDodorider();
    
    void Update();
protected:
    /// GameObject interface
    virtual void onInitialized() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onDraw(Graphics* i_g) override;
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
private:
    
    void initializePAM(PopAnim* i_popAnim, PopAnim* i_popAnimEmoji);
    void onAnimStopped(const std::string& i_animName);
    
    void setVisible(bool i_visible) { m_visible = i_visible; }
    bool isVisible() { return m_visible; }
    
    int32 getStarvingChomperStateSerialization();
    void setStarvingChomperStateSerialization(int32 i_state);
    
//    void checkState();
//    void keepState();
    
    void PlayIdleLooped();
    void onDropHead();
    
    DECLARE_STATE_FUNCTIONS(StarvingChomperState, INIT);
    DECLARE_STATE_FUNCTIONS(StarvingChomperState, STARVING);
    DECLARE_STATE_FUNCTIONS(StarvingChomperState, EATING);
    
public:
private:
    bool                                    m_hint;
    bool                                    m_visible;
    ChomperBiteStep                         m_biteStep;
    pvztime_t                               m_biteStartTime;
    pvztime_t                               m_plantStartTime;
    RtWeakPtr<class PopAnimRig>             m_popAnimRig;
    RtWeakPtr<class PopAnimRig>             m_popAnimRigEmoji;
    StateMachine<StarvingChomperState>      m_StarvingChomperState;
};

namespace Message
{
    void DodoriderKilled(bool i_chompedByChomper);
}

#endif /* defined(__PlantsVersusZombies2__StarvingChomper__) */
