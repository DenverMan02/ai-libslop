//

//  ZombieMech.h

//  PlantsVersusZombies2

//

//  Created by jsola on 10/11/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieMech_h

#define PlantsVersusZombies2_ZombieMech_h



#include <string>



#include "RtDb.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "Zombie.h"



STATE_ENUM_CHILD_BEGIN(ZombieState_Mech, ZombieState)

    ZS_MECH_EMPeachStun,

STATE_ENUM_END(ZombieState_Mech)



class ZombieMech : public Zombie

{

public:

	RT_CLASS_DEFINE(ZombieMech, Zombie, RtClass);



	void onDestroy() override;

	virtual void EMPeachStun(pvztime_t i_duration) override;

	bool IsStunned() const override;



	DECLARE_STATE_FUNCTIONS(ZombieState, EMPeachStun);



protected:

	void onUpdate() override;

	void onPlaceOnBoard() override;



	// Some future zombies do not have proper anims electrocute/ash

	bool allowElectrocuteState() const override

	{

		return false;

	}

	bool allowAshState() const override

	{

		return false;

	}

	DamageTypeFlags getEatingDamageType() const override;



	void onMechStunAnimEnd(const std::string& i_animLabelName);



	pvztime_t m_stunDuration;

	RtWeakPtr<class Effect_PopAnim> m_stunDamageEffect;

	int m_damageState;

};



#endif

