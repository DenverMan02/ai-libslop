//
//  PacketCursor.h
//  PlantsVersusZombies2
//
//	Defines a cursor to use an item from a packet (in the seedbank or on a conveyor belt, etc)
//
//  Created by Joseph Sola on 7/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PacketCursor__
#define __PlantsVersusZombies2__PacketCursor__

#include "BaseCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"

namespace Sexy {
struct Touch;
}  // namespace Sexy

class PacketCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(PacketCursor, BaseCursor, RtClass) {}

	PacketCursor() {}
	PacketCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);

	virtual bool CanUseAtCurrentPosition()
	{
		// IMPLEMENT ME!
		return false;
	}
	virtual Point GetCurrentGridPosition()
	{
		// IMPLEMENT ME!
		return Point(-1, -1);
	}

	SeedPacketPtr GetSeedPacket() const { return m_seedPacket; }

protected:
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	virtual void tryToUse()
	{
		// IMPLEMENT ME!
	}

	SeedPacketPtr m_seedPacket;
};


#endif /* defined(__PlantsVersusZombies2__PacketCursor__) */
