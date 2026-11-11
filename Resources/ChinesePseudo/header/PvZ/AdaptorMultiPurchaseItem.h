//
//  AdaptorMultiPurchaseItem.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 2/15/18.
//  Copyright © 2018 PopCap Games. All rights reserved.
//

#ifndef AdaptorMultiPurchaseItem_h
#define AdaptorMultiPurchaseItem_h

#include "AwardEnums.h"
#include "HotUIAdaptor.h"
#include "LevelOfTheDay_RewardData.h"

struct AdaptorMultiPurchaseItemConfig
{
	enum DisplayStyle
	{
		Compact,
		BigHorizontal,
		BigHorizontal_Right,
		CompactItemOnly,
		WorldPreviewUpgrade,
		WorldPreviewPinata,
        RiftCompact
	};
	
	AdaptorMultiPurchaseItemConfig()
	{
		IsGuaranteed = false;
		IsGrayscale = false;
		IsLocked = false;
	}
	
	AdaptorMultiPurchaseItemConfig(AwardType i_type, const std::string& i_item, int i_min, int i_max, bool i_isGuaranteed, bool i_isGrayscale, bool i_isLocked, DisplayStyle i_style = Compact) :
		Type(i_type),
		Item(i_item),
		Min(i_min),
		Max(i_max),
		IsGuaranteed(i_isGuaranteed),
		IsGrayscale(i_isGrayscale),
		IsLocked(i_isLocked),
		Style(i_style)
	{}
	
	AdaptorMultiPurchaseItemConfig(const LevelOfTheDay_RewardItemType* i_item, DisplayStyle i_style);
	
	AwardType	Type;
	std::string	Item;
	int			Min;
	int			Max;
	bool		IsGuaranteed;
	bool		IsGrayscale;
	bool		IsLocked;
	DisplayStyle	Style;
};

class AdaptorMultiPurchaseItem : public HotUIAdaptor
{

	struct MultiPurchaseItemVisibility
	{
		bool Image = false;
		bool SeedPacket = false;
		bool Anim = false;
	};
	
public:
	RT_CLASS_DEFINE(AdaptorMultiPurchaseItem, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorMultiPurchaseItem()
		: m_parent(nullptr)
	{
		m_displayDirty = false;
	}
	
	void Configure(WidgetContainer* i_parent, const AdaptorMultiPurchaseItemConfig& i_config);
	void Update() override;
	AdaptorMultiPurchaseItemConfig GetConfig() { return m_config; }
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
private:
	void prepareDisplayItem(HotUIStringMap& i_stringMap);
	std::string createAmountRangeDescription(int i_min, int i_max);
    
    std::string createBasicCountDescription(int i_amount, int i_secondAmount);
	std::string createMultiplierDescription(int i_amount);
    std::string createAddedAmountDescription(int i_amount, int i_secondAmount);

	std::vector<std::string> m_itemResourceGroups;
	WidgetContainer* m_parent;
	AdaptorMultiPurchaseItemConfig m_config;
	bool m_displayDirty;
	
	MultiPurchaseItemVisibility m_widgetVisibility;
};

class AdaptorMultiPurchaseItemSpacer : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorMultiPurchaseItemSpacer, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorMultiPurchaseItemSpacer()
	: m_parent(nullptr)
	{}
	
	void Configure(Sexy::WidgetContainer *i_parent);
	
protected:
	void onLoadUIView() override;
	
private:
	WidgetContainer* m_parent;
};


#endif
