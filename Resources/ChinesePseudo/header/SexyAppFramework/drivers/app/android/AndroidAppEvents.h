
#ifndef _ANDROIDAPPEVENTS_H_
#define _ANDROIDAPPEVENTS_H_


enum EAndroidAppEventTypes
{
	  eAAET_Lifecycle
	, eAAET_OrientationChange
	, eAAET_StartFromUrl
	, eAAET_GotFocus
	, eAAET_LostFocus

	, eAAET_ApplicationWillBecomeForeground
	, eAAET_ApplicationDidBecomeActive
	, eAAET_ApplicationWillResignActive
	, eAAET_ApplicationDidEnterBackground

	, eAAET_MAX
};

struct AndroidAppEvent
{
public:
	AndroidAppEvent( EAndroidAppEventTypes InEventType )
		: mType(InEventType)
	{}
    
    virtual ~AndroidAppEvent() {}

	EAndroidAppEventTypes mType;
};


enum EAndroidLifecycleEventTypes
{
	// IMPORTANT! These values must match the eALC_* values
	//  defined over in the java code. See AndroidGameApp.java	
	  eALC_Create
	, eALC_Restart
	, eALC_Start
	, eALC_Resume
	, eALC_Pause
	, eALC_Stop
	, eALC_Destroy
	
	, eALC_MAX
};

struct AndroidGotFocusEvent : public AndroidAppEvent
{
	AndroidGotFocusEvent()
		: AndroidAppEvent( eAAET_GotFocus )
	{}
    
    virtual ~AndroidGotFocusEvent() {}
};

struct AndroidLostFocusEvent : public AndroidAppEvent
{
	AndroidLostFocusEvent()
		: AndroidAppEvent( eAAET_LostFocus )
	{}
    
    virtual ~AndroidLostFocusEvent() {}
};


struct AndroidAppLifeCycleEvent : public AndroidAppEvent
{
	AndroidAppLifeCycleEvent( EAndroidLifecycleEventTypes InLifecycleStage, bool InbWantsACK )
		: AndroidAppEvent( eAAET_Lifecycle )
		, mLifecycleStage(InLifecycleStage)
		, mbWantsACK( InbWantsACK )
	{}
    
    virtual ~AndroidAppLifeCycleEvent() {}

	EAndroidLifecycleEventTypes mLifecycleStage;
	bool mbWantsACK;
};

struct AndroidAppOrientationChangeEvent : public AndroidAppEvent
{
	AndroidAppOrientationChangeEvent( Sexy::UI_ORIENTATION InOldOrientation, Sexy::UI_ORIENTATION InNewOrientation, int InNewWidth, int InNewHeight )
		: AndroidAppEvent( eAAET_OrientationChange )
		, mOldOrientation(InOldOrientation)
		, mNewOrientation(InNewOrientation)
		, mNewWidth(InNewWidth)
		, mNewHeight(InNewHeight)
	{}
    
    virtual ~AndroidAppOrientationChangeEvent() {}

	Sexy::UI_ORIENTATION mOldOrientation;
	Sexy::UI_ORIENTATION mNewOrientation;
	int mNewWidth;
	int mNewHeight;
};

struct AndroidApplicationWillBecomeForegroundEvent : public AndroidAppEvent
{
	AndroidApplicationWillBecomeForegroundEvent()
		: AndroidAppEvent( eAAET_ApplicationWillBecomeForeground )
	{}
    
    virtual ~AndroidApplicationWillBecomeForegroundEvent() {}
};

struct AndroidApplicationDidBecomeActiveEvent : public AndroidAppEvent
{
	AndroidApplicationDidBecomeActiveEvent()
		: AndroidAppEvent( eAAET_ApplicationDidBecomeActive )
	{}
    
    virtual ~AndroidApplicationDidBecomeActiveEvent() {}
};

struct AndroidApplicationWillResignActiveEvent : public AndroidAppEvent
{
	AndroidApplicationWillResignActiveEvent()
		: AndroidAppEvent( eAAET_ApplicationWillResignActive )
	{}
    
    virtual ~AndroidApplicationWillResignActiveEvent() {}
};

struct AndroidApplicationDidEnterBackgroundEvent : public AndroidAppEvent
{
	AndroidApplicationDidEnterBackgroundEvent()
		: AndroidAppEvent( eAAET_ApplicationDidEnterBackground )
	{}
    
    virtual ~AndroidApplicationDidEnterBackgroundEvent() {}
};

struct AndroidAppStartFromUrlEvent : public AndroidAppEvent
{
	AndroidAppStartFromUrlEvent( std::string aURL )
		: AndroidAppEvent( eAAET_StartFromUrl )
		, mStartUrl( aURL )
	{}
    
    virtual ~AndroidAppStartFromUrlEvent() {}

	std::string mStartUrl;
};



#endif // _ANDROIDAPPEVENTS_H_

