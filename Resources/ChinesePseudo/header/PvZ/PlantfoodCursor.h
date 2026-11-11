//
//  PlantfoodCursor.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantfoodCursor__
#define __PlantsVersusZombies2__PlantfoodCursor__

#include "BaseCursor.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
struct Touch;
}  // namespace Sexy

//Helper class to be used by Crazy Olaf to keep code paths in sync
bool ApplyPlantFoodToPlantGroup(class PlantGroup* i_plant);

class PlantfoodCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(PlantfoodCursor, BaseCursor, RtClass) {}

	PlantfoodCursor() {}
	PlantfoodCursor(const Sexy::Touch& i_boardSpaceTouch);

	virtual bool canApplyPlantfood(int i_x, int i_y);
	virtual void applyPlantfood(class Plant* i_plant);

protected:
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void onDraw(Sexy::Graphics* i_g) override;

private:
	void tryToUsePlantfood();
	bool applyPlantFoodToGridItem();
	bool m_isSoccerGame;
	bool m_isNostalgicGame;
	bool m_isUsed;
};

//Helper class to be used by Crazy Olaf to keep code paths in sync
bool ApplyPlantFoodToPlant(class PlantGroup* i_plant, PlantfoodCursor* i_cursor);

namespace Message
{
	// void PlantfoodUsed(const std::string& i_plantName);
	// void ToolAppliedPlantfood(class Plant* i_plant);
	void ToolAppliedPlantfoodToGridItem(class GridItem* i_gridItem);
    // void CanApplyPlantfood(class Plant* i_plant, bool* o_isCan);
    // void ApplySoccerPlantfood(class Plant* i_plant);
	
	
	void ToolAppliedPlantfood(class PlantGroup* i_group);
	void CanApplyPlantfood(class PlantGroup* i_plant, bool* o_isCan);
	void ApplySoccerPlantfood(class PlantGroup* i_plant);
}

#endif /* defined(__PlantsVersusZombies2__PlantfoodCursor__) */
