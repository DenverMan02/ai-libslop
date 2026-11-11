#ifndef OBJCINTERFACE_H_INCLUDED
#define OBJCINTERFACE_H_INCLUDED

#include <string>
#include <ctime>
#include "Common.h"
#include "RtDelegate.h"
#include "MemoryImage.h"

#if SEXY_IS_CAMERA_ENABLED
#include "ICameraDriver.h"
#endif

namespace Sexy
{
    typedef Delegate1<MemoryImage *> ImageReceivedDelegate;

	class iPhoneOSAppDriver;
	
	bool CreateAppWindows(iPhoneOSAppDriver*);
	bool RunApplication(iPhoneOSAppDriver*);

	unsigned int GetGLViewSysFBO(iPhoneOSAppDriver*);
	void SetGLViewContext(iPhoneOSAppDriver*);
	void SetLoadingContext(iPhoneOSAppDriver*);
	void PresentGLView(iPhoneOSAppDriver*);
    void ForceViewResize(iPhoneOSAppDriver* driver);
    void SetGLViewScaleFactor(iPhoneOSAppDriver*,float theScale);
	float GetGLViewScaleFactor(iPhoneOSAppDriver*);
    bool CanSetGLViewScaleFactor(iPhoneOSAppDriver*);
	void GetScreenSizeHelper( int appOrientation, float & outWidth, float & outHeight );
	void GetScreenSizeInPoints(int* width, int* height);
	void GetScreenSizeInPixels(iPhoneOSAppDriver*,int* width, int* height);
    void GetNativeScreenSizeInPixels(iPhoneOSAppDriver* driver,int* width, int* height);
	void GetGLViewSize(iPhoneOSAppDriver*, int* width, int* height);
    void GetDeviceScreenSize(int& width,int & height);
	float GetPointSizeInPixels();
    float GetNativePointSizeInPixels();
    
	bool IsKeyboardShowing();
    void ShowKeyboard();
    void ShowPhoneNumKeyboard();
    void ShowEmailKeyboard();
    void HideKeyboard();
    
    void Vibrate();

    void* ShowReportingPopup(iPhoneOSAppDriver* theDriver, const SexyString &theText, const SexyString &theTitle, int theFlags, bool allowResizing, int* theReturnCode);
	
	iPhoneOSAppDriver* GetAppDriver();
    std::string GetCPUInfo();
	std::string GetResourceFolder(iPhoneOSAppDriver*);
	std::string GetUserDataFolder(iPhoneOSAppDriver*);
	std::string GetCacheDataFolder(iPhoneOSAppDriver*);
    std::string GetAppSupportDataFolder(iPhoneOSAppDriver*);
    bool SetDataFolderAsNoBackup_iOS_5_1_later(const std::string& inPath);
    bool SetDataFolderAsNoBackup_iOS_5_0_1(const std::string& inPath);
    
    float GetTotalDiskSpaceInBytes();
	uint64 GetDeviceFreeDiskSpaceInKB();
    std::string GetLocale();
    
    bool iPhoneOSSysOpenURL(const std::string& theURL);
    
    std::string SysGetProductVersion();
    int SysGetProductVersionCode();
    std::string SysGetProductVersionName();

    std::string SysGetBuildNumber();
    tm* SysGetPlistDate(const std::string& key);
    std::string SysGetHardwareInfoString();
    std::string SysGetOSVersionString();
    std::string SysGetDeviceVersionString();

    void SetDefaultAppIdPrefix( const std::string& prefix );
	std::string GetApplicationIdentifierPrefix();
	std::string GetApplicationIdentifier();
	std::string GetBundleIdentifier();
	std::string GetAPSEnvironment();
    std::string GetCountryString();
	std::string GetCountryCodeString();
    
    int	IPhoneOSSysNumCommandLineParams();
    std::string IPhoneOSSysGetCommandLineParam(int theParam);
	
	void AddUIEvents(iPhoneOSAppDriver* driver);
	void ProcessUIEvents(iPhoneOSAppDriver* driver);

	//these use the UI_ORIENTATION enum
	int GetStartupUIOrientation();
    bool IsSupportedUIOrientation( int orientation );
    unsigned int SupportedUIOrientations(); //use bit mask
    
	void* CreateAutoreleasePool();
	void DrainAutoreleasePool( void* pool );
    
    bool IsOSVersionSupported( const std::string& aVersionQuery );
    
    //PVZ2_CHINESE_START Copy Protection
    bool IsIOS_SEVEN();
    float IOS_Version();
    bool IsLegacyIOSDevice();
    std::string GetIdentifierForVendor();
    //PVZ2_CHINESE_END
    
    std::string getValueInKeychain(std::string key);
    bool storeValueInKeychain(std::string key, std::string value);
    
#if SEXY_IS_CAMERA_ENABLED
	unsigned int GetNumCameras( Sexy::ECameraPlacement placementFilter );
	
	void SetCameraPreviewRect( ICameraDriver * theDriver, Rect const & absRect );

    void CreateFrontFacingCameraView( ICameraDriver * theDriver );
    void TakeFrontFacingCameraPicture( ICameraDriver * theDriver, ImageReceivedDelegate delegate) ;
    void DestroyFrontFacingCameraView( ICameraDriver * theDriver );
	
	void ShowCameraView();
	void HideCameraView();
	
#endif // SEXY_IS_CAMERA_ENABLED
};

#endif
