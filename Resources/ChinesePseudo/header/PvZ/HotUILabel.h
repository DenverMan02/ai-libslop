//
//  HotUILabel.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUILabel__
#define __PlantsVersusZombies2__HotUILabel__

#include <string>

#include "HotUIWidget.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyString.h"

namespace Sexy {
class Graphics;
class PrimeTextWidget;
}  // namespace Sexy

typedef RtWeakPtr<class HotUILabel> HotUILabelPtr;
typedef RtWeakPtr<class HotUILabelProperties> HotUILabelPropertiesPtr;

enum UITextHorizontalJustification
{
	UITEXT_H_JUSTIFICATION_LEFT,
	UITEXT_H_JUSTIFICATION_CENTERED,
	UITEXT_H_JUSTIFICATION_RIGHT,
};

enum UITextVerticalJustification
{
	UITEXT_V_JUSTIFICATION_TOP,
	UITEXT_V_JUSTIFICATION_CENTERED,
	UITEXT_V_JUSTIFICATION_BOTTOM,
};

class HotUILabel: public HotUIWidget
{
public:

	RT_CLASS_DEFINE(HotUILabel, HotUIWidget, RtClass);

	HotUILabel()
	{
		m_primeTextWidget = nullptr;
	};

	virtual ~HotUILabel()
	{

	};

	virtual void	SetText(const SexyString& i_text);
	SexyString		GetText() {return m_labelText;}
	virtual void	SetTextColor(const Color& i_textColor);

	void 			RefreshMesh();

protected:

	// Widget initialization
	void			onInitializeWidget() override;
	void			onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;

	// Widget layout
	void			onLayoutFinalized() override;
	Insets			getContentBounds() override;

private:

	// Serialized

	// Not serialized
	SexyString				m_labelText;
	PrimeTextWidget*		m_primeTextWidget;
	EA::Text::HAlignment	m_HAlignment;
	EA::Text::VAlignment	m_VAlignment;
	class PrimeTypeface*	m_fontTypeface;
	Color					m_textColor;
};

class HotUILabelProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUILabelProperties, HotUIWidgetProperties, RtClass);

	HotUILabelProperties()
	{
		HorizontalJustification = UITEXT_H_JUSTIFICATION_CENTERED;
		VerticalJustification = UITEXT_V_JUSTIFICATION_CENTERED;
		IgnoreMouseInput = true;
		UsingMesh = false;
	};

	RtClass* GetWidgetClass() const override
	{
		return HotUILabel::StaticGetClass();
	}

	std::string						Label;
	UITextHorizontalJustification	HorizontalJustification;
	UITextVerticalJustification		VerticalJustification;
	std::string						Font;
	std::string						Color;
	bool							UsingMesh;

};


#endif /* defined(__PlantsVersusZombies2__HotUILabel__) */
