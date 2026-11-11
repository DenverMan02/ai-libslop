//
//  ZombossLastStandMinigame.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-2-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombossLastStandMinigame__
#define __PlantsVersusZombies2__ZombossLastStandMinigame__

#include "StandardLevelIntro.h"
#include "Core.h"
#include "ButtonListener.h"
#include "GameNotify.h"
#include "ZombieSkillUtils.h"
#include "Zombie.h"

class ZombossLastStandMinigameModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(ZombossLastStandMinigameModule, StandardLevelIntro, RtClass);
    
    virtual void onPostLoad() override;
    void SendZombossMusicEvent(const std::string &i_event);
    int getStartStageIndex();
    int GetRetreatColumn() const;
protected:
	ZombossLastStandMinigameModule();
	
	virtual void registerForEvents() override;
    
	void onViewBoardOrZombiesButtonPressed();
	void onStartGameButtonPressed();
    void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
    
	enum State
	{
		PVZ_BEGIN_ENUM(STATE_LSM_),
		STATE_LSM_START,
		STATE_LSM_INTRO,
		STATE_LSM_START_PLANTING,
		STATE_LSM_PLANTING,
		STATE_LSM_TO_VIEWING_ZOMBIES,
		STATE_LSM_VIEW_ZOMBIES,
		STATE_LSM_FROM_ZOMBIES_TO_PLANTING,
		STATE_LSM_PLAYING,
		PVZ_END_ENUM(STATE_LSM_),
	};
    
public:
    bool isPlayingGame(){return m_lastStandState == STATE_LSM_PLAYING;}
    
    
private:
	
    void OnLuaNotify(const std::string& rLuaEvent);
    void PlayIntro(void);

	virtual void bringUpSeedChooser() override;
	
	
	void onLoadComplete() override;
	void startIntro();
	void onUpdate();
	void onGameplayStarted();
	void onEndLevel();
	void onViewZombiesComplete();
    
	void setState(State i_state);

	void findStreetZombieForZomboss(const CZombieSummonDataPool* i_summonPool);
	void placeSteetZombieForZomboss(int &i_startGridX, int &i_startGridY, Zombie* boss);
    
	void setToolsState(const bool i_introState);
    void onPlantPlanted(Plant* i_plant);
    void onPlantShoveled(Plant* i_plant);
    int  GetPlantCount() const;
    
    void startGame();
    
    void onShowProgressMeterFinished();
    
    bool checkWin();
    
	State     m_lastStandState;
	pvztime_t m_stateEntryTime;
    bool	  m_doesPlayerWin;
    
    RtWeakPtr<class Zomboss> m_zomboss;
    std::vector<RtWeakPtr<class Zombie> > m_streetZombies;
    int m_streetZombieCount;
    std::string m_lastZombossMusicEventSent;
};

class ZombossLastStandMinigameProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(ZombossLastStandMinigameProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return ZombossLastStandMinigameModule::StaticGetClass();
	}
    
	ZombossLastStandMinigameProperties()
	{
		StartingSun = 0;
		StartingPlantfood = 0;
        ZombossInitialGridCol = 1;
        ZombossInitialGridRow = 1;
        ZombossStartStageIndex = 0;
	}
	
	int StartingSun;
	int StartingPlantfood;
    int ReservedColumnCount = 2;
    bool SkipPlanting = false;
    
    std::string	ZombossTypeName;
	int 		ZombossInitialGridCol;
	int			ZombossInitialGridRow;
	int			ZombossStartStageIndex;
};

#endif /* defined(__PlantsVersusZombies2__ZombossLastStandMinigame__) */
