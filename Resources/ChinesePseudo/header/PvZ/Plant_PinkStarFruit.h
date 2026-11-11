//
//  Plant_PinkStarFruit.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/4/29.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_PinkStarFruit_h
#define Plant_PinkStarFruit_h

#include <stdio.h>
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "PlantPropertySheet.h"

class Zombie;

#pragma mark - PinkStarFruitProps

class PinkStarFruitProps : public StarRateProps
{
public:
    RT_CLASS_DEFINE(PinkStarFruitProps, StarRateProps, RtClass);
    
    PinkStarFruitProps()
    {
        PlantFoodProjectileCount = 1;
        FireHeight = 0.32;
        SuperStarRate = 1.0f;
    }
    
    int PlantFoodProjectileCount;
    float FireHeight;
    float SuperStarRate;

};

#pragma mark - PlantPinkStarFruit

class PlantPinkStarFruit : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPinkStarFruit, PlantFramework, RtClass);
    
    enum FruitState
    {
        STATE_NORMAL,
        STATE_ROTATED,
    };
    
    virtual void 			Initialize() override;
    virtual bool			CanApplyPlantfood() override;
    virtual void			ApplyPlantfood() override;
    virtual void			UpdatePlantfood() override;
    virtual void			CancelPlantfood() override;
    bool                    FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual Projectile*	    Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    ZombiePtr		FindTargetZombie(Rect& i_rect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    GridItemPtr		FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;
    
private:
    void setState(FruitState i_state);
    
    Projectile* fireProjectile(int i_index, ProjectilePropertySheetPtr i_projectileType, bool i_isSuper );
    BoardEntityPtr FindTargetInNormalState(PVZDB::TableIndex i_itemTableIndex);
    BoardEntityPtr FindTargetInRotateState(PVZDB::TableIndex i_itemTableIndex);
    virtual void    onAnimStoppedCallback(const std::string& name) override;
    
    int pickProjectileIndex(bool i_isPlantfood, bool i_isSuper);
    
    pvztime_t m_turnTime;
    float m_rotation;
    float m_rotateInterval;
    pvztime_t m_shotsPerSecond;
    pvztime_t m_startTime;
    int m_shotsFired;
    int m_shotTotal;
    
    //For Rotation
    FruitState m_currentState;
    bool m_needRotate;
    bool m_startPlantfoodFire;
    float m_newAvatarBoostSpecial;
};

#pragma mark - PlantAnimRig_PinkStarFruit

class PlantAnimRig_PinkStarFruit : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PinkStarFruit, PlantAnimRig, RtClass);
    
    enum FruitAnimState
    {
        STATE_NORMAL,
        STATE_ROTATED,
    };
    
    void setAnimState(FruitAnimState i_state) { m_animState = i_state; }
    bool playRotate(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

protected:
    void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;

private:
    FruitAnimState m_animState;
};

#endif /* Plant_PinkStarFruit_h */
