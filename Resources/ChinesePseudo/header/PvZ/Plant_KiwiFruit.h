//
//  Plant_KiwiFruit.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/1/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_KiwiFruit_h
#define Plant_KiwiFruit_h

#include <stdio.h>
#include "PlantFramework.h"
#include "PopAnimRig.h"
#include "PlantAnimRig.h"

#pragma mark - KiwiFruitProps

class KiwiFruitProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(KiwiFruitProps, PlantPropertySheet, RtClass);
    
    KiwiFruitProps()
    {
        NormalAliveTime = 3.f;
        LevelAliveTime = 5.f;
        NormalAttackInterval = 0.5f;
        LevelAttackInterval = 0.333f;
        PFStuckIntoGroundTime = 4.f;
        AvatarPFStuckIntoGroundTime = 6.f;
		SuperSkillTime = 6.0f;
		SuperSkillRate = 0.2f;
    }
    
    float NormalAliveTime;
    float LevelAliveTime;
    float NormalAttackInterval;
    float LevelAttackInterval;
    pvztime_t PFStuckIntoGroundTime;
    pvztime_t AvatarPFStuckIntoGroundTime;
    std::vector<std::string> ZombieStuckBlacklist;
	//copy by ColdSnapdragon
	float SuperSkillTime;
	float SuperSkillRate;
};

#pragma mark - PlantKiwiFruit

typedef std::map<Zombie*, int> TargetMap;
#define MAX_SMALL_KIWI_COUNT_PER_ZOMBIE 2
#define MAX_SMALL_KIWI_COUNT_PER_PLANT 2

class PlantKiwiFruit : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantKiwiFruit, PlantFramework, RtClass);
    
    virtual void    Initialize() override;
    void            UpdateActions() override;
    bool            CanApplyPlantfood() override;
    void            ApplyPlantfood() override;
    void            UpdatePlantfood() override;
    void            CancelPlantfood() override;
    virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual void    DoSpecial(int i_extraParam) override;

	//add by level 5 skill
	void PlaySuperAnimation();
 	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	void reduceSmallKiwiCount();
    
protected:

private:
    Projectile*     normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
	Projectile*     superFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    void dealPlantfoodDamage();
    bool zombieIsBlacklisted(const Zombie* i_zombie) const;
    void tossStuckZombies();

    
    bool m_isAvatarSecondAttack = false;
    pvztime_t m_tossZombieTimer = PVZ_EOT();
    std::vector<ZombiePtr> m_hitZombies;
	bool m_isSuperSkillFired;
	int m_smallKiwiCount;
public:
	static TargetMap m_targetList;
};

#pragma mark - PlantAnimRig_KiwiFruit

class PlantAnimRig_KiwiFruit : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_KiwiFruit, PlantAnimRig, RtClass) {}
    
    bool PlayIdleLooped() override;
    //    bool PlayPlantFoodStart(int i_mainAnimPlayCount) override;
    bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
    std::string getPlantFoodMainAnimName() override;
    
private:
    
};

#endif /* Plant_KiwiFruit_h */
