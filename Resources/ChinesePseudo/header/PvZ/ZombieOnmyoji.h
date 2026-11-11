/*
 * ZombieOnmyoji.h
 *
 *  Created on: 2021-3-15
 *      Author: zhousen
 */

#ifndef ZOMBIEONMYOJI_H_
#define ZOMBIEONMYOJI_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

///
/// zombie onmyoji props
///
class ZombieOnmyojiProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieOnmyojiProps, ZombiePropertySheet, RtClass);

    int AffectZombies;// heian wind system param
    int MoveDistance;// heian wind system param
    pvztime_t MoveTime;// heian wind system param
    pvztime_t AddSummonWindDeltaTime;// summon wind delta time
    pvztime_t SummonChargeTimeThreshold;// summon tornado charge time
};

///
/// zombie state
///
STATE_ENUM_CHILD_BEGIN(ZombieState_Onmyoji, ZombieState)
    ZS_Onmyoji_Summon, // summon tornado
STATE_ENUM_END(ZombieState_Onmyoji)
 
///
/// zombie onmyoji
///
class ZombieOnmyoji : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieOnmyoji, Zombie, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Summon);

	void onZombieInitialize() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onUpdate() override;

protected:
    void onAnimStop(const std::string& i_animCommand);
    virtual void addSmallWind(pvztime_t i_atTime);
    virtual void addTornado(pvztime_t i_atTime);

protected:
    pvztime_t _summonStartTime;// summon start time
    pvztime_t _summonChargeTimeThreshold;// summon charge time
    TimeLine _summonTimeline;// the summon timeline
};

///
/// zombie onmyoji animrig
///
class ZombieAnimRig_HeianOnmyoji : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_HeianOnmyoji, ZombieAnimRig_Basic, RtClass) {}

protected:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
};


#endif /* ZOMBIEONMYOJI_H_ */
