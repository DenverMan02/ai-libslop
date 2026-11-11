//
//  Plant_WhiteMelon.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang & Jonathan Han on 13-11-29.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_WhiteMelon__
#define __PlantsVersusZombies2__Plant_WhiteMelon__

#include "PlantFramework.h"
#include "RtObject.h"
#include <list>

class WhiteMelonProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(WhiteMelonProps, PlantPropertySheet, RtClass);

	WhiteMelonProps();

	float Lv2AttackRate;
	float Lv4AttackRate;
	float AttackTick;
	int TossSmallGrid;
	int TossMidGrid;
	int TossBigGrid;
	float SuperAttackRate;
};

class PlantWhiteMelon : public PlantFramework
{
private:
	enum State
	{
		STATE_ATTACK_READY = STATE_FRAMEWORK_BEGIN,
		StATE_ATTACKING,
	};

public:
	RT_CLASS_DEFINE(PlantWhiteMelon, PlantFramework, RtClass);
    
    PlantWhiteMelon();
	
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;

	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual bool	CanEndPlantfood()override;

	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	bool 			HasGravity() override;
    
protected:
	virtual void	onDestroy() override;
    
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

	ZombiePtr FindAttackTargetZombie(PlantTargetParams& i_targetParams);

private:
    void TakeAttack(PlantWeapon weapon);
	void TakePlantFoodAttack_Hit1(PlantWeapon weapon);
	void TakePlantFoodAttack_Hit2(PlantWeapon weapon);
	void TakePlantFoodFinalAttack(PlantWeapon weapon);
	void TakePlantFoodAttack_HitSuper(PlantWeapon weapon);
	void TossZombie(ZombiePtr zombie);
	inline void UpdateAttackTick(){ m_fAttackTick = PVZ_T() + GetProps()->CastChecked<WhiteMelonProps>()->AttackTick; }
	bool TriggerAttack();
	bool TriggerLv2Attack();
	bool TriggerLv4Attack();
	bool TriggerSuperAttack();

private:
	float m_fAttackTick;
	const float m_cfApexHeight;
	const pvztime_t m_cfTimeToHit;
	const pvztime_t m_cfPlantfoodTimeToHit;
};

class PlantAnimRig_WhiteMelon : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_WhiteMelon, PlantAnimRig, RtClass);

	bool PlayAttackStorage();
	bool PlayAttackHit(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayAvatarAttackHit(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlaySuperAttackHit(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	virtual bool PlayPlantFood(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
public:
	enum PlantAnimRig_WhiteMelon_State
	{
		PLANTANIM_PLANTFOOD_STEP1 = PLANTANIM_USERDEFINED,
		PLANTANIM_PLANTFOOD_STEP2,
		PLANtANIM_WHITEMELON_ATTACK,
	};

private:
	virtual std::string getAttackAnimationName() { return "attack_ready"; }
};



#endif /* defined(__PlantsVersusZombies2__Plant_Turnip__) */
