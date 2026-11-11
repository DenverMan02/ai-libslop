//
//  ZombieSurrenderSubsystem.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/15/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieSurrenderSubsystem__
#define __PlantsVersusZombies2__ZombieSurrenderSubsystem__

#include "GameSubSystem.h"

//
// Some kinds of zombies can't actually end the game in defeat, either because they are
// stationary or because they move left-to-right.  If these zombies are they only ones
// left in a level, the level is effectively won, and they should give up (die).
// This system handles that.
//
class ZombieSurrenderSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombieSurrenderSubsystem, GameSubSystem, RtClass);
	
	void Update() override;
	
private:
	bool areOnlySurrenderingZombiesLeft() const;
	void killRemainingZombies();

	bool areOnlySurrenderingZombiesRight() const;
	void killPetrifiedZombies();
};

#endif /* defined(__PlantsVersusZombies2__ZombieSurrenderSubsystem__) */
