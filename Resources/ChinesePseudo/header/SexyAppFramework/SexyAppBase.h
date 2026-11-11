#ifndef __SEXYAPPBASE_H__
#define __SEXYAPPBASE_H__

#include "Common.h"
#include "Rect.h"
#include "Color.h"
#include "ButtonListener.h"
#include "DialogListener.h"
#include "Buffer.h"
#include "CritSect.h"
#include "SharedImage.h"
#include "Ratio.h"
#include "SharedRenderTarget.h"
#include "PopLoc.h"
#include "SexyThread.h"
#include "Flags.h"
#include "RtObject.h"
#include "UiEnums.h"
#include "IInteractiveAudioDriver.h"

#if SEXY_IS_WWISE_ENABLED
#include "InteractiveSoundTypes.h"
#endif

#if SEXY_IS_CAMERA_ENABLED
#include "ICameraDriver.h"
#endif


namespace ImageLib
{
	class Image;
};

#ifdef SUPPORT_REFLECTION
namespace Reflection
{
	class CRefSymbolDb;
}
#endif

namespace Sexy
{

class WidgetManager;
class Image;
class ImageFont;
class PrimeFont;
class PIEffect;
class PopAnim;
class DeviceImage;
class Widget;
class WidgetContainer;

#if SEXY_IS_WWISE_ENABLED
class InteractiveSoundManager;
#else
class SoundManager;
#endif

class MusicInterface;
class MemoryImage;
class HTTPTransfer;
class Dialog;
class SoundResource;
class SoundInstance;
class RtSerialBuffer;
class AppControls;
class AppDiagnostics;

class ICfgCompiler;

class IAppDriver; 
#if SEXY_IS_WWISE_ENABLED
class IInteractiveAudioDriver;
#else
class IAudioDriver;
#endif
class IGraphicsDriver;
class IFileDriver;
class ResourceManager;
class ResStreamsManager;
class IResStreamsDriver;
class IProfileDriver;
class ISaveGameDriver;
class IHttpDriver;
class ILeaderboardDriver;
class IAchievementDriver;
class IDiagDriver;
	
#if SEXY_IS_CAMERA_ENABLED
class ICameraDriver;
#endif
class IAntiHackDriver; //PVZ2_CHINESE

#if SEXY_IS_LIVELINK_ENABLED
class ILiveLinkSocketDriver;
#endif // SEXY_IS_LIVELINK_ENABLED

class ProfileManager;
class LeaderboardManager;

class WidgetSafeDeleteInfo
{
public:
	int						mUpdateAppDepth;
	Widget*					mWidget;
};

	typedef std::list<WidgetSafeDeleteInfo> WidgetSafeDeleteList;
	typedef std::set<MemoryImage*> MemoryImageSet;
	typedef std::set<ImageFont*> ImageFontSet;
	typedef std::set<PrimeFont*> PrimeFontSet;
	typedef std::set<PIEffect*> PIEffectSet;
	typedef std::set<PopAnim*> PopAnimSet;
	typedef std::map<int, Dialog*> DialogMap;
	typedef std::list<Dialog*> DialogList;
	
#ifdef HOST_WINDOWS
	//JVW - MOVE to windows driver
	typedef std::list<MSG> WindowsMessageList;
	typedef std::map<HANDLE, int> HandleToIntMap;

#endif
	typedef std::vector<std::string> StringVector;
	//typedef std::basic_string<TCHAR> tstring; // string of TCHARs

