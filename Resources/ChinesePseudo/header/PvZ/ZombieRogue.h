/*
 * ZombieRogue.h
 *
 *  Created on: 2014-9-23
 *      Author: jianglc
 */

#ifndef ZOMBIEROGUE_H_
#define ZOMBIEROGUE_H_

#include "RtObject.h"
#include "StateMachine.h"
#include "Zombie.h"

namespace Message
{
    void CheckInvisibleZombie(Zombie* pZombie);
};

STATE_ENUM_CHILD_BEGIN(ZombieState_Rogue, ZombieState)
    ZS_ROGUE_Casting,
STATE_ENUM_END(ZombieState_Rogue)

class ZombieRogue : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieRogue, Zombie, RtClass);
    
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Casting);

	virtual void onDraw(class Sexy::Graphics* i_g) override;
    void OnInvisibleStateChanged(InvisibleState oldState, InvisibleState newState) override;
private:
	void onZombieInitialize() override;
	void onInvisibleAnimDone(const std::string& i_label);
	void CastInvisible();
	bool canCastInvisible();

	pvztime_t m_InvisibleStartTime = PVZ_EOT();
};


#endif /* ZOMBIEROGUE_H_ */
