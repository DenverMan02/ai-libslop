//
//  Plant_Chestnut.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-4-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant__Chestnut__
#define __PlantsVersusZombies2__Plant__Chestnut__

#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"

class ChestnutProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ChestnutProps, PlantPropertySheet, RtClass);
    
    ChestnutProps()
    {
        MaxChildrenDistance = 1;
    }
    
    int MaxChildrenDistance;
    std::vector<int> ChildrenCount;
    std::vector<pvztime_t> ChildrenLaunchInterval;
};

class PlantChestnut : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantChestnut, PlantFramework, RtClass);
    
    void Initialize() override;
    void onDestroy() override;
    void	UpdateActions() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void	 onAnimStoppedCallback(const std::string& i_animCommand) override;
    void onStandaloneEffectFinishedCallback(class StandaloneEffect *i_effect) override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    bool	 BlockRailcartMovement() const override;
    void Idle() override;
    CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
private:
    void SetState(uint state);
    void UpdateIdleAction();
    void LaunchChildren(int count);
    void SpawnChild(const SexyVector2& offset);
    void PlayChildJumpEffect(const SexyVector2& offset);
    void PlayPlantFoodEffect();
    void FirePlantFoodProjectile();
    void OnOpenMouthStopped();
    void OnChildJumpStopped();
    void OnCloseMouthStopped();
    int GetMaxChildrenCount();
    bool SpawnPlaceIsSafe();
    pvztime_t GetChildrenLaunchInterval();
    class Projectile* FireProjectile(PlantWeapon weapon);
    PlantTypePtr GetChildType();
    PopAnimRig::AnimStoppedReflectionDelegate GetAnimationStopDelegate();
    
    int m_launchCount = 0;
    pvztime_t m_nextLaunch = PVZ_EOT();
    bool m_finishLaunch;
    SexyVector2 m_childOffset;
    std::vector<PlantPtr> m_children;
};

class PlantAnimRig_Chestnut : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Chestnut, PlantAnimRig, RtClass);
    PlantAnimRig_Chestnut();
    ~PlantAnimRig_Chestnut();
    void PlayOpenMouth(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayLaunchChild(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayLaunchLastChild(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayCloseMouth(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    std::string GetOpenMouthName();
    std::string GetLaunchChildName();
    std::string GetLaunchLastChildName();
    std::string GetCloseMouthName();

    void SetIsLevel5(bool i_flag);

protected:
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;
private:
    bool IsLevel5;
};

#endif /* defined(__PlantsVersusZombies2__Plant__Chestnut__) */
