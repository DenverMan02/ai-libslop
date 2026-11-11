//
//  RenderQueue.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 2/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_RenderQueue_h
#define PlantsVersusZombies2_RenderQueue_h

#include "RtDelegate.h"

struct RenderItem
{
	RenderItem() : m_zPos(0)
	{}
	
	Delegate1<class Graphics*>	m_renderDelegate;
	int							m_zPos;
};


class RenderQueue
{
public:
	RenderQueue(int i_reservedSize = 0)
		: m_sorted(false)
	{
		m_renderItems.reserve(i_reservedSize);
	}
	
	void Add(int i_renderOrder, Delegate1<class Graphics*> i_renderCall);
	
	const std::vector<RenderItem>& GetSortedQueue();
	
private:
	bool m_sorted;
	std::vector<RenderItem> m_renderItems;
};

#endif
