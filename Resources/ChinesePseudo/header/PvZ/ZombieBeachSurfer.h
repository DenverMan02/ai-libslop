//
//  ZombieBeachSurfer.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 6/15/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIESURFER_H__
#define __ZOMBIESURFER_H__

#include "GravestoneAnimRig.h"
#include "GridItemGravestone.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieBeachSurferState, ZombieState)
	ZS_Surfer_Surfing,
	ZS_Surfer_SlamBoard,
	ZS_Surfer_SurfingToWalking,
STATE_ENUM_END(ZombieBeachSurferState);

class ZombieBeachSurfer : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBeachSurfer, Zombie, RtClass);

	ZombieBeachSurfer();

	bool ShouldClipWithWater() const override;

	Rect CalcZombieAttackRect() override;
	
	bool IsSurfing() const;
	bool IsOnFoot() const;
	void FallOffBoard();
	void ShatterBoardInstantly();
    bool ShouldDrawShadow() const override;
	
protected:
    // states
    DECLARE_STATE_FUNCTIONS(ZombieState, Surfing);
    DECLARE_STATE_FUNCTIONS(ZombieState, SlamBoard);
    DECLARE_STATE_FUNCTIONS(ZombieState, SurfingToWalking);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	void onApplyCondition(ZombieConditions i_condition) override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void onPlaceOnBoard() override;
	void onPlaceOnStreet() override;
	float getHeadDropFraction() const override;

	ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
	void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
	DamageInfo takeHelmDamage(const DamageInfo& i_incomingDamage) override;
	bool hasHeadParticle() const override;
	
private:
	bool hasBoard();
	void slamBoard(bool i_dropped, int i_helmHitpoints);
	void spawnBoardShatterEffect(const Sexy::Point& i_targetPosition, const std::string& i_animationName);
	Point getDefaultBoardSpawnPosition();
	void updateBoardDamage();

	bool canSpawnBoardAt(const Point& i_targetPosition) const;
	class GridItemSurfboard* tryPlaceBoard(const Point& i_gridPosition);

	void onSlamAnimCompleted(const std::string&);
	void onSurfToWalkAnimCompleted(const std::string&);

	bool isOnWater() const;
};

enum ZombieAnimRigState_BeachSurfer
{
	ZOMBIEANIM_BEACHSURFER_SURFING = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_BEACHSURFER_SLAMBOARD,
	ZOMBIEANIM_BEACHSURFER_SURFTOWALK,
};

class ZombieAnimRig_BeachSurfer : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BeachSurfer, ZombieAnimRig, RtClass);

	bool PlaySurf();
    bool PlaySurfWithoutWave();
	bool PlaySlam(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlaySurfToWalk(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

    bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	
	void HideSurfboard();
	void UpdateSurfboardDamageState(int i_damageIndex);

protected:
	const std::string getWalkAnimationName() override;
	const std::string getDieAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const bool getDieShouldBlend() override { return false; }
    
private:
	bool m_hasSurfboard = true;
};

class GridItemSurfboardProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemSurfboardProps, GridItemGravestonePropertySheet, RtClass);
};

class GridItemSurfboard : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemSurfboard, GridItemGravestone, RtClass);

	void CalcDamageState();
	bool ShouldClipWithWater() const override;
	PlantingReason GetCantPlantReason() const override;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;

private:
	void updateGroundEffect();
};

class SurfboardAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(SurfboardAnimRig, GravestoneAnimRig, RtClass);
    
    SurfboardAnimRig();

	void PlayFlip();
	void PlayStationary();
    
    void SetDamageState(int i_damageState, bool i_isAnimated) override;
    
    void onAnimStopped() override;
    
private:
    int m_queuedDamageStateAnim;
    bool m_inIntroAnim;
};



#endif
