//
//  ZombieRocket.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-22.
//  Copyright (c) 2013年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieRocket__
#define __PlantsVersusZombies2__ZombieRocket__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Rocket, ZombieState)
ZS_RK_Flying,
ZS_RK_DroppingFromSky,
STATE_ENUM_END(ZombieState_Rocket)

class ZombieRocket : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieRocket, Zombie, RtClass);
    
    void Land();
    
    virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
    virtual bool CollidesWithFlying() const override { return true; }
    bool ShouldDrawShadow() const override { return false; }
    
    bool m_HaveQTE = false;
	
protected:
    
    virtual void onLostArm() override;
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    
    virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	
	DECLARE_STATE_FUNCTIONS(ZombieState, Flying);
    DECLARE_STATE_FUNCTIONS(ZombieState, DroppingFromSky);
    
    virtual void onEnterState_MowedDown(ZombieState i_oldState) override;
    virtual void updateState_MowedDown() override;
    virtual void onExitState_MowedDown(ZombieState i_newState) override;
    
	void onRocketLandAnimDone(const std::string& i_animLabel);
    void onRocketFlyDieAnimDone(const std::string& i_animLabel);
    
    bool willDieToShrinking() override { return true; }

private:
    pvztime_t m_timeFlying = PVZ_EOT();
};

#endif /* defined(__PlantsVersusZombies2__ZombieRocket__) */
