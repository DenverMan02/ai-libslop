#ifndef __ZOMBIEENUMS_H__
#define __ZOMBIEENUMS_H__

#include "Precompile.h"
#include "Core.h"

const int ZOMBIE_WAVE_DEBUG = -1;
const int ZOMBIE_WAVE_CUTSCENE = -2;
const int ZOMBIE_WAVE_UI = -3;
const int ZOMBIE_WAVE_WINNER = -4;
const int ZOMBIE_WAVE_SPECIAL = -5;
const float CHILLED_SPEED_FACTOR = 0.4f;

enum CollisionTypeFlags
{
	PVZ_BEGIN_FLAG_ENUM(COLLIDE_),
	
	PVZ_FLAG(COLLIDE_GROUND_ZOMBIES),
	PVZ_FLAG(COLLIDE_OFF_GROUND_ZOMBIES),
	PVZ_FLAG(COLLIDE_DYING_ZOMBIES),
	PVZ_FLAG(COLLIDE_GRIDITEMS),
    PVZ_FLAG(COLLIDE_ON_GROUND_PLANTS),
    PVZ_FLAG(COLLIDE_LOW_PLANTS),
    PVZ_FLAG(COLLIDE_NORMAL_PLANTS),
    PVZ_FLAG(COLLIDE_TALL_PLANTS),
	PVZ_FLAG(COLLIDE_GROUND),
//PVZ2_CHINESE_BEGIN
    PVZ_FLAG(COLLIDE_FLAME_GRIDITEMS),
//PVZ2_CHINESE_END
	
	PVZ_END_FLAG_ENUM(COLLIDE_),
	
    COLLIDE_ALL_PLANTS = COLLIDE_ON_GROUND_PLANTS | COLLIDE_LOW_PLANTS | COLLIDE_NORMAL_PLANTS | COLLIDE_TALL_PLANTS,
	COLLIDE_ALL_ZOMBIES = COLLIDE_GROUND_ZOMBIES | COLLIDE_OFF_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES
};
PVZ_MAKE_ENUM_BIT_OPERATORS(CollisionTypeFlags);


enum ArmorTypeFlags
{
	PVZ_BEGIN_FLAG_ENUM(ARMOR_),
	PVZ_FLAG(ARMOR_METALLIC),
	PVZ_FLAG(ARMOR_DAMAGEABLE),
	PVZ_FLAG(ARMOR_DROPPABLE),
	PVZ_FLAG(ARMOR_PASSDAMAGE),
	PVZ_FLAG(ARMOR_ABSORBOVERFLOW),
	PVZ_FLAG(ARMOR_BODY),
	PVZ_FLAG(ARMOR_HELM),
	PVZ_FLAG(ARMOR_INVINCIBLE),

	PVZ_END_FLAG_ENUM(ARMOR_),
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ArmorTypeFlags);

enum HelmType
{
	HELMTYPE_NONE,
	HELMTYPE_CONE,
	HELMTYPE_BUCKET,
    HELMTYPE_HELMET,
	HELMTYPE_SARCOPHAGUS,
	HELMTYPE_CAMELSIGN,
	HELMTYPE_PONCHO,
	HELMTYPE_METALPLATE,
	HELMTYPE_COWBOYHAT,
	HELMTYPE_STICK,
    HELMTYPE_CROWN,
    HELMTYPE_SURFBOARD,
    HELMTYPE_SHELL,
    HELMTYPE_ICEBLOCK,
    HELMTYPE_ICECRUST_ZOMBOSS,
    HELMTYPE_SHOVEL,
	HELMTYPE_NEWSPAPER,
	HELMTYPE_MINING_TOOL,
	HELMTYPE_COAL_TRUCK,
    HELMTYPE_GLIDING,
    HELMTYPE_BRICK,
	HELMTYPE_BOX,

};



enum ZombieRenderLayerOffset
{
	ZOMBIE_LAYER_OFFSET_BENEATH_ALL, 	// This should be the first entry...
	ZOMBIE_LAYER_OFFSET_NORMAL,
	ZOMBIE_LAYER_OFFSET_ABOVE_ALL,		// ... and this should be the last!
};

