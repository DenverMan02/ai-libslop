//
//  Plant_PowerVine.h
//  PlantsVersusZombies2
//
//  Created by Sudheer, Alma on 03/03/21.
//  Copyright © 2021 PopCap Games. All rights reserved.
//

#ifndef Plant_PowerVine_h
#define Plant_PowerVine_h

#include "PlantStatefulFramework.hpp"
#include "AnimRigLayerSet.h"
#include "PlantTypeVine.h"

STATE_ENUM_CHILD_BEGIN(PowerVineState, PlantState)
    POWERVINE_ATTACKING,
    POWERVINE_PFATTACKING,

    POWERVINE_NETWORK_IDLE,
    POWERVINE_NETWORK_ATTACKING,
    POWERVINE_NETWORK_PFATTACKING,

STATE_ENUM_END(PowerVineState);


class PowerVineProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PowerVineProps, PlantPropertySheet, RtClass);

    int NetworkShots = 3;
    int NetworkPlantMin = 2;
    int NetworkedPlantFoodPlayCount = 1;
    float PFRotationAngleDegrees = 15.0;
    ValueRange PFProjectileRotationOffset = ValueRange(-8, 8);
    float NetworkShotCooldown = 0.5;
    ZombieRestrictionSet PFEmpBurstIncludeList;
    float EmpBurstActivationRadius = 0.f;
    float EmpBurstStunTime = 0.f;
    float Lv2BoostProjectile = 0.f;
    float Lv3BoostProjectile = 0.f;
    int Lv5BoostProjectileCount = 0;
};

class PlantPowerVine : public PlantVineFramework
{
public:
    RT_CLASS_DEFINE(PlantPowerVine, PlantVineFramework, RtClass);

    PlantPowerVine();
    ~PlantPowerVine();
    void Initialize() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void SetPopAnimDelegates(class PlantAnimRig *i_rig) override ;
    int	 GetPlantFoodPlayCount() override ;
    bool IsNetworked();
    void PlayAttackAnimation() override;
    void UpdateActions() override;

    static const std::string k_networkedLayerSetName;
    static const std::string k_normalLayerSetName;


protected:
    OVERRIDE_STATE_ONENTER(PlantState, Idle);
    OVERRIDE_STATE_UPDATE(PlantState, Idle);
    OVERRIDE_STATE_ONEXIT(PlantState, Idle);

    DECLARE_PLANTSTATE_FUNCTIONS(PlantState, Attacking);
    DECLARE_PLANTSTATE_FUNCTIONS(PlantState, PFAttacking);

    DECLARE_PLANTSTATE_FUNCTIONS(PlantState, NetworkedIdle);
    DECLARE_PLANTSTATE_FUNCTIONS(PlantState, NetworkedAttacking);
    DECLARE_PLANTSTATE_FUNCTIONS(PlantState, NetworkedPFAttacking);

    void OnPlantCombos(Plant* i_plant);

private:
    void onPlantPlaced(Plant* i_plant);
    bool canAttackZombie(const Zombie* i_zombie) const;
    Projectile* firePFProjectile(Zombie* i_targetZombie, PlantWeapon i_plantWeapon, int i_forwardSlotOffset);
    void getAdjacentPowerVines();
    void setNetworkedState(bool i_isNetworked, Plant* i_plant);
    void onUseActionAnimCommand(pvztime_t i_timeStamp);
    void OnUseSpecialAnimCommand(pvztime_t i_timeStamp);
    void onPlantMoving(Plant* i_plant, Point& i_targetGridLocation);
    void onPlantDied(Plant* i_plant);
    void removePlantFromNetwork(Plant* i_plant);
    void updateAnimLayers();
    void addPlantToNetwork(Plant* i_plant);
    void applyEmpeachStunBurst();
    bool canTargetZombieToEmpBurst(Zombie* i_zombie);
    void pkinProject();
    void playEffectAnim();    

    std::vector<RtWeakPtr<Plant>> m_networkedPowerVines;
    int m_pfPlayCountIndex = 0;
    pvztime_t m_nextShotTime = PVZ_T();
    int m_noOfShots = 0;
    bool m_isNetworked = false;
    bool m_isNetworkInitialised = false;
    int m_lv5BoostAttack = 0;
    bool m_boostMainPlant = false;
    // RtWeakPtr<Effect_PopAnim> m_effect;
    bool m_isSpecial = false;
    bool m_isLv5 = false;
    bool m_canAttack = false;
};

class PlantAnimRig_PowerVine : public PlantAnimRig
{
public:
RT_CLASS_DEFINE(PlantAnimRig_PowerVine, PlantAnimRig, RtClass);

    void onPopAnimInitialized() override;
    void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
    void ShowLayerSet(std::string setName);
    bool PlayZenGardenIdleAnim() override;
    bool PlayPreviewAnim(bool bHideLayer = false) override;
    bool PlayLv2Projectile();
    bool PlayLv5Projectile();
private:
    AnimRigLayerSet m_layerSet;
    int m_attackIndex = 0;
};


#endif /* Plant_PowerVine_h */
