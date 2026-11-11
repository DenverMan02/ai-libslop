//
//  GamePropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __GAMEPROPERTYSHEET_H__
#define __GAMEPROPERTYSHEET_H__

#include "Precompile.h"
#include "PropertySheetBase.h"
#include "ZombieEnums.h"

class GamePropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(GamePropertySheet, PropertySheetBase, RtClass);
    
    GamePropertySheet()
	{
		ZombieVsZombieCrushingDamageScale = 1.0f;
		ZombieVsFriendlyZombieDamageScale = 1.0f;
	}
	
	// Specifies the order of plants in the seed chooser and the seed bank
	std::vector<std::string> PlantTypeOrder;
    std::vector<std::string> PlantAlmanacOrder;
	// Specifies the order of zombies in the almanac
	std::vector<std::string> ZombieAlmanacOrder;
    
    
    // Power Tile global config
	float PowerTilePropagationAlpha;
	float PowerTilePropagationDelay;
	float PowerTilePropagationInitialDelay;
    
    float ZombieVsZombieCrushingDamageScale;
	float ZombieVsFriendlyZombieDamageScale;
    
    std::vector<ZombieConditions> ZombieConditionsWhichInvincibleOverrides;
    std::vector<ZombieConditions> ZombieConditionsWhichZombieBossImmunities;
    std::vector<ZombieConditions> ZombieConditionsWhichZombieEliteImmunities;
    std::vector<ZombieConditions> ZombieConditionsWhichZombieFogShieldImmunities;
};

GamePropertySheet *GetDefaultGameProps();

#endif // __GAMEPROPERTYSHEET_H__
