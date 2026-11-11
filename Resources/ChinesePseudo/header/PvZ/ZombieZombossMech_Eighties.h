//
//  ZombieZombossMech_Eighties.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 8/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Eighties__
#define __PlantsVersusZombies2__ZombieZombossMech_Eighties__

#include "Effect_ZombossCrosshair.h"
#include "GridItemSpeaker.h"
#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"

enum StageState
{
	STAGE_INTRO,
	STAGE_IDLE,
	STAGE_DYING,
	STAGE_TALKING,
	STAGE_EXITING
};

class ZombieZombossMechEightiesProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechEightiesProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechEightiesProps()
	{}
	
	std::vector<std::string> StageJamOrder;
	std::vector<std::string> ZombossAnimOrder;
};

class ZombieZombossMech_Eighties : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Eighties, ZombieZombossMech, RtClass);
	
	void SwapJam();
	void Retreat(ZombieState i_endState) override;
	void CreateSpeakerReticle(Point i_targetLoc, float i_duration);
	void CancelSpeakerReticle(Point i_targetLoc);
	bool HasSummonAnimation() override { return false; }
	bool HasStunAnimation() override { return false; }
	bool ShouldDrawShadow() const override { return false; }
	void BeginExiting() override;
	bool UsesDefaultZombossAudio() override { return false; }
	
protected:
	void buildStunMovementCurve() override { getMovementCurve().Clear(); }
	OVERRIDE_STATE_ONENTER (ZombieState, ZombossStageChange);
	OVERRIDE_STATE_ONEXIT  (ZombieState, ZombossStageChange);
	OVERRIDE_STATE_ONENTER (ZombieState, ZombossDeath);
	
private:
	StageState m_stageState = STAGE_INTRO;
	RtWeakPtr<Effect_ZombossCrosshair> m_crosshairEffect;
	bool m_stageDamagedThisPhase = false;
	
	void registerForEvents() override;
	void unregisterForEvents() override;
	
	void onZombieAddedToBoard(Zombie* i_zombie);
	void onPlaceOnBoard() override;
	void onIntroAnimDone(const std::string& i_animName) override;
	void onUpdate() override;
	void updateStageEffect();
};

class ZombieAnimRig_ZombossMech_Eighties : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Eighties, ZombieAnimRig_ZombossMech, RtClass);
	
	ZombieAnimRig_ZombossMech_Eighties() {}
	
	const char* getPreIntroAnimName() const override;
	const char* getIntroAnimName() const override;
	const Sexy::FPoint getTeleportationEffectOffset() const override;
	bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued) override;
};

#pragma mark - ZombossEightiesDropSpeakerAction

class ZombossEightiesDropSpeakerActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossEightiesDropSpeakerActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossEightiesDropSpeakerActionDefinition()
	: FireMinColumn(0)
	, FireMaxColumn(5)
	, FireTargetEmptyWithNoDmgWeight(1)
	, FireTargetEmptyWithDmgWeight(1)
	, FireTargetPlantWeight(1)
	, DropDelay(3.f)
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	
	int FireMinColumn;
	int FireMaxColumn;
	int FireTargetEmptyWithNoDmgWeight;
	int FireTargetEmptyWithDmgWeight;
	int FireTargetPlantWeight;
	float DropDelay;
	
protected:
	bool pickSpeakerTarget(ZombieZombossMech_Eighties* i_zomboss, Point& o_targetLoc) const;
	void getSpeakerTargetSquaresInRect(ZombieZombossMech_Eighties* i_zomboss, const Rect& i_targetRect, std::vector<Point>& o_targetGridSquares, Delegate1wRet<bool, const Sexy::Point&> i_acceptSquare) const;
};

class ZombossEightiesDropSpeakerActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossEightiesDropSpeakerActionHandler, ZombieActionHandler, RtClass);
	
	ZombossEightiesDropSpeakerActionHandler()
		: m_timeToDropSpeaker(PVZ_EOT())
	{}
	
	void SetFiringData(const Point& i_targetLoc);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	
private:
	Point m_targetLoc;
	float m_timeToDropSpeaker;
};

#pragma mark - ZombossEightiesFireSpeakerRayAction

class ZombossEightiesFireSpeakerRayActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossEightiesFireSpeakerRayActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossEightiesFireSpeakerRayActionDefinition()
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	
	float ClearDelay = 0;
};

class ZombossEightiesFireSpeakerRayActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossEightiesFireSpeakerRayActionHandler, ZombieActionHandler, RtClass);
	
	ZombossEightiesFireSpeakerRayActionHandler()
		: m_timeToClearLane(PVZ_EOT())
	{}
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	
private:
	GridItemSpeakerZomboss* spawnSpeakerAt(int col, int row);
	float m_timeToClearLane;
};

#pragma mark - ZombossEightiesSwapJamAction

class ZombossEightiesSwapJamActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossEightiesSwapJamActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossEightiesSwapJamActionDefinition()
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
};

class ZombossEightiesSwapJamActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossEightiesSwapJamActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
};
#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Eighties__) */