enum ZombieConditions
{
	PVZ_BEGIN_ENUM(ZCONDITION_),
	ZCONDITION_Chilled,
	ZCONDITION_Frozen,
	ZCONDITION_Stunned,
	ZCONDITION_Buttered,
	ZCONDITION_Buttered9,
	ZCONDITION_Bleeding,
    ZCONDITION_LightningAura,
    ZCONDITION_RushOnscreen,
	ZCONDITION_SpeedUp1,
	ZCONDITION_SpeedUp2,
	ZCONDITION_SpeedUp3,
	ZCONDITION_SpeedUp4,
    ZCONDITION_SpeedUp5,
    ZCONDITION_SpeedUp6,
    ZCONDITION_Tossed,
    ZCONDITION_Stabbed,
    ZCONDITION_Water,
    ZCONDITION_WarpingIn,
    ZCONDITION_ZombiePotionSpeed1,
	ZCONDITION_ZombiePotionSpeed2,
	ZCONDITION_ZombiePotionSpeed3,
	ZCONDITION_ZombiePotionToughness1,
	ZCONDITION_ZombiePotionToughness2,
	ZCONDITION_ZombiePotionToughness3,
    //zhaobk added, use stuck for old stun effect
    ZCONDITION_Stucked,
    ZCONDITION_Hypnotized,
    ZCONDITION_ToxicWater,
    ZCONDITION_Sunbeaned,
    ZCONDITION_MorphedToGargantuar,
    ZCONDITION_Knighted,
    ZCONDITION_HasPlantfood,
    ZCONDITION_DamageFlash,
    ZCONDITION_ZombossStun,
    ZCONDITION_Haunted,
    ZCONDITION_ImpatiensBind_1,
    ZCONDITION_ImpatiensBind_2,
    ZCONDITION_Hungered,
    ZCONDITION_StoneBlocked,
    ZCONDITION_StoneBlocked_1,
    ZCONDITION_Icecubed,
    ZCONDITION_Sapped,
    ZCONDITION_Amber,
    ZCONDITION_BlueEffect,  //for snake slow down
    ZCONDITION_Unsuspendable,
    ZCONDITION_PresentBoxed,
    ZCONDITION_Stalled,
    //ZCONDITION_SpeedDown1,
    //ZCONDITION_SpeedDown2,
    //ZCONDITION_SpeedDown3,
    //ZCONDITION_SpeedDown4,
    ZCONDITION_Invincible,
    ZCONDITION_Poisoned,
    ZCONDITION_ShadowPoisoned,
    ZCONDITION_Venom,                          // snake poisoned
	ZCONDITION_OnFire,
	ZCONDITION_Slowdown,
	ZCONDITION_Superslowdown,
    ZCONDITION_Burn,
    ZCONDITION_BlueBurn,
    ZCONDITION_Blocked,
    ZCONDITION_Numb,
    ZCONDITION_Binded,
    //For Eliminate
    ZCONDITION_Colored,
    ZCONDITION_Minify,
    ZCONDITION_Electrocute,                     // maybee electr condition is different ZS_Electrocute!
    ZCONDITION_Rage,
    ZCONDITION_Select,
    ZCONDITION_WarpingOut,
    ZCONDITION_Shrinking,
    ZCONDITION_Shrunken,
    ZCONDITION_HocusCrocusShrinking,			// adv: target scale, exv: shrunk duration, exv2: shrinking duration
    ZCONDITION_HocusCrocusShrunken,				// adv: target scale, exv: shrink recovering duration
    ZCONDITION_HocusCrocusShrinkRecovering,		// adv: initial scale
    ZCONDITION_Syringe,
    ZCONDITION_Terrified,
    ZCONDITION_ContagiousPoison,
    ZCONDITION_BloomingHeartDebuff,
    ZCONDITION_BloomingHeartFocusFireDebuff,
    ZCONDITION_Leader, //Tiger added for leader zombie in endless mode
    ZCONDITION_Slimed,
    ZCONDITION_ChemistPoison,
    ZCONDITION_ChemistVenom,
    ZCONDITION_ChemistContagiousPoison,
    ZCONDITION_LotusPoison,
    ZCONDITION_Confusion,
    ZCONDITION_ShadowMist,
    ZCONDITION_Gluttonous,
    ZCONDITION_BadSmell,
    ZCONDITION_BadSmellPoison,
    ZCONDITION_Gummed,
    ZCONDITION_FireVulnerable,
    ZCONDITION_StickyBombed,
    ZCONDITION_Radiated,
    ZCONDITION_CureUp,// full health
    ZCONDITION_CureShield,// invincible
    ZCONDITION_Positive,
    ZCONDITION_Negative,
    ZCONDITION_Artifact_Bleeding,
    ZCONDITION_Artifact_Stunning,
    ZCONDITION_Artifact_Slowing,
    ZCONDITION_ThemeShrunken,
    ZCONDITION_ZombiePotionInvisible,
    ZCONDITION_ZombiePotionPoison,
    ZCONDITION_ZombieBuffSpeed,
    ZCONDITION_ZombieBuffAttack,
    ZCONDITION_Squidified,
    ZCONDITION_Snowed,
    ZCONDITION_InvisibleSlow,
    ZCONDITION_LemonRain,
    ZCONDITION_HeavyShield,
    ZCONDITION_FogShieldLvl1,
    ZCONDITION_FogShieldLvl2,
    ZCONDITION_FogShieldLvl3,
    ZCONDITION_FogWindSlow,
    ZCONDITION_Berserk,
    ZCONDITION_FastSpell,
    ZCONDITION_Sheeped,
    ZCONDITION_CardGameInvisible,
    ZCONDITION_CardGameShield,
    ZCONDITION_Sleepy,
    ZCONDITION_DripWater,
    ZCONDITION_Artifact_Burning,
    ZCONDITION_Artifact_PercentBurning,
    ZCONDITION_GhostLantern,
    ZCONDITION_New_PVP_Upgrade_SpeedUp,
    ZCONDITION_New_PVP_Upgrade_HP,
    ZCONDITION_New_PVP_Upgrade_Berserk,
    ZCONDITION_Merge,
    ZCONDITION_Merged,
    ZCONDITION_AffectEatDPS,
    ZCONDITION_BeanChemist_Posion,
    ZCONDITION_Goldlization,
    ZCONDITION_Artifact_Acid,
    ZCONDITION_Devouring,
    ZCONDITION_ImmuneControl,
    ZCONDITION_CthulhuActinia,
    ZCONDITION_DevilsParasite,
    ZCONDITION_DevilsSuperParasite,
    ZCONDITION_OIL,
    ZCONDITION_OILFIRE,
    ZCONDITION_VulnerableFire,
    ZCONDITION_HighFire,
	PVZ_END_ENUM(ZCONDITION_)
};

