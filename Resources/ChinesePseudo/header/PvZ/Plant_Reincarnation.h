/*
 * Plant_Reincarnation.h
 *
 *  Created on: 2021-6-11
 *      Author: admin
 */

#ifndef PLANT_REINCARNATION_H_
#define PLANT_REINCARNATION_H_

#include "Plant.h"
#include "Projectile.h"
#include "ComponentDamageRadius.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "RtDelegate.h"

class PlantReincarnation : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantReincarnation, PlantFramework, RtClass);

    void Initialize() override;
    void PostInitializeFromPropertySheet() override;

    void UpdateActions() override;

    bool CanApplyPlantfood() override { return m_plant->m_state != STATE_PLANTFOOD_ATTACK; }
    void CancelPlantfood() override;
    void ApplyPlantfood() override;

    Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;
    void FirePuffCallback(float i_time);
    void FireWindCallback(float i_time);
    void FireStrongWind(int i_col, int i_row);

    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;

private:
    enum State
    {
        STATE_PLANTFOOD_ATTACK = STATE_FRAMEWORK_BEGIN,
        STATE_TRANSITION,
        STATE_RECOVERY
    };

    void setState(const uint i_state);

    bool canFirePetal() { return m_plant->m_state != STATE_RECOVERY && m_plant->m_state != STATE_TRANSITION; }

    int getPetalAmount();

    int32_t m_growthLevel;
    int32_t m_lastGrowthLevelForAttack;
    int m_petals;
    bool m_hasPlayedPlantFoodAnimation;
    ProjectilePtr m_plantfood_proj;
};

class PlantReincarnationProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantReincarnationProps, PlantPropertySheet, RtClass);

    int PetalAmount;
    pvztime_t RecoveryTime;
    float AvatarMoveGrids;
    float AvatarMoveTime;
    float AvatarStunDuration;
    float AvatarPuffSpeedUp;
    float AvatarPuffInitSpeed;
};

class PlantAnimRig_Reincarnation : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Reincarnation, PlantAnimRig, RtClass);

    typedef Delegate1<pvztime_t> UsePuffDelegate;
    typedef Delegate1<pvztime_t> UseWindDelegate;

    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
    bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
    bool PlayPuff(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, int i_growthLevel);

    bool PlayInitialFrame() override;
    void onPopAnimCommand(pvztime_t i_atTime, const std::string &i_command, const std::string &i_param) override;
    void SetPlantDelegates(UseSpecialDelegate i_onUseSpecial, UseActionDelegate i_onUseAction, UsePuffDelegate i_onUsePuff, UseWindDelegate i_onUseWind);
    bool PlayPlantFoodEnd() override;

    bool PlayPreviewAnim(bool bHideLayer = false) override;
    //bool PlayZenGardenIdleAnim() override;

protected:
    void onInitialized() override;
    std::string getIdleAnimationName() override;
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;

private:
    std::string getAttackStartAnimationName();

    std::string getPuffAnimationName(int i_growthLevel);

    UsePuffDelegate m_onUsePuff;
    UseWindDelegate m_onUseWind;

    int32_t m_growthLevel;
};

class ReincarnationPuffProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ReincarnationPuffProjectile, Projectile, RtClass);

protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
};


#endif /* PLANT_REINCARNATION_H_ */
