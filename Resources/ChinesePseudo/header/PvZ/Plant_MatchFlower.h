//
//  Plant_MatchFlower.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/7/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_MatchFlower_h
#define Plant_MatchFlower_h

#include <stdio.h>
#include "PlantAnimRig.h"
#include "PlantPropertySheet.h"
#include "ComponentWarmingRadius.h"
#include "ComponentProjectileConverter.h"
#include "ComponentObjectImpactor.h"
#include "Effect_PopAnim.h"

#pragma mark = MatchFlowerProps

class MatchFlowerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(MatchFlowerProps, PlantPropertySheet, RtClass);
    
    float PlantfoodInitialInterval = 1.f;
    float PlantfoodDamageInterval = 0.2f;
    float FireBurnDuration = 15.f;
    float BlueFireDamageRate = 1.25f;
    float Level5SkillRate = 0.3f;
    int NormalHitCount = 8;
    int AdvancedHitCount = 4;
    
    ComponentProjectileConverterProps ProjectileConverterProps;
    ComponentObjectImpactorProps ObjectImpactorProps;
    
    ComponentWarmingRadiusProps NormalWarmingRadius;
    ComponentWarmingRadiusProps PlantfoodWarmingRadius;

};

#pragma mark - PlantMatchFlower

enum MatchFlowerState
{
    MATCHSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
    MATCHSTATE_ATTACK,
    MATCHSTATE_PLANTFOOD,
};

class PlantMatchFlower : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMatchFlower, PlantFramework, RtClass);
    
    enum MatchAttackState
    {
        AttackState_None = 0,
        AttackState_NormalFire,
        AttackState_MegaFire,
        AttackState_End,
    };
    
    void Initialize() override;
    void UpdateActions() override;
    void UpdateUnconditionally() override;
    void DoSpecial(int i_extraParam = 0) override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void UpdatePlantfood() override;
    
    bool IsInFireState() { return m_attackState > AttackState_None; }
    bool IsInMegaFireState() { return m_attackState == AttackState_MegaFire; }
    
//    virtual int CalcRenderOrder() override;
    
protected:
    GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon) override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
    void IsImpactedByObject(RtWeakPtr<RtObject> i_object) override;
    void NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    
private:
    void updateFireEffect();
    void setFireAttackState(MatchAttackState i_state);
    void increaseAndCheckAttackCount();
    const PlantAction& choosePlantAction();
    bool IsInNegativeStatus();
    
private:
    RtWeakPtr<ComponentProjectileConverter> m_projectileConverter;
    RtWeakPtr<ComponentObjectImpactor> m_objectImpactor;
    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
    
    MatchAttackState m_attackState;
    pvztime_t m_plantfoodDamageTime;
    pvztime_t m_fireBurnTime;
    int m_attackCount;
    int m_fireUpdateCount;
};

#pragma mark - PlantAnimRig_MatchFlower

class PlantAnimRig_MatchFlower : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_MatchFlower, PlantAnimRig, RtClass);
    
    enum MatchAnimState
    {
        MatchAnimState_Yellow = 0,
        MatchAnimState_Blue,
    };
    
    PlantAnimRig_MatchFlower();
    void onDestroy() override;
    
    virtual bool PlayPunchAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
    std::string getAttackAnimationName() override;
    std::string getPlantFoodMainAnimName() override;
    
    void setMatchAnimState(MatchAnimState i_state) { m_animState = i_state; }
    void resetAttackAnimIndex() { m_punchAttackIndex = 0; }
    
    void updateFireEffect(int i_index);
    void updateFirePos(const Sexy::SexyVector2 &i_pos, const Sexy::SexyVector2 &i_artCenter, int i_renderOrder);
    bool IsFinalPunchAttack();
    
private:
    std::string getFlameColorName();
    void setFireLayerVisible(const std::vector<std::string>& i_layerName);
    
private:
    RtWeakPtr<Effect_PopAnim> m_burnEffect;
    int m_burnEffectIdx;
    int m_punchAttackIndex;
    MatchAnimState m_animState;
    bool m_isFinalPunchAttack;
};

#endif /* Plant_MatchFlower_h */