	typedef std::map<std::string, SexyString> StringSexyStringMap;
	typedef std::map<std::string, std::string> StringStringMap;
	typedef std::map<std::string, std::wstring> StringWStringMap;
	typedef std::map<std::string, bool> StringBoolMap;
	typedef std::map<std::string, int> StringIntMap;
	typedef std::map<std::string, double> StringDoubleMap;
	typedef std::map<std::string, StringVector> StringStringVectorMap;

enum
{
	CURSOR_POINTER,
	CURSOR_HAND,
	CURSOR_DRAGGING,
	CURSOR_TEXT,
	CURSOR_CIRCLE_SLASH,
	CURSOR_SIZEALL,
	CURSOR_SIZENESW,
	CURSOR_SIZENS,
	CURSOR_SIZENWSE,
	CURSOR_SIZEWE,	
	CURSOR_WAIT,
	CURSOR_NONE,
	CURSOR_CUSTOM,
	NUM_CURSORS
};

enum
{
	DEMO_MOUSE_POSITION,	
	DEMO_ACTIVATE_APP,
	DEMO_SIZE,
	DEMO_KEY_DOWN,
	DEMO_KEY_UP,
	DEMO_KEY_CHAR,
	DEMO_CLOSE,
	DEMO_MOUSE_ENTER,
	DEMO_MOUSE_EXIT,
	DEMO_LOADING_COMPLETE,
	DEMO_REGISTRY_GETSUBKEYS,
	DEMO_REGISTRY_READ,
	DEMO_REGISTRY_WRITE,
	DEMO_REGISTRY_ERASE,	
	DEMO_FILE_EXISTS,
	DEMO_FILE_READ,
	DEMO_FILE_WRITE,
	DEMO_HTTP_RESULT,
	DEMO_SYNC,
	DEMO_ASSERT_STRING_EQUAL,
	DEMO_ASSERT_INT_EQUAL,
	DEMO_MOUSE_WHEEL,
	DEMO_HANDLE_COMPLETE,
	DEMO_VIDEO_DATA,
	DEMO_IDLE = 31
};

enum {
	FPS_ShowFPS,
	FPS_ShowFPSWithHistory,
	FPS_ShowCoords,
	Num_FPS_Types
};

	enum
	{
		UPDATESTATE_MESSAGES,
		UPDATESTATE_PROCESS_1,
		UPDATESTATE_PROCESS_2,
		UPDATESTATE_PROCESS_DONE
	};
	
	
	//UI_ORIENTATION is mainly used for iPhone/iPad/Android for now.
	//surely there will be more platforms that use it soon.
	// IMPORTANT! If you change the values here, then you much change the mirror constants
	//  in AndroidGameApp.java for Android
	typedef
	enum
	{
		UI_ORIENTATION_UNKNOWN,
			
		UI_ORIENTATION_PORTRAIT,
		UI_ORIENTATION_PORTRAIT_UPSIDE_DOWN,
		UI_ORIENTATION_LANDSCAPE_RIGHT,
		UI_ORIENTATION_LANDSCAPE_LEFT,
		
		UI_ORIENTATION_FACE_UP,
		UI_ORIENTATION_FACE_DOWN,
	}
	UI_ORIENTATION;
	
	
    typedef enum
    {
        RUT_MODVALS = 0,
        RUT_RSB = 1,
        RUT_LOOSE_FILES = 2,
    }
    ResourceUpdateType;
	
//touches may go somewhere else eventually
	typedef enum _TouchPhase
	{
		TOUCH_BEGAN,
		TOUCH_MOVED,
		TOUCH_STATIONARY,
		TOUCH_ENDED,
		TOUCH_CANCELED,
	} TouchPhase;
	
	typedef size_t TouchID;
	const TouchID InvalidTouchID = 0;
	struct Touch
	{
		TouchID ident;
		// This really shouldn't be a void*. It encourages writing non portable code.
		void* event;
		Sexy::Point location;
		Sexy::Point previousLocation;
		int tapCount;
		double timestamp;
		TouchPhase phase;

		bool operator == (const Touch& other) const
		{
			return other.ident == ident;
		}
	};
	
	typedef std::vector<Touch> TouchList;
		
	enum MessageBoxFlags
	{
		MSGBOX_OK =                             0x0000,
		MSGBOX_OKCANCEL =                       0x0001,
		MSGBOX_ABORTRETRYIGNORE =               0x0002,
		MSGBOX_YESNOCANCEL =                    0x0003,
		MSGBOX_YESNO =                          0x0004,
		MSGBOX_RETRYCANCEL =                    0x0005,
		MSGBOX_CANCELTRYCONTINUE =              0x0006,
        //Non-standard (ios)
        MSGBOX_ABORTRETRYIGNOREIGNOREALL =      0x0007,
		//icons
		MSGBOX_ICONERROR =                      0x0010,
		MSGBOX_ICONQUESTION =                   0x0020,
		MSGBOX_ICONWARNING =                    0x0030,
		MSGBOX_ICONINFORMATION =                0x0040,
	};
	
