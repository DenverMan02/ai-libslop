//
//  ZombiePirateSeagull.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEPIRATESEAGULL_H__
#define __ZOMBIEPIRATESEAGULL_H__

#include "Zombie.h"

class ZombiePirateSeagull : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePirateSeagull, Zombie, RtClass);
	
	inline void SetSplineFollower(bool i_followingSpline)
	{
		m_followingSpline = i_followingSpline;
	}
	
protected:
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual void onZombieInitialize() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	virtual bool hasHeadParticle() const override;
	virtual class BoardEntity* findTarget() override;
	
	virtual std::string getElectrocutePAMName() const override;
	
private:
	OVERRIDE_STATE_ONEXIT(ZombieState, Electrocute);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
	
    virtual void onApplyCondition(ZombieConditions i_condition) override;
	void playBirdLossAnimation(bool i_birdExplodes);
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	bool m_followingSpline;
	bool m_butteredWhileDying;
	bool m_hasHeadParticle;
};

#endif
