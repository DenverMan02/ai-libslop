//
//  Renderable.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Renderable_h
#define PlantsVersusZombies2_Renderable_h

#include "Graphics.h"
#include "RtObject.h"
#include "SexyMatrix.h"

namespace Sexy
{
    class Graphics;
    class Image;
}

enum RenderLayer
{
    RENDER_LAYER_STAGE_BACKGROUND =	100000,
    RENDER_LAYER_ABOVE_GROUND =		150000,
    RENDER_LAYER_UI_BOTTOM =		200000,
    RENDER_LAYER_GROUND =			300000,
    RENDER_LAYER_LAWN =				400000,
    RENDER_LAYER_TOP =				500000,
    RENDER_LAYER_FOG =				600000,
    RENDER_LAYER_COIN_BANK =		650000,
    RENDER_LAYER_UI =				700000,
    RENDER_LAYER_UI_TOP =			800000,
    RENDER_LAYER_ABOVE_UI =			900000,
    RENDER_LAYER_SCREEN_FADE =		1000000,
    
    RENDER_LAYER_DARK_BRAZIER_TOP			= RENDER_LAYER_ABOVE_GROUND + 100,
    RENDER_LAYER_TIDE_WET_SAND				= RENDER_LAYER_ABOVE_GROUND + 100,
    RENDER_LAYER_TIDE_LOWER_LAYER			= RENDER_LAYER_ABOVE_GROUND + 101,
    RENDER_LAYER_TIDE_UNDERWATER_SQUARE		= RENDER_LAYER_ABOVE_GROUND + 102,
    RENDER_LAYER_TIDE_UPPER_LAYER			= RENDER_LAYER_ABOVE_GROUND + 103,
    RENDER_LAYER_STAGE_FOREGROUND			= RENDER_LAYER_ABOVE_GROUND + 1000,
    RENDER_LAYER_STAGE_FOREGROUND_SHADOW	= RENDER_LAYER_ABOVE_GROUND + 1001,
    RENDER_LAYER_TIDE_SIGN					= RENDER_LAYER_ABOVE_GROUND + 1002,
    
    RENDER_LAYER_POWER_TILE_DOT				= RENDER_LAYER_UI_BOTTOM - 1,
    
    RENDER_LAYER_SHADOWS					= RENDER_LAYER_GROUND + 2,
    RENDER_LAYER_GHOSTPEPPER_FOG			= RENDER_LAYER_GROUND + 3,
    
    RENDER_LAYER_DIRTY_LAWN					= RENDER_LAYER_GROUND + 1,
    
    RENDER_LAYER_TILES						= RENDER_LAYER_LAWN + 1,
    RENDER_LAYER_PROTECT_THE_PLANT			= RENDER_LAYER_LAWN + 5,
    RENDER_LAYER_LAVA_CRACK					= RENDER_LAYER_LAWN + 7,
    RENDER_LAYER_LILYPAD					= RENDER_LAYER_LAWN + 9,
    RENDER_LAYER_SAP						= RENDER_LAYER_LAWN + 10,
    RENDER_LAYER_SHADOWPORTAL				= RENDER_LAYER_LAWN + 11,
    RENDER_LAYER_RAILCART					= RENDER_LAYER_LAWN + 100,
    
    RENDER_LAYER_MOONFLOWER_GLOW			= RENDER_LAYER_LAWN + 500,
	RENDER_LAYER_ELECTRIC_FENCE				= RENDER_LAYER_LAWN + 600,
    RENDER_LAYER_GRAVE_STONE				= RENDER_LAYER_LAWN + 1000,
    RENDER_LAYER_PLANT						= RENDER_LAYER_LAWN + 2000,
    RENDER_LAYER_PLANT_ARMOR                = RENDER_LAYER_LAWN + 3000,
    RENDER_LAYER_PLANT_POWER                = RENDER_LAYER_LAWN + 4000,
    RENDER_LAYER_PLANT_GROUND               = RENDER_LAYER_LAWN + 5000,
    RENDER_LAYER_CREATURE					= RENDER_LAYER_LAWN + 6000,
    RENDER_LAYER_LOSTCITY_TENT				= RENDER_LAYER_LAWN + 6990,
    RENDER_LAYER_ZOMBIE						= RENDER_LAYER_LAWN + 7000,
    RENDER_LAYER_PLANT_ABOVE_ZOMBIES		= RENDER_LAYER_LAWN + 8000,
    RENDER_LAYER_PLANT_ABOVE_ZOMBIES_ARMOR  = RENDER_LAYER_LAWN + 9000,
    RENDER_LAYER_PLANT_ABOVE_ZOMBIES_POWER  = RENDER_LAYER_LAWN + 10000,
    RENDER_LAYER_PLANT_ABOVE_ZOMBIES_GROUND = RENDER_LAYER_LAWN + 11000,
    RENDER_LAYER_PROJECTILE					= RENDER_LAYER_LAWN + 12000,
    RENDER_LAYER_LAWN_MOWER					= RENDER_LAYER_LAWN + 13000,
    RENDER_LAYER_PARTICLE					= RENDER_LAYER_LAWN + 14000,
    
    RENDER_LAYER_DROPPED_SEEDPACKETS		= RENDER_LAYER_TOP + 1000,
    RENDER_LAYER_END_OF_LEVEL_REWARD		= RENDER_LAYER_TOP + 2000,
    RENDER_LAYER_SCORE						= RENDER_LAYER_TOP + 3000,
    
    RENDER_LAYER_ROW_OFFSET =	10000,
    RENDER_LAYER_GLITTER_RAINBOW_FRONT_OFFSET = -500,
    RENDER_LAYER_GLITTER_RAINBOW_BACK_OFFSET = -2500,
    RENDER_LAYER_PLANT_VINE						= RENDER_LAYER_PLANT + 1

};

class Renderable
{
public:
    virtual ~Renderable() {}
    virtual void Draw(Sexy::Graphics* g) = 0;
    virtual int CalcRenderOrder() const { return 0; }
};

class MatrixPusher
{
public:
    static SexyMatrix3 CalcTransformMatrix(float i_scale, float i_translateX, float i_translateY)
    {
        Sexy::SexyTransform2D scaleTransform;
        Sexy::SexyTransform2D moveTransform;
        Sexy::SexyTransform2D negMoveTransform;
        
        moveTransform.Translate(i_translateX, i_translateY);
        scaleTransform.Scale(i_scale, i_scale);
        negMoveTransform.Translate(-i_translateX, -i_translateY);
        
        SexyMatrix3 fullTransform = moveTransform * scaleTransform * negMoveTransform;
        return fullTransform;
    }
    
    MatrixPusher(Sexy::Graphics* i_g, float i_scale, float i_translateX, float i_translateY)
    {
        mG = i_g;
        
        SexyMatrix3 transform = MatrixPusher::CalcTransformMatrix(i_scale, i_translateX, i_translateY);
        mG->Get3D()->PushTransform(transform, true);
    }
    
    ~MatrixPusher()
    {
        mG->Get3D()->PopTransform();
    }
    
private:
    Sexy::Graphics* mG;
};
#endif