	enum MessageBoxResults
	{
		MSGBOX_RESULT_OK =			0001,
		MSGBOX_RESULT_CANCEL =		0002,
		MSGBOX_RESULT_ABORT =		0003,
		MSGBOX_RESULT_RETRY =		0004,
		MSGBOX_RESULT_IGNORE =		0005,
		MSGBOX_RESULT_YES =			0006,
		MSGBOX_RESULT_NO =			0007,
		MSGBOX_RESULT_TRYAGAIN =	0010,
		MSGBOX_RESULT_CONTINUE =	0011,
        MSGBOX_RESULT_IGNOREALL =	0012,
	};
		


extern bool gIs3D;
extern IFileDriver* gFileDriver;

#if SEXY_IS_LIVELINK_ENABLED
extern ILiveLinkSocketDriver* gLiveLinkSocketDriver;
#endif // SEXY_IS_LIVELINK_ENABLED


class SexyAppBase : public ButtonListener, public DialogListener
{
public:
	IAppDriver*				mAppDriver; 
#if SEXY_IS_WWISE_ENABLED
	IInteractiveAudioDriver*	mInteractiveAudioDriver;
#else
	IAudioDriver*			mAudioDriver;
#endif
	IGraphicsDriver*		mGraphicsDriver;
	IFileDriver*			mFileDriver;
	IResStreamsDriver*		mResStreamsDriver;
	IProfileDriver*			mProfileDriver;
	ISaveGameDriver*		mSaveGameDriver;
	IHttpDriver*			mHttpDriver;
	ILeaderboardDriver*		mLeaderboardDriver;
	IAchievementDriver*		mAchievementDriver;
	IDiagDriver*			mDiagDriver;
	
#if SEXY_IS_CAMERA_ENABLED
	ICameraDriver *	mCameraDriver;
#endif

	//PVZ2_CHINESE_START
	IAntiHackDriver*		mAntiHackDriver;
	//PVZ2_CHINESE_END

#if SEXY_IS_LIVELINK_ENABLED
	ILiveLinkSocketDriver*  mLiveLinkSocketDriver;
    AppControls*			mControls;
	AppDiagnostics*			mDiag;
#endif // SEXY_IS_LIVELINK_ENABLED
	
	ulong					mRandSeed;

	std::string				mErrorLog;
		
	std::string				mCompanyName;
	std::string				mFullCompanyName;
	std::string				mProdName;	
	SexyString				mTitle;	
	std::string				mRegKey;
	std::string				mChangeDirTo;
    
    std::string             mResumeCachedFolder;
	
	int						mRelaxUpdateBacklogCount; // app doesn't try to catch up for this many frames
	int						mMaxUpdateBacklog;
	bool					mPauseWhenMoving;
	int						mPreferredX;
	int						mPreferredY;
	int						mPreferredWidth;
	int						mPreferredHeight;
	int						mWidth;
	int						mHeight;
	int						mFullscreenBits;
	double					mMusicVolume;
	double					mSfxVolume;
	double					mDemoMusicVolume;
	double					mDemoSfxVolume;
	bool					mNoSoundNeeded;
	bool					mWantFMod;
	bool					mCmdLineParsed;
	bool					mSkipSignatureChecks;
	bool					mStandardWordWrap;
	bool					mbAllowExtendedChars;

	bool					mOnlyAllowOneCopyToRun;
	uint					mNotifyGameMessage;
	CritSect				mCritSect;	
	CritSect				mGetImageCritSect;
	uchar					mAdd8BitMaxTable[512];
	WidgetManager*			mWidgetManager;
	DialogMap				mDialogMap;
	DialogList				mDialogList;
	uint32					mPrimaryThreadId;
	bool					mSEHOccured;
	bool					mShutdown;
	bool					mExitToTop;
	bool					mIsWindowed;
	bool					mIsPhysWindowed;
	bool					mFullScreenWindow; // uses ChangeDisplaySettings to run fullscreen with mIsWindowed true
	bool					mForceFullscreen;
	bool					mForceWindowed;	
	bool					mInitialized;	
	bool					mProcessInTimer;
	uint32					mTimeLoaded;
	bool					mIsScreenSaver;
	bool					mAllowMonitorPowersave;
	bool					mWantsDialogCompatibility;

	bool					mNoDefer;	
	bool					mFullScreenPageFlip;	
	bool					mTabletPC;
	//DDInterface*			mDDInterface;	
#if !SEXY_IS_WWISE_ENABLED
	MusicInterface*			mMusicInterface;	
#endif
	bool					mReadFromRegistry;
	std::string				mRegisterLink;
	std::string				mProductVersion;	
	Image*					mCursorImages[NUM_CURSORS];
	
	bool					mIsOpeningURL;
	bool					mShutdownOnURLOpen;
	std::string				mOpeningURL;
	uint32					mOpeningURLTime;
	uint32					mLastTimerTime;
	uint32					mLastBigDelayTime;	
	double					mUnmutedMusicVolume;
	double					mUnmutedSfxVolume;	
	int						mMuteCount;
	int						mAutoMuteCount;
	bool					mDemoMute;
	bool					mMuteOnLostFocus;
	MemoryImageSet			mMemoryImageSet;
	CritSect				mImageSetCritSect;
	ImageFontSet			mImageFontSet;
    PrimeFontSet            mPrimeFontSet;
	PIEffectSet				mPIEffectSet;
    
#ifdef PRIME_FOR_BEJBLITZ
    bool					mPrimaryFrame;
#endif
	
//JVW - MOVE to windows driver
	
