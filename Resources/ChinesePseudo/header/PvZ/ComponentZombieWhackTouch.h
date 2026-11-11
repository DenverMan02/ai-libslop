//
//  ComponentZombieWhackTouch.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 12/2/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentZombieWhackTouch__
#define __PlantsVersusZombies2__ComponentZombieWhackTouch__

#include "ComponentBase.h"

class ComponentZombieWhackTouch : public ComponentBase
{
public:
	RT_CLASS_DEFINE(ComponentZombieWhackTouch, ComponentBase, RtClass);
	
	ComponentZombieWhackTouch();
	~ComponentZombieWhackTouch() {}
	
protected:
	void onBegin() override;
	void onUpdate() override;
	void onEnd() override;
	void registerForEvents() override;
	void unregisterForEvents() override;

	bool onTouchEvent(const Sexy::Touch& i_touch);
	
private:
	
	void whackThyOwner(float i_hitFraction);
	void whackThyOwnerOneHit();

	float			m_currentHitFraction;
	
	// not serialized
	
	Sexy::TouchID	m_owningTouchIdent;
};

#endif /* defined(__PlantsVersusZombies2__ComponentZombieWhackTouch__) */
