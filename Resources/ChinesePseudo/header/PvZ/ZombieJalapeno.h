/*
 * ZombieJalapeno.h
 *
 *  Created on: 2020-10-21
 *      Author: zhousen
 */

#ifndef ZOMBIEJALAPENO_H_
#define ZOMBIEJALAPENO_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "GameSubSystem.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

namespace Message
{
    void NotifySelfExplodeJalapeno();
}

/// 
/// zombie anim rig
///
class ZombieAnimRig_Jalapeno : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Jalapeno, ZombieAnimRig_Basic, RtClass);

private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
};

///
/// zombie jalapeno props
///
class ZombieJalapenoProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieJalapenoProps, ZombiePropertySheet, RtClass);
};

///
/// state
///
STATE_ENUM_CHILD_BEGIN(ZombieState_Jalapeno, ZombieState)
    ZS_Jalapeno_Explode,// touch plants and explode
STATE_ENUM_END(ZombieState_Jalapeno)

///
/// zombie jalapeno
///
class ZombieJalapeno : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieJalapeno, Zombie, RtClass);

    OVERRIDE_STATE_ONENTER(ZombieState, Eat);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    DECLARE_STATE_FUNCTIONS(ZombieState, Explode);

    void onZombieInitialize() override;
    ZombieParticle* DropHead() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

private:
    void Explode();

private:
	pvztime_t m_explodedAtTime;
	int m_lastExplosionPropagationDistance;
	std::vector<BoardEntity*> m_damagedEntities;// only do fatal attack once entities
};


#endif /* ZOMBIEJALAPENO_H_ */
