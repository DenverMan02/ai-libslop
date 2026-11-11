//

//  ZombieFutureJetpack.h

//  PlantsVersusZombies2

//

//  Created by jsola on 10/5/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieFutureJetpack_h

#define PlantsVersusZombies2_ZombieFutureJetpack_h



#include <string>



#include "BoardEntity.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "Zombie.h"

#include "dtypes.h"



STATE_ENUM_CHILD_BEGIN(ZombieState_Jetpack, ZombieState)

    ZS_JP_DroppingFromSky,

	ZS_JP_JumpingOverEntity,

STATE_ENUM_END(ZombieState_Jetpack)



class ZombieFutureJetpack : public Zombie

{

public:

	RT_CLASS_DEFINE(ZombieFutureJetpack, Zombie, RtClass);

	

    virtual bool    canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;

	virtual void	onZombieInitialize() override;

	

	void			DropFromSky();



	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	

	DECLARE_STATE_FUNCTIONS(ZombieState, DroppingFromSky);

	DECLARE_STATE_FUNCTIONS(ZombieState, JumpingOverEntity);

	

protected:

	virtual void	onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	virtual Sexy::Rect calcCollisionRect() override;



	// Some future zombies do not have proper anims electrocute/ash

	virtual bool allowElectrocuteState() const override

	{

		return false;

	}

	virtual bool allowAshState() const override

	{

		return false;

	}

	

private:

	bool			shouldFlyOverEntity(BoardEntity* i_entity);

	bool			shouldBeUp();



	void			onDropAnimDone(const std::string& i_animLabel);

	void			onFlyUpAnimDone(const std::string& i_animLabel);

	void			onFlyDownAnimDone(const std::string& i_animLabel);

	

	bool			m_jumpMovement = false;

};



#endif

