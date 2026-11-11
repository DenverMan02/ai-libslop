/*
 * PVZ1DashboardLoadingState.h
 *
 *  Created on: 2021-8-11
 *      Author: admin
 */

#ifndef PVZ1DASHBOARDLOADINGSTATE_H_
#define PVZ1DASHBOARDLOADINGSTATE_H_

#include "PVZGameState.h"
#include "MacroStateMachine.h"

STATE_ENUM_BASE_BEGIN(PVZ1DashboardLoadingSubState)
    PVZ1_LOADING_INIT,
    PVZ1_LOADING_DONE,
STATE_ENUM_END(PVZ1DashboardLoadingSubState);

class PVZ1DashboardLoadingState : public PVZGameState
{
public:
	RT_CLASS_DEFINE(PVZ1DashboardLoadingState, PVZGameState, RtClass);

	void Enter() override;
	void Update() override;
	void Exit() override;

protected:

    DECLARE_FSM_HANDLER_BASE(PVZ1DashboardLoadingSubState);

    DECLARE_FSM_STATE_VALUE(PVZ1DashboardLoadingSubState);

private:
    void finalizeAndExit();
};


#endif /* PVZ1DASHBOARDLOADINGSTATE_H_ */
