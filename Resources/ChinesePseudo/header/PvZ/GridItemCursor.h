//
//  GridItemCursor.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/8/4.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemCursor__
#define __PlantsVersusZombies2__GridItemCursor__

#include "PacketCursor.h"
#include "PVZTypes.h"
#include "SeedPacket.h"

class GridItemCursor : public PacketCursor
{
public:
    RT_CLASS_DEFINE(GridItemCursor, BaseCursor, RtClass) {}
    
    GridItemCursor() {}
    explicit GridItemCursor(const Sexy::Touch& i_touch, SeedPacketPtr i_seedPacket);
    explicit GridItemCursor(const Sexy::Touch& i_touch, GridItemTypePtr i_seedGridItemType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0));
    
    Point GetCurrentGridPosition() override;
    bool CanUseAtCurrentPosition() override;
    void SetPlantingFreeForCursor(bool i_isPlantingFree);
    bool DidPlant() const;
    bool CanPlantBesiegeBox(int i_gridX, int i_gridY) const;
    bool IsRightTutorialBesiegeBox(int i_gridX, int i_gridY) const;
    bool IsInsideOriginRect() const override;
    
protected:
    void onDraw(Graphics* i_g) override;
//    Sexy::SexyVector2 getCursorAnimOffset() const override;
    void tryToUse() override;
    
private:
    bool shouldInitializeToFreePlanting() const;
    bool canAffordPlant(GridItemTypePtr i_plantType) const;
    void tryToPlant();
    
    GridItemTypePtr m_gridItemType;
    bool m_gridItemPlanted = false;
    bool m_isFreePlantingCursor = false;
};

#endif /* defined(__PlantsVersusZombies2__GridItemCursor__) */
