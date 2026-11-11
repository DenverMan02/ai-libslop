#ifndef __WIDGETMANAGER_H__
#define __WIDGETMANAGER_H__

#include "Common.h"
#include "KeyCodes.h"
#include "UiEnums.h"
#include "WidgetContainer.h"
#include "IGamepadDriver.h"

namespace Sexy
{

class Widget;
class Image;
class MemoryImage;
class SexyAppBase;
class Graphics;
	struct Touch;

	
typedef std::list<Widget*> WidgetList;

enum
{
	WIDGETFLAGS_UPDATE			= 1,
	WIDGETFLAGS_MARK_DIRTY		= 2,
	WIDGETFLAGS_DRAW			= 4,
	WIDGETFLAGS_CLIP			= 8,	
	WIDGETFLAGS_ALLOW_MOUSE		= 16,
	WIDGETFLAGS_ALLOW_FOCUS		= 32,	
};

class PreModalInfo
{
public:
	Widget*					mBaseModalWidget;
	Widget*					mPrevBaseModalWidget;
	Widget*					mPrevFocusWidget;
	FlagsMod				mPrevBelowModalFlagsMod;
};

typedef std::list<PreModalInfo> PreModalInfoList;

typedef std::vector<std::pair<Widget*, int> > DeferredOverlayVector;

class WidgetManager : public WidgetContainer
{
public:	
	Widget*					mDefaultTab;
	
	Graphics*				mCurG;
	SexyAppBase*			mApp;
	MemoryImage*			mImage;	
	MemoryImage*			mTransientImage;
	bool					mLastHadTransients;	
	Widget*					mPopupCommandWidget;	
	DeferredOverlayVector	mDeferredOverlayWidgets;
	int						mMinDeferredOverlayPriority;
	
	bool					mHasFocus;
	Widget*					mFocusWidget;
	Widget*					mLastDownWidget;
	Widget*					mOverWidget;
	Widget*					mBaseModalWidget;
	Widget*					mGamepadSelectionWidget;
	FlagsMod				mLostFocusFlagsMod;
	FlagsMod				mBelowModalFlagsMod;
	FlagsMod				mDefaultBelowModalFlagsMod;
	PreModalInfoList		mPreModalInfoList;
	Rect					mMouseDestRect;
	Rect					mMouseSourceRect;
	bool					mMouseIn;
	int						mLastMouseX;
	int						mLastMouseY;
	int						mDownButtons;
	int						mActualDownButtons;
	int						mLastInputUpdateCnt;
	
	bool					mKeyDown[0xFF];
	int						mLastDownButtonId;	

	// $ (mf) Fixing issue with TouchEnd losing the widget focus with more than one touch
	int						mTouches;
	
	int						mWidgetFlags;
	int						GetWidgetFlags();

protected:
	void					MouseEnter(Widget* theWidget);
	void					MouseLeave(Widget* theWidget);

protected:
	void					SetBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod);

public:
	WidgetManager(SexyAppBase* theApplet);
	virtual ~WidgetManager();
	
	void					FreeResources();		
	void					AddBaseModal(Widget* theWidget, const FlagsMod& theBelowFlagsMod);
	void					AddBaseModal(Widget* theWidget);
	void					RemoveBaseModal(Widget* theWidget);
	void					Resize(const Rect& theMouseDestRect, const Rect& theMouseSourceRect);
	void					DisableWidget(Widget* theWidget);	
	Widget*					GetAnyWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY);
	Widget*					GetWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY);
	void					SetFocus(Widget* aWidget);
	void					GotFocus();	
	void					LostFocus();	
	void					InitModalFlags(ModalFlags* theModalFlags);
	void					DrawWidgetsTo(Graphics* g);
	void					DoMouseUps(Widget* theWidget, ulong theDownCode);	
	void					DoMouseUps();
	void					DeferOverlay(Widget* theWidget, int thePriority);
	void					FlushDeferredOverlayWidgets(int theMaxPriority);
	
	bool					DrawScreen();
	bool					UpdateFrame();				
	bool					UpdateFrameF(float theFrac);
	void					SetPopupCommandWidget(Widget* theList);
	void					RemovePopupCommandWidget();	
	void					MousePosition(int x, int y);	
	void					RehupMouse();
	void					RemapMouse(int& theX, int& theY);
	bool					MouseUp(int x, int y, int theClickCount);
	bool					MouseDown(int x, int y, int theClickCount);
	bool					MouseMove(int x, int y);
	bool					MouseDrag(int x, int y);
	bool					MouseExit(int x, int y);
	void					MouseWheel(int theDelta);
	bool					KeyChar(SexyChar theChar);
	bool					KeyDown(KeyCode key);
	bool					KeyUp(KeyCode key);
	
	//JVW - removing this. Who uses it? 
	//bool					KeyMessageRaw(void* hwnd, unsigned int message, unsigned __int64 wparam, __int64 lparam);

	bool					IsLeftButtonDown();
	bool					IsMiddleButtonDown();
	bool					IsRightButtonDown();
	
    void					TouchBegan( const Sexy::Touch& touch );
    void					TouchMoved( const Sexy::Touch& touch );
    void					TouchEnded( const Sexy::Touch& touch );
	void					TouchesCanceled();
	
	void 					OnGestureLongPress(Sexy::Point i_startingLocation);
	void 					OnGestureFlick(Sexy::GestureFlickDirection i_direction, Sexy::Point i_startingLocation);
	void					OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta);

};

}

#endif // __WIDGETMANAGER_H__
