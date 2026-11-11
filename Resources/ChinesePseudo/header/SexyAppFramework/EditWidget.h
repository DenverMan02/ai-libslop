#ifndef __EDITWIDGET_H__
#define __EDITWIDGET_H__

#include "Widget.h"
#include "IMEDispatcher.h"
namespace Sexy
{
    
enum EditWidgetType
{
    EWT_Default,
    EWT_PhoneNum,
    EWT_Email,
};

class Font;
class EditListener;

class EditWidget : public Widget,public IMEDelegate
{
public:
	enum
	{
		COLOR_BKG,
		COLOR_OUTLINE,
		COLOR_TEXT,
		COLOR_HILITE,
		COLOR_HILITE_TEXT,
		NUM_COLORS
	};

	int						mId;
	SexyString				mString;
	SexyString				mPasswordDisplayString;
	int						mClipInset;
	int						mTextInset;
	int						mCursorOffset;
	int						mHiliteWidthAdd;

//PVZ2_CHINESE_BEGIN
#ifdef WIDGETS_USE_PRIMETEXT
    PrimeTypeface*          mPrimeFont;
#endif
//PVZ2_CHINESE_END
	Font*					mFont;

    
	struct WidthCheck
	{
//PVZ2_CHINESE_BEGIN
#ifdef WIDGETS_USE_PRIMETEXT
        PrimeTypeface*          mPrimeFont;
#endif
        Font*					mFont;
//PVZ2_CHINESE_END

		int mWidth;
	};
	typedef std::list<WidthCheck> WidthCheckList;
	WidthCheckList				mWidthCheckList;
	
	EditListener*			mEditListener;		
	bool					mShowingCursor;
	bool					mDrawSelOverride; // set this to true to draw selected text even when not in focus
	bool					mHadDoubleClick;	// Used to fix a bug with double clicking to hilite a word after the widget manager started calling mouse drag before mouse down/up events
	int						mCursorPos;
	int						mHilitePos;
	int						mBlinkAcc;
	int						mBlinkDelay;
	int						mLeftPos;		
	int						mMaxChars;
	int						mMaxPixels;
	SexyChar				mPasswordChar;
	
	SexyString				mUndoString;
	int						mUndoCursor;
	int						mUndoHilitePos;
	int						mLastModifyIdx;

	bool					mClearStringOnFocus;
	bool					mIsEditWidgetActive;
	SexyString				mClearStringUndo;


    virtual std::string getText() override
    {
        return Sexy::SexyStringToUTF8String(mString);
    }
    virtual void setText(const std::string& text) override
    {
        SetText(Sexy::UTF8StringToSexyString(text));
    }
    
    EditWidgetType          m_editType = EWT_Default;
    void                    ShowKeyboard();
    void                    HideKeyboard();

protected:
	virtual void			ProcessKey(KeyCode theKey, SexyChar theChar);
	SexyString&			GetDisplayString();
	virtual void			HiliteWord();
	void					UpdateCaretPos();

public:
    //PVZ2_CHINESE_BEGIN
#ifdef WIDGETS_USE_PRIMETEXT
	virtual void			SetFont(PrimeTypeface* theFont, PrimeTypeface* theWidthCheckFont = NULL);
	void					AddWidthCheckFont(PrimeTypeface *theFont, int theMaxPixels = -1); // defaults to mMaxPixels
#endif
	virtual void			SetFont(Font* theFont, Font* theWidthCheckFont = NULL);
	void					AddWidthCheckFont(Font *theFont, int theMaxPixels = -1); // defaults to mMaxPixels
    //PVZ2_CHINESE_END
    
	virtual void			SetText(const SexyString& theText, bool leftPosToZero = true);
	virtual bool			IsPartOfWord(SexyChar theChar);
	virtual int				GetCharAt(int x, int y);

    virtual void			Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void			Draw(Graphics* g) override; // Already translated;
    //PVZ2_CHINESE_BEGIN
    virtual void            DrawWithFont(Graphics* g);
#ifdef WIDGETS_USE_PRIMETEXT
    virtual void            DrawWithPrimeFont(Graphics* g);
#endif
    //PVZ2_CHINESE_END
    
    virtual void			Update() override;
    virtual void			MarkDirty() override;
    
    virtual bool			WantsFocus() override;
    virtual void			GotFocus() override;
    virtual void			LostFocus() override;
    virtual void			FocusCursor(bool bigJump);

//PVZ2_CHINESE_START
	void					AttachIME();
	void					DetachIME();
//PVZ2_CHINESE_END
    void					SetEditWidgetActive();
    
    virtual void			KeyDown(KeyCode theKey) override;
    virtual void			KeyChar(SexyChar theChar) override;
    
    void                    TouchBegan( const Sexy::Touch& i_touch ) override; //PVZ2_CHINESE
    
    virtual void			MouseDown(int x, int y, int theClickCount) override { Widget::MouseDown(x, y, theClickCount); }
    virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount) override;
    virtual void			MouseUp(int x, int y) override { Widget::MouseUp(x, y); }
    virtual void			MouseUp(int x, int y, int theClickCount) override { Widget::MouseUp(x, y, theClickCount); }
    virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount) override;
    virtual void			MouseDrag(int x, int y) override;
    virtual void			MouseEnter() override;
    virtual void			MouseLeave() override;
	void					ClearWidthCheckFonts();
	void					EnforceMaxPixels();

public:
	EditWidget(int theId, EditListener* theEditListener);
	virtual ~EditWidget();
};

}

#endif //__EDITWIDGET_H__