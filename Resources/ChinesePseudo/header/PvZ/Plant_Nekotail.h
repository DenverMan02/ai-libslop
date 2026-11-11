//
//  Plant_Nekotail.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/8/22.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_Nekotail_h
#define Plant_Nekotail_h

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "BoardEntity.h"

enum NekoStabType
{
    NS_None = 0,
    NS_Normal,
    NS_Elec,
    NS_Huge,
    NS_Arrow
};

enum NTLaserState
{
    NTLS_INACTIVE,
    NTLS_WARMINGUP,
    NTLS_ACTIVE,
    NTLS_DISABLING
};

enum LaserType
{
    LT_Laser,
    LT_Impact,
    LT_Explode,
};

enum LaserShooter
{
    LSNone = 0,
    LSLevel1,
    LSLevel2,
    LSLevel3,
    LSLevelAvatar
};

class NekotailProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(NekotailProps, PlantPropertySheet, RtClass);
    
    int ElecStabMinLevel = 2;
    int ElecStabRate = 15;
    int ElecStabRatePro = 10;
    float LaserDPS = 90.f;
    float AvatarLaserDPS = 105.f;
    float LaserLevelUpDPSPro = 15.f;
    float HugeStabRate = 0.001;
    float LaserAngleDegrees = 85.f;
    float LaserMaxDist = 900.f;
    float LaserRate = 2000.f;
    float NumbRate = 0.15f;
    float NumbRateProPerLevel = 0.05;
    float NumbDuration = 2.f;
    float AvatarLaserSplashDPS = 50.f;
    float AvatarLaserSplashRadius = 2.0736;
    float ReedArrowRate = 0.8f;
    SexyVector2 LaserEffectPos = { 105.f, 105.f };
    SexyVector2 LaserStarOffset = { 0.f, 98.f };
    SexyVector2 LaserEndOffset = { 200.f, 98.f };
};

class NekotailStab;

class PlantNekotail : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantNekotail, PlantFramework, RtClass);
    
    PlantNekotail();
    ~PlantNekotail();
    
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void Initialize() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanApplyPlantfood() override;
    void UpdateUnconditionally() override;
    void DoSpecial(int i_extraParam = 0) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void UpdateActions() override;
    virtual void AddToRenderQueue(class RenderQueue* i_queue) override;
    
private:
    BoardEntity* FindLaserTargetByType(BoardEntityTypeFlag i_type, float& targetDistSqr);
    BoardEntity* FindLaserTarget();
    
    bool LaserNeedLevelUp();
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool IsLaserInLevel(LaserShooter i_level);
    void LaserLevelUp();
    void UpdateLaserShooterLayer();
    void setLaserState(NTLaserState i_newState);
    void ApplyLaserDamage(BoardEntity* i_entity);
    void ApplyAvatarLaserSplashDamage(BoardEntity* i_entity);
    void LaserHitBlasting(BoardEntity* i_entity, const SexyVector2& i_laserPivotScreenSpace);
    void RenderLaser(Graphics *i_g);
    SexyVector2 GetLaserShooterPos();
    bool CanBeTarget(BoardEntity* i_entity);
    
    RtWeakPtr<class Effect_PopAnim> GetLaserRig();
    RtWeakPtr<class Effect_PopAnim> GetLaserImapctRig();
    RtWeakPtr<class Effect_PopAnim> GetLaserSplashRig();
    RtWeakPtr<GameObject> LoadLaserEffect(std::string i_name, LaserType i_laserType);
    
private:
    NTLaserState m_laserState = NTLS_INACTIVE;
    
    NekoStabType m_stabType = NS_None;
    
    LaserShooter m_laserShooter = LSNone;
    
    pvztime_t m_laserStartTime = 0.f;
    
    BoardEntityPtr m_stabTarget = nullptr;
    BoardEntityPtr m_laserTarget = nullptr;
    
    SexyVector2 m_laserPos;
    SexyVector2 m_laserTargetPos;
    int m_newAvatarElecRate;
    
    RtWeakPtr<class Effect_PopAnim> m_laserRig;
    RtWeakPtr<class Effect_PopAnim> m_laserImpactRig;
    RtWeakPtr<class Effect_PopAnim> m_laserSplashRig;
};

class PlantAnimRig_Nekotail : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Nekotail, PlantAnimRig, RtClass);
    
    PlantAnimRig_Nekotail();
    void SetElec(int i_elec);
    
private:
    std::string getAttackAnimationName() override;
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;
    
private:
    int m_elec = 1;
};

class NekotailStabProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(NekotailStabProps, ProjectilePropertySheet, RtClass);
    
    float MaxRotationsPerSecond = 1.0;
};

class NekotailStab : public Projectile
{
public:
    RT_CLASS_DEFINE(NekotailStab, Projectile, RtClass);
    
    NekotailStab();
    void SetOverrideTarget(BoardEntity* i_overrideTarget);
    void SetRotatedVelocity(float i_magnitude);
    void SetNumbInfo(float i_rate, float i_duration);
    void FindNewTarget();
    void SetPenetrate(float i_rate) { m_penetrate = i_rate; }
    
protected:
    void onDeflection(class BoardEntity* i_deflector) override;
    void moveThroughTime(pvztime_t i_dt) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
    BoardEntity* FindTargetWithFlag(BoardEntityTypeFlag i_flag);
    bool CanBeTarget(BoardEntity* i_entity);
    SexyVector3 GetTargetPos(BoardEntity* i_target);
    
private:
    RtWeakPtr<BoardEntity> m_overrideTarget;
    bool m_deflected = false;
    float m_numbRate = 0.f;
    float m_numbDuration = 0.f;
    std::vector<BoardEntityPtr> m_hitEntities;
    float m_penetrate;
};

class NekotailArrow : public Projectile
{
public:
    RT_CLASS_DEFINE(NekotailArrow, Projectile, RtClass);

    bool OnCollideEntity(BoardEntity* i_entity) override; 
private:
    std::vector<BoardEntityPtr> m_hitted;
};

#endif /* Plant_Nekotail_h */
