//
//  Plant_ShrinkingViolet.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 16/10/14.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_ShrinkingViolet_h
#define Plant_ShrinkingViolet_h

#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ZombieEnums.h"

class PlantShrinkingViolet : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantShrinkingViolet, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;
    
    float GetShadowScaling() override
    {
        return 0.7f;
    }
    
    bool HasShadow() override;
    
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool IsInvincible() const override;
    CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    void TakeSmashAttack(ZombiePtr i_srcZombie) override;
    bool TryBlockZombossRush(Zombie* i_zomboss) override;
    bool TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void CustomizePlantActionDamage(const PlantAction& i_action, DamageInfo &io_damageInfo) override;
    
private:
    bool isUnshrinkable(const Zombie* i_zombie) const;
    bool m_exploded = false;
};

class ShrinkingVioletProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ShrinkingVioletProps, PlantPropertySheet, RtClass);
    
    float ShrinkTime;
    float StuckedTime;
    ZombieRestrictionSet UnshrinkableZombies;    
};

#endif /* Plant_ShrinkingViolet_h */
