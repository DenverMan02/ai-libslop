//
//  PrimeText_Game.h
//  PlantsVersusZombies2
//
//  Contains defines for accessing PvZ2 text values.
//
//  Also potential spot for extra game-specific functionality / staging.
//
//  Created by Jason Emery on 4/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PrimeText_Game__
#define __PlantsVersusZombies2__PrimeText_Game__

#include "SexyString.h"
#include "Color.h"
#include "PrimeText_PotentialTypeface.h"
//PVZ2_CHINESE_BEGIN
#include "ResourceHelpers.h"

//PVZ2_CHINESE_END



//PVZ2_CHINESE_BEGIN
class PrimeText_PotentialTypeface;
#define PVZ2_CHINESE_VERSION

#ifndef PVZ2_CHINESE_VERSION
#define DEBUG_TEXT_FONT_LARGE           ((PrimeText_Game::Typeface_Pico_34 == NULL) ? NULL : PrimeText_Game::Typeface_Pico_34->Typeface())
#define DEBUG_TEXT_FONT                 ((PrimeText_Game::Typeface_Pico_26 == NULL) ? NULL : PrimeText_Game::Typeface_Pico_26->Typeface())
#define DEBUG_TEXT_FONT_SMALL           ((PrimeText_Game::Typeface_Pico_12 == NULL) ? NULL : PrimeText_Game::Typeface_Pico_12->Typeface())
#define DEBUG_TEXT_FONT_SMALL_OUTLINE   ((PrimeText_Game::Typeface_Pico_12 == NULL) ? NULL : PrimeText_Game::Typeface_Pico_12->Typeface())
#define DEBUG_TEXT_FONT_STATS           ((PrimeText_Game::Typeface_CafeteriaBlack_16 == NULL) ? NULL : PrimeText_Game::Typeface_CafeteriaBlack_16->Typeface())

