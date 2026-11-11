//
//  GridItemSliderTile.cpp
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/24/14
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemSliderTile__
#define __PlantsVersusZombies2__GridItemSliderTile__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

enum GridItemSliderDirection
{
	PVZ_BEGIN_ENUM(SLIDE_DIRECTION_),
	SLIDE_DIRECTION_Up,
	SLIDE_DIRECTION_Down,
	PVZ_END_ENUM(SLIDE_DIRECTION_)
};

enum SliderState
{
	PVZ_BEGIN_ENUM(SLIDERSTATE_),
	SLIDERSTATE_IDLE,
	SLIDERSTATE_START,
	SLIDERSTATE_SLIDING,
	SLIDERSTATE_END,
	PVZ_END_ENUM(SLIDERSTATE_)
};

class GridItemSliderTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemSliderTile, GridItemAnimation, RtClass);

	GridItemSliderTile() :
		m_state(SLIDERSTATE_IDLE), m_lastSlideTime(PVZ_EOT())
	{
	}
	
	int CalcRenderOrder() const override;
	void SetIsOccupied(bool i_occupied);

	void OnPropagatedTo();
	void OnOccupantPlantfooded();

	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	std::vector<BoardEntity*> findTargets();
	void tryPushZombie(class Zombie* i_zombie, int i_row);
	void showZombieSlide();

	void onAnimDone(const std::string &i_animLabel);
	
#ifndef WANTS_CHEATS_DISABLED
	void onDraw(Graphics* i_g) override;
#endif
	
private:	
	GridItemSliderDirection getSliderDirection() const;
	
	void setState(SliderState i_state);
	void updateState();
	
	SliderState m_state;
	pvztime_t m_lastSlideTime;
};


class GridItemSliderTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemSliderTileProps, GridItemAnimationProps, RtClass);

	GridItemSliderTileProps()
	{
		Direction = SLIDE_DIRECTION_Invalid;
	}
	
	GridItemSliderDirection Direction;
	Sexy::Rect TargetRect;
};

class GridItemSliderTileAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemSliderTileAnimRig, PopAnimRig, RtClass);
	
	void PlaySlideIdle();
	void PlaySlideStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlaySlideLoop();
	void PlaySlideEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};


#endif /* defined(__PlantsVersusZombies2__GridItemSliderTile__) */
