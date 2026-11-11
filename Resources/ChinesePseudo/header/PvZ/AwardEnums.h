//
//  AwardEnums.h
//  PlantsVersusZombies2
//
//  Created by Terrry Franguiadakis on 2/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_AwardEnums_h
#define PlantsVersusZombies2_AwardEnums_h
#include "core.h"

enum AwardType 
{
    PVZ_BEGIN_ENUM(AWARD_),
	AWARD_None,
	AWARD_Present,
	AWARD_Collectable,
	
	// The following awards will bring up special award presentation dialogs when collected
	AWARD_UnlockPlant,
	AWARD_Powerup,
	AWARD_Upgrade,
	AWARD_MapGadget,
	AWARD_PowerupGadget,
	AWARD_FirstKey,
	AWARD_Note,
	AWARD_WorldTrophy,
    
    // The following awards do not currently spawn in-game
    AWARD_Coins,
    AWARD_Gems,
    AWARD_PowerupUse,
    AWARD_Key,
    AWARD_GameFeature,
    AWARD_CostumeGroupLOD,
    AWARD_Costume,
	
	AWARD_GiftBox,
	AWARD_WorldKey,
	AWARD_Sprout,
	AWARD_PlantBoost,
    
    //Chinese Ver
    AWARD_Bonus,
    AWARD_StarKey,
    AWARD_PieceFireGourd,
    AWARD_PieceGravebuster,
    AWARD_PlantPiece,
    AWARD_AccessoryPiece,

    AWARD_CH_PLANT,
    AWARD_CH_PLANT_PIECE,
    AWARD_CH_AVATAR,
    AWARD_CH_AVATAR_PIECE,
    AWARD_CH_ACCESSORY,
    AWARD_CH_ACCESSORY_PIECE,
    AWARD_CH_GEM,
    AWARD_CH_COIN,
    AWARD_CH_CUKE,
    AWARD_CH_MATERIAL,
    AWARD_CH_CHEST,
    AWARD_CH_ARTIFACT,
    PVZ_END_ENUM(AWARD_),
};

enum AWARD_Context
{
	AWARDCONTEXT_LODReward,
	AWARDCONTEXT_ConsecutiveLODReward,
	AWARDCONTEXT_InviteAward,
	AWARDCONTEXT_ProfileConversion,
	AWARDCONTEXT_Cheat,
	AWARDCONTEXT_GiftBox,
	AWARDCONTEXT_ZenGarden,
	AWARDCONTEXT_ElderQuestRollup,
	AWARDCONTEXT_Rankup,
	AWARDCONTEXT_EASqaured,
	AWARDCONTEXT_EpicQuest,
	AWARDCONTEXT_Joust
};

#endif
