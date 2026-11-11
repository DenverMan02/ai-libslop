//
//  HotUIButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIButton__
#define __PlantsVersusZombies2__HotUIButton__

#include <string>

#include "HotUIImage.h"
#include "HotUIWidget.h"
#include "Image.h"
#include "Insets.h"
#include "PVZ2UIButton.h"
//#include "PVZ2UIImage.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyString.h"
#include "Core.h"

namespace Sexy {
class ButtonListener;
class PrimeTypeface;
}  // namespace Sexy
//#include "PVZ2UIImage.h"
//#include "PrimeTextWidget.h"

typedef RtWeakPtr<class HotUILabel> HotUIButtonPtr;
typedef RtWeakPtr<class HotUILabelProperties> HotUIButtonPropertiesPtr;

class HotUIButton: public HotUIWidget, public ButtonListener
{
public:

	RT_CLASS_DEFINE(HotUIButton, HotUIWidget, RtClass);
	
	HotUIButton();
	
	virtual ~HotUIButton();
	
	// Widget management
	void					SetFont(PrimeTypeface* i_font);
	PrimeTypeface*			GetFont();
	void					SetListener(ButtonListener* i_listener);
	void					SetListener(const int i_buttonID, ButtonListener* i_listener);
	void					SetLabel(SexyString i_label);
	SexyString				GetLabel() {return m_labelText;}
	void					SetLabelWithImage(SexyString i_label, ImagePtr i_image, int i_buffer);
	void					SetInvisible(bool i_invisible);
	void					SetDisabled(bool i_disabled) override;
	void					ButtonPress(int i_buttonID) override;
	void					ButtonDepress(int i_buttonID) override;
    void                    SetUpAudio(std::string i_upAudio);
	void                    SetDownAudio(std::string i_downAudio);
	void					SetUpImage(ImagePtr i_image) { m_upImage = i_image; initializeButtonStates(); setButtonSize(); }
	void					SetDownImage(ImagePtr i_image) { m_downImage = i_image; initializeButtonStates(); setButtonSize(); }
	PVZ2UIButton*			GetButtonWidget() { return m_buttonWidget; }
	void					SetDrawGrayscaleWhenDisabled(bool i_drawGrayscale);
	void                    SetAdditionalContentsInset(const Insets& i_inset);

	ImagePtr          		GetUpImage() { return m_upImage; }
	ImagePtr          		GetDownImage() { return m_downImage; };

protected:

	// Widget initialization
	void					onInitializeWidget() override;
	void					assignImagesFromProcessedStrings();
	void					onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;
	
	// Widget layout
	void					onLayoutFinalized() override;
	Insets					getContentBounds() override;
	int						getImageWidthForResizeData() override;
	int						getImageHeightForResizeData() override;
	
	void                    setButtonSize();
	void                    getImageAspectRatioStretchedData(UIImageDrawStyle i_drawStyle, ImagePtr i_image, float &io_width, float &io_height, float &io_x, float &io_y);

	// Serialized
	
	// Not serialized
	SexyString				m_labelText;
	class PrimeTypeface*	m_fontTypeface;
	Color					m_textColor;
	PVZ2UIButton*			m_buttonWidget;
	PVZ2UIImageType			m_buttonImageType;
	ImagePtr				m_upImage;
	ImagePtr				m_downImage;
	Insets                  m_externalInset;
	std::string				m_processedUpImageName;
	std::string				m_processedDownImageName;
	std::string				m_processedUpAudioName;
	std::string				m_processedDownAudioName;
	ButtonListener*			m_adaptorListener;
	
private:
	
	void					initializeButtonStates();
	
};

class HotUIButtonProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIButtonProperties, HotUIWidgetProperties, RtClass);

	HotUIButtonProperties()
	{
		UpImage = "IMAGE_UI_GENERIC_PURPLEBUTTON";
		DownImage = "IMAGE_UI_GENERIC_PURPLEBUTTON_DOWN";
		HideButtonImages = false;
		UpAudio = "";
		DownAudio = "";
		ButtonImageType = UIIMAGE_TYPE_3SLICE_HORIZONTAL;
		ButtonImageDrawStyle = UIIMAGE_DRAW_STYLE_NORMAL;
	};

	RtClass* GetWidgetClass() const override
	{	
		return HotUIButton::StaticGetClass();
	}
	
	std::string						Label;
	DynamicPadding					LabelInset;
	std::string						UpImage;
	std::string						DownImage;
	bool							HideButtonImages;
	std::string						UpAudio;
	std::string						DownAudio;
	UIImageType						ButtonImageType;
	UIImageDrawStyle				ButtonImageDrawStyle;
//	UITextHorizontalJustification	HorizontalJustification;
//	UITextVerticalJustification		VerticalJustification;
	std::string						Font;
	std::string						Color;
	std::string						WhitelistID;
};

#endif /* defined(__PlantsVersusZombies2__HotUIButton__) */
