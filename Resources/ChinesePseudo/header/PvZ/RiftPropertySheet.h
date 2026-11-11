//
//  RiftPropertySheet
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/28/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RiftPropertySheet__
#define __PlantsVersusZombies2__RiftPropertySheet__

#include "AdaptorHowToPlayScreen.h"
#include "PropertySheetBase.h"

struct RiftLocalNoteConfig
{
    int LocalNoteMinDelayTime;
    int LocalNoteMaxDelayTime;
};

class RiftPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(RiftPropertySheet, PropertySheetBase, RtClass);

	RiftPropertySheet()
	{
		PlantsRequiredToUnlock = 12;
    }

	HowToPlayScreenData	HowToPlayData;
	int		PlantsRequiredToUnlock;
    
    RiftLocalNoteConfig EventEndNoteConfig;
    RiftLocalNoteConfig ZombossEndNoteConfig;
    
    int ZombossPointOfLossGemCost;
    int ZombossPointOfLossNumAvailable;
    int ZombossPointOfLossTimeGained;
    
public:
	static RiftPropertySheet* GetProperties();
};

#endif
