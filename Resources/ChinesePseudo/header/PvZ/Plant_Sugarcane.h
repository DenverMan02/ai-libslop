//
//  Plant_Sugarcane.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-4-29.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Sugarcane__
#define __PlantsVersusZombies2__Plant_Sugarcane__

#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "RestrictionSet.h"
#include "Plant_TangleKelp.h"

class SugarcaneProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(SugarcaneProps, PlantPropertySheet, RtClass);
    
    SugarcaneProps()
    {
        KnockbackTime = 1.0f;
        KnockbackHeight = 0.0f;
        KnockbackOffset = 96.0f;
        PlantFoodStunTime = 2.0f;
    }
    
    float   KnockbackTime;
    float   KnockbackHeight;
    float   KnockbackOffset;
    pvztime_t PlantFoodStunTime;
    ZombieRestrictionSet BlockAbleZombie;
    std::vector<float> RecoverTime;
    std::vector<float> RecoverHealth;
};

class PlantSugarcane : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantSugarcane, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void	 onAnimStoppedCallback(const std::string& i_animCommand) override;
    void onKilled(bool i_instantKill) override;
    void	 UpdateUnconditionally() override;
    bool CanBeTargeted() override;
    bool	 IsDelayDestroy() override;
    bool	 CanBeShoveled() override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
private:
    void RepulseZombie(const Rect& rect);
    void BlockZombie();
    void PlayPlantFoodEffect();
    void UpdateZombieBlocked();
    void SetState(uint i_plantState);
    bool IsZombieClose();
    bool CanbeDamaged(const Zombie* zombie) const;
    bool CanbeBlocked(const Zombie* zombie) const;
    bool CanbeFlipped(const Zombie* zombie) const;
    void FlipAndDmageEntitiesInGrids(const DamageInfo& damage, const Rect& rect);
    void AbsorbZombie(const Rect& gridRect);
    void BeginKeyFrameTransform(Zombie* zombie);
    void FlipZombie(Zombie* i_zombie);
    void ClearBlockZombie();
    void ClearAbsorbZombie();
    float GetRecoverHealth();
    Rect GetRepulseRect();
    pvztime_t GetRecoverInterval();
    PopAnimRig::AnimStoppedReflectionDelegate GetAnimationStopDelegate();
private:
    bool m_killed = false;
    pvztime_t m_nextRecoverTime = PVZ_EOT();
    std::vector<ZombiePtr> m_blockedZombie;
    std::vector<ZombiePtr> m_absorbedZombie;
    ZombieRepulseSystem m_repulseSystem;
    TransfromKeyFrameSystem m_keyFrameSystem;
};

class PlantAnimRig_Sugarcane : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Sugarcane, PlantAnimRig, RtClass);
    PlantAnimRig_Sugarcane();
    
    bool PlayStoopLooped();
    bool PlayRecoverStraight(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayStooping(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    std::string GetStoopingName();
    std::string GetStoopedName();
    std::string GetDieName();
    std::string GetRecoverStraightName();
protected:
    void onPopAnimInitialized() override;
    int CalcDamageStateCount() override;
    void onDamageStateIndexChanged(int i_oldDamageIndex) override;
    std::string getPlantFoodMainAnimName() override;
private:
    void UpdateDamageState();
};

#endif /* defined(__PlantsVersusZombies2__Plant_Sugarcane__) */