#define FONT_WORLDMAP_NAME              PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_WORLDMAP_UI                PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_COUNTER           PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_HUD_BUTTON        PrimeText_Game::Typeface_CafeteriaBlack_24_HardShadow->Typeface()
#define FONT_WORLDMAP_MINIMAP           PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_STORE_BUTTON      PrimeText_Game::Typeface_CafeteriaBlack_24_HardShadow->Typeface()
#define FONT_WORLDMAP_EDITOR_SMALL      PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_WORLDMAP_EVENT             PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_STARGATE_COST     PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_KEYGATE_FLAG      PrimeText_Game::Typeface_CafeteriaBlack_24_Navy_Outline->Typeface()
#define FONT_EDIT_WIDGET                PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_SUN_COIN_BANK              PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_CONVERSATION_DAVE          PrimeText_Game::Typeface_BrianneTod_32->Typeface()
#define FONT_CONVERSATION_WINNIE        PrimeText_Game::Typeface_Pico_30->Typeface()
#define FONT_CONVERSATION_DAVE_MAP      PrimeText_Game::Typeface_BrianneTod_36->Typeface()
#define FONT_CONVERSATION_WINNIE_MAP    PrimeText_Game::Typeface_Pico_34->Typeface()
#define FONT_CONVERSATION_TAP_TEXT      PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_DAVE_ADVICE                PrimeText_Game::Typeface_BrianneTod_32->Typeface()
#define FONT_GENERIC_ADVICE             PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_WINNIE_ADVICE              PrimeText_Game::Typeface_Pico_30->Typeface()
#define FONT_CHALLENGE_NAME             PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_CHALLENGE_TITLE            PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_CHALLENGE_INFO             PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_CHALLENGE_SEPARATOR        PrimeText_Game::Typeface_CafeteriaBlack_16->Typeface()
#define FONT_CREDITS_TITLE_GAME			PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_CREDITS_TITLE_SECTION		PrimeText_Game::Typeface_CafeteriaBlack_36_ThickOutline->Typeface()
#define FONT_CREDITS_TITLE_ROLE			PrimeText_Game::Typeface_CafeteriaBlack_28_Outline->Typeface()
#define FONT_CREDITS_NAME				PrimeText_Game::Typeface_CafeteriaBlack_22_ThickOutline->Typeface()
#define FONT_CREDITS_NOTE_NAME			PrimeText_Game::Typeface_CafeteriaBlack_22_ThickOutline->Typeface()
#define FONT_CREDITS_NOTE_MESSAGE		PrimeText_Game::Typeface_CafeteriaBlack_22_ThickOutline->Typeface()
#define FONT_GAME_UI_PLANTFOOD_COST     PrimeText_Game::Typeface_CafeteriaBlack_20->Typeface()
#define FONT_GAME_UI_POWERUP_COST       PrimeText_Game::Typeface_CafeteriaBlack_20->Typeface()
#define FONT_GAME_UI_LEVEL_NAME         PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_CONFIRM_TITLE              PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_CONFIRM_DESCRIPTION        PrimeText_Game::Typeface_CafeteriaBlack_32_HardShadow->Typeface()
#define FONT_ALMANAC_OBJECT_NAME		PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_ALMANAC_PLANT_PRICE		PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_ALMANAC_STAT_NAME			PrimeText_Game::Typeface_CafeteriaBlack_24->Typeface()
#define FONT_ALMANAC_STAT_VALUE			PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_ALMANAC_DESCRIPTION        PrimeText_Game::Typeface_CafeteriaBlack_28->Typeface()
#define FONT_ALMANAC_ONELINER           PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_ALMANAC_TAB_LABEL			PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_STORE_TAB_LABEL			PrimeText_Game::Typeface_CafeteriaBlack_32_ThickOutline->Typeface()
#define FONT_STORE_HEADER				PrimeText_Game::Typeface_CafeteriaBlack_26_ThickOutline->Typeface()
#define FONT_STORE_ITEM_TITLE           PrimeText_Game::Typeface_CafeteriaBlack_26_ThickOutline->Typeface()
#define FONT_STORE_BEST_DEAL            PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_STORE_DESCRIPTION          PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_STORE_COMING_SOON_Q        PrimeText_Game::Typeface_CafeteriaBlack_60->Typeface()
#define FONT_REWARD_DIALOG_HEADLINE     PrimeText_Game::Typeface_CafeteriaBlack_46_HardShadow->Typeface()
#define FONT_REWARD_NAME                PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_REWARD_COST                PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_REWARD_DESCRIPTION         PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_WORLD_TEASER_TITLE         PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_WORLD_TEASER_HEADER        PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_WORLD_TEASER_PROMO         PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_WORLD_TEASER_DESCRIPTION   PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_WORLD_TEASER_DESC_DARK     PrimeText_Game::Typeface_CafeteriaBlack_28->Typeface()
#define FONT_WORLD_TEASER_BLACK         PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_MAP_POPOVER_KG_CHALLENGE_NM  PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_MAP_POPOVER_KG_HEADER      PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_MAP_POPOVER_KG_COST		PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_MAP_POPOVER_KG_REWARD      PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_MAP_POPOVER_KG_BYPASS      PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_MAP_POPOVER_HEADER         PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_MAP_POPOVER_DESC           PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_MAP_POPOVER_PURPLE_BTN     PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_MAP_POPOVER_GREEN_BTN		PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_KEYGATE_LARGE				PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_KEYGATE_MEDIUM             PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_KEYGATE_SMALL				PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_MORE_GAMES                 PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_LEVEL_NAME                 PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_STREET_GRID                PrimeText_Game::Typeface_Pico_12->Typeface()
#define FONT_STONE_BUTTON_HIGHLIGHT     PrimeText_Game::Typeface_CafeteriaBlack_32_Shaded->Typeface()
#define FONT_STONE_BUTTON               PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_GENERAL_BUTTON             PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_GENERAL_BUTTON_PLAIN       PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_DIALOG_LABEL               PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_DIALOG_LINES               PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_MESSAGE_MAIN               PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_MESSAGE_SMALL              PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_EDIT_NAME_WIDGET           PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_OPTIONS_UI_OBJECTIVES      PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_OPTIONS_UI_TITLE           PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_OPTIONS_UI                 PrimeText_Game::Typeface_CafeteriaBlack_32_HardShadow->Typeface()
#define FONT_DOWNLOAD_WARNING_UI        PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_SETTINGS_TITLE				PrimeText_Game::Typeface_CafeteriaBlack_40_ThickOutline->Typeface()
#define FONT_SETTINGS_WIDGET_LABEL		PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_SETTINGS_ABOUT_TEXT		PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_SETTINGS_LEGAL_TEXT		PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_SETTINGS_CREDITS_TEXT		PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_TOOLTIP                    PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_SEED_CHOOSER_SMALL         PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_SEED_CHOOSE_HEADER			PrimeText_Game::Typeface_CafeteriaBlack_46_HardShadow->Typeface()
#define FONT_SEED_CHOOSE_DESCRIPTION    PrimeText_Game::Typeface_CafeteriaBlack_28->Typeface()
#define FONT_SEED_CHOOSE_BUY_BUTTON     PrimeText_Game::Typeface_CafeteriaBlack_22_Shaded->Typeface()
#define FONT_SEED_PACKET_COST           PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_GAME_UI_SEED_COST          PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_GAME_CANNON_SCORE          PrimeText_Game::Typeface_CafeteriaBlack_40_Outline->Typeface()
#define FONT_GAME_CANNON_DEATHS         PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_GAME_CANNON_SCORE_FLOATER  PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_DOWNLOAD                   PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_WELCOME_EDIT               PrimeText_Game::Typeface_CafeteriaBlack_32->Typeface()
#define FONT_WELCOME                    PrimeText_Game::Typeface_CafeteriaBlack_28->Typeface()
#define FONT_COPA_WARNING               PrimeText_Game::Typeface_CafeteriaBlack_24_Outline->Typeface()
#define FONT_FACEBOOK_WIDGET_TITLE      PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_FACEBOOK_WIDGET            PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_ADD_PICTURE                PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_TUTORIAL_DEMO_BAR          PrimeText_Game::Typeface_CafeteriaBlack_32_HardShadow->Typeface()
#define FONT_TERROR_EVENT               PrimeText_Game::Typeface_HouseOfTerror_50->Typeface()
#define FONT_GAME_OVER_BRAINS           PrimeText_Game::Typeface_HouseOfTerror_50->Typeface()
#define FONT_TERROR_EVENT_SMALLER       PrimeText_Game::Typeface_HouseOfTerror_40->Typeface()
#define FONT_READYSET_PLANT				PrimeText_Game::Typeface_HouseOfTerror_BlackOutline_32->Typeface()
#define FONT_STORE_TAB                  PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_UNIVERSE_WORLDNAME         PrimeText_Game::Typeface_CafeteriaBlack_46_HardShadow->Typeface()
#define FONT_PAUSE_LARGE_LABEL          PrimeText_Game::Typeface_CafeteriaBlack_38_HardShadow->Typeface()
#define FONT_DANGERROOM_LARGE_LABEL     PrimeText_Game::Typeface_CafeteriaBlack_46_HardShadow->Typeface()
#define FONT_DANGERROOM_LABEL			PrimeText_Game::Typeface_CafeteriaBlack_32_HardShadow->Typeface()
#define FONT_DANGERROOM_REWARD_LABEL	PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_DANGERROOM_REWARD_COUNT	PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_DANGERROOM_CARD_DESC		PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_WORLDMAP_DL_PROGRESS       PrimeText_Game::Typeface_CafeteriaBlack_18->Typeface()
#define FONT_OLAFSTATS					PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_OLAFSTATS_OUTLINE			PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_ZOMBIE_NOTE_TAP_CONTINUE   PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_POOYAN_SCORE               PrimeText_Game::Typeface_FZShaoEr_20_Outline->Typeface()

