//
//  ZombieSkyCityTwinsPlane.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 06/12/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSkyCityTwinsPlane_h
#define PlantsVersusZombies2_ZombieSkyCityTwinsPlane_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "ZombieSkyCity.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"
#include "Zombie.h"
#include "Projectile.h"
#include "Effect_Barrage.h"

enum
{
    SuperDamage_Force_NoUpDown = -2,
    SuperDamage_None,
    SuperDamage_Up,
    SuperDamage_Down,
    SuperDamage_All,
};

class ZombieSkyCityTwinsPlaneProps : public ZombieSkyCityProps
{
public:
    RT_CLASS_DEFINE(ZombieSkyCityTwinsPlaneProps, ZombieSkyCityProps, RtClass);
    
public:
    std::vector<float>  DamageFactor;
    float               EatingSpeed;
    int                 GridInterval;
};

class ZombieSkyCityTwinsPlane : public ZombieSkyCity
{
public:
	RT_CLASS_DEFINE(ZombieSkyCityTwinsPlane, ZombieSkyCity, RtClass);
    ZombieSkyCityTwinsPlane() { }
    
    Effect_Barrage *    GetBarragePtr();
    Effect_Barrage *    GetBarragePtr2();
    void SetPooyanBossHP(float i_hp);
    
    virtual BoardEntity *findTarget() override;
    
protected:
    void onZombieInitialize() override;
    void eatTarget(BoardEntity* i_target) override;
    void TakeDamage(const DamageInfo& i_damage) override;
    
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Glide);
    
    OVERRIDE_STATE_ONENTER(ZombieState, Eat);
    OVERRIDE_STATE_ONEXIT(ZombieState, Eat);
    
    void InitBodyHealth();
    int ShouldDoSuperDamage(int iBody);
    void DoDamageHalf(float iRealHit, int iIndex);
    int CheckDamageValue(float iHeal);
    bool IsAnyPlantInGridInterval();
        
private:
    Effect_Barrage      m_barrage;
    Effect_Barrage      m_barrage2;
    std::vector<float> m_vHalfHealth;	
};

class ZombieAnimRig_TwinsPlane : public ZombieAnimRig_SkyCity
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_TwinsPlane, ZombieAnimRig_SkyCity, RtClass);
    void ShowLittleDamage(int iIndex);
    void ShowBigDamage(int iIndex);
    void VisibleDown(bool bVisible, int iIndex);
    
protected:
    void onPopAnimInitialized() override;
    const std::string getEatAnimationName() override;
};

#endif
