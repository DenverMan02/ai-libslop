//
//  PVZ2UIDialog.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/21/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

// 	General purpose dialog box, to be used at various points in PvZ2
//	Supports any number of the following inner elements:
//		- Header Label, above all other elements
//		- Contents Sub-widget, resized to fill unused area between header and footer
//		- Buttons, any number, layed out automatically on the bottom
//		- Footer Label, directly above buttons
//
//	Resizing this widget will cause all contained elements to be fit and sized automatically

#ifndef PlantsVersusZombies2_PVZ2UIDialog_h
#define PlantsVersusZombies2_PVZ2UIDialog_h

#include "PVZ2UIButton.h"
#include "WidgetButtonList.h"
#include "Effect_PopAnim.h"

enum UIDialogButtonType
{
	BUTTON_CANCEL
};

class PVZ2UIDialog : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	
	struct DialogConfig
	{
		DialogConfig()
		{
			DialogConfig(0,0,0,0,0,0,0);
            FooterPrimeFont = NULL;
            HeaderPrimeFont = NULL;
            FooterFont = NULL;
            HeaderFont = NULL;
            
		}
		DialogConfig(int i_ButtonWidth, int i_ButtonMaxWidth, int i_ButtonBuffer, int i_ButtonVertBuffer, int i_InnerBorder, int i_HeaderLabelHeight, int i_FooterLabelHeight)
			: ButtonWidth(i_ButtonWidth), ButtonMaxWidth(i_ButtonMaxWidth), ButtonBuffer(i_ButtonBuffer), ButtonVertBuffer(i_ButtonVertBuffer), InnerBorder(i_InnerBorder), HeaderLabelHeight(i_HeaderLabelHeight), FooterLabelHeight(i_FooterLabelHeight)
		{
            FooterPrimeFont = NULL;
            HeaderPrimeFont = NULL;
            FooterFont = NULL;
            HeaderFont = NULL;
        }
		
		int ButtonWidth;
        int ButtonMaxWidth;
		int ButtonBuffer;
        int ButtonVertBuffer;
		
		int InnerBorder;
		int HeaderLabelHeight;
		int FooterLabelHeight;
		
        //PVZ2_CHINESE_BEGIN
		PrimeTypeface* FooterPrimeFont;
        PrimeTypeface* HeaderPrimeFont;
        Font* FooterFont;
        Font* HeaderFont;
        //PVZ2_CHINESE_END
	};
	
    enum DialogButtonType
    {
        BUTTON_TYPE_GENERIC_PRIMARY,    // Purple
        BUTTON_TYPE_GENERIC_SECONDARY,  // Brown
    };
    
    static const uint DIALOG_HIDE_FLAG_BOX     = 0x01;
    static const uint DIALOG_HIDE_FLAG_HEADER  = 0x02;
    static const uint DIALOG_HIDE_FLAG_FOOTER  = 0x04;
    
public:
	PVZ2UIDialog();
	virtual ~PVZ2UIDialog();

	virtual void		Update();
	virtual void		Draw(Sexy::Graphics* i_g);
	void				DrawButtonsManually(Sexy::Graphics* i_g);

	void				SetButtonsVisible(const bool i_buttonsAreVisible);
	
	void				SetHeaderLabel(const SexyString& i_header);
	void				SetContents(Sexy::Widget* i_contentsWidget);
	Sexy::Widget*		GetContents() const;
	void				SetFooterLabel(const SexyString& i_footer);
	void				SetFooterBottomPadding(const int i_footerBottomPadding);
    void				SetFooterSeparator(bool hasFooterSeparator);
    void				SetHeaderFont(Sexy::PrimeTypeface* font, const Sexy::Color& color);
    void				SetHeaderFont(Sexy::Font* font, const Sexy::Color& color);
    void                SetHeaderHeight(int height);
    void                SetFooterHeight(int height);
    void				SetFooterFont(Sexy::PrimeTypeface* font, const Sexy::Color& color);
    void				SetFooterFont(Sexy::Font* font, const Sexy::Color& color);
    void                SetFooterAlign(DrawStringJustification i_align = DS_ALIGN_CENTER_VERTICAL_MIDDLE);
	void				SetBackgroundDarken(bool hasBackgroundDarken, float backgroundAlphaPercent = 0.5);
	void				SetAlwaysExist(bool bAlways){ m_bAlways = bAlways; }
	bool				GetAlwaysExist(){ return m_bAlways; }

	void                AutoHeight();
    void                AutoCenter();
	void				AddButton(int i_buttonID, const SexyString& i_label, Sexy::ButtonListener* i_listener, DialogButtonType buttonType = BUTTON_TYPE_GENERIC_PRIMARY);

    // helpers for legacy support
    PVZ2UIButton*       AddButton(int i_buttonId, const SexyString &i_label, Sexy::Delegate0 i_onPressed, DialogButtonType i_options = BUTTON_TYPE_GENERIC_PRIMARY);
	PVZ2UIButton*		AddButton(const SexyString& i_label, Sexy::Delegate0 i_onPressed, DialogButtonType buttonType = BUTTON_TYPE_GENERIC_PRIMARY);
    
    PVZ2UIButton* 		AddButton(PVZ2UIButton *i_button, Delegate0 i_onPressed);
    using OnPressedCallback = std::function<void()>;//must = Widget_ButtonList::OnPressedCallback;
    PVZ2UIButton*		AddButton(const SexyString& i_label, OnPressedCallback&& i_onPressed, DialogButtonType i_options = BUTTON_TYPE_GENERIC_PRIMARY);
    PVZ2UIButton* 		AddButton(PVZ2UIButton *i_button, OnPressedCallback&& i_onPressed);
    void				ReplaceButton(int i_idToReplace, PVZ2UIButton *i_button, Delegate0 i_onPressed);
    void                SetButtonCallback(PVZ2UIButton *i_button, OnPressedCallback&& i_onPressed);
    
    bool				HasButton(int i_buttonID);
    PVZ2UIButton*       GetButton(int i_buttonID);
    
	void				AddCancelButton();
	void				ClearButtons();
	virtual void		LayoutElements();

    void				SetImage(Sexy::Image* i_image, Sexy::Point position);
    void 				SetImageColor(Sexy::Color color);
    void                SetImageScale(float scale);
    
    void 				Hide(uint i_elementFlagsToHide);

	virtual void		ButtonPress(int theId);
	virtual void 		ButtonDepress(int i_theId);
    void SetUpdateCallBack(Delegate0 update);
