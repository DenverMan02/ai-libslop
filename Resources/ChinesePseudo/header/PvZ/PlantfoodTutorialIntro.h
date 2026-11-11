//
//  PlantfoodTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantfoodTutorialIntro_h
#define PlantsVersusZombies2_PlantfoodTutorialIntro_h

#include "IntroModule.h"
#include "StandardLevelIntro.h"
#include "AnimationMgr.h"
#include "Zombie.h"
#include "GameNotify.h"
#include "SeedPacket.h"
#include "TutorialFinger.h"

class PlantfoodTutorialIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(PlantfoodTutorialIntro, StandardLevelIntro, RtClass);

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
	virtual void 	unregisterForEvents() override;
	
private:
	class Board*	getBoard();
	void			enablePlantfood(bool i_isShown, bool i_isClickable);
    void        pauseEntities(bool bPause, bool i_enableSun = false);
	
	void			startIntro();
	void			onUpdate();
	void			onEndLevel();
    void        onGameplayStarted();

	void			addToRenderQueue(class RenderQueue* i_queue);
    
    void			drawHighlight(Graphics* i_g);
    void			drawLawnOverlays(Graphics* i_g);
	
    void			onToolAppliedPlantFood(class PlantGroup* i_plant);
    void			onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void			onPlantDied(Plant* i_plant);
    void			onPlantPlanted(Plant* i_plant);
	void			onPlantfoodSpawned(class CollectablePlantfood* i_plantfood);
    void        onCanApplyPlantfood(class PlantGroup* i_plant, bool* o_isCan);
	void			onCoinBanked(Collectable* i_collectable);
	void			onCursorAdded(class BaseCursor *i_cursor);
	void			onCursorDestroyed(class BaseCursor* i_cursor);
	void			onPlantfoodCountChanged(int i_newCount);
	void			onNarrationFinished();
    void            onSunHitGround(class Collectable* i_collectable);
    void			onSunClicked(class CollectableSun* i_sun, SunCurrency i_upcomingAmount);
    void            onSunProducedByPlant(class CollectableSun* i_sun);
    void            onOk();
    
	void			startGame();
	void			introduceDave();

	void			setupDaveProlog();
    void            setupDavePFEpilog();
	void			setupDaveEpilog();
	void			setupDaveFailed();
	
	void			makeZombieRiseFromGround(Zombie* i_zombie, int i_minColumn = 6);
    
    void			setupTutorialAdvice(int oldState);
    
    void			showUI(bool i_isShown);
    void            createTutorialDialog(const std::string& i_animName, const std::string& i_animToPlay, const SexyString& i_footerLabel);
    void        gatherPlantlessPlantingRestrictions(const Sexy::Point &i_gridPosition,
                                                    std::vector<PlantingReason> *io_plantingReasons);
    void        StartNarrativeID(const std::string &i_narrativeID);
    void		onPlantShoveled(Plant* i_plant);
	enum State
	{
		PVZ_BEGIN_ENUM(STATE_TUTORIAL_),
		STATE_TUTORIAL_START,
		STATE_TUTORIAL_DAVE_INTRO,
        STATE_TUTORIAL_SUNFLOWER_ANIM,
        STATE_TUTORIAL_TAP_SUNFLOWER,
        STATE_TUTORIAL_TAP_TO_PLANT_SUNFLOWER,
        STATE_TUTORIAL_WAITING_FOR_SUN,
        STATE_TUTORIAL_PLANT_THREE_SUNFLOWER,
        STATE_TUTORIAL_WAITING_FOR_ZOMBIE,
        STATE_TUTORIAL_ZOMBIE_IMG_HINT,
        STATE_TUTORIAL_PEASHOOTER_ANIM,
        STATE_TUTORIAL_TAP_PEASHOOTER,
        STATE_TUTORIAL_TAP_TO_PLANT_PEASHOOTER,
        STATE_TUTORIAL_WAITING_FOR_KILLING_ZOMBIE,
        STATE_TUTORIAL_WAITING_FOR_BUCKET_ZOMBIE,
        STATE_TUTORIAL_BUCKET_ZOMBIE_HINT_IMG,
        STATE_TUTORIAL_DAVE_PF_INTRO,
        STATE_TUTORIAL_PF_ANIM,
        STATE_TUTORIAL_TAP_PF,
        STATE_TUTORIAL_TAP_TO_USE_PF,
        STATE_TUTORIAL_WAITING_FOR_KILLING_BUCKET_ZOMBIE,
        STATE_TUTORIAL_WAITING_FOR_PF_ZOMBIE,
        STATE_TUTORIAL_PF_ZOMBIE_IMG_HINT,
        STATE_TUTORIAL_LAST_HINT,
		STATE_TUTORIAL_PLAYING,
        STATE_TUTORIAL_DEMO_BATTLE_START,
        STATE_TUTORIAL_WAITING_FIRST_SUN_PRODUCE,
        STATE_TUTORIAL_WAITING_FIRST_SUN_CLICKED,
        STATE_TUTORIAL_WAITING_FOR_COLLECTING_PLANTFOOD,
        STATE_TUTORIAL_WAITING_FOR_ALL_ZOMBIE_DIED,
        STATE_TUTORIAL_WAITING_FOR_SHOVELE_PLANT,
        STATE_TUTORIAL_DEMO_BATTLE_END,
		PVZ_END_ENUM(STATE_TUTORIAL_),
	};
	void			setState(State i_state);

	State                           m_state;
	pvztime_t						m_stateTimer;
	AnimationMgrWkPtr               m_animationMgr;

	bool							m_plantfoodUsed;
	
	std::vector<StandaloneEffectPtr>	m_bouncingArrows;
    TutorialFinger  m_finger;

    float                   m_tutorialFingerPosX;
    float                   m_tutorialFingerPosY;
    
    pvztime_t               m_tutorialFingerFlyTime;
    pvztime_t               m_tutorialFingerRestTime;
    
    bool                    m_isTutorialFingerActive;
    bool                    m_isTutorialFingerResting;
    
    int                     m_sunFlowerNum;
    
    ZombiePtr               m_zombiePtr;
    PlantPtr                m_plantPtr;
    SeedPacketPtr           m_peashooterPacketPtr;
    SeedPacketPtr           m_sunflowerPacketPtr;
    RtWeakPtr<class CollectableSun>   m_sunPtr;
    std::vector<RtWeakPtr<class CollectablePlantfood>>  m_plantfoodCached;
};


class PlantfoodTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(PlantfoodTutorialIntroProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return PlantfoodTutorialIntro::StaticGetClass();
	}
};

#endif
