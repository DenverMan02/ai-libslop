//
//  HotUITextEntry.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/7/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUITextEntry__
#define __PlantsVersusZombies2__HotUITextEntry__

#include "HotUIWidget.h"
#include "RtObject.h"
#include "PVZ2UIButton.h"

class HotUITextEntry : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUITextEntry, HotUIWidget, RtClass);

	HotUITextEntry() { m_editWidget = nullptr; }
	virtual ~HotUITextEntry();

	void SetListener(Sexy::EditListener* i_editListener);
	SexyString GetTextEntryString() const;
	bool IsDefaultText() const;
	void SetEditWidgetActive();

protected:
	void onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;
	void onInitializeWidget() override;
	void onLayoutFinalized() override;

private:
	PVZ2UIEditWidget* m_editWidget;
	SexyString m_defaultText;
};

class HotUITextEntryProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUITextEntryProperties, HotUIWidgetProperties, RtClass);

	HotUITextEntryProperties()
	{
		MaxCharacters = 12;
		UseNumericKeyboard = false;
	}

	RtClass* GetWidgetClass() const override
	{
		return HotUITextEntry::StaticGetClass();
	}

	std::string	DefaultText;
	int MaxCharacters;
	bool UseNumericKeyboard;
};

#endif /* defined(__PlantsVersusZombies2__HotUITextEntry__) */
