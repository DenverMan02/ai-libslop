//
//  ZombieBlower_SubSystem.h
//  PlantsVersusZombies2
//
//  Created by aseavy on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  A subsystem that blows zombies off the screen
//

#ifndef __ZOMBIE_BLOWER_SUBSYSTEM_H__
#define __ZOMBIE_BLOWER_SUBSYSTEM_H__

#include "GameSubSystem.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "RtReflectionDelegate.h"

typedef RtReflectionDelegate<Delegate1<class Zombie*> > ZombieBlownAwayCallback;

struct BlownZombie
{
	SexyVector3					m_velocity;
	SexyVector3					m_acceleration;
	RtWeakPtr<class Zombie>		m_zombie;
	RtWeakPtr<class Plant>		m_plant;
	ZombieBlownAwayCallback		m_onBlownAwayCallback;
};

class ZombieBlowerSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieBlowerSubSystem, GameSubSystem, RtClass);
    void BlowZombie(class Plant* i_plant, class Zombie* i_zombie, float i_windAccel, float i_upPercent, ZombieBlownAwayCallback i_blownAwayCallback = ZombieBlownAwayCallback());
    
    virtual void Update() override;
    
protected:
	virtual void registerForEvents() override;
    
private:
    void onZombieDestroyed(Zombie* i_zombie);
	void onBlowGriItem(int row = -1);
	void onBlowGridItemAll();
    void internalBlowZombie(float i_apexHeight, float i_windAccel, BlownZombie &i_blownZombie);
    
    std::vector<BlownZombie> m_blownZombies;
    std::vector<BlownZombie> m_newBlownZombies;
    std::vector<RtWeakPtr<class Zombie> > m_deadZombies;
    bool m_isRiftThemeHeavyBalloonVaild;
};

namespace Message
{
    void ZombieBlown(Zombie* i_zombie);
}

#endif
