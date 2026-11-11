#pragma once
#ifndef __WINRT_APP_DRIVER__
#define __WINRT_APP_DRIVER__

#include "IAppDriver.h"
#include "Dialog.h"

namespace Sexy
{

class Dx11GraphicsDriver;
struct Touch;

class WinRTAppDriver  : public IAppDriver, public Sexy::DialogListener
{
public:
	WinRTAppDriver(SexyAppBase*);
	virtual ~WinRTAppDriver();
   
	class PointerDevice	  
	{
	public:
		enum
		{
			POINTER_LBUTTON  = (1<<0),
			POINTER_RBUTTON  = (1<<1), 
			POINTER_MBUTTON	 = (1<<2), 
			POINTER_XBUTTON1 = (1<<3), 
			POINTER_XBUTTON2 = (1<<4), 
		} POINTER_BUTTON_TYPES;

		PointerDevice()
		{
			m_nPosX = m_nPosY = 0;
			m_nWheelDelta = 0;
			m_nButtonsPressed = 0;
		}

		void GetState(int &nX, int &nY, int &nButtonsPressed, int &nWheelDelta)
		{
			nX = m_nPosX;
			nY = m_nPosY;
			nButtonsPressed = m_nButtonsPressed;
			nWheelDelta = m_nWheelDelta;
		}

		void SetPosition(int nX, int nY)		{ m_nPosX = nX; m_nPosY = nY; }
		void SetButtons(int nButtonsPressed)	{ m_nButtonsPressed = nButtonsPressed; };
		void SetWheelDelta(int nWheelDelta)		{ m_nWheelDelta = nWheelDelta; };
		
	private:
		int m_nPosX, m_nPosY;
		int m_nWheelDelta;
		int m_nButtonsPressed;
	};

	class KeyPress
	{
	public:
		enum
		{
			KEYPRESS_KEYDOWN = 	(1<<0),
			KEYPRESS_KEYUP = 		(1<<1),
			KEYPRESS_REPEAT  = 	(1<<2)
		} KEYPRESS_TYPES;

		int nVirtualKey;
		int nFlags;
	};
	typedef std::vector<KeyPress> KeyPressList;
	 
	virtual bool			InitAppDriver();
	
	virtual void			Start();	
	virtual void			Init();	//this is effectively empty for Mac, b/c SexyAppRun reorders initiazation from the SexyApplicationDelegate
	virtual void			InitPreAppLaunch();
	virtual void			InitPostAppLaunch();
	
	
	virtual bool			IsSystemUIShowing() override;
	virtual void			InitWindowCreated();
	virtual bool			UpdateAppStep(bool* updated);
	virtual void			ClearUpdateBacklog(bool relaxForASecond = false);
	virtual void			Shutdown();	
	virtual void			DoExit(int theCode);
	
	bool					IsFullVersion();
	bool					CheckFullVersion( bool fromInit );
	void					OnFullVersionChange();

	void					HandleSystemNotification( const DWORD &id, const ULONG_PTR param );


	virtual void			Remove3DData(MemoryImage* theMemoryImage);

	static void OutputMemoryUsage( const std::string& dbgHint );
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
	void CalcHIDPosition(int theX, int theY, int &outX, int &outY);

	void HandleMouse();
	void HandleTouch();
	void InitMouse();
	Touch *FindTouch( Touch *pTouch);
	bool DeleteTouch( Touch *pTouch);

	void HandleKeyboard();

	bool Process(bool allowSleep=true);
	void UpdateFTimeAcc();
	
	void DoUpdateFramesF(float theFrac);
	bool DoUpdateFrames();
	
	bool DrawDirtyStuff(bool force);
	void Redraw();

	static void LoadingThreadProcStub(void *param);

public:
	SexyAppBase*	mApp;
	Dx11GraphicsDriver* mGraphicsDriver;

	void SetWindowSize();
			
	PointerDevice *GetPointer(int nPointerID) 	{ return &m_aPointer[nPointerID]; }
	bool		IsTouchEnabled()				{ return m_bTouchEnabled; }
	
	// Touch Support
	bool		m_bTouchEnabled;
	bool        m_bUseMultitouch;
	bool        m_bHasSingleTouch;
	Touch     	m_pCurSingleTouch;
	TouchList	m_aDeferredTouchList;		// WinRT callback fills this in...  It is flushed by the AppDriver
	TouchList	m_aTouchList;	 
	CritSect	m_aTouchMutex;   
		
	// Keyboard Support
	CritSect	m_aKeyPressMutex;   
	KeyPressList m_aDeferredKeyPressList; 	// WinRT callback fills this in...  It is flushed by the AppDriver
					
private:
	friend class WinRTDesktopSaveGameDriver;
	friend class WinRTDesktopSaveGameContext;
	friend class WinRTDesktopLeaderboardDriver;
	friend class WinRTDesktopLeaderboardReadContext;
	friend class WinRTDesktopLeaderboardWriteContext;
	friend class WinRTDesktopProfileDriver;
	friend class WinRTDesktopProfileData;

	bool DoModalRetryDialog( const SexyString& title, const SexyString& text, const SexyString& footer, int buttons = Dialog::BUTTONS_OK_CANCEL );

private:
	static const int MAX_POINTERS = 1;
	int 	m_mouse_x;
	int 	m_mouse_y;
	bool 	m_mouse_buttons[5];
	bool 	m_has_mouse;
	DWORD 	m_mouse_button_masks[5];		

	HANDLE 	mNotificationHandle;
	bool 	mIsFullVersion;
	bool 	mSysUIShowing;

	PointerDevice	m_aPointer[MAX_POINTERS];	// Pointing device (i.e., mouse)

	//Debug Drawing
	bool mDebugOverlayRSB;
};

};
#endif

