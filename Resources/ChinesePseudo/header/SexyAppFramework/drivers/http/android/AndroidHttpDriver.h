#pragma once
#ifndef ANDROIDHTTPDRIVER_H_INCLUDED
#define ANDROIDHTTPDRIVER_H_INCLUDED
#include "IHttpDriver.h"
#include "Common.h"
#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"

#include <set>

namespace Sexy 
{
	class AndroidHttpTransaction;

	class AndroidHttpDriver
		: public IHttpDriver
		, public JavaBound< AndroidHttpDriver >
	{
	public:
		AndroidHttpDriver();
		~AndroidHttpDriver();
		void Update();
		IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url, uint32 responseBufferSize = IHttpTransaction::DEFAULT_RESPONSE_BUFFER_SIZE );

		NetworkStatus GetNetworkStatus();
		void AddNetworkStatusListener( INetworkStatusListener* listener );
		void RemoveNetworkStatusListener( INetworkStatusListener* listener );

		void RemoveHttpTransaction( AndroidHttpTransaction* http );

	protected:

		void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
		static JavaMethod<jobject> JavaCreateHttpTransaction;
		static JavaMethod<jint> JavaGetNetworkStatus;

		std::set<INetworkStatusListener*> mNetworkStatusListeners;
		NetworkStatus mNetworkStatus;

		typedef std::vector< AndroidHttpTransaction* > HttpTransactions;
		HttpTransactions mHttpTransactions;
	};
}

#endif


