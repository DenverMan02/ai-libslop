//
//  PVZ2UIButton.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 3/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZ2UIButton__
#define __PlantsVersusZombies2__PVZ2UIButton__

#include "ButtonWidget.h"
#include "CheckboxListener.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "TodCommon.h"
#include "ResourceHelpers.h"
#include "EditWidget.h"
#include "TimeLine.h"
#include "Whitelistable.h"
#include "PrimeTextWidget.h"

namespace Sexy
{
	class Image;
}

enum PVZ2UIButtonType
{
	PVZ2UIBUTTON_DEFAULT,
	PVZ2UIBUTTON_RADIO,
	PVZ2UIBUTTON_NORMAL,
	PVZ2UIBUTTON_DIALOG,
};

enum PVZButtonJustification
{
	BUTTON_JUST_LEFT	= -1,
	BUTTON_JUST_CENTER,
	BUTTON_JUST_RIGHT
};

enum PVZ2UIImageType
{
	PVZ2UIIMAGE_INITIALIZED = 0,
	PVZ2UIIMAGE_SINGLE = 1,
	PVZ2UIIMAGE_SINGLE_STRETCHED = 2,
	PVZ2UIIMAGE_3SLICE_SINGLE_IMAGE = 3,
	PVZ2UIIMAGE_3SLICE_MULTI_IMAGE = 4,
	PVZ2UIIMAGE_9SLICE_SINGLE_IMAGE = 5,
    PVZ2UIIMAGE_SINGLE_SHAKE = 6,
    PVZ2UIIMAGE_SINGLE_MIRROR = 7,
    PVZ2UIIMAGE_SINGLE_ROTATED = 8,
	PVZ2UIIMAGE_SINGLE_ADJUST = 9,
	PVZ2UIIMAGE_SINGLE_ADJUST_IN_INSCRIBED_CIRCLE = 10,
    PVZ2UIIMAGE_HORIZONTAL_CROP = 11,
    PVZ2UIIMAGE_VERTICAL_CROP = 12,
    PVZ2UIIMAGE_AUTO_CROP = 13,
    
    PVZ2UIIMAGE_MAX,
};

class PVZ2UIImage
{
public:
	PVZ2UIImage();
	PVZ2UIImage(Sexy::Image* i_singleImage, const PVZ2UIImageType i_imageType=PVZ2UIIMAGE_SINGLE);
	PVZ2UIImage(CachedUIResourcePtr<Sexy::Image>& i_singleImage, const PVZ2UIImageType i_imageType=PVZ2UIIMAGE_SINGLE);
	PVZ2UIImage(Sexy::Image* i_leftImage, Sexy::Image* i_middleImage, Sexy::Image* i_rightImage);

	void Draw(Sexy::Graphics* i_g, Sexy::Rect i_drawRect);
	bool IsValid() const { return m_imageType != PVZ2UIIMAGE_INITIALIZED; }
    
	//PVZ2_CHINESE_START
    int GetWidth() const;
    int GetHeight() const;
    
    void ShakeDraw(Sexy::Graphics* i_g, Sexy::Rect& i_drawRect);
    
	//PVZ2_CHINESE_END

	PVZ2UIImageType m_imageType;

	Sexy::Image* m_singleImage;
	Sexy::Image* m_leftImage;
	Sexy::Image* m_middleImage;
	Sexy::Image* m_rightImage;
    
    pvztime_t    m_iNextShakeTime;
    bool         m_bShaking;
    int          m_iShakeStep;
    float        m_fRotate = 0.0f;
};

struct PVZ2UIButtonPart
{
//PVZ2_CHINESE_START
    PVZ2UIButtonPart() {
#ifdef WIDGETS_USE_PRIMETEXT
        mPrimeFont = NULL;
#endif
        mFont = NULL;
        mfScale = 1.0f;
        m_type = PVZ2UIBUTTONPARTTYPE_STRING;
        m_justification = BUTTON_JUST_LEFT;
        m_iconScale = 1.0f;
    }
//PVZ2_CHINESE_END
	enum PVZ2UIButtonPartType
	{
		PVZ2UIBUTTONPARTTYPE_STRING,
		PVZ2UIBUTTONPARTTYPE_STRINGWITHICON,
		PVZ2UIBUTTONPARTTYPE_IMAGE,
	} m_type;

	Sexy::Rect m_rect;
	PVZButtonJustification m_justification ;
	SexyString m_string;
	PVZ2UIImage m_image;
//PVZ2_CHINESE_START
#ifdef WIDGETS_USE_PRIMETEXT
    PrimeTypeface*          mPrimeFont;
#endif
	Font*					mFont;
    float                   mfScale;
    int m_iconBuffer;
    float m_iconScale;
//PVZ2_CHINESE_END
};

