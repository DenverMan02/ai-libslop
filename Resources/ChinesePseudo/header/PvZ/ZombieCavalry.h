//
//  ZombieCavalry.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieCavalry__
#define __PlantsVersusZombies2__ZombieCavalry__

#include "ZombieAnimRig.h"
#include "Zombie.h"
#include "GridItemGravestone.h"
#include "ZombieCavalryRider.h"
#include "GravestoneAnimRig.h"

class ZombieAnimRig_Cavalry : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Cavalry, ZombieAnimRig, RtClass);
    
	ZombieAnimRig_Cavalry();
	virtual ~ZombieAnimRig_Cavalry();
	
	bool PlayPawing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	//bool PlayPreRun(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayRearing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
	SexyVector2 GetHeadOffset() override;
    
	void SetDamageState(const int i_state);
	void SetRunning(bool i_running);
	void HideRider();
    
protected:
	virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
	virtual const std::string getDieAnimationName() override;
    
private:
	bool m_running;
    
	void onPopAnimInitialized() override;
};

//////////

STATE_ENUM_CHILD_BEGIN(ZombieCavalryState, ZombieState)
ZS_CAVALRY_Entering,
ZS_CAVALRY_Pawing,
//ZS_CAVALRY_PreRun,
ZS_CAVALRY_Running,
ZS_CAVALRY_Rearing,
STATE_ENUM_END(ZombieCavalryState);

class ZombieCavalry : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieCavalry, Zombie, RtClass);
    
    std::string getElectrocutePAMName() const override;
    
    Sexy::Rect CalcZombieAttackRect() override;
    
    bool canPullDown();
    ZombieCavalryRider * takePullDown();
	bool GetRider() {return m_IsRider;}
protected:
    
    bool canAttack() override;
    
    SexyVector3 GetStunnedEffectOffset() const override;
    
    void onEndCondition(ZombieConditions i_condition) override;
    virtual float GetAmberScale() override;
    void applyButterGraphicalEffects() override;
protected:
	// states
	OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_ONENTER(ZombieState, Attack);
	OVERRIDE_STATE_ONEXIT(ZombieState, Electrocute);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
	DECLARE_STATE_FUNCTIONS(ZombieState, Entering);
	DECLARE_STATE_FUNCTIONS(ZombieState, Pawing);
	//DECLARE_STATE_FUNCTIONS(ZombieState, PreRun);
	DECLARE_STATE_FUNCTIONS(ZombieState, Running);
	DECLARE_STATE_FUNCTIONS(ZombieState, Rearing);
	
    
	// anim callbacks
	void onPawingAnimDone(const std::string &i_animLabel);
	//void onPreRunAnimDone(const std::string &i_animLabel);
	void onRearingAnimDone(const std::string &i_animLabel);
    void onRiderAttackAnimDone(const std::string &i_animLabel);
	void onWalkAnimContinued(const std::string&, const std::string&, int);
    
	virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;
    
	// overridden from zombie base class
	virtual void onElectrocuted() override;
    
	virtual void onPlaceOnBoard() override;
	virtual void onUpdate() override;
    
	virtual void launchImp();
    
	Rect calcBuckRect();
    Rect calcGunRect();
    
	bool m_hitPlant;
	bool m_walkCycled;
	int m_damageState;
    
    bool m_IsRider;
};

///////

class GridItemCavalryGunProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemCavalryGunProps, GridItemGravestonePropertySheet, RtClass);
};

class GridItemCavalryGun : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemCavalryGun, GridItemGravestone, RtClass);
    
    void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    
	void CalcDamageState();
    
protected:
	void onGridItemInitialize() override;
};

class CavalryGunAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(CavalryGunAnimRig, GravestoneAnimRig, RtClass);
    
	void PlayFlip();
	void PlayStationary();
};

#endif /* defined(__PlantsVersusZombies2__ZombieCavalry__) */
