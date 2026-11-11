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

#ifndef __PlantsVersusZombies2__PrimeText_Effects_Game__
#define __PlantsVersusZombies2__PrimeText_Effects_Game__

#include "EAText/EATextStyle.h"

enum TypefaceEffect
{
    FONT_EFFECT_NONE                    = (EA::Text::kEffectNone),
    FONT_EFFECT_OUTLINE                 = (EA::Text::kEffectOutline),
    FONT_EFFECT_SHADOW                  = (EA::Text::kEffectShadow),
    FONT_EFFECT_RAISED                  = (EA::Text::kEffectRaised),
    FONT_EFFECT_DEPRESSED               = (EA::Text::kEffectDepressed),
    
    FONT_EFFECT_SEED_COST               = (EA::Text::kEffectUser + 1),  // Outline + Shadow
    FONT_EFFECT_INVERSE_OUTLINE         = (EA::Text::kEffectUser + 2),  // White with black outline
    FONT_EFFECT_HORROR                  = (EA::Text::kEffectUser + 3),  // Green with white outline
    FONT_EFFECT_HORROR_BLACK_OUTLINE    = (EA::Text::kEffectUser + 4),  // White with black outline
    FONT_EFFECT_HARD_SHADOW             = (EA::Text::kEffectUser + 5),  // Outline + hard shadow underneath
    FONT_EFFECT_HORROR_SMALLER          = (EA::Text::kEffectUser + 6),  // Green with white outline
    FONT_EFFECT_THICK_OUTLINE           = (EA::Text::kEffectUser + 7),  // White with black outline
    FONT_EFFECT_OUTLINE_LITE_SHADOW     = (EA::Text::kEffectUser + 8),  // Outline + hard shadow underneath
    FONT_EFFECT_OUTLINE_NAVY_SHADOW     = (EA::Text::kEffectUser + 9),
    FONT_EFFECT_OUTLINE_RED_SHADOW      = (EA::Text::kEffectUser + 10),
};

class PrimeText_Effects_Game
{
public:
    static void GenerateFontEffects();
};


#endif
