//
//  Zombie_PVPCannon.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_PVPCANNON_H__
#define __ZOMBIE_PVPCANNON_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombiePVPCannonState, ZombieState)
    ZS_PCannon_Waiting, 
    ZS_PCannon_PrepForFire,
    ZS_PCannon_Firing,
    ZS_PCannon_BigFiring,
	ZS_PCannon_Explode,
STATE_ENUM_END(ZombiePVPCannonState);

class ZombiePVPCannon : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePVPCannon, Zombie, RtClass);
    
    virtual void ApplyZombieFood() override;
    virtual void CancelZombieFood() override;
    void        FireZombieImp();
    
protected:
    virtual void playDeathAnimation() override;
	virtual void onApplyCondition(ZombieConditions i_condition) override;
    bool isImmuneToShrinking() override { return true; }

private:
    // dispatch from parent class.
	void onPlaceOnBoard() override;
	void chooseDeathState(const DamageInfo& i_deathBlow) override;
    
    // states
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	DECLARE_STATE_FUNCTIONS(ZombieState, CannonWaiting);
	DECLARE_STATE_FUNCTIONS(ZombieState, CannonPrepForFire);
	DECLARE_STATE_FUNCTIONS(ZombieState, CannonFiring);
    DECLARE_STATE_FUNCTIONS(ZombieState, CannonBigFiring);
	DECLARE_STATE_FUNCTIONS(ZombieState, CannonExplode);
    
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

    DamageInfo modifyBodyDamage(const DamageInfo& i_incomingDamage) override;
	
	void			onPrepAnimStopped(const std::string& i_animLabel);
	void			onFiringAnimStopped(const std::string& i_animLabel);
	void			onExplodeAnimStopped(const std::string& i_animLabel);
	
	void			launchDeathImps();
    SexyVector3 getImpTargetPos();
	
///
	int				m_ammoRemaining;
    SexyVector3     m_startPos;
	SexyVector3		m_endPos;
    pvztime_t       m_waitTime;
	bool			m_outOfAmmoDeath;
    std::vector<SexyVector3> m_impTargetPosList;
	
	std::vector<ZombieConditionEntry> m_pendingConditions;

};

#endif //__ZOMBIE_PVPCANNON_H__
