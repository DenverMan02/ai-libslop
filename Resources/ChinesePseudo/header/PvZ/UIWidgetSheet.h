//
//  UIWidgetSheet.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __UIWIDGETSHEET_H__
#define __UIWIDGETSHEET_H__

#include "PropertySheetBase.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "UIWidgetAnchorEnums.h"

class UIWidgetSheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(UIWidgetSheet, PropertySheetBase, RtClass);

	UIWidgetSheet()
	{
		Class = "UIWidget";
		Parent = "";
		ParentAnchor = ANCHOR_TOPLEFT;
		Anchor = ANCHOR_TOPLEFT;
		ResourceGroup = "";
		Width = 0;
		Height = 0;
		VirtualWidth = 0;
        BoardScaledVirtualWidth = 0;
		VirtualHeight = 0;
		SizeFromImage = "";
		SizeFromScreen = false;
		WidthFromImage = "";
		HeightFromImage = "";
		WidthFromScreen = false;
		HeightFromScreen = false;
		InputPriority = 0;
		RenderOrder = 0;
		PositionOffset = SexyVector2(0, 0);
		ScalePositionOffset = false;
        ImmuneToDeviceScaling = false;
		VirtualHitInsets = Insets(0, 0, 0, 0);
        SingleInstance = false;
		SupportForFullScreen = false;
		UnlockFrom = "";
	}
	
	std::string		Class;
	std::string		Parent;
	AnchorType		ParentAnchor;
	AnchorType		Anchor;
	std::string		ResourceGroup;
	uint16			Width;
	uint16			Height;
	uint16			VirtualWidth;
	uint16			VirtualHeight;
	std::string		SizeFromImage;
	bool			SizeFromScreen;
	std::string		WidthFromImage;
	std::string		HeightFromImage;
	bool			WidthFromScreen;
	bool			HeightFromScreen;
	int8			InputPriority;
	int16			RenderOrder;
    uint16			BoardScaledVirtualWidth;
	SexyVector2		PositionOffset;
	bool			ScalePositionOffset;
    bool			ImmuneToDeviceScaling;
	Insets			VirtualHitInsets;
    bool            SingleInstance;
	bool			SupportForFullScreen;
	std::string		UnlockFrom;
};

typedef RtWeakPtr<UIWidgetSheet> UIWidgetSheetPtr;

#endif // __UIWIDGETSHEET_H__
