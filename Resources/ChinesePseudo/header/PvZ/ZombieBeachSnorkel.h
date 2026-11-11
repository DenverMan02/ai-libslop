//
//  ZombieBeachSnorkel.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 5/27/142.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIESNORKEL_H__
#define __ZOMBIESNORKEL_H__

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieBeachSnorkelState, ZombieState)
	ZS_SNORKEL_Submerge,
	ZS_SNORKEL_Emerge,
STATE_ENUM_END(ZombieBeachSnorkelState)

class ZombieBeachSnorkel : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBeachSnorkel, Zombie, RtClass);

	ZombieBeachSnorkel();

	void TakeDamage(const DamageInfo& i_damage) override;
	bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;

protected:
	float calcTideDepth(const SexyVector3& i_position, float i_additionalWaterDepth) override;
	bool canBeDamagedByAttack(Plant* i_instigator, 	DamageTypeFlags i_damageFlags);

	DECLARE_STATE_FUNCTIONS(ZombieState, SnorkelSubmerge);
	DECLARE_STATE_FUNCTIONS(ZombieState, SnorkelEmerge);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

private:
	void onPlaceOnBoard() override;
	void onPlaceOnStreet() override;

	void onSubmergeAnimFinished(const std::string& i_animLabel);

	bool m_isSubmerged;
};

class ZombieAnimRig_BeachSnorkel : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BeachSnorkel, ZombieAnimRig, RtClass);

	void PlaySubmerge(PopAnimRig::AnimStoppedReflectionDelegate i_onCompletion = PopAnimRig::AnimStoppedReflectionDelegate());
	void PlayEmerge(PopAnimRig::AnimStoppedReflectionDelegate i_onCompletion = PopAnimRig::AnimStoppedReflectionDelegate());

	// For the Snorkel PROTOTYPE, we are having the anim rig adjust our vertical
	// offset to simulate an animation of him submerging / emerging
	void PROTOTYPE_SetSubmerged(bool i_submerged);
	float PROTOTYPE_GetVerticalOffset() const;
	bool PROTOTYPE_IsLerping() const;

protected:
	void onPopAnimInitialized() override;
	void onUpdate() override;

	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;

private:
	void PROTOTYPE_startLerp(float i_startOffset, float i_endOffset, PopAnimRig::AnimStoppedReflectionDelegate i_onCompletion = PopAnimRig::AnimStoppedReflectionDelegate());

	float m_PROTOTYPE_startingOffset;
	float m_PROTOTYPE_targetOffset;
	pvztime_t m_PROTOTYPE_offsetChangeTime;
	PopAnimRig::AnimStoppedReflectionDelegate m_PROTOTYPE_onLerpDoneDelegate;
};

#endif
