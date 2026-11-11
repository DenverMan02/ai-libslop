//
//  BoardEnums.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/13/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_BoardEnums_h
#define PlantsVersusZombies2_BoardEnums_h

enum GridSquareType
{
	GRIDSQUARE_NONE,
	GRIDSQUARE_GRASS,
	GRIDSQUARE_DIRT,
	GRIDSQUARE_WATER,
	GRIDSQUARE_RAIL,
	GRIDSQUARE_FUTURETILE,
	GRIDSQUARE_GEAR,
    GRIDSQUARE_TD_ROAD,
    GRIDSQUARE_TD_PLANTED,
    GRIDSQUARE_WORLDCUP,
    GRIDSQUARE_ROOF,
    GRIDSQUARE_CONCRETE,
    GRIDSQUARE_OPPOENT,
    GRIDSQUARE_DISABLED_AREA
};

enum PlantRowType
{
	PLANTROW_DIRT,
	PLANTROW_NORMAL,
};

// PlantingReason
//	- This is the list of reasons why user-initiated planting might fail
//	- This list must be ordered, from least-significant reason to most
//	- If multiple reasons exist for not planting, the reason furthest down this list will be messaged
enum PlantingReason
{
    PLANTING_OK,										// No problem, plant away!
    
    // Low-importance reasons
    //	- These reasons are temporary or otherwise unimportant to the player. If better advice
    //	exists, we should display that instead.
    PLANTING_GRIDSQUARE_LOCKED,							// This gridsquare is temporarily locked for planting
    