	//jvw - 
	//a condition is the new x-plat Event system
	//(Condition is the term used in BSD/posix systems)
	Condition				mSharedImageEvent;
#ifdef HOST_WINDOWS
	HANDLE					mMutex;

	WindowsMessageList		mDeferredMessages;
#endif
	
	bool					mCleanupSharedImages;
	
	int						mNonDrawCount;
	float					mFrameTime;
   
	bool					mIsDrawing;
	bool					mLastDrawWasEmpty;
	bool					mHasPendingDraw;
	double					mPendingUpdatesAcc;
	double					mUpdateFTimeAcc;
	uint64					mLastTimeCheck;
	uint64					mLastTime;
	uint64					mLastUserInputTick;

	int						mSleepCount;
	int						mDrawCount;
	int						mUpdateCount;
	int						mUpdateAppState;
	int						mUpdateAppDepth;
	int						mMaxNonDrawCount;
	double					mUpdateMultiplier;		
	bool					mPaused;
	int						mFastForwardToUpdateNum;
	bool					mFastForwardToMarker;
	bool					mFastForwardStep;
	uint64					mLastDrawTick;
	uint64					mNextDrawTick;
	int						mStepMode;  // 0 = off, 1 = step, 2 = waiting for step

	int						mCursorNum;
#if SEXY_IS_WWISE_ENABLED
	InteractiveSoundManager* mInteractiveSoundManager;
#else
	SoundManager*			mSoundManager;
#endif
	
	//JVW -- MOVE to windows driver
#ifdef HOST_WINDOWS
	HCURSOR					mOverrideCursor;
	HCURSOR					mHandCursor;
	HCURSOR					mDraggingCursor;
	
	HWND					mHWnd;
	HWND					mInvisHWnd;

	long					mOldWndProc;

	HandleToIntMap			mHandleToIntMap; // For waiting on handles
	int						mCurHandleNum;

#endif
	
	WidgetSafeDeleteList	mSafeDeleteList;
	bool					mMouseIn;	
	bool					mRunning;
	bool					mActive;
	bool					mMinimized;
	bool					mPhysMinimized;
	bool					mIsDisabled;
	bool					mHasFocus;
	int						mDrawTime;
	ulong					mFPSStartTick;
	int						mFPSFlipCount;
	int						mFPSDirtyCount;
	int						mFPSTime;
	int						mFPSCount;		
	bool					mShowFPS;
	bool					mCalcFPS;
	int						mShowFPSMode;
	double					mVFPSUpdateTimes;
	int						mVFPSUpdateCount;
	double					mVFPSDrawTimes;
	int						mVFPSDrawCount;
	float					mCurVFPS;
	int						mScreenBltTime;
	bool					mAutoStartLoadingThread;
	bool					mLoadingThreadStarted;
	bool					mLoadingThreadCompleted;
	bool					mLoaded;
	bool					mReloadingResources;
	float					mReloadPct;
	std::string				mReloadText;
	std::string				mReloadSubText;
	bool					mYieldMainThread;
	bool					mLoadingFailed;
	bool					mCursorThreadRunning;
	bool					mSysCursor;	
	bool					mCustomCursorsEnabled;
	bool					mCustomCursorDirty;	
	bool					mLastShutdownWasGraceful;
	bool					mIsWideWindow;
	bool					mWriteToSexyCache;
	bool					mSexyCacheBuffers;
	bool					mWriteFontCacheDir;

	int						mNumLoadingThreadTasks;
	int						mCompletedLoadingThreadTasks;

	bool					mDebugKeysEnabled;
	bool					mEnableMaximizeButton;
	bool					mCtrlDown;
	bool					mAltDown;
	bool					mAllowAltEnter;
	
	int						mSyncRefreshRate;
	bool					mVSyncUpdates;
	bool					mNoVSync;
	bool					mVSyncBroken;	
	int						mVSyncBrokenCount;
	uint64					mVSyncBrokenTestStartTick;
	uint64					mVSyncBrokenTestUpdates;
	bool					mWaitForVSync;
	bool					mSoftVSyncWait;
	bool					mAutoEnable3D;
	bool					mTest3D;
	bool					mNoD3D9;
	uint32					mMinVidMemory3D;
	uint32					mRecommendedVidMemory3D;

