//
//  Plant_MorningGlory.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/8/16.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_MorningGlory_h
#define Plant_MorningGlory_h

#include "Precompile.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "Plant.h"

#pragma mark - MorningGloryProps

class MorningGloryProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(MorningGloryProps, PlantPropertySheet, RtClass);
    
    int SecondMaxLinkCount = 2;
    int ThirdMaxLinkCount = 3;
    
    float LinkExtraDpsModifier = 0.25f;

    float LV5Rate = 0.8;

};


#pragma mark - PlantMorningGlory

class PlantMorningGlory : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMorningGlory, PlantFramework, RtClass);
    
    enum LinkDirection
    {
        GLORYLINK_UP = 0,
        GLORYLINK_DOWN,
        GLORYLINK_LEFT,
        GLORYLINK_RIGHT,
        GLORYLINK_MAX,
    };
    
    void Initialize() override;
    void UpdateActions() override;
    void DoSpecial(int i_extraParam = 0) override;
    bool CanApplyPlantfood() override;
    void onDestroy() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    void SetAttackUp(bool i_isAttackUp, pvztime_t i_attackUpTime = PVZ_EOT(), float i_percent = 0) { m_plant->SetAttackUpValue(i_isAttackUp, i_attackUpTime, i_percent); }
    
    void checkLinkingStatus();
    PlantMorningGlory* checkLinkingHelper(LinkDirection i_direction, int &o_linkCount);
    void setIsLinking(bool i_link);
    
    void AbsorbSoundWave(ZombiePtr i_zombie = nullptr);
  
private:
    void onAnimStoppedCallback(const std::string& i_animName) override;
    void createLinkingEffect();
    int getMaxLinkingCount();
    
    int m_normalProjCounter;
    bool m_isLinking;
    bool m_isReflecting;
    int m_linkingCount;
    int m_prevLinkingCount;
    RtWeakPtr<Effect_PopAnim> m_linkingEffect;
    SexyVector3 m_targetPos;
    RtWeakPtr<BoardEntity> m_targetEntity;
    bool m_isLv5Attack;
    int m_Lv5ProjectileCount;
};

#pragma mark - MorningGloryProjectile

class MorningGloryProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(MorningGloryProjectile, Projectile, RtClass);
    
    void onProjectileInitialized() override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    void setMajorProjectile(bool i_isMajor) { m_isMajorProj = i_isMajor; }
    void setDiePosition(const SexyVector3& i_pos) { m_diePosition = i_pos; }
    void setTarget(RtWeakPtr<BoardEntity> i_entity) { m_target = i_entity; }
    
protected:
    void onUpdate(pvztime_t i_dt) override;
    
private:
    void createImpactAndDestroy();
    bool isTargetZombieDamageable();
    
    pvztime_t m_attackStartTime;
    bool m_isMajorProj;
    SexyVector3 m_diePosition;
    RtWeakPtr<BoardEntity> m_target;
};

#pragma mark - MorningGloryPFProjectileProps

class MorningGloryPFProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(MorningGloryPFProjectileProps, ProjectilePropertySheet, RtClass);
    
    int GridRange = 3;
    float DamageInterval = 0.5f;
    float StayTime = 6.f;
};

#pragma mark - MorningGloryPFProjectile

struct BlockedZombie
{
    ZombiePtr m_zombie;
    SexyVector3 m_position;
};

class MorningGloryPFProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(MorningGloryPFProjectile, Projectile, RtClass);
    void onProjectileInitialized() override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    void InitialSetPosition(const float i_x, const float i_y, const float i_z) override;
    
protected:
    void onUpdate(pvztime_t i_dt) override;
    void moveThroughTime(pvztime_t i_dt) override;
    void Destroy() override;
    
private:
    bool isZombieAlreadyPushed(ZombiePtr i_zombie = nullptr);
    void dealAreaDamage();
    
    float m_targetPosX;
    bool m_isMoving;
    std::vector<BlockedZombie> m_pushedZombies;
    pvztime_t m_damageTime;
    pvztime_t m_stayTime;
};

#pragma mark - MorningGloryAvatarProjectile

class MorningGloryAvatarProjectile : public MorningGloryPFProjectile
{
public:
    RT_CLASS_DEFINE(MorningGloryAvatarProjectile, MorningGloryPFProjectile, RtClass);
    
    void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
};

#pragma mark - MorningGloryLevel5Projectile

class MorningGloryLevel5Projectile : public Projectile
{
public:
    RT_CLASS_DEFINE(MorningGloryLevel5Projectile, Projectile, RtClass);

    MorningGloryLevel5Projectile();

    bool OnCollideEntity(BoardEntity* i_entity) override;
    void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;

protected:
    void onUpdate(pvztime_t i_dt) override;

private:
    pvztime_t m_time;
};

#pragma mark - PlantAnimRig_MorningGlory

class PlantAnimRig_MorningGlory : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_MorningGlory, PlantAnimRig, RtClass);
    
    virtual std::string getPlantFoodMainAnimName() override;
    virtual std::string getAttackAnimationName() override;

    void setIsLv5Attack(bool i_flag){
        m_isLv5Attack = i_flag;
    }

private:
    bool m_isLv5Attack;
};



#endif /* Plant_MorningGlory_h */
