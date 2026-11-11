//
//  Plant_DragonRoar.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/11/2.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_DragonRoar_h
#define Plant_DragonRoar_h

#include "PlantFramework.h"
#include "PlantAnimRig.h"

#pragma mark - DragonRoarState
class DragonRoarProps : public StarRateProps
{
public:
    RT_CLASS_DEFINE(DragonRoarProps, StarRateProps, RtClass);
    
    int NumberOfPlantfoodTargets = 5;
    
    std::vector<std::string> ZombieChewBlacklist;
    float ChewDamage = 100.f;
    float ChewLastTime = 5.f;
    float AvatarStunTime = 2.f;
    SexyVector2 SuctionSpeed = {4.f, 2.f};
    
    //for level 5
    float NovaSuccessRate = 0.4f;
    float NovaDamageInterval = 0.2f;
    float NovaSuccessDamage = 100.f;
    float NovaFailDamage = 50.f;
    
    float NovaPoisonRate = 0.5f;
    float NovaPoisonLastTime = 3.f;
};

#pragma mark - PlantDragonRoar

enum
{
    ROAR_NORMAL_PROJ = 1,
    ROAR_LEVEL_PROJ = 2,
};

enum DragonRoarState
{
    ROARSTATE_BITE = STATE_FRAMEWORK_BEGIN,
    ROARSTATE_BITETOIDLE,
    ROARSTATE_BITETOCHEWING,
    ROARSTATE_BITETOSWALLOWINGEGG,
    ROARSTATE_CHEWING,
    ROARSTATE_CHEWATTACKING,
    ROARSTATE_SWALLOWING,
    ROARSTATE_PFROARING,
    ROARSTATE_PFSUCKING,
    ROARSTATE_PFCHEWING,
    ROARSTATE_LEVEL5ATTACK,
};

class PlantDragonRoar : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantDragonRoar, PlantFramework, RtClass);
    
    ~PlantDragonRoar();
    void Initialize() override;
    
    bool CanApplyPlantfood() override { return true; }
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanEndPlantfood() override;
    
    void UpdateActions() override;
    
    void onWatered(bool watered) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    
    void PlayAttackAnimation() override;
    
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    GridItemPtr FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;
    Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    
protected:
//    void onAnimStoppedCallback(const std::string& name) override;
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    int CalcRenderOrder() override;
    
    void onBeThrown() override;

private:
    void setState(int i_state);
    bool canSwallowZombie(const Zombie* i_zombie) const;
    
    void markSuctionZombies();
    void pullSuctionZombies();
    bool allSuctionZombiesAreWithinRange();

    SexyVector2 calcSuctionDestination(const Zombie* i_zombie) const;
    bool canBeMovedByDragonRoar(const Zombie* i_zombie) const;
    
    bool zombieIsBlacklisted(const Zombie* i_zombie) const;
    bool zombieIsInRange(const Zombie* i_zombie) const;
    
    void AbsorbZombie(Zombie* i_zombie, SexyVector2 i_destination, SexyVector2 i_speed);
    
    void chewTarget();
    void doRoarAttack();
    
    void doNovaAttack(bool i_lastHit);
    void scareAwayDinoRunners();
    
    BoardEntityPtr m_targetEntity;
    int m_lastState;
    
    pvztime_t m_chewEndTime;
    std::vector<ZombiePtr> m_suctionZombies;
    
    //level 5 attack
    pvztime_t m_novaTimer;
    pvztime_t m_roarStartTime;
    pvztime_t m_roarEndTime;
    bool m_isNovaSuccessful = false;
    bool m_isNovaDealingDamage = false;
};


#pragma mark - PlantAnimRig_DragonRoar

class PlantAnimRig_DragonRoar : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_DragonRoar, PlantAnimRig, RtClass);
    
    bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
    bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
    
    void PlayBiteAttack();
    void PlaySwallowAttack();
    
    void PlayChewing();
    void PlayChewingAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    void PlaySwallow();
    void PlaySwallowEgg();
    
    void PlayPFRoaring();
    
    void PlayLevel5Attack(bool i_success);
    
    bool CurrentAnimationIsFinished();
private:
    AnimHandle m_currentAnimationHandle;

};

#endif /* Plant_DragonRoar_h */
