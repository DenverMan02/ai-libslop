//
//  SeedPacket_Tool.h
//  PlantsVersusZombies2
//
//  Created by jsola on 9/4/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SeedPacket_Tool_h
#define PlantsVersusZombies2_SeedPacket_Tool_h

#include <string>

#include "RtObject.h"
#include "SeedPacket.h"

namespace Sexy {
    class Graphics;
    struct Touch;
}  // namespace Sexy

namespace Message
{
	void NotifyToolPacketUsed(const std::string& i_typeName, int i_delta, int i_usedCount);
}

class SeedPacket_Tool : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_Tool, SeedPacket, RtClass);
	
	virtual void Draw(Graphics* i_g) override;
	
	virtual void SetToolType(const std::string& i_tool);
	virtual bool OnTouch(const Sexy::Touch& i_touch) override;
	virtual SunCurrency GetSunCost() override { return 0; }
	virtual float GetPacketCoolDown() { return 0.0f; }
	virtual bool NeedDrawOffset() { return true; }
};

class SeedPacket_ToolRift : public SeedPacket_Tool
{
public:
	RT_CLASS_DEFINE(SeedPacket_ToolRift, SeedPacket_Tool, RtClass);

	SeedPacket_ToolRift();

	void Draw(Graphics* i_g) override;

	void SetToolType(const std::string& i_tool) override;
	bool OnTouch(const Sexy::Touch& i_touch) override;
	void CopyFrom(SeedPacket* pCopy) override;
	void SetPlantType(const PlantTypePtr i_plantType) override {}

	bool NeedDrawOffset() override { return false; }

	virtual bool Activate(const Point& i_point = Point(0, 0));
	SunCurrency GetSunCost() override;
	const ObjectTypeDescriptorPtr GetSeedType() override;

private:
	void OnNotifyToolPlantLevelUpMax(class ToolPacketData* i_data);
	void OnNotifyToolPlantfoodMax(ToolPacketData* i_data);
	void OnPlantfoodUsed(class PlantGroup* plant);
	void OnNotifyRiftTimedUsedMax();
	void OnInitBoardArtifactManager();
	void OnArtifactTrigger();

	class ToolPacketData* m_packetData;
	int m_usedCount;
};

#endif