#else
#define DEBUG_TEXT_FONT_LARGE           ((PrimeText_Game::Typeface_CafeteriaBlack_34 == NULL) ? NULL : PrimeText_Game::Typeface_CafeteriaBlack_34->Typeface())
#define DEBUG_TEXT_FONT                 ((PrimeText_Game::Typeface_CafeteriaBlack_26 == NULL) ? NULL : PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface())
#define DEBUG_TEXT_FONT_SMALL           ((PrimeText_Game::Typeface_CafeteriaBlack_16 == NULL) ? NULL : PrimeText_Game::Typeface_CafeteriaBlack_16->Typeface())
#define DEBUG_TEXT_FONT_SMALL_OUTLINE   ((PrimeText_Game::Typeface_CafeteriaBlack_16 == NULL) ? NULL : PrimeText_Game::Typeface_CafeteriaBlack_16->Typeface())
#define DEBUG_TEXT_FONT_STATS           ((PrimeText_Game::Typeface_CafeteriaBlack_16 == NULL) ? NULL : PrimeText_Game::Typeface_CafeteriaBlack_16->Typeface())

#define FONT_WORLDMAP_NAME              PrimeText_Game::Typeface_FZShaoEr_40_ThickOutline->Typeface()
#define FONT_WORLDMAP_UI                PrimeText_Game::Typeface_FZShaoEr_26_Shaded->Typeface()
#define FONT_WORLDMAP_COUNTER           PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_HUD_BUTTON        PrimeText_Game::Typeface_FZShaoEr_24_HardShadow->Typeface()
#define FONT_WORLDMAP_MINIMAP           PrimeText_Game::Typeface_FZShaoEr_26_Shaded->Typeface()
#define FONT_WORLDMAP_STORE_BUTTON      PrimeText_Game::Typeface_FZShaoEr_24_HardShadow->Typeface()
#define FONT_WORLDMAP_EDITOR_SMALL      PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_WORLDMAP_EVENT             PrimeText_Game::Typeface_FZShaoEr_26_Shaded->Typeface()
#define FONT_WORLDMAP_STARGATE_COST     PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_WORLDMAP_KEYGATE_FLAG      PrimeText_Game::Typeface_FZShaoEr_24_Navy_Outline->Typeface()
#define FONT_EDIT_WIDGET                PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_SUN_COIN_BANK              PrimeText_Game::Typeface_CafeteriaBlack_26_Shaded->Typeface()
#define FONT_ACHIEVEMENT_NUMBER         PrimeText_Game::Typeface_CafeteriaBlack_24_Shaded->Typeface()
#define FONT_CONVERSATION_DAVE          PrimeText_Game::Typeface_FZKaTong_30->Typeface()
#define FONT_CONVERSATION_WINNIE        PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_CONVERSATION_DAVE_MAP      PrimeText_Game::Typeface_FZKaTong_30->Typeface()
#define FONT_CONVERSATION_WINNIE_MAP    PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_CONVERSATION_TAP_TEXT      PrimeText_Game::Typeface_FZShaoEr_20->Typeface()
#define FONT_DAVE_ADVICE                PrimeText_Game::Typeface_FZKaTong_32->Typeface()
#define FONT_GENERIC_ADVICE             PrimeText_Game::Typeface_FZCuYuan_24_ThickOutline->Typeface()
#define FONT_WINNIE_ADVICE              PrimeText_Game::Typeface_FZCuYuan_32->Typeface()
#define FONT_CHALLENGE_NAME             PrimeText_Game::Typeface_FZShaoEr_34_ThickOutline->Typeface()
#define FONT_CHALLENGE_TITLE            PrimeText_Game::Typeface_FZShaoEr_28_ThickOutline->Typeface()
#define FONT_CHALLENGE_INFO             PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
#define FONT_CHALLENGE_SEPARATOR        PrimeText_Game::Typeface_FZShaoEr_16->Typeface()
#define FONT_CREDITS_TITLE_GAME			PrimeText_Game::Typeface_FZShaoEr_40_ThickOutline->Typeface()
#define FONT_CREDITS_TITLE_SECTION		PrimeText_Game::Typeface_FZShaoEr_36_ThickOutline->Typeface()
#define FONT_CREDITS_TITLE_ROLE			PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface()
#define FONT_CREDITS_NAME				PrimeText_Game::Typeface_FZShaoEr_22_ThickOutline->Typeface()
#define FONT_CREDITS_NOTE_NAME			PrimeText_Game::Typeface_FZShaoEr_22_ThickOutline->Typeface()
#define FONT_CREDITS_NOTE_MESSAGE		PrimeText_Game::Typeface_FZShaoEr_22_ThickOutline->Typeface()
#define FONT_GAME_UI_PLANTFOOD_COST     PrimeText_Game::Typeface_CafeteriaBlack_20->Typeface()
#define FONT_GAME_UI_POWERUP_COST       PrimeText_Game::Typeface_FZShaoEr_16->Typeface()
#define FONT_GAME_UI_LEVEL_NAME         PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_CONFIRM_TITLE              PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface()
#define FONT_CONFIRM_DESCRIPTION        PrimeText_Game::Typeface_FZCuYuan_19_HardShadow->Typeface()
#define FONT_ALMANAC_OBJECT_NAME		PrimeText_Game::Typeface_FZShaoEr_32_ThickOutline->Typeface()
#define FONT_ALMANAC_PLANT_PRICE		PrimeText_Game::Typeface_CafeteriaBlack_26_Outline->Typeface()
#define FONT_ALMANAC_STAT_NAME			PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_ALMANAC_STAT_VALUE			PrimeText_Game::Typeface_FZCuYuan_19_Outline->Typeface()
#define FONT_ALMANAC_DESCRIPTION        PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_ALMANAC_ONELINER           PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_ALMANAC_TAB_LABEL			PrimeText_Game::Typeface_FZShaoEr_32_ThickOutline->Typeface()
#define FONT_STORE_TAB_LABEL			PrimeText_Game::Typeface_FZShaoEr_32_ThickOutline->Typeface()
#define FONT_STORE_HEADER				PrimeText_Game::Typeface_FZShaoEr_26_ThickOutline->Typeface()
#define FONT_STORE_ITEM_TITLE           PrimeText_Game::Typeface_FZShaoEr_26_ThickOutline->Typeface()
#define FONT_STORE_BEST_DEAL            PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_STORE_DESCRIPTION          PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_STORE_COMING_SOON_Q        PrimeText_Game::Typeface_FZShaoEr_60->Typeface()
#define FONT_REWARD_DIALOG_HEADLINE     PrimeText_Game::Typeface_FZShaoEr_34_HardShadow->Typeface()
#define FONT_REWARD_NAME                PrimeText_Game::Typeface_FZShaoEr_28_ThickOutline->Typeface()
#define FONT_REWARD_COST                PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_REWARD_DESCRIPTION         PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
#define FONT_WORLD_TEASER_TITLE         PrimeText_Game::Typeface_FZShaoEr_32->Typeface()
#define FONT_WORLD_TEASER_HEADER        PrimeText_Game::Typeface_FZShaoEr_32->Typeface()
#define FONT_WORLD_TEASER_PROMO         PrimeText_Game::Typeface_FZCuYuan_26_Outline->Typeface()
#define FONT_WORLD_TEASER_DESCRIPTION   PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_WORLD_TEASER_DESC_DARK     PrimeText_Game::Typeface_FZCuYuan_28->Typeface()
#define FONT_WORLD_TEASER_BLACK         PrimeText_Game::Typeface_FZShaoEr_32->Typeface()
#define FONT_MAP_POPOVER_KG_CHALLENGE_NM  PrimeText_Game::Typeface_FZCuYuan_32->Typeface()
#define FONT_MAP_POPOVER_KG_HEADER      PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
//#define FONT_MAP_POPOVER_KG_COST		PrimeText_Game::Typeface_CafeteriaBlack_26->Typeface()
#define FONT_MAP_POPOVER_KG_COST		PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
#define FONT_MAP_POPOVER_KG_REWARD      PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
#define FONT_MAP_POPOVER_KG_BYPASS      PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
#define FONT_MAP_POPOVER_HEADER         PrimeText_Game::Typeface_FZCuYuan_28->Typeface()
#define FONT_MAP_POPOVER_DESC           PrimeText_Game::Typeface_FZCuYuan_18->Typeface()
#define FONT_MAP_POPOVER_PURPLE_BTN     PrimeText_Game::Typeface_FZShaoEr_22_Shaded->Typeface()
#define FONT_MAP_POPOVER_GREEN_BTN		PrimeText_Game::Typeface_FZShaoEr_22_Shaded->Typeface()
#define FONT_KEYGATE_LARGE				PrimeText_Game::Typeface_FZShaoEr_32->Typeface()
#define FONT_KEYGATE_MEDIUM             PrimeText_Game::Typeface_FZShaoEr_26->Typeface()
#define FONT_KEYGATE_SMALL				PrimeText_Game::Typeface_FZShaoEr_22->Typeface()
#define FONT_MORE_GAMES                 PrimeText_Game::Typeface_FZShaoEr_22->Typeface()
#define FONT_LEVEL_NAME                 PrimeText_Game::Typeface_FZKaTong_30_HardShadow->Typeface()
#define FONT_STREET_GRID                PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_STONE_BUTTON_HIGHLIGHT     PrimeText_Game::Typeface_FZShaoEr_32_Shaded->Typeface()
#define FONT_STONE_BUTTON               PrimeText_Game::Typeface_FZShaoEr_32->Typeface()
#define FONT_GENERAL_BUTTON             PrimeText_Game::Typeface_FZShaoEr_22_Shaded->Typeface()
#define FONT_GENERAL_BUTTON_PLAIN       PrimeText_Game::Typeface_FZShaoEr_26->Typeface()
#define FONT_DIALOG_LABEL               PrimeText_Game::Typeface_FZCuYuan_40_ThickOutline->Typeface()
#define FONT_DIALOG_LINES               PrimeText_Game::Typeface_FZCuYuan_26_Outline->Typeface()
#define FONT_MESSAGE_MAIN               PrimeText_Game::Typeface_FZCuYuan_26_Shaded->Typeface()
#define FONT_MESSAGE_SMALL              PrimeText_Game::Typeface_FZCuYuan_18->Typeface()
#define FONT_EDIT_NAME_WIDGET           PrimeText_Game::Typeface_FZShaoEr_22->Typeface()
#define FONT_OPTIONS_UI_OBJECTIVES      PrimeText_Game::Typeface_FZCuYuan_24->Typeface()
#define FONT_OPTIONS_UI_TITLE           PrimeText_Game::Typeface_FZShaoEr_26->Typeface()
#define FONT_OPTIONS_UI                 PrimeText_Game::Typeface_FZShaoEr_22_HardShadow->Typeface()
#define FONT_DOWNLOAD_WARNING_UI        PrimeText_Game::Typeface_FZShaoEr_22->Typeface()
#define FONT_SETTINGS_TITLE				PrimeText_Game::Typeface_FZShaoEr_32_ThickOutline->Typeface()
#define FONT_SETTINGS_WIDGET_LABEL		PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_SETTINGS_ABOUT_TEXT		PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_SETTINGS_LEGAL_TEXT		PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_SETTINGS_CREDITS_TEXT		PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_TOOLTIP                    PrimeText_Game::Typeface_FZCuYuan_18->Typeface()
//Added by Bokun Zhao 2013/6/18
#define FONT_HOUSE_NAME                 PrimeText_Game::Typeface_FZKaTong_42_HardShadow->Typeface()
#define FONT_REWARD_DIALOG_TITLE        PrimeText_Game::Typeface_FZShaoEr_28_ThickOutline->Typeface()
//==============
#define FONT_SEED_CHOOSER_SMALL         PrimeText_Game::Typeface_FZCuYuan_18->Typeface()
#define FONT_SEED_CHOOSE_HEADER			PrimeText_Game::Typeface_FZShaoEr_28_HardShadow->Typeface()
#define FONT_SEED_CHOOSE_DESCRIPTION    PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_SEED_CHOOSE_BUY_BUTTON     PrimeText_Game::Typeface_FZShaoEr_22_Shaded->Typeface()
#define FONT_SEED_PACKET_COST           PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_GAME_UI_SEED_COST          PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_GAME_CANNON_SCORE          PrimeText_Game::Typeface_FZShaoEr_40_Outline->Typeface()
#define FONT_GAME_CANNON_DEATHS         PrimeText_Game::Typeface_FZShaoEr_26_Outline->Typeface()
#define FONT_GAME_CANNON_SCORE_FLOATER  PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_DOWNLOAD                   PrimeText_Game::Typeface_FZCuYuan_18->Typeface()
#define FONT_WELCOME_EDIT               PrimeText_Game::Typeface_FZCuYuan_32->Typeface()
#define FONT_WELCOME                    PrimeText_Game::Typeface_FZCuYuan_28->Typeface()
#define FONT_COPA_WARNING               PrimeText_Game::Typeface_FZShaoEr_24_Outline->Typeface()
#define FONT_FACEBOOK_WIDGET_TITLE      PrimeText_Game::Typeface_FZShaoEr_26_HardShadow->Typeface()
#define FONT_FACEBOOK_WIDGET            PrimeText_Game::Typeface_FZShaoEr_22->Typeface()
#define FONT_ADD_PICTURE                PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_TUTORIAL_DEMO_BAR          PrimeText_Game::Typeface_FZShaoEr_32_HardShadow->Typeface()
#define FONT_TERROR_EVENT               PrimeText_Game::Typeface_FZKaTong_42->Typeface()
#define FONT_GAME_OVER_BRAINS           PrimeText_Game::Typeface_FZKaTong_42->Typeface()
#define FONT_TERROR_EVENT_SMALLER       PrimeText_Game::Typeface_FZShaoEr_28->Typeface()
#define FONT_READYSET_PLANT				PrimeText_Game::Typeface_FZKaTong_42_BlackOutline->Typeface()
#define FONT_STORE_TAB                  PrimeText_Game::Typeface_FZShaoEr_26_Shaded->Typeface()
#define FONT_UNIVERSE_WORLDNAME         PrimeText_Game::Typeface_FZShaoEr_28_HardShadow->Typeface()
#define FONT_PAUSE_LARGE_LABEL          PrimeText_Game::Typeface_FZShaoEr_34_HardShadow->Typeface()
#define FONT_DANGERROOM_LARGE_LABEL     PrimeText_Game::Typeface_FZCuYuan_46_HardShadow->Typeface()
#define FONT_DANGERROOM_LABEL			PrimeText_Game::Typeface_FZCuYuan_32_HardShadow->Typeface()
#define FONT_DANGERROOM_REWARD_LABEL	PrimeText_Game::Typeface_FZCuYuan_26->Typeface()
#define FONT_DANGERROOM_REWARD_COUNT	PrimeText_Game::Typeface_FZCuYuan_26_Outline->Typeface()
#define FONT_DANGERROOM_CARD_DESC		PrimeText_Game::Typeface_FZCuYuan_26_Outline->Typeface()
#define FONT_WORLDMAP_DL_PROGRESS       PrimeText_Game::Typeface_FZShaoEr_18->Typeface()
#define FONT_OLAFSTATS					PrimeText_Game::Typeface_FZShaoEr_26_Outline->Typeface()
#define FONT_OLAFSTATS_OUTLINE			PrimeText_Game::Typeface_FZShaoEr_26_Outline->Typeface()
#define FONT_ZOMBIE_NOTE_TAP_CONTINUE   PrimeText_Game::Typeface_FZShaoEr_26_HardShadow->Typeface()
#define FONT_CARD_NAME                  PrimeText_Game::Typeface_FZShaoEr_22_ThickOutline->Typeface()
#define FONT_CARD_DESCRIPTION           PrimeText_Game::Typeface_FZCuYuan_18->Typeface()
#define FONT_CARD_NUM                   PrimeText_Game::Typeface_CafeteriaBlack_19_ThickOutline->Typeface()
#define FONT_CARD_BUTTON                PrimeText_Game::Typeface_FZShaoEr_22->Typeface()
#define FONT_CARD_BUTTON_NUM            PrimeText_Game::Typeface_CafeteriaBlack_22->Typeface()
#define FONT_POOYAN_SCORE               PrimeText_Game::Typeface_FZShaoEr_20_Outline->Typeface()
#define FONT_EDITOR                     PrimeText_Game::Typeface_FZCuYuan_16->Typeface()
#define FONT_EDITOR_OUTLINE             PrimeText_Game::Typeface_FZCuYuan_16_Outline->Typeface()

