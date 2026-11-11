#pragma once
#ifndef WINDOWSHTTPDRIVER_H_INCLUDED
#define WINDOWSHTTPDRIVER_H_INCLUDED
#include "IHttpDriver.h"
#include "Common.h"
#include <winhttp.h>

namespace Sexy 
{
	class WindowsHttpTransaction;

	class WindowsHttpDriver
		: public IHttpDriver
	{
	public:
		WindowsHttpDriver();
		~WindowsHttpDriver();
		void Update();

		//PVZ2_CHINESE_START CJD_RSG3
		//IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url );
		IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url, uint32 inResponseBufferSize = IHttpTransaction::DEFAULT_RESPONSE_BUFFER_SIZE );
		//PVZ2_CHINESE_END

		NetworkStatus GetNetworkStatus();
		void AddNetworkStatusListener( INetworkStatusListener* listener );
		void RemoveNetworkStatusListener( INetworkStatusListener* listener );

		HINTERNET GetSessionHandle();
		void RemoveHttpTransaction( WindowsHttpTransaction* http );

	protected:

		HINTERNET mHttpSession;

		typedef std::vector< WindowsHttpTransaction* > HttpTransactions;
		HttpTransactions mHttpTransactions;

	};
}

#endif

