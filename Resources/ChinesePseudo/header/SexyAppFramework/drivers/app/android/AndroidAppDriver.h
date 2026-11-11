#pragma once
#ifndef ANDROIDAPPDRIVER_H_INCLUDED
#define ANDROIDAPPDRIVER_H_INCLUDED

#include "IAppDriver.h"
#include "Interpolator.h"

#include "RtDelegate.h"
#include "SexyURL.h"

#include "KeyCodes.h"
#include <list>

struct AndroidAppEvent;


namespace Sexy
{
	struct Touch;
	typedef enum
	{
		DEVICE_ORIENTATION_UNKNOWN,              // UIDeviceOrientationUnknown
		DEVICE_ORIENTATION_PORTRAIT,             // UIDeviceOrientationPortrait
		DEVICE_ORIENTATION_PORTRAIT_UPSIDE_DOWN, // UIDeviceOrientationPortraitUpsideDown
		DEVICE_ORIENTATION_LANDSCAPE_LEFT,       // UIDeviceOrientationLandscapeLeft
		DEVICE_ORIENTATION_LANDSCAPE_RIGHT,      // UIDeviceOrientationLandscapeRight
		DEVICE_ORIENTATION_FACE_UP,              // UIDeviceOrientationFaceUp
		DEVICE_ORIENTATION_FACE_DOWN,            // UIDeviceOrientationFaceDown
	} DeviceOrientation;

	enum NotchPlatform
	{
		NOTCH_HUAWEI,
		NOTCH_XIAOMI,
		NOTCH_VIVO,
	};

	class AndroidGraphicsDriver;


	//this fetches a system font lazily, for use in debug huds
	SysFont* GetSystemFont();

	class AndroidAppDriver  : public IAppDriver
	{
	public:
		AndroidAppDriver(SexyAppBase*);
		virtual ~AndroidAppDriver();

		virtual bool			InitAppDriver();


		virtual void			Start();	
		virtual void			Init();
		virtual void			LaunchApp();
		virtual void			InitPreAppLaunch();
		virtual void			InitPostAppLaunch();

		virtual void			InitWindowCreated();
		virtual bool			UpdateAppStep(bool* updated);
		virtual void			ClearUpdateBacklog(bool relaxForASecond = false);
		virtual void			Shutdown();	
		virtual void			DoExit(int theCode);


		virtual void			Remove3DData(MemoryImage* theMemoryImage);

	public:
			
