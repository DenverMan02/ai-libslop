//
//  GridItemGoldTile.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemGoldTile__
#define __PlantsVersusZombies2__GridItemGoldTile__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

enum GoldTileState
{
	GOLD_TILE_INITIAL,
	GOLD_TILE_PLANT_HELD,
	GOLD_TILE_PLANT_LOST
};

class GridItemGoldTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemGoldTile, GridItemAnimation, RtClass);
	
	int CalcRenderOrder() const override;
	void SetIsOccupied(bool i_occupied);
	
	void OnOccupantPlantfooded();
	
	bool IsDisabled() const { return IsHidden(); }
	bool IsTileOccupied();
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
protected:
	void registerForEvents() override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onPlaceOnBoard() override;
	
private:
	void onRegionChanged(class BoardRegion* i_region);
	void onGameplayEnded();
	void onPlantPlaced(Plant* i_plant);
	void updateVisibility();
	void produceSun(int producedAmount);
	void updateTileState();
	void spawnInitialSun();
	void updateSunSpawner();
	void playStateAnim();
	void playInitialSunAwardAnim();
	void playRecurringSunAwardAnim();

	void onAnimDone(const std::string& i_animName);

	pvztime_t m_nextSunSpawnTime = PVZ_EOT();
	GoldTileState m_tileState = GOLD_TILE_INITIAL;
	RtWeakPtr<Plant> m_plantOnTile;
};


class GridItemGoldTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemGoldTileProps, GridItemAnimationProps, RtClass);
	
	GridItemGoldTileProps()
	{
		SunGrantedPerPlant = 50;
		SunGrantedOnFirstPlant = 100;
		TimeBetweenPlantSpawnedSunDrops = 5.0f;
	}
	
	int SunGrantedPerPlant;
	int SunGrantedOnFirstPlant;
	pvztime_t TimeBetweenPlantSpawnedSunDrops;
};

#endif /* defined(__PlantsVersusZombies2__GridItemGoldTile__) */
