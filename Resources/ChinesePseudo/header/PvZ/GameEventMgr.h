//
//  GameEventMgr.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 12/14/11.
//  Copyright (c) 2011 PopCap. All rights reserved.
//

#ifndef PlantsVersusZombies2_GameEventMgr_h
#define PlantsVersusZombies2_GameEventMgr_h

#include <map>
#include <utility>
#include <vector>

#include "Debug.h"
#include "RtDb.h"
#include "RtDelegate.h"

namespace Sexy {
class RtObject;
}  // namespace Sexy

using Sexy::RtWeakPtr;
using Sexy::RtObject;

class MessageRouter
{
public:
    virtual ~MessageRouter() {}
    MessageRouter()
    : m_postCount(0)
    {
        // Do nothing.
    }

    //
    // Zero Args
    // This is the simplest implementation, One Arg is more complicated (and more commented)
    //
    void Subscribe(void (*message)(void), const Sexy::Delegate0 &listener);
    void Unsubscribe(void (*message)(void), const Sexy::Delegate0 &listener);
    void Broadcast(void (*message)(void));
    void Post(void (*message)(void)) { Broadcast(message); }
    void SendTo(RtWeakPtr<RtObject> object, void (*message)(void));

    //
    // One Arg
    //
    template <typename P1, typename TranslatorType> void Subscribe(void (*message)(P1), TranslatorType listener);
    template <typename P1, typename TranslatorType> void Unsubscribe(void (*message)(P1), TranslatorType listener);
    template <typename P1, typename C1> void Broadcast(void (*message)(P1), C1 c1);
    template <typename P1, typename C1> void Post(void (*message)(P1), C1 c1) { Broadcast(message, c1); }
    template <typename P1, typename C1> void SendTo(RtWeakPtr<RtObject> object, void (*message)(P1), C1 c1);

    //
    // Two Args
    //
    template <typename P1, typename P2, typename TranslatorType> void Subscribe(void (*message)(P1, P2), TranslatorType listener);
    template <typename P1, typename P2, typename TranslatorType> void Unsubscribe(void (*message)(P1, P2), TranslatorType listener);
    template <typename P1, typename P2, typename C1, typename C2> void Broadcast(void (*message)(P1, P2), C1 c1, C2 c2);
    template <typename P1, typename P2, typename C1, typename C2> void Post(void (*message)(P1, P2), C1 c1, C2 c2) { Broadcast(message, c1, c2); }
    template <typename P1, typename P2, typename C1, typename C2> void SendTo(RtWeakPtr<RtObject> object, void (*message)(P1, P2), C1 c1, C2 c2);

    //
    // Three Args
    //
    template <typename P1, typename P2, typename P3, typename TranslatorType> void Subscribe(void (*message)(P1, P2, P3), TranslatorType listener);
    template <typename P1, typename P2, typename P3, typename TranslatorType> void Unsubscribe(void (*message)(P1, P2, P3), TranslatorType listener);
    template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void Broadcast(void (*message)(P1, P2, P3), C1 c1, C2 c2, C3 c3);
    template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void Post(void (*message)(P1, P2, P3), C1 c1, C2 c2, C3 c3) { Broadcast(message, c1, c2, c3); }
    template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void SendTo(RtWeakPtr<RtObject> object, void (*message)(P1, P2, P3), C1 c1, C2 c2, C3 c3);

    //
    // Four Args
    //
    template <typename P1, typename P2, typename P3, typename P4, typename TranslatorType> void Subscribe(void (*message)(P1, P2, P3, P4), TranslatorType listener);
    template <typename P1, typename P2, typename P3, typename P4, typename TranslatorType> void Unsubscribe(void (*message)(P1, P2, P3, P4), TranslatorType listener);
    template <typename P1, typename P2, typename P3, typename P4, typename C1, typename C2, typename C3, typename C4> void Broadcast(void (*message)(P1, P2, P3, P4), C1 c1, C2 c2, C3 c3, C4 c4);
    template <typename P1, typename P2, typename P3, typename P4, typename C1, typename C2, typename C3, typename C4> void Post(void (*message)(P1, P2, P3, P4), C1 c1, C2 c2, C3 c3, C4 c4) { Broadcast(message, c1, c2, c3, c4); }
    template <typename P1, typename P2, typename P3, typename P4, typename C1, typename C2, typename C3, typename C4> void SendTo(RtWeakPtr<RtObject> object, void (*message)(P1, P2, P3, P4), C1 c1, C2 c2, C3 c3, C4 c4);


