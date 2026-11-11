/*
 * Plant_KiwiBeast.h
 *
 *  Created on: 2017-11-21
 *      Author: Administrator
 */

#ifndef PLANT_KIWIBEAST_H_
#define PLANT_KIWIBEAST_H_

#include "ComponentDamageRadius.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"

class PlantKiwiBeast : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantKiwiBeast, PlantFramework, RtClass);

    void Initialize() override;
	void UpdateActions() override;

	bool CanApplyPlantfood() override { return m_plant->m_state != STATE_PLANTFOOD_ATTACK; }
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

	bool HasGravity() override;

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void NotifyComponentOwner() override;

private:
	enum State
	{
		STATE_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_PLANTFOOD_ATTACK,
		STATE_GROWING
	};

	const ComponentDamageTossRadiusProps& getDamageRadiusProps(bool i_super = false);
	void calculateNextAttack();
	bool shouldStartAttack();
	void setState(const uint i_state);
	void doBasicAttack();
	void doKnockbackAttack();
	int  getDesiredGrowthLevel();
    void doKnockback();
    void doAvatarAttack();
    bool TriggerSuperAttack();
    void tryAttack();

	int32_t m_growthLevel;
	float m_damageTaken;
	RtWeakPtr<ComponentDamageTossRadius> m_damageRadius;
	pvztime_t m_timeOfNextAttack;
	bool m_firstPlantfoodAttack;
};

class KiwiBeastProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(KiwiBeastProps, PlantPropertySheet, RtClass);

	float						GrowthStageOneDamageLimit;
	float						GrowthStageTwoDamageLimit;
	ComponentDamageTossRadiusProps	GrowthStageOneDamageRadius;
	ComponentDamageTossRadiusProps	GrowthStageTwoDamageRadius;
	ComponentDamageTossRadiusProps	GrowthStageThreeDamageRadius;
	ComponentDamageTossRadiusProps	SuperDamageRadius;
	ComponentDamageTossRadiusProps	PlantfoodDamageRadius;
	int							SunReducedAmount;
	float						ImprovedSunReducedBonus;
	float						ZombieLaunchHeight;
	pvztime_t					ZombieLaunchTime;
	float						SuperAttackRate;
};

class PlantAnimRig_KiwiBeast : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_KiwiBeast, PlantAnimRig, RtClass);

	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	bool PlaySuperAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	bool PlayGrow(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, int i_growthLevel);

protected:
	void onInitialized() override;
	std::string getIdleAnimationName() override;
	std::string getPlantFoodOnAnimName() override;

private:
	std::string getAttackAnimationName();
	std::string getGrowAnimationName(int i_growthLevel);

	int32_t m_growthLevel;
};

class PlantTypeKiwibeast : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeKiwibeast, PlantType, RtClass) {}

    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
};


#endif /* PLANT_KIWIBEAST_H_ */
