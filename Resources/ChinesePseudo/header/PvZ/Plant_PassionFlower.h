//
//  Plant_PassionFlower.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/1/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_PassionFlower_h
#define Plant_PassionFlower_h

#include <stdio.h>
#include "PlantFramework.h"
#include "PopAnimRig.h"
#include "PlantAnimRig.h"

#pragma mark - PassionFlowerProps

class PassionFlowerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PassionFlowerProps, PlantPropertySheet, RtClass);
    
    PassionFlowerProps()
    {
        PFStuckIntoGroundTime = 4.f;
        AvatarPFStuckIntoGroundTime = 6.f;
		SuperSkillTime = 6.0f;
		SuperSkillRate = 0.2f;
        Level2SkillRate = 0.3f;
        Level3SkillRate = 0.5f;
    }
    

    pvztime_t PFStuckIntoGroundTime;
    pvztime_t AvatarPFStuckIntoGroundTime;
	//copy by ColdSnapdragon
	float SuperSkillTime;
	float SuperSkillRate;
    float Level2SkillRate;
    float Level3SkillRate;
};

#pragma mark - PlantPassionFlower

typedef std::map<Zombie*, int> TargetMap;
#define MAX_SMALL_KIWI_COUNT_PER_ZOMBIE 2
#define MAX_SMALL_KIWI_COUNT_PER_PLANT 2

class PlantPassionFlower : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPassionFlower, PlantFramework, RtClass);
    
    virtual void    Initialize() override;
    void            UpdateActions() override;
    bool            CanApplyPlantfood() override;
    void            ApplyPlantfood() override;
    void            UpdatePlantfood() override;
    void            CancelPlantfood() override;
    virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	//add by level 5 skill
	void PlaySuperAnimation();
 	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    
protected:

private:
    Projectile*     normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
	Projectile*     superFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    Projectile* foodFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    float   getDegree(RtWeakPtr<BoardEntity> i_target);
    float getFoodDegree(ZombiePtr i_targetZombie, const SexyVector3& endPosition);
    SexyVector3 getFoodTargetPos(ZombiePtr i_targetZombie);

    
    bool m_isAvatarSecondAttack = false;
	bool m_isSuperSkillFired;
    bool m_isNeedRotation;

    bool m_bIsSKillPro;
};

#pragma mark - PlantAnimRig_PlantPassion

class PlantAnimRig_PlantPassion : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PlantPassion, PlantAnimRig, RtClass) {}
    
    bool PlayIdleLooped() override;
    //    bool PlayPlantFoodStart(int i_mainAnimPlayCount) override;
    bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
    std::string getPlantFoodMainAnimName() override;
    
private:
    
};

#endif /* Plant_PassionFlower_h */
