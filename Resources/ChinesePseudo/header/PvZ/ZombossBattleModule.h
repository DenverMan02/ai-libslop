//
//  ZombossBattleModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 9/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombossBattleModule_h
#define PlantsVersusZombies2_ZombossBattleModule_h

#include <string>
#include <vector>

#include "BoardEnums.h"
#include "LevelModule.h"
#include "MacroStateMachine.h"
#include "Point.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "VictoryOutro.h"

class PlantType;

STATE_ENUM_BASE_BEGIN(ZombossBattleState)
	ZBS_Initial,
	ZBS_SpawningMech,
	ZBS_FightingMech,
	ZBS_ZombossDying,
	ZBS_ZombossDead,
	ZBS_Done,
STATE_ENUM_END(ZombossBattleState);

class ZombossBattleModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ZombossBattleModule, LevelModule, RtClass);
    
    int GetRetreatColumn() const;
    Point GetDeathLocation() const;
    bool IsZombossDone();
    void TriggerZombossExit();
    void ShowZombossIntro();
    
    void SendZombossMusicEvent(const std::string& i_event);
	
	int GetZombossStartStageIndex() const;
    int GetZombossStageCount() const;
    
protected:
	// Virtual interfaces
	void onInitialized() override;
	virtual void onLoadComplete();
	void onPostLoad() override;
	virtual void OnGameplayStarted();
	void initializeModule() override;
	void registerForEvents() override;
	virtual std::string GetZombossMechType();
	
	DECLARE_FSM_HANDLER_BASE(ZombossBattleState);

private:
	void spawnInitialZomboss();
	void startZombossBattling();
	void onUpdate();
	void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	bool checkWinCondition();
	void playZombossIntroMusic();
	void playZombossOutroMusic();
	void playZombossFailureMusic();
	
	void showProgressMeter() const;
	void hideProgressMeter() const;
	void updateProgressMeter() const;
	std::string getBossMeterUIName() const;
	
	void onLastStandInit();
	void onLastStandStart();
	void spawnZomboss();

	pvztime_t m_spawnZombossAtTime;
	ZombiePtr m_currentZombossMech;
	std::string m_lastZombossMusicEventSent;
	bool m_battleStarted;
	bool m_waitingForLastStand;
	
	DECLARE_FSM_STATE_VALUE(ZombossBattleState);
};

class ZombossBattleModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ZombossBattleModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return ZombossBattleModule::StaticGetClass();
	}
	
	ZombossBattleModuleProperties()
    {
        ZombossStartStageIndex = 0;
    }

	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	virtual void GatherSpecialRequirements(std::set<std::string> &io_resourceGroupNames) const;
	
	// Where to spawn a new Zomboss mech
	Point	ZombossSpawnGridPosition;
	
	// Number of columns in the back of the board to reserve for Zomboss usage
	// Whenever Zomboss retreats to the back of the board, he'll jump into a square
	// in the leftmost reserved column
	int		ReservedColumnCount = 0;
	
	// Positioning of Zomboss when he dies
	int		ZombossDeathRow = 1;
	int		ZombossDeathColumn = 1;

	// We'll go through this list, starting with the first mech and finishing with the last
	// As mechs are destroyed, resource groups are loaded in and out for them
	std::string ZombossMechType;
    
    int     ZombossStartStageIndex = 0;
    int     ZombossStageCount = 0;
};

class ModernZombossBattleModule : public ZombossBattleModule
{
public:
	RT_CLASS_DEFINE(ModernZombossBattleModule, ZombossBattleModule, RtClass);

	ModernZombossBattleModule();

protected:
	void onLoadComplete() override;
	std::string GetZombossMechType() override;
private:
	void GatherResources(std::set<std::string> &io_resourceGroupNames);
	void loadTargetZomboss();
	void pickRandomZomboss();
	std::string m_zombossMechType;
};

class ModernZombossBattleModuleProperties : public ZombossBattleModuleProperties
{
public:
	RT_CLASS_DEFINE(ModernZombossBattleModuleProperties, ZombossBattleModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return ModernZombossBattleModule::StaticGetClass();
	}

	void GatherSpecialRequirements(std::set<std::string> &io_resourceGroupNames) const override;

	std::vector<std::string> ZombossMechPool;
};

class ZombossVictoryOutroModule : public VictoryOutroModule
{
public:
    RT_CLASS_DEFINE(ZombossVictoryOutroModule, VictoryOutroModule, RtClass);
    
protected:
	void		startCoinShower() override;
	void		startBoardFade() override;
	void		onUpdate() override;
};

class ZombossVictoryOutroProperties : public VictoryOutroProperties
{
public:
    RT_CLASS_DEFINE(ZombossVictoryOutroProperties, VictoryOutroProperties, RtClass);
	
	RtClass* GetModuleClass() const override
    {
        return ZombossVictoryOutroModule::StaticGetClass();
    }
};

#endif
