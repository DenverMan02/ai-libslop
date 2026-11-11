#pragma once
#ifndef PS3APPDRIVER_H_INCLUDED
#define PS3APPDRIVER_H_INCLUDED

#include "IAppDriver.h"
#include "Dialog.h"

namespace Sexy
{
	class PS3GraphicsDriver;

	class PS3AppDriver  : public IAppDriver, public Sexy::DialogListener
	{
	public:
		static bool gExitRequested;

		PS3AppDriver(SexyAppBase*);
		virtual ~PS3AppDriver();
		
		virtual bool InitAppDriver();
		
		virtual void Start();	
		virtual void Init();
		virtual void InitPreAppLaunch();
		virtual void InitPostAppLaunch();
		virtual void InitWindowCreated();
		virtual bool UpdateAppStep(bool* updated);
		virtual void ClearUpdateBacklog(bool relaxForASecond = false);
		virtual void Shutdown();	
		virtual void DoExit(int theCode);
		
		bool IsFullVersion(){return true;};
		bool IsSystemUIShowing() override;
		virtual void Remove3DData(MemoryImage* theMemoryImage);

		bool CheckAvailableHDDSpace();//THIS CAN ONLY BE CALLED ON A SUB THREAD
		bool InsufficientStorage() { return mInsufficientStorage;}

		static void OutputMemoryUsage( const std::string& dbgHint );
	public:
		
		// Public methods
		virtual void BeginPopup();
		virtual void EndPopup();
		virtual int MsgBox(const std::string &theText, const std::string &theTitle = "Message", int theFlags = MB_OK);
		virtual int MsgBox(const std::wstring &theText, const std::wstring &theTitle = L"Message", int theFlags = MB_OK);
		virtual void Popup(const std::string& theString);
		virtual void Popup(const std::wstring& theString);
		
		virtual bool OpenURL(const std::string& theURL, bool shutdownOnOpen = false);	
		
		virtual std::string GetGameSEHInfo();
		
		virtual void DoParseCmdLine();
		virtual void ParseCmdLine(const std::string& theCmdLine);
		virtual void HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);
		
		virtual void StartLoadingThread();
		virtual double GetLoadingThreadProgress();	
		
		virtual void CopyToClipboard(const std::string& theString);
		virtual std::string GetClipboard();
		
		virtual void SetCursor(int theCursorNum);
		virtual int GetCursor();
		virtual void EnableCustomCursors(bool enabled);	
		
		virtual void SetCursorImage(int theCursorNum, Image* theImage);
		
		
		virtual void SwitchScreenMode();
		virtual void SwitchScreenMode(bool wantWindowed);
		virtual void SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);	
		
		
		//virtual bool IsAltKeyUsed(WPARAM wParam);
		virtual bool KeyDown(int theKey);
		virtual bool DebugKeyDown(int theKey);	
		virtual bool DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		virtual bool Is3DAccelerated();
		virtual bool Is3DAccelerationSupported();
		virtual bool Is3DAccelerationRecommended();
		virtual void Set3DAcclerated(bool is3D, bool reinit = true);	
        virtual void            ShowKeyboard() {}
        virtual void            HideKeyboard() {}
		
		virtual bool CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
		
		// Resource access methods
		virtual bool ReloadAllResources();
		
		
		//sort of need these in the driver, but I'd like to remove the idea of a registry...
		// Registry access methods
		virtual bool ConfigGetSubKeys(const std::string& theKeyName, StringVector* theSubKeys);
		virtual bool ConfigReadString(const std::string& theValueName, std::string* theString);
		virtual bool ConfigReadString(const std::string& theValueName, std::wstring* theString);
		virtual bool ConfigReadInteger(const std::string& theValueName, int* theValue);
		virtual bool ConfigReadBoolean(const std::string& theValueName, bool* theValue);
		virtual bool ConfigReadData(const std::string& theValueName, uchar* theValue, ulong* theLength);
		virtual bool ConfigWriteString(const std::string& theValueName, const std::string& theString);
		virtual bool ConfigWriteString(const std::string& theValueName, const std::wstring& theString);
		virtual bool ConfigWriteInteger(const std::string& theValueName, int theValue);
		virtual bool ConfigWriteBoolean(const std::string& theValueName, bool theValue);
		virtual bool ConfigWriteData(const std::string& theValueName, const uchar* theValue, ulong theLength);
		virtual bool ConfigEraseKey(const SexyString& theKeyName);
		virtual void ConfigEraseValue(const SexyString& theValueName);

		// File access methods
		virtual bool WriteBufferToFile(const std::string& theFileName, const Buffer* theBuffer);
		virtual bool ReadBufferFromFile(const std::string& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);
		virtual bool WriteBytesToFile(const std::string& theFileName, const void *theData, unsigned long theDataLen);

		virtual DeviceImage* GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);

		virtual bool ShouldPauseUpdates();

		bool HasMouse();
		void GetSysMousePosition(int& x, int& y);
	public:
		static void SysutilCallback( uint64_t status, uint64_t param, void *userData );

	protected:
		void HandleMouse();
		void InitMouse();

		void HandleKeyboard();

		bool Process(bool allowSleep=true);
		void UpdateFTimeAcc();
		
		void DoUpdateFramesF(float theFrac);
		bool DoUpdateFrames();
		
		bool DrawDirtyStuff(bool force);
		void Redraw();

		static void LoadingThreadProcStub(void *param);
	public:
		SexyAppBase* mApp;
		PS3GraphicsDriver* mPS3GraphicsDriver;

	private:
		friend class PS3ProfileDriver;
		friend class PS3ProfileData;
		friend class PS3LeaderboardDriver;
		friend class PS3LeaderboardWriteContext;
		friend class PS3LeaderboardReadContext;
		friend class PS3SaveGameDriver;
		friend class PS3SaveGameContext;

		bool DoModalRetryDialog( const SexyString& title, const SexyString& text, const SexyString& footer, int buttons = Dialog::BUTTONS_OK_CANCEL );

	private:
		static const int NUM_MOUSE_BUTTONS = 3;
		int m_mouse_x;
		int m_mouse_y;
		bool m_mouse_buttons[NUM_MOUSE_BUTTONS];
		bool m_has_mouse;
		uint8 m_mouse_button_masks[NUM_MOUSE_BUTTONS];


		bool mSysUIShowing;
		bool mInsufficientStorage;

		//Debug Drawing
		bool mDebugOverlayRSB;
	};
};
#endif
