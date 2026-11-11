#pragma once
#ifndef NULLHTTPDRIVER_H_INCLUDED
#define NULLHTTPDRIVER_H_INCLUDED
#include "IHttpDriver.h"

namespace Sexy 
{
	class NullHttpDriver
		: public IHttpDriver
	{
	public:
		NullHttpDriver();
		~NullHttpDriver();
		void Update();
		IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url );

		NetworkStatus GetNetworkStatus();
		void AddNetworkStatusListener( INetworkStatusListener* listener );
		void RemoveNetworkStatusListener( INetworkStatusListener* listener );
		
		std::string GetPrimaryMACAddress();
	};
}

#endif

