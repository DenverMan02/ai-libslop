//
//  Plant_Strawburst.h
//  PlantsVersusZombies2
//
//  Created by Mina, Elliott on 6/18/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Strawburst__
#define __PlantsVersusZombies2__Plant_Strawburst__

#include <string>
#include <vector>

#include "EffectObject.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "GridItemAnimation.h"

class StrawburstProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(StrawburstProps, PlantPropertySheet, RtClass);

    StrawburstProps()
    {
        Level2Boost = 0.2;
        Level2Boost = 0.15;
        NumPushedZombiesForMinSpeed = 5;
        MinimumSpeedScaleWhilePushing = 0.3f;
        ExplodeAtXPosition = 750.f;
    }

    float                   Level2Boost;
    float                   Level3Boost;
    float                   MinimumSpeedScaleWhilePushing;
    int32                   NumPushedZombiesForMinSpeed;
    float                   ExplodeAtXPosition;
	PultProjectileProps		NormalLaunchProps;
};

class BoardEntity;

enum StrawburstState
{
    STRAWBURST_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
    STRAWBURST_STATE_RECOVER_LOOP,
    STRAWBURST_STATE_RECOVER_END,
    STRAWBURST_STATE_SELF_DESTRUCT
};

class EffectObject_StrawburstPlantfoodProps : public EffectObjectPropertySheet
{
public:
    RT_CLASS_DEFINE(EffectObject_StrawburstPlantfoodProps, EffectObjectPropertySheet, RtClass);

    EffectObject_StrawburstPlantfoodProps()
    {
        DamageOnHit = 0.0f;
    }

    float		DamageOnHit;
};

class EffectObject_StrawburstPlantfood : public EffectObject
{
public:
    RT_CLASS_DEFINE(EffectObject_StrawburstPlantfood, EffectObject, RtClass);

    void SetInstigator(RtWeakPtr<BoardEntity> i_entity);

protected:
    void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;

private:
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);

    void takeListDamage(std::vector<BoardEntity*> i_entityList, float i_damageScale);

    float m_damageRate;
    TeamFlags m_instigatorTeam;
	std::vector<std::string> m_instigatorFamilies;
};

class StrawburstProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(StrawburstProjectile, Projectile, RtClass);

    StrawburstProjectile();
    void SetJamFlag(bool i_flag);

protected:
    bool m_jamFlag;
};

class SmallStrawburstProjectile : public StrawburstProjectile
{
public:
    RT_CLASS_DEFINE(SmallStrawburstProjectile, StrawburstProjectile, RtClass);

    bool OnCollideEntity(BoardEntity* i_entity) override;
};

class MediumStrawburstProjectile : public StrawburstProjectile
{
public:
    RT_CLASS_DEFINE(MediumStrawburstProjectile, StrawburstProjectile, RtClass);

    bool OnCollideEntity(BoardEntity* i_entity) override { return false; }
    bool OnCollideGround() override;
};

class LargeStrawburstProjectile : public StrawburstProjectile
{
public:
    RT_CLASS_DEFINE(LargeStrawburstProjectile, StrawburstProjectile, RtClass);

    bool OnCollideEntity(BoardEntity* i_entity) override { return false; }
    bool OnCollideGround() override;
};

class PlantStrawBurst : public PlantFramework
{
    RT_CLASS_DEFINE(PlantStrawBurst, PlantFramework, RtClass);

    PlantStrawBurst()
    : m_hitRowBelow(false)
    , m_touchIdent(Sexy::InvalidTouchID)
    , m_needsTouchInitialization(true)
    {
        // Do nothing.
    }

    virtual ~PlantStrawBurst();

public:
    void            SetPopAnimDelegates(class PlantAnimRig* i_rig) override;
    void            Initialize() override;
    void            UpdateActions() override;
    bool            OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

    bool            CanApplyPlantfood() override;
    void            ApplyPlantfood() override;
    void            CancelPlantfood() override;

