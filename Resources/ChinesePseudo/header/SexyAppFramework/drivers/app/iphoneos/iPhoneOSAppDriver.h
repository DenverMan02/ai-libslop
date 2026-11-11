#pragma once
#ifndef IPHONEOSAPPDRIVER_H_INCLUDED
#define IPHONEOSAPPDRIVER_H_INCLUDED

#include "IAppDriver.h"
#include "Interpolator.h"

#include "KeyCodes.h"
#include "SexyURL.h"
#include "MemoryImage.h"
#include "drivers/app/iphoneos/ObjCInterface.h"

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
	
	class iPhoneOSGraphicsDriver;
	
	
	//this fetches a system font lazily, for use in debug huds
	SysFont* GetSystemFont();

	class iPhoneOSAppDriver  : public IAppDriver
	{
	public:
		iPhoneOSAppDriver(SexyAppBase*);
		virtual ~iPhoneOSAppDriver();
		
		virtual bool			InitAppDriver();
		
		
		virtual void			Start();	
		virtual void			Init();	//this is effectively empty for Mac, b/c SexyAppRun reorders initiazation from the SexyApplication
		virtual void			InitPreAppLaunch();
		virtual void			InitPostAppLaunch();
		
		virtual void			LaunchApp();
		
		virtual void			InitWindowCreated();
		virtual bool			UpdateAppStep(bool* updated);
		virtual void			ClearUpdateBacklog(bool relaxForASecond = false);
		virtual void			Shutdown();	
		virtual void			DoExit(int theCode);
		
		
		virtual void			Remove3DData(MemoryImage* theMemoryImage);

		void					DisplayLinkUpdateAppStep(double timeStamp);
	public:
		
		// Public methods
		virtual void			BeginPopup();
		virtual void			EndPopup();
#if PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED
        virtual int				ReportingPopup(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC);
        virtual int				ReportingPopup(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC);
        virtual int				DisplayReportingPopup(const SexyString &theText, const SexyString &theTitle, int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC);
#endif //PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED
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
		virtual bool			KeyDown(int theKey);
		virtual bool			DebugKeyDown(int theKey);	
		virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		virtual bool			Is3DAccelerated();
		virtual bool			Is3DAccelerationSupported();
		virtual bool			Is3DAccelerationRecommended();
		virtual void			Set3DAcclerated(bool is3D, bool reinit = true);	
        virtual bool            IsUIOrientationAllowed(UI_ORIENTATION theOrientation);
        virtual void            ShowKeyboard();
        virtual void            ShowPhoneNumKeyboard();
        virtual void            ShowEmailKeyboard();
        virtual void            HideKeyboard();
        virtual bool			IsKeyboardShowing();
        virtual std::string     GetDeviceName();
        virtual void 			Vibrate(long long milliseconds);
		
		virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
		
		// Resource access methods
		virtual bool			ReloadAllResources();
        
		
        int                     GetFPS();
        uint64                  GetMemoryUsed();
        uint64                  GetMemoryAvailable(); 
		
		
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
		virtual bool			WriteBufferToFile(const std::string& theFilePath, const Buffer* theBuffer);
		virtual bool			ReadBufferFromFile(const std::string& theFilePath, Buffer* theBuffer, bool dontWriteToDemo = false);
		virtual bool			WriteBytesToFile(const std::string& theFilePath, const void *theData, unsigned long theDataLen);
		virtual bool			WriteBytesToFileAt(const std::string& theFilePath, const void *theData, unsigned long theDataLen, unsigned long theSeekPos);
		virtual bool			CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen);
		virtual bool            CopyFile(const std::string& theFromFilePath, const std::string& theToFilePath);
		virtual bool            RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath);
		
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
		
		void TransformPoints( int& io_x, int& io_y );
		void OnGestureFlick(GestureFlickDirection i_direction, Sexy::Point i_startingLocation);
		void OnGestureLongPress(Sexy::Point i_startingLocation);
		void OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta);

        void GotFocus();
        void LostFocus();	
		
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
		
		void RotateUI( UI_ORIENTATION theDestOrientation, float durationSecs );
		
		UI_ORIENTATION  GetUIOrientation() { return mInterfaceOrientation; }
		
        
        void DumpProgramInfo();

		// Events!
		Event1wRet< EventReturnBehavior::LogicalOr_NoShortCircuit_DefaultFalse, bool, const SexyURL& > ApplicationOpenURL;
		Event0 ApplicationWillResignActive;
		Event0 ApplicationDidBecomeActive;
		Event0 ApplicationDidEnterBackground;
		Event0 ApplicationWillBecomeForeground;
		
        void SetupOrientation();
        
        //SZF added.
        void StopAnimation();
        void StartAnimation();
        //SZF end.
        
	protected:
		bool Process(bool allowSleep=true);
		void UpdateFTimeAcc();
		
		void DoUpdateFramesF(float theFrac);
        bool DoUpdateFrames(bool primary=true);   
		
		bool DrawDirtyStuff(bool force);
		void Redraw();
		
		void SetupScreenMatrix(float theRotation);
        void OrientationChange();

		bool InitConfig();
		void SyncConfig();
        
        KeyCode CharToKeyCode(SexyChar c);
        
	public:
		SexyAppBase*			mApp;
		
		//This is the ObjC GlView object kept opaque to pass into OBJInterface functions
		void*					mGLView; 
		iPhoneOSGraphicsDriver* miPhoneOSGraphicsDriver;
		
		pthread_t m_loading_thread;
		
		int						mScreenWidth;
		int						mScreenHeight;
#if !SEXY_IS_WWISE_ENABLED
        bool                    mAudioSessionActive;
        bool                    mMusicEnabled;
#endif // !SEXY_IS_WWISE_ENABLED
		float					mScreenRotation;
		bool					mIsRotating;
        //SZF added.
        bool                    mInvaild;
        //SZF end.
		
	public:
		//public so that the other driver classes can get at this
		SexyTransform3D			mScreenMatrix;
		
		
		
		//orientation tracking
		uint64					mStartRotTick;
		uint64					mRotTickTime;
		
		bool					mRotatedHalfWay;
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
        bool                    mSupportDebugKeyboard;
        int                     mDebugKeyboardTouchCount;
        
        int                     mDisplayLinkInterval;
	};
	
	
};
#endif

