//
//  LevelModuleManager.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelModuleManager_h
#define PlantsVersusZombies2_LevelModuleManager_h

#include "RtObject.h"
#include "LevelDefinition.h"
#include "LevelModule.h"
#include "Outros.h"

namespace Message
{
    void ModuleManagerInitializedForLevelDefinition(LevelDefinitionPtr& io_levelDefinition);
	void InitializingModuleManagerForLevelDefinition(LevelDefinitionPtr& io_levelDefinition);
	void LoadingModuleForProps(LevelModulePropertiesPtr& io_levelModuleProperties);
}

class LevelModuleManager : public RtObject
{
public:
	RT_CLASS_DEFINE(LevelModuleManager, RtObject, RtClass);
	
	LevelModuleManager()
	{
		m_handlesIntro = false;
	}
	~LevelModuleManager()
	{
	}
    
	// Initialization
	void InitializeFromLevel(RtWeakPtr<class LevelDefinition> i_level, bool i_hardAuto);
	void AddModuleFromProperties(RtWeakPtr<const class LevelModuleProperties> i_levelModule);
	LevelModule* AddRuntimeModuleFromProperties(RtWeakPtr<const class LevelModuleProperties> i_levelModule);
	
	// Restoring from a save
	void PostLoad();

	// Access to modules
	class StageModule* GetStageModule();
	template <typename T>
	T* GetModuleByClass();
	LevelModule* GetModuleByClass(RtClass* i_moduleClass);
	
	const std::vector<RtWeakPtr<class LevelModule> >& GetModules() { return m_modules; }

	const std::set<std::string>& GetLoadedResourceGroups() const;
	
	// Load loop
	void StartLoad();			// Collect all required resources, start loading them
	bool IsLoadComplete();		// Return false until we're done
	void CompleteLoad();		// Do final setup on any resources
	void Unload();
	void UnloadAllZombies();

	void IncreaseRefCounts();	// For tutorial skipping.
	void ReduceRefCounts();		// For tutorial skipping.
    
    void AddVictoryModule(LevelDefinitionPtr ptrLevel);
    void AddLossModule(OutroType i_type, LevelDefinitionPtr ptrLevel);
	
	bool HandlesIntro() const
	{
		return m_handlesIntro;
	}
	
	// These are events that the modules can register to
	void OnLoadStarted()
	{
		m_onLoadStarted();
	}
	void OnLoadComplete()
	{
		m_onLoadComplete();
	}
	void OnLevelInit()
	{
		m_onLevelInit();
	}
	void OnIntroStarted()
	{
		m_onIntroStarted();
	}
	void OnGameplayStarted()
	{
		m_onGameplayStarted();
	}
	void OnGameplayUpdate()
	{
		m_onGameplayUpdate();
	}
	void OnGameplayRealUpdate()
	{
		m_onGameplayRealUpdate();
	}
	void OnGameplayEnded()
	{
		m_onGameplayEnded();
	}
	void OnWinOutroStarted()
	{
		m_onWinOutroStarted();
	}
	void OnLossOutroStarted()
	{
		m_onLossOutroStarted();
	}
	void OnLossImminent()
	{
		m_onLossImminent();
	}
	void OnLevelEnded()
	{
		m_onLevelEnded();
	}
	
	void OnUpdate();
	void OnLossAversionUpsellUpdate();
	
	void OnPauseStateChange(bool i_paused)
	{
		m_onPauseStateChange(i_paused);
	}
	
	bool GetWinConditionsSatisfied()
	{
		return m_testWinCondition();
	}
	bool GetPreventSave()
	{
		return m_testPreventSave();
	}
	
	void AddToRenderQueue(class RenderQueue* i_queue)
	{
		m_addToRenderQueue(i_queue);
	}
	
	void AddToUIRenderQueue(class RenderQueue* i_queue)
	{
		m_addToUIRenderQueue(i_queue);
	}

	// These are the registration functions
	void RegisterOnLoadStarted(Delegate0 i_onLoadStarted)
	{
		m_onLoadStarted += i_onLoadStarted;
	}
	void RegisterOnLoadComplete(Delegate0 i_onLoadComplete)
	{
		m_onLoadComplete += i_onLoadComplete;
	}
	void RegisterOnLevelInit(Delegate0 i_onLevelInit)
	{
		m_onLevelInit += i_onLevelInit;
	}
	void RegisterOnIntroStarted(Delegate0 i_onIntroStarted)
	{
		m_onIntroStarted += i_onIntroStarted;
	}
	void RegisterOnGameplayStarted(Delegate0 i_onGameplayStarted)
	{
		m_onGameplayStarted += i_onGameplayStarted;
	}
	void RegisterOnGameplayUpdate(Delegate0 i_onGameplayUpdate)
	{
		m_onGameplayUpdate += i_onGameplayUpdate;
	}
	void RegisterOnGameplayRealUpdate(Delegate0 i_onGameplayRealUpdate)
	{
		m_onGameplayRealUpdate += i_onGameplayRealUpdate;
	}
	void RegisterOnGameplayEnded(Delegate0 i_onGameplayEnded)
	{
		m_onGameplayEnded += i_onGameplayEnded;
	}
	void RegisterOnWinOutroStarted(Delegate0 i_onOutroStarted)
	{
		m_onWinOutroStarted += i_onOutroStarted;
	}
	void RegisterOnLossOutroStarted(Delegate0 i_onOutroStarted)
	{
		m_onLossOutroStarted += i_onOutroStarted;
	}
	void RegisterOnLossImminent(Delegate0 i_onLossImminent)
	{
		m_onLossImminent += i_onLossImminent;
	}
	void RegisterOnLevelEnded(Delegate0 i_onLevelEnded)
	{
		m_onLevelEnded += i_onLevelEnded;
	}
	