    void			SetHitRowBelow(bool i_hitRowBelow);

    DamageInfo      TakeDamage(const DamageInfo& i_damage) override;
    void            TakeSmashAttack(ZombiePtr i_srcZombie) override;

private:
    void            registerForEvents() override;
    void            unregisterForEvents() override;

    void			unregisterTouchesIfNeeded();

	void			LobSomething(Projectile* i_newProjectile, PlantWeapon i_plantWeapon);
    void			fireProjectileCallback(pvztime_t i_atTime);
    void			onFireAnimDone(const std::string& i_animLabel);
    void			onRecoverAnimDone(const std::string& i_animLabel);

    void			setState(int i_newState);
    bool			isReadyToFire();

    bool			onTouchEvent(const Sexy::Touch& i_touch);
    bool            touchEnd(const Sexy::Touch& i_touch);
    bool            touchBegin(const Sexy::Touch& i_touch);
    void			onCancelEvent();
    void			onGameplayEnded();

    bool            canAttemptToGrow();
    void            resetGrowth();
    void            upgradeGrowthStage();
    bool            isFullyGrown() const;
    const int       getMaxGrowthStage() const;
    void            setGrowthStage(int i_growthStage, PopAnimRig::AnimStoppedReflectionDelegate i_onGrowthAnimComplete = {});
    void            setGrowthTimer(int i_stageIndex);

    Projectile*     createStandardProjectile();

    void            onAnimStoppedCallback(const std::string& i_anim) override;
	void			fireSelfDestructProjectile(bool i_showProjectile);

    // Set by the Cannon Minigame to make targeting easier

    // Serialized
    pvztime_t       m_nextGrowthTime;
    int             m_currentGrowthStage;
    bool 			m_hitRowBelow;
    bool			m_needsTouchInitialization;

    // Not Serialized
    Sexy::TouchID	m_touchIdent;
};


class PlantAnimRig_Strawburst : public PlantAnimRig
{

public:
    RT_CLASS_DEFINE(PlantAnimRig_Strawburst, PlantAnimRig, RtClass);

    PlantAnimRig_Strawburst()
    {
        m_currentGrowthStage = 0;
    }
    void SetGrowthStage(uint8 i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onGrowthAnimComplete = {});

    /// Overrides

    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
    bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
    bool PlayPlantFoodEnd() override;
    pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
	bool PlayPreviewAnim(bool bHideLayer = false) override;

    /// Custom functionality

    bool PlayRecoverLooped();
    bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlaySelfDestruct(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});

private:
    std::string getIdleAnimationName() override;
    std::string getSelfDestructAnimationName();

    void growthAnimComplete(const std::string& i_anim);

    uint8 m_currentGrowthStage;
    std::string m_lastUsedIdleAnim;
};


enum StrawburstJamState{
	PVZ_BEGIN_ENUM(StrawburstJamSTATE_),
	JAMSTATE_UNKNOWN,
	JAMSTATE_SPAWNING,
	JAMSTATE_IDLE,
	JAMSTATE_DISAPPEAR,
	JAMSTATE_DEAD,
    PVZ_END_ENUM(StrawburstJamSTATE_)
};

class StrawburstJam : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(StrawburstJam, GridItemAnimation, RtClass);

    StrawburstJam();

    virtual int CalcRenderOrder() const override;

    void InitJam(float i_duration, int i_jamType);
    void RefreshJam();

protected:
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    void setState(StrawburstJamState i_state);
    void takeEffect();
    void onAnimationDone(const std::string& i_tabel);
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);

    int m_jamType;
    float m_duration;
    StrawburstJamState m_state;
    pvztime_t m_endTime;
    RtWeakPtr<class Effect_PopAnim> m_effect;
};

class GridItemStrawburstJamProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemStrawburstJamProps, GridItemAnimationProps, RtClass);
    GridItemStrawburstJamProps()
    {
        ZombieBlacklist.clear();
    }

    std::vector<std::string> ZombieBlacklist;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Strawburst__) */
