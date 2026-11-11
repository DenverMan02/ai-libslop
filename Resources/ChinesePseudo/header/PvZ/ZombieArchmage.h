//
//  ZombieArchmage.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-8-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieArchmage__
#define __PlantsVersusZombies2__ZombieArchmage__

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombiePropertySheet.h"
#include "RestrictionSet.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Archmage, ZombieState)
ZS_ARCHMAGE_Hypnotize,
STATE_ENUM_END(ZombieState_Archmage)

class ZombieArchmageProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieArchmageProps, ZombiePropertySheet, RtClass);
    
    ZombieArchmageProps()
    {
        
    }
    
    ValueRange TimeBeforeFirstHypnotize;
    ValueRange TimeBetweenHypnotize;
    PlantRestrictionSet TargetablePlantTypes;
    
    ProjectilePropertySheetPtr          Projectile;
};

class ZombieArchmage : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieArchmage, Zombie, RtClass);
    
protected:
    void onZombieInitialize() override;
	void onUpdate() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    OVERRIDE_STATE_UPDATE(ZombieState, Attack);
	DECLARE_STATE_FUNCTIONS(ZombieState, Hypnotize);

private:
    
    bool isValidHypnotizeTarget(Plant * plant);
    Plant * getValidHypnotizeTarget();
    
    void onHypnotizeAnimationDone(const std::string& i_animName);
    
private:
    
    pvztime_t m_nextHypnotizeTime = PVZ_EOT();
    
};

////////////

enum ZombieAnimRigState_Archmage
{
	ZOMBIEANIM_ARCHMAGE_HYPNOTIZE = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_Archmage : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Archmage, ZombieAnimRig, RtClass) {}
    
	bool StartHypnotize(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieArchmage__) */
