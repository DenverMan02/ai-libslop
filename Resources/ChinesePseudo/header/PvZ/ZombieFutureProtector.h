//

//  ZombieFutureProtector.h

//  PlantsVersusZombies2

//

//  Created by Michael Fromwiller on 7/19/13.

//  Copyright (c) 2013 PopCap Games. All rights reserved.

//



#ifndef __PlantsVersusZombies2__ZombieFutureProtector__

#define __PlantsVersusZombies2__ZombieFutureProtector__



#include "DamageInfo.h"

#include "PlatformAutodetect.h"

#include "RtDb.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "ZombieMech.h"



STATE_ENUM_CHILD_BEGIN(ZombieState_FutureProtector, ZombieState_Mech)

	ZS_Protector_ActivatingShield,

	ZS_Protector_DeactivatingShield,

STATE_ENUM_END(ZombieState_FutureProtector)



class GridItemProtectorShield;



class ZombieFutureProtector : public ZombieMech

{

public:

	RT_CLASS_DEFINE(ZombieFutureProtector, ZombieMech, RtClass);



	virtual ~ZombieFutureProtector();



	void				OnShieldDestroyed();



	virtual void EMPeachStun(pvztime_t i_duration) override;

	void				activateShield();

	void				deactivateShield();

protected:



	virtual void		registerForEvents() override;



	DECLARE_STATE_FUNCTIONS(ZombieState, Protector_ActivatingShield);

	DECLARE_STATE_FUNCTIONS(ZombieState, Protector_DeactivatingShield);

	OVERRIDE_STATE_ONENTER(ZombieState, Walk);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	OVERRIDE_STATE_ONENTER(ZombieState, Die);

	void onDestroy() override;



	virtual void		onZombieInitialize() override;

	virtual void		onUpdate() override;

	virtual void		onLostHead() override;

	virtual void		onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

	virtual void		onFlicked(Zombie* i_zombie);

	virtual void		onApplyCondition(ZombieConditions i_condition) override;

    virtual void 		onChangeTeams(TeamFlags i_oldTeams, TeamFlags i_newTeams) override;



protected:

    

	void				onShieldActivateAnimationDone();

	void				onShieldDeactivateAnimationDone();



	virtual void		spawnShield();





	// Private member variables (serialized)



	int					m_damageState;

	bool				m_shieldIsActive;

	int32				m_shieldCount;

	pvztime_t			m_shieldReactivationDelay;

	RtWeakPtr<GridItemProtectorShield>	m_shieldPtr;

	bool				m_playedWalkSound;

	bool				m_stoppedWalkSound;

};



#endif /* defined(__PlantsVersusZombies2__ZombieFutureProtector__) */

