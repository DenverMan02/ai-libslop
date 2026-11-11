//
//  ZombieProspector.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIESPROSPECTOR_H__
#define __ZOMBIESPROSPECTOR_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieProspectorState, ZombieState)
    ZS_Prospector_Blastoff,
	ZS_Prospector_Flying,
    ZS_Prospector_Landing,
    ZS_Prospector_Stunned,
STATE_ENUM_END(ZombieProspectorState);

class ZombieProspector : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieProspector, Zombie, RtClass);

protected:
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	virtual void onMowedDown() override;
	virtual DamageInfo modifyBodyDamage(const DamageInfo& i_receivedDamage) override;

private:
	DECLARE_STATE_FUNCTIONS(ZombieState, Blastoff);
	DECLARE_STATE_FUNCTIONS(ZombieState, Flying);
    DECLARE_STATE_FUNCTIONS(ZombieState, Landing);
    DECLARE_STATE_FUNCTIONS(ZombieState, Stunned);

	void onBlastoffEnd(const std::string& i_name);
	void onFlyingEnd(Zombie *i_zombie);
	void onLandingEnd(const std::string& i_name);

	bool m_dynamiteActive;
	bool m_countdownStarted;
	
	pvztime_t m_countdown;
	bool m_deferDamage;
	float m_deferredDamage;

	SexyVector2 m_lastParticlePosition;
};

#endif
