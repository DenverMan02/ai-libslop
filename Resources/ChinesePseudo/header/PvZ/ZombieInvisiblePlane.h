//
//  ZombieInvisiblePlane.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-6-24.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieInvisiblePlane__
#define __PlantsVersusZombies2__ZombieInvisiblePlane__

#include "ZombieSkyCity.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "Zombie.h"
#include "Projectile.h"
#include "Effect_Barrage.h"

STATE_ENUM_CHILD_BEGIN(ZombieInvisiblePlaneState, ZombieState)
     ZS_InvisiblePlane_Rush,
     ZS_InvisiblePlane_Crush,
STATE_ENUM_END(ZombieInvisiblePlaneState)

class ZombieInvisiblePlaneProps : public ZombieSkyCityProps
{
public:
    RT_CLASS_DEFINE(ZombieInvisiblePlaneProps, ZombieSkyCityProps, RtClass);
    
    ZombieInvisiblePlaneProps();
    int DamageLayerIndices;
};

class ZombieInvisiblePlane : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieInvisiblePlane, Zombie, RtClass);
    int CalcRenderOrder() const override;
    void TakeDamage(const DamageInfo& i_damage) override;
    void onApplyCondition(ZombieConditions i_condition) override;
    ZombieInvisiblePlane();
    Effect_Barrage * GetBarragePtr();
    Effect_Barrage * GetBarragePtr2();
    void SetPooyanBossHP(float i_hp);
protected:
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Glide);
    OVERRIDE_STATE_ONENTER(ZombieState, Die);
    OVERRIDE_STATE_UPDATE(ZombieState, Besiege);
    
    void onDestroy() override;
    void onUpdate() override;
    void onZombieInitialize() override;
    void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
    bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
    bool allowElectrocuteState() const override;
    bool allowAshState() const override;
    
private:
    DECLARE_STATE_FUNCTIONS(ZombieState, Rush);
    DECLARE_STATE_FUNCTIONS(ZombieState, Crush);
    
    int CalcDamageIndex();
    void OpenHalo();
    void CloseHalo(bool immediately);
    void Explode();
    void DamageAirShip(float damage);
    void OnHaloOpen(StandaloneEffect* i_effect);
    void RevokeInvisible();
    void UpdateInvisiblePlane();
    void OnAnimStopped(const std::string& label);
    void CrushTarget(BoardEntity* i_target);
    bool IsCloseToShip();
    Rect CalcInvisibleRect();
    std::vector<BoardEntity*> FindTargets();
private:
    bool m_openHalo;
    RtWeakPtr<class Effect_PopAnim> m_halo;
    std::vector<ZombiePtr> m_invokedZombie;
    Effect_Barrage      m_barrage;
    Effect_Barrage      m_barrage2;
};

class ZombieAnimRig_InvisiblePlane : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_InvisiblePlane, ZombieAnimRig, RtClass);
    void SetState(ZombieAnimRigState state);
    void SetDamageIndex(int index);
    ZombieAnimRig_InvisiblePlane();
    static std::string GetRushName();
    static std::string GetCrushName();
    static std::string GetCrushPrepareName();
protected:
    void onPopAnimInitialized() override;
private:
    void UpdateDamageLayerVisibility();
    const std::vector<std::string>& GetDamageLayerNames();
private:
    int m_damageIndex;
};

#endif /* defined(__PlantsVersusZombies2__ZombieInvisiblePlane__) */
