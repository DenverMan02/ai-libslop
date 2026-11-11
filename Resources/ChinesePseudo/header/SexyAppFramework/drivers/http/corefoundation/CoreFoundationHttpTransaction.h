#ifndef COREFOUNDATIONHTTPTRANSACTION_H_INCLUDED
#define COREFOUNDATIONHTTPTRANSACTION_H_INCLUDED
#include "Common.h"
#include "IHttpDriver.h"
#ifdef HOST_IPHONEOS
#include <CoreFoundation/CoreFoundation.h>
#include <CFNetwork/CFNetwork.h>
#elif defined HOST_MACOSX
#include <CoreServices/CoreServices.h>
#endif

namespace Sexy
{
	class CoreFoundationHttpTransaction
    : public IHttpTransaction
	{
	public:
		CoreFoundationHttpTransaction( const std::string& method, const std::string& url, uint32 inResponseBufferSize);
		
		void SetListener( IHttpListener* listener );
		void SetUserData( void* userData );
		void SetRequestHeader( const std::string& name, const std::string& value );
		void SetRequestBody( const void* data, size_t length );
		void SetResponseBuffer( void* buffer, size_t bufferSize );
		void SetTimeout( int seconds );
		void SetSlackCertificateValidation( bool slack );
		void SetBasicAuth( const std::string& username, const std::string& password );
		
		void Start();
		void Release();
		
		std::string GetRequestUrl();
		void* GetUserData();
		int GetStatusCode();
		std::string GetStatusLine();
		int GetResponseLength();
		std::string GetResponseHeader( const std::string& key );
		
		std::string GetSerializedRequest();
		std::string GetErrorMessage();

		int GetErrorCode();
		
	protected:
        
		~CoreFoundationHttpTransaction();
		
		static void ReadStreamCallBackStub( CFReadStreamRef stream, CFStreamEventType type, void* clientCallBackInfo );
		void ReadStreamCallBack( CFReadStreamRef stream, CFStreamEventType type );
		void ResetWatchdogTimer();
		static void TimerCallBackStub( CFRunLoopTimerRef timer, void* info );
		void TimerCallBack( CFRunLoopTimerRef timer );
		void StoreError( CFErrorRef error );
		void CloseReadStream();
		void CreateResponseBuffer();
		void ReleaseResponseBuffer();
		void GetResponseHeadersFromStream();
		
        IHttpListener* mListener;
		void* mUserData;
		bool mSlackCertificateValidation;
		CFHTTPMessageRef mRequest;
		CFHTTPMessageRef mResponse;
		CFReadStreamRef mReadStream;
		CFErrorRef mError;
		CFRunLoopTimerRef mWatchdogTimer;
		CFTimeInterval mWatchdogTimeout;
		UInt8* mResponseBuffer;
		UInt8* mResponseBufferLocal;
		size_t mResponseBufferSize;
	};
	
}

#endif


