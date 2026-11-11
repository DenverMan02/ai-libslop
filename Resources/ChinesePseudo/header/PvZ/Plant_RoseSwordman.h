//
//  Plant_RoseSwordman.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-5-28.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_RoseSwordman__
#define __PlantsVersusZombies2__Plant_RoseSwordman__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"

class RoseSwordmanProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(RoseSwordmanProps, PlantPropertySheet, RtClass);
    RoseSwordmanProps();
    
    float ChargeAttackHitpointRate;
    std::vector<float> AdvancedAttackProbability;
    std::vector<float> SlashAttackProbability;
};

class PlantRoseSwordman : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantRoseSwordman, PlantFramework, RtClass);
    bool	 CanApplyPlantfood() override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void	 UpdateActions() override;
    void	 ApplyPlantfood() override;
    DamageTypeFlags	GetDamageFlags(PlantWeapon i_plantWeapon) override;
    GridItemPtr FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;
//    void onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect);
    void	 onKilled(bool i_instantKill) override;
    PlantRoseSwordman();
private:
    void DamageTarget(int weaponIndex);
    void PlaySwordEffect(bool charge);
    void PlaySlashEffect();
//    void PlayPlantfoodEffect();
//    void PlayRoseExplosion(int row, int column);
    void ApplyPlantfoodDamage();
    void ApplyAvatarDamage();
    void ApplySlashDamage();
    bool FindTargetAndAttack();
    bool TrigerAdvancedAttack();
    bool TrigerSlashAttack();
    float GetHitpointRate(const BoardEntityPtr& entity);
    void GetPlantfoodAttackTargets(const Point& startGrid, std::vector<BoardEntity*>& targets);
    void GetPlantfoodAttackTargets(const Rect& GridSquares, std::vector<BoardEntity*>& targets);
private:
    bool m_firstAttack;
    bool m_advancedAttack;
    bool m_slashAttack = false;
    BoardEntityPtr m_target;
    StandaloneEffectPtr m_explosion;
    StandaloneEffectPtr m_splashEffect;
};

class PlantAnimRig_RoseSwordman : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_RoseSwordman, PlantAnimRig, RtClass);
    bool SwordIsShow();
    bool PlayIdleLooped() override;
    bool playPlantFoodMain() override;
    bool PlayShowSword(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayChargeAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlaySlashAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    PlantAnimRig_RoseSwordman();
protected:
     std::string getPlantFoodMainAnimName() override;
private:
    bool m_showSword;
};

#endif /* defined(__PlantsVersusZombies2__Plant_RoseSwordman__) */
