//
//  Plant_RedStinger.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/17/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_RedStinger__
#define __PlantsVersusZombies2__Plant_RedStinger__

#include <string>

#include "Plant.h"
#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "PopAnimRig.h"
#include "RtObject.h"

class Zombie;

enum StingerLocationState
{
	LOCATIONSTATE_NONE = -1,
	LOCATIONSTATE_OFFENSIVE = 0,
	LOCATIONSTATE_MIXED,
	LOCATIONSTATE_DEFENSIVE
};

enum StingerWeapons
{
	WEAPON_OFFENSIVE = 0,
	WEAPON_MIXED,
	WEAPON_PLANTFOOD,
    WEAPON_PLANTFOOD_AVATAR,
};

class PlantRedStinger : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantRedStinger, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void CancelPlantfood() override;
    bool IsDelayDestroy() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	void onKilled(bool i_instantKill) override;
	int GetLocationState() const { return m_locState; }
    
	int GetMaxHitpoints() override { return calcMaxHealthForLocState(m_locState); }
	
private:
	void updateLocState();
	void updateHealth(int i_prevColumn);
	int calcMaxHealthForLocState(StingerLocationState i_locState);
    
    void Explode();
    
	StingerLocationState calcLocStateFromColumn(int i_column);
	
	StingerLocationState m_locState;
	int m_prevColumn;
	RtWeakPtr<Effect_PopAnim> m_plantfoodEffect;
    float m_attackSpeed;
};

//
//  Property sheet
//

class RedStingerProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(RedStingerProps, StarRateProps, RtClass);
	
	RedStingerProps()
    {
        ExplosionRadius = 3.f;
    }
	
	std::vector<StingerLocationStateData> LocationStateData;
    std::vector<float> ExplosionDamage;
    float ExplosionRadius;
};

//
//  Anim rig
//

class PlantAnimRig_RedStinger : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_RedStinger, PlantAnimRig, RtClass);
	
	PlantAnimRig_RedStinger();
	
	bool PlayIdleLooped() override;
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	
	int CalcDamageStateCount() override;
	void SetLocState(StingerLocationState i_locState);
	bool PlayPreviewAnim(bool bHideLayer = false) override;

protected:
	std::string getPlantFoodOnAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override;
	
private:
    virtual std::string getIdleAnimationName() override;
    
private:
	StingerLocationState m_locState;
	std::string m_lastPlayedIdleAnim;
	AnimHandle m_attackHandle;
	PopAnimRig::AnimStoppedReflectionDelegate m_onAttackStopped;
};

#endif /* defined(__PlantsVersusZombies2__Plant_RedStinger__) */
