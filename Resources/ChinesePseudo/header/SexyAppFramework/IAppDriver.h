#pragma once
#ifndef IAPPDRIVER_H_INCLUDED
#define IAPPDRIVER_H_INCLUDED

#include "Common.h"
#include "Buffer.h"
#include "Rect.h"
#include "PopLoc.h"
#include "RtDelegate.h"
#include "SexyAppBase.h"


namespace ImageLib
{
	class Image;
};

#ifndef RELEASEFINAL
namespace Reflection
{
	class CRefSymbolDb;
}
#endif


namespace Sexy
{
	class SexyAppBase;
	class MemoryImage;
	class MusicInterface;
	class Image;

	class SexyAppBase;

	class WidgetSafeDeleteInfo;
	class PIEffect;
	class Dialog;
	class PopAnim;
	class ImageFont;

    enum ReportDisplayType
    {
        RPT_DISPLAY_BASIC,
        RPT_DISPLAY_GRAPHIC
    };


	/**
	 * System functions related to interfacing with the OS
	 * as a native application can go here (creating windows,
	 * dealing w menus/messages, etc...)
	 *
	 * This is empty for now as the interface is being iterated in the WindowsAppDriver until it looks better
	 */
	class IAppDriver 
	{
	public:
		static IAppDriver* CreateAppDriver(SexyAppBase*);

		virtual ~IAppDriver() {};
		
		virtual bool			InitAppDriver() = 0;
#ifdef PRIME_FOR_BEJBLITZ
		virtual void			RunInit() {}
		virtual bool			RunStep() { Start(); return false; }
		virtual void			RunDone() {}
#endif
		virtual void			Start() = 0;	
		virtual void			Init() = 0;	
		virtual bool			UpdateAppStep(bool* updated) = 0;
		virtual void			ClearUpdateBacklog(bool relaxForASecond = false) = 0;
		virtual void			Shutdown() = 0;	
		virtual void			DoExit(int theCode) = 0;
		
		
		virtual void			Remove3DData(MemoryImage* theMemoryImage) = 0;
	public:
		
		// Public methods
		virtual void			BeginPopup() = 0;
		virtual void			EndPopup() = 0;
		virtual int				MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MSGBOX_OK) = 0;
		virtual int				MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MSGBOX_OK) = 0;
		virtual void			Popup(const std::string& theString) = 0;
		virtual void			Popup(const std::wstring& theString) = 0;
#   if (PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED) && IS_SUPPORT_REPORTING_DEFINED
        virtual int             ReportingPopup(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC) = 0;
        virtual int             ReportingPopup(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC) = 0;
