/*
 * Plant_Electricitea.h
 *
 *  Created on: 2019-10-10
 *      Author: Administrator
 */

#ifndef PLANT_ELECTRICITEA_H_
#define PLANT_ELECTRICITEA_H_

#include "NewLightningBolt.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"

class DamageInfo;
class Zombie;

class ElectriciteaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ElectriciteaProps, PlantPropertySheet, RtClass);

	ElectriciteaProps()
	{
		BoltCount = 3;
		BoltRange = 2.0f;
		ElectricBurstBoltCount = 3;
		ElectricBurstBoltRange = 5;
		ElectricBurstNumBounces = 2;
		ElectricBurstBounceDamagePercent = 0.5f;
		ElectricBurstDecayDelay = 0.45f;
		ElectricBurstBounceDelay = 0.15f;
		AdvancedRate = 1.0f;
		ImprovedAdvancedBonus = 1.0f;
		ChainNumBounces = 2;
		ChainBounceDamagePercent = 0.5f;
		ChainDecayDelay = 0.45f;
		ChainBounceDelay = 0.15f;
		ChainDamage = 150.0f;
		SuperRate = 0.5f;
		StunDuration = 2.0f;
		AvatarRange = 2;
		AvatarDamage = 500.0f;
	}

	int BoltCount;
	float BoltRange;
	int ElectricBurstBoltCount;
	float ElectricBurstBoltRange;
	int ElectricBurstNumBounces;
	float ElectricBurstBounceDamagePercent;
	float ElectricBurstDecayDelay;
	float ElectricBurstBounceDelay;
	float AdvancedRate;
	float ImprovedAdvancedBonus;
	int ChainNumBounces;
	float ChainBounceDamagePercent;
	float ChainDecayDelay;
	float ChainBounceDelay;
	float ChainDamage;
	float SuperRate;
	float StunDuration;
	int AvatarRange;
	float AvatarDamage;
};

struct ElectriciteaBurstProperties
{
	ElectriciteaBurstProperties()
	{
		BoltCount = 0;
		BoltRange = 0.0;
		NumBounces = 0;
		BounceDelay = 0.0;
		Damage = 0.0;
		BounceDamagePercent = 0.0;
		MasteryResistancePiercing = 0.0;
		DecayDelay = 0.0;
	}

	int BoltCount;
	float BoltRange;
	int NumBounces;
	float BounceDelay;
	float Damage;
	float BounceDamagePercent;
	float MasteryResistancePiercing;
	float DecayDelay;
};

class PlantElectricitea : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantElectricitea, PlantFramework, RtClass);

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	void UpdateActions() override;
	void Initialize() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void SetAttackState() { setState(STATE_ATTACK); }

protected:
	void setState(const uint i_state);
	std::vector<BoardEntityPtr> findTargets(int i_numTargets, int i_range);
	BoardEntity* findPlantfoodTarget();
	void findAndShockTargets();
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void calculateNextAttackTime();
	bool isValidTarget(BoardEntityPtr i_target);

private:
	enum State
	{
		STATE_IDLE = STATE_FRAMEWORK_BEGIN,
		STATE_ATTACK,
		STATE_PLANTFOOD_ATTACK
	};

	void onPlantfoodLooped() override;

	bool shouldSpark();
	void doPlantfoodDamagePulse(BoardEntityPtr i_damageTarget);
	bool TriggerAdvancedAttack();
	bool TriggerSuperAttack();
	bool isValidTargetZombie(BoardEntityPtr target);
	bool shouldStuck(Zombie* i_zombie);
	void tryStuckZombie(Zombie* i_zombie);
	void createChainLightning(Zombie* i_zombie);
	std::vector<BoardEntityPtr> findTargets(SexyVector3 i_origin, int i_range, std::vector<BoardEntityPtr> i_targetsToExclude);
	void doAvatarAttack(BoardEntityPtr i_damageTarget);
	std::vector<std::string> GetEffectsAttackName(bool i_superAttack);
	std::vector<std::string> GetHitEffectNames(bool i_superAttack);

	pvztime_t m_timeOfNextSpark;
	RtWeakPtr<NewLightningBolt> m_plantfoodBolt;
	BoardEntityPtr m_plantfoodTarget;
};

class PlantAnimRig_Electricitea : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Electricitea, PlantAnimRig, RtClass);

	void SetIsSuperAttack(bool i_super) { m_isSuperAttack = i_super; }
	bool GetIsSuperAttack() { return m_isSuperAttack; }

protected:
	void onPopAnimInitialized() override;

	std::string getPlantFoodOnAnimName() override { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }
	std::string getAttackAnimationName() override;

private:
    bool m_isSuperAttack;
};


#endif /* PLANT_ELECTRICITEA_H_ */
