//
//  PlantBoostPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 1/7/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PLANT_BOOST_PROPERTY_SHEET_H__
#define __PLANT_BOOST_PROPERTY_SHEET_H__

#include "PropertySheetBase.h"
#include "RtObject.h"

//Do not delete or reorder these.  You will break live saved player datas
enum PlantBoostType
{
	NONE,
	EXTRA_PLANTFOOD_DURATION,
	EXTRA_SUNMONEY,
    EXTRA_ACCESSORY_SUNMONEY,
	EXTRA_HITPOINTS,
	EXTRA_HITPOINTS_VALUE,
	EXTRA_ATTACK,
	REGENERATION,
	FAST_COOLDOWN,
	LOWER_COST,
	FAST_PLANT,
	IMPROVED_ATK_RATE,
	IMPROVED_EXPLODE_DAMAGE,
	IMPROVED_FLAME_DAMAGE,
	IMPROVED_COLD_DAMAGE,
	IMPROVED_LIGHTNING_DAMAGE,
	IMPROVED_MAGIC_DAMAGE,
	WATER_MASTER,
    INVINCIBLE,
    GHOST,
    PLANT_SUN_REFUND,
	IMPROVE_POISON,
	STUN_ZOMBIE_ON_EATEN,
	CREATE_PLANTFOOD_ON_KILL,
	CREATE_SUNMONEY_ON_KILL,
	CREATE_COIN_ON_KILL,
	CLEAR_PLANTING,
	REDUCEDAMAGE_AFTERTOKE,
	SLING_SHOT,
	TRUE_DAMAGE_APPEND,
	FROZEN_EXTEND,
	STUNNED_EXTEND,
	STUCKED_EXTEND,
	BUTTERED_EXTEND,
	Extra_PLANTFOOD_RATE,

	PlantBoostType_Max
};

typedef RtWeakPtr<class PlantBoostPropertySheet> PlantBoostPropertySheetPtr;

struct PlantBoost
{
    PlantBoost()
    {
        
    }
    
    PlantBoostPropertySheetPtr PlantBoostProps;
    // Improved value
    std::vector<float> Values;
};

class PlantBoostPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantBoostPropertySheet, PropertySheetBase, RtClass);

	PlantBoostPropertySheet()
	{
		Type = NONE;
	}
	
	PlantBoostType Type;
};

#endif // __PLANT_BOOST_PROPERTY_SHEET_H__