#   endif
		
		
		virtual bool			OpenURL(const std::string& theURL, bool shutdownOnOpen = false) = 0;
		
		
		virtual std::string		GetGameSEHInfo() = 0;
		virtual void			SEHOccured() {}
		virtual void			GetSEHWebParams(DefinesMap* theDefinesMap) {}
		
		virtual void			DoParseCmdLine() = 0;
		virtual void			ParseCmdLine(const std::string& theCmdLine) = 0;
		virtual void			HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue) = 0;
		
		
		
		
		
		
		virtual void			StartLoadingThread() = 0;
		virtual double			GetLoadingThreadProgress() = 0;	
		
		virtual void			CopyToClipboard(const std::string& theString) = 0;
		virtual std::string		GetClipboard() = 0;
		
		virtual void			SetCursor(int theCursorNum) = 0;
		virtual int				GetCursor() = 0;
		virtual void			EnableCustomCursors(bool enabled) = 0;	
		
		virtual void			SetCursorImage(int theCursorNum, Image* theImage) = 0;
		
		
		virtual void			SwitchScreenMode() = 0;
		virtual void			SwitchScreenMode(bool wantWindowed) = 0;
		virtual void			SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false) = 0;	
		
		
		//virtual bool			IsAltKeyUsed(WPARAM wParam);
        virtual void            InputCancelAll() = 0;
		virtual bool			KeyDown(int theKey) = 0;
		virtual bool			DebugKeyDown(int theKey) = 0;	
		virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown) = 0;
		virtual bool			Is3DAccelerated() = 0;
		virtual bool			Is3DAccelerationSupported() = 0;
		virtual bool			Is3DAccelerationRecommended() = 0;
		virtual void			Set3DAcclerated(bool is3D, bool reinit = true) = 0;
        
        virtual bool            IsUIOrientationAllowed(UI_ORIENTATION theOrientation) { return true; }
		virtual UI_ORIENTATION  GetUIOrientation() { return UI_ORIENTATION_LANDSCAPE_LEFT; }
        
        virtual std::string     GetDeviceName() = 0;
        
		virtual bool			IsSystemUIShowing(){ return false; };

        //for devices which use onscreen keyboards
        virtual void            ShowKeyboard() = 0;
        virtual void            ShowPhoneNumKeyboard() = 0;
		virtual bool 			isOppoFullScreen() = 0;
		virtual int 			CalcOppoFullScreenOffset() = 0;
        virtual void            ShowEmailKeyboard() = 0;
        virtual void            HideKeyboard() = 0;
        virtual bool			IsKeyboardShowing() = 0;

        virtual void 			Vibrate(long long milliseconds){}        
        virtual void 			VibrateWithPattern(long long pattern[], int isRepeat){}
        virtual void 			CancelVibrate(){}

		virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName) = 0;
		
		// Resource access methods
		virtual bool			ReloadAllResources() = 0;
		
		
		//sort of need these in the driver, but I'd like to remove the idea of a registry...
		// Registry access methods
		virtual bool			ConfigGetSubKeys(const std::string& theKeyName, StringVector* theSubKeys) = 0;
		virtual bool			ConfigReadString(const std::string& theValueName, std::string* theString) = 0;
		virtual bool			ConfigReadString(const std::string& theValueName, std::wstring* theString) = 0;
		virtual bool			ConfigReadInteger(const std::string& theValueName, int* theValue) = 0;
		virtual bool			ConfigReadBoolean(const std::string& theValueName, bool* theValue) = 0;
		virtual bool			ConfigReadData(const std::string& theValueName, uchar* theValue, ulong* theLength) = 0;
		virtual bool			ConfigWriteString(const std::string& theValueName, const std::string& theString) = 0;
		virtual bool			ConfigWriteString(const std::string& theValueName, const std::wstring& theString) = 0;
		virtual bool			ConfigWriteInteger(const std::string& theValueName, int theValue) = 0;
		virtual bool			ConfigWriteBoolean(const std::string& theValueName, bool theValue) = 0;
		virtual bool			ConfigWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength) = 0;	
		virtual bool			ConfigEraseKey(const SexyString& theKeyName) = 0;
		virtual void			ConfigEraseValue(const SexyString& theValueName) = 0;
		
		// hooks to store driver specific values in the "registry"
		virtual void			ReadFromConfig() {}
		virtual void			WriteToConfig() {}
		
		// File access methods
		virtual bool			WriteBufferToFile(const std::string& theFilePath, const Buffer* theBuffer) = 0;
		virtual bool			ReadBufferFromFile(const std::string& theFilePath, Buffer* theBuffer, bool dontWriteToDemo = false) = 0;
		virtual bool			WriteBytesToFile(const std::string& theFilePath, const void *theData, unsigned long theDataLen) = 0;
		virtual bool			WriteBytesToFileAt(const std::string& theFilePath, const void *theData, unsigned long theDataLen, unsigned long theSeekPos) = 0;
		virtual bool			WriteBytesToFileEnd(const std::string& theFilePath, const void *theData, unsigned long theDataLen) = 0;
		virtual bool			CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen) = 0;
        virtual bool            CopyFile(const std::string& theFromFilePath, const std::string& theToFileName) = 0;
		virtual bool            RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath) = 0;
        
		// Optimization opportunities for PrimeDrivers
		// GetOptimizedImage lets a driver intercept SexyAppBase's GetImage call and load an image itself
		virtual DeviceImage*	GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps) = 0;
		virtual DeviceImage*	GetOptimizedImage(ImageLib::Image *inSrcImage, bool inCommitBits, bool inAllowTriReps, bool inShouldDeleteSrcImage = true) = 0;
		
		// Returns true if the application should not update the WidgetManager. For instance, if it is
		// minimized (Windows/Mac) or rotating orientation (iPhone)
		virtual bool			ShouldPauseUpdates() = 0;
		
#ifdef SUPPORT_AUTOREFLECTION
		virtual Reflection::CRefSymbolDb* GetAutoReflection() = 0;
#endif
        
#ifdef PRIME_FOR_BEJBLITZ
        virtual int             GetProductVersionCode() { return -1; }
        virtual std::string     GetProductVersionName() { return std::string(""); }
        virtual std::string     GetPackageName() { return std::string(""); }
#endif        
		
		/**
		 * iOS UIApplicationDelegate application:WillResignActive
		 * Android: Activity.onPause
		 */
		Event0 ApplicationWillResignActive;

		/**
		 * iOS ApplicationDidBecomeActive
		 * Android: Activity.onResume
		 */
		Event0 ApplicationDidBecomeActive;

		/**
		 * iOS: UIApplicationDelegate application:DidEnterBackground
		 * Android: Activity.onStop
		 */
		Event0 ApplicationDidEnterBackground;

		/**
		 * iOS: UIApplicationDelegate application:WillBecomeForeground
		 * Android: Activity.onStart
		 */
		Event0 ApplicationWillBecomeForeground;
	};


};
#endif
