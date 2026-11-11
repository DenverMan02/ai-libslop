//
//  PlantCursor.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantCursor__
#define __PlantsVersusZombies2__PlantCursor__

#include "PVZTypes.h"
#include "PacketCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"

class PlantCursor : public PacketCursor
{
public:
	RT_CLASS_DEFINE(PlantCursor, PacketCursor, RtClass) {}

	PlantCursor() {}
    ~PlantCursor();
    
	explicit PlantCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket, int i_level = -1);
	explicit PlantCursor(const Sexy::Touch& i_boardSpaceTouch, PlantTypePtr i_plantType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0), bool i_useBoost = false, int i_level = -1);

	void SetPlantingFreeForCursor(bool i_isPlantingFree);

	bool CanUseAtCurrentPosition() override;
	Point GetCurrentGridPosition() override;

    bool IsInsideOriginRect() const override;
    
	PlantTypePtr GetPlantType() const { return m_plantType; }

	bool DidPlant() const;

protected:
	Sexy::SexyVector2 getCursorAnimOffset() const override;
	void tryToUse() override;
	virtual Plant* makeNewPlantAt(PlantTypePtr i_type, const int i_gridX, const int i_gridY, int iLevel = -1, bool i_useBoost = false);
	virtual bool canAffordPlant(PlantTypePtr i_plantType, int i_level) const;
	int payForPlant(PlantTypePtr i_plantType);
	bool getIsFreePlantingCursor() const { return m_isFreePlantingCursor; }
	bool getPlantPlanted() const { return m_plantPlanted; }
	Plant*	tryReplaceExistingPlantAt(const int i_gridX, const int i_gridY);
	Plant*	tryMakeNewPlantAt(const int i_gridX, const int i_gridY, int iLevel = -1);

private:
	bool shouldInitializeToFreePlanting() const;	
	void	tryToPlantAt(const int i_gridX, const int i_gridY);
	
	PlantTypePtr m_plantType;
	bool m_plantPlanted = false;
	bool m_isFreePlantingCursor = false;
	bool m_useBoost = false;
	int m_level;
};

#endif /* defined(__PlantsVersusZombies2__PlantCursor__) */
