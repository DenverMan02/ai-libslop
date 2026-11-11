//
//  ActionRunner.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 5/13/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ActionRunner_h
#define PlantsVersusZombies2_ActionRunner_h

#include "RunnableAction.h"

class ActionRunner : public RunnableAction
{
public:
	
	// Gives an action to the runner, to be run once the runner is started.
	// The ActionRunner should take ownership of any action it is passed - it
	// will take care of deletion of the action when it is no longer needed.
	virtual RunnableAction* Add(RunnableAction* i_action) = 0;
	
	// Ends all actions held by the runner
	virtual void EndAllActions() = 0;
	
	// Gives the number of actions held by the runner
	virtual int Size() const = 0;
	
	// TRUE if the runner holds no actions
	virtual bool IsEmpty() const = 0;
};

#endif
