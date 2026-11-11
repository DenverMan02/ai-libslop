#ifndef _JAVAINTERFACE_H_
#define _JAVAINTERFACE_H_

#include <jni.h>


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM * jvm,void * reserved);
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM * jvm,void * reserved);

namespace Sexy
{
	class AndroidAppDriver;
#if !SEXY_IS_WWISE_ENABLED
	class AndroidSoundManager;
	class AndroidMusicStream;
	class AndroidMusicInterface;
#endif
}

#define PAUSEINJAVA()  Android::DEBUG::PauseInJava(__FILE__, __LINE__)

enum MobileCardType
{
	MobileCard_Null = 0,
	MobileCard_ChinaMobile = 0x01,
	MobileCard_Unicom = 0x02,
	MobileCard_Telecom = 0x04
};

namespace Android
{
	namespace Util
	{
		bool 			Register( JNIEnv* InEnv, jclass InGameClass );

		JNIEnv * 		GetJNIEnv();
		JavaVM * 		GetJVM();
		//PVZ2_CHINESE_START
		//raoyj
		jobject 		GetPackageManagerObject(JNIEnv * pEnv);
		jobject 		GetGameObject(JNIEnv * pEnv);
		std::string		GetPackageName();
		//PVZ2_CHINESE_END
		jobject 		GetHttpObject( JNIEnv * pEnv );
		jobject 		GetFacebookObject( JNIEnv * pEnv );
		bool 			StringFromJString( JNIEnv * InEnv,  std::string & outStr, jstring jsStr );

		std::string		GetUUIDString();
		long            GetElapsedRealtime();
		void            StartPNS(int version);
		void 			OpenSystemSetting();
		void 			NotifyDecompressStage();

		bool            IsAutosmoking();
	}

