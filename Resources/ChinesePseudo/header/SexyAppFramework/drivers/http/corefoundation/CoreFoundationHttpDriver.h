#ifndef COREFOUNDATIONHTTPDRIVER_H_INCLUDED
#define COREFOUNDATIONHTTPDRIVER_H_INCLUDED
#include "IHttpDriver.h"
#include <SystemConfiguration/SystemConfiguration.h>
#include <set>

namespace Sexy
{
	class CoreFoundationHttpDriver
    : public IHttpDriver
	{
		
	public:
		
		CoreFoundationHttpDriver();
		~CoreFoundationHttpDriver();
		void Update();
		IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url, uint32 inResponseBufferSize = IHttpTransaction::DEFAULT_RESPONSE_BUFFER_SIZE );
		NetworkStatus GetNetworkStatus();
        void UpdateReachability();
		void AddNetworkStatusListener( INetworkStatusListener* listener );
		void RemoveNetworkStatusListener( INetworkStatusListener* listener );
        
	protected:
		
		typedef std::set< INetworkStatusListener* > StatusListeners;
		
		NetworkStatus mNetworkStatus;
		StatusListeners mNetworkStatusListeners;
		SCNetworkReachabilityRef mReachability;
		bool mEnableReachabilityLogging;
		
		void StartReachabilityMonitoring();
		void EndReachabilityMonitoring();
		static void ReachabilityCallback( SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info );
		void ReachabilityChanged( SCNetworkReachabilityFlags flags );
	};
}

#endif

