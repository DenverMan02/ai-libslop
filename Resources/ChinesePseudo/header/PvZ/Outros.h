//
//  Outros
//  PlantsVersusZombies2
//
//  Created by jsola on 7/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Outros_h
#define PlantsVersusZombies2_Outros_h

#include "Core.h"
#include "Singleton.h"
#include "OutroModule.h"
#include "RtObject.h"

enum OutroType
{
	PVZ_BEGIN_ENUM(OUTRO_),
	
	OUTRO_FAILURE_FADE_WITH_MESSAGE,
	OUTRO_FAILURE_ZOMBIES_ATE_YOUR_BRAINS,
	
	OUTRO_VICTORY_DEFAULT,

	OUTRO_WHACKAMOL_GAME_VICTORY,
	OUTRO_WHACKAMOL_GAME_LOSE,
	
	OUTRO_SOCCER_GAME_VICTORY,

	OUTRO_SOCCER_GAME_LOSE,
	OUTRO_TIME_ENERGY_LOSE,

	OUTRO_FAILURE_CARD_GAME_ZOMBIES_ATE_YOUR_BASE,

	OUTRO_FAILURE_NEW_PVP,

	PVZ_END_ENUM(OUTRO_)
};

struct OutroInfo
{
	OutroType Type;
	RtId PropertySheetLocation;
};

class OutroManager : public RtObject
{
public:
    RT_CLASS_DEFINE(OutroManager, RtObject, RtClass);
	static OutroModulePropertiesPtr GetOutro(OutroType i_type);
	static bool VerifyEntries();
};

#endif
