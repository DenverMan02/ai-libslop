#pragma once
#ifndef WINDOWSAPPDRIVER_H_INCLUDED
#define WINDOWSAPPDRIVER_H_INCLUDED

///for now the app driver is going to look a lot like sexyappbase
#include "IAppDriver.h"
#include "drivers/app/windows/WindowsSEHCatcher.h"

namespace Sexy
{

	class WindowsGraphicsDriver;

	class WindowsAppDriver : public IAppDriver
	{
	private:
		SexyAppBase* mApp;
		WindowsGraphicsDriver* mWindowsGraphicsDriver;
	public:
		WindowsSEHCatcher* mSEHCatcher;

		WindowsAppDriver(SexyAppBase* base);	
		virtual ~WindowsAppDriver();

		bool InitAppDriver();

	public:	
		bool					ProcessMessages();
		bool					ProcessDeferredMessages(bool singleMessage);
		void					UpdateFTimeAcc();
		virtual bool			Process(bool allowSleep = true);		
		virtual bool			DoUpdateFrames();
		virtual void			DoUpdateFramesF(float theFrac);
		virtual void			MakeWindow();
		virtual void			EnforceCursor();
		void					Remove3DData(MemoryImage* theMemoryImage);
		
		// Loading thread methods	
		static void				LoadingThreadProcStub(void *theArg);	

		// Cursor thread methods
		void					CursorThreadProc();
		static void				CursorThreadProcStub(void *theArg);
		void					StartCursorThread();
		
		void					WaitForLoadingThread();				
		void					RestoreScreenResolution();
		void					DoExit(int theCode);

		void					TakeScreenshot();
		void					DumpProgramInfo();	
		void					ShowMemoryUsage();	
	    int						GetFPS();
		MEMORYSTATUSEX			GetMemStatus();
		uint64					GetMemoryUsed();
		uint64					GetMemoryAvailable();

		// Registry helpers
		bool					ConfigRead(const std::string& theValueName, ulong* theType, uchar* theValue, ulong* theLength);
		bool					RegistryReadKey(const std::string& theValueName, ulong* theType, uchar* theValue, ulong* theLength, HKEY theMainKey = HKEY_CURRENT_USER);
		bool					ConfigWrite(const std::string& theValueName, ulong theType, const uchar* theValue, ulong theLength);

	public:

		// Public methods
		virtual void			BeginPopup();
		virtual void			EndPopup();
		virtual int				MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MB_OK);
		virtual int				MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MB_OK);
		virtual void			Popup(const std::string& theString);
		virtual void			Popup(const std::wstring& theString);
		virtual void			LogScreenSaverError(const std::string &theError);

		virtual bool			OpenURL(const std::string& theURL, bool shutdownOnOpen = false);	
		virtual std::string		GetProductVersion(const std::string& thePath);	

		virtual void			SEHOccured() override;
		virtual std::string		GetGameSEHInfo();
		virtual void			GetSEHWebParams(DefinesMap* theDefinesMap) override;

		virtual void			Shutdown();	

		virtual void			DoParseCmdLine();
		virtual void			ParseCmdLine(const std::string& theCmdLine);
		virtual void			HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);
		virtual void			HandleNotifyGameMessage(int theType, int theParam); // for HWND_BROADCAST of mNotifyGameMessage (0-1000 are reserved for SexyAppBase for theType)
		virtual void			HandleGameAlreadyRunning(); 

		virtual void			Start();	
		virtual void			Init();	

		void					StartLoadingThread();
		virtual double			GetLoadingThreadProgress();	

		void					CopyToClipboard(const std::string& theString);
		std::string				GetClipboard();

		void					SetCursor(int theCursorNum);
		int						GetCursor();
		void					EnableCustomCursors(bool enabled);	
		
		void					SetCursorImage(int theCursorNum, Image* theImage);

		virtual void			SwitchScreenMode();
		virtual void			SwitchScreenMode(bool wantWindowed);
		virtual void			SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);	
		

		virtual bool			IsAltKeyUsed(WPARAM wParam);
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

		virtual std::string     GetDeviceName() { return "Windows"; }
        virtual void            ShowKeyboard() {}
		virtual bool 			isOppoFullScreen() { return false; }
		virtual int 			CalcOppoFullScreenOffset() { return 0; }
        virtual void            HideKeyboard() {}
		virtual void            ShowPhoneNumKeyboard() {}
		virtual void            ShowEmailKeyboard()	   {}
		virtual bool			IsKeyboardShowing() { return false; }

		virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
		virtual bool			DrawDirtyStuff();
		virtual void			Redraw(Rect* theClipRect);

		// Resource access methods
		//void					ReloadAllResources_DrawStateUpdate(const std::string& theHeader, const std::string& theSubText, float thePct);
		//virtual void			ReloadAllResourcesProc();
		//static void			ReloadAllResourcesProcStub(void* theArg);
		bool					ReloadAllResources();
		
		
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
		virtual bool			ConfigWriteInteger(const std::string& theValueName, int theValue) ;
		virtual bool			ConfigWriteBoolean(const std::string& theValueName, bool theValue);
		virtual bool			ConfigWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength);	
		virtual bool			ConfigEraseKey(const SexyString& theKeyName);
		virtual void			ConfigEraseValue(const SexyString& theValueName);

		// File access methods
		bool					WriteBufferToFile(const std::string& theFileName, const Buffer* theBuffer);
		bool					ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);//UNICODE
		bool					WriteBytesToFile(const std::string& theFileName, const void *theData, unsigned long theDataLen);
		bool					WriteBytesToFileAt(const std::string& theFilePath, const void *theData, unsigned long theDataLen, unsigned long theSeekPos);
		bool					WriteBytesToFileEnd(const std::string& theFilePath, const void *theData, unsigned long theDataLen);
		bool					CreateFileOfSize(const std::string& theFilePath, unsigned long theDataLen);
        bool					CopyFile(const std::string& theFromFilePath, const std::string& theToFileName);
		bool					RenameFile(const std::string& theFromFilePath, const std::string& theToFilePath);
        
		// Misc methods
		virtual void			DoMainLoop();
		virtual bool			UpdateAppStep(bool* updated);
		int						InitGraphicsInterface();
		void					ClearUpdateBacklog(bool relaxForASecond = false);
		bool					IsScreenSaver();
		virtual bool			AppCanRestore();
		static LRESULT CALLBACK	WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		
		virtual bool			OverrideWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* theResult);

		void					RehupFocus();
		void					ClearKeysDown();

		DeviceImage*			GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		DeviceImage*			GetOptimizedImage(ImageLib::Image *inSrcImage, bool inCommitBits, bool inAllowTriReps, bool inShouldDeleteSrcImage = true) { return NULL; };
		
		bool					ShouldPauseUpdates() { return mApp->mMinimized; }

	#ifdef SUPPORT_AUTOREFLECTION
		Reflection::CRefSymbolDb* GetAutoReflection();
	#endif

		static bool ScreenSaverWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT &theResult);

		//PVZ2_CHINESE CJD_RSG3
		virtual void  InputCancelAll()  {};

	};

}; //namespace
#endif //__SEXYAPPBASE_H__
