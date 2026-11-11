//
//  ZombieImp.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieImp_h
#define PlantsVersusZombies2_ZombieImp_h

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieStateImp, ZombieState)
	ZS_I_Flying,
	ZS_I_Landing,
	ZS_I_HitHead,
	ZS_I_Falling,
	ZS_I_GettingUp,
STATE_ENUM_END(ZombieStateImp);

class ZombieImp : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieImp, Zombie, RtClass);

	ZombieImp();
	
	virtual void SetFlyingDestinationWithTravelTime(const SexyVector3 i_destination, const float i_timeToTravel, const float i_apex = 64.0f, bool i_invincibleWhileInAir = false);

    void LandImmediately();
	
	virtual Sexy::Rect calcCollisionRect() override;
	int CalcProgressMeterHitpoints() const override;

	void SetGetsUpFromLanding(bool i_getsUp);
	void SetAshAnim(const std::string &i_ashAnim);
    GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }

protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, ImpFlying);
	DECLARE_STATE_FUNCTIONS(ZombieState, ImpLanding);
	DECLARE_STATE_FUNCTIONS(ZombieState, ImpHitHead);
	DECLARE_STATE_FUNCTIONS(ZombieState, ImpFalling);
	DECLARE_STATE_FUNCTIONS(ZombieState, ImpGettingUp);
	
	virtual void onLandingAnimStopped(const std::string& i_animLabel);
	virtual void onHitHeadAnimStopped(const std::string &i_animLabel);
	virtual void onGetUpAnimStopped(const std::string &i_animLabel);

	void vasebreakerKillBullrider(Zombie* i_zombie);
	void onTurnedToAsh() override;
	void onLanding(Zombie* i_zombie);

	virtual void onPreImpFlight() {}
    virtual void onLandingSuccess() {}

	virtual void onEndCondition(ZombieConditions i_condition) override;

    SexyVector3 GetStunnedEffectOffset() const override;
    
    bool isImmuneToShrinking() override;
	bool willDieToShrinking() override { return true; }

	virtual std::string getElectrocutePAMName() const override;
    virtual float GetAmberScale() override;
private:
	bool m_invincibleWhileInAir;
	bool m_getsUpFromLanding;
	float m_fallVelocity;
	bool m_animFailed;
	std::string m_ashAnim;
};

#endif
