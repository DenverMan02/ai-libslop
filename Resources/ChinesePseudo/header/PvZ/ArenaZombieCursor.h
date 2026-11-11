//
//  ArenaZombieCursor.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-19.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaZombieCursor__
#define __PlantsVersusZombies2__ArenaZombieCursor__

#include "PacketCursor.h"
#include "PVZTypes.h"
#include "SeedPacket.h"

class ArenaZombieCursor : public PacketCursor
{
public:
    RT_CLASS_DEFINE(ArenaZombieCursor, PacketCursor, RtClass) {}
    
    ArenaZombieCursor() {}
    explicit ArenaZombieCursor(const Sexy::Touch& i_touch, SeedPacketPtr i_seedPacket);
    explicit ArenaZombieCursor(const Sexy::Touch& i_touch, ZombieTypePtr i_seedZombieType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0));
    
    Point GetCurrentGridPosition() override;
    
    bool DidPlant() const;
    
    bool IsInsideOriginRect() const override;
    
    Sexy::SexyVector2 getCursorAnimOffset() const override;
    
protected:
    //Sexy::SexyVector2 getCursorAnimOffset() const override;
    void tryToUse() override;
    
private:
    void tryToPlant();
    
protected:
    ZombieTypePtr m_zombieType;
    bool m_zombiePlanted = false;
};

#endif /* defined(__PlantsVersusZombies2__ArenaZombieCursor__) */
