//
//  SequentialActionRunner.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 5/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SequentialActionRunner__
#define __PlantsVersusZombies2__SequentialActionRunner__

#include <vector>
#include "ActionRunner.h"
#include "RunnableAction.h"

// Runs all actions in sequence, waiting until one action is complete
// before beginning the next.
// Actions added while running are queued at the end of the sequence.
class SequentialActionRunner : public ActionRunner
{
public:
	SequentialActionRunner();
	virtual ~SequentialActionRunner();
	
	RunnableAction* Add(RunnableAction* i_action) override;
	
	void EndAllActions() override;
	int Size() const override;
	bool IsEmpty() const override;
	
protected:
	void onBegin() override;
	void onUpdate() override;
	void onEnd() override;
	
	void processActions();
	
	std::vector<RunnableAction*> m_actions;
};

// Designed for standalone use, not to run on another runner
// Two major differences from a SequentialActionRunner:
// 1. No lifecycle - Begin() is automatically called on construction, and End() is never called.
// 2. Actions added to this runner are consumed as they are completed.
class ForeverSequentialActionRunner : public SequentialActionRunner
{
protected:
	void onUpdate() override;
	
private:
	void deleteCompletedActions();
};

#endif /* defined(__PlantsVersusZombies2__SequentialActionRunner__) */
