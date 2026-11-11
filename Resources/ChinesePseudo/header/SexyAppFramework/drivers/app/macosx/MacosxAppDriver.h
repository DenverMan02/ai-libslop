#pragma once
#ifndef MACOSXAPPDRIVER_H_INCLUDED
#define MACOSXAPPDRIVER_H_INCLUDED

#include "IAppDriver.h"
#include <CoreFoundation/CFMachPort.h>
#include <CoreFoundation/CoreFoundation.h>

namespace Sexy
{
	class MacosxGraphicsDriver;

	class MacosxAppDriver  : public IAppDriver
	{
	public:
		MacosxAppDriver(SexyAppBase*);
		virtual ~MacosxAppDriver();
		
		virtual bool			InitAppDriver();
		
		
		virtual void			Init();
		virtual void			Start();	
		
		virtual void			MakeWindow();
		virtual void			InitGraphicsInterface();
		virtual bool			UpdateAppStep(bool* updated);
		virtual void			ClearUpdateBacklog(bool relaxForASecond = false);
		virtual void			Shutdown();	
		virtual void			DoExit(int theCode);
		
		
		virtual void			Remove3DData(MemoryImage* theMemoryImage);
	public:
		
		// Public methods
		virtual void			BeginPopup();
		virtual void			EndPopup();
		
		virtual bool			MacOpenFileBox(std::string& theResult, int theFlags);
		virtual bool			MacSaveFileBox(std::string& theResult, int theFlags);
		
		virtual int				MacMsgBox(const SexyString& theText, const SexyString& theTitle, int theFlags = MSGBOX_OK);
		virtual int				MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MSGBOX_OK);
		virtual int				MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MSGBOX_OK);
		virtual void			Popup(const std::string& theString);
		virtual void			Popup(const std::wstring& theString);
#   if (PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED) && IS_SUPPORT_REPORTING_DEFINED
        virtual int             ReportingPopup(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC);
        virtual int             ReportingPopup(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MSGBOX_OK, ReportDisplayType i_displayType = RPT_DISPLAY_BASIC);
#   endif
		
		
		virtual bool			OpenURL(const std::string& theURL, bool shutdownOnOpen = false);	
		
		
		virtual std::string		GetGameSEHInfo();
		
		
		
		virtual void			DoParseCmdLine();
		virtual void			ParseCmdLine(const std::string& theCmdLine);
		virtual void			HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);
		
		int                     GetFPS();
        uint64                  GetMemoryUsed();
        uint64                  GetMemoryAvailable(); 
		
		
		
		
		virtual void			StartLoadingThread();
		virtual double			GetLoadingThreadProgress();	
		virtual void			WaitForLoadingThread();
		
		virtual void			CopyToClipboard(const std::string& theString);
		virtual std::string		GetClipboard();
		
		virtual void			SetCursor(int theCursorNum);
		virtual int				GetCursor();
		virtual void			EnableCustomCursors(bool enabled);	
		
		virtual void			SetCursorImage(int theCursorNum, Image* theImage);
		
		
		virtual void			SwitchScreenMode();
		virtual void			SwitchScreenMode(bool wantWindowed);
		virtual void			SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);	
        
        
        virtual void            InputCancelAll() {}
		
		//virtual bool			IsAltKeyUsed(WPARAM wParam);
		virtual bool			KeyDown(int theKey);
		virtual bool			DebugKeyDown(int theKey);	
		virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		virtual bool			Is3DAccelerated();
		virtual bool			Is3DAccelerationSupported();
		virtual bool			Is3DAccelerationRecommended();
		virtual void			Set3DAcclerated(bool is3D, bool reinit = true);	

        virtual void            ShowKeyboard() {}
        virtual void            HideKeyboard() {}
        virtual void            ShowPhoneNumKeyboard() {}
        virtual void            ShowEmailKeyboard() {}
        virtual bool			IsKeyboardShowing() { return false; };

		virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
		
		// Resource access methods
		virtual bool			ReloadAllResources();
		
		
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

		virtual void			ReadFromConfig();
		virtual void			WriteToConfig();
		
		// File access methods
		virtual bool			WriteBufferToFile(const std::string& theFileName, const Buffer* theBuffer);
		virtual bool			ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);
		virtual bool			WriteBytesToFile(const std::string& theFileName, const void *theData, unsigned long theDataLen);
        virtual bool			WriteBytesToFileAt(const std::string& theFilePath, const void *theData, unsigned long theDataLen, unsigned long theSeekPos);
		virtual bool			CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen);
        virtual bool            CopyFile(const std::string& theFromFilePath, const std::string& theToFilePath);
        virtual bool            RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath);

		
		virtual DeviceImage*	GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		virtual DeviceImage*	GetOptimizedImage(ImageLib::Image *inSrcImage, bool inCommitBits, bool inAllowTriReps, bool inShouldDeleteSrcImage = true);
        
		virtual bool			ShouldPauseUpdates();
		
		void SysMouseDown(int x, int y, int button);
		void SysMouseUp(int x, int y, int button);
		void SysMouseMove(int x, int y);
		void SysMouseDrag(int x, int y);
		void SysMouseWheel(int theDelta);
		
		void SysKeyDown(int key);
		void SysKeyUp(int key);
		void SysKeyChar(SexyChar theChar);
		
		void RehupFocus();
		
		bool DrawDirtyStuff(bool force);
		void Redraw();
		
		void DoSetCursor(int theCursorNum);
        
        virtual std::string GetDeviceName();
		
	protected:
		void DoMainLoop();
		bool Process(bool allowSleep=true);
		void UpdateFTimeAcc();
		
		void DoUpdateFramesF(float theFrac);
		bool DoUpdateFrames();
		
		bool InitConfig();
		void SyncConfig();
		CFPropertyListRef GetConfigValue(std::string key);

	public:
		SexyAppBase*	mApp;
		uint32			mPreferredScreen;
		void*			mWindow;
		void*			mGLView; //This is the ObjC GlView object kept opaque to pass into OBJInterface functions
		void*			mAppDelegate;
		void*			mImageCursors[NUM_CURSORS];
		MacosxGraphicsDriver* mMacosxGraphicsDriver;
		
		pthread_t m_loading_thread;
		
		bool			mConfigInitted;
		CFStringRef		mConfigId;
		CFArrayRef		mConfigList;
	};
	
	
};
#endif

