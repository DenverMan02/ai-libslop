//
//  ZombieMonkImp.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 14-1-2.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieMonkImp__
#define __PlantsVersusZombies2__ZombieMonkImp__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_MonkImp, ZombieState)
ZS_MI_Preparing,
ZS_MI_Jumping,
ZS_MI_Flying,
ZS_MI_Landing,
ZS_MI_Falling,
STATE_ENUM_END(ZombieState_MonkImp)

class ZombieMonkImp : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieMonkImp, Zombie, RtClass);

    virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;

protected:

    virtual void onUpdate() override;

    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual void onZombieInitialize() override;

	void onPreparingAnimStopped(const std::string& i_animLabel);
	void onJumpingAnimStopped(const std::string& i_animLabel);
	void onLandingAnimStopped(const std::string& i_animLabel);
	void onFallingAnimStopped(const std::string& i_animLabel);
	void onFlyingDieAnimStopped(const std::string& i_animLabel);
    void onLanding(Zombie* i_zombie);

	DECLARE_STATE_FUNCTIONS(ZombieState, Preparing);
	DECLARE_STATE_FUNCTIONS(ZombieState, Jumping);
	DECLARE_STATE_FUNCTIONS(ZombieState, Flying);
	DECLARE_STATE_FUNCTIONS(ZombieState, Landing);
	DECLARE_STATE_FUNCTIONS(ZombieState, Falling);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, MowedDown);
    virtual float GetAmberScale() override;
    
    bool isImmuneToShrinking() override;
    bool willDieToShrinking() override { return true; }
private:

	bool 	m_hasJumped = false;
	float	m_flySpeedByPixel = 0.0f;
};

#endif /* defined(__PlantsVersusZombies2__ZombieMonkImp__) */