	namespace DEBUG
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );
		void PauseInJava( char const * InFileName, int InLineNo );
		void AndroidDebugString( char const * InFileName );
	}

	namespace Game
	{
		bool GameMonitorEnter();
		bool GameMonitorExit();
		void SetAppDriverPointer( class Sexy::AndroidAppDriver * InAppDriverPtr );
	}

	// AndroidAppDriver interfaces
	namespace Config
	{
		
		bool Register( JNIEnv * InEnv, jclass InGameClass );
		
		bool InitConfig();

		bool ConfigReadUTF8String( std::string const & theKeyName, std::string & theString );
		bool ConfigReadUTF8StringEx( std::string const & theKeyName, std::string & theString );
		bool ConfigReadWideString( std::string const & theKeyName, std::wstring & theString );
		bool ConfigReadInteger( std::string const & theKeyName, int32& theValue );
		bool ConfigReadBoolean( std::string const & theKeyName, bool& theValue );
		
		bool ConfigWriteUTF8String( std::string const & theKeyName, std::string const & theString );
		bool ConfigWriteWideString( std::string const & theKeyName, std::wstring const & theString );
		bool ConfigWriteInteger( std::string const & theKeyName, int32 theValue );
		bool ConfigWriteBoolean( std::string const & theKeyName, bool theValue );
		void ConfigEraseKey( std::string const & theKeyName );
		void ConfigEraseKey( std::wstring const & theKeyName );
	}

	namespace Game
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );
		void AcknowledgeLifecycleEvent( int iEvent );
	}

	namespace Info
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );

		std::string SysGetProductVersion();
        int SysGetProductVersionCode();
		std::string SysGetUserCurrencySymbol();
        std::string SysGetPackageName();
        std::string SysGetCPUInfo();
	}


	namespace Device
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );
		
		void ShowKeyboard();	
		void HideKeyboard();
		bool IsKeyboardShowing( bool bIncludeHardKeyboard = false );

		void Vibrate(long long milliseconds);
		void VibrateWithPattern(long long pattern[], int isRepeat);
		void CancelVibrate();

		uint32 GetStartupUIOrientation();
		uint32 GetCurrentUIOrientation();
		bool IsSupportedUIOrientation( uint32 InOrientation );
        
        std::string GetCachesDir();

        void ExitToHome();
        void ExitApp();

        void CopyToClipBoard(const std::string& content);

	}

	namespace UI
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );
		
		void ProcessTouchEvents( class Sexy::AndroidAppDriver* pDriver );
		void ProcessGesturePinchEvents( class Sexy::AndroidAppDriver* pDriver );	//PVZ2_CHINESE_BEGIN
		void ProcessKeyEvents( class Sexy::AndroidAppDriver* pDriver );
		void DidRecieveFocus();
		int Dip2Pixels(int dip);	//PVZ2_CHINESE
		void ProcessEvents( class Sexy::AndroidAppDriver* pDriver );
		void ShowAlertDialog(const std::string i_title, const std::string i_msg, const std::string i_ok = "OK", bool bExitApp = false);
		void StartShowProgressBar();
		void FinishShowProgressBar();
		void ShowExitGame();
	}

	namespace Resources
	{
		bool Register( JNIEnv * InEnv, jclass InClass );
		
		std::string GetResourceFolder( class Sexy::AndroidAppDriver* theAppDriver );
		std::string GetUserDataFolder( class Sexy::AndroidAppDriver* theAppDriver );
		std::string GetCacheDataFolder( class Sexy::AndroidAppDriver* theAppDriver );
		std::string GetAppSupportDataFolder( class Sexy::AndroidAppDriver* theAppDriver );
		std::string GetExternalStorageDirectory( class Sexy::AndroidAppDriver* theAppDriver );
		std::string GetExternalFilesDirectory(class Sexy::AndroidAppDriver* theAppDriver );

		long GetAssetFileSize( std::string const & InFilename );
		bool GetAssetFileInfo( std::string const & InFilename, std::string & outArchiveFilename, long & outFileOffset, long & outFileSize );
        
        
        long GetFileSystemBlockCount( const std::string &pathInFS );
        long GetFileSystemBlocksFree( const std::string &pathInFS );
        long GetFileSystemBlockSize( const std::string &pathInFS );

        bool InstallApk(const std::string &i_filePath);
	}
	

	namespace Graphics
	{
		bool RegisterCallbacks( JNIEnv * InEnv, jclass InGraphicsClass );
		bool Register( JNIEnv * InEnv, jclass InGraphicsClass );
		
		void Native_onSurfaceCreated( JNIEnv * env, jobject viewObj );
		void Native_onSurfaceChanged( JNIEnv * env, jobject viewObj, jint InWidth, jint InHeight );
		void Native_onSurfaceDestroyed( JNIEnv * env, jobject viewObj );

		void Native_onDrawFrame( JNIEnv * env, jobject viewObj );

		void GetScreenSizeInPixels( class Sexy::AndroidAppDriver * pDriver, int* outWidth, int* outHeight );
		void GetScreenSizeInPoints( int * pOutWidth, int * pOutHeight );
		void GetGLViewSize( class Sexy::AndroidAppDriver * pDriver, int* outWidth, int* outHeight);
		void SetGLViewContext( class Sexy::AndroidAppDriver* pDriver );
		bool IsOpenGLES20( class Sexy::AndroidAppDriver* theAppDriver );
		bool CanSetGLViewScaleFactor( class Sexy::AndroidAppDriver* theAppDriver );
		void SetGLViewScaleFactor( class Sexy::AndroidAppDriver* theAppDriver, float theScale );
		float GetGLViewScaleFactor( class Sexy::AndroidAppDriver* theAppDriver );
		bool PresentGLView( class Sexy::AndroidAppDriver* theAppDriver );
		uint32 GetGLViewSysFBO( class Sexy::AndroidAppDriver* theAppDriver );
		
		void SetLoadingContext( class Sexy::AndroidAppDriver* theAppDriver );
	}

