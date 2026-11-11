#ifndef __NETWORKMGR_H__
#define __NETWORKMGR_H__
#include <string>
#include <map>
#include "StructuredData.h"

#include "SexyAppFramework/CritSect.h"
#include "SexyAppFramework/AutoCrit.h"
#define  MAX_BUF_LEN    1024*1024
using namespace Sexy;
// added by weiqi.zhong @ 2012 -3- 12
#include "NetworkMsgProcess.h"
class StreamBuffer;
// added end
class NetworkMgr
{
public:
	NetworkMgr();
	~NetworkMgr();	

	int     Init();
	void    Update();
    static NetworkMgr*  Instance();
    static NetworkMgr*  s_pNetworkMgr;
    uint64  GetNetTime(){ return m_NetTime;};
    void    UpdateNetTime(const std::string& netData);

private:

public:
	StreamBuffer * m_pMsgQueue;

	INetworkMsgProcess* GetNewNetWorkProcess();		// fake server
	INetworkMsgProcess* GetNetWorkProcess();				// real server
	CritSect mRecMsgQueueCS;
    static void ReceivedMsgCallback(const unsigned char *buffer,int bufLen);

private:
    void              	UpdateNetTime();

    INetworkMsgProcess * m_pNetWorkMsgProc;
	
	char*        m_pReceivedBuf;
    unsigned int m_iOutlen;
    uint64       m_NetTime;
    uint64       m_lastTime;
    int          m_LoopCount;
    float        m_UpdateCacheTimer;

};
extern NetworkMgr *gNetworkMgr;
#endif
