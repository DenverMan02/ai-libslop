#ifndef OBJCINTERFACE_H_INCLUDED
#define OBJCINTERFACE_H_INCLUDED

#include <string>
#include "Common.h"

namespace Sexy 
{
	class MacosxAppDriver;
	
	bool AnotherInstanceIsRunning();
	
	bool AppDriverConstructHelper(MacosxAppDriver*);
	bool AppDriverDestructHelper(MacosxAppDriver*);
	bool CreateAppWindow(MacosxAppDriver*);
	bool DestroyAppWindow(MacosxAppDriver*);
	bool ShowAppWindow(MacosxAppDriver*);
	bool HideAppWindow(MacosxAppDriver*);
	
	void SetGLViewContext(MacosxAppDriver*);
	void PresentGLView(MacosxAppDriver*);
	
	void GetGLViewContentSize(MacosxAppDriver* driver,int* width, int* height);
	
	void GetMacosxScreenSize(int* width, int* height);
	//gets the screen size for the screen that the window is currently on
	void GetMacosxWindowScreenSize(MacosxAppDriver* driver,int* width, int* height);
	
	void* ShowMacosxOpenDialog(MacosxAppDriver* theDriver, int theFlags,std::string* theReturnFile, int* theReturnCode);
	void  CleanMacosxOpenDialog(void* theHandle);
	
	void* ShowMacosxSaveDialog(MacosxAppDriver* theDriver, int theFlags,std::string* theReturnFile, int* theReturnCode);
	void  CleanMacosxSaveDialog(void* theHandle);
	
	void* ShowMacosxMsgBox(MacosxAppDriver* theDriver, const SexyString &theText, const SexyString &theTitle, int theFlags, int* theReturnCode);
	void  CleanMacosxMsgBox(void* theHandle);
	
	bool MacosxSysOpenURL(const std::string& theURL);
	
	void* MacosxCreateCursor( int width, int height, int x, int y, const uint32* bits );
	void MacosxReleaseCursor( void* cursor );
	void MacosxSetCustomCursor(MacosxAppDriver* theDriver, void* theCursor);
	void MacosxSetSystemCursor(MacosxAppDriver* theDriver, int theCursorType);
	
	void MacosxSysMinimize(MacosxAppDriver* theDriver, bool shouldMinimize=true);
	
	SexyString MacosxSysGetMemLoadString();
										 
	SexyString MacosxSysGetOSVersionString();
	
	SexyString MacosxSysGetHardwareInfoString();
	
	std::string MacosxSysGetProductVersion();
	
	std::string GetResourceFolder(MacosxAppDriver*);
	std::string GetUserDataFolder(MacosxAppDriver* driver);
	std::string GetCacheDataFolder(MacosxAppDriver* driver);
	
	void AddNSEvents(MacosxAppDriver*);
	void ProcessNSEvents(MacosxAppDriver*);
	
	void			CopyToClipboard(const std::string& theString);
	std::string		GetClipboard();
	
	void MacosxSysRestartApp(MacosxAppDriver* theDriver);
	
	bool MacosxSysIsFullScreen(MacosxAppDriver* theDriver);
	void MacosxSysEnterFullScreen(MacosxAppDriver* theDriver);
	void MacosxSysExitFullScreen(MacosxAppDriver* theDriver);
	
	void MacosxSysLog(const char* theString);
	
	void* CreateAutoreleasePool();
	void DrainAutoreleasePool( void* pool );
	
	int	MacosxSysNumCommandLineParams();
	std::string MacosxSysGetCommandLineParam(int theParam);
	
	void MacosxSysPlayDebugSound(const std::string& theSoundName);
};

#endif