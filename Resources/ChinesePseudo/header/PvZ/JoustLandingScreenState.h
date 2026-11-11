//
//  JoustLandingScreenState.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/16/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustLandingScreenState_h
#define JoustLandingScreenState_h

#include "PVZGameState.h"

class JoustLandingScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(JoustLandingScreenState, PVZHotUIGameState, RtClass);
	
protected:
	RtClass* getTopHudControllerClass() override;
	RtClass* getHotUIAdaptorClass() override;
	
	std::string GetMusicStartEvent() override { return "Play_Joust_Dashboard_Music"; }
	std::string GetMusicStopEvent() override { return "Stop_Joust_Dashboard_Music"; }

};

#endif /* JoustLandingScreenState_h */
