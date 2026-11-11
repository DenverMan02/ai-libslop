#ifndef __BUTTONWIDGET_H__
#define __BUTTONWIDGET_H__

#include "Widget.h"

namespace Sexy
{

class Image;
class ButtonListener;

class ButtonWidget : public Widget
{
	RT_CLASS_DEFINE(ButtonWidget, Widget, RtClass);
public:
	enum ButtonJustification {
		BUTTON_LABEL_LEFT	= -1,
		BUTTON_LABEL_CENTER,
		BUTTON_LABEL_RIGHT
	};
	enum
	{
		COLOR_LABEL,
		COLOR_LABEL_HILITE,
		COLOR_DARK_OUTLINE,
		COLOR_LIGHT_OUTLINE,
		COLOR_MEDIUM_OUTLINE,
		COLOR_BKG,
		NUM_COLORS
	};

	int						mId;	
	SexyString				mLabel;
	int						mLabelJustify;
	Image*					mButtonImage;
	Image*					mIconImage;
	Image*					mOverImage;
	Image*					mDownImage;	
	Image*					mDisabledImage;
	Rect					mNormalRect;
	Rect					mOverRect;
	Rect					mDownRect;
	Rect					mDisabledRect;

#ifdef WIDGETS_USE_PRIMETEXT
    PrimeTypeface*          mPrimeFont;
#endif
	Font*					mFont;

	bool					mInverted;
	bool					mBtnNoDraw;
	bool					mFrameNoDraw;
	ButtonListener*			mButtonListener;

	//index of the gamepad to last pressed the button
	int						mLastPressedBy;

	double					mOverAlpha;
	double					mOverAlphaSpeed;
	double					mOverAlphaFadeInSpeed;

	int						mLabelOffsetX,mLabelOffsetY;

	virtual bool		    HaveButtonImage(Image *theImage, const Rect &theRect);
	virtual void			DrawButtonImage(Graphics *g, Image *theImage, const Rect &theRect, int x, int y);
	

public:
	ButtonWidget();
	ButtonWidget(int theId, ButtonListener* theButtonListener);
	virtual ~ButtonWidget();
	
#ifdef WIDGETS_USE_PRIMETEXT
    virtual void            SetFont(PrimeTypeface* theFont);
#endif
	virtual void			SetFont(Font* theFont);
	virtual bool			IsButtonDown();
	virtual void			Draw(Graphics* g);
	virtual void			SetDisabled(bool isDisabled);
	virtual void			MouseEnter();
	virtual void			MouseLeave();
	virtual void			MouseMove(int theX, int theY);
	virtual void			MouseDown(int theX, int theY, int theClickCount) { Widget::MouseDown(theX, theY, theClickCount); }
	virtual void			MouseDown(int theX, int theY, int theBtnNum, int theClickCount);
	virtual void			MouseUp(int theX, int theY) { Widget::MouseUp(theX, theY); }
	virtual void			MouseUp(int theX, int theY, int theClickCount) { Widget::MouseUp(theX, theY, theClickCount); }
	virtual void			MouseUp(int theX, int theY, int theBtnNum, int theClickCount);
	virtual void			Update();

	//Sub-classes can override this to get an event of when the button is pressed.
	virtual void			OnPressed();
    
protected:
    void                    DrawIcon(Graphics* g, Color& color, int imageX, int imageY, int textX, int textY);
    void                    EnsureFonts();

};

}

#endif //__BUTTONWIDGET_H__