//
//  Plant_Dratodil.h
//  PlantsVersusZombies2
//
//  Created by Andrew Min on 11/23/2020.
//  Copyright (c) 2020 PopCap Games. All rights reserved.
//

#ifndef __Plant_Draftodil__
#define __Plant_Draftodil__

#include <string>

#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "PlantPropertySheet.h"
#include "ZombieTosser_SubSystem.h"

class DraftodilProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(DraftodilProps, PlantPropertySheet, RtClass);
    
    DraftodilProps()
    : FlyingZombieBlowingSpeed{100.f}
    , FlyingZombieUpAccelerationFactor{0.f}
    , SlowdownPercentage{0.5f}
    , SlowDuration{3.f}
    , BlowDuration{3.f}
    , WindGiveHelpLimit(0)
    , PFShots(0)
    , ExtraPFShots(0)
    , LightweightZombieFlickChance{0.25f}
    , LightweightZombieFlickChance2{0.4f}
    , LightweightZombieFlickChance3{0.5f}
    , LightweightZombieFlickChance5{0.9f}
    , PFLightweightZombieFlickChance{0.5f}
    {}
    
    float FlyingZombieBlowingSpeed;
    float FlyingZombieUpAccelerationFactor;
    float SlowdownPercentage; 
    float SlowDuration;
    float BlowDuration;
    int   WindGiveHelpLimit;
    int PFShots;
    int ExtraPFShots;
    float LightweightZombieFlickChance;
    float LightweightZombieFlickChance2;
    float LightweightZombieFlickChance3;
    float LightweightZombieFlickChance5;
    float PFLightweightZombieFlickChance;
    
};

class PlantDraftodil : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantDraftodil, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;
    
//    bool CanApplyPowerUpFlags() override;
    bool CanApplyPowerUpFlags() ;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    bool CanApplyPlantfood()    override { return true; }
    bool IsInvincible() const   override { return false; }
    bool CanBeShoveled()        override { return true; }
    bool CanBeTargeted()        override { return true; }
    
//    Projectile* Fire(Zombie* i_targetZombie, PlantWeapon i_plantWeapon) override;
    Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) ;
    
private:
	void giveWindBoost();
    void slowZombies();
	void blowZombiesToBack();
    void firePlantfoodProjectile(Zombie* i_zombie = NULL);
    class Projectile* FireProjectile(PlantWeapon weapon);
    void startBlowingZombiesBack();
    void startPlantfoodAirProjectileLoop();
    void shootPlantfoodAirProjectiles();
    
    bool canBeMovedByDratodil(Zombie* i_zombie);
    bool canBeSlowedByDraftodil(Zombie* i_zombie);
    
    int m_currPFLoopShotCount = 0;
    int m_extra_currPFLoopShotCount = 0;
    bool m_isBlowingZombiesToBack = false;
    bool m_shouldShootPFAirProjectiles = false;
    
    pvztime_t m_blowToBackStartTime;
    pvztime_t m_lastShotTime;
    
    std::vector<BoardEntity*> getTargetableZombies();
    std::vector<RtWeakPtr<Zombie>> m_plantfoodAlreadyHitZombies;
};

class DraftodilProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(DraftodilProjectileProps, ProjectilePropertySheet, RtClass);
    
    DraftodilProjectileProps() :
    WindAccel{100.0f},
    UpPercent{0.0f},
    StuckedDuration{0.5f},
    StuckedDuration5{1.0f},
    stuckedChance1{50},
    stuckedChance2{70},
    stuckedChance3{90}
    {
    }
    
    float WindAccel;
    float UpPercent;
    float StuckedDuration;
    float StuckedDuration5;
    int stuckedChance1;
    int stuckedChance2;
    int stuckedChance3;
    ClassRestrictionSet CanBlowAway;
};

class PlantDraftodilProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PlantDraftodilProjectile, Projectile, RtClass);
    
    void SetProjectileData(float i_lightweightZombieFlickChance,float i_lightweightZombieFlickChance2,float i_lightweightZombieFlickChance3,float i_lightweightZombieFlickChance5);
    
protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual ~PlantDraftodilProjectile() {}
    
private:
    void applyConditions(BoardEntity* i_entity);
    void handleFlyingZombie(Zombie* i_zombie);
    void handleGroundZombie(Zombie* i_zombie);
    void handleLightweightZombie(Zombie* i_zombie);
    
    float m_lightweightZombieFlickChance = 0.0f;
    float m_lightweightZombieFlickChance2 = 0.0f;
    float m_lightweightZombieFlickChance3 = 0.0f;
    float m_lightweightZombieFlickChance5 = 0.0f;
};


class DraftodilProjectile2Props : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(DraftodilProjectile2Props, ProjectilePropertySheet, RtClass);

    DraftodilProjectile2Props() :
    WindAccel{100.0f},
    UpPercent{0.0f},
    StuckedDuration{0.5f},
    StuckedDuration5{1.0f},
    stuckedChance1{50},
    stuckedChance2{70},
    stuckedChance3{90}
    {
    }

    float WindAccel;
    float UpPercent;
    float StuckedDuration;
    float StuckedDuration5;
    int stuckedChance1;
    int stuckedChance2;
    int stuckedChance3;
    ClassRestrictionSet CanBlowAway;
};
class PlantDraftodilProjectile2 : public Projectile
{
public:
    RT_CLASS_DEFINE(PlantDraftodilProjectile2, Projectile, RtClass);

    void SetProjectileData(float i_lightweightZombieFlickChance,float i_lightweightZombieFlickChance2,float i_lightweightZombieFlickChance3,float i_lightweightZombieFlickChance5);

    bool can_destory = false;
    BoardEntity* BlackEntity = nullptr;
protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual ~PlantDraftodilProjectile2() {}

private:
    void applyConditions(BoardEntity* i_entity);
    void handleFlyingZombie(Zombie* i_zombie);
    void handleGroundZombie(Zombie* i_zombie);
    void handleLightweightZombie(Zombie* i_zombie);

    float m_lightweightZombieFlickChance = 0.0f;
    float m_lightweightZombieFlickChance2 = 0.0f;
    float m_lightweightZombieFlickChance3 = 0.0f;
    float m_lightweightZombieFlickChance5 = 0.0f;
};
#endif /* defined(__Plant_Draftodil__) */
