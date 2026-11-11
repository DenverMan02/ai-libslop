#ifndef __PLANT_VAMPORCINI_H__
#define __PLANT_VAMPORCINI_H__

#include "Core.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ZombieEnums.h"
#include "DamageInfo.h"
#include "PlantAnimRig_Shielded.h"
#include "Shield.h"

namespace Sexy
{
    class Point;
} // namespace Sexy

class VamporciniProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(VamporciniProps, PlantPropertySheet, RtClass);
    
    float AttackDelay = 0;
    float GainHealthDuration = 0;
    float MaxHealthCap = 0;
    float GainHealthTick = 0;
    float PfGainHealthTick = 0;
    float DamageRate = 0;
    float InitAttack = 0;
    float PfDamageRate = 0;
    float ShieldHitpoint = 0;
    float BatDuration = 0;
    float BoostAttackDelay = 0;
    float PlantFoodRate = 0;
    float BoostRate = 0;
    Rect GainHealthTargetRect;
    ClassRestrictionSet DrainExcludelist;
    GridItemRestrictionSet TargetableGridItemTypes;
};

enum PlantVamporciniState
{
    VAMPORCINISTATE_IDLE = STATE_FRAMEWORK_BEGIN,
    VAMPORCINISTATE_WAITFORATTACK,
    VAMPORCINISTATE_GAINHEALTH,
    VAMPORCINISTATE_PLANTFOOD,
    VAMPORCINISTATE_WALL,
    VAMPORCINISTATE_DEATH,
    VAMPORCINISTATE_UNDER,
    VAMPORCINISTATE_CONTRACT
};

class PlantVamporcini : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantVamporcini, PlantFramework, RtClass);

public:
    void Initialize() override;
    void UpdateActions() override;
    bool IsInvincible() const override;
    bool CanApplyPlantfood() override;
    bool CanApplyDelayedBoost();
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    BoardEntityHeight GetEntityHeight() const override;
    bool CanBeTargeted() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) override;
    bool TryBlockZombossRush(Zombie* i_zomboss) override;
    void Draw(Graphics* i_g) override;

    CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override
    {
        return (COLLIDE_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES);
    }

    void TakeSmashAttack(ZombiePtr i_srcZombie) override;
    bool GetHandleDeath() { return IsOnLevel5() ? m_lv5Attack : m_isPlayingDeathAnim; }
    void onSleeped(bool isSleep) { if ((m_state == VAMPORCINISTATE_GAINHEALTH || m_state == VAMPORCINISTATE_DEATH) && isSleep) { m_plant->SetIsSleepping(false); } }

protected:
    void onAnimStoppedCallback(const std::string& i_anim) override;
	void onDestroy() override;

private:
    bool m_isPlantFoodUsed = false;
    PlantVamporciniState m_state;
    float m_waitingTime = 0;
    float m_attackTick = 0;
    bool m_pfAttac = false;
    float m_gainHealthTime = 0;
    bool m_initAttack = false;
    float m_activeHealthCap = 0.0f;
    DamageInfo m_deathDamageInfo;
    bool m_isPlayingDeathAnim = false;
    bool m_handledDeathAnim = false;
    bool m_isBoostActive = false;
    bool m_canActivateBoost = false;
    int m_firstAttack = 0;
    bool m_canSecondAttack = false;
    float m_batDuration = 0;
    float m_batTick = 0;
    float m_baseHitpoint = 0;
    Rect m_attackRect;
    bool m_canAttack = false;
    bool m_lv5Attack = false;
    bool m_lv5Death = false;
    RtWeakPtr<Shield> m_shield;

    
    void SetState(const PlantVamporciniState i_state);
    void StealHealth(float i_damage);
    bool CalculateStealHealthTargetRect();
    DamageInfo handleAnimation(const DamageInfo& i_damage);
    bool zombieInExclusionList(const Zombie* i_zombie) const;
    bool canTargetGridItem(const GridItem* i_gridItem);
    void vampireShield();
    void batFly(float i_damage);
    void calculateAttackTime();
    void clearControl();

};

class PlantAnimRig_Vamporcini : public PlantAnimRig_Shielded
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Vamporcini, PlantAnimRig_Shielded, RtClass);
    
    std::string getIdleAnimationName() override;
    void SetHealthDrained(bool i_healthDrained){ m_healthDrained = i_healthDrained;}
    bool GetDrained() { return m_healthDrained; }
    void SetShield(bool i_shield);
    bool GetShield() { return m_Shield; }
    void SetAvatar(bool i_avatar) { m_avatar = i_avatar; }

    bool PlayStealHealthOnAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped= {});
    bool PlayStealHealthLoopAnim();
    bool PlayStealHealthOffAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped= {});

    bool PlayAndContinueSleepAnim();
    bool PlayAndContinuePFLoopAnim();
    bool PlayWakeupAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped= {});
    
    bool PlayDeathOnAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped= {});
    bool PlayDeathLoopAnim();
    bool PlayDeathOffAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped= {});

    bool PlayWaitAnim(/*PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}*/);

    bool PlayContract(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped= {});

    bool PlayLv5DeathOnAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayLv5DeathLoopAnim();
    bool PlayLv5DeathOffAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});

    bool PlayPFOnAnim(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayPFIdleAnim();
    bool PlayIdleAnim();

    std::string getPlantFoodOnAnimName() override;
    int GetArmorStateCount() override;
    void SetArmorStateIndex(int i_index) override;
    const std::vector<std::string>& getArmorStateLayerNames() const;
    // bool PlayPFLoopAnim();
    // bool PlayPFOffAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    
    // std::string getPlantFoodOnAnimName() override { return "pf_start"; }
    // std::string getPlantFoodMainAnimName() override { return "pf_loop"; }
    //bool playPlantFoodOff() override;
    
    bool m_healthDrained = false;
    bool m_Shield = false;
    bool m_avatar = false;
};

#endif

