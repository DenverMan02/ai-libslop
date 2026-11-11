//
//  ZombiePVPSkill.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.29
//  Copyright (c) 2015Äê PopCap Games. All rights reserved.
//

#ifndef __ZombiePVPSkill_H__
#define __ZombiePVPSkill_H__

#include "Zombie.h"
#include "Projectile.h"
#include "Effect_Barrage.h"
#include "ZombieAnimRig_Basic.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_PVPSkill, ZombieState)
	ZS_PVPSkill_Playing,
STATE_ENUM_END(ZombieState_PVPSkill)

class ZombiePVPSkill : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePVPSkill, Zombie, RtClass);
	ZombiePVPSkill();
	virtual ~ZombiePVPSkill();
    int CalcRenderOrder() const override;
    bool ShouldDrawShadow() const override;
    void CreateZombieLevelEffect(bool i_street) override;
protected:
	virtual bool		allowElectrocuteState() const override { return false; }
    virtual bool		allowAshState() const override { return false; }
	virtual void		onZombieInitialize() override;
	virtual void		onPlaceOnBoard() override;
	virtual void		onUpdate() override;
	virtual class   BoardEntity* findTarget() override;
	
	virtual void		onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	// use playing state for all skills
	virtual void		onEnterState_Playing(ZombieState i_oldState);
	virtual void		updateState_Playing();
	virtual void		onExitState_Playing(ZombieState i_newState);
    virtual void        CreateArenaSpawnEffect() override {}
    
protected:
    
};

class ZombiePVPSkillProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePVPSkillProps, ZombiePropertySheet, RtClass);

	ZombiePVPSkillProps();

	//float SpeedSlide;
    int                 SkillScope = 0;
    float               SkillRadius = 1.0f;
    float               InitEnergyCost = 0.0f;
    float               MaxEnergyCost = 0.0f;
    std::vector<int>    UpgradeCoin;
    std::vector<int>    UpgradeBaseLevel;
    std::vector<int>    UpgradeTime;
    std::vector<float>  ReduceCost;
    float   GetReduceCost(int level);
    int     GetMaxLevel();
};

class ZombieAnimRig_PVPSkill : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_PVPSkill, ZombieAnimRig_Basic, RtClass);
    
protected:

};


#endif