    //
    // Need More? Copy, paste, and extend the functions above.
    // Need help? Talk to dsiems.
    //

    // This function does a full pass and unsubribes the listener from all events.
    void Unsubscribe(void *listener);
    int SubscriberCount(void *message);

protected:
    virtual const std::vector<Sexy::Delegate0> &getTableForTarget(RtWeakPtr<RtObject> object, void *message) const;
    virtual const std::vector<Sexy::Delegate0> &getTable(void *message) const;

private:
    // Have to store as a Delegate0 because Delegate's constructor is protected...
    // This should be okay because all of our delegates are the same size.
    typedef std::map<void*, std::vector<Sexy::Delegate0> > RoutingTable;

    void queueInsert(void *message, const Sexy::Delegate0 &listener);
    void queueRemove(void *message, const Sexy::Delegate0 &listener);
    void queueRemove(void *listener);

    void insert(void *message, const Sexy::Delegate0 &listener);
    void remove(void *message, const Sexy::Delegate0 &listener);
    void remove(void *message, void *listener);
    void remove(void *listener);

    void dispatch(const std::vector<Sexy::Delegate0> &table);
    template <typename P1, typename C1> void dispatch(void (*message)(P1), const std::vector<Sexy::Delegate0> &table, C1 c1);
    template <typename P1, typename P2, typename C1, typename C2> void dispatch(void (*message)(P1, P2), const std::vector<Sexy::Delegate0> &table, C1 c1, C2 c2);
    template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void dispatch(void (*message)(P1, P2, P3), const std::vector<Sexy::Delegate0> &table, C1 c1, C2 c2, C3 c3);
    template <typename P1, typename P2, typename P3, typename P4,typename C1, typename C2, typename C3, typename C4> void dispatch(void (*message)(P1, P2, P3, P4), const std::vector<Sexy::Delegate0> &table, C1 c1, C2 c2, C3 c3, C4);

    void addAndRemoveSubscribers();
    bool isDelegateValid(const Sexy::Delegate0& rDelegate) const;

    RoutingTable m_routingTable;
    std::map<void*, RoutingTable> m_targettedRoutingTables;

    struct AddRemoveRequest {
        enum QueueAction
        {
            Unknown,
            Add,
            RemoveDelegate,
            RemoveObject,
        };

        AddRemoveRequest()
        : Action(Unknown)
        , Message(nullptr)
        {
            // Do nothing.
        }

        AddRemoveRequest(QueueAction i_action, void* i_message, const Sexy::Delegate0& i_observer)
        : Action(i_action)
        , Message(i_message)
        , ObserverDelegate(i_observer)
        {
            DBG_ASSERT(i_action == Add || i_action == RemoveDelegate);
        }

        AddRemoveRequest(QueueAction i_action, void* i_observer)
        : Action(i_action)
        , ObserverObject(i_observer)
        {
            DBG_ASSERT(i_action == RemoveObject);
        }

        QueueAction Action;
        Sexy::Delegate0 ObserverDelegate;
        union
        {
            void* Message;
            void* ObserverObject;
        };
    };
    std::vector<AddRemoveRequest> m_queuedRequests;
    int m_postCount;
};

extern MessageRouter* gMessageRouter;

