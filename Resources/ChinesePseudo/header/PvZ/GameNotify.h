//
//  GameNotify.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 12/6/11.
//  Copyright (c) 2011 PopCap. All rights reserved.
//

#ifndef PlantsVersusZombies2_GameNotify_h
#define PlantsVersusZombies2_GameNotify_h

#include "RtId.h"

//
// GameNotify
//
// 

// Event Type
typedef int eventid;

//
// Notification
// The message being passed around. 
//
class GameEventNotification 
{
public:
	explicit GameEventNotification(void* i_poster=0, void* i_data=0, eventid i_eventId=0):m_poster(i_poster), m_data(i_data), m_eventId(i_eventId) {}
	explicit GameEventNotification(Sexy::RtId i_posterId, void* i_data=0, eventid i_eventId=0):m_posterId(i_posterId), m_data(i_data), m_eventId(i_eventId) {}
	explicit GameEventNotification(eventid i_eventId, void* i_poster=0, void* i_data=0):m_poster(i_poster), m_data(i_data), m_eventId(i_eventId) {}
	explicit GameEventNotification(eventid i_eventId, Sexy::RtId i_posterId, void* i_data=0):m_posterId(i_posterId), m_data(i_data), m_eventId(i_eventId) {}
	
	eventid GetEventId() { return m_eventId; }
	
	void* GetPoster() { return m_poster;}
	Sexy::RtId GetPosterId() { return m_posterId;}
	void* GetData()   { return m_data; }
	
	template <typename T>
	T* GetPoster() { return static_cast<T*>(m_poster); }
	
private:
	
	void*		m_poster;
	void*		m_data;
	Sexy::RtId		m_posterId;
	eventid		m_eventId;
};

#endif
