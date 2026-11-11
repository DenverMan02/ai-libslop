//
//  LocklessQueue.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 8/21/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

//  Implements multithreaded lockless queue - one producer, one consumer.
//  Produce() should only be called by the producer.
//  Consume() should only be called by the consumer.

#ifndef __PlantsVersusZombies2__LocklessQueue__
#define __PlantsVersusZombies2__LocklessQueue__

#include <atomic>

template <typename T>
class LocklessQueue
{
private:
	struct Node
	{
		Node( T val ) : value(val), next(nullptr) { }
		T value;
		Node* next;
	};
	
	Node* first;									// for producer only
	std::atomic<Node*> divider, last;				// shared
	
public:
	LocklessQueue()
	{
		first = divider = last = new Node( T() );	// add dummy separator
	}
	
	~LocklessQueue()
	{
		while( first != nullptr )
		{											// release the list
			Node* tmp = first;
			first = tmp->next;
			delete tmp;
		}
	}
	
	void Produce(const T& t)
	{
		Node* tmp = last.load();
		tmp->next = new Node(t);					// add the new item
		last.store(tmp->next);						// publish it
		
		while( first != divider )
		{											// trim unused nodes
			Node* tmp2 = first;
			first = first->next;
			delete tmp2;
		}
	}
	
	bool Consume(T& result)
	{
		if( divider != last )
		{											// if queue is nonempty
			Node* tmp = divider.load();
			result = tmp->next->value;				// copy it back
			divider.store(tmp->next);				// publish that we took it
			return true;							// and report success
		}
		
		return false;								// else report empty
	}
};

#endif /* defined(__PlantsVersusZombies2__LocklessQueue__) */