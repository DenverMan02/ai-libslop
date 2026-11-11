//
//  ZombieCavalryRider.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-3.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieCavalryRider__
#define __PlantsVersusZombies2__ZombieCavalryRider__

#include "ZombieBasic.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_CavalryRider : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_CavalryRider, ZombieAnimRig_Basic, RtClass);
	
	virtual bool PlayFlying();
	virtual bool PlayLand(AnimStoppedReflectionDelegate i_onAnimStopped);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    
    virtual const std::vector<std::string>& getFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
	virtual const std::vector<std::string>& getCrownLayerNames() override;

    virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
	virtual const std::string getDieAnimationName() override;
    virtual const std::string getStunAnimationName() override;
	virtual const std::string GetHeadParticleName() override;
	virtual const std::string GetArmParticleName() override;
    
	enum CavalryRiderAnimState
	{
		CAVALRYRIDER_ANIM_FLYING = ZOMBIEANIM_USERDEFINED,
	};
};

//////

STATE_ENUM_CHILD_BEGIN(ZombieStateCavalryRider, ZombieState)
ZS_CR_Flying,
ZS_CR_Landing,
ZS_CR_HitHead,
ZS_CR_Falling,
STATE_ENUM_END(ZombieStateCavalryRider);

class ZombieCavalryRider : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieCavalryRider, ZombieBasic, RtClass);
    
    ZombieCavalryRider();
	
	void SetFlyingDestinationWithTravelTime(const SexyVector3 i_destination, const float i_timeToTravel, const float i_apex = 64.0f, bool i_invincibleWhileInAir = false);
    
    void LandImmediately();
	
	virtual Sexy::Rect calcCollisionRect() override;
	int CalcProgressMeterHitpoints() const override;
    
protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, CavalryRiderFlying);
	DECLARE_STATE_FUNCTIONS(ZombieState, CavalryRiderLanding);
	DECLARE_STATE_FUNCTIONS(ZombieState, CavalryRiderHitHead);
	DECLARE_STATE_FUNCTIONS(ZombieState, CavalryRiderFalling);
	
	void onLandingAnimStopped(const std::string& i_animLabel);
	void onHitHeadAnimStopped(const std::string &i_animLabel);
    
	void onLanding(Zombie* i_zombie);
    
    void onEndCondition(ZombieConditions i_condition) override;
    
private:
	bool  m_invincibleWhileInAir;
	float m_fallVelocity;
	bool  m_animFailed;
};

#endif /* defined(__PlantsVersusZombies2__ZombieCavalryRider__) */
