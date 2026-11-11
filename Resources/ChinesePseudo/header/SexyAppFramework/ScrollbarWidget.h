// ScrollbarWidget.h: interface for the ScrollbarWidget class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __SCROLLBARWIDGET_H__
#define __SCROLLBARWIDGET_H__

#include "Widget.h"
#include "ButtonListener.h"

namespace Sexy 
{

class ScrollListener;
class ScrollbuttonWidget;

class ScrollbarWidget : public Widget, public ButtonListener 
{
public:

enum 
{
	UPDATE_MODE_IDLE		=0,
	UPDATE_MODE_PGUP,
	UPDATE_MODE_PGDN
};

enum
{
	COLOR_BAR,				// Color of scrollbar background
	COLOR_BAR_PAGING,		// Color of scrollbar background during PgUp and PgDn
	COLOR_THUMB,			// Surface color of thumb
	COLOR_DARK_OUTLINE,		// Color of shadow around outer edge of thumb
	COLOR_MEDIUM_OUTLINE,	// Dark raised edge color of thumb
	COLOR_LIGHT_OUTLINE,	// Light raised edge color of thumb
	NUM_COLORS
};

public:

	ScrollbuttonWidget		*mUpButton;
	ScrollbuttonWidget		*mDownButton;

	bool					mInvisIfNoScroll;			

public:

	int						mId;

	double					mValue;
	double					mMaxValue;
	double					mPageSize;
	bool					mHorizontal;
	int						mButtonLength;		// If != 0, value overrides default size of scroll buttons along the bar axis. Default value is equal to thickness of bar.

	bool					mPressedOnThumb;
	int						mMouseDownThumbPos;
	int						mMouseDownX;
	int						mMouseDownY;

	int						mUpdateMode;
	int						mUpdateAcc;
	int						mButtonAcc;
	int						mLastMouseX;
	int						mLastMouseY;
	ScrollListener*			mScrollListener;

	Image					*mThumbImage;		// Custom image for thumb
	Image					*mBarImage;			// Custom scrollbar image
	Image					*mPagingImage;		// Used in place of mBarImage when the scrollbar itself is clicked

public:
	ScrollbarWidget(int theId, ScrollListener *theScrollListener);
	virtual ~ScrollbarWidget();

	virtual void			SetInvisIfNoScroll(bool invisIfNoScroll);
	virtual void			SetMaxValue(double theNewMaxValue);
	virtual void			SetPageSize(double theNewPageSize);
	virtual void			SetValue(double theNewValue);
	virtual void			SetHorizontal(bool isHorizontal);

							// button, down, disabled: Image strips containing either:
							// A. 2 buttons consisting of up/down or left/right
							// B. 4 buttons consisting of up/down/left/right
							// Be sure to define "cols" attribute in resource XML
	virtual void			SetButtonImages(Image *button, Image *down, Image *disabled = 0);
	virtual void			SetThumbImage(Image *img);
							// theBarImage: The image for the scrollbar itself, drawn to size by DrawImageBox()
							// thePagingImage: The image for the scrollbar when it is clicked
	virtual void			SetBarImages(Image *theBarImage, Image *thePagingImage = 0);

	virtual void			SetButtonColors(int theColors[][3], int theNumColors);
	virtual void			SetButtonColors(int theColors[][4], int theNumColors);
	virtual void			SetButtonColor(int theIdx, const Color& theColor);

	virtual void			ResizeScrollbar(int theX, int theY, int theWidth, int theHeight);			
	virtual bool			AtBottom();
	virtual void			GoToBottom();
	virtual void			DrawThumb(Graphics *g, int theX, int theY, int theWidth, int theHeight);
	virtual void			DrawThumb(Graphics *g, Rect theRect);
	virtual int				GetTrackSize();
	virtual int				GetThumbSize();
	virtual int				GetThumbPosition();
	virtual void			Draw(Graphics *g);
	virtual void			ClampValue();
	virtual void			SetThumbPosition(int thePosition);
	virtual void			ButtonPress(int theId);
	virtual void			ButtonDepress(int theId);
	virtual void			ButtonDownTick(int theId);
	virtual void			Update();
	virtual int				ThumbCompare(int x, int y);
	virtual void			MouseDown(int x, int y, int theClickCount) { Widget::MouseDown(x, y, theClickCount); }
	virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseUp(int x, int y) { Widget::MouseUp(x, y); }
	virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount);
	virtual void			MouseDrag(int x, int y);

	virtual void			RemoveAllWidgets(bool doDelete /* = false */, bool recursive /* = false */);
};

}

#endif // __SCROLLBARWIDGET_H__