#define FONT_SIMPLE_NUM                 PrimeText_Game::Typeface_CafeteriaBlack_20->Typeface()
#define FONT_SIMPLE_BIGNUM              PrimeText_Game::Typeface_CafeteriaBlack_32_ThickOutline->Typeface()
#define FONT_SIMPLE_MININUM             PrimeText_Game::Typeface_CafeteriaBlack_10_ThickOutline->Typeface()

#define FONT_CUYUAN_NUM                 PrimeText_Game::Typeface_FZCuYuan_20->Typeface()
#define FONT_CUYUAN_BIGNUM              PrimeText_Game::Typeface_FZCuYuan_32_ThickOutline->Typeface()
#define FONT_CUYUAN_MININUM             PrimeText_Game::Typeface_FZCuYuan_16_ThickOutline->Typeface()

#define FONT_HEALTHBAR                  PrimeText_Game::Typeface_FZCuYuan_12->Typeface()
#define FONT_SHIELDBAR                  PrimeText_Game::Typeface_FZCuYuan_12_Outline->Typeface()

#define FONT_MAP2_LOD_BANNER_HEADER     PrimeText_Game::Typeface_CafeteriaBlack_26_HardShadow->Typeface()
#define FONT_MAP2_LOD_BANNER_DESC       PrimeText_Game::Typeface_CafeteriaBlack_24_HardShadow->Typeface()
#define FONT_MAP2_LOD_BANNER_COUNTDOWN  PrimeText_Game::Typeface_CafeteriaBlack_22_ThickOutline->Typeface()

//QZY added to display english credtis with a different font.
#define FONT_CREDITS_NAME_EN				PrimeText_Game::Typeface_CafeteriaBlack_22_ThickOutline->Typeface()
#define FONT_CREDITS_NAME_CH				PrimeText_Game::Typeface_FZShaoEr_22_ThickOutline->Typeface()
#define FONT_CREDITS_TITLE_ROLE_EN			PrimeText_Game::Typeface_CafeteriaBlack_28_Outline->Typeface()
#define FONT_CREDITS_TITLE_ROLE_CH			PrimeText_Game::Typeface_FZShaoEr_28_Outline->Typeface()

#define FONT_PRICE_IN_LIGHT			PrimeText_Game::Typeface_FZCuYuan_26_HardShadow->Typeface()
#define FONT_PRICE_ORIGENAL         PrimeText_Game::Typeface_FZCuYuan_20_HardShadow->Typeface()

#define FONT_JOUST_SCORE_FLOATER		PrimeText_Game::Typeface_CafeteriaBlack_32_ThickOutline->Typeface()

#endif
//PVZ2_CHINESE_END

class PrimeText_Game
{
public:
    // Font Names
    static SexyString Font_Pico;
    static SexyString Font_BrianneTod;
    static SexyString Font_HouseOfTerror;
    static SexyString Font_USVBlack;
    static SexyString Font_Embedded;
    //PVZ2_CHINESE_BEGIN
    static SexyString Font_FZKaTong;
    static SexyString Font_FZShaoEr;
    static SexyString Font_FZCuYuan;
    //PVZ2_CHINESE_END
    
public:
    // HTML Colors
    static Sexy::Color Color_LawnGreen;
    static Sexy::Color Color_OliveDrab;
    static Sexy::Color Color_SeaGreen;
    static Sexy::Color Color_Wheat;
    static Sexy::Color Color_Tomato;
    static Sexy::Color Color_OrangeRed;
    static Sexy::Color Color_Thistle;
    static Sexy::Color Color_SlateGray;

