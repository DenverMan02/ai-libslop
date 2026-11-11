#ifndef __WININETHTTPTRANSFER_H__
#define __WININETHTTPTRANSFER_H__

#include "Common.h"

#ifdef SUPPORT_WININET
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <vector>
#include "CritSect.h"
#include "Buffer.h"

namespace Sexy
{
	class WinInetHTTPTransfer
	{
	public:
		enum EResult
		{
			RESULT_DONE,
			RESULT_NOT_STARTED,
			RESULT_NOT_COMPLETED,
			RESULT_NOT_FOUND,
			RESULT_HTTP_ERROR,
			RESULT_HTTP_REDIRECT,
			RESULT_ABORTED,
			RESULT_SOCKET_ERROR,
			RESULT_INVALID_ADDR,
			RESULT_CONNECT_FAIL,
			RESULT_DISCONNECTED,
			RESULT_INTERNAL_ERROR
		};


	public:
		WinInetHTTPTransfer(void);
		WinInetHTTPTransfer(const WinInetHTTPTransfer& rhs);
		WinInetHTTPTransfer& operator=(const WinInetHTTPTransfer& rhs);
		virtual ~WinInetHTTPTransfer(void);

		bool					SetOutputFile(const std::string& theFileName);
		bool					SetOutputFile(const std::wstring& theFileName);

		void					Get(const std::string& theURL, bool isBinary=false);
		void					Get(const std::string& theBaseURL, const std::string& theRelURL, bool isBinary=false);

		void					Post(const std::string& theURL, const std::string& theParams);
		void					Post(const std::string& theBaseURL, const std::string& theRelURL, const std::string& theParams);
		void					PostMultiPart(const std::string& theURL, const std::string& theParams, const std::string& theSeparator);
		void					PostMultiPart(const std::string& theBaseURL, const std::string& theRelURL, const std::string& theParams, const std::string& theSeparator);

		void					Reset();
		void					Abort();
		void					WaitFor();
		EResult					GetResultCode() const { return mResult; }
		std::string				GetContent();
		bool					GetContentBinary(Buffer& outContent);

		static void				TransferThreadProcStub(void* theParameter);

	protected:
		std::string				GetAbsURL(const std::string& theBaseURL, const std::string& theRelURL);
		void					GetHelper(const std::string& theURL);
		void					PostHelper(const std::string& theURL, const std::string& theParams, const char* theSeparator);
		void					PrepareTransfer(const std::string& theURL);
		void					StartTransfer();
		void					TransferThreadProc();
		void					Fail(EResult theResult);

	private:
		std::string				mSpecifiedBaseURL;
		std::string				mSpecifiedRelURL;
		std::string				mURL;

		std::string				mProto;
		std::string				mUserName;
		std::string				mUserPass;
		std::string				mHost;	
		int						mPort;	
		std::string				mPath;
		std::string				mAction;
		std::string				mUserAgent;
		std::string				mPostContentType;
		std::string				mPostData;

		FILE*					mFP;
		bool					mUsingFile;
		bool					mGetIsBinary;

		std::string				mContent;
		int						mContentLength;
		int						mCurContentLength;
		Buffer					mContentBinary;

		bool					mTransferPending;
		bool					mThreadRunning;	
		bool					mExiting;
		bool					mAborted;
		EResult					mResult;

		CritSect		        mFileCritSection;
	};
}
#endif
#endif // #ifndef __WININETHTTPTRANSFER_H__