    // Plant-specific reasons
    PLANTING_NOT_HERE,
    PLANTING_TILE_PLANTS_ON_TILES,						// Tile Turnip and Gold Tile Turnip cannot be planted on gold tiles or powertiles
    PLANTING_ONLY_ON_GRAVES,							// GraveBuster can only be placed on a gravestone
    PLANTING_HOTPOTATO_ONLY_ON_ICEBLOCKS,				// Hotpotato can only be placed on iceblocks
    PLANTING_GRAVEBUSTER_CANT_EAT,						// GraveBuster cannot eat this gravestone for some reason! TODO -- Flesh this out!
    PLANTING_LILYPAD_ON_DRY_SAND,						// Lilypad cannot be placed on dry sand (that the tide will never reach)
    PLANTING_NOT_ON_LAVA,								// Can't plant on a lava puddle left by Lava Guava
    PLANTING_NOT_ON_LOLLIPOPS,
    PLANTING_NOT_ON_LILYPAD,							// Can't plant underground plants on lilypads
    PLANTING_ESCAPEROOT_CANT_PLANT_HERE,				// Catchall for "can't swap to a non-plantable location"
    PLANTING_ESCAPEROOT_CANT_SWAP_THIS_PLANT,			// Target plant is blacklisted
    PLANTING_ESCAPEROOT_CANT_SWAP_PLANTFOODED_PLANTS,	// Because we don't want to deal with moving PF effects
    PLANTING_ESCAPEROOT_CANT_SWAP_AFFECTED_PLANTS,		// Target plant is sheeped or squidified
    PLANTING_ESCAPEROOT_CANT_SWAP_WATER_PLANTS,
    // Stage-module specific reasons
    PLANTING_NOT_ON_GRAVE,					// Non-gravebusters cannot be placed on gravestones
    PLANTING_NOT_ON_ICEBLOCKS,				// No planting on ice blocks
    PLANTING_NOT_ON_CRATERS,				// No planting on craters
    PLANTING_NOT_ON_WATER,					// No plants can be placed in the water on Pirate stages
    PLANTING_NOT_ON_SURFBOARD,				// No planting on surfboards.
    PLANTING_NOT_ON_TENT,					// No planting on Lost City tents
    PLANTING_NEEDS_GROUND,
    PLANTING_NOT_ON_ARCADE_MACHINE,			// No planting on eighties arcade cabinet
    PLANTING_NOT_ON_BACKPACK,				// No planting on Lost City backpacks
    PLANTING_NOT_ON_SPEAKER,				// No planting on Eighties speakers
    PLANTING_POTATOMINE_ON_PLANKS,			// Potatomines can't be placed on planks
    PLANTING_NOT_ON_RAIL,					// No plants can be placed on a non-railcart'ed rail
    PLANTING_NOT_ON_MOLD,					// No planting on my mold!
    PLANTING_NOT_ON_PLANKS,
    PLANTING_NOT_ON_RAIL_BAMBOO,
    PLANTING_NOT_ON_RAIL_MAGICBEANS,
    PLANTING_NOT_ON_GEAR,
    PLANTING_TOO_MANY_PLANTS,           	// Stage doesn't allow planting too many plants
    PLANTING_POWERPLANT_ON_POWERTILE,		// The Tile Turnip can't be placed on an existing power tile
    PLANTING_ZOMBIE_ON_RIGHT_REDLINE,
    PLANTING_NOT_ON_FLAMES,					// Don't plant on top of flames!
    PLANTING_NOT_ON_SHARKS,					// Can't plant on the school of sharks in beach zomboss level
    PLANTING_NOT_ON_KING,					// Nope.
    PLANTING_NOT_ON_FISHERMAN,				// Nope.
    PLANTING_NOT_ON_POTIONS,                // Can't plant on zombie potions
    PLANTING_NOT_ON_DUMPLING,               // Can't plant on griditem dumpling
    PLANTING_NOT_ON_TANGYUAN,               // Can't plant on griditem tangyuan
    PLANTING_NOT_ON_PIGBANK,               // Can't plant on griditem pigbank
    PLANTING_NOT_ON_PLANTSEED,              // Can't plant on griditem rift theme plantseed
    PLANTING_NOT_ON_ZOMBIE_CHANGER,          // Can't plant on griditem zombie changer
    PLANTING_NOT_ON_FIRECRACKER,            // Can't plant on griditem firecracker
    PLANTING_NOT_ON_ELECSHIELD_GENERATOR,   // Can't plant on griditem elecshieldgenerator
    PLANTING_NEED_LILYPAD_FIRST,			// Need a lilypad here before you can plant on the tide
    PLANTING_NOT_ON_TIDE,					// Can never be planted on the tide
    PLANTING_ONLY_ON_WAVES,					// Can only plant on waves (for tanglekelp)
    PLANTING_LILYPAD_ON_LILYPAD,			// Can't plant lilypads on lilypads
    PLANTING_TANGLEKELP_ON_LILYPAD,			// Can't plant tanglekelp on lilypad
    PLANTING_NOT_ON_VASES,					// Can't plant on vasebreaker vases
    PLANTING_NOT_IN_SKY,
    PLANTING_PLANT_ON_ROAD,
    PLANTING_POWERPLANT_ON_POOL,
    PLANTING_NOT_ON_GUN,
    PLANTING_BOWLING_OVER_THE_LINE,			// Can't plant a bowling bulb bulb past the planting line
    PLANTING_NEW_BOWLING_OVER_THE_LINE,      // Can't plant a new bowling game at right of line
    PLANTING_NO_BANANA_ON_RAILCART,			// Can't plant a banana on a railcart (due to conflicting touch issues)
    PLANTING_NO_JACKOLANTERN_ON_RAILCART,	// Can't plant a jack-o-lantern on a railcart (same reasoning as banana)
    PLANTING_NO_LAVAGUAVA_ON_RAILCART,		// Can't plant a lava guava on a railcart (design request, lava / railcarts bad)
    PLANTING_NO_ESCAPEROOT_ON_RAILCART,		// Can't plant an escape root on a railcart
    PLANTING_NOT_ON_SLIDER_TILE,			// Can't plant on a slider tile
    PLANTING_NOT_ON_WHACK_PUDDLE,			// Can't plant on a whack-a-zombie puddle
    PLANTING_NOT_ON_BESIEGE_BOX,
    PLANTING_BESIEGE_BOX_NOT_HERE,
    PLANTING_BESIEGE_BOX_NOT_ON_ZOMBIE,
    PLANTING_BESIEGE_BOX_IN_TUTORIAL_POINT,
    PLANTING_ON_BESIEGE_BOX,
    PLANTING_PLANT_ON_RIGHT_REDLINE,
    PLANTING_NOT_ON_GUIDE_DOOR,
    PLANTING_NOT_IN_GOLDROAD,               // Can't plant on GoldRoad
    // High-importance reasons
    //	- These should remain last as they are either highly instructive to a confused player,
    //	or trump all other existing reasons
    PLANTING_NOT_OUTSIDE_PLANT_DEFINED_AREA, 					// The plant being planted can only be planted in a subsection of the grid
    PLANTING_NOT_ON_EXISTING_PLANT,			 					// Can't plant non-upgrade plants on existing plants
    PLANTING_OFF_GRID,											// This location is off the board or not plantable, period
    PLANTING_INTENSIVECARROT_NOT_ON_PREVIOUSLY_PLANTED_SQUARE,	// IntensiveCarrots must be planted on grid squares that are previously planted in
    PLANTING_COBCANNON_CANNOT_BE_HERE,                          // for cob cannon
    PLANTING_COBCANNON_MUST_BE_ON_TWO_KERNELPULT,      // for cob cannon
    PLANTING_COBCANNON_CANNOT_ON_VINES,
    PLANTING_BEYOND_NEW_PVP_LIMIT,
    PLANTING_VINE_MUST_BE_ON_A_PLANT,                   // for vine template
    PLANTING_VINE_CAN_NOT_PLANT_ON_COBCANNON,           // for vine and cannon
    PLANTING_BEYOND_NEW_PVP_LIMIT_UPGRADE_FULL,
    PLANTING_NOT_ON_DINOEGG,
    PLANTING_NOT_ON_DINOTREAD,
    PLANTING_NOT_ON_DUSKSEED,
    PLANTING_NOT_ON_OBSTACLE,
    PLANTING_NOT_ON_COAL_TRUCK,
    PLANTING_NOT_ON_COAL,
    PLANTING_FLATTENEDSHROOM_CANNOT_BE_HERE,
    PLANTING_NOT_ON_MANHOLE,
    PLANTING_NOT_ON_ROLLER,
    PLANTING_NOT_ON_SCHOOLBUS,
    PLANTING_NOT_ON_RENAI_TILE,
    PLANTING_NOT_ON_STATUE,
    PLANTING_NOT_ON_GLIDING,
    PLANTING_NOT_ON_HEALERSTAFF,
    PLANTING_NOT_ON_SUSHI,
    PLANTING_NOT_ON_HEIAN_BOX,
    PLANTING_NEED_FLOWERPOT_FIRST,
    PLANTING_FLOWERPOT_ON_FLOWERPOT,
    PLANTING_FLOWERPOT_ONLY_ROOF,
    PLANTING_NOT_ON_FLOWERPOT,
    PLANTING_NOT_ON_ROOF,
    PLANTING_NOT_ON_BUFF_TILE,
    PLANTING_NOT_ON_HEAVY_SHIELD,
    PLANTING_NOT_ON_FOG,
    PLANTING_NOT_ON_MAGIC_MIRROR,
    PLANTING_NOT_ON_SNOWBALL,
    PLANTING_NOT_ON_YUANBAO,
    PLANTING_NOT_ON_BONFIRE,
    PLANTING_WIZARD_CRUCIBLE_NOT_ACTIVATED,
    PLANTING_WIZARD_CRUCIBLE_NEW_SEEDPACKET,
    PLANTING_ARTIFACT_BLACKHOLE_NOT_ON_THIS,
    PLANTING_ARTIFACT_EVOLUTION_NOT_ON_THIS,
    PLANTING_ARTIFACT_ACID_NOT_ON_THIS,
    PLANTING_ARTIFACT_SILVERKEY_NOT_ON_THIS,
    PLANTING_NOT_ON_BOUNDTILE,
    PLANTING_NOT_ON_CONCRETE,
    PLANTING_NOT_ON_TURKEY,
    PLANTING_NOT_ON_SCARECROW,
    PLANTING_NOT_ON_SARRACENIA,
    PLANTING_NOT_ON_SEEING_STAR,
    PLANTING_NOT_ON_FROST,					// No planting on my mold!
};

