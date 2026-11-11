//
//  HotUISlider.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/21/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUISlider__
#define __PlantsVersusZombies2__HotUISlider__

#include <string>

#include "HotUIWidget.h"
#include "Image.h"
#include "Insets.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyAppFramework/Slider.h"
#include "SexyAppFramework/SliderListener.h"

typedef RtWeakPtr<class HotUISlider> HotUISliderPtr;
typedef RtWeakPtr<class HotUISliderProperties> HotUISliderPropertiesPtr;

class HotUISlider: public HotUIWidget, public SliderListener
{
public:

	RT_CLASS_DEFINE(HotUISlider, HotUIWidget, RtClass);
	
	HotUISlider()
	{
		
	};
	
	virtual ~HotUISlider()
	{
		RemoveWidget(m_sliderWidget);
		delete m_sliderWidget;
	};

	// Slider management
	void					SetValue(const double i_soundVolume);
	void					SetListener(const int i_sliderID, SliderListener* i_listener);
	
protected:

	// Widget initialization
	void			onInitializeWidget() override;
	void			onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;
	
	// Widget layout
	void			onLayoutFinalized() override;
	Insets			getContentBounds() override;
	int				getImageWidthForResizeData() override;
	int				getImageHeightForResizeData() override;
	
private:
	
	// Serialized
	
	// Not serialized
	std::string				m_processedKnobImageName;
	std::string				m_processedBarImageName;
	std::string				m_processedFillImageName;
	ImagePtr				m_knobImage;
	ImagePtr				m_barImage;
	ImagePtr				m_fillImage;
	Slider*					m_sliderWidget;
};

class HotUISliderProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUISliderProperties, HotUIWidgetProperties, RtClass);

	HotUISliderProperties()
	{}

	RtClass* GetWidgetClass() const override
	{	
		return HotUISlider::StaticGetClass();
	}
	
	std::string				SliderKnobImage;
	std::string				SliderBarImage;
	std::string				SliderFillImage;
};


#endif /* defined(__PlantsVersusZombies2__HotUISlider__) */
