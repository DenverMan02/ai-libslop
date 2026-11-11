#ifndef __PLANT_NIGHTSHADE_H__
#define __PLANT_NIGHTSHADE_H__

#include <string>

#include "PlantFramework.h"
#include "ComponentConditionRadius.h"
#include "Plant_Wallnut.h"
#include "AnimRigLayerSet.h"

#define WEAPON_UPGRADED 4

class NightshadeProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(NightshadeProps, PlantPropertySheet, RtClass);
	
	NightshadeProps():LeafRespawnCooldown(0.0f),
			ImprovedLeafRespawnRate(0.0f),
			ImprovedLeafRespawnBonus(0.0f){}
	
	float MeleeDamage;
	float PFMeleeDamage;
	float LeafRespawnCooldown;
	float ImprovedLeafRespawnRate;
	float ImprovedLeafRespawnBonus;
	
	TargetInfoProps TargetProps;
};

enum NightShade_State
{
	NIGHTSHADE_IDLE = STATE_FRAMEWORK_BEGIN,
	NIGHTSHADE_SLAPPING,
	NIGHTSHADE_SHOOTING,
};

class PlantNightshade : public PlantFramework
{
public:
	static const std::string k_pfOffLayerSetName;
	static const std::string k_pfOnLayerSetName;
	static const std::string k_boostedOffLayerSetName;
	static const std::string k_boostedOnLayerSetName;
	static int k_maxLeaves;
	
public:
	RT_CLASS_DEFINE(PlantNightshade, PlantFramework, RtClass);
	void UpdateActions() override;
	void Initialize() override;
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	
	void onAnimStoppedCallback(const std::string& i_anim) override;

	void PlayAttackAnimation() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	bool CanApplyPlantfood() override { return true; }
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	int	GetPlantFoodPlayCount() override;
	
private:
	void setState(NightShade_State newState);
	
	bool isBoosted();
	bool zombiesInMeleeRange();
	std::vector<BoardEntity*> getMeleeTargets();
	
	void updateLeafCount(int leafCount);
	bool tryMeleeAttack();
	bool dealMeleeDamage();
	bool hasLeaves();
	void useLeaf();
	void regenLeaf();
	void updateLeafRegen();
	bool canBeginRegen();
	void deactivateRegenTimer();
	bool hasMaxLeaves();
	PlantWeapon getWeapon();
	void updateRigLayers();

	int m_currentLeafCount;
	pvztime_t m_timeToRegenLeaf;
	bool m_plantfooded;
};


class PlantAnimRig_Nightshade : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Nightshade, PlantAnimRig, RtClass);
	PlantAnimRig_Nightshade();
	
	bool PlayIdleLooped() override { return playIdleAnimation(); }

	void AdjustLeafDisplay(int leafCount, bool plantfooded);
	void SetToAttackState() { SetState(PLANTANIM_ATTACK); }
	void SetToIdleState()   { SetState(PLANTANIM_IDLE); }
	
	void AddPfLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowPfLayerSet(std::string setName);
	void AddBoostedLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowBoostedLayerSet(std::string setName);

	bool PlayZenGardenIdleAnim() override;
	bool PlayPreviewAnim(bool bHideLayer) override;

protected:
	void onPopAnimInitialized() override;

private:
	bool playIdleAnimation();

	std::string m_lastPlayedIdleAnim;
	AnimRigLayerSet m_pfLayerSet;
	AnimRigLayerSet m_boostedLayerSet;
	std::vector<std::string> normalLeafLayers = {"shade_petal1", "shade_petal2", "shade_petal3"};
	std::vector<std::string> pfLeafLayers = {"shade_petal1_pf", "shade_petal2_pf", "shade_petal3_pf"};
};

#endif
