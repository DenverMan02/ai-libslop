//
//  LogServer.h
//  PlantsVersusZombies2
//
//  
//
//  (Pusher)
//
//  Created by weiqi.zhong on 6/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef LOG_SERVER_H_
#define LOG_SERVER_H_
#include "sock_buffer.h"
#include "TcpClient.h"
#include "SexyApp.h"
#define  TMP_BUF_LEN    8192
void Thread_fun(void* pObj);
class LogServer
{
public:
    LogServer();
    ~LogServer();
    
    static LogServer* s_pLogServer;
    static LogServer* Instance();
    void  Init();
    void  Init(const char* logServerAddr,unsigned short port);
    void  updateLogServerAddress();
    bool  InitNetSocket();
    void  Update();
    bool  SendMsg(const char* buff, unsigned short len);
    bool  IsStoped(){ return m_stop;};
    LogServer& AppendMsg(std::string msg);
    void  Stop();
    void  Start();
    void  SendMsg();
    void  Clean();
    void  SendFakeInfo(const std::string& uuId,int fakeCode,int lastRechargeGems,int lastFreeGems,int lastCoins);
    void  SendFakderNewUUI(const std::string& uuId,const std::string& newUUid);
private:
    void DeermineBlock();
   
    //int              m_addr;
    unsigned short   m_port;
    std::string      m_strIp;
    TcpClient*       m_pTcpClient;
    StreamBuffer*    m_pStreamBuff;
    pthread_cond_t   m_stCond;
    pthread_mutex_t  m_stMutex;
    //Sexy::CritSect	mCritSect;
    std::string     m_sendMsg;
    char*           m_tmpBuf;
    bool   m_stop;
    bool   m_bThradRun;
      
};
#endif