		// Public methods
		virtual void			BeginPopup();
		virtual void			EndPopup();
		virtual int				MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MB_OK);
		virtual int				MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MB_OK);
		virtual void			Popup(const std::string& theString);
		virtual void			Popup(const std::wstring& theString);


		virtual bool			OpenURL(const std::string& theURL, bool shutdownOnOpen = false);	


		virtual std::string		GetGameSEHInfo();



		virtual void			DoParseCmdLine();
		virtual void			ParseCmdLine(const std::string& theCmdLine);
		virtual void			HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);






		virtual void			StartLoadingThread();
		virtual double			GetLoadingThreadProgress();	

		virtual void			CopyToClipboard(const std::string& theString);
		virtual std::string		GetClipboard();

		virtual void			SetCursor(int theCursorNum);
		virtual int				GetCursor();
		virtual void			EnableCustomCursors(bool enabled);	

		virtual void			SetCursorImage(int theCursorNum, Image* theImage);


		virtual void			SwitchScreenMode();
		virtual void			SwitchScreenMode(bool wantWindowed);
		virtual void			SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);	


		//virtual bool			IsAltKeyUsed(WPARAM wParam);

        virtual void            InputCancelAll();
				void			KeyDown(Sexy::KeyCode theKeyCode, SexyChar theChar);
		virtual bool			KeyDown(int theKey);
		virtual bool			DebugKeyDown(int theKey);	
		virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		virtual bool			Is3DAccelerated();
		virtual bool			Is3DAccelerationSupported();
		virtual bool			Is3DAccelerationRecommended();
		virtual void			Set3DAcclerated(bool is3D, bool reinit = true);	
		virtual bool            IsUIOrientationAllowed(UI_ORIENTATION theOrientation);
		virtual void            ShowKeyboard();
		virtual void            HideKeyboard();
        virtual std::string     GetDeviceName();
        virtual void            ShowPhoneNumKeyboard();
        virtual void            ShowEmailKeyboard();
        
		virtual void			Vibrate(long long milliseconds);		
		virtual void 			VibrateWithPattern(long long pattern[], int isRepeat);
		virtual void 			CancelVibrate();

        // HVS_JJK Added missing function
        virtual bool            IsKeyboardShowing();

		virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName);

		// Resource access methods
		virtual bool			ReloadAllResources();

		//PVZ2_CHINESE_START
		long                  GetMemoryUsed();
		long                  GetMemoryAvailable();
		//PVZ2_CHINESE_END

		//sort of need these in the driver, but I'd like to remove the idea of a registry...
		// Registry access methods
		virtual bool			ConfigGetSubKeys(const std::string& theKeyName, StringVector* theSubKeys);
		virtual bool			ConfigReadString(const std::string& theValueName, std::string* theString);
		virtual bool			ConfigReadString(const std::string& theValueName, std::wstring* theString);
		virtual bool			ConfigReadInteger(const std::string& theValueName, int* theValue);
		virtual bool			ConfigReadBoolean(const std::string& theValueName, bool* theValue);
		virtual bool			ConfigReadData(const std::string& theValueName, uchar* theValue, ulong* theLength);
		virtual bool			ConfigWriteString(const std::string& theValueName, const std::string& theString);
		virtual bool			ConfigWriteString(const std::string& theValueName, const std::wstring& theString);
		virtual bool			ConfigWriteInteger(const std::string& theValueName, int theValue);
		virtual bool			ConfigWriteBoolean(const std::string& theValueName, bool theValue);
		virtual bool			ConfigWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength);	
		virtual bool			ConfigEraseKey(const SexyString& theKeyName);
		virtual void			ConfigEraseValue(const SexyString& theValueName);

		// File access methods
		virtual bool			WriteBufferToFile(const std::string& theFileName, const Buffer* theBuffer);
		virtual bool			ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);
		virtual bool			WriteBytesToFile(const std::string& theFileName, const void *theData, unsigned long theDataLen);
		virtual bool			WriteBytesToFileAt(const std::string& theFilePath, const void *theData, unsigned long theDataLen, unsigned long theSeekPos);
		virtual bool			WriteBytesToFileEnd(const std::string& theFilePath, const void *theData, unsigned long theDataLen);
		virtual bool			CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen);
		virtual bool            CopyFile(const std::string& theFromFilePath, const std::string& theToFilePath);
        virtual bool            RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath);

        virtual int             GetProductVersionCode();
        virtual std::string     GetProductVersionName();
        virtual std::string     GetPackageName();

		void SysMouseDown(int x, int y, int button);
		void SysMouseUp(int x, int y, int button);
		void SysMouseMove(int x, int y);
		void SysMouseDrag(int x, int y);
		void SysMouseWheel(int theDelta);

		void TouchBegan( const Sexy::Touch& touch );
		void TouchEnded( const Sexy::Touch& touch );
		void TouchMoved( const Sexy::Touch& touch );
		void TouchesCanceled();
		void TouchesCanceled_Internal();
		void TransformTouch( Touch *touch );
		
		void TransformPoint( Sexy::Point *point );
		void OnGestureFlick(GestureFlickDirection i_direction, Sexy::Point i_startingLocation);
		void OnGestureLongPress(Sexy::Point i_startingLocation);
		void OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta);
		void OnBackButtonPressed();
		
		void GotFocus();
		void LostFocus();	

		void StartSounds();
		void GainedWindow();
		void LostWindow();

		void DoVibration();
		void ActivateAudioSession();

		void DeactivateAudioSession();        
		void EnableMusic( bool enable );        
		void DeviceOrientationChanged( DeviceOrientation orientation );
		void AccelerometerDidAccelerate( double timestamp, double ax, double ay, double az );

		DeviceImage*	GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
        DeviceImage*	GetOptimizedImage(ImageLib::Image *image, bool commitBits, bool allowTriReps, bool inShouldDeleteSrcImage);

		const SexyMatrix4& GetScreenMatrix();

		bool			ShouldPauseUpdates();

		UI_ORIENTATION	GetOrientation() { return mInterfaceOrientation; }

		void RotateUI(UI_ORIENTATION theSrcOrientation, UI_ORIENTATION theDestOrientation);

		UI_ORIENTATION  GetUIOrientation() { return mInterfaceOrientation; }