    // Game Colors
    static Sexy::Color Color_AlmanacHead;
    static Sexy::Color Color_AlmanacDesc;
    static Sexy::Color Color_Conversation_Tap_Text;
    static Sexy::Color Color_Challenge_Title;
    static Sexy::Color Color_Challenge_Text;
    static Sexy::Color Color_Powerup_Cost;
	static Sexy::Color Color_ProgressBar_LevelName;
	static Sexy::Color Color_Popover_Btn_Label;
	static Sexy::Color Color_Popover_Header;
	static Sexy::Color Color_Popover_Cost;
	static Sexy::Color Color_Popover_Reward;
	static Sexy::Color Color_Popover_Bypass;
	static Sexy::Color Color_Popover_Desc;
	static Sexy::Color Color_DangerRoom_LargeLabel;
	static Sexy::Color Color_DangerRoom_LabelName;
	static Sexy::Color Color_DangerRoom_LabelInfo;
	static Sexy::Color Color_DangerRoom_RewardLabel;
	static Sexy::Color Color_DangerRoom_RewardInfo;
    static Sexy::Color Color_Horror_Green;
	static Sexy::Color Color_DangerRoom_Plantfood;
    static Sexy::Color Color_Seed_Packet_Cost;
    static Sexy::Color Color_Description_Brown;
    static Sexy::Color Color_Teaser_Brown;
    static Sexy::Color Color_WorldTeaser_Yellow;
    static Sexy::Color Color_Generic_Title;
    static Sexy::Color Color_Add_Player_Faded;
    static Sexy::Color Color_WorldMap_StarGateCost;
    static Sexy::Color Color_New_Plant_Header;
    static Sexy::Color Color_Description_Green;
    static Sexy::Color Color_PooyanScore_Yellow;
    static Sexy::Color Color_LOD_Upcoming_Header;
    
public:
    // Predefined Font Instances
#ifndef PVZ2_CHINESE_VERSION
    static PrimeText_PotentialTypeface* Typeface_HouseOfTerror_28;
    static PrimeText_PotentialTypeface* Typeface_HouseOfTerror_50;
    static PrimeText_PotentialTypeface* Typeface_HouseOfTerror_40;
	static PrimeText_PotentialTypeface* Typeface_HouseOfTerror_BlackOutline_32;

    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_60;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_46_Outline;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_46_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_40_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_40_ThickOutline;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_38_HardShadow;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_36_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32_InverseOutline;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32_Shaded;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_28;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_28_Shaded;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_28_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26_SeedPacketCost;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24_Outline;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24_Navy_Outline;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24_Red_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24_ThickOutline;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_22_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_19_Shaded;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_19_HardShadow;
	static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_19_Outline;
    static PrimeText_PotentialTypeface* Typeface_BrianneTod_32;
    static PrimeText_PotentialTypeface* Typeface_BrianneTod_36;
    
