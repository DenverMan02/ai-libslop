//
//  GridItemPowerTile.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 1/23/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemPowerTile__
#define __PlantsVersusZombies2__GridItemPowerTile__

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"
#include "PowerTileSubsystem.h"

namespace Message
{
    void PowerTilePlaced(GridItem* i_gridItem);
    void PowerTileRemoved(GridItem* i_gridItem);
}

class GridItemPowerTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemPowerTile, GridItemAnimation, RtClass);

	int CalcRenderOrder() const override;
	void SetIsOccupied(bool i_occupied);

	void OnPropagatedTo();
	void OnOccupantPlantfooded();

	PowerTileClass GetTileClass() const;
	
	bool IsDisabled() const { return IsHidden(); }

protected:
	void registerForEvents() override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onPlaceOnBoard() override;

private:
	void onRegionChanged(class BoardRegion* i_region);
	void updateVisibility();
	
	bool m_isPlantFoodActive = false;
};


class GridItemPowerTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemPowerTileProps, GridItemAnimationProps, RtClass);

	GridItemPowerTileProps()
	{
		TileClass = POWERTILE_Invalid;
	}

	PowerTileClass TileClass;
	Color TileColor;
};

#endif /* defined(__PlantsVersusZombies2__GridItemPowerTile__) */
