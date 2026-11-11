//

//  ZombieMechDisco.h

//  PlantsVersusZombies2

//

//  Created by jsola on 8/15/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieMechDisco_h

#define PlantsVersusZombies2_ZombieMechDisco_h



#include <vector>



#include "DamageInfo.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "Zombie.h"

#include "ZombieMech.h"

#include "GameSubSystem.h"



STATE_ENUM_CHILD_BEGIN(ZombieMechDiscoState, ZombieState_Mech)

	ZS_DiscoMech_Dancing,

	ZS_DiscoMech_DanceCooldown,

STATE_ENUM_END(ZombieMechDiscoState);



class ZombieMechDisco : public ZombieMech

{

public:

	RT_CLASS_DEFINE(ZombieMechDisco, ZombieMech, RtClass);



protected:

	OVERRIDE_STATE_ONENTER(ZombieState, Walk);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	DECLARE_STATE_FUNCTIONS(ZombieState, Dancing);
	

	void onPlaceOnBoard() override;

	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

	void onMowedDown() override;

	void addDancers();
	virtual void updateDancers();
	std::vector<ZombiePtr> m_dancers;
    float m_countdown = 0.0f;

private:


    DECLARE_STATE_FUNCTIONS(ZombieState, DanceCooldown);	

	void updateDancerPositions(float i_timeLeft);

	void killDancers();

};



class ZombieMechDiscoSubsystem : public GameSubSystem

{

public:

	RT_CLASS_DEFINE(ZombieMechDiscoSubsystem, GameSubSystem, RtClass);

	

	// Override functions from GameSubSystem

    

	virtual void		Update() override;

	void		AssociateWithSubSystem(Sexy::RtWeakPtr<Sexy::RtObject> i_object);

	

protected:

	

	void		registerForEvents() override;

	

private:

	

	void				onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void 				onZombieDestroyed(Zombie* i_zombie);

	void				onLevelEnded();

	

	void				updateAudioTracks();

	

	// Serialized

	

	std::vector<RtWeakPtr<ZombieMechDisco> >	m_discoMechZombies;

	

	// Not serialized

	

	bool								m_playingDiscoMusic;

	bool								m_firstMechEntered;

	bool								m_boardActive;

};



#endif

