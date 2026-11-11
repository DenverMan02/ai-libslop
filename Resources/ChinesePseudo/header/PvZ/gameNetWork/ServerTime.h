#ifndef SERTIME_H_
#define SERTIME_H_

#include <string>
#include <list>
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/RtDelegate.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include "ServerTimeHandler.h"

#ifndef _64BIT_TRANSFER_
#define _64BIT_TRANSFER_

template <class T> T SafeTransferFromUInt64(uint64 src_value, T target_type_max)
{
    //DBG_ASSERT(0==(src_value/target_type_max));
    return static_cast<T>(src_value);
}

template <class T> T SafeTransferFromInt64(int64 src_value, T target_type_max)
{
    //DBG_ASSERT(0==(src_value/target_type_max));
    return static_cast<T>(src_value);
}

#endif

typedef  void (*ServerTimeHandler)(int ret,long serverTime);

class ServerTime : public Sexy::NetworkServiceListener
{

public:
	ServerTime();
	~ServerTime();
	static ServerTime*  s_pServerTime;
	static ServerTime* Instance();
	void  Update(float dt = 0);

	long GetServerTime();
	const  tm* GetServerTimeS();
    void GetServerTime(ServerTimeHandler hanlder);
	void GetServerTimeFromNet(CServerTimeHandler* pHandler,bool bShowUI=true);

    virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
    virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) {}
    virtual void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context ) {}
    virtual void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
    void StartRequest();
    
    bool IsHeartbeatSuccess(){return m_IsConnected; }

    void    AddServerTimeHandler(CServerTimeHandler*& pHandler);

    void SetServerTime(const std::string& strTime);

private:

	void              Init();
	void			  StartRequest(bool bShowUI);
	bool			  ValidServerTime();
    void              ProcessHandler(bool ret);
    void              RemoveNetConnectUI();
    
    ServerTimeHandler m_ServerTimeHanlde;
    std::string 	  m_srvURL;
    long			  m_ServerTime;
    long              m_lastTime;
    int               m_LoopCount;
    int               m_requestCount;
    Sexy::CritSect    mHttpRequestCS;
    bool              m_IsConnected;
    float             m_heatBeatTimer;
    short             m_failedCount;

	bool			  m_bRequesting;
    bool              m_bShowConnectUI;
    std::list<CServerTimeHandler*>  m_pServerHandlers;

};



#endif

