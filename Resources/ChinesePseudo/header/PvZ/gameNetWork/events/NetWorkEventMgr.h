/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 14
 ------------------------------------------------------------------------------------------------------------*/

#ifndef NET_WORK_EVENT_MGR_H_
#define NET_WORK_EVENT_MGR_H_
#include "NetWorkEvent.h"
#include <vector>
typedef std::vector<NetWorkEvent*> EventArray;
typedef EventArray::iterator  EventIter;
class NetWorkEventMgr
{
public:
    NetWorkEventMgr();
    ~NetWorkEventMgr();
    
    void Init();
    static NetWorkEventMgr* Instance();
    
    static NetWorkEventMgr* s_pNetWorkEventMgr;
    void Update();
    EventArray m_EventArray;
    time_t  m_lastTime;
    int    m_tickCount ;
    
};
#endif