#if !SEXY_IS_WWISE_ENABLED
	namespace SoundManager
	{
		bool Register( JNIEnv * InEnv, jclass InSoundClass );
		bool RegisterCallbacks( JNIEnv * InEnv, jclass InSoundClass );

		bool Startup( class Sexy::AndroidSoundManager * pNativeManager );
		void Shutdown();

		bool Enable( int InSampleRate, int InNumChannels, int InBitsPerSample );
		void Disable();
		
		void Update( float fDeltaTime );

		uint GetAudioFetchSize();
		void NotifyAudioAvailable( uint32 NumFramesAvailable );
		
		jint FetchAudioDataCallback( JNIEnv * env, jobject audioProxyObj, jlong pNativeManager, jbyteArray InDestData, jint InNumFramesToRead );
		jint SkipAudioDataCallback( JNIEnv * env, jobject audioProxyObj, jlong pNativeManager, jint InNumFramesToSkip );

		void FlushAudioTrack();
		
	}


	namespace Music
	{
		bool Register( JNIEnv * InEnv, jclass InMusicClass );
		bool RegisterCallbacks( JNIEnv * InEnv, jclass InClass );
		
		bool Startup( class Sexy::AndroidMusicInterface * pNativeManager );
		void Shutdown( );
		void Enable( bool bShouldEnable );

		bool SetCurrentMusicStream( class Sexy::AndroidMusicStream * pInStream );
		void SetLooping( bool bDoLooping );
		void SetCurrentStreamPosition( int InOffset );
		bool PlayCurrentStream();
		void PauseCurrentStream();
		void ResumeCurrentStream();
		void StopCurrentStream();
		bool IsStreamPlaying( class Sexy::AndroidMusicStream * pInStream  );
		void SetDeviceVolume( float fVolume );

		void NotifyMusicCompletedCallback( jlong pNativeManager, jstring InFilename, jint InMusicId );
		void NotifyMusicErrorCallback( jlong pNativeManager, jlong MusicContext, jstring InFilename, jint InMusicId, jint InErrorCode );
	}
#endif


	namespace Diag
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );

		void GetPrimaryMACAddress( std::string & outString );
		void GetOSVersion( std::string & outString );
		void GetHardwareModel( std::string & outString );
		void GetDeviceID( std::string & outString );
		void GetUniqueCharacterID( std::string & outString );
		void GetLocal(std::string & outString);		//PVZ2_CHINESE

		long GetAvailMemory();						//PVZ2_CHINESE
		long GetUsedMemory();						//PVZ2_CHINESE

		std::string GetNetworkType();	//PVZ2_CHINESE
		int GetMobileCardType();	//PVZ2_CHINESE
		bool IsMobileCardType(MobileCardType i_type);
		int GetSimProvince();
		void GetDeviceIMSI( std::string& outString);
		void GetDeviceIMEI( std::string& outString);
		void GetDeviceMODEL( std::string& outString);
		void GetDeviceBRAND( std::string& outString);
		bool HasNotchInScreen(int i_type);
		int GetNotchHeight(int i_type);
		int GetSwitchOpen();
	}

	namespace Web
	{
		bool Register( JNIEnv * InEnv, jclass InGameClass );

		bool SysOpenURL( std::string const & theURL );
	}

	namespace Http
	{
		int Register( JNIEnv * InEnv, jclass InHttpClass );
	}
}

namespace Sexy
{
	// these functions are called from outside Android specific code.
	inline std::string SysGetProductVersion()
	{
		return Android::Info::SysGetProductVersion();
	}

	inline tm* SysGetTimeBombDate()
	{
		return NULL;//Android::Info::SysGetTimeBombDate();
	}

	std::string GetLocale();
	bool IsInterfaceTabletSize();
	std::string GetCountryCodeString();

	std::string SysGetOSVersionString();
}

#endif // _JAVAINTERFACE_H_