#define BroadcastMessage(message, ...) \
do { \
    gMessageRouter->Broadcast(message, ##__VA_ARGS__); \
} while(0)

#define SendMessageTo(recipient, message, ...) \
do { \
    gMessageRouter->SendTo(recipient, message, ##__VA_ARGS__); \
} while(0)



//
// One Arg
//
template <typename P1, typename TranslatorType> void MessageRouter::Subscribe(void (*message)(P1), TranslatorType listener)
{
    // This is extremely important. If this breaks, then this entire thing will fall apart.
    // (because all delegates are stored as Delegate0's internally)
    DBG_ASSERTSTATIC(sizeof(Sexy::Delegate1<P1>) == sizeof(Sexy::Delegate0));
    Sexy::Delegate1<P1> d(listener);
    queueInsert((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename TranslatorType> void MessageRouter::Unsubscribe(void (*message)(P1), TranslatorType listener)
{
    Sexy::Delegate1<P1> d(listener);
    queueRemove((void*)message, (const Sexy::Delegate0&)d);
}

// Having different template parameters for the function and for the arg that's actually
// passed in lets the compiler do implicit conversions.
template <typename P1, typename C1> void MessageRouter::Broadcast(void (*message)(P1), C1 c1)
{
    dispatch(message, getTable((void*)message), c1);
}

template <typename P1, typename C1> void MessageRouter::SendTo(RtWeakPtr<RtObject> object, void (*message)(P1), C1 c1)
{
    dispatch(message, getTableForTarget(object, (void*)message), c1);
}

template <typename P1, typename C1> void MessageRouter::dispatch(void (*message)(P1), const std::vector<Sexy::Delegate0> &table, C1 c1)
{
    ++m_postCount;
    for (const auto &target : table)
    {
        // Cast the delegate we stored as a Delegate0 to the appropriate type, this is type-safe
        // because we only allowed delegates with a matching event signature to be subscribed
        // to this event.
        if (isDelegateValid(target))
            (*(Sexy::Delegate1<P1>*)&target)(c1);
    }
    --m_postCount;

    if (m_postCount == 0)
    {
        addAndRemoveSubscribers();
    }
}

//
// Two Args
//
template <typename P1, typename P2, typename TranslatorType> void MessageRouter::Subscribe(void (*message)(P1, P2), TranslatorType listener)
{
    DBG_ASSERTSTATIC(sizeof(Sexy::Delegate2<P1, P2>) == sizeof(Sexy::Delegate0));
    Sexy::Delegate2<P1, P2> d(listener);
    queueInsert((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename P2, typename TranslatorType> void MessageRouter::Unsubscribe(void (*message)(P1, P2), TranslatorType listener)
{
    Sexy::Delegate2<P1, P2> d(listener);
    queueRemove((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename P2, typename C1, typename C2> void MessageRouter::Broadcast(void (*message)(P1, P2), C1 c1, C2 c2)
{
    dispatch(message, getTable((void*)message), c1, c2);
}

template <typename P1, typename P2, typename C1, typename C2> void MessageRouter::SendTo(RtWeakPtr<RtObject> object, void (*message)(P1, P2), C1 c1, C2 c2)
{
    dispatch(message, getTableForTarget(object, (void*)message), c1, c2);
}

template <typename P1, typename P2, typename C1, typename C2> void MessageRouter::dispatch(void (*message)(P1, P2), const std::vector<Sexy::Delegate0> &table, C1 c1, C2 c2)
{
    ++m_postCount;
    for (const auto &target : table)
    {
        if (isDelegateValid(target))
            (*(Sexy::Delegate2<P1, P2>*)&target)(c1, c2);
    }
    --m_postCount;

    if (m_postCount == 0)
    {
        addAndRemoveSubscribers();
    }
}

//
// Three Args
//
template <typename P1, typename P2, typename P3, typename TranslatorType> void MessageRouter::Subscribe(void (*message)(P1, P2, P3), TranslatorType listener)
{
    DBG_ASSERTSTATIC(sizeof(Sexy::Delegate3<P1, P2, P3>) == sizeof(Sexy::Delegate0));
    Sexy::Delegate3<P1, P2, P3> d(listener);
    queueInsert((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename P2, typename P3, typename TranslatorType> void MessageRouter::Unsubscribe(void (*message)(P1, P2, P3), TranslatorType listener)
{
    Sexy::Delegate3<P1, P2, P3> d(listener);
    queueRemove((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void MessageRouter::Broadcast(void (*message)(P1, P2, P3), C1 c1, C2 c2, C3 c3)
{
    dispatch(message, getTable((void*)message), c1, c2, c3);
}

template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void MessageRouter::SendTo(RtWeakPtr<RtObject> object, void (*message)(P1, P2, P3), C1 c1, C2 c2, C3 c3)
{
    dispatch(message, getTableForTarget(object, (void*)message), c1, c2, c3);
}

template <typename P1, typename P2, typename P3, typename C1, typename C2, typename C3> void MessageRouter::dispatch(void (*message)(P1, P2, P3), const std::vector<Sexy::Delegate0> &table, C1 c1, C2 c2, C3 c3)
{
    ++m_postCount;
    for (const auto &target : table)
    {
        if (isDelegateValid(target))
            (*(Sexy::Delegate3<P1, P2, P3>*)&target)(c1, c2, c3);
    }
    --m_postCount;

    if (m_postCount == 0)
    {
        addAndRemoveSubscribers();
    }
}

//
// Four Args
//
template <typename P1, typename P2, typename P3, typename P4, typename TranslatorType> void MessageRouter::Subscribe(void (*message)(P1, P2, P3, P4), TranslatorType listener)
{
    DBG_ASSERTSTATIC(sizeof(Sexy::Delegate4<P1, P2, P3, P4>) == sizeof(Sexy::Delegate0));
    Sexy::Delegate4<P1, P2, P3, P4> d(listener);
    queueInsert((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename P2, typename P3, typename P4, typename TranslatorType> void MessageRouter::Unsubscribe(void (*message)(P1, P2, P3, P4), TranslatorType listener)
{
    Sexy::Delegate4<P1, P2, P3, P4> d(listener);
    queueRemove((void*)message, (const Sexy::Delegate0&)d);
}

template <typename P1, typename P2, typename P3, typename P4, typename C1, typename C2, typename C3, typename C4> void MessageRouter::Broadcast(void (*message)(P1, P2, P3, P4), C1 c1, C2 c2, C3 c3, C4 c4)
{
    dispatch(message, getTable((void*)message), c1, c2, c3, c4);
}

template <typename P1, typename P2, typename P3, typename P4, typename C1, typename C2, typename C3, typename C4> void MessageRouter::SendTo(RtWeakPtr<RtObject> object, void (*message)(P1, P2, P3, P4), C1 c1, C2 c2, C3 c3, C4 c4)
{
    dispatch(message, getTableForTarget(object, (void*)message), c1, c2, c3, c4);
}

template <typename P1, typename P2, typename P3, typename P4, typename C1, typename C2, typename C3, typename C4> void MessageRouter::dispatch(void (*message)(P1, P2, P3, P4), const std::vector<Sexy::Delegate0> &table, C1 c1, C2 c2, C3 c3, C4 c4)
{
    ++m_postCount;
    for (const auto &target : table)
    {
        if (isDelegateValid(target))
            (*(Sexy::Delegate4<P1, P2, P3, P4>*)&target)(c1, c2, c3, c4);
    }
    --m_postCount;

    if (m_postCount == 0)
    {
        addAndRemoveSubscribers();
    }
}


class MessageUnsubscriber
{
public:
	MessageUnsubscriber(void* i_listener)
	: m_listener{i_listener}
	{
	}
	
	~MessageUnsubscriber()
	{
		if (m_listener)
		{
			gMessageRouter->Unsubscribe(m_listener);
		}
	}
	
	MessageUnsubscriber(MessageUnsubscriber&& i_rhs)
	: m_listener {i_rhs.m_listener}
	{
		i_rhs.m_listener = nullptr;
	}
	
	MessageUnsubscriber& operator=(MessageUnsubscriber&& i_rhs)
	{
		if (m_listener)
		{
			gMessageRouter->Unsubscribe(m_listener);
		}
		m_listener = i_rhs.m_listener;
		i_rhs.m_listener = nullptr;
		
		return *this;
	}
	
	// move only type -- disallow copying
	MessageUnsubscriber(const MessageUnsubscriber& i_rhs) = delete;
	MessageUnsubscriber& operator=(const MessageUnsubscriber& i_rhs) = delete;

private:
	void* m_listener;
};

#endif