	void RegisterOnUpdate(Delegate0 i_onUpdate)
	{
		m_onUpdate += i_onUpdate;
	}
	void RegisterOnLossAversionUpsellUpdate(Delegate0 i_onUpdate)
	{
		m_onLossAversionUpsellUpdate += i_onUpdate;
	}
	void RegisterOnPauseStateChange(Delegate1<bool> i_onPauseStateChange)
	{	
		m_onPauseStateChange += i_onPauseStateChange;
	}
	
	void RegisterAddToRenderQueue(Delegate1<RenderQueue*> i_addToRenderQueue)
	{
		m_addToRenderQueue += i_addToRenderQueue;
	}
	
	void RegisterAddToUIRenderQueue(Delegate1<RenderQueue*> i_addToRenderQueue)
	{
		m_addToUIRenderQueue += i_addToRenderQueue;
	}

	// Use these to tell the board that you're handling an intro or outro
	void RegisterHandlesIntro()
	{
		DBG_ASSERT(!m_handlesIntro); 
		m_handlesIntro = true;
	}
	
	// Subscribe to this and return whether your win condition has been satisfied
	void RegisterWinCondition(Delegate0wRet<bool> i_testWinCondition)
	{
		m_testWinCondition += i_testWinCondition;
	}
	
	void RegisterCanPreventSave(Delegate0wRet<bool> i_testPreventSave)
	{
		m_testPreventSave += i_testPreventSave;
	}
		

private:
	LevelModule* createLevelModule(RtWeakPtr<const class LevelModuleProperties> i_levelModule);
	void gatherModuleResources(class LevelModule* i_module, std::set<std::string>& o_groupNames);
    
	void createAndInitializeLevelModule(RtWeakPtr<const class LevelModuleProperties> i_levelModuleProperties, std::vector<LevelModule*>& io_createdModules) const;

	void createAndInitializeLevelModulePVZ1Mode(RtWeakPtr<const class LevelModuleProperties> i_levelModuleProperties, std::vector<LevelModule*>& io_createdModules,  std::vector<bool> selectCondition) const;

    void gatherModuleInstanceAndPropertySheetResources(class LevelModule* i_module, std::set<std::string>& o_groupNames) const;
    
    void addInitializedLevelModule(LevelModule* i_module);

    void AddPlantTrialModule();
    void AddHardLevelModule();
    void AddRiftThemeModule();
    void AddArtifactModuleIfNeeded();
    void AddCardGameModulesIfNeeded();
    void AddNewPVPGameModulesIfNeeded();
	void AddHeroPlantModulesIfNeeded();
    
    struct TrialData* GetTrialDataInTheLevel();
	
	/// Serializable properties
	std::vector<RtWeakPtr<class LevelModule> > 	m_modules;
	std::vector<std::string>					m_resourceGroupList;
	
	/// Transient properties
	// Bare pointers to LevelModules because they shouldn't change over the course of our lifetime
	std::vector<class LevelModule*> m_runtimeModulesToAdd;
	std::set<std::string> m_resourceGroupNames;
	
	bool m_handlesIntro;
	
	Event0 m_onLoadStarted;
	Event0 m_onLoadComplete;
	Event0 m_onLevelInit;
	Event0 m_onIntroStarted;
	Event0 m_onGameplayStarted;
	Event0 m_onGameplayUpdate;
	Event0 m_onGameplayRealUpdate;
	Event0 m_onGameplayEnded;
	Event0 m_onWinOutroStarted;
	Event0 m_onLossOutroStarted;
	Event0 m_onLossImminent;
	Event0 m_onLevelEnded;
	
	Event0 m_onUpdate;
	Event0 m_onLossAversionUpsellUpdate;
	
	Event1<bool> m_onPauseStateChange;
	
	Event0wRet<EventReturnBehavior::LogicalAnd_ShortCircuit_DefaultFalse, bool> m_testWinCondition;
	Event0wRet<EventReturnBehavior::LogicalOr_NoShortCircuit_DefaultFalse, bool> m_testPreventSave;

	Event1<RenderQueue*> m_addToRenderQueue;
	Event1<RenderQueue*> m_addToUIRenderQueue;
};

template<typename T>
T* LevelModuleManager::GetModuleByClass()
{
	LevelModule* levelMod = GetModuleByClass(T::StaticGetClass());
	if (levelMod)
	{
		return levelMod->CastChecked<T>();
	}
	return NULL;
}

#endif
