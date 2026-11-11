//
//  Plant_ExplodeONut.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 4/15/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_ExplodeONut_h
#define Plant_ExplodeONut_h

#include "Plant_Wallnut.h"
#include "PlantAnimRig_Shielded.h"

class ExplodeONutProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ExplodeONutProps, PlantPropertySheet, RtClass);

	float ProduceLittleNutRatioLv2;
	float ProduceLittleNutRatioLv3;
};

class PlantExplodeONut : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantExplodeONut, PlantFramework, RtClass);
	
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	void TakeSmashAttack(ZombiePtr i_instigator) override;
	void Initialize() override;
	bool HandleDamageStateChanged() override;
	void UpdateActions() override;
	
	// China override
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	bool TryBlockZombossRush(Zombie* i_zombie) override;
	bool HasPlantfoodShield() override;

	void PlayChewedOnSound() override;

protected:
	virtual void explode();

protected:
	RtWeakPtr<Shield> m_shield;
	RtWeakPtr<ComponentDamageRadius> m_explodeRadius;
	int m_currentBeepCount;
	float m_newAvatarSkillBoostRate1;
};

class PlantSmallExplodeONut: public PlantExplodeONut
{
public:
	RT_CLASS_DEFINE(PlantSmallExplodeONut, PlantExplodeONut, RtClass);

	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	bool CanApplyPlantfood() override;
	bool TryBlockZombossRush(Zombie* i_zombie) override;

protected:
	void explode() override;
};

class PlantAnimRig_ExplodeONut : public PlantAnimRig_Shielded
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ExplodeONut, PlantAnimRig_Shielded, RtClass) {}
	virtual ~PlantAnimRig_ExplodeONut(){}
	pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
	bool PlayPlantFoodEnd() override;
	
	int GetArmorStateCount() override;
	void SetArmorStateIndex(int i_index) override;
	
private:
	void onPopAnimInitialized() override;
};

class PlantExplodeSmallONut : public PlantExplodeONut
{
public:
	RT_CLASS_DEFINE(PlantExplodeSmallONut, PlantExplodeONut, RtClass);

	virtual bool CanApplyPlantfood() override;
};


#endif /* Plant_ExplodeONut_h */
