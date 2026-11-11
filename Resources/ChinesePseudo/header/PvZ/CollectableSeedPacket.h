//
//  CollectableSeedPacket.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableSeedPacket_h
#define PlantsVersusZombies2_CollectableSeedPacket_h

#include <cstddef>
#include <string>

#include "Collectable.h"
#include "CollectableType.h"
#include "PVZTypes.h"
#include "PlatformAutodetect.h"
#include "RtObject.h"

namespace Sexy {
class DeviceImage;
class Graphics;
}  // namespace Sexy

class CollectableSeedPacketType : public CollectableType
{
	RT_CLASS_DEFINE(CollectableSeedPacketType, CollectableType, RtClass);
};

class BaseCursor;
class PlantCursor;

class CollectableSeedPacket : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableSeedPacket, Collectable, RtClass);
	
	void SetSeedType(const std::string& i_seedType);
	
#ifdef HOST_ANDROID
	CollectableSeedPacket();
	void Android_OnAppResumeFocus();
#endif

	int CalcRenderOrder() const override;

protected:
	void onDraw(class Sexy::Graphics* i_g) override;
	void onDestroy() override;
	
	virtual bool drawCost();
	virtual bool drawSelectionMarker();
	
	void drawToBuffer();
	
	PlantTypePtr m_seedType;
	DeviceImage* m_seedPacketImage = NULL;
};

class CollectableSeedPacketPlantable : public CollectableSeedPacket
{
public:
	RT_CLASS_DEFINE(CollectableSeedPacketPlantable, CollectableSeedPacket, RtClass);
	
	CollectableSeedPacketPlantable();

	void SetLevel(int i_level) { m_level = i_level; }

protected:
	void registerForEvents() override;
    bool onTouchEvent(const Sexy::Touch& i_touch) override;
    
	bool drawCost() override;
	bool drawSelectionMarker() override;
	
	void onCursorDestroyed(BaseCursor* i_cursor);
	
private:
	// Not serialized
	PlantCursor* m_packetCursor;
	int m_level;
};

#endif
