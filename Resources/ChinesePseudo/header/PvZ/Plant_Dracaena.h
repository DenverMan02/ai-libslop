//  Plant_Dracaena
//  Created by lfy
//  2023.09.26

#ifndef __PLANT_DRACAENA__
#define __PLANT_DRACAENA__

#include "PlantFramework.h"
#include "PlantAnimRig.h"
#include "Projectile.h"
#include "PlantUtils.h"
#include "ActionSubSystem.h"
#include "PropertySheetBase.h"


enum DracaenaState
{
    DRACAENA_IDLE = STATE_FRAMEWORK_BEGIN,
    DRACAENA_PREPARE,
    DRACAENA_READY,
    DRACAENA_ATTACK_SWORD,
    DRACAENA_ATTACK_FLY_SWORD,
    DRACAENA_ATTACK_FLY_SWORD_IN_ONE,
    DRACAENA_ATTACK_FLY_SWORD_IN_ONE_OVER,
    DRACAENA_PLANTFOOD,    
};

class DracaenaProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(DracaenaProps, PlantPropertySheet, RtClass);
    DracaenaProps() 
    {
        FlySwordDamage = 120.0f;
    }
    float FlySwordDamage;     
};

class PlantDracaena : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantDracaena, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;         
    void ApplyPlantfood() override;    

    void SetTargetZombie(BoardEntityPtr i_target) { m_target = i_target; }
    void setState(DracaenaState i_plantState);    
    DracaenaState getState() { return m_state; }

protected:
    void onAnimStoppedCallback(const std::string& i_animLabel) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    bool CanApplyPlantfood() { return true; }
    void CancelPlantfood();
    void UpdatePlantfood();
    void PlayAttackAnimation() { }
private:    

    void swordAttack();
    void flySwordAttack();
    void flySwordInOne();
    void pfSwords();
    BoardEntityPtr findAttackTarget();
    bool isViableTarget(Zombie* i_zombie);

    pvztime_t m_attackTimeStamp;
    BoardEntityPtr m_target;
    DracaenaState m_state;
    class DracaenaPlantgfood m_plantfood;
    class DracaenaPlantgfood m_plantfoodExtraUp;
    class DracaenaPlantgfood m_plantfoodExtraDown;
};

class DracaenaSwordProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(DracaenaSwordProjectile, Projectile, RtClass);
protected:
    void damageEntity(BoardEntity* i_entity) override;   
    void onDestroy() override;
private:
    bool m_hit = false;
};

class Lv5SwordProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(Lv5SwordProps, ProjectilePropertySheet, RtClass);
    Lv5SwordProps() { }
    std::vector<RtWeakPtr<ProjectilePropertySheet> > splitBullets;
};

class Lv5DracaenaSwordProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(Lv5DracaenaSwordProjectile, Projectile, RtClass);
    void InitBackPos();
protected:
    void damageEntity(BoardEntity* i_entity) override;
    void onDestroy() override;    
private:    
    SexyVector3 m_initPos;
    std::vector<BoardEntity*> m_hitTargets;
};

class PfDracaenaSwordProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PfDracaenaSwordProjectile, Projectile, RtClass);   
    void onProjectileInitialized() { JoinTeam(TEAM_PLANTS); } 
protected:
    void damageEntity(BoardEntity* i_entity) override;    
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
    void onSetInstigator(BoardEntity* i_instigator) override;
private:    
    int m_instigatorLv = 1;
};

class Lv5BackProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(Lv5BackProjectile, Projectile, RtClass);    
protected:    
    void onFlyBackDone(BoardEntity * target);    
private:    
    SexyVector3 m_initPos;
};

class PlantAnimRig_Dracaena : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Dracaena, PlantAnimRig, RtClass);
    
    PlantAnimRig_Dracaena() {}
        
    void PlayAttack2Loop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayAttack2End(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayLv5AttackLoop();
    void PlayIdleReady();
protected:
    std::string getPlantFoodOnAnimName() { return "plantfood_start"; }

private:    


};

#endif