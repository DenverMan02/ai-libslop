//
//  HotUISeedPacket.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 9/14/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef HotUISeedPacket_h
#define HotUISeedPacket_h

#include "HotUIWidget.h"
#include "HotUIAdaptor.h"
#include "SeedPacketUtils.h"

struct HotUISeedPacketConfig
{
	HotUISeedPacketConfig()
	: PlantLevel(-1)
	, IsImitater(false)
	, PlantType("")
	, Grayscale(false)
	{}
	
	std::string PlantType;
	bool IsImitater;
	int PlantLevel;
	bool Grayscale;
};

class HotUISeedPacket : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUISeedPacket, HotUIWidget, RtClass);
	
	HotUISeedPacket();
	
	void SetPacketConfig(const HotUISeedPacketConfig& i_config);
	void SetPacketColor(Color i_color) { m_color = i_color; }
	void SetImageGrayscale(bool i_grayscale) { m_seedPacketConfig.Grayscale = i_grayscale; }
	
protected:
	void onInitializeWidget() override;
	void onDraw(Sexy::Graphics* i_g) override;
	
private:
	HotUISeedPacketConfig m_seedPacketConfig;
	bool m_packetRenderDataSet;
	PacketRenderData m_packetRenderData;
	Color m_color;
};

class HotUISeedPacketProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUISeedPacketProperties, HotUIWidgetProperties, RtClass);
	
	RtClass* GetWidgetClass() const override
	{
		return HotUISeedPacket::StaticGetClass();
	}
	
	//PacketRenderOptions RenderOptions;
	HotUISeedPacketConfig PacketConfig;
};

class HotUISeedPacketList : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUISeedPacketList, HotUIWidget, RtClass);
	
	HotUISeedPacketList()
		: m_rowsBuilt(false)
	{}
	
	void SetSeedTypes(const std::vector<HotUISeedPacketConfig>& i_packetConfigs, int i_maxPerRow = 0);
	
private:
	void ensureRowsBuilt();
	
	struct SeedPacketRow
	{
		class HotUIHorizontalList* List;
		std::vector<HotUISeedPacket*> Packets;
	};
	
	std::vector<SeedPacketRow> m_rows;
	bool m_rowsBuilt;
};

class HotUISeedPacketListProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUISeedPacketListProperties, HotUIWidgetProperties, RtClass);
	
	RtClass* GetWidgetClass() const override
	{
		return HotUISeedPacketList::StaticGetClass();
	}
};

#endif /* HotUISeedPacket_h */
