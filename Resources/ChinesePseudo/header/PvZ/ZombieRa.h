//
//  ZombieRa.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 5/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieRa_h
#define PlantsVersusZombies2_ZombieRa_h


#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Ra, ZombieState)
    ZS_RA_Claiming,
    ZS_RA_PoweringDown,
STATE_ENUM_END(ZombieState_Ra)

class ZombieRa : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieRa, Zombie, RtClass);
    
    void IncrementSunsCollected(const int i_sunCurrency) override;
    void IncrementSunsClaimed(const int i_sunCurrency) override;
    void DecrementSunsClaimed(const int i_sunCurrency) override;
    bool ShouldReleaseSun() override;
    bool CanClaimSun() override;
	SexyVector3 GetSunTarget() { return SexyVector3(-10.0, 0.0, 130.0) * GetConditionTracker().GetDrawScale(); }

	void onPlaceOnBoard() override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	virtual void registerForEvents() override;
    
private:  
    
	DECLARE_STATE_FUNCTIONS_EMPTY(ZombieState, RA_Claiming);
	DECLARE_STATE_FUNCTIONS_EMPTY(ZombieState, RA_PoweringDown);
	
    void onAnimationDone(StandaloneEffect* i_effect);
    
    virtual void onZombieInitialize() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    virtual void onLostHead() override;
	virtual void onMowedDown() override;
    virtual void onChangeTeams(TeamFlags i_oldTeam, TeamFlags i_newTeam) override;

    void onFlicked(Zombie* i_zombie);
    void releaseCollectedSuns(bool i_autocollect);
    
    int m_sunCurrencyCollected;
    int m_sunCurrencyClaimed;
    int m_sunsClaimed;
    
};


inline void ZombieRa::IncrementSunsCollected(const int i_sunCurrency)
{
     m_sunCurrencyCollected += i_sunCurrency;
}


#endif
