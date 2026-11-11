//
//  Zombie_Piano_Subsystem.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_PIANO_SUBSYSTEM_H__
#define __ZOMBIE_PIANO_SUBSYSTEM_H__

#include "TimeMgr.h"
#include "PvZ2IDs.h"
#include "GameSubSystem.h"
#include "GameEventMgr.h"
#include "Zombie.h"

struct ZombieDance
{
	float EndY;
	float Speed;
	ZombiePtr Zombie;
};

class ZombiePianoSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombiePianoSubsystem, GameSubSystem, RtClass);
	
 	virtual void Update() override;
	virtual void AssociateWithSubSystem(Sexy::RtWeakPtr<Sexy::RtObject> i_object);
    void ForceActivate();

protected:
	virtual void onInitialized() override;
	virtual void registerForEvents() override;
	virtual void onDestroy() override;

private:
	bool canDance();
	bool inIntro();
	void updateDancers();
	void populateDancers();
	void updateDanceAnimations(bool i_canDance);
	pvztime_t calculateDanceTime() const;

	void onZombieDestroyed(Zombie* i_zombie);

	std::vector<ZombiePtr> m_pianoZombies;
	pvztime_t m_nextDanceTime;

	std::vector<ZombieDance> m_dancingZombies;

	bool m_active;
    bool m_playingPiano;
};

#endif