	bool					mWidescreenAware;
	bool					mWidescreenTranslate;
	Rect					mScreenBounds;
	bool					mEnableWindowAspect;
	Ratio					mWindowAspect;	
	Ratio					mMinAspect;
	Ratio					mMaxAspect;	
	bool					mAllowWindowResize;
	int						mOrigScreenWidth;
	int						mOrigScreenHeight;
	bool					mIsSizeCursor;

	StringWStringMap		mStringProperties;
	StringBoolMap			mBoolProperties;
	StringIntMap			mIntProperties;
	StringDoubleMap			mDoubleProperties;
	StringStringVectorMap	mStringVectorProperties;
	ResourceManager*		mResourceManager;	
	PopLoc					mPopLoc;

	SharedRenderTarget::Pool* mSharedRTPool;

	bool 					mLostFocusOnly;// zhousen : this is for only lost focus, but not switch to background. fix oppo blackscreen

    //Events
    Event2<const char*, const char*>     mCrashEvent;

	enum EShowCompatInfoMode
	{
		SHOWCOMPATINFOMODE_OFF=0,		
		SHOWCOMPATINFOMODE_BOTTOM,
		SHOWCOMPATINFOMODE_TOP,

		SHOWCOMPATINFOMODE_COUNT,
	};
	EShowCompatInfoMode		mShowCompatInfoMode;

	bool					mShowWidgetInspector;
	bool					mWidgetInspectorPickMode;
	bool					mWidgetInspectorLeftAnchor;
	WidgetContainer*		mWidgetInspectorPickWidget;
	WidgetContainer*		mWidgetInspectorCurWidget;
	int						mWidgetInspectorScrollOffset;
	Point					mWidgetInspectorClickPos;

	ResStreamsManager*		mResStreamsManager;
    
	SexyThreadId			mMainThreadId;

#ifdef ZYLOM
	uint					mZylomGameId;
#endif

	ProfileManager*			mProfileManager;
	LeaderboardManager*		mLeaderboardManager;

#ifdef SUPPORT_AUTOREFLECTION
	Reflection::CRefSymbolDb* mRefAutoSymbolDb;
#endif
	
	bool					mAllowSwapScreenImage;

	bool					mbNewSetup;
    bool                    mEnableMapEdit;

	static bool				sAttemptingNonRecommended3D;

	void					ProcessSafeDeleteList();
	virtual void			ReInitImages();
	virtual void			DeleteNativeImageData();	
	virtual void			DeleteExtraImageData();
	virtual void			LoadingThreadCompleted();
	virtual void			UpdateFrames();
	virtual void			UpdateFramesPaused();
    void                    UpdateAudio();
#ifdef PRIME_FOR_PVZ2
    // Moving draw call into App
	virtual void 			DrawScreen();
    // adding UpdateFramesF handler...
    virtual void            UpdateFramesF(float i_dt) {;} // expecting delta time, not faction of a frame... 
#endif // PRIME_FOR_PVZ2
protected:	
	
	
	void					DoExit(int theCode);

public:
	SexyAppBase();
	virtual ~SexyAppBase();

	static void				InitFileDriver();
    
    void                    SetResumeCachedFolder(const std::string& i_folder);

	// Common overrides:
#if !SEXY_IS_WWISE_ENABLED
	virtual MusicInterface*	CreateMusicInterface();
#endif
	virtual void			InitHook();
	virtual void			ShutdownHook();	
	virtual void			PreTerminate();
	virtual void			LoadingThreadProc();
	virtual void			WriteToRegistry();
	virtual void			ReadFromRegistry();
	virtual Dialog*			NewDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);		
	virtual void			PreDisplayHook();
	
	virtual bool			IsUIOrientationAllowed(UI_ORIENTATION theOrientation);
	virtual void			UIOrientationChanged(UI_ORIENTATION theOrientation);
	virtual UI_ORIENTATION  GetUIOrientation();

    std::string             GetDeviceName();
    
	virtual	void			OnFullVersionChange() {};
	
	//This is built for the iPhone, but in theory could be applied 
	// to any of our platforms
	virtual void			LowMemoryWarning();
    virtual void            AppEnteredForeground() {}
    virtual void            AppEnteredBackground() {}
    virtual void			AppBecomingForeground() {}
	
	//many games now do reinit cycles based on a GameApp::mReInit variable.
	//this is difficult to support with  OS's where we don't have control of the runloop,
	//Apps should implement this callback returning true when the app should restart after
	// shutting down
	virtual bool			ShouldReInit() { return false; }

