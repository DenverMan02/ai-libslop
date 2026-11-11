//
//  ZombiePVPPirateCaptain.h
//  PlantsVersusZombies2
//
//  Created by Tiger.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePVPPirateCaptain_h
#define PlantsVersusZombies2_ZombiePVPPirateCaptain_h

#include "Zombie.h"
#include "StateMachine.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_PVPPirateCaptain, ZombieState)
    ZS_PVPPIRATECAPTAIN_BigCasting,
STATE_ENUM_END(ZombieState_PVPPirateCaptain)

class ZombiePvpPirateCaptainProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePvpPirateCaptainProps, ZombiePropertySheet, RtClass);
    
    ZombiePvpPirateCaptainProps()
    {
        ParrotCooldown = 8.0f;
        ParrotRetryCooldown = 2.0f;
    }
    
    float ParrotCooldown;
    float ParrotRetryCooldown;
};

class ZombiePVPPirateCaptain : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePVPPirateCaptain, Zombie, RtClass);
	
	void OnParrotReturned();
	bool HasBird() { return m_parrotShown; }
    
    virtual void ApplyZombieFood() override;
    virtual void CancelZombieFood() override;
	
protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	virtual void onLostHead() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastReceivedDamage) override;
    void onApplyCondition(ZombieConditions i_condition) override;
	
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    DECLARE_STATE_FUNCTIONS(ZombieState, BigCasting);
	
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onAnimationDone(const std::string& i_animName);
    
private:
	void checkForParrotRelease();
	void releaseParrot(class Plant* i_targetPlant);
	void showParrot(bool i_show);
	class Plant* findPlantForParrotToAttack();
    void findPlantForParrotToBigAttack();
	
	pvztime_t m_parrotLaunchTime;
	float m_parrotHealth;
	ZombiePtr m_parrotPtr;
	bool m_parrotShown;
    
    std::vector<ZombiePtr> m_parrotVec;
    Plant*    m_target1;
    Plant*    m_target2;
    Plant*    m_target3;
    int32     m_parrotCount;
	
	bool m_hasParrotLaunched;
};

#endif
