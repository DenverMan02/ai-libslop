//
//  MagicBeansCursor.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MagicBeansCursor__
#define __PlantsVersusZombies2__MagicBeansCursor__

#include "PVZTypes.h"
#include "PacketCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"

class MagicBeansCursor : public PacketCursor
{
public:
	RT_CLASS_DEFINE(MagicBeansCursor, PacketCursor, RtClass) {}

	MagicBeansCursor() {}
	~MagicBeansCursor();

	explicit MagicBeansCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);
	explicit MagicBeansCursor(const Sexy::Touch& i_boardSpaceTouch, PlantTypePtr i_plantType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0, 0, 0, 0), bool i_useBoost = false, int i_level = -1);

	void SetPlantingFreeForCursor(bool i_isPlantingFree);

	bool CanUseAtCurrentPosition() override;
	Point GetCurrentGridPosition() override;

	bool IsInsideOriginRect() const override;

	PlantTypePtr GetPlantType() const { return m_plantType; }

	bool DidPlant() const;

protected:
	Sexy::SexyVector2 getCursorAnimOffset() const override;
	//void onDraw(Sexy::Graphics* i_g) override;
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void cacheOrDestroyCursor();
	void tryToUse() override;

private:
	bool shouldInitializeToFreePlanting() const;
	bool canAffordPlant(PlantTypePtr i_plantType) const;
	void payForPlant(PlantTypePtr i_plantType);

	void	tryToPlantAt(const int i_gridX, const int i_gridY);
	Plant* tryReplaceExistingPlantAt(const int i_gridX, const int i_gridY);
	Plant* tryMakeNewPlantAt(const int i_gridX, const int i_gridY, int iLevel = -1);

	PlantTypePtr m_plantType;
	bool m_plantPlanted = false;
	bool m_isFreePlantingCursor = false;
	bool m_useBoost = false;
	int m_level;
	Sexy::SexyVector2 m_cursorOffset;
};

#endif /* defined(__PlantsVersusZombies2__MagicBeansCursor__) */