	// LiveLink connection state handler
	virtual void			OnLiveLinkConnected();
	virtual void			OnLiveLinkDisconnected();

	// Public methods
	virtual void			BeginPopup();
	virtual void			EndPopup();
	virtual int				MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MSGBOX_OK);
	virtual int				MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MSGBOX_OK);
	virtual void			Popup(const std::string& theString);
	virtual void			Popup(const std::wstring& theString);
	
	virtual void			SafeDeleteWidget(Widget* theWidget);	

	virtual void			URLOpenFailed(const std::string& theURL);
	virtual void			URLOpenSucceeded(const std::string& theURL);
	virtual bool			OpenURL(const std::string& theURL, bool shutdownOnOpen = false);	
    virtual bool			HandleOpenURLRequest( const std::string& theURL );    
    
	
	

	virtual std::string		GetGameSEHInfo();

	virtual void			Shutdown();	

	virtual void			DoParseCmdLine();
	virtual void			ParseCmdLine(const std::string& theCmdLine);
	virtual void			HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);
	virtual void			HandleGameAlreadyRunning(); 

	virtual void			Start();	
	virtual void			Init();	
	virtual void			PreDDInterfaceInitHook();
	virtual void			PostDDInterfaceInitHook();
	virtual bool			ChangeDirHook(const char *theIntendedPath);
#if !SEXY_IS_WWISE_ENABLED
	virtual void			PlaySample(SoundResource* theSound);
	virtual void			PlaySample(SoundResource* theSound, int thePan);
    virtual SoundInstance*  GetSoundInstance(SoundResource* theSound);
#endif

	virtual double			GetMasterVolume();
	virtual double			GetMusicVolume();
	virtual double			GetSfxVolume();
	virtual bool			IsMuted();

	virtual void			SetMasterVolume(double theVolume);
	virtual void			SetMusicVolume(double theVolume);
	virtual void			SetSfxVolume(double theVolume);	
	virtual void			Mute(bool autoMute = false);
	virtual void			Unmute(bool autoMute = false);
	
#if SEXY_IS_WWISE_ENABLED
	// handlers for when the system drives a mute-message - User-music on iOS devices for example.
	virtual void			MuteMusic() {}
	virtual void			UnmuteMusic() {}
    virtual void            HandleWwiseError() {}
