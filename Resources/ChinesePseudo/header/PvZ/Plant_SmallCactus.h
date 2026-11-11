//
//  Plant_SmallCactus.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-12-4.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantSmallCactus_h
#define PlantsVersusZombies2_PlantSmallCactus_h

#include "PlantFramework.h"
#include "Projectile.h"

enum SMALLCACTUSANIMSTATE
{
    SMALLCACTUS_WALK = PLANTANIM_USERDEFINED + 1,
    SMALLCACTUS_IDLE,
    SMALLCACTUS_COLLISION,
    SMALLCACTUS_UNDERATTACK
};

class PlantSmallCactus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSmallCactus, PlantFramework, RtClass);
    
    PlantSmallCactus() :m_NextStuckTime(0),m_NextDamageTime(0) {}
    virtual ~PlantSmallCactus() {}
    
public:
    virtual DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
    void StartWalk();
    void DestorySelf();

protected:
    bool CanApplyPlantfood() override;
	void Initialize() override;
    void UpdateActions() override;
    ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
private:
    void UpdateLogic();
    void UpdateAnimation();
    void UpdateSmallCactusPosition(float iSpeed);
    bool HaveDamage(BoardEntityPtr ptr);

private:
    pvztime_t m_NextStuckTime;
    pvztime_t m_NextDamageTime;
};

class SmallCactusPropertySheet : public PlantPropertySheet
{ 
public:   
    RT_CLASS_DEFINE(SmallCactusPropertySheet, PlantPropertySheet, RtClass);
    
    SmallCactusPropertySheet()
    : WalkSpeed(40),StuckCooldown(2)
    {}
    
    float WalkSpeed;
    float StuckCooldown;
};

class PlantAnimRig_SmallCactus : public PlantAnimRig
{
public:
    
    RT_CLASS_DEFINE(PlantAnimRig_SmallCactus, PlantAnimRig, RtClass);
    
    PlantAnimRig_SmallCactus() {}
    void PlayNormalRun();
    void PlayUnderAttack();
    
protected:
    void onAnimStopped() override;
    std::string getIdleAnimationName() override;
private:
    void PlayOnceCommon(SMALLCACTUSANIMSTATE pstate, const std::string& strLabel);
    void PlayLoopCommon(SMALLCACTUSANIMSTATE pstate, const std::string& strLabel);
    
};

#endif