// DBG_ASSERTSTATIC(ZCONDITION_Count <= 64);

extern std::string ConvertZombieConditionToString(ZombieConditions);

enum ZombieTossedPower
{
    PVZ_BEGIN_ENUM(ZOMBIETOSSED_),
    ZOMBIETOSSED_STRONG,
    ZOMBIETOSSED_WEAK,
    PVZ_END_ENUM(ZOMBIETOSSED_)
};

enum ZombieSpawnPattern
{
	PVZ_BEGIN_ENUM(ZOMBIESPAWNPATTERN_),
	ZOMBIESPAWNPATTERN_BLOCKER,		// A single zombie in front of the hero.
	ZOMBIESPAWNPATTERN_VERTICAL,	// Three zombies vertically centered on the hero.
	ZOMBIESPAWNPATTERN_HORIZONTAL,	// Three zombies in the same row and in front of the hero.
	ZOMBIESPAWNPATTERN_SQUARE,		// Square with the hero at the center.
	ZOMBIESPAWNPATTERN_DIAMOND,		// Diamond with the hero at the center.
	PVZ_END_ENUM(ZOMBIESPAWNPATTERN_),
};

enum ZombieSkillType
{
    ZOMBIE_SKILL_SUMMON,
	ZOMBIE_SKILL_PULL,
	ZOMBIE_SKILL_JUMP,
	ZOMBIE_SKILL_DASH,
	ZOMBIE_SKILL_NONE = -1,
};

enum ZombieActionType
{
	ZOMBIE_ACTION_EXPLODE,
    ZOMBIE_ACTION_SUMMON,
	ZOMBIE_ACTION_SPECIAL,
	ZOMBIE_ACTION_NONE = -1,
};

enum ZombieExplodeType
{
	ZOMBIE_EXPLODE_3X3,
	ZOMBIE_EXPLODE_5X5,
	ZOMBIE_EXPLODE_ROW,
	ZOMBIE_EXPLODE_COLUMN,
	ZOMBIE_EXPLODE_NONE = -1,
};