#endif
	
	void					StartLoadingThread();
	virtual double			GetLoadingThreadProgress();	

	void					CopyToClipboard(const std::string& theString);
	std::string				GetClipboard();

	void					SetCursor(int theCursorNum);
	int						GetCursor();
	void					EnableCustomCursors(bool enabled);	
	SharedRenderTarget::Pool* GetSharedRenderTargetPool();
	
	void					CleanSharedImages();
	void					PrecacheAdditive(MemoryImage* theImage);
	void					PrecacheAlpha(MemoryImage* theImage);
	void					PrecacheNative(MemoryImage* theImage);
	void					SetCursorImage(int theCursorNum, Image* theImage);
    
    Sexy::Point				GetNativeScreenSize();
    void					SetNativeScreenSize(int width, int height);

	DeviceImage*			CreateCrossfadeImage(Image* theImage1, const Rect& theRect1, Image* theImage2, const Rect& theRect2, double theFadeFactor);
	void					ColorizeImage(Image* theImage, const Color& theColor);
	DeviceImage*			CreateColorizedImage(Image* theImage, const Color& theColor);
	DeviceImage*			CopyImage(Image* theImage, const Rect& theRect);
	DeviceImage*			CopyImage(Image* theImage);
	void					MirrorImage(Image* theImage);
	void					FlipImage(Image* theImage);
	void					RotateImageHue(Sexy::MemoryImage *theImage, int theDelta);
	ulong					HSLToRGB(int h, int s, int l);
	ulong					RGBToHSL(int r, int g, int b);
	void					HSLToRGB(const ulong* theSource, ulong* theDest, int theSize);
	void					RGBToHSL(const ulong* theSource, ulong* theDest, int theSize);

	void					AddMemoryImage(MemoryImage* theMemoryImage);
	void					RemoveMemoryImage(MemoryImage* theMemoryImage);
	void					Remove3DData(MemoryImage* theMemoryImage);
	virtual void			SwitchScreenMode();
	virtual void			SwitchScreenMode(bool wantWindowed);
	virtual void			SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);	
	
	virtual Dialog*			DoDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);
	virtual Dialog*			GetDialog(int theDialogId);
	virtual void			AddDialog(int theDialogId, Dialog* theDialog,const FlagsMod &belowModalFlagsMod);
	virtual void			AddDialog(int theDialogId, Dialog* theDialog);
	virtual void			AddDialog(Dialog* theDialog);
	virtual bool			KillDialog(int theDialogId, bool removeWidget, bool deleteWidget);
	virtual bool			KillDialog(int theDialogId);
	virtual bool			KillDialog(Dialog* theDialog);
	virtual int				GetDialogCount();
	virtual void			ModalOpen();
	virtual void			ModalClose();	
	virtual void			DialogButtonPress(int theDialogId, int theButtonId);
	virtual void			DialogButtonDepress(int theDialogId, int theButtonId);
	
	virtual bool			GetCheatsEnabled();
	virtual void			SetCheatsEnabled(bool i_enabled);

	virtual void			GotFocus();
	virtual void			LostFocus();
	virtual void			StartSounds(){};
	virtual void			ActivateAudioSession();
	virtual void			DeactivateAudioSession();
	//virtual bool			IsAltKeyUsed(WPARAM wParam);
	virtual bool			KeyDown(int theKey);
	virtual bool			DebugKeyDown(int theKey);	
	virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
	virtual void			CloseRequestAsync();
	bool					Is3DAccelerated();
	bool					Is3DAccelerationSupported();
	bool					Is3DAccelerationRecommended();
	virtual void			Set3DAcclerated(bool is3D, bool reinit = true);	
	virtual void			Done3dTesting();
	virtual std::string		NotifyCrashHook(); // return file name that you want to upload
    
    virtual void            ShowKeyboard();
    virtual void            ShowPhoneNumKeyboard();
    virtual void            ShowEmailKeyboard();
    virtual void            HideKeyboard();
    virtual bool			IsKeyboardShowing();
    
	virtual bool			IsFullScreen();
	virtual int				CalcFullScreenOffset();

	UI_ORIENTATION 			FullScreenUIOrientationLeft();
	UI_ORIENTATION 			FullScreenUIOrientationRight();

    virtual void 			Vibrate(long long milliseconds);    
    virtual void 			VibrateWithPattern(long long pattern[], int isRepeat);
    virtual void 			CancelVibrate();

	virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
	//virtual bool			DrawDirtyStuff();
    
//PVZ2_CHINESE_BEGIN
    virtual void            WechatShareSuccess(){}
    virtual void            WechatShareFailed(){}
