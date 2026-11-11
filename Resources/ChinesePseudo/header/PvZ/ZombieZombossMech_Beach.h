//
//  ZombieZombossMech_Beach.h
//  PlantsVersusZombies2
//
//  Created by Brad Buchanan on 10/7/2014.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Beach__
#define __PlantsVersusZombies2__ZombieZombossMech_Beach__

#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"
#include "SharkMinion.h"

class SharkMinion;

#pragma mark - Custom Actions

#pragma mark Beach Dive Action
// This action embodies the shark diving and resurfacing in a different location

class ZombossBeachDiveActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossBeachDiveActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossBeachDiveActionDefinition()
	: SubmergedDuration(0.f)
	, PreferSquashChance(0.f)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	bool PickEmergePosition(class ZombieZombossMech* i_zomboss, Point& o_targetPosition) const;
	
	float SubmergedDuration;
	float PreferSquashChance;
};

class ZombossBeachDiveActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossBeachDiveActionHandler, ZombieActionHandler, RtClass);

	void SetEmergeTarget(const Point& i_emergeTarget, float i_submergedDuration);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	
	void onSubmergeAnimDone(const std::string& i_animName);
	void onEmergeAnimDone(const std::string& i_animName);
	
private:
	Point m_emergeTarget;
	float m_submergedDuration = 0.0f;
	float m_emergeTime = PVZ_EOT();
};

#pragma mark Fan Pull Action

class ZombossFanPullActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossFanPullActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossFanPullActionDefinition()
	: FanDuration(5.0f)
	, PlantfoodDamageToInterrupt(100.f)
	, BasePullTimePerGridSquare(0.1f)
	, AdditionalPullTimePerLinearDistanceFromFan(0.f)
	, AdditionalPullTimePerSquaredDistanceFromFan(0.f)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void FindTargetsInFrontOfFan(class ZombieZombossMech_Beach* i_zomboss, BoardEntityTypeFlag i_acceptedTypes, std::vector<BoardEntity*>& o_targets) const;
	
	float FanDuration;
	float PlantfoodDamageToInterrupt;
	float BasePullTimePerGridSquare;
	float AdditionalPullTimePerLinearDistanceFromFan;
	float AdditionalPullTimePerSquaredDistanceFromFan;
};

class ZombossFanPullActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossFanPullActionHandler, ZombieActionHandler, RtClass);
	
	ZombossFanPullActionHandler()
	: m_isSuctionOn(false)
	, m_fanEndTime(PVZ_EOT())
	{}
	
	bool IsPulling() const;
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void onFanPullStartEnded(const std::string& i_animName);
	void onFanPullEndEnded(const std::string& i_animName);
	
	// Top-level suction management
	void beginSuction();
	void pullTargets();
	void endSuction();
	static void sortTargets(std::vector<BoardEntity*>& io_targets);
	DamageInfo makeFanDamageInfo() const;
	float calculatePullTimeForOneGridSquare(const float i_distanceFromFan) const;
	
	// Plant suction
	void beginPlantSuction() {}
	// void pullPlant(Plant* i_plant);
	void pullPlantGroup(class PlantGroup* i_plantGroup);
	void endPlantSuction() {}
	void spawnPlantGuts(const BoardEntity* i_destroyedPlant);
	
	// Zombie suction
	void beginZombieSuction();
	void pullZombie(Zombie* i_zombie);
	void endZombieSuction();
	bool hasControlOfZombie(const Zombie* i_zombie) const;
	bool canTakeControlOfZombie(const Zombie* i_zombie) const;
	bool canFanStunZombie(const Zombie* i_zombie) const;
	void moveZombieTowardFan(Zombie* i_zombie);
	bool isZombieTouchingFan(const Zombie* i_zombie) const;
	void spawnZombieBits(Zombie* i_zombie) const;
    
    static bool SortCall(const BoardEntity* left, const BoardEntity* right);

	
	bool m_isSuctionOn;
	float m_fanEndTime;
	std::vector<RtWeakPtr<Zombie> > m_zombiesBeingPulled;
};

#pragma mark - Shark Minion Attack Action

class ZombossSharkMinionAttackActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSharkMinionAttackActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossSharkMinionAttackActionDefinition()
	: SharksToLaunch(0)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	int SharksToLaunch;
};

class ZombossSharkMinionAttackActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSharkMinionAttackActionHandler, ZombieActionHandler, RtClass);
	
	ZombossSharkMinionAttackActionHandler()
	{}
	
protected:
	void onStartAction() override;
	void onSummonAnimDone(const std::string& i_animName);
	
};

#pragma mark - Props

class ZombieZombossMechBeachProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechBeachProps, ZombieZombossMechProps, RtClass);

	ZombieZombossMechBeachProps()
	: TangleKelpStunDuration(0.f)
	, TangleKelpStunShouldUseKnockback(false)
	, TangleKelpStunShouldUseFlash(false)
	, RetreatSubmergedDuration(0.f)
	{}
	
	float TangleKelpStunDuration;
	bool TangleKelpStunShouldUseKnockback;
	bool TangleKelpStunShouldUseFlash;
	float RetreatSubmergedDuration;
	SharkMinionParameters MinionParameters;
};

#pragma mark - Zomboss

STATE_ENUM_CHILD_BEGIN(ZombossBeachMechState, ZombossMechState)
	ZombossBeachTangleKelpStun,
STATE_ENUM_END(ZombossBeachMechState);


class ZombieZombossMech_Beach : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Beach, ZombieZombossMech, RtClass);

	ZombieZombossMech_Beach();
	virtual ~ZombieZombossMech_Beach();
	
	bool ShouldClipWithWater() const override { return false; }
	
	void SetSubmerged(bool i_isSubmerged);
	bool IsSubmerged() const;
	
	void StartTangleKelpStun();
	
	void Retreat(ZombieState i_endState) override;
	
	bool CanAnyMinionAttack();
	void TellMinionsToAttack(int i_numberOfAttacks);

	bool TryHandleSummonZombie(Zombie* i_zombie, const SexyVector3& i_targetPosition) const override;
	
	void SetWindEffectEnabled(bool i_enabled);
	
	Sexy::Rect CalcMouthFootprint() const;
	Sexy::Rect CalcBellyFootprint() const;

protected:
	void onPlaceOnBoard() override;
	void onUpdate() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) override;
	SexyVector3 getDamageEffectsBoardSpaceOffset() const override;
	
	OVERRIDE_STATE_ONENTER(ZombieState, ZombossIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, TangleKelpStun);
	OVERRIDE_STATE_ONEXIT(ZombieState, ZombossStun);
	OVERRIDE_STATE_ONEXIT(ZombieState, ZombossStageChange);
	
private:
	void onTangleKelpStunAnimDone(const std::string& i_animLabel);
	void onTangleKelpStunEndAnimDone(const std::string& i_animLabel);
	
	void createWindEffect();
	void updateWindEffect();
	void createMinions();
	
	bool m_isSubmerged;
	bool m_playingTangleKelpStunStart;
	bool m_playingTangleKelpStunEnd;
	std::vector<RtWeakPtr<SharkMinion> > m_minions;
	RtWeakPtr<Effect_PopAnim> m_windEffect;
	bool m_isWindEffectEnabled;
};

#pragma mark - Anim Rig

class ZombieAnimRig_ZombossMech_Beach : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Beach, ZombieAnimRig_ZombossMech, RtClass);

	ZombieAnimRig_ZombossMech_Beach()
		: m_playingIdle(false)
	{}
	
	bool PlaySubmerge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayEmerge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	bool PlayFanPullStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayFanPullLoop();
	bool PlayFanPullEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	bool PlayLobbedFireStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLobbedFireAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayLobbedFireEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	bool PlayTangleKelpStunStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayTangleKelpStunLoop();
	bool PlayTangleKelpStunEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	void PlayIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	void PlayWalkForDirection(ZombossWalkDirection i_walkDir, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	
	const Sexy::FPoint getTeleportationEffectOffset() const override;
	
protected:
	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	const char* getSummoningAnimName() const override;
	void onPostPlayCalled() override;
private:
	bool m_playingIdle;
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Beach__) */
