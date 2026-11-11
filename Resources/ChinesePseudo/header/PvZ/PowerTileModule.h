//
//  PowerTileModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/27/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerTileModule__
#define __PlantsVersusZombies2__PowerTileModule__

#include "GridItemPowerTile.h"
#include "LevelModule.h"

struct PowerTileEntry
{
	PowerTileEntry()
	{
		Group = POWERTILE_Invalid;
	}
	Sexy::Point	 		Location;
	PowerTileClass		Group;
};

class PowerTileModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PowerTileModule, LevelModule, RtClass) {}

	void ReRollTiles();
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void setupLinkedTiles();
	bool tileLayoutFits(const std::vector<Sexy::Point>& i_tilePoints, const Point& i_upperLeft);
};

class PowerTileProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PowerTileProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PowerTileModule::StaticGetClass();
	}
	
	std::vector<PowerTileEntry> LinkedTiles;
};


#endif /* defined(__PlantsVersusZombies2__PowerTileModule__) */
