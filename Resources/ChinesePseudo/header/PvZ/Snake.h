//
//  Snake.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-12-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Snake__
#define __PlantsVersusZombies2__Snake__

#include "BoardEntity.h"
#include "StateMachine.h"

#include <queue>

STATE_ENUM_BASE_BEGIN(SnakeState)
SnakeState_INIT,
SnakeState_RIGHT,
SnakeState_LEFT,
SnakeState_UP,
SnakeState_DOWN,
STATE_ENUM_END(SnakeState);

class SnakeNode : public BoardEntity
{
public:
	RT_CLASS_DEFINE(SnakeNode, BoardEntity, RtClass);
	
	SnakeNode();
	virtual ~SnakeNode();
    
	void				SnakeNodeInitialize(PopAnim* i_mowerPopAnim);
    
    void                AddTrace(const SexyVector3& pos);
    
    Rect                GetAttackRect();
    
	/// BoardEntity interface
	virtual int 		CalcRenderOrder() const override;

    bool       			isInState(SnakeState i_state) const;
	void        		setState(SnakeState i_newState);
    SnakeState          getState();
    
    void        		setTouchState(SnakeState i_newState);
    void                HandleTouch(const Point& pos);
    
    void                setChompDamage(int   i_chompDamage);
    void                setCurrentStep(float i_currentStep);
    
    void                setIsSlowDown(bool   i_slowDown);
    bool                IsSlowDown();

    void                setIsBlink(bool   i_isBlink);
    
    class SnakeNode * next;
    class SnakeNode * prior;
    
    int                  tag;
	
protected:
    
	/// GameObject interface
	virtual void		onInitialized() override;
	virtual void		onUpdate() override;
	virtual void		onDestroy() override;
	virtual void		onDraw(Graphics* i_g) override;
	//virtual void		onDrawShadow(Graphics* i_g);
    virtual void		registerForEvents() override;
	virtual void		unregisterForEvents() override;
	
private:
    
	void				initializePAM(PopAnim* i_mowerPopAnim);
    void				onAnimStopped(const std::string& i_animName);
    
    int32				getSnakeStateSerialization();
	void				setSnakeStateSerialization(int32 i_state);
    
    void                checkState();
    void                keepState();
    
    
    void                onZombieDropHead(class Zombie * i_zombie);
    
    // Snake State Machine
    DECLARE_STATE_FUNCTIONS(SnakeState, INIT);
	DECLARE_STATE_FUNCTIONS(SnakeState, RIGHT);
	DECLARE_STATE_FUNCTIONS(SnakeState, LEFT);
	DECLARE_STATE_FUNCTIONS(SnakeState, UP);
	DECLARE_STATE_FUNCTIONS(SnakeState, DOWN);
    
private:
    
	RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    StateMachine<SnakeState> 	m_snakeState;
    
    std::queue<SexyVector3>     m_trace;
    
    float                       m_step;
    float                       m_currentStep;
    SnakeState                  m_touchSnakeState;
    
    int                         m_nAddNodeCount;
    int                         m_chompDamage;
    
    bool                        m_isSlowDown;
    bool                        m_isBlink;
    bool                        m_needSendSlowDown;
};

namespace Message
{
	void SnakeAdd();
    void SnakeHeadHitBody();
    void SnakeHitBlock();
    void SnakeRunOutBorder();
    void SnakeRunOutBorderWorning();
    void SnakeSlowDown();
    void SnakeHandleTouchState(int direction);
}

#endif /* defined(__PlantsVersusZombies2__Snake__) */
