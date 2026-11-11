//
//  CowboyMinigame.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CowboyMinigame_h
#define PlantsVersusZombies2_CowboyMinigame_h

#include "LevelModule.h"
#include "Core.h"
#include "GameEventMgr.h"
#include "AnimationMgr.h"
#include "Effect_ZombieGate.h"
#include "SeedPacket.h"
#include "DamageInfo.h"

class CowboyMinigameModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CowboyMinigameModule, LevelModule, RtClass);
	
protected:
	
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;

private:
	
	enum State
	{
		PVZ_BEGIN_ENUM(STATE_TRAIN_),
		STATE_TRAIN_LOADING,
		STATE_TRAIN_START,
		STATE_TRAIN_DAVE_INTRO,
		STATE_TRAIN_SHOWING_ZOMBIES,
		STATE_TRAIN_WAIT_FOR_FIRST_PLANT,
		STATE_TRAIN_WAIT_FOR_PROJECTILES_TO_DIE,
		STATE_TRAIN_WAIT_FOR_PLANT,
        STATE_TRAIN_TO_VIEWING_ZOMBIES,
        STATE_TRAIN_VIEW_ZOMBIES,
        STATE_TRAIN_FROM_ZOMBIES_TO_PLANTING,
        STATE_TRAIN_FINISHED_VIEWING_ZOMBIES,
		STATE_TRAIN_PLAYING,
		STATE_TRAIN_FAILED,
		STATE_TRAIN_WON,
		PVZ_END_ENUM(STATE_TRAIN_),
	};
	
	enum MinigameMode
	{
		MGMODE_CONTINUOUS,
		MGMODE_FRESH_START
	};

    enum ZombiePanType
	{
		ZPT_AUTO,
        ZPT_RIGHT,
        ZPT_LEFT
	};
    
	void					startIntro();
	void 					onLoadComplete();
	void 					onEndLevel();
	void 					onUpdate();
    void                    onViewZombiesComplete();
    void                    onViewBoardOrZombiesButtonPressed();
	
	void 					addToRenderQueue(class RenderQueue* i_queue);
	void					showTools(bool i_isShown);
    void					setState(State i_state);
    bool					checkWinCondition();
	
	void 					onNarrationFinished();
	void					onZombieDestroyedNew(class Zombie* i_zombie);
    void					onZombieDestroyed(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void					onPlantDied(class Plant* i_plant);
//PVZ2_CHINESE_START
    void                    onSeedPacketPlanted(SeedPacket* i_packet);
//PVZ2_CHINESE_END
    
    void					setupDaveProlog();
    void					introduceDave();
	
	void					animateZombiePreview(ZombiePanType i_panType = ZPT_AUTO);
	void					setZombiesIdle(bool i_idle);
	void					moveZombies(float i_xOffset);

	void					setPlayingUIState(bool i_enabled);
    
	MinigameMode			m_gameMode;
	State					m_state;
	
	AnimationMgrWkPtr		m_animationMgr;

	std::vector<RtWeakPtr<Effect_ZombieGate> > m_zombieGates;
	pvztime_t				m_delayStart;
};

class CowboyMinigameProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CowboyMinigameProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{	
		return CowboyMinigameModule::StaticGetClass(); 
	}
	
	CowboyMinigameProperties()
	{
		ShowTutorial = false;
		BeginString = "";
	}
	
	bool ShowTutorial;
	std::string BeginString;
};

#endif