enum ZombieSummonType
{
	ZOMBIE_SUMMON_RISEFROMGROUND,
	ZOMBIE_SUMMON_PLACEONBOARD,
	ZOMBIE_SUMMON_NONE = -1,
};

enum ZombieSizeType
{
    ZOMBIE_SIZE_SMALL,
    ZOMBIE_SIZE_MID,
    ZOMBIE_SIZE_BIG,
    SIZE
};

enum ZombieTestFlag
{
    PVZ_BEGIN_FLAG_ENUM(ZT_),
    PVZ_FLAG(ZT_DYING),
    PVZ_FLAG(ZT_OPPOSING_TEAM),
    PVZ_FLAG(ZT_SAME_TEAM),
    PVZ_FLAG(ZT_BLEEDING_OUT),
    PVZ_FLAG(ZT_TARGETABLE),
    PVZ_FLAG(ZT_NOT_TARGETABLE),
    PVZ_FLAG(ZT_PLANT_CAN_TARGET_ZOMBIE),
    PVZ_FLAG(ZT_PLANT_CANNOT_TARGET_ZOMBIE),
    PVZ_FLAG(ZT_ON_SCREEN),
    PVZ_FLAG(ZT_OFF_SCREEN),
    PVZ_FLAG(ZT_ZOMBIE_CAN_BE_TARGETED_BY_PLANT),
    PVZ_FLAG(ZT_ZOMBIE_CANNOT_BE_TARGETED_BY_PLANT),
    PVZ_FLAG(ZT_COLLIDES_WITH_PLANT),
    PVZ_FLAG(ZT_DOES_NOT_COLLIDE_WITH_PLANT),
    PVZ_FLAG(ZT_IN_ROW),
    PVZ_FLAG(ZT_NOT_IN_ROW),
    PVZ_FLAG(ZT_MARKED_FOR_DEATH),
    PVZ_FLAG(ZT_INVISIBLE),
    PVZ_END_FLAG_ENUM(ZT_),
    
    ZT_STANDARD_IGNORED = ZT_DYING | ZT_BLEEDING_OUT | ZT_SAME_TEAM | ZT_NOT_TARGETABLE
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ZombieTestFlag);

enum ZombieSpawnFlags
{
	PVZ_BEGIN_FLAG_ENUM(ZOMBIE_SPAWN_),
	PVZ_FLAG(ZOMBIE_SPAWN_AllowFlagZombie),
	PVZ_FLAG(ZOMBIE_SPAWN_AllowHolidaySwaps),
    PVZ_FLAG(ZOMBIE_SPAWN_AllowZombieOverrides),
	PVZ_END_FLAG_ENUM(ZOMBIE_SPAWN_),

	ZOMBIE_SPAWN_DEFAULT = ZOMBIE_SPAWN_AllowHolidaySwaps | ZOMBIE_SPAWN_AllowZombieOverrides,
	ZOMBIE_SPAWN_ANYTIME = ZOMBIE_SPAWN_AllowHolidaySwaps | ZOMBIE_SPAWN_AllowZombieOverrides,
	ZOMBIE_SPAWN_WAVE	 = ZOMBIE_SPAWN_AllowFlagZombie | ZOMBIE_SPAWN_AllowHolidaySwaps | ZOMBIE_SPAWN_AllowZombieOverrides,
    ZOMBIE_SPAWN_NO_OVERRIDES = ZOMBIE_SPAWN_AllowHolidaySwaps,
	ZOMBIE_SPAWN_NON_HOLIDAY = ZOMBIE_SPAWN_None
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ZombieSpawnFlags);

enum InvisibleState
{
    Not_Invisible,
    Invoke_Invisible,
    Invisible_Not_Detected,
    Invisible_Detected,
};

enum StreetLampChangeState
{
    Light_Up,
    Light_Down,
    Light_Fade,
};

namespace ZombieConstants
{
    const int LevelMax = 10;
}

enum EliteZombie_Type
{
    EliteZombie_Invalid = -1,
    EliteZombie_Artifact = 0,// artifact battle
    EliteZombie_PVZ1_Normal,// pvz1 mode normal
    ElizeZombie_PVZ1_Hard,// pvz1 mode hard
    EliteZombie_Max,
};

#endif

