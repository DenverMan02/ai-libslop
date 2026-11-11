/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 14
 ------------------------------------------------------------------------------------------------------------*/

#ifndef LEVEL_GIFT_EVENT_H_
#define LEVEL_GIFT_EVENT_H_
#include "NetWorkEvent.h"

class FriendGiftEvent : public NetWorkEvent
{
public:
    FriendGiftEvent();
   ~FriendGiftEvent();

   virtual void Update(long ms);
   virtual void Init();
};

#endif

