//
//  JoustTournamentEndScreenState.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/16/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustTournamentEndScreenState_h
#define JoustTournamentEndScreenState_h

#include "PVZGameState.h"

class JoustTournamentEndScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(JoustTournamentEndScreenState, PVZHotUIGameState, RtClass);
	
protected:
	void onHotUILoaded(HotUIAdaptor* i_adaptor) override;
	
	RtClass* getTopHudControllerClass() override { return nullptr; }
	RtClass* getHotUIAdaptorClass() override;
};

#endif /* JoustTournamentEndScreenState_h */
