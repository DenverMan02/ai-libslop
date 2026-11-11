
#pragma once
#ifndef IHTTPDRIVER_H_INCLUDED
#define IHTTPDRIVER_H_INCLUDED

#include "common.h"

#include <string>

namespace Sexy 
{
	class SexyAppBase;
	class IHttpTransaction;
	
	enum HttpStatusCodes
	{
		HTTP_CONTINUE            = 100, // OK to continue with request
		HTTP_SWITCH_PROTOCOLS    = 101, // server has switched protocols in upgrade header

		HTTP_OK                  = 200, // request completed
		HTTP_CREATED             = 201, // object created, reason = new URI
		HTTP_ACCEPTED            = 202, // async completion (TBS)
		HTTP_PARTIAL             = 203, // partial completion
		HTTP_NO_CONTENT          = 204, // no info to return
		HTTP_RESET_CONTENT       = 205, // request completed, but clear form
		HTTP_PARTIAL_CONTENT     = 206, // partial GET fulfilled
		HTTP_WEBDAV_MULTI_STATUS = 207, // WebDAV Multi-Status

		HTTP_AMBIGUOUS           = 300, // server couldn't decide what to return
		HTTP_MOVED               = 301, // object permanently moved
		HTTP_REDIRECT            = 302, // object temporarily moved
		HTTP_REDIRECT_METHOD     = 303, // redirection w/ new access method
		HTTP_NOT_MODIFIED        = 304, // if-modified-since was not modified
		HTTP_USE_PROXY           = 305, // redirection to proxy, location header specifies proxy to use
		HTTP_REDIRECT_KEEP_VERB  = 307, // HTTP/1.1: keep same verb

		HTTP_BAD_REQUEST         = 400, // invalid syntax
		HTTP_DENIED              = 401, // access denied
		HTTP_PAYMENT_REQ         = 402, // payment required
		HTTP_FORBIDDEN           = 403, // request forbidden
		HTTP_NOT_FOUND           = 404, // object not found
		HTTP_BAD_METHOD          = 405, // method is not allowed
		HTTP_NONE_ACCEPTABLE     = 406, // no response acceptable to client found
		HTTP_PROXY_AUTH_REQ      = 407, // proxy authentication required
		HTTP_REQUEST_TIMEOUT     = 408, // server timed out waiting for request
		HTTP_CONFLICT            = 409, // user should resubmit with more info
		HTTP_GONE                = 410, // the resource is no longer available
		HTTP_LENGTH_REQUIRED     = 411, // the server refused to accept request w/o a length
		HTTP_PRECOND_FAILED      = 412, // precondition given in request failed
		HTTP_REQUEST_TOO_LARGE   = 413, // request entity was too large
		HTTP_URI_TOO_LONG        = 414, // request URI too long
		HTTP_UNSUPPORTED_MEDIA   = 415, // unsupported media type
		HTTP_RETRY_WITH          = 449, // retry after doing the appropriate action.

		HTTP_SERVER_ERROR        = 500, // internal server error
		HTTP_NOT_SUPPORTED       = 501, // required not supported
		HTTP_BAD_GATEWAY         = 502, // error response received from gateway
		HTTP_SERVICE_UNAVAIL     = 503, // temporarily overloaded
		HTTP_GATEWAY_TIMEOUT     = 504, // timed out waiting for gateway
		HTTP_VERSION_NOT_SUP     = 505, // HTTP version not supported
	};
	
	class IHttpListener
	{
	public:
		virtual ~IHttpListener() {};
		
		virtual void HttpReceivedResponse( IHttpTransaction* http ) {};
		virtual void HttpReceivedData( IHttpTransaction* http, void* data, size_t length ) {};
		virtual void HttpTransactionComplete( IHttpTransaction* http ) {};
		virtual void HttpTransactionError( IHttpTransaction* http ) {};
	};
	
	class IHttpTransaction
	{
	public:
        const static uint32 DEFAULT_RESPONSE_BUFFER_SIZE = 2048;
		
		virtual void SetListener( IHttpListener* listener ) = 0;
		virtual void SetUserData( void* userData ) = 0;
		virtual void SetRequestHeader( const std::string& name, const std::string& value ) = 0;
		virtual void SetRequestBody( const void* data, size_t length ) = 0;
		virtual void SetTimeout( int seconds ) = 0;
		virtual void SetSlackCertificateValidation( bool slack ) = 0;
		virtual void SetBasicAuth( const std::string& username, const std::string& password ) = 0;
		
		virtual void Start() = 0;
		virtual void Release() = 0;
		
		virtual std::string GetRequestUrl() = 0;
		virtual void* GetUserData() = 0;
		virtual int GetStatusCode() = 0;
		virtual std::string GetStatusLine() = 0;
		virtual int GetResponseLength() = 0;
		virtual std::string GetResponseHeader( const std::string& key ) = 0;

		/**
		 * This method should be used only for debugging purposes and may
		 * not be supported on your platform.  Currently implemented on
		 * iOS and OSX, and not supported on Windows.
		 */
		virtual std::string GetSerializedRequest() = 0;

		virtual std::string GetErrorMessage() = 0;
		
	protected:
		virtual ~IHttpTransaction() {};

	};
	
	class INetworkStatusListener;
	
	class IHttpDriver 
	{
	public:
		static IHttpDriver* CreateHttpDriver( SexyAppBase* app );
		virtual ~IHttpDriver() {};
		virtual void Update() = 0;
		virtual IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url, uint32 inResponseBufferSize = IHttpTransaction::DEFAULT_RESPONSE_BUFFER_SIZE ) = 0;
		
		enum NetworkStatus
		{
			NET_NOT_REACHABLE = 0,
			NET_REACHABLE_WWAN,
			NET_REACHABLE_WIFI,
			NET_REACHABILITY_UNKNOWN,
			NET_REACHABIE_ETHERNET,
		};
		
		virtual NetworkStatus GetNetworkStatus() = 0;
		virtual void AddNetworkStatusListener( INetworkStatusListener* listener ) = 0;
		virtual void RemoveNetworkStatusListener( INetworkStatusListener* listener ) = 0;
	};

	class INetworkStatusListener
	{
	public:
		virtual ~INetworkStatusListener() {};
		virtual void NetworkStatusChanged( IHttpDriver::NetworkStatus status ) = 0;
	};
	
}

#endif

