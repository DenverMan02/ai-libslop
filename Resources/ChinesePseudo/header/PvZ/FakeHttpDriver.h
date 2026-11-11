//
//  NullNetworkServiceManager.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 8/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_NullNetworkServiceManager_h
#define PlantsVersusZombies2_NullNetworkServiceManager_h

#include "SexyAppBase.h"
#include "IHttpDriver.h"
#include "StructuredData.h"
#include <memory>

class NullHttpTransaction : public Sexy::IHttpTransaction
{
public:
	void SetListener( Sexy::IHttpListener* listener )
	{
	}
	void SetUserData( void* userData )
	{
		// Put breakpoint here if you want to inspect data before it is 'sent' over the wire.
		SetUserDataArgs.push_back(userData);
	}
	void SetRequestHeader( const std::string& name, const std::string& value )
	{
		// Put breakpoint here if you want to inspect data before it is 'sent' over the wire.
		SetRequestHeaderArgs.push_back(std::pair<std::string, std::string>(name, value));
	}
	void SetRequestBody( const void* data, size_t length )
	{
		// Put breakpoint here if you want to inspect data before it is 'sent' over the wire.
		// To inspect data in gdb:
		// p (char*) data
		// To make sure all is visible, use:
		// set print elements 0
		SetRequestBodyArgs.push_back(std::string((char*)data, length));
	}
	void SetTimeout( int seconds )
	{
	}
	void SetSlackCertificateValidation( bool slack )
	{
	}
    void SetBasicAuth( const std::string& username, const std::string& password )
    {
    }
	void Start()
	{
	}
	void Release()
	{
	}
	std::string GetRequestUrl()
	{
		return "";
	}
	void* GetUserData()
	{
		return NULL;
	}
	int GetStatusCode()
	{
		return 0;
	}
	std::string GetStatusLine()
	{
		return "";
	}
	int GetResponseLength()
	{
		return 0;
	}
	std::string GetResponseHeader( const std::string& key )
	{
		return "";
	}
	std::string GetSerializedRequest()
	{
		return "";
	}
	std::string GetErrorMessage()
	{
		return "";
	}
	
	void Clear()
	{
		SetUserDataArgs.clear();
		SetRequestHeaderArgs.clear();
		SetRequestBodyArgs.clear();
	}

	std::vector<void*> SetUserDataArgs;
	std::vector< std::pair<std::string, std::string> > SetRequestHeaderArgs;
	std::vector<std::string> SetRequestBodyArgs;
};

class FakeHttpDriver : public Sexy::IHttpDriver
{
public:
	virtual ~FakeHttpDriver()
	{		
		Sexy::gSexyAppBase->mHttpDriver = m_realHttpDriver;
	}
	static FakeHttpDriver* GetInstance()
	{
		if (m_Instance.get() == NULL)
			m_Instance = std::unique_ptr<FakeHttpDriver>(new FakeHttpDriver());
		return m_Instance.get();
	}
	void Update()
	{
	}
	Sexy::IHttpTransaction* CreateHttpTransaction( const std::string& method, const std::string& url, uint32 inResponseBufferSize )
	{
		CreateHttpTransactionArgs.push_back(std::pair<std::string, std::string>(method, url));
		return GetNullHttpTransaction();
	}
	NetworkStatus GetNetworkStatus()
	{
		return m_networkStatus;
	}
	void AddNetworkStatusListener( Sexy::INetworkStatusListener* listener )
	{
	}
	void RemoveNetworkStatusListener( Sexy::INetworkStatusListener* listener )
	{
	}
	void SetNetworkStatus(NetworkStatus newValue)
	{
		m_networkStatus = newValue;
	}
	NullHttpTransaction* GetNullHttpTransaction()
	{
		return m_NullHttpTransaction.get();
	}
	void Clear()
	{
		CreateHttpTransactionArgs.clear();
		m_NullHttpTransaction.get()->Clear();
	}
	std::vector< std::pair<std::string, std::string> > CreateHttpTransactionArgs;

protected:
	FakeHttpDriver()
	: m_realHttpDriver(Sexy::gSexyAppBase->mHttpDriver)
	, m_NullHttpTransaction(new NullHttpTransaction())
	, m_networkStatus(NET_REACHABLE_WIFI)
	{
		if (m_NullHttpTransaction.get() == NULL)
		{
			// What the heck
			m_NullHttpTransaction.get();
		}
		// Intercept unless traffic is allowed to go to real server.
#if !defined(WANTS_METRICS_ENABLED)
		Sexy::gSexyAppBase->mHttpDriver = this;
#endif
	}	
private:
	static std::unique_ptr<FakeHttpDriver> m_Instance;
	Sexy::IHttpDriver* m_realHttpDriver;
	std::unique_ptr<NullHttpTransaction> m_NullHttpTransaction;
	NetworkStatus m_networkStatus;
};



#endif
