//
//  TimelineActionRunner.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 5/13/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TimelineActionRunner__
#define __PlantsVersusZombies2__TimelineActionRunner__

#include "ActionRunner.h"
#include "RunnableAction.h"
#include "TimeMgr.h"

struct TimelineActionRunnerEvent
{
	TimelineActionRunnerEvent(RunnableAction* i_action, pvztime_t i_startTimeSeconds)
	: Action(i_action)
	, StartTimeSeconds(i_startTimeSeconds)
	{}
	
	RunnableAction* Action;
	pvztime_t StartTimeSeconds;
};

// Runs all actions
class TimelineActionRunner : public ActionRunner
{
public:
	TimelineActionRunner();
	virtual ~TimelineActionRunner();
	
	RunnableAction* Add(RunnableAction* i_action) override;
	RunnableAction* Add(RunnableAction* i_action, pvztime_t i_startDelaySeconds);
	
	void EndAllActions() override;
	int Size() const override;
	bool IsEmpty() const override;
	
protected:
	void onBegin() override;
	void onUpdate() override;
	void onEnd() override;
	
private:
	bool allActionsAreFinished();
	
	std::vector<TimelineActionRunnerEvent> m_events;
	pvztime_t m_startTime;
};

#endif /* defined(__PlantsVersusZombies2__TimelineActionRunner__) */
