//
//  Plant_Bramble.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/12/1.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef Plant_Bramble_h
#define Plant_Bramble_h

#include "PlantFramework.h"
#include "PlantPropertySheet.h"

#pragma mark - BrambleProps

class BrambleProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(BrambleProps, PlantPropertySheet, RtClass);
    

};

#pragma mark - PlantBramble

enum BrambleState
{
    BRAMBLESTATE_ATTACK = STATE_FRAMEWORK_BEGIN,
    BRAMBLESTATE_LEAVE,
};

class PlantBramble : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantBramble, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
    bool HasShadow() override;
    float GetShadowScaling() override;
    
    void PrepareToAttack();
    void LeaveWithDinoTread();
    bool IsReadyToAttack();
    
    virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override
    {
        return COLLIDE_None;
    }
    
    bool CanBeShoveled() override;
    bool IsInvincible() const override;
    
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    
    int CalcRenderOrder() override;
    
    void onStandaloneEffectFinishedCallback(class StandaloneEffect *i_effect) override;
private:
    void setState(int i_state);
    bool isInState(BrambleState i_state) const { return m_plant->m_state == i_state; }
    
    virtual void    onAnimStoppedCallback(const std::string& name) override;
};

#pragma mark - PlantAnimRig_Bramble

class PlantAnimRig_Bramble : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Bramble, PlantAnimRig, RtClass) {}
    
    void PlayAttackReady(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    void PlayAttackLoop();
};

#endif /* Plant_Bramble_h */
