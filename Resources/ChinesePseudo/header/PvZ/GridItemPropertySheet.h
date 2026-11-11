//
//  GridItemPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEMPROPERTYSHEET_H__
#define __GRIDITEMPROPERTYSHEET_H__

#include "Precompile.h"
#include "PropertySheetBase.h"
#include "BoardEntity.h"
#include "RestrictionSet.h"
#include "DamageLifetime.h"

struct GridItemLevelStat
{
	GridItemLevelStat()
	{
		HitPointsLevel = 1.0f;
	}

	float HitPointsLevel;
};

enum GridItemTestFlag
{
    PVZ_BEGIN_FLAG_ENUM(GT_),
    PVZ_FLAG(GT_OPPOSING_TEAM),
    PVZ_FLAG(GT_SAME_TEAM),
    PVZ_FLAG(GT_ON_SCREEN),
    PVZ_FLAG(GT_OFF_SCREEN),
    PVZ_FLAG(GT_IN_ROW),
    PVZ_FLAG(GT_NOT_IN_ROW),
    PVZ_FLAG(GT_IN_COL),
    PVZ_FLAG(GT_NOT_IN_COL),
    PVZ_FLAG(GT_IS_DAMAGABLE),
    PVZ_FLAG(GT_IS_NOT_DAMAGABLE),
    PVZ_FLAG(GT_IS_DAMAGABLE_BY_PLANTS),
    PVZ_FLAG(GT_IS_NOT_DAMAGABLE_BY_PLANTS),
    PVZ_FLAG(GT_IS_TARGETABLE_BY_ENTITY),
    PVZ_FLAG(GT_IS_NOT_TARGETABLE_BY_ENTITY),
    PVZ_FLAG(GT_ANY),
    PVZ_END_FLAG_ENUM(GT_),
    
    GT_STANDARD_PLANTS_IGNORE = GT_SAME_TEAM | GT_IS_NOT_DAMAGABLE_BY_PLANTS
};
PVZ_MAKE_ENUM_BIT_OPERATORS(GridItemTestFlag);

class GridItemPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(GridItemPropertySheet, PropertySheetBase, RtClass);
	
	GridItemPropertySheet()
	{
		Hitpoints = 1000;
		HitRectOffsetX = 0;
		HitRectOffsetWidth = 0;
        HitRectOffsetY = 0;
        HitRectOffsetHeight = 0;
        Height = ENTITYHEIGHT_NORMAL;
        CanBeMowed = false;
	}

	float Hitpoints;
	int HitRectOffsetX;			// this offset is applied to the hit rect's mX value
	int HitRectOffsetWidth;		// this offset is applied to the hit rect's mWidth value
    
    int HitRectOffsetY;			// this offset is applied to the hit rect's mY value
	int HitRectOffsetHeight;		// this offset is applied to the hit rect's mHeight value
    
	std::vector<std::string> PlantsCanAttackList; 		// Being empty means all.

	std::vector<GridItemLevelStat> GridItemLevelStats;
    BoardEntityHeight Height;
    bool CanBeMowed;
    PlantingRestrictionSet PlantingRestrictions;
};

class GridItemAnimationProps : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemAnimationProps, GridItemPropertySheet, RtClass);

	GridItemAnimationProps()
	{
		PopAnimRigClass = "PopAnimRig";
		PopAnimRenderOffset = SexyVector2(100, 115);
        PopAnimRenderScale = SexyVector2(1.0f, 1.0f);
        LinkedOffset = SexyVector3(0,0,0);
        LinkedLayerOffset = 1;
	}

	std::string PopAnim;
	std::string PopAnimRigClass;
	SexyVector2 PopAnimRenderOffset;
    SexyVector2 PopAnimRenderScale;

    // Link a second animation object to this one
    std::string	LinkedPopAnim;
    SexyVector3	LinkedOffset;
    int			LinkedLayerOffset;
};

class GridItemBreakableTargetProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemBreakableTargetProps, GridItemAnimationProps, RtClass);

    GridItemBreakableTargetProps()
    {
        HealthRegenRate = 10.f;
        DelayBeforeRegen = 1.0f;
        PopAnimIdleAnim = "animation";

        Regenerates = false;
    }

    std::string	PopAnimSpawnAnim;
    std::string PopAnimIdleAnim;
    std::string PopAnimHitAnim;
    std::string PopAnimDeathAnim;
    std::string BreakEffect;
    std::string BreakEffectSound;
    bool Regenerates;
    float HealthRegenRate;
    float DelayBeforeRegen;
    DamageLifetime	DamagePhases;

	std::string LinkedEffectObject;
};

class GridItemRailcartPropertySheet : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemRailcartPropertySheet, GridItemPropertySheet, RtClass);
	
	GridItemRailcartPropertySheet()
	{
		ImagePrefix = "";
	}
	
	std::string ImagePrefix;
};

#endif // __GRIDITEMPROPERTYSHEET_H__
