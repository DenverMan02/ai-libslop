//
//  LastStandMinigame.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 3/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LastStandMinigame__
#define __PlantsVersusZombies2__LastStandMinigame__

#include "StandardLevelIntro.h"
#include "Core.h"
#include "ButtonListener.h"
#include "GameNotify.h"
#include "PVZTypes.h"
#include "Plant.h"
#include "ZombieZombossMech.h"
#include "PlantType.h"

class LastStandMinigameModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(LastStandMinigameModule, StandardLevelIntro, RtClass);

	bool IsPlantingDone();
	bool IsPlantDisabled(const std::string& i_plantName);

protected:
	LastStandMinigameModule();
	
	virtual void registerForEvents() override;
    virtual bool isConsumableInstantPlant(PlantTypePtr i_plantTypePtr);

	void onViewBoardOrZombiesButtonPressed();
	void onStartGameButtonPressed();

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
		STATE_LSM_READYSETGO,
		STATE_LSM_ZOMBOSS_METER_FILL,
		STATE_LSM_PLAYING,
		PVZ_END_ENUM(STATE_LSM_),
	};

	void AddReadySetPlantToAnimMgr(AnimationMgr* i_animMgr, float& io_startTime, Delegate0 i_finishedDelegate, bool i_finishAfterSet = false) override;
    
public:
    bool isPlayingGame(){return m_lastStandState == STATE_LSM_PLAYING;}
    
    bool isViewingZombie() {return m_lastStandState == STATE_LSM_TO_VIEWING_ZOMBIES || m_lastStandState == STATE_LSM_VIEW_ZOMBIES || m_lastStandState == STATE_LSM_FROM_ZOMBIES_TO_PLANTING;}
    
private:
    void onSecondIntroComplete();
	virtual void bringUpSeedChooser() override;
	
	
	void onLoadComplete() override;
	void startIntro();
	void onUpdate();
	void onGameplayStarted();
	void onEndLevel();
	void onViewZombiesComplete();

	const ZombieZombossMechProps* getZombossProperties();
	void initZombossMeter();
	void onZombossIntroDone();
	void showZomboss();

	void setState(State i_state);

	void setToolsState(const bool i_introState);
    void onPlantPlanted(Plant* i_plant);
    void onPlantShoveled(Plant* i_plant);
    int  GetPlantCount() const;

    void zombossBattleEnablePlanting(bool i_enabled);

	State m_lastStandState;
	pvztime_t m_stateEntryTime;

	bool m_hasZomboss;
};

class LastStandMinigameProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(LastStandMinigameProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return LastStandMinigameModule::StaticGetClass();
	}

	LastStandMinigameProperties()
	{
		StartingSun = 0;
		StartingPlantfood = 0;
	}
	
	int StartingSun;
	int StartingPlantfood;
	std::vector<PlantTag> DisablePlantTags;
};

#endif /* defined(__PlantsVersusZombies2__LastStandMinigame__) */
