//
//  JoustOrAdventureScreenState.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/28/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustOrAdventureScreenState_h
#define JoustOrAdventureScreenState_h

#include "PVZGameState.h"

class JoustOrAdventureScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(JoustOrAdventureScreenState, PVZHotUIGameState, RtClass);
	
protected:
	RtClass* getTopHudControllerClass() override;
	RtClass* getHotUIAdaptorClass() override;

	std::string GetMusicStartEvent() override { return "Play_Amb_WorldMap_Space_BG_LP"; }
	std::string GetMusicStopEvent() override { return "Stop_Amb_WorldMap_Space_BG_LP"; }
	
};

#endif /* JoustOrAdventureScreenState_h */
