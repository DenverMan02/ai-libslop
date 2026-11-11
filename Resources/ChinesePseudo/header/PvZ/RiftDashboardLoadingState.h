//
//  RiftDashboardLoadingState.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/10/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef RiftDashboardLoadingState_h
#define RiftDashboardLoadingState_h

#include "AdaptorRiftZombossProgress.h"
#include "PVZGameState.h"
#include "MacroStateMachine.h"
#include "JoustDataPackets.h"

STATE_ENUM_BASE_BEGIN(RiftDashboardLoadingSubState)
    RIFT_LOADING_INIT,
    RIFT_LOADING_CHECK_FOR_INCOMPLETE_MATCHES,
    RIFT_LOADING_CHECK_FOR_EVENT_TRANSITION,
    RIFT_LOADING_AWARD_ZOMBOSS_ATTEMPT_SHOW_PROGRESS,
    RIFT_LOADING_AWARD_ZOMBOSS_ATTEMPT_GIVE_AWARD,
    RIFT_LOADING_EVENT_TRANSITION,
    RIFT_LOADING_CHECK_FOR_SUB_EVENT_TRANSITION,
    RIFT_LOADING_SUB_EVENT_TRANSITION,
    RIFT_LOADING_DONE,
STATE_ENUM_END(RiftDashboardLoadingSubState);

class RiftDashboardLoadingState : public PVZGameState
{
public:
	RT_CLASS_DEFINE(RiftDashboardLoadingState, PVZGameState, RtClass);

	void Enter() override;
	void Update() override;
	void Exit() override;
	
protected:
    
    DECLARE_FSM_HANDLER_BASE(RiftDashboardLoadingSubState);
    
    DECLARE_FSM_STATE_VALUE(RiftDashboardLoadingSubState);
    
private:
    void finalizeAndExit();
    void finalizeAndFail();
    void onRiftOverAcknowledged();
    
    void onZombossResultsScreenDismissed();
    void onPinataRewardDialogEnded();

    AdaptorRiftZombossProgress* m_zombossResultsScreen = nullptr;
};

#endif
