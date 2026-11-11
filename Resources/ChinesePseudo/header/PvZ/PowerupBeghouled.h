//
//  PowerupBeghouled.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/22/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupBeghouled__
#define __PlantsVersusZombies2__PowerupBeghouled__

#include "BasePowerup.h"

namespace Message
{
	void BeghouledClearGridLocation(int gridX, int gridY);
	void BeghouledShufflePowerup();
}

class PowerupTypeBeghouledShuffle : public PowerupType
{
public:
	RT_CLASS_DEFINE(PowerupTypeBeghouledShuffle, PowerupType, RtClass);
};

class PowerupBeghouledShuffle : public BasePowerup
{
public:
	RT_CLASS_DEFINE(PowerupBeghouledShuffle, BasePowerup, RtClass);
	
protected:
	void onSelected() override;
};

class PowerupTypeBeghouledShovel : public PowerupType
{
public:
	RT_CLASS_DEFINE(PowerupTypeBeghouledShovel, PowerupType, RtClass);
};

class PowerupBeghouledShovel : public PowerupTouchBased
{
public:
	RT_CLASS_DEFINE(PowerupBeghouledShovel, PowerupTouchBased, RtClass);
	
protected:
	bool onTouchBegin(const Sexy::Touch& i_touch) override;
	void onTouchEnd(const Sexy::Touch& i_touch) override;
};

#endif /* defined(__PlantsVersusZombies2__PowerupBeghouled__) */
