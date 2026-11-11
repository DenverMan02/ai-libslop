//
//  ZombieAkinndo.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 5/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieHeianAkinndo_h
#define PlantsVersusZombies2_ZombieHeianAkinndo_h


#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"

enum ZombieAnimRigState_Akinndo
{
	ZOMBIEANIM_AKINNDO_POWERON = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_AKINNDO_POWER,
	ZOMBIEANIM_AKINNDO_POWEROFF,
};

class ZombieHeianAkinndoProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieHeianAkinndoProps, ZombiePropertySheet, RtClass);
	
	ZombieHeianAkinndoProps()
	{
		MaxClaimedPlantfood = 2;
	}
	  
	int MaxClaimedPlantfood;
    int ProjectileBounceHeight;
    float ProjectileBounceTime;
    int ProjectileBounceDistance;
    
    std::vector<ProjectilePropertySheetPtr> BounceableProjectiles;
};

STATE_ENUM_CHILD_BEGIN(ZombieState_Akinndo, ZombieState)
    ZS_Akinndo_Claiming,
    ZS_Akinndo_PoweringDown,
STATE_ENUM_END(ZombieState_Akinndo)

class ZombieHeianAkinndo : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieHeianAkinndo, Zombie, RtClass);
    
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;

    void IncrementPlantfoodCollected();
    void IncrementPlantfoodClaimed();
    void DecrementPlantfoodClaimed();

    bool ShouldReleasePlantfood();
    bool CanClaimPlantfood();
    
	SexyVector3 GetPlantfoodTarget() { return SexyVector3(-10.0, 0.0, 130.0) * GetConditionTracker().GetDrawScale(); }
	
protected:
	virtual void registerForEvents() override;
    
private:  
    
	DECLARE_STATE_FUNCTIONS_EMPTY(ZombieState, Akinndo_Claiming);
	DECLARE_STATE_FUNCTIONS_EMPTY(ZombieState, Akinndo_PoweringDown);
	
    void onAnimationDone(StandaloneEffect* i_effect);
    
    virtual void onZombieInitialize() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    virtual void onLostHead() override;
	virtual void onMowedDown() override;
    virtual void onChangeTeams(TeamFlags i_oldTeam, TeamFlags i_newTeam) override;

    void onFlicked(Zombie* i_zombie);
    void releaseCollectedPlantfood(bool i_autocollect);
    
    int m_plantfoodCollected;
    int m_plantfoodClaimed;
};

class ZombieAnimRig_HeianAkinndo : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_HeianAkinndo, ZombieAnimRig, RtClass) {}
    
	// Ra specific functionality
	virtual bool StartPowerSuck();
	virtual bool StopPowerSuck(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	virtual SexyVector2 GetHeadOffset() override;
	
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	virtual void onAnimStopped() override;
};

#endif
