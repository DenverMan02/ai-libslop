#pragma once
#ifndef WIIAPPDRIVER_H_INCLUDED
#define WIIAPPDRIVER_H_INCLUDED

#include "IAppDriver.h"

#include "SexyAppBase.h"

namespace Sexy
{
	
	class WiiGraphicsDriver;

	class WiiAppDriver  : public IAppDriver
	{
	public:
		WiiAppDriver(SexyAppBase*);
		virtual ~WiiAppDriver();
		
		virtual bool			InitAppDriver();
		
		
		virtual void			Start();	
		virtual void			Init();	//this is effectively empty for Mac, b/c SexyAppRun reorders initiazation from the SexyApplicationDelegate
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
		virtual bool			KeyDown(int theKey);
		virtual bool			DebugKeyDown(int theKey);	
		virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		virtual bool			Is3DAccelerated();
		virtual bool			Is3DAccelerationSupported();
		virtual bool			Is3DAccelerationRecommended();
		virtual void			Set3DAcclerated(bool is3D, bool reinit = true);	
		
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
		
		// File access methods
		virtual bool			WriteBufferToFile(const std::string& theFileName, const Buffer* theBuffer);
		virtual bool			ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);
		virtual bool			WriteBytesToFile(const std::string& theFileName, const void *theData, unsigned long theDataLen);
		
		virtual DeviceImage*	GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);
		
		virtual bool			ShouldPauseUpdates();

        virtual void            ShowKeyboard() {}
        virtual void            HideKeyboard() {}

		bool HasMouse();
		void GetSysMousePosition(int& x, int& y);
	protected:
		void HandleMouse();
		void InitMouse();

		bool Process(bool allowSleep=true);
		void UpdateFTimeAcc();
		
		void DoUpdateFramesF(float theFrac);
		bool DoUpdateFrames();
		
		bool DrawDirtyStuff(bool force);
		void Redraw();

		static void LoadingThreadProcStub(void *param);
	public:
		SexyAppBase*	mApp;
		WiiGraphicsDriver* mWiiGraphicsDriver;
		
	public:
		typedef std::vector<WiiThreadInfo *> WiiThreadVector;
		WiiThreadVector mActiveThreads;

	private:
		int m_mouse_x;
		int m_mouse_y;
		bool m_mouse_buttons[5];
		bool m_has_mouse;
		u8 m_mouse_button_masks[5];
	};
	
	
};
#endif

