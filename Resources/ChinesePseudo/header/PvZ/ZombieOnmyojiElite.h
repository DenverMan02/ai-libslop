/*
 * ZombieOnmyojiElite.h
 *
 *  Created on: 2021-7-14
 *      Author: zhousen
 */

#ifndef ZOMBIEONMYOJIELITE_H_
#define ZOMBIEONMYOJIELITE_H_

#include "EliteModule.h"

class ZombieEliteOnmyoji : public ZombieOnmyoji, public ZombieEliteModule
{
public:
	RT_CLASS_DEFINE(ZombieEliteOnmyoji, ZombieOnmyoji, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);

	void onZombieInitialize() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
    bool CanDropArm() const override { return false; }
	bool CanDropHead() const override { return false; }
    void takeBodyDamage(const DamageInfo& i_incomingDamage) override;

protected:
    void DoSpecialSkill();
    void addSmallWind(pvztime_t i_atTime) override;
    void addTornado(pvztime_t i_atTime) override;

protected:
    pvztime_t _specialSkillEndTime;// after this time , we should end special skill
    pvztime_t _skillCooldownTime;
    bool _isDoingSpecialSkill;// when we are in special skill , we should not turn to walk state
    bool _isFirstWaveState;// if is in first wave of special skill state
};

class ZombieEliteOnmyojiProps : public ZombieOnmyojiProps
{
public:
    RT_CLASS_DEFINE(ZombieEliteOnmyojiProps, ZombieOnmyojiProps, RtClass);

    ZombieEliteOnmyojiProps();

    pvztime_t SpecialSkillDuration;// skill time duration
    pvztime_t SkillCooldownTime;// skill cool down time
    int EliteAffectZombies;// heian wind system param
    int EliteMoveDistance;// heian wind system param
    int EliteTornadoCount;// how many tornado will create in speical skill
};

#endif /* ZOMBIEONMYOJIELITE_H_ */
