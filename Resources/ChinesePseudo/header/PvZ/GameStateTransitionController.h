//
//  GameStateTransitionController.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 6/27/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GameStateTransitionController__
#define __PlantsVersusZombies2__GameStateTransitionController__

#include "GameStateMgr.h"
#include "TransitionOverlayWidget.h"

STATE_ENUM_BASE_BEGIN(GameTransitionState)
	GAMETRANSITIONSTATE_Off,
	GAMETRANSITIONSTATE_Out,
	GAMETRANSITIONSTATE_WarpTunnel,
	GAMETRANSITIONSTATE_WarpTunnelPVZ1,
	GAMETRANSITIONSTATE_In,
STATE_ENUM_END(GameTransitionState)

struct GameTransitionParameters
{
	GameTransitionType 	Type;
	FadeTransitionType	FadeType;
	Color				FadeColor;
	float				Duration;
};

class GameStateTransitionController : public RtObject
{
public:
	RT_CLASS_DEFINE(GameStateTransitionController, RtObject, RtClass) {}
	GameStateTransitionController();
	
	void SetGameStateMgr(GameStateMgr* i_gameStateMgr) { m_gameStateMgr = i_gameStateMgr; }
	
	void Update();
	void Draw(Graphics* i_g);
	
	void TransitionToState(GameState i_targetState, GameTransitionType i_out, GameTransitionType i_in);
	bool IsTransitioning() const;
	bool IsTransitioningOut() const;
	const GameState GetQueuedStateChange() { return m_queuedStateChange; }
	const GameTransitionType GetInTransition() { return m_inTransition; }
	const GameTransitionState GetTransitionState() { return m_transitionState.GetState(); }
	
	void SetFullScreenTransitionType(const FullScreenTransitionType i_transitionType) { m_fullscreenTransitionType = i_transitionType; }
	const FullScreenTransitionType GetFullScreenTransitionType() { return m_fullscreenTransitionType; }
	
	void SetCoveringLoad(bool i_isCoveringLoad) { m_coveringLoad = i_isCoveringLoad; }
	void SetOverlayRenderActive(bool i_active);
    
    
    StateMachine<GameTransitionState> GetState() { return m_transitionState; }
    
	
protected:
	DECLARE_STATE_FUNCTIONS(GameTransitionState, TransitionOut);
	DECLARE_STATE_FUNCTIONS(GameTransitionState, TransitionWarpTunnel);
	DECLARE_STATE_FUNCTIONS(GameTransitionState, TransitionWarpTunnelPVZ1);
	DECLARE_STATE_FUNCTIONS(GameTransitionState, TransitionIn);
	
private:
	void startTransitionEffect(GameTransitionType i_type, bool i_transitioningOut);
	void setTransitionState(const StateDefinition<GameTransitionState>& i_transitionState);
	void doQueuedStateChange();
	void continueTransition();
	
	GameStateMgr* m_gameStateMgr;
	StateMachine<GameTransitionState> m_transitionState;
	GameTransitionType m_outTransition;
	GameTransitionType m_inTransition;
	bool m_finalFrameDrawn;
	GameState m_queuedStateChange;
	FullScreenTransitionType m_fullscreenTransitionType;
	class PopAnimRig* m_fullScreenTransitionEffect;
	bool m_coveringLoad;
};

#endif /* defined(__PlantsVersusZombies2__GameStateTransitionController__) */
