//
//  VaseBreakerFlowModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__VaseBreakerFlowModule__
#define __PlantsVersusZombies2__VaseBreakerFlowModule__

#include "LevelModule.h"
#include "RunnableAction.h"

class VaseBreakerFlowModule;
class VaseBreakerModule;

class VaseBreakerFlowAction : public GameObject, public RunnableAction
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowAction, GameObject, RtClass);
	
	void SetOwningModules(VaseBreakerFlowModule* i_flowModule, VaseBreakerModule* i_vaseBreakerModule);
	
    void AddToRenderQueue(class RenderQueue* i_queue);
	
protected:
	void onBegin() override {}
	void onUpdate() override {}
	void onEnd() override {}
	
	virtual void onAddToRenderQueue(class RenderQueue* i_queue) {}
	
	VaseBreakerFlowModule* getFlow() const;
	VaseBreakerModule* getVaseBreaker() const;
	
private:
	RtWeakPtr<VaseBreakerFlowModule> m_flow;
	RtWeakPtr<VaseBreakerModule> m_vb;
};

class VaseBreakerFlowModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowModule, LevelModule, RtClass);
	
	VaseBreakerFlowModule();

	VaseBreakerFlowAction* CreateAndAddAction(RtClass* i_actionClass);
	template<typename T>
	T* CreateAndAddAction();
	
	void StartEndlessVictoryFlow(int i_completedWave, bool i_newRecord, const std::string& i_unlockedPowerup);
	
protected:
	void registerForEvents() override;
	void postInitialize() override;
	
private:
	void updateActions();
	void setupInitialFlow();
	void addStartGameplayFlow();
	void addIntroNarrative();
	void addRequiredTutorials();
	void addActionsForPowerupTutorial(const std::string& i_powerupTypeName);
    
    void addToRenderQueue(class RenderQueue* i_queue);
	
	RtWeakPtr<VaseBreakerModule> m_vbModule;
	std::vector<RtWeakPtr<VaseBreakerFlowAction> > m_actionQueue;
};

template<typename T>
T* VaseBreakerFlowModule::CreateAndAddAction()
{
	VaseBreakerFlowAction* action = CreateAndAddAction(T::StaticGetClass());
	return (action->CastChecked<T>());
}


class VaseBreakerFlowModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(VaseBreakerFlowModuleProperties, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return VaseBreakerFlowModule::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__VaseBreakerFlowModule__) */
