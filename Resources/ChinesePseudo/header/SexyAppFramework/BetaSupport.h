#ifndef __BETASUPPORT_H__
#define __BETASUPPORT_H__

#include "Common.h"

#ifdef SUPPORT_BETA_SUPPORT

#include "Buffer.h"
#include "WinInetHTTPTransfer.h"

namespace Sexy
{

class SexyApp;

typedef std::map<std::string, Buffer> StringToBufferMap;

class BetaSupport
{
public:
	class DataLogEntry
	{
	public:
		Buffer mBuffer;
		std::string mFileName;
		std::string mFileExt;

		DataLogEntry(const Buffer& theBuffer, const std::string& theFileName, const std::string& theFileExt)
		: mBuffer(theBuffer), mFileName(theFileName), mFileExt(theFileExt)
		{}
	};
	typedef std::map<std::string, DataLogEntry> StringToDataLogEntryMap;

	SexyApp*				mApp;
	HFONT					mDialogFont;
	HFONT					mItalicsFont;
	HFONT					mBoldFont;

	int						mPeriodCount;
	HWND					mHWnd;
	HWND					mTextHWnd;
	HWND					mNameHWnd;
	HWND					mPasswordHWnd;

	WinInetHTTPTransfer		mWinInetHTTPTransfer;

	bool					mAborted;
	bool					mDialogClosed;
	std::string				mBetaCommentURL;
	std::string				mDemoUploadFile;

	std::string				mName;
	std::string				mPassword;
	bool					mValidated;

	StringToDataLogEntryMap	mDataLogs;

protected:
	void					PositionDialog(HWND theWindow);
	void					WaitForDialogClose();

	static LRESULT CALLBACK	ValidateWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	
	static LRESULT CALLBACK	LoginWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK	SubmitWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	std::string				GetBetaSiteDomainName();
	bool					GetLoginInfo();
	bool					ValidateWithServer();

	void					ReadFromRegistry();
	void					WriteToRegistry();
		
	void					SubmitDemoBufferThread();
	static void				SubmitDemoBufferThreadStub(void *theArg);
	bool					SubmitDemoBuffer();

public:
	BetaSupport(SexyApp* theApp);
	virtual ~BetaSupport();
		
	bool					Validate();
	bool					RequestDemoUpload(const char *theFilePath = NULL);
	bool					RequestComments();
	void					StoreDataLog(const std::string& theName, const Buffer& theBuffer, const char* optServerFileName = NULL, const char* optServerFileExtension = NULL);
};

}

#endif //#ifdef SUPPORT_BETA_SUPPORT
#endif //__BETASUPPORT_H__
