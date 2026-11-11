//
//  VaseBreakerFlowActionTutorials.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 8/4/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__VaseBreakerFlowActionTutorials__
#define __PlantsVersusZombies2__VaseBreakerFlowActionTutorials__

#include "VaseBreakerFlowModule.h"
#include "TimeMgr.h"
#include "MacroStateMachine.h"

STATE_ENUM_BASE_BEGIN(VaseBreakerTutorialState)
	VBTS_Start,
	VBTS_TapThePowerup,
	VBTS_UseThePowerup,
	VBTS_AfterPowerupUsage,
	VBTS_Outro,
STATE_ENUM_END(VaseBreakerTutorialState)

class VaseBreakerFlowActionTutorialBase : public VaseBreakerFlowAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionTutorialBase, VaseBreakerFlowAction, RtClass);
	VaseBreakerFlowActionTutorialBase();

protected:
	void registerForEvents() override;
	void onInitialized() override;
	void onBegin() override;
	void onUpdate() override;
	void onEnd() override;
	
	/// Override these to do your magic
	virtual void setupBoardForTutorial() {}
	virtual bool wasPowerupUsed() { return false; }
	virtual std::string getPowerupType() { return ""; }
	
	virtual SexyString getPowerupSelectAdvice() { return _S(""); }
	virtual SexyString getOutroAdvice() { return _S(""); }
	///
	
	DECLARE_FSM_HANDLER_BASE(VaseBreakerTutorialState);
	void setPowerupsFree(bool i_free);
	void setPowerupsClickable(bool i_clickable);
	void pointArrowAtPowerupButton(const std::string& i_powerupName);
	void pointArrowAtEntity(class BoardEntity* i_ent, const SexyVector3& i_offset);
	void hideArrow();
	void onPowerupSelected(class BasePowerup* i_powerup);
	void onPowerupDeactivated(class BasePowerup* i_powerup);
	
	DECLARE_FSM_STATE_VALUE(VaseBreakerTutorialState);
	pvztime_t m_stateTimer;
	RtWeakPtr<class Effect_BouncingArrow> m_bouncingArrow;
};

class VaseBreakerFlowActionRevealTutorial : public VaseBreakerFlowActionTutorialBase
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionRevealTutorial, VaseBreakerFlowActionTutorialBase, RtClass);
	
protected:
	void setupBoardForTutorial() override;
	bool wasPowerupUsed() override;
	std::string getPowerupType() override;
	SexyString getPowerupSelectAdvice() override;
	SexyString getOutroAdvice() override;
	
	void onEnd() override;
	
	DECLARE_FSM_HANDLER_DERIVED(VaseBreakerTutorialState);
	
	std::vector<RtWeakPtr<class GridItemVase> > m_spawnedVases;
};

class VaseBreakerFlowActionMoveTutorial : public VaseBreakerFlowActionTutorialBase
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionMoveTutorial, VaseBreakerFlowActionTutorialBase, RtClass);
	
protected:
	void setupBoardForTutorial() override;
	bool wasPowerupUsed() override;
	std::string getPowerupType() override;
	SexyString getPowerupSelectAdvice() override;
	SexyString getOutroAdvice() override;
	
	void onEnd() override;

	DECLARE_FSM_HANDLER_DERIVED(VaseBreakerTutorialState);
	
	std::vector<std::string> m_forceLoadedResourceGroups;
	RtWeakPtr<class GridItemVase> m_movableVase;
};

class VaseBreakerFlowActionButterTutorial : public VaseBreakerFlowActionTutorialBase
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowActionButterTutorial, VaseBreakerFlowActionTutorialBase, RtClass);
	
protected:
	void setupBoardForTutorial() override;
	bool wasPowerupUsed() override;
	std::string getPowerupType() override;
	SexyString getPowerupSelectAdvice() override;
	SexyString getOutroAdvice() override;

	void onEnd() override;

	DECLARE_FSM_HANDLER_DERIVED(VaseBreakerTutorialState);

	std::vector<std::string> m_forceLoadedResourceGroups;
	RtWeakPtr<class Zombie> m_spawnedZombie;
};

#endif /* defined(__PlantsVersusZombies2__VaseBreakerFlowActionTutorials__) */
