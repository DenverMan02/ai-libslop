//

//  ZombieFutureImp.h

//  PlantsVersusZombies2

//

//  Created by jsola on 11/2/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieFutureImp_h

#define PlantsVersusZombies2_ZombieFutureImp_h



#include <string>



#include "PopAnimRig.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "Zombie.h"

#include "ZombieAnimRig_Imp.h"

#include "ZombieImp.h"



namespace Sexy {

class Graphics;

}  // namespace Sexy



STATE_ENUM_CHILD_BEGIN(ZombieState_FutureImp, ZombieStateImp)

	ZS_FUTUREIMP_EMPeachStun,

STATE_ENUM_END(ZombieState_FutureImp)



class ZombieFutureImp : public ZombieImp

{

public:

	RT_CLASS_DEFINE(ZombieFutureImp, ZombieImp, RtClass);

	

	ZombieFutureImp()

	{

		m_stunDuration = -1.0f;

	}

	void SetIsFallingFromSpawn(bool i_x);

	

	void EMPeachStun(pvztime_t i_duration) override;

	bool IsStunned() const override;

    bool ShouldDrawShadow() const override;

	

	DECLARE_STATE_FUNCTIONS(ZombieState, FutureImpEMPeachStun);

	

protected:

	

	void onMechStunAnimEnd(const std::string& i_animLabelName);

	

	pvztime_t m_stunDuration;

	

	// Some future zombies do not have proper anims electrocute/ash

	bool allowElectrocuteState() const override

	{

		return false;

	}

	bool allowAshState() const override

	{

		return false;

	}

};



class ZombieAnimRig_FutureImp : public ZombieAnimRig_Imp

{

public:

	RT_CLASS_DEFINE(ZombieAnimRig_FutureImp, ZombieAnimRig_Imp, RtClass);

	ZombieAnimRig_FutureImp()

	{

		m_isFallingFromSky = false;

	}

	

	virtual bool PlayFlying() override;

	virtual bool PlayLand(AnimStoppedReflectionDelegate i_onAnimStopped) override;

	virtual bool PlayGetUp(AnimStoppedReflectionDelegate i_onAnimStopped) override;

	

	void SetIsFallingFromSpawn(bool i_x) { m_isFallingFromSky = i_x; }

	bool GetIsFallingFromSpawn() { return m_isFallingFromSky; }

	

	void PlayEMPeachStunStart();

	void PlayEMPeachStunIdle();

	void PlayEMPeachStunEnd();

	

private:

	bool m_isFallingFromSky;

	void onStunStartEnd(const std::string& i_animLabelName);

};

//  Summer Imp
class ZombieAnimRig_SummerImp : public ZombieAnimRig_FutureImp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_SummerImp, ZombieAnimRig_FutureImp, RtClass);

protected:
	const std::vector<std::string>& getHeadLayerNames() override;
};

// Childrensday Imp
class ZombieAnimRig_ChildrensdayImp : public ZombieAnimRig_FutureImp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ChildrensdayImp, ZombieAnimRig_FutureImp, RtClass);

protected:
	const std::vector<std::string>& getHeadLayerNames() override;
};
#endif

