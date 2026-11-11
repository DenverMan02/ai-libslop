/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 14
 ------------------------------------------------------------------------------------------------------------*/

#ifndef LEVEL_HEARTBEAT_EVENT_H_
#define LEVEL_HEARTBEAT_EVENT_H_
#include "NetWorkEvent.h"

class HeartBeatEvent : public NetWorkEvent
{
public:
    HeartBeatEvent();
   ~HeartBeatEvent();

   virtual void Update(long ms);
   virtual void Init();
};

#endif

