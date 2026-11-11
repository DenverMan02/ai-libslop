//
//  PowerupFlickZombie.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 12/4/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PowerupFlickZombie_h
#define PlantsVersusZombies2_PowerupFlickZombie_h

#include "Effect_PopAnim.h"
#include "BasePowerup.h"

class PowerupFlickZombie : public BasePowerup
{
public:
	RT_CLASS_DEFINE(PowerupFlickZombie, BasePowerup, Sexy::RtClass);

	PowerupFlickZombie()
	: m_touchIdent(Sexy::InvalidTouchID)
	{}
	
protected:

	OVERRIDE_STATE_ONENTER(PowerupState, Idle);
	OVERRIDE_STATE_ONENTER(PowerupState, Selected);

	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
	
private:
	bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();
	void flick(const SexyVector2& i_direction);
	void findTargetZombie(const SexyVector2& i_startPoint, const SexyVector2& i_endPoint, std::vector<class Zombie*>& o_zombies);
	bool isValidTarget(class Zombie* i_zombie);

	/// Serialized values
	
	/// Transient values
	
	Sexy::TouchID m_touchIdent;
	SexyVector2 m_touchStart;
};

class Zombie;
namespace Message
{
	void ZombieFlicked(Zombie* i_zombie);
}

#endif
