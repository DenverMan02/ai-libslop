//
//  Plant_LilyPad.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 5/22/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PLANT_LILYPAD_H__
#define __PLANT_LILYPAD_H__

#include "PlantFramework.h"
#include "BoardEnums.h"
#include "GridItemAnimation.h"
#include "PlantAnimRig.h"

class Projectile;
class Zombie;

class GridItemAnimRig_LilyPad : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemAnimRig_LilyPad, PlantAnimRig, RtClass);

	void PlayIdle();
	void PlayPlantEnteredTile();
	void PlayPlantLeftTile();
	void SetPlantIsOnTile(bool i_onTile);

private:
	void onPopAnimInitialized() override;
	void onAnimStopped() override;

	bool m_isOccupied = false;
	bool m_isOnWater = false;
};

class PlantLilyPad : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLilyPad, PlantFramework, RtClass);

	void Initialize() override;

    bool IsInvincible() const override { return true; }
	bool CanBeShoveled() override { return false; }
	bool HasShadow() override { return true; }

	void ApplyPlantfood() override;

	GridItem* m_gridItemSpawnPointer = NULL;
};

class GridItemLilyPad : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemLilyPad, GridItemAnimation, RtClass);

	int		CalcRenderOrder() const override;
	void 	onUpdate() override;

	void	ApplyPlantfood();
	void	Heal();

	bool	CanBeShoveled() override;
	int		Shovel() override;
    
    void    SetIsDuplicatePlant(bool i_duplicate);
	bool	IsDuplicatePlant() { return m_isDuplicate; }
	void	SetRenderOffset(SexyVector2 i_offset) { m_renderOffset = i_offset; }

	bool	CanBeTargetedBy(const BoardEntity* i_entity) const override;
	void 	onDestroy() override;

	void	SetHealValue(float i_healValue) { m_healValue = i_healValue; }

protected:
	SexyVector2	getRenderOffset() override;
	void	registerForEvents() override;
	void	GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	void	onGridItemInitialize() override;
	void	onTakeDamage(const DamageInfo& i_damage) override;
	void	onKilled() override;

private:
	void	onPlantSmashed(Plant* i_plant);
    
    bool	m_isDuplicate = false;
	float	m_healTimer;
	float	m_healValue;

	SexyVector2 m_renderOffset;
};

class GridItemLilyPadProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemLilyPadProps, GridItemAnimationProps, RtClass);
    GridItemLilyPadProps() {}
    
    PlantRestrictionSet PlantsWhichCannotBePlantedOnLilypads;
};

class PlantTypeLilyPad : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeLilyPad, PlantType, RtClass) {}
	
	// Lilypads can be placed on top of (most) other plants
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
    bool GetCanBeUsedOnStage(const std::string& i_stagePrefix) const override;
};

namespace Message
{
	void LilyPadDied(class GridItemLilyPad* i_lilyPad);
}

#endif // __PLANT_LILYPAD_H__