#if 0 
		void MapLogicalPointToScreenPoint( float theLogicalX, float theLogicalY, float *theResultX, float *theResultY );
		void MapScreenPointToLogicalPoint( float theScreenX, float theScreenY, float *theResultX, float *theResultY );
#endif
		void DumpProgramInfo();	

		typedef Delegate0 Callback;

		virtual bool isOppoFullScreen();
		virtual int CalcOppoFullScreenOffset();
	protected:
		bool Process(bool allowSleep=false);
		void UpdateFTimeAcc();

		void DoUpdateFramesF(float theFrac);
		bool DoUpdateFrames();

		bool DrawDirtyStuff(bool force);
		void Redraw();

		void SetupScreenMatrix(float theRotation);
		void OrientationChange();
		void SetupOrientation();

		bool InitConfig();
		void SyncConfig();

		KeyCode CharToKeyCode(SexyChar c);


	public:		
		void DisplayLinkUpdateAppStep();

	public:
		SexyAppBase*			mApp;

		//This is the opaque GlView object passed to JavaInterface functions
		void*					mGLView; 
		AndroidGraphicsDriver*	mAndroidGraphicsDriver;

		SexyThreadId			m_loading_thread;

		int						mScreenWidth;
		int						mScreenHeight;
		bool                    	mAudioSessionActive;

		float					mScreenRotation;
			
	public:
		bool mMusicEnabled;

		//public so that the other driver classes can get at this
		SexyTransform3D			mScreenMatrix;

		// QZY added.
		int 					mFrontBufferWidth;
		int 					mFrontBufferHeight;
		SexyTransform3D			mDeviceScreenMatrix;
		const SexyMatrix4& GetDeviceScreenMatrix();
		void SetDeviceResolution(int w, int h);
		// QZY end.


		//orientation tracking
		uint64					mStartRotTick;
		FloatInterpolator*		mRotationInterpolator;

		bool const mbLerpOrientationChanges;
		bool mbIsOrientationChangeInProgress;
		bool mbRotatedHalfWay;
		UI_ORIENTATION			mNewOrientation;
		UI_ORIENTATION			mInterfaceOrientation;


		//Audio

		TouchList				mTouches;

		//Debug Drawing
		bool					mDebugOverlayRSB;
		bool					mDebugOverlayGraphics;
		// Config
		bool					mConfigInitted;

		int						mMiniUpdateExtraFrame;

		SexyString              mSysInfoStr;
		SexyString              mGameInfoStr;

		bool                    mUseMultitouch;
		bool                    mHasSingleTouch;
		Touch                   mCurSingleTouch;

		bool					mbForceReinitSurface;
private:

		uint64 					mLastFrameTime;
        int						mFrameTimer;
		int						mFrameStep;
		int						mFrameDelta;

		bool mbAppIsSuspended;
		int32 mLostFocusCount;
		
		struct CallbackInstanceEquals
		{
			void* instanceContext;
			CallbackInstanceEquals( void* _instanceContext ) : instanceContext( _instanceContext ) {}
			bool operator()( const Callback& callback ) { return callback.GetInstanceContext() == instanceContext; }
		};

		static CritSect sCallbackQueueCS;
		typedef std::vector< Callback > CallbackQueue_t;
		static CallbackQueue_t sCallbackQueue;

		void HandleCallbacks();

		static CritSect sAppEventQueueCS;
		typedef 	std::list<AndroidAppEvent*> AppEventQueue_t;
		static AppEventQueue_t sAppEventQueue;

		void HandleAndroidEvents();
		void HandleAndroidLifecycleEvent( AndroidAppEvent * pEvent );
		void HandleAndroidOrientationChange( AndroidAppEvent * pEvent );
		void HandleAndroidStartFromUrl( AndroidAppEvent * pEvent );

		void HandleApplicationWillBecomeForeground();
		void HandleApplicationDidBecomeActive();
		void HandleApplicationWillResignActive();
		void HandleApplicationDidEnterBackground();

		void HandleAndroidLifecyclePause();
		void HandleAndroidLifecycleResume();
		void HandleAndroidLifecycleDestroy();
		int GetNotchPlatformByPackageName(const std::string& i_package);
		
