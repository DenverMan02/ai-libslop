/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 14
 ------------------------------------------------------------------------------------------------------------*/

#ifndef FRIEND_LIST_EVENT_H_
#define FRIEND_LIST_EVENT_H_
#include "NetWorkEvent.h"

class FriendListEvent : public NetWorkEvent
{
public:
    FriendListEvent();
   ~FriendListEvent();

   virtual void Update(long ms);
    virtual void Init();
};

#endif

