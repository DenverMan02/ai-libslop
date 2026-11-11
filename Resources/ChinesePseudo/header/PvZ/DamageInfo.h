//
//  DamageInfo.h
//  PlantsVersusZombies2
//
//  Created by jsola on 9/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DamageInfo_h
#define PlantsVersusZombies2_DamageInfo_h

#include "Core.h"
#include "ZombieEnums.h"
#include "GridItemConditionTracker.h"
#include "Point.h"

enum DamageTypeFlags : std::int64_t
{
	PVZ_BEGIN_FLAG_ENUM(DAMAGE_),
	
    PVZ_FLAG(DAMAGE_NONE),
	PVZ_FLAG(DAMAGE_FATAL),
    PVZ_FLAG(DAMAGE_INSTANTLY_FATAL),
	PVZ_FLAG(DAMAGE_BYPASSES_SHIELD),
    PVZ_FLAG(DAMAGE_BYPASSES_ONE_SHIELD_LAYER),
	PVZ_FLAG(DAMAGE_HITS_SHIELD_AND_BODY),
	PVZ_FLAG(DAMAGE_HITS_ONLY_SHIELD),
	PVZ_FLAG(DAMAGE_LIGHTNING),
	PVZ_FLAG(DAMAGE_DOESNT_CAUSE_FLASH),
	PVZ_FLAG(DAMAGE_PREVENT_DEATH_SPAWNS),
	PVZ_FLAG(DAMAGE_HAS_FIRE),
	PVZ_FLAG(DAMAGE_FROM_LOBBED),
	PVZ_FLAG(DAMAGE_ASH_ON_DEATH),
	PVZ_FLAG(DAMAGE_FROM_PLANTFOOD_EFFECT),
	PVZ_FLAG(DAMAGE_FROM_MOWER),
    PVZ_FLAG(DAMAGE_PROPAGATED),
    PVZ_FLAG(DAMAGE_DOESNT_CAUSE_SOUND),
	PVZ_FLAG(DAMAGE_FROM_CUKE),
    PVZ_FLAG(DAMAGE_FROM_EATING),
    PVZ_FLAG(DAMAGE_FROM_SPINNING),
    PVZ_FLAG(DAMAGE_FROM_MECH),
    PVZ_FLAG(DAMAGE_FROM_CRUSHING),
    PVZ_FLAG(DAMAGE_FRIENDLY_FIRE),
    PVZ_FLAG(DAMAGE_FROM_MAGNET),
    PVZ_FLAG(DAMAGE_FROM_CATAPULT),
    PVZ_FLAG(DAMAGE_SQUIDIFY),
    PVZ_FLAG(DAMAGE_HITS_SUBMERGED),
    PVZ_FLAG(DAMAGE_FROST_TINY),
    PVZ_FLAG(DAMAGE_FROST_MODERATE),
    PVZ_FLAG(DAMAGE_FROST_STAGE),
    PVZ_FLAG(DAMAGE_FROST_FREEZE),
    PVZ_FLAG(DAMAGE_THAW_TINY),
    PVZ_FLAG(DAMAGE_THAW_MODERATE),
    PVZ_FLAG(DAMAGE_THAW_STAGE),
    PVZ_FLAG(DAMAGE_ACID),
    PVZ_FLAG(DAMAGE_ARTIFACT_ACID),
    PVZ_FLAG(DAMAGE_HEALS_ICEBLOCKS),
	PVZ_FLAG(DAMAGE_FROM_SHOOTER),
    PVZ_FLAG(DAMAGE_FROM_MELEE),
    PVZ_FLAG(DAMAGE_SUICIDE),
    PVZ_FLAG(DAMAGE_SMASH),
    PVZ_FLAG(DAMAGE_DROWN),
    PVZ_FLAG(DAMAGE_SHOVEL),
    PVZ_FLAG(DAMAGE_REMOVED_FROM_BOARD),
    PVZ_FLAG(DAMAGE_PLANTIFY_ON_DEATH),
    PVZ_FLAG(DAMAGE_NO_BLEED_ON_DEATH),
    PVZ_FLAG(DAMAGE_MAGIC),
    PVZ_FLAG(DAMAGE_POISON),
    PVZ_FLAG(DAMAGE_COLD),
    PVZ_FLAG(DAMAGE_ELECTRIC),
	PVZ_END_FLAG_ENUM(DAMAGE_),
    
    DAMAGE_ANY_FROST = DAMAGE_FROST_TINY | DAMAGE_FROST_MODERATE | DAMAGE_FROST_STAGE | DAMAGE_FROST_FREEZE | DAMAGE_THAW_TINY | DAMAGE_THAW_MODERATE | DAMAGE_THAW_STAGE,
    DAMAGE_NON_ZOMBIE = DAMAGE_SUICIDE | DAMAGE_DROWN | DAMAGE_SHOVEL | DAMAGE_REMOVED_FROM_BOARD,
    DAMAGE_INSTANT_KILL = DAMAGE_FATAL | DAMAGE_INSTANTLY_FATAL,
    DAMAGE_PHYSICAL = DAMAGE_NONE | DAMAGE_FROM_MELEE | DAMAGE_FROM_SHOOTER | DAMAGE_SMASH | DAMAGE_BYPASSES_SHIELD | DAMAGE_BYPASSES_ONE_SHIELD_LAYER
    | DAMAGE_HITS_SHIELD_AND_BODY | DAMAGE_HITS_ONLY_SHIELD | DAMAGE_FROM_LOBBED | DAMAGE_FROM_CATAPULT,
    DAMAGE_MAGICAL = DAMAGE_MAGIC,
    DAMAGE_ANY_FLAME = DAMAGE_HAS_FIRE,
    DAMAGE_ANY_LIGHTNING = DAMAGE_LIGHTNING | DAMAGE_ELECTRIC,
    DAMAGE_ANY_POISON = DAMAGE_POISON,
    DAMAGE_ANY_COLD = DAMAGE_COLD,
    DAMAGE_ALL = 0x7fffffffffffffff,
};
PVZ_MAKE_ENUM_BIT_OPERATORS(DamageTypeFlags);

