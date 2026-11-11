#ifndef WINDOWSHTTPTRANSACTION_H_INCLUDED
#define WINDOWSHTTPTRANSACTION_H_INCLUDED
#pragma once
#include "IHttpDriver.h"
#include "Common.h"
#include <winhttp.h>
#include <queue>

namespace Sexy
{
	class WindowsHttpDriver;

	class WindowsHttpTransaction
		: public IHttpTransaction
	{
	public:
		WindowsHttpTransaction( WindowsHttpDriver* driver, const std::string& method, const std::string& url );

		void SetListener( IHttpListener* listener );
		void SetUserData( void* userData );
		void SetRequestHeader( const std::string& name, const std::string& value );
		void SetRequestBody( const void* data, size_t length );
		void SetResponseBuffer( void* buffer, size_t bufferSize );
		void SetTimeout( int seconds );
		void SetSlackCertificateValidation( bool slack );
		void SetBasicAuth( const std::string& username, const std::string& password ); //PVZ2_CHINESE CJD_RSG3

		void Start();
		void Release();
		void Update();

		std::string GetRequestUrl();
		void* GetUserData();
		int GetStatusCode();
		std::string GetStatusLine();
		int GetResponseLength();
		std::string GetResponseHeader( const std::string& key );

		std::string GetSerializedRequest();
		std::string GetErrorMessage();

		static void CALLBACK StatusCallbackStub( HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength );
		void EnqueueStatusCallback( HINTERNET handle, DWORD status, LPVOID statusInformation, DWORD statusInformationLength );
		void ProcessStatusCallback( HINTERNET handle, DWORD status, LPVOID statusInformation, DWORD statusInformationLength );

	protected:

		~WindowsHttpTransaction();

		void CreateResponseBuffer();
		void ReleaseResponseBuffer();

		void LockStatusCallbackQueue();
		void UnlockStatusCallbackQueue();

		WindowsHttpDriver* mDriver;
		IHttpListener* mListener;
		void* mUserData;
		HINTERNET mConnection;
		HINTERNET mRequest;
		unsigned char* mRequestBody;
		DWORD mRequestBodySize;
		unsigned char* mResponseBuffer;
		unsigned char* mResponseBufferLocal;
		DWORD mResponseBufferSize;
		DWORD mError;

		struct StatusCallbackRecord
		{
			HINTERNET handle;
			DWORD status;
			LPVOID statusInformation;
			DWORD statusInformationLength;
		};

		typedef std::queue< StatusCallbackRecord > StatusCallbackQueue;
		StatusCallbackQueue mStatusCallbackQueue;
		LONG mStatusCallbackQueueLock;

	};
}

#endif
