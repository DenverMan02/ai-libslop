//
//  ZombieCursor.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-22.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieCursor__
#define __PlantsVersusZombies2__ZombieCursor__

#include "PacketCursor.h"
#include "PVZTypes.h"
#include "SeedPacket.h"

class ZombieCursor : public PacketCursor
{
public:
	RT_CLASS_DEFINE(ZombieCursor, PacketCursor, RtClass) {}
    
	ZombieCursor() {}
	explicit ZombieCursor(const Sexy::Touch& i_touch, SeedPacketPtr i_seedPacket);
    explicit ZombieCursor(const Sexy::Touch& i_touch, ZombieTypePtr i_seedZombieType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0));
    
    Point GetCurrentGridPosition() override;

    bool DidPlant() const;
    
    bool IsInsideOriginRect() const override;
    
protected:
	Sexy::SexyVector2 getCursorAnimOffset() const override;
    void tryToUse() override;
    
private:
	void tryToPlant();
  
protected:
	ZombieTypePtr m_zombieType;
    bool m_zombiePlanted = false;
};

#endif /* defined(__PlantsVersusZombies2__ZombieCursor__) */