    static PrimeText_PotentialTypeface* Typeface_Pico_34;
    static PrimeText_PotentialTypeface* Typeface_Pico_30;
    static PrimeText_PotentialTypeface* Typeface_Pico_26;
    static PrimeText_PotentialTypeface* Typeface_Pico_36;
    static PrimeText_PotentialTypeface* Typeface_Pico_12;
#endif
    
    //PVZ2_CHINESE_BEGIN
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_12;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_16;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_18;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_19_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_20;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_22;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_22_ThickOut;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_22_Shaded;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_22_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_22_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_32_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24_Shaded;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_24_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26_Shaded;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_26_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_28_Outline;
    static PrimeText_PotentialTypeface* Typeface_CafeteriaBlack_10_ThickOutline;
    
    // Predefined Font Instances
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_22;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_22_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_26;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_28;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_30;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_30_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_32;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_36;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_40;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_42_HardShadow;
	static PrimeText_PotentialTypeface* Typeface_FZKaTong_42_BlackOutline;
    static PrimeText_PotentialTypeface* Typeface_FZKaTong_42;
    
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_60;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_40_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_40_ThickOutline;
	static PrimeText_PotentialTypeface* Typeface_FZShaoEr_36_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_34_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_34_ThickOutline;
    
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_32;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_32_Shaded;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_32_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_32_ThickOutline;
    
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_28;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_28_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_28_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_28_HardShadow;
    
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_26;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_26_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_26_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_26_Shaded;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_26_Outline;

    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_24_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_24_Outline;
	static PrimeText_PotentialTypeface* Typeface_FZShaoEr_24_Navy_Outline;

    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_22;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_22_Shaded;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_22_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_22_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_20;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_20_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_18;
    static PrimeText_PotentialTypeface* Typeface_FZShaoEr_16;
    
	static PrimeText_PotentialTypeface* Typeface_FZCuYuan_46_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_40_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_32;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_32_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_32_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_28;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_26;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_26_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_26_Shaded;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_26_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_24;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_24_ThickOutline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_20_HardShadow;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_20;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_19_HardShadow;
	static PrimeText_PotentialTypeface* Typeface_FZCuYuan_19_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_18;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_12;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_12_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_16;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_16_Outline;
    static PrimeText_PotentialTypeface* Typeface_FZCuYuan_16_ThickOutline;

    //PVZ2_CHINESE_END
    
    // Generates standard reusable font instances
    // (Call after fonts are loaded)
    static void GenerateFontInstances();
    static int ScaleFont(int size);
    static void GenerateFontEffects();
};



#endif /* defined(__PlantsVersusZombies2__PrimeText_Game__) */