class PVZ2UIButton : public Sexy::ButtonWidget, public Whitelistable
{
public:
	PVZ2UIButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
	virtual ~PVZ2UIButton();

	void SetRadioStates(const PVZ2UIImage& i_unselectedImage, const PVZ2UIImage& i_selectedImage, const bool i_selected);
	void SetNormalStates(const PVZ2UIImage& i_backgroundImage, const PVZ2UIImage& i_iconImage);
	void SetDialogStates(const PVZ2UIImage& i_normalImage, const PVZ2UIImage& i_downImage);
    void SetDialogStates(const PVZ2UIImage& i_normalImage, const Sexy::Color& i_pressColor = Sexy::Color(90,90,90));

	void LinkRadioButtons(const std::vector<PVZ2UIButton*> i_siblingRadioButtons);
	void UnlinkRadioButton(PVZ2UIButton* pBtnUnlink);
	
	void SetTextJustification(const PVZButtonJustification i_textJustification);
	void SetLabelText(const SexyString& i_text); //override;
	void SetContentsRect(const Sexy::Rect& i_rect);
	void SetFont(PrimeTypeface* theFont) override;
    PVZButtonJustification GetTextJustification() const { return m_textJustification; }
    
    void SetOnlyDrawParts();

//PVZ2_CHINESE_BEGIN
    void LayoutPart(const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    
	void AddImage(const PVZ2UIImage& i_image, const Sexy::Rect& i_drawRect);
	void AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, Font *i_font, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    void AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, class PrimeText_PotentialTypeface *i_font, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    
    void AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    
    void AddImage(const PVZ2UIImage& i_image, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    void AddImageScale(const PVZ2UIImage& i_image, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER,float fScale=1.0f);
    void AddText(const SexyString& i_textString, Font *i_font, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    void AddText(const SexyString& i_textString, class PrimeText_PotentialTypeface *i_font, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    void AddText(const SexyString& i_textString, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
#ifdef WIDGETS_USE_PRIMETEXT
    void AddText(const SexyString& i_textString, Sexy::Rect i_drawRect, PrimeTypeface *i_font, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    void AddText(const SexyString& i_textString, PrimeTypeface *i_font, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER);
    PrimeTypeface* GetTextFontDrawn();
#endif
    void ClearButton();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g) override;
    virtual void Update() override;
    virtual void Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void Resize(const Sexy::Rect& theRect) override;
    //PVZ2_CHINESE_END
    
    // do nothing for the mouseup/mousedown because we want to only be touch based
    virtual void MouseDown(int i_x, int i_y, int i_btnNum, int i_clickCount) override {}
    virtual void MouseUp(int i_x, int i_y, int i_btnNum, int i_clickCount) override {}
    virtual void MouseUp(int theX, int theY, int theClickCount) override;
	virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchMoved(const Sexy::Touch& i_touch) override;
	virtual void TouchEnded(const Sexy::Touch& i_touch) override;
	virtual void TouchesCanceled() override;

	bool IsRadioButtonSelected() const { return m_radioButtonSelected; }
	void SetRadioButtonSelected();

	PVZ2UIImage	GetImageNormal() { return m_normalImage; }
	PVZ2UIImage	GetImageDown() { return m_selectedImage; }
    Color GetPressColor() { return m_pressColor; }
    Color GetNormalColor() { return m_normalColor; }

    void SetNormalColor(const Sexy::Color& i_color) { m_normalColor = i_color; }
    
	void SetClipDisabled(bool setting) { m_bClipDisabled = setting; }		// special handle for radio

    void SetButtonWithIcons();
    void SetDelayDisabled(float delay_time = 1.5f);
    void SetGray(bool setting) { m_bGray = setting; }
    bool IsGray() const { return m_bGray; }
    Sexy::Rect getContentsRect();
    void SetInvisible(bool i_invisible);
    void SetGrayscaleWhenDisabled(bool i_shouldGrayscale) { m_grayscaleWhenDisabled = i_shouldGrayscale; updateFontColor(); }
    void AddTextWithIcon(const SexyString& i_textString, const PVZ2UIImage& i_image, int i_iconBuffer, Sexy::Rect i_drawRect, const PVZButtonJustification i_justification=BUTTON_JUST_CENTER, float i_iconScale = 1.0f);
protected:
	DrawStringJustification getDrawStringJust(const PVZButtonJustification i_justification) const;
	int getPositionFromJustification(const PVZButtonJustification i_justification, const int i_xOff, const int i_width);
	void internalDraw(Graphics* i_g);
	Color& getFontColor();
	virtual void drawLabel(Graphics* i_g);

	bool m_radioButtonSelected;
	PVZ2UIButtonType m_buttonType;
	Sexy::Color m_fontColor;

	std::vector<PVZ2UIButton*> m_siblingRadioButtons;

	PVZ2UIImage m_normalImage;
	PVZ2UIImage m_iconImage;
	PVZ2UIImage m_selectedImage;

	PVZButtonJustification m_iconJustification;
	PVZButtonJustification m_textJustification;
	Sexy::Rect m_contentsRect;

	std::vector<PVZ2UIButtonPart> m_parts;

	Sexy::TouchID m_touchIdent;
	bool m_touchIsOver;
//PVZ2_CHINESE_START  
    bool m_bLayout;
    PVZButtonJustification m_layoutJustification;
//PVZ2_CHINESE_END
	bool m_bClipDisabled;
    float m_delayTime;
    bool m_bGray = false;
    Sexy::Color m_normalColor = Sexy::Color::White;
    Sexy::Color m_pressColor = Sexy::Color::White;
private:
    Sexy::PrimeTextWidget* m_textLabel;
    bool m_grayscaleWhenDisabled;
    bool m_invisible;

    void updateFontColor();
};

class PVZ2UICheckBox : public Sexy::ButtonWidget
{
public:
	PVZ2UICheckBox(int i_id, Sexy::ButtonListener* i_listener, Sexy::CheckboxListener* i_checkboxListener);

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void MouseUp(int i_x, int i_y, int i_btnNum, int i_clickCount);

	void SetCheckboxStates(Sexy::Image* i_backgroundImage, Sexy::Image* i_checkImage, const bool i_checked, const int i_xCheckOff = 0, const int i_yCheckOff = 0);

	void SetRightAligned(bool i_rightAligned);

	bool IsChecked() const { return m_checked; }
	void SetChecked(const bool i_checked) { m_checked = i_checked; }

private:

	bool m_checked;
	int m_checkOffsetX;
	int m_checkOffsetY;

	bool m_rightAligned;

	class Sexy::CheckboxListener* m_checkboxListener;
};

class PVZ2UIScrollingWidget : public Sexy::ScrollWidget
{
	RT_CLASS_DEFINE(PVZ2UIScrollingWidget, Sexy::ScrollWidget, RtClass);
public:
	PVZ2UIScrollingWidget();
	PVZ2UIScrollingWidget(Sexy::ScrollWidgetListener* i_listener);

	void SetBackground(const PVZ2UIImage& i_backgroundImage) { m_backgroundImage = i_backgroundImage; }

	virtual void Draw(Sexy::Graphics* i_g);

private:

	PVZ2UIImage m_backgroundImage;
};

class PVZ2UIEditWidget : public Sexy::EditWidget
{
public:
	PVZ2UIEditWidget(const Sexy::Rect& i_rect, int i_id, Sexy::EditListener* i_editListener, const SexyString& i_defaultString, const bool i_clearOnFocus);

	void SetBackground(const PVZ2UIImage& i_backgroundImage) { m_backgroundImage = i_backgroundImage; }
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Sexy::Graphics* i_g);

private:

	PVZ2UIImage m_backgroundImage;
};

class PVZ2UIScrollingPaneWidget : public Sexy::Widget
{
	RT_CLASS_DEFINE(PVZ2UIScrollingPaneWidget, Sexy::Widget, RtClass);
public:
	PVZ2UIScrollingPaneWidget();
	PVZ2UIScrollingPaneWidget(const Sexy::Rect& i_rect, Sexy::Widget* i_parentWidget, Sexy::Widget* i_firstWidget=NULL);
	virtual ~PVZ2UIScrollingPaneWidget();

	virtual void Update();
    virtual void Close();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);

	void ScrollRight(Sexy::Widget* i_scrollingToWidget);
	void ScrollLeft();

	int GetDepth() const { return static_cast<int>(m_widgetPanes.size()); }
    
    void SetDarkenLayer(bool darkenBackground) { m_drawDarkeningLayerBehind = darkenBackground; }

private:
	void removeAndHide();
	void deleteRightWidget();
    bool onlyWidgetPaneLeftIsInvisible();
	std::vector<Sexy::Widget*> m_widgetPanes;
	TimeLineTrack<float> m_scrollTimeline;
    bool m_drawDarkeningLayerBehind;
	enum ScrollingPaneWidgetState
	{
		SCROLLING_NONE,
		SCROLLING_RIGHT,
		SCROLLING_LEFT,
	} m_scrollingState;

	Sexy::Widget* m_parentWidget;
};

namespace PVZ2UI
{
	void LinkRadioButtons(const std::vector<PVZ2UIButton*> i_siblingRadioButtons);
}

#endif /* defined(__PlantsVersusZombies2__PVZ2UIButton__) */
