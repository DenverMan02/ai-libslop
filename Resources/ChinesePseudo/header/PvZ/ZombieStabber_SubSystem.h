//
//  ZombieStabber_SubSystem.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-6-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieStabber_SubSystem__
#define __PlantsVersusZombies2__ZombieStabber_SubSystem__

#include "GameSubSystem.h"
#include "GameEventMgr.h"
#include "RtReflectionDelegate.h"
#include "TimeMgr.h"

typedef RtReflectionDelegate<Delegate1<class Plant*> > ZombieStabbedCallback;

struct StabbedZombie
{
	SexyVector3 m_originalPos;
	SexyVector3 m_targetPos;
	SexyVector3 m_position;
	SexyVector3 m_velocity;
	SexyVector3 m_acceleration;
    
	RtWeakPtr<class Zombie> m_zombie;
    RtWeakPtr<class Plant>	m_plant;
    
	ZombieStabbedCallback    m_onStabbedCallback;
    
	bool        m_wasFlying;
};

class ZombieStabberSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieStabberSubSystem, GameSubSystem, RtClass);
	
    void LaunchZombie(class Zombie* i_zombie,
                      class Plant*  i_plant,
                      const Sexy::SexyVector3 &i_target,
                      float i_apexHeight,
                      pvztime_t i_timeToHit,
                      ZombieStabbedCallback i_stabbedCallback = ZombieStabbedCallback());
    
    void ReleaseZombie(class Zombie* i_zombie);
    
    SexyVector3 GetTargetPosition(class Zombie * i_zombie);
    bool IsStabbed(class Zombie * i_zombie);
    
    virtual void Update() override;
    
protected:
    virtual void registerForEvents() override;
    
private:
    void onZombieDestroyed(Zombie* i_zombie);
    void internalLaunchZombie(float i_apexHeight,
                              pvztime_t i_timeToHit,
                              StabbedZombie &i_stabbedZombie);
    
    StabbedZombie * findStabbedZombie(Zombie* i_forZombie);
	void removeStabbedZombie(Zombie* i_forZombie);
    
    
    std::vector<StabbedZombie> m_stabbedZombies;
    std::vector<StabbedZombie> m_newStabbedZombies;
    std::vector<RtWeakPtr<class Zombie> > m_deadZombies;
};



#endif /* defined(__PlantsVersusZombies2__ZombieStabber_SubSystem__) */
