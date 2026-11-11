//
//  ZombieQigong.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIES_QIGONG_H__
#define __ZOMBIES_QIGONG_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieQigongState, ZombieState)
	ZS_Qigong_Pull,
STATE_ENUM_END(ZombieQigongState);

class ZombieQigong : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieQigong, Zombie, RtClass);

    void startPullAnimation();
    bool isCdAvailable;
    
protected:
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
    void pullPlant(Plant* i_plant, bool canFly);
    virtual ZombieParticle* DropArm() override;
private:

	DECLARE_STATE_FUNCTIONS(ZombieState, Pull);

	void startPulling(Zombie* z);
    void onPullAnimationEnd(Zombie* z);

	bool m_dynamiteActive;
	bool m_countdownStarted;
	
	pvztime_t m_countdown;
	pvztime_t m_startPlayingPullAnimTime;
};

#endif
