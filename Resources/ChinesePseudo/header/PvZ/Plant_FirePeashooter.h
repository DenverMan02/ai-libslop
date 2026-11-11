//
//  Plant_FirePeashooter.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 11/14/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_FirePeashooter__
#define __PlantsVersusZombies2__Plant_FirePeashooter__

#include "ComponentWarmingRadius.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"

class Zombie;

#pragma mark
class FirePeashooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(FirePeashooterProps, PlantPropertySheet, RtClass);
    
    FirePeashooterProps()
    {
        FlameThrowerLengthInNumTiles = 1.0f;
        FountainDamage = 0;
    }
    
    float FlameThrowerLengthInNumTiles;
	
	ComponentWarmingRadiusProps NormalWarmingRadius;
	ComponentWarmingRadiusProps PlantfoodWarmingRadius;
    std::vector<pvztime_t> ContinuousFireRate;
    float FountainDamage;
};



#pragma mark
class PlantFirePeashooter : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantFirePeashooter, PlantFramework, RtClass);
	
	void Initialize() override;
    
    bool        CanApplyPlantfood() override;
    Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	void ApplyPlantfood() override;
	void UpdatePlantfood() override;
    void CancelPlantfood() override;
    
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	
protected:
    void onDestroy() override;
	void onKilled(bool i_instantKill) override;
	
private:
    void updatePlantfoodDamageEndtime();
    void fireFlamethrower();
    bool canFireFlamethrower();
    Sexy::Rect createFlamethrowerRect();
    void causeFlamethrowerDamage(const std::vector<BoardEntity*>& i_targetableEntities);
    void playFlamethrowerEffect();
    void StartFountain();
    void EndFountain();
    bool FountainIsStart();
    void UpdateFountain();
    void PlayFountainEffect(int row, int col);
    void CauseFountainDamage(int row, int col);
    
    pvztime_t m_plantfoodDamageEndTime;
	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
    int m_currentFountain;
    pvztime_t m_nextFountain;
};



#pragma mark
class PlantAnimRig_FirePeashooter : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_FirePeashooter, PlantAnimRig, RtClass);
    
    bool PlayPreviewAnim(bool bHideLayer = false) override;
    
    void PlayFlamethrowerEffect(int lengthOfFlamethrower, const Sexy::Point& flamethrowerStartingSquare);
    
protected:
    bool playPlantFoodOff() override;
    
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;
    
private:
    void initializeFlameEffects(int lengthOfFlamethrower);
    void setFlamethrowerEmissionLocation(const Sexy::Point& flamethrowerStartingSquare);
    
    const float k_flamethrowerDelayMultiplier = 0.098f;
    
    std::vector<RtWeakPtr<Effect_PopAnim>> m_effects;
};



#pragma mark
class EffectAnimRig_FirePeashooterFireSquare : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(EffectAnimRig_FirePeashooterFireSquare, PopAnimRig, RtClass);
    
    void SetOwningEffect(class Effect_PopAnim* i_effect);
    
    void StartPlayingFireEffect(pvztime_t i_delay);
    void StopPlayingFireEffect(pvztime_t i_delay);
    
protected:
    void onPopAnimInitialized() override;
    void onUpdate() override;
    
private:
    void determineActivationTime(pvztime_t i_delay);
    void playDelayedAnimationSequence();
    void onFireSequenceContinued(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
    void onFireSequenceEnded(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
    
    RtWeakPtr<class Effect_PopAnim> m_owningEffect;
    pvztime_t m_activationTime = PVZ_T();
    bool m_playEndAnimation = false;
};

#endif /* defined(__PlantsVersusZombies2__Plant_FirePeashooter__) */
