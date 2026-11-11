#pragma once

#include "core.h"

typedef Sexy::RtWeakPtr<class Plant> PlantPtr;
typedef Sexy::RtWeakPtr<class PlantGroup> PlantGroupPtr;

enum PlantGridPlantingType
{
	PLANT_GRID_PLANTING_GROUND,
	PLANT_GRID_PLANTING_WATER,
	PLANT_GRID_PLANTING_ANY,
};

enum MultiPlantGridLayer
{
    MULTI_PLANT_GRID_LAYER_ARMOR,
    MULTI_PLANT_GRID_LAYER_MAIN,
    MULTI_PLANT_GRID_LAYER_GROUND,
    
    MULTI_PLANT_GRID_LAYER_POWER,
    MULTI_PLANT_GRID_LAYER_EFFECT,  // Plant has become an effect.  For example, when Imitater spawns another plant, it remains on the board and acts more like an effect.
    
    MULTI_PLANT_GRID_LAYER_TARGETABLE_MAX = MULTI_PLANT_GRID_LAYER_GROUND,
    MULTI_PLANT_GRID_LAYER_MAX = MULTI_PLANT_GRID_LAYER_EFFECT
};

enum PlantActionType
{
	PLANT_ACTION_PROJECTILE,
	PLANT_ACTION_EXPLODE,
	PLANT_ACTION_PRODUCE_SUN,
	PLANT_ACTION_SPECIAL,
    PLANT_ACTION_CURE,
	PLANT_ACTION_NONE = -1,
};

enum SplashDamageType
{
    SPLASH_DAMAGE_EXPLODE_RADIUS,
    SPLASH_DAMAGE_EXPLODE_LARGE_RADIUS,
	SPLASH_DAMAGE_EXPLODE_ROW,
	SPLASH_DAMAGE_EXPLODE_COLUMN,
	SPLASH_DAMAGE_EXPLODE_SQUARE,
	SPLASH_DAMAGE_EXPLODE_ENEMY,
	SPLASH_DAMAGE_EXPLODE_NONE = -1,
};

enum PlantActionTriggerType
{
	PLANT_ACTION_TRIGGER_INSTANT,
	PLANT_ACTION_TRIGGER_COLUMN,
	PLANT_ACTION_TRIGGER_ROW,
	PLANT_ACTION_TRIGGER_RECT,
    PLANT_ACTION_TRIGGER_GRID_RECT,
    PLANT_ACTION_TRIGGER_MANUAL,
    PLANT_ACTION_TRIGGER_ENTIRE_BOARD,
	PLANT_ACTION_TRIGGER_NONE = -1,
};

enum PlantAvatarType
{
    E_AVATAR_ILLEGAL = -2,
	E_AVATAR_NONE = -1,
	E_AVATAR_NORMAL,
	E_AVATAR_ALL
};

enum PlantConditions
{
	PVZ_BEGIN_ENUM(PCONDITION_),
	PCONDITION_RapidFire,
	PCONDITION_Squidified,
    PCONDITION_Sheeped,
	PCONDITION_DamageFlash,
	PCONDITION_PlantfoodFlash,
	PCONDITION_Highlighted,
	PCONDITION_Icecubed,
	PCONDITION_FrostStage1,
	PCONDITION_FrostStage2,
    PCONDITION_Positive,
    PCONDITION_Negative,
    PCONDITION_Paralysis,
    PCONDITION_Burning,
    PCONDITION_SlowDown,
    PCONDITION_MoreSlowDown,
    PCONDITION_NotFiring,
    PCONDITION_Sauced,
    PCONDITION_StunnedByZombieLove,
    PCONDITION_Stunned,
    PCONDITION_ShadowBoosted,
    PCONDITION_Ghost,
    PCONDITION_Swapping,
    PCONDITION_LiftedOff,
	PCONDITION_Smoke,
	PCONDITION_TrappedInNet,
	PCONDITION_WrappedInWormHole,
	PCONDITION_DamageReduction,
	PCONDITION_LemonRain,
	PCONDITION_AppendTrueDamage,
	PCONDITION_Transformed,
	PCONDITION_AntiInjury,
	PCONDITION_DripWater,
	PCONDITION_ImproveFlameDamage,

	// Conditions propagated to group when topmost plant is affected.
    PCONDITION_GroupIcecubed,
    PCONDITION_GroupSquidified,
    PCONDITION_GroupSheeped,
    PCONDITION_GroupTrappedInNet,
    PCONDITION_GroupSauced,
	PCONDITION_GroupStunned,
    
    // Conditions propagated to group when any plant is affected
    PCONDITION_GroupPlantfooded,

    PCONDITION_BeingCharged,

	PVZ_END_ENUM(PCONDITION_)
};

enum PlantProfessions
{
	PVZ_BEGIN_ENUM(PROFESSION_),
	PROFESSION_Shooter,
	PROFESSION_Warrior,
	PROFESSION_Supporter,
	PROFESSION_Protector,
	PROFESSION_Sunmaker,
	PROFESSION_Specialist,
	PVZ_END_ENUM(PROFESSION_)
};

enum PlantDetailsType
{
	PVZ_BEGIN_ENUM(PDetails_),
	PDetails_SunCost,
	PDetails_Cooldown,
	PDetails_Hitpoint,
	PDetails_Damage,
	PDetails_AttackInterval,
	PDetails_Range,
	PDetails_Area,
	PDetails_Duration,
	PDetails_Rest,
	PDetails_Yield,
	PDetails_YieldInterval,
	PVZ_END_ENUM(PDetails_)
};

namespace PlantConstants
{
    const int LevelMax = 5;
};



enum PlantAdditionType
{
	PVZ_BEGIN_ENUM(PAddition_),
	PAddition_HeroPlant_Grade_AttackUp,
	PAddition_Armorflame_Self_AttackUP,
	PAddition_Armorflame_Talent_SpeedUP,
	PVZ_END_ENUM(PAddition_)
};



