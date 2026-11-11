/*
 * ZombieRomanHealerElite.h
 *
 *  Created on: 2021-6-1
 *      Author: zhousen
 */

#ifndef ZOMBIEROMANHEALERELITE_H_
#define ZOMBIEROMANHEALERELITE_H_

#include "EliteModule.h"

class ZombieEliteRomanHealer : public ZombieRomanHealer, public ZombieEliteModule
{
public:
	RT_CLASS_DEFINE(ZombieEliteRomanHealer, ZombieRomanHealer, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);

	void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	void onUpdate() override;
    bool CanDropArm() const override { return false; }
	bool CanDropHead() const override { return false; }
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void takeBodyDamage(const DamageInfo& i_incomingDamage) override;

protected:
    void DoSpecialSkill();
    void PlayCureAnim();
	void onPopAnimStop(const std::string& command);

protected:
    pvztime_t _specialSkillEndTime;// after this time , we should end special skill
    pvztime_t _skillCooldownTime;
    bool _isDoingSpecialSkill;// when we are in special skill , we should not turn to walk state
    bool _isFirstWaveState;// if is in first wave of special skill state
};

class ZombieEliteRomanHealerProps : public ZombieRomanHealerProps
{
public:
    RT_CLASS_DEFINE(ZombieEliteRomanHealerProps, ZombieRomanHealerProps, RtClass);

    ZombieEliteRomanHealerProps();

    pvztime_t SpecialSkillDuration;// skill time duration
    pvztime_t SkillCooldownTime;// skill cool down time
    pvztime_t CureShieldTime;// shield time
};

#endif /* ZOMBIEROMANHEALERELITE_H_ */
