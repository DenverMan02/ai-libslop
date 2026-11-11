//
//  JoustDashboardLoadingState.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/11/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustDashboardLoadingState_h
#define JoustDashboardLoadingState_h

#include "PVZGameState.h"

class AdaptorJoustNetworkConnection;

class JoustDashboardLoadingState : public PVZGameState
{
public:
	RT_CLASS_DEFINE(JoustDashboardLoadingState, PVZGameState, RtClass);

	void Enter() override;
	void Update() override;
	void Exit() override;
	
protected:
	void onJoustNetworkResponse(int i_context, int i_status);
	void onJoustNetworkIssueDecision(int i_context, int i_decision);
	
	void sendNextInitRequest();
	void checkCurrentDashboardInfo();
	void sendIncompleteMatch();
	void sendDashboardRequest();
	void sendAvatarCreationRequest();
	void abandonNetworkFlow();
	
	void showConnectionDialog();
	void hideConnectionDialog();
	
	AdaptorJoustNetworkConnection* m_networkDialog;
	bool m_firstUpdate = false;
};

#endif
