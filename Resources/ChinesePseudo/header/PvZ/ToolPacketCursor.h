//
//  ToolPacketCursor.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ToolPacketCursor__
#define __PlantsVersusZombies2__ToolPacketCursor__

#include "PacketCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"
#include "EffectAnimRig_LinkedTile.h"
#include "GridItemPowerTile.h"

class ToolPacketCursor : public PacketCursor
{
public:
	RT_CLASS_DEFINE(ToolPacketCursor, PacketCursor, RtClass) {}
    
	ToolPacketCursor() : PacketCursor(), m_packetData(NULL) {}
	ToolPacketCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);
    
	bool CanUseAtCurrentPosition() override;
	Point GetCurrentGridPosition() override;
    
protected:
	void tryToUse() override;
	Sexy::SexyVector2 getCursorAnimOffset() const override;
    
private:
	class ToolPacketData* m_packetData;
	RtWeakPtr<GridItemPowerTileProps> m_propsPtr;
};

#endif /* defined(__PlantsVersusZombies2__ToolPacketCursor__) */