enum EndOfPlayReason
{
    ENDOFPLAYREASON_NONE,
    ENDOFPLAYREASON_WON,
    ENDOFPLAYREASON_LOST,
    ENDOFPLAYREASON_RESTART,
    ENDOFPLAYREASON_QUIT,
    ENDOFPLAYREASON_CHEAT,
    ENDOFPLAYREASON_SHUTDOWN,
};

enum BoardResult
{
	BOARDRESULT_NONE,
	BOARDRESULT_WON,
	BOARDRESULT_LOST,
	BOARDRESULT_RESTART,
    BOARDRESULT_NEXT_STAR,
	BOARDRESULT_QUIT,
	BOARDRESULT_QUIT_APP,
	BOARDRESULT_CHEAT,
    // For pvp change opponent
    BOARDRESULT_INTERRUPT,
};

enum MowerSpawnOverride
{
    MOWER_SPAWN_USE_DEFAULT,
    MOWER_SPAWN_NONE,
    MOWER_SPAWN_ONCE,
    MOWER_SPAWN_INFINITE,
    MOWER_SPAWN_REGEN_ONCE
};

struct SunGet
{
	int free;
	int recharge;
	SunGet()
	{
		free = 0;
		recharge = 0;
	}
};
struct PlantfoodGet
{
	int free;
	int recharge;
	PlantfoodGet()
	{
		free = 0;
		recharge = 0;
	}
};

#endif
