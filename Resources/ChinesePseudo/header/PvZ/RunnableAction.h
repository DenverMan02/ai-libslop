//
//  RunnableAction.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 5/2/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RunnableAction__
#define __PlantsVersusZombies2__RunnableAction__

#include "TodDebug.h"

enum RunnableActionState
{
	NotStarted,
	Running,
	Finished,
};

// An atom of code that can be used with ActionRunners to build up complex behaviors.
// Actions should implement onBegin() and/or onUpdate(), and should call End() on themselves
// when their work is done.
class RunnableAction
{
public:
	RunnableAction() : m_runnableActionState(NotStarted) {}
	virtual ~RunnableAction() {};
	
	void Begin()
	{
		DBG_ASSERT(NotStarted == m_runnableActionState);
		m_runnableActionState = Running;
		onBegin();
	}
	
	void Update()
	{
		DBG_ASSERT(Running == m_runnableActionState);
		onUpdate();
	}
	
	void End()
	{
		DBG_ASSERT(Finished != m_runnableActionState);
		onEnd();
		m_runnableActionState = Finished;
	}
	
	bool IsStarted() { return (NotStarted != m_runnableActionState); }
	bool IsRunning() { return (Running == m_runnableActionState); }
	bool IsFinished() { return (Finished == m_runnableActionState); }
	
protected:
	virtual void onBegin() {}
	virtual void onUpdate() {}
	virtual void onEnd() {}
	
	RunnableActionState m_runnableActionState;
};


#endif /* defined(__PlantsVersusZombies2__RunnableAction__) */
