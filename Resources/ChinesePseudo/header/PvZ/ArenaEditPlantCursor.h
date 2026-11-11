//
//  ArenaEditPlantCursor.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-12-2.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaEditPlantCursor__
#define __PlantsVersusZombies2__ArenaEditPlantCursor__

#include "PVZTypes.h"
#include "PacketCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"
#include "Plant.h"

namespace Message
{
    void NotifySwitchPlant(Plant* i_originPlant, int i_gridX, int i_gridY);
}

class ArenaEditPlantCursor : public PacketCursor
{
public:
    RT_CLASS_DEFINE(ArenaEditPlantCursor, PacketCursor, RtClass) {}
    
    ArenaEditPlantCursor() {}
    explicit ArenaEditPlantCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket, Plant* i_originPlant);
    explicit ArenaEditPlantCursor(const Sexy::Touch& i_boardSpaceTouch, PlantTypePtr i_plantType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0), bool i_useBoost = false, Plant* i_originPlant = NULL);
    
    void SetPlantingFreeForCursor(bool i_isPlantingFree);
    
    bool CanUseAtCurrentPosition() override;
    Point GetCurrentGridPosition() override;
    
    bool IsInsideOriginRect() const override;
    
    PlantTypePtr GetPlantType() const { return m_plantType; }
    
    bool DidPlant() const;
    
protected:
    Sexy::SexyVector2 getCursorAnimOffset() const override;
    void tryToUse() override;
    virtual void onDestroy() override;
    
private:
    bool shouldInitializeToFreePlanting() const;
    bool canAffordPlant(PlantTypePtr i_plantType) const;
    void payForPlant(PlantTypePtr i_plantType);
    
    void	tryToPlantAt(const int i_gridX, const int i_gridY);
    Plant*	tryReplaceExistingPlantAt(const int i_gridX, const int i_gridY);
    Plant*	tryMakeNewPlantAt(const int i_gridX, const int i_gridY, int iLevel = -1);
    
    PlantTypePtr m_plantType;
    bool m_plantPlanted = false;
    bool m_isFreePlantingCursor = false;
    bool m_useBoost = false;
    PlantPtr m_originPlant;
};

#endif /* defined(__PlantsVersusZombies2__ArenaEditPlantCursor__) */
