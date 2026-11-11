//
//  ZombiePull_SubSystem.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-10-24.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombiePull_SubSystem__
#define __PlantsVersusZombies2__ZombiePull_SubSystem__

#include "GameSubSystem.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "RtReflectionDelegate.h"

typedef RtReflectionDelegate<Delegate1<class Zombie*> > ZombiePullAwayCallback;

struct PullZombie
{
	SexyVector3					m_velocity;
	SexyVector3					m_acceleration;
    SexyVector3					m_targetPosition;
    
	RtWeakPtr<class Zombie>		m_zombie;
	RtWeakPtr<class Plant>		m_plant;
	ZombiePullAwayCallback		m_onPullAwayCallback;
};

class ZombiePullSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ZombiePullSubSystem, GameSubSystem, RtClass);
	
    void PullZombieToTarget(class Plant * i_plant,
                            class Zombie* i_zombie,
                            SexyVector3	  i_targetPosition,
                            ZombiePullAwayCallback i_pullAwayCallback = ZombiePullAwayCallback());
    
    virtual void Update() override;
    
protected:
	virtual void registerForEvents() override;
    
private:
    void onZombieDestroyed(Zombie* i_zombie);
    
    void internalPullZombie(PullZombie &i_pullZombie);
    
    std::vector<PullZombie> m_pullZombies;
    std::vector<PullZombie> m_newPullZombies;
    std::vector<RtWeakPtr<class Zombie> > m_deadZombies;
};

#endif /* defined(__PlantsVersusZombies2__ZombiePull_SubSystem__) */