public:
		void HandleAndroidSurfaceCreated();
		void HandleAndroidSurfaceChange( int InNewWidth, int InNewHeight );

		static void StaticNotifyApplicationGainFocus();
		static void StaticNotifyApplicationLoseFocus();
	
		static void StaticNotifyApplicationWillBecomeForeground();
		static void StaticNotifyApplicationDidBecomeActive();

		static void StaticNotifyApplicationWillResignActive();
		static void StaticNotifyApplicationDidEnterBackground();

		static void StaticNotifyOrientationChanged( UI_ORIENTATION InOldOrienation, UI_ORIENTATION InNewOrientation, int InNewWidth, int InNewHeight );
		
		static void StaticEnqueueCallback( const Callback& callback );
		static void StaticRemoveCallbacksForInstanceContext( void* instanceContext );
		static void StaticEnqueueAndroidEvent( AndroidAppEvent * pNewEvent );

		// Events!
		static void StaticApplicationOpenURL( std::string  aURL);
		Event1wRet< EventReturnBehavior::LogicalOr_NoShortCircuit_DefaultFalse, bool, const SexyURL& > ApplicationOpenURL;

protected:
	
		template< typename T, typename P1 >
		struct CallbackBinder1
		{
			typedef void (T::*M)( const P1& );
			CallbackBinder1( T& instance, M method, const P1& param1 )
				: mInstance( instance ), mMethod( method ), mParam1( param1 )
				, mCallback( MakeDelegate( *this, &CallbackBinder1::Func ) )
				{ }
			void Func()
			{
				(mInstance.*mMethod)( mParam1 );
				delete this;
			}
			AndroidAppDriver::Callback mCallback;
			T& mInstance;
			M mMethod;
			P1 mParam1;
		};

		template< typename T, typename P1, typename P2 >
		struct CallbackBinder2
		{
			typedef void (T::*M)( const P1&, const P2& );
		public:
			CallbackBinder2( T& instance, M method, const P1& param1, const P2& param2 )
				: mInstance( instance ), mMethod( method ), mParam1( param1 ), mParam2( param2 )
				, mCallback( MakeDelegate( *this, &CallbackBinder2::Func ) )
				{ }
			void Func()
			{
				(mInstance.*mMethod)( mParam1, mParam2 );
				delete this;
			}
			Callback mCallback;
			T& mInstance;
			M mMethod;
			P1 mParam1;
			P2 mParam2;
		};

public:
	
		template< typename T >
		static void StaticEnqueueCallback( T& instance, void (T::*method)() )
		{
			Callback callback = MakeDelegate( instance, method );
			StaticEnqueueCallback( callback );
		}
	
		template< typename T, typename P1 >
		static void StaticEnqueueCallback( T& instance, void (T::*method)(const P1&), const P1& param1 )
		{
			CallbackBinder1<T,P1>* callback = new CallbackBinder1<T,P1>( instance, method, param1 );
			StaticEnqueueCallback( callback->mCallback );
		}
	
		template< typename T, typename P1, typename P2 >
		static void StaticEnqueueCallback( T& instance, void (T::*method)(const P1&, const P2&), const P1& param1, const P2& param2 )
		{
			CallbackBinder2<T,P1,P2>* callback = new CallbackBinder2<T,P1,P2>( instance, method, param1, param2 );
			StaticEnqueueCallback( callback->mCallback );
		}
	
	
	};
		
	
}

#endif // ANDROIDAPPDRIVER_H_INCLUDED