protected:
    virtual Sexy::Rect  GetButtonRegion();
    
private:
    PVZ2UIButton*       BuildButton(DialogButtonType buttonType, const SexyString& i_label);
    
    void 				drawShadedBox(Sexy::Graphics* i_g, Sexy::Rect extents);
    void 				drawHeader(Graphics* i_g);
	void 				drawFooter(Graphics* i_g);
    virtual void 		drawImage(Graphics* i_g);

	PVZ2UIButton* 		addButton(int i_buttonID, const SexyString& i_label, DialogButtonType buttonType = BUTTON_TYPE_GENERIC_PRIMARY);
	
	bool				m_layoutDirty;
	
    Widget_ButtonList*  m_buttonList;
	Sexy::Widget*		m_contentsWidget;
	SexyString			m_headerLabel;
	SexyString			m_footerLabel;
	float				m_footerHeight;
    float               m_headerHeight;
	int					m_nextFreeButtonId;
    uint				m_elementFlagsToHide;
    
    int					m_buttonHeight;
    bool				m_hasFooterSeparator;
    bool				m_hasBackgroundDarken;
    //zhaobk added, set background darken alpha
    float               m_backgroundAlphaPercent;
    Sexy::Rect			m_footerSeparatorRect;
    Sexy::Rect			m_footerRect;
    Sexy::Rect			m_labelRect;
    int                 m_footerBottomPadding;
    bool        		m_hasImage;
    Image*      		m_image;
    Sexy::Point 		m_imagePosition;
    Sexy::Color 		m_imageColor;
    float               m_imageScale;
    DrawStringJustification m_footerAlign;
    bool				m_hasCancelButton;
    Delegate0 m_update;    
    bool				m_bAlways;
protected:
    // Positions of elements for other things to base off of
    float				m_buttonStartY;
    Sexy::Color			m_headerFontColor;
    Sexy::Color			m_footerFontColor;
};

class PVZ2UIImageWidget : public Sexy::Widget
{
public:
	PVZ2UIImageWidget();
	virtual ~PVZ2UIImageWidget();
	
	virtual void Draw(Sexy::Graphics* i_g);
	
	void SetImage(Sexy::Image* i_image);
	void SetImageAndResize(Sexy::Image* i_image);
	void SetStretch(bool i_stretch);
	
private:
	Sexy::Image* m_image;
	bool m_stretch;
};

class PVZ2UIStrechAndCenterImage : public Sexy::Widget
{
public:
	PVZ2UIStrechAndCenterImage();
	virtual ~PVZ2UIStrechAndCenterImage();
	
	virtual void Draw(Sexy::Graphics* i_g);
	
	void SetImage(Sexy::ImagePtr i_image);
	
private:
	Sexy::ImagePtr m_image;
};

class PVZ2UIImageCard : public Sexy::Widget
{
public:
    PVZ2UIImageCard();
    virtual ~PVZ2UIImageCard();
    
    void SetDesc(SexyString i_desc);
    void SetImage(Sexy::Image* i_img, Sexy::Image* i_imgBg);
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void DrawAll(ModalFlags* i_Flags, Graphics* i_g);
    
private:
    Image* m_imgBg;
    Image* m_imgBanner;
    
    SexyString  m_strDesc;
    Sexy::Rect        m_rectDesc;
    
    Sexy::Rect        m_rectBanner;
    Sexy::Rect        m_rectBg;
};

class PVZ2WaitingDialog :public PVZ2UIDialog
{
public:
	PVZ2WaitingDialog(const SexyString& i_headLabel, int i_waitingSec);
    
	virtual ~PVZ2WaitingDialog();

	virtual void Update();

	void	SetError();
    void    SetShowWaiting(bool iShowWaiting);
    
    void    SetCloseCallBack(Delegate0 onClose);

private:
	void	OnClose();

private:
	int		mWaitingSec;
	time_t	mWaitingBeginTime;
	bool	mWaitingStop;
    bool    mShowWaiting;
    
    Delegate0   m_onClose;
};

class PVZ2NewTutorialDialog : public PVZ2UIDialog
{
public:
    PVZ2NewTutorialDialog(const std::string& i_effectAnimName, const std::string& i_animToPlay);
    virtual ~PVZ2NewTutorialDialog();
    
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void Update();
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
private:
    class Effect_PopAnim* m_popAnim;

};

#endif
