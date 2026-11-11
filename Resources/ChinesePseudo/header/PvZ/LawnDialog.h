#ifndef __LAWNDIALOG_H__
#define __LAWNDIALOG_H__

#include "SexyAppFramework/CheckboxListener.h"
#include "SexyAppFramework/Dialog.h"

#include "PVZTypes.h"
#include "RtDelegate.h"
#include "PopAnimRig.h"

class LawnApp;
class LawnDialog;
class StretchableNewLawnButton;

typedef Delegate0 ButtonPressDelegate;

class LawnDialog : public Sexy::Dialog
{
public:
	// TODO -- Oh my god!! A pvztime_t conversion we missed!
	int m_buttonDelay;
	bool m_drawStandardBack;
	StretchableNewLawnButton* m_lawnYesButton;
	StretchableNewLawnButton* m_lawnNoButton;
	bool m_tallBottom;
	bool m_verticalCenterText;



	int GetLeft();
	int GetWidth();
	int GetTop();

public:
	LawnDialog(int i_id, bool isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode);
	virtual ~LawnDialog();
	virtual void SetButtonDelay(int i_delay);
	virtual void Update();
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void CheckboxChecked(int i_id, bool cheked);		
	virtual void KeyDown(KeyCode i_key);
	virtual void AddedToManager(WidgetManager* i_widgetManager);
	virtual void RemovedFromManager(WidgetManager* i_widgetManager);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void Draw(Graphics* g);
	void CalcSize(int i_extraX, int i_extraY, bool i_padDialogWidth = true);
    
    //PVZ2_CHINESE_BEGIN
    void CalcSizeWithFont(int i_extraX, int i_extraY, bool i_padDialogWidth = true);
#ifdef WIDGETS_USE_PRIMETEXT
    void CalcSizeWithPrimeFont(int i_extraX, int i_extraY, bool i_padDialogWidth = true);
#endif
    //PVZ2_CHINESE_END

    void SetButtonImage(ImagePtr i_image, int i_buttonMode, const SexyString& i_dialogFooter);
    
	virtual void OrderInManagerChanged();

    /*
#ifdef WIDGETS_USE_PRIMETEXT
    virtual void			WriteCenteredLine(Graphics* g, PrimeTypeface* font, Color color, int anOffset, const SexyString& theLine);
	virtual void			WriteCenteredLine(Graphics* g, PrimeTypeface* font, int anOffset, const SexyString& theLine, Color theColor1, Color theColor2, const Point& theShadowOffset = Point(1,2));
	virtual int				WriteString(Graphics* g, PrimeTypeface* font, Color color, const SexyString& theString, int theX, int theY, int theWidth = -1, int theJustification = -1, bool drawString = true, int theOffset = 0, int theLength = -1);
	virtual int				WriteWordWrapped(Graphics* g, PrimeTypeface* font, Color color, const Rect& theRect, const SexyString& theLine, int theLineSpacing, int theJustification);
	virtual int             GetWordWrappedHeight(Graphics* g, PrimeTypeface* font, int theWidth, const SexyString& theLine, int aLineSpacing);
#else
    virtual Rect			WriteCenteredLine(Graphics* g, int offset, const SexyString& i_line);
	virtual Rect			WriteCenteredLine(Graphics* g, int offset, const SexyString& i_line, Color i_color1, Color i_color2, const Point& i_shadowOffset = Point(1,2));
	virtual int				WriteString(Graphics* g, const SexyString& i_string, int i_x, int i_y, int i_width = -1, int i_justification = -1, bool drawString = true, int i_offset = 0, int i_length = -1);
	virtual int				WriteWordWrapped(Graphics* g, const Rect& i_rect, const SexyString& i_line, int i_lineSpacing, int i_justification);
	virtual int				GetWordWrappedHeight(Graphics* g, int i_width, const SexyString& i_line, int lineSpacing);
#endif
    */
	
	inline void				SetOnYesButtonPressed(ButtonPressDelegate i_onYesButtonPressed);
	inline void				SetOnNoButtonPressed(ButtonPressDelegate i_onNoButtonPressed);
	
	void				SetPlant(const PlantTypePtr i_plantType);
	
	void				SetPopAnim(class PopAnim* i_pam, const std::string& i_animName);
	void				SetStaticImage(ImagePtr i_img);

private:

	ButtonPressDelegate		m_onYesButtonPressed;
	ButtonPressDelegate		m_onNoButtonPressed;
    

    PopAnimRig*		m_popAnimRig;
    PlantTypePtr    m_plantType;
	
	ImagePtr		m_staticImage;
};

inline void LawnDialog::SetOnYesButtonPressed(ButtonPressDelegate i_onYesButtonPressed)
{
	m_onYesButtonPressed = i_onYesButtonPressed;
}

inline void LawnDialog::SetOnNoButtonPressed(ButtonPressDelegate i_onNoButtonPressed)
{
	m_onNoButtonPressed = i_onNoButtonPressed;
}

#endif //__LAWNDIALOG_H__
