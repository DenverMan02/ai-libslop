//
//  Plant_Wintersweet.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/2/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_Wintersweet_h
#define Plant_Wintersweet_h

#include <stdio.h>
#include "PlantFramework.h"
#include "Projectile.h"
#include "PlantAnimRig.h"
#include "PlantPropertySheet.h"

#pragma mark - WintersweetProps

class WintersweetProps : public StarRateProps
{
public:
    RT_CLASS_DEFINE(WintersweetProps, StarRateProps, RtClass);
    
    WintersweetProps()
    {
        PlantFoodFlowerNum = 15;
        AvatarPlantFoodFlowerNum = 25;
    }
    
    int PlantFoodFlowerNum;
    int AvatarPlantFoodFlowerNum;
};

#pragma mark - PlantWintersweet

class PlantWintersweet : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantWintersweet, PlantFramework, RtClass);
    
    enum WintersweetState
    {
        WINTERSWEETSTATE_BEGIN = STATE_FRAMEWORK_BEGIN + 1,
        WINTERSWEETSTATE_COOLDOWN,
        WINTERSWEETSTATE_PREPARING = WINTERSWEETSTATE_COOLDOWN + 3,
        WINTERSWEETSTATE_READY,
    };
    
    void			Initialize() override;
    void            UpdateActions() override;
    bool			CanApplyPlantfood() override;
    void            ApplyPlantfood() override;
    void			CancelPlantfood() override;
    Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
private:
    virtual void    onAnimStoppedCallback(const std::string& name) override;
    Projectile*     normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    void            separatePlantfoodFlower();
    void            setState(uint i_plantState);
    
private:
    std::vector<int>        m_plantfood_flower_num;
    int32                   m_plantfood_index;
    pvztime_t               m_cooldown_time;
    bool                    m_isCooldowning;
    bool                    m_isLevelAttack;
};

#pragma mark - PlantAnimRig_Wintersweet

class PlantAnimRig_Wintersweet : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Wintersweet, PlantAnimRig, RtClass) {}
    
    void updateIdleAnimState(const std::string& i_color, int i_index);
    
    void playGrowAnim(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
    std::string getPlantFoodMainAnimName() override;
};

#pragma mark - WintersweetProjectileProps

class WintersweetProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(WintersweetProjectileProps, ProjectilePropertySheet, RtClass);
    
    WintersweetProjectileProps()
    {
        TinyProjectileNum = 5;
    }
    
    int TinyProjectileNum;
};

#pragma mark - WintersweetProjectile

class WintersweetProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(WintersweetProjectile, Projectile, RtClass);
    
    virtual void onProjectileInitialized() override;
    
    virtual bool OnCollideRoof() override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    
    void setLevelAttack(bool i_isLevelAttack);

    void setLevelAttackAnimColor(const std::string& i_color);
    
protected:
    bool m_isLevelAttack;
    
private:
    Projectile* LaunchTinyProjectile(int i_index);
    
    void setTinyProjectileVelocity(int i_index, Projectile* newProj);

};

#pragma mark - WintersweetTinyProjectile

class WintersweetTinyProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(WintersweetTinyProjectile, Projectile, RtClass);
    
    virtual void onProjectileInitialized() override;
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    
    void setLevelAttackAnimColor(const std::string& i_color);
    
    void setSpawnEntity(BoardEntity* i_entity) { m_spawnEntity = i_entity->GetPtr(); }
    
private:

    RtWeakPtr<BoardEntity> m_spawnEntity;
};

#endif /* Plant_Wintersweet_h */