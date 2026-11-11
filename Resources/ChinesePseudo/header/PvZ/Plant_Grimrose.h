//
//  Plant_Grimrose.hpp
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 12/17/15.
//  Copyright © 2015 PopCap Games. All rights reserved.
//

#ifndef Plant_Grimrose_hpp
#define Plant_Grimrose_hpp

#include "AnimRigLayerSet.h"
#include "ComponentVisualStretcher.h"
#include "PlantStatefulFramework.hpp"

class PlantGrimroseTentacle;
class Zombie;



STATE_ENUM_CHILD_BEGIN(GrimroseState, PlantState)
	GRIMROSE_BEGIN_ATTACKING,
	GRIMROSE_ATTACKING,
	GRIMROSE_WAITING_FOR_ATTACK_TO_FINISH,
	GRIMROSE_END_ATTACKING,

	GRIMROSE_FADE_AWAY,

	GRIMROSE_PLANTFOOD_BEGIN,
	GRIMROSE_PLANTFOOD_SEEK_TO_NEXT_TARGET,
	GRIMROSE_PLANTFOOD_WAIT_FOR_LAST_PORTAL_TO_CLOSE,
	GRIMROSE_PLANTFOOD_END,
STATE_ENUM_END(GrimroseState);

namespace Message
{
	void GrimroseSwallowedZombie(Zombie* i_zombie);
}

class GrimroseProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GrimroseProps, PlantPropertySheet, RtClass);
	
	GrimroseProps()
	{
		MaxPlantfoodKills = 1;
		
		NumTimesToActivateWhenNotPowered = 1;
		NumTimesToActivateWhenPowered = 3;
		
		SlapDamage = 200.0f;
		SkillTriggerLv2 = 0.5f;
		SkillTriggerLv3 = 1.0f;
		SkillTriggerLv4 = 1.0f;
		BaseExplodeDamae = 0;
	}
	
	int MaxPlantfoodKills;
	
	int NumTimesToActivateWhenNotPowered;
	int NumTimesToActivateWhenPowered;
	
	ComponentVisualStretcherProps ShadowStretcherProps;
	std::vector<std::string> ZombieDeathBlackList;
	float SlapDamage;
	float SkillTriggerLv2;
	float SkillTriggerLv3;
	float SkillTriggerLv4;
	float BaseExplodeDamae;
};

class PlantGrimrose : public PlantStatefulFramework
{
public:
	RT_CLASS_DEFINE(PlantGrimrose, PlantStatefulFramework, RtClass);

	static const std::string k_boostedLayerSetName;
	static const std::string k_normalLayerSetName;
	
	PlantGrimrose();
	virtual ~PlantGrimrose() {}
	
	void Initialize() override;
	
	void UpdateActions() override;
	bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	
	bool HasShadow() override { return false; }
	
	bool CanBeTargeted() override;
	bool IsInvincible() const override;
	
	bool CanApplyPlantfood() override;
	bool CanEndPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	
	void onApplyCondition(PlantConditions i_condition) override;
	void onEndCondition(PlantConditions i_condition) override;
	
protected:
	OVERRIDE_STATE_ONENTER(PlantState, Idle);
	OVERRIDE_STATE_UPDATE(PlantState, Idle);
	
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, BeginAttacking);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, Attacking);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, WaitingForAttackToFinish);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, EndAttacking);
	
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, FadeAway);
	
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, PlantfoodBegin);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, PlantfoodSeekToNextTarget);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, PlantfoodWaitingForLastPortalToClose);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, PlantfoodEnd);
	
private:
	void updateCurrentLayerSet();
	
	bool isBoosted() const;
	bool zombieIsBlacklisted(const Zombie* i_zombie) const;
	RtWeakPtr<Zombie> findTargetZombie(bool i_plantFood);

	bool validateCurrentTargetOrRetargetIfPossible();
	bool isTargetZombieValid(const Zombie* i_zombie) const;
	SexyVector2 calcShadowPortalOriginPosition() const;
	SexyVector2 calcShadowPortalTargetPosition(const Zombie* i_zombieTarget) const;
	
	void createShadowStretcher();
	void stretchTowardsCurrentTarget(float i_currentLength = 0.0f);
	bool tryToRetractStretcher();
	void destroyShadowStretcher();
	int determineFurthestColumnToTarget(int i_row);

	void switchStateOnDecision(bool i_decision, uint32_t i_stateIfTrue, uint32_t i_stateIfFalse);
	
	void activateTentaclesAgainst(Zombie* i_zombie);
	bool hasReachedFinalActivation() const;
	bool hasReachedFinalPlantfoodActivation() const;
	
	std::set<RtWeakPtr<Zombie> >		m_previouslyTargetedZombiesForPF;
	RtWeakPtr<ComponentVisualStretcher>	m_shadowStretcher;
	RtWeakPtr<Zombie>					m_targettedZombie;
	RtWeakPtr<Effect_PopAnim>			m_lastOpenedShadowPortal;
	int									m_numTimesActivated;
};

class PlantAnimRig_Grimrose : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Grimrose, PlantAnimRig, RtClass);
	
	static const std::vector<std::string>				k_baseNormalLayers;
	static const std::vector<std::string>				k_baseBoostedLayers;
	static const std::vector<std::vector<std::string> > k_explosionStymenLayers;
	
	bool PlayPreviewAnim(bool bHideLayer = false) override;
	
	void SetNumTimesCanBeUse(const int i_numWhenNotBoosted, const int i_numWhenBoosted);
	void SetNumTimesCurrentlyUsed(const int i_numTimesUsed);
	
	void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowLayerSet(std::string setName);
	
	void PlayAttackBegin(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PlayAttackLoop(AnimStoppedReflectionDelegate i_onAnimLooped = {});
	void PlayAttackEnd(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
	void PlayFadeAway(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
	void PlayPlantfoodBegin(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PlayPlantfoodLoop(AnimStoppedReflectionDelegate i_onAnimLooped = {});
	void PlayPlantfoodEnd(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
protected:
	void onPopAnimInitialized() override;
	
private:
	void updateStymenLayerVisability(const std::string& i_layerSetName);
	void updateNonBoostedStymens();
	void updateBoostedStymens();
	
	AnimRigLayerSet				m_layerSet;
	int							m_timesCanBeUsedWhenNotBoosted;
	int							m_timesCanBeUsedWhenBoosted;
	int							m_numTimesUsed;
};

// -----------
// Tentacles!
// -----------

STATE_ENUM_BASE_BEGIN(GrimrosePortalState)
	GTS_PortalInvalid = 0,
	GTS_PortalOpening,
	GTS_PortalAttacking,
	GTS_PortalClosing,
STATE_ENUM_END(GrimrosePortalState);

class PlantGrimroseTentacle : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(PlantGrimroseTentacle, Effect_PopAnim, RtClass);
	PlantGrimroseTentacle();
	
	void SwallowZombie(RtWeakPtr<Zombie> i_zombie);
	void SlapZombie(RtWeakPtr<Zombie> i_zombie, float i_slapDamage);
	void SpawnAtPosition(const Sexy::SexyVector3& i_position);

	void SetExplodeDamage(float i_damage)
	{
		m_explodeDamage = i_damage;
	}
	
protected:
	void onUpdate() override;
	void onAnimStopped(const std::string& i_animLabel) override;
	
private:
	AnimationSequence createAnimSequenceForPortal() const;
	
	void onPortalOpenAnimStopped(const std::string& i_anim);
	void onPortalAttackingAnimStopped(const std::string& i_anim);
	void onPortalClosedAnimStopped(const std::string& i_anim);
	
	void setState(int32_t i_nextState);
	void onEnter(int32_t i_state);
	
	void onUpdateZombieBeingSuckedIntoPortal();
	
	int32_t							m_currentState;
	RtWeakPtr<Zombie>				m_zombieToEat;
	RtWeakPtr<Zombie>				m_zombieToSlap;
	float							m_shadowSuckVelocity;
	float							m_slapDamage;
	float							m_explodeDamage;
};

class PlantGrimroseExplode : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(PlantGrimroseExplode, Effect_PopAnim, RtClass);
	PlantGrimroseExplode();

	void startEffect(const Point& i_point, float i_explodeDamage);

protected:
	void onUpdate() override;
	void onAnimStopped(const std::string& i_animLabel) override;

private:
	void takeAreaDamage();

	float							m_explodeDamage;
	Point							m_point;
};

#endif /* Plant_Grimrose_hpp */
