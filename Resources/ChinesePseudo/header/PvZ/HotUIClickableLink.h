//
//  HotUIClickableLink.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIClickableLink__
#define __PlantsVersusZombies2__HotUIClickableLink__

#include "HotUIWidget.h"
#include "RtObject.h"
#include "HyperlinkWidget.h"

class HotUIClickableLink : public HotUIWidget, public Sexy::ButtonListener
{
public:
	RT_CLASS_DEFINE(HotUIClickableLink, HotUIWidget, RtClass);

	HotUIClickableLink();
	virtual ~HotUIClickableLink();
	void ButtonDepress(int i_buttonID) override;

protected:
	void onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;
	void onInitializeWidget() override;
	void onLayoutFinalized() override;
	Insets getContentBounds() override;

private:
	Sexy::HyperlinkWidget* m_hyperlinkWidget;
	class PrimeTypeface* m_fontTypeface;
	SexyString m_labelText;
};

class HotUIClickableLinkProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIClickableLinkProperties, HotUIWidgetProperties, RtClass);

	HotUIClickableLinkProperties()
	{
		// do nothing
	}

	RtClass* GetWidgetClass() const override
	{
		return HotUIClickableLink::StaticGetClass();
	}

	std::string Text;
	std::string Link;
	std::string Font;
};

#endif /* defined(__PlantsVersusZombies2__HotUIClickableLink__) */