//PVZ2_CHINESE_END
	

	// Properties access methods
	bool					LoadProperties(const std::string& theFileName, bool required, bool checkSig, bool needsLocaleCorrection);
	bool					LoadProperties();
	virtual void			InitPropertiesHook();

	// Resource access methods
	bool					ReloadAllResources();
	
	bool					GetBoolean(const std::string& theId);
	bool					GetBoolean(const std::string& theId, bool theDefault);	
	int						GetInteger(const std::string& theId);
	int						GetInteger(const std::string& theId, int theDefault);
	double					GetDouble(const std::string& theId);
	double					GetDouble(const std::string& theId, double theDefault);
	SexyString				GetString(const std::string& theId);
	SexyString				GetString(const std::string& theId, const SexyString& theDefault);

	StringVector			GetStringVector(const std::string& theId);

	void					SetBoolean(const std::string& theId, bool theValue);
	void					SetInteger(const std::string& theId, int theValue);
	void					SetDouble(const std::string& theId, double theValue);
	void					SetString(const std::string& theId, const std::wstring& theValue);
	
	

	// Registry access methods
	bool					RegistryGetSubKeys(const std::string& theKeyName, StringVector* theSubKeys);
	bool					RegistryReadString(const std::string& theValueName, std::string* theString);
	bool					RegistryReadString(const std::string& theValueName, std::wstring* theString);
	bool					RegistryReadInteger(const std::string& theValueName, int* theValue);
	bool					RegistryReadBoolean(const std::string& theValueName, bool* theValue);
	bool					RegistryReadData(const std::string& theValueName, uchar* theValue, ulong* theLength);
	bool					RegistryWriteString(const std::string& theValueName, const std::string& theString);
	bool					RegistryWriteString(const std::string& theValueName, const std::wstring& theString);
	bool					RegistryWriteInteger(const std::string& theValueName, int theValue);
	bool					RegistryWriteBoolean(const std::string& theValueName, bool theValue);
	bool					RegistryWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength);	
	bool					RegistryEraseKey(const SexyString& theKeyName);
	void					RegistryEraseValue(const SexyString& theValueName);

	// File access methods
	bool					WriteBufferToFile(const std::string& theFilePath, const Buffer* theBuffer);
	bool					ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);//UNICODE
	bool					ReadBufferFromFile(const std::string& theFileName, void*& theBuffer, unsigned long& theBufferLen);
	RtSerialBuffer*			CreateReadBufferFromFile(const std::string& theFilePath, bool allowRSBFixedBuffer = true);
	bool					WriteBytesToFile(const std::string& theFilePath, const void *theData, unsigned long theDataLen);
	bool					WriteBytesToFileAt(const std::string& theFilePath, const void *theData, unsigned long theDataLen, unsigned long theSeekPos);
	bool					WriteBytesToFileEnd(const std::string& theFilePath, const void *theData, unsigned long theDataLen);
    bool                    CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen);
    bool                    CopyFile(const std::string& theFromFilePath, const std::string& theToFilePath);
    bool                    RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath);
	bool					FileExists(const std::string& theFilePath);
	bool					EraseFile(const std::string& theFilePath);

	// Misc methods
	virtual bool			UpdateAppStep(bool* updated);
	virtual bool			UpdateApp();
	void					ClearUpdateBacklog(bool relaxForASecond = false);
	bool					IsScreenSaver();
	virtual bool			AppCanRestore();

	void					RehupFocus();
    
    bool                    isReducedResolutionIPhone();

    // Touch intercept methods.
    // By default these will forward to the WidgetManager.
    // Apps can override these to get info directly, which is especially useful
    // for tricky multitouch code.
    virtual void TouchBegan(const Sexy::Touch& theTouch);
    virtual void TouchEnded(const Sexy::Touch& theTouch);
    virtual void TouchMoved(const Sexy::Touch& theTouch);
    virtual void TouchesCanceled();
	
	// Gesture detection handling
    virtual void OnGestureLongPress(Sexy::Point i_startingLocation);
	virtual void OnGestureFlick(Sexy::GestureFlickDirection i_direction, Sexy::Point i_startingLocation);
	virtual void OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta);
	virtual void AccelerometerChanged(double theTimestamp, double theX, double theY, double theZ);

	//Physical device back button handling
	virtual void OnBackButtonPressed();

#ifdef SUPPORT_AUTOREFLECTION
	Reflection::CRefSymbolDb* GetAutoReflection();
#endif
#ifdef SUPPORT_REFLECTION
	Reflection::CRefSymbolDb* GetManualReflection();
#endif
	
    // this will be a callback to override when resources change.
    // this will include modval parsing. generic for now, this will be fleshed out
    virtual void            OnResourcesUpdated( ResourceUpdateType theType, void* theInfo);
	
	//
    // This returns true if the currently running thread is the same thread that game was launched on
    //
	bool					IsMainThread() const;

	//
    // This sets the current thread as the accepted main thread
    //
	void                    SetMainThreadToCurrent();

	
	
	virtual bool			FrameNeedsSwapScreenImage();
    
private:
    
    int			m_nativeScreenWidth;
    int			m_nativeScreenHeight;

    int			m_allScreenOffset;
};
	
	//
    // SexyAppRun is the Prime way to run applications to make sure that all of the stages
    // of the app are called at the correct times for all platforms.
    //
    // SexyAppRun will not return.
    //
    // SexyAppRun is defined in the AppDrivers for platforms
	void SexyAppRun(SexyAppBase* app);  

    void SexyAppRunWithInitializedAppObject(SexyAppBase *app);

extern SexyAppBase* gSexyAppBase;

#if SEXY_IS_LIVELINK_ENABLED
/*
	AppControls - Exposes fields in SexyAppBase to reflection
*/
class AppControls : public RtObject
{
	RT_CLASS_DEFINE(AppControls, RtObject, RtClass);

	AppControls() {};
public:
	bool IsSupported();
	bool IsPaused();
	void SetPaused(bool paused);
	bool GetStepMode();
	void SetStepMode(bool isStep);
	double GetSpeed();
	void SetSpeed(double multiplier);
};

/*
	GameDiagnostics - Exposes fields in SexyAppBase to reflection
*/
class AppDiagnostics : public RtObject
{
	RT_CLASS_DEFINE(AppDiagnostics, RtObject, RtClass);

	AppDiagnostics() {};
public:
	double GetFPS();
	double GetMemoryUsed();
	double GetMemoryAvailable();
	std::string GetPlatform();
};
#endif // SEXY_IS_LIVELINK_ENABLED

}; // namespace Sexy

#endif //__SEXYAPPBASE_H__
