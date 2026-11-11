//
//  RiverCrossingDodoRider.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/4/7.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RiverCrossingDodoRider__
#define __PlantsVersusZombies2__RiverCrossingDodoRider__

#include "BoardEntity.h"
#include "StateMachine.h"
#include <queue>
#include "ProbabilitySet.h"

STATE_ENUM_BASE_BEGIN(RiverCrossingDodoRiderState)
    RiverCrossingDodoRiderState_IDLE,
    RiverCrossingDodoRiderState_WALKING,
    RiverCrossingDodoRiderState_FLYING,
    RiverCrossingDodoRiderState_LEAVING,
    RiverCrossingDodoRiderState_DEAD,
STATE_ENUM_END(RiverCrossingDodoRiderState);

enum MoveDirection
{
    RiverCrossingDodoRiderDir_UP,
    RiverCrossingDodoRiderDir_DOWN,
    RiverCrossingDodoRiderDir_LEFT,
    RiverCrossingDodoRiderDir_RIGHT
};

enum DodoRiderFlyingMotion
{
    DodoRiderFlyingMotion_Land,
    DodoRiderFlyingMotion_Start,
    DodoRiderFlyingMotion_Loop,
    DodoRiderFlyingMotion_End
};

class RiverCrossingDodoRider : public BoardEntity
{
public:
    RT_CLASS_DEFINE(RiverCrossingDodoRider, BoardEntity, RtClass);
    
    RiverCrossingDodoRider();
    virtual ~RiverCrossingDodoRider();
    
    void RiverCrossingDodoRiderInitialize(PopAnim* i_popAnim);
    void RiverCrossingExternDodoRiderInitialize(PopAnim* i_popAnim);
//    void AddTrace(const SexyVector3& pos);
    // Rect GetAttackRect();
    
    Rect GetDodoRiderRect();
    virtual int CalcRenderOrder() const override;
    
    bool isInState(RiverCrossingDodoRiderState i_state) const;
    void setState(RiverCrossingDodoRiderState i_newState);
    RiverCrossingDodoRiderState getState();
    
    void SetNextPosition(SexyVector3 nextPos);
    Sexy::SexyVector3 GetNextPosition();
    void SetWillJumpIntoWater() { m_willJumpIntoWater = true; }
    void JumpIntoWater();
    void OnDodoRiderLanded();
    
    bool canMove();
    void SetWalkingRate(float i_rate);
    void SetFlyingRate(float i_rate);
    float GetWalkingRate();
    float GetFlyingRate();
    float CalcDodoFlyingTime();
    void SetIsMoving(bool i_moving);
    void SetIsFlying(bool i_fly);
    bool IsFlying();
    void Update();
    
    void PlayIdleLooped();
    void WalkToNext();
    void FlyToNext();
    
protected:
    /// GameObject interface
    virtual void onInitialized() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onDraw(Graphics* i_g) override;
    //virtual void onDrawShadow(Graphics* i_g);
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
    virtual void initializePAM(PopAnim* i_popAnim);
    virtual void onAnimStopped(const std::string& i_animName);
    virtual void GetIdleWeights(ProbabilitySet<std::string>& i_idleWeights);
    virtual SexyVector2 GetDrawOffet();
    
private:
    
    int32 getRiverCrossingDodoRiderStateSerialization();
    void setRiverCrossingDodoRiderStateSerialization(int32 i_state);
    
    void SetFlyingMotion(DodoRiderFlyingMotion i_motion);
    
//    void checkState();
//    void keepState();
    
    void onDropHead();
    
    // Snake State Machine
    DECLARE_STATE_FUNCTIONS(RiverCrossingDodoRiderState, IDLE);
    DECLARE_STATE_FUNCTIONS(RiverCrossingDodoRiderState, WALKING);
    DECLARE_STATE_FUNCTIONS(RiverCrossingDodoRiderState, FLYING);
    DECLARE_STATE_FUNCTIONS(RiverCrossingDodoRiderState, LEAVING);
    DECLARE_STATE_FUNCTIONS(RiverCrossingDodoRiderState, DEAD);
private:
    SexyVector3                                 m_startPosition;
    SexyVector3                                 m_nextPosition;
    pvztime_t                                   m_startingMovingTime;
    float                                       m_walkingRate;
    float                                       m_flyingRate;
    bool                                        m_isFlying;
    bool                                        m_isMoving;
    bool                                        m_willJumpIntoWater;
    bool                                        m_landed;
    StateMachine<RiverCrossingDodoRiderState>   m_riverCrossingDodoRiderState;
    DodoRiderFlyingMotion                       m_flyingMotion;

protected:
    RtWeakPtr<class PopAnimRig>                 m_popAnimRig;
};

namespace Message
{
    void DodoriderKilled(bool i_chompedByChomper);
    void PlayFloatingIceCarryingAnim();
    void DodoRiderDied();
    void DodoriderJumpIntoRiver();
    void CheckDodorider();
    void DodoRiderLanding();
}

#endif /* defined(__PlantsVersusZombies2__RiverCrossingDodoRider__) */
