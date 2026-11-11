//
//  Plant_ImpPear.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 5/7/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef Plant_ImpPear_h
#define Plant_ImpPear_h

#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"

class ImpPearProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ImpPearProps, PlantPropertySheet, RtClass);
	
	ImpPearProps()
	{
		PFZombiesImped = 0;
		ImpIndigestion = 0;
		ImpType = "";
		NormalStunDamage = 100.0f;
		NormalStunDuration = 2.0f;
		AdvancedRate = 1.0f;
		ImprovedAdvancedBonus = 1.0f;
		PFZombiesImpedAvatar = 0;
	}

	int 				PFZombiesImped;
	int 				ImpIndigestion;
	ClassRestrictionSet ZombiePFBlacklist;
	std::string			ImpType;
	float				NormalStunDamage;
	float				NormalStunDuration;
	float 				AdvancedRate;
	float 				ImprovedAdvancedBonus;
	int					PFZombiesImpedAvatar;
};

class PlantImpPear : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantImpPear, PlantFramework, RtClass);
	
	void Initialize() override;
	bool CanApplyPlantfood() override { return true; }
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	
private:
	void spawnImp(const SexyVector3 i_spawnPosition, const int i_spawnLevel);
	void spawnImpOrFart(Zombie* i_zombie);
	bool canTarget(Zombie* i_zombie);
	bool TriggerAdvancedAttack();
};

#endif /* Plant_ImpPear_h */
