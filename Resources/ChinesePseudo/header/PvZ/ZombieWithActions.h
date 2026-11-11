//
//  ZombieAction.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 5/9/12.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEWITHACTIONS_H__
#define __ZOMBIEWITHACTIONS_H__

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAction.h"

typedef RtWeakPtr<const class ZombieActionDefinition> ZombieActionDefinitionPtr;

STATE_ENUM_CHILD_BEGIN(ZombieWithActionsState, ZombieState)
	ZombiePullFromActionQueue,
	ZombiePerformAction,
	ZombiePickNextAction,
STATE_ENUM_END(ZombieWithActionsState);

class ZombieWithActions : public Zombie
{
public:
	void onZombieInitialize() override;
	
	RT_CLASS_DEFINE(ZombieWithActions, Zombie, RtClass);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombiePullFromActionQueue)
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombiePerformAction);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombiePickNextAction);
	
	template<typename T>
	T* QueueAction(ZombieActionDefinitionPtr i_definition);
	bool QueueActionImmediate(ZombieActionDefinitionPtr i_action);
	
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	virtual bool TryJamAction(GridItem *item) { return false; }
	void CancelCurrentAction();
	RtWeakPtr<ZombieActionHandler> GetCurrentAction() { return m_currentAction; }
	int m_actionRepeatsLeft;
	ZombieActionPhase m_queuedPhaseAfterAction;
	ZombieActionPhase m_queuedPhaseAfterActionRepeatsLeftZero;
	float t_die = 0;
protected:
	// Phases (sets of actions)

    void SetPhase(ZombieActionPhase i_nextPhase) { if (m_currentPhase != i_nextPhase) { m_currentPhase = i_nextPhase; onPhaseChanged(); } }
	ZombieActionPhase GetPhase() { return m_currentPhase; }

    virtual void onPhaseChanged() {}
protected:
	// Action picking
	
    bool tryRepeatAction();
	bool tryStartActionRandom(const std::vector<RtWeakPtr<ZombieActionDefinition> >& i_actions);
	bool tryStartAction(ZombieActionDefinitionPtr i_action);
	int pickRandomRepeatCountForAction(ZombieActionDefinitionPtr i_action) const;
	void clearActionQueue();
	
	void setStateOnActionQueueEmpty(ZombieState i_zombieState);
	ZombieState getStateOnActionQueueEmpty() const { return m_queueEmptyState; }
	
	void clearActionRepeats() { m_actionRepeatsLeft = 0; }

	class ZombieActionHandler* getCurrentAction() const;
	
	template<typename T>
	ZombieActionDefinitionPtr getBaseActionDefinition() const;
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
protected:
	ZombieState m_queueEmptyState = ZombieState_INVALID;
//	ZombieActionPhase m_queuedPhaseAfterAction;

//	int m_actionRepeatsLeft = 0;
	ZombieActionPhase m_currentPhase;
	ZombieActionDefinitionPtr m_lastAction;

	RtWeakPtr<ZombieActionHandler> m_currentAction;
	std::vector<RtWeakPtr<ZombieActionHandler> > m_actionQueue;
};

template<typename T>
T* ZombieWithActions::QueueAction(ZombieActionDefinitionPtr i_definition)
{
	T* handler = GameObject::Create<T>(PVZDB::TABLE_GAMEOBJECTS);
	handler->InitFromDefinition(this, i_definition);
	m_actionQueue.push_back(handler->GetPtr());
	return handler;
}


template<typename T>
ZombieActionDefinitionPtr ZombieWithActions::getBaseActionDefinition() const
{
	for (auto i : GetProps<ZombieWithActionsProps>()->Actions)
	{
		if (i->IsA<T>())
		{
			return i;
		}
	}
	
	return nullptr;
}

#endif

