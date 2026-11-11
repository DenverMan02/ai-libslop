//
//  Plant_HeadbutterLettuce.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 6/29/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef Plant_HeadbutterLettuce_h
#define Plant_HeadbutterLettuce_h

#include "Plant.h"
#include "PlantFramework.h"
#include "Rect.h"
#include "RtObject.h"

class GridItem;

enum HeadbuttState
{
	HEADBUTTSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	HEADBUTTSTATE_ATTACKRIGHT,
	HEADBUTTSTATE_ATTACKLEFT,
	HEADBUTTSTATE_PLANTFOOD,
};

class HeadbutterLettuceProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HeadbutterLettuceProps, PlantPropertySheet, RtClass);
	
	HeadbutterLettuceProps()
	{
		ButterChance = 0.3f;
		ButterChanceLevel2 = 0.3f;
		ButterChanceLevel3 = 0.3f;
		MinButterQuantity = 1;
		MaxButterQuantity = 3;
		PFButterQuantity = 3;
		ButterDuration = 8.0f;
		ButterTimeOfFlight = 1.2f;
		ButterLobHeight = 350.f;
		Level5SkillRatio = 0.1f;
		PlantFoodAvatarPlayCount = 4;
		Level3MaxButterQuantity = 2;
		Level5MaxButterQuantity = 3;
	}
	
	float ButterChance; //Chance to fire butter down-lane
	float ButterChanceLevel2; //Chance to fire butter down-lane
	float ButterChanceLevel3; //Chance to fire butter down-lane
	int PlantFoodAvatarPlayCount;
	int Level3MaxButterQuantity;
	int Level5MaxButterQuantity;
	float Level5SkillRatio;
	int MinButterQuantity;
	int MaxButterQuantity;
	int PFButterQuantity;
	
	float ButterDuration;
	
	float ButterTimeOfFlight;
	float ButterLobHeight;
};

class PlantHeadbutterLettuce : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHeadbutterLettuce, PlantFramework, RtClass);
	
	PlantHeadbutterLettuce();
	
	void Initialize() override;
	void UpdateActions() override;
	void DoSpecial(int i_extraParam = 0) override;
	Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	Projectile* Fire(RtWeakPtr<class Zombie> targetZombie, int row, PlantWeapon i_plantWeapon) override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animCommand) override;
	
protected:
	void onPlantfoodLooped() override;
	void createHitEffect(bool i_left, bool isLevel5 = false);
	
protected:
	bool FireProjectileDownLane(int i_row, bool i_left);
	bool FindTargetsAndPlayAttackAnim();
	void launchButters(bool i_left, int numbers = 1);
	void launchPFButters();
	void launchPFButterAtTarget(BoardEntityPtr i_target);
	void launchDefaultButterAtTarget(class Projectile* i_projectile, const SexyVector3& i_targetLoc);
	void updateButterDuration(Projectile* i_proj);
	
	GridItem* GetGridItemMeleeTarget(bool i_left);
	ZombiePtr GetZombieMeleeTarget(bool i_left);

	GridItem* FindTargetGridItemInRow(int i_row, bool i_left);

	PlantWeapon GetPlantWeaponType();
	int			GetPlantFoodPlayCount() override;

	void PlayLevel5Anim();
	void DoLevel5Skill();
	
	bool m_searchingLeft;
	bool m_doingLeftPFHeadbutt;
	bool m_isLevel5Attack;
	std::vector<BoardEntityPtr> m_targetsAlreadyButtered;
};

class PlantAnimRig_HeadbutterLettuce : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HeadbutterLettuce, PlantAnimRig, RtClass);

	bool PlayRightHeadbutt(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayLeftHeadbutt(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
private:
	std::string getPlantFoodMainAnimName() override;
};

#endif /* Plant_HeadbutterLettuce_h */
