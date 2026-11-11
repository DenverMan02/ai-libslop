//
//  ComponentZombieWhackTouch.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 12/2/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentOnDeath__
#define __PlantsVersusZombies2__ComponentOnDeath__

// Shared base class for components that do something on death.

#include "ComponentBase.h"

class ComponentOnDeath : public ComponentBase
{
public:
	RT_CLASS_DEFINE(ComponentOnDeath, ComponentBase, RtClass);
	
	ComponentOnDeath() {}
	~ComponentOnDeath() {}
	
protected:
	void onEnd() override;

	virtual void onDeath() {}
	
private:
	
};

class ComponentOnDeath_SpawnZombie : public ComponentOnDeath
{
public:
	RT_CLASS_DEFINE(ComponentOnDeath_SpawnZombie, ComponentOnDeath, RtClass);

    void SetZombieTypeToSpawn(std::string i_zombieType, int zombieLevel, bool i_riseFromGround);
    ComponentOnDeath_SpawnZombie();
protected:
	void onDeath() override;
	
private:
	std::string m_zombieTypeToSpawn;
    int m_zombieLevel;
	bool		m_zombieRiseFromGround;
	
};

#endif