struct ZombieConditionInfo
{
	ZombieConditionInfo()
	{
		Condition = ZCONDITION_Chilled;
	}
	std::vector<std::string> BlackList;
	ZombieConditions Condition;
};

struct ResilienceDamageInfo
{
	ResilienceDamageInfo()
	: BaseDamage(0.0f)
	, ExtraDamage(0.0f)
	{

	}

	ResilienceDamageInfo(float i_baseDamage, float i_extraDamage)
	: BaseDamage(i_baseDamage)
	, ExtraDamage(i_extraDamage)
	{

	}

	float BaseDamage;
	float ExtraDamage;
};

struct DamageInfo
{
	DamageInfo()
		: Amount(0.f)
		, Instigator(NULL)
		, Flags(DAMAGE_NONE)
        , DamageGrid(Sexy::Point{-1, -1})
		, ResilienceDamage(ResilienceDamageInfo{1.0f, 0.0f})
	{}
	
    DamageInfo(float i_amount, Sexy::Point dp = {-1, -1}, ResilienceDamageInfo info = {1.0f, 0.0f})
		: Amount(i_amount)
		, Instigator(NULL)
		, Flags(DAMAGE_NONE)
        , DamageGrid(dp)
        , ResilienceDamage(info)
	{}
	
	DamageInfo(float i_amount, class BoardEntity* i_instigator, Sexy::Point dp = {-1, -1}, ResilienceDamageInfo info = {1.0f, 0.0f})
		: Amount(i_amount)
		, Instigator(i_instigator)
		, Flags(DAMAGE_NONE)
        , DamageGrid(dp)
        , ResilienceDamage(info)
	{}
	
	DamageInfo(float i_amount, DamageTypeFlags i_flags, Sexy::Point dp = {-1, -1}, ResilienceDamageInfo info = {1.0f, 0.0f})
		: Amount(i_amount)
		, Instigator(NULL)
		, Flags(i_flags)
        , DamageGrid(dp)
        , ResilienceDamage(info)
	{}
	
	DamageInfo(float i_amount, DamageTypeFlags i_flags, class BoardEntity* i_instigator, Sexy::Point dp = {-1, -1}, ResilienceDamageInfo info = {1.0f, 0.0f})
		: Amount(i_amount)
		, Instigator(i_instigator)
		, Flags(i_flags)
        , DamageGrid(dp)
        , ResilienceDamage(info)
	{}
	
	void AddCondition(ZombieConditions i_condition, float i_duration = 0.f)
	{
		ZombieConditionInfo conditionInfo;
		conditionInfo.Condition = i_condition;
		Conditions.push_back(std::pair<ZombieConditionInfo, float>(conditionInfo, i_duration));
	}

	void AddCondition(ZombieConditionInfo i_condition, float i_duration = 0.f)
	{
		Conditions.push_back(std::pair<ZombieConditionInfo, float>(i_condition, i_duration));
	}
    
    void AddCondition(GridItemConditions i_condition, float i_duration = 0.f)
    {
    	RemoveGridItemCondition(i_condition);
        GridItem_Conditions.push_back(std::pair<GridItemConditions, float>(i_condition, i_duration));
    }
    
    int GetFrostAmount() const;
    
    bool ObtainZombieCondition(ZombieConditions zcValue) const
    {
        for (auto& e : Conditions)
        {
        	const auto& info = e.first;
            if (info.Condition == zcValue)
            {
                return true;
            }
        }
        
        return false;
    }
    
    void RemoveZombieCondition(ZombieConditions zcValue)
    {
        std::vector<std::pair<ZombieConditionInfo, float> >::iterator itr = Conditions.begin();
        for (; itr != Conditions.end(); )
        {
        	const auto& info = itr->first;
            if (info.Condition == zcValue)
                Conditions.erase(itr);
            else
                ++itr;
        }
    }

    void RemoveGridItemCondition(GridItemConditions zcValue)
    {
        std::vector<std::pair<GridItemConditions, float> >::iterator itr = GridItem_Conditions.begin();
        for (; itr != GridItem_Conditions.end(); )
        {
        	const auto& info = itr->first;
            if (info == zcValue)
            	GridItem_Conditions.erase(itr);
            else
                ++itr;
        }
    }
	
	class BoardEntity* 	Instigator;
	float 				Amount;
	DamageTypeFlags		Flags;
    Sexy::Point         DamageGrid;
	//std::vector<std::pair<ZombieConditions, float> > Conditions;
    std::vector<std::pair<ZombieConditionInfo, float> > Conditions;
    std::vector<std::pair<GridItemConditions, float> > GridItem_Conditions;
    ResilienceDamageInfo ResilienceDamage;
};

#endif
