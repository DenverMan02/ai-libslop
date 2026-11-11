//
//  Plant_HollyBarrierLeaf.h
//  PlantsVersusZombies2
//
//  Created by Alex Gelles on 10/17/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_HollyBarrierLeaf__
#define __PlantsVersusZombies2__Plant_HollyBarrierLeaf__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "DamageLifetime.h"

class HollyBarrierLeafProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HollyBarrierLeafProps, PlantPropertySheet, RtClass);
	
	HollyBarrierLeafProps()
	{}
public:
	DamageLifetime	DamagePhases;
	DamageLifetime	DamagePhases_PF;
	DamageLifetime	DamagePhasesLV5;
	DamageLifetime	DamagePhases_PFLV5;
};

class HollyBarrierLeaf : public PlantFramework
{
public:
	RT_CLASS_DEFINE(HollyBarrierLeaf, PlantFramework, RtClass);

	HollyBarrierLeaf();
	bool HasShadow() override;
	void onHealed() override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	
	void initEffect();
	void setIsAvatarSkill(bool i_isAvatarSkill);
protected:
	void DoDamageToTargets();
	void UpdateActions() override;
	void PlayAttackEffect();
	void OnHealthChanged();
private:
	bool m_IsAvatarSkill;
	int m_damagePhase;
	pvztime_t m_lastAttack;
};

class PlantAnimRig_HollyBarrierLeaf : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HollyBarrierLeaf, PlantAnimRig, RtClass);
	
	void PlayIntro(const std::string& label);
	bool PlayPreviewAnim(bool bHideLayer = false) override;
private:
	std::string m_defaultAnim;
};

#endif
