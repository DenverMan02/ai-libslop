/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 14
 ------------------------------------------------------------------------------------------------------------*/

#ifndef FRIEND_SUN_EVENT_H_
#define FRIEND_SUN_EVENT_H_
#include "NetWorkEvent.h"

class FriendSunEvent : public NetWorkEvent
{
public:
    FriendSunEvent();
   ~FriendSunEvent();

   virtual void Update(long ms);
   virtual void Init();
};

#endif

