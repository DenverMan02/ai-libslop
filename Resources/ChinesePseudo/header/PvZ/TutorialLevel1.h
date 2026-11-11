//
//  TutorialLevel1.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TutorialLevel1_h
#define PlantsVersusZombies2_TutorialLevel1_h

#include "IntroModule.h"
#include "AnimationMgr.h"
#include "Zombie.h"
#include "GameNotify.h"
#include "StandardLevelIntro.h"
#include "StandaloneEffect.h"
#include "AnimationControllerHelpers.h"

class TutorialLevel1 : public IntroModule
{
public:
	RT_CLASS_DEFINE(TutorialLevel1, IntroModule, RtClass);
	
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
private:
	
	enum State 
	{
		PVZ_BEGIN_ENUM(STATE_TUTORIAL1_),
		STATE_TUTORIAL1_WAIT_FOR_SKIP,
		STATE_TUTORIAL1_LAWN_PREVIEW,
		STATE_TUTORIAL1_1_TAP_PACKET,
		STATE_TUTORIAL1_2_TAP_TO_PLANT,
		STATE_TUTORIAL1_3_WAITING_FOR_SUN, 
		STATE_TUTORIAL1_4_TAP_TO_COLLECT_SUN,
		STATE_TUTORIAL1_5_COLLECTING_SUN,
		STATE_TUTORIAL1_6_WAITING_FOR_PACKET,
		STATE_TUTORIAL1_7_TAP_SECOND_PLANT,
		STATE_TUTORIAL1_8_PLANTING_SECOND_PLANT,
		STATE_TUTORIAL1_9_DEFEND_AGAINST_ZOMBIES,
		STATE_TUTORIAL1_PLAYING,
		PVZ_END_ENUM(STATE_TUTORIAL1_),
	};
	
	void					startIntro();
	void					onUpdate();
	void					onEndLevel();
	void					addToRenderQueue(class RenderQueue* i_queue);

	void					onSunClicked(class CollectableSun* i_sun, SunCurrency i_upcomingAmount);
	void					onSunExpired(class Collectable* i_collectable);
    void					onPlantPlanted(class Plant* i_plant);
	void					onCursorAdded(class BaseCursor* i_cursor);
	void					onCursorDestroyed(class BaseCursor* i_cursor);
	void					onGameWon();
	void					onNarrationFinished();
	void					onFadeToWhiteEnd();
	void					onFadeToNormalEnd();
	void					onLawnPreviewComplete();

	void					setupLawnPreview();
	void					setupSodRollout();
	void					setupTutorialAdvice();
	
	void					setState(State i_state);

	void					drawLawnOverlays(Graphics* i_g);
	class Board*			getBoard();
	void					showUI(bool i_isShown);
	void					startGame();

	void					onSkip();
	void					onDontSkip();
	
	
	State					m_state;
	pvztime_t				m_stateEnterTime;

	pvztime_t				m_sodRollTimeStart;
	pvztime_t				m_sodRollTimeEnd;
	pvztime_t				m_stateTimerEnd;
    
    AnimationMgrWkPtr		m_animationMgr;
	BouncingArrowWkPtr      m_bouncingArrow;

	StandaloneEffectPtr		m_sodRoller;
};

class TutorialLevel1Properties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(TutorialLevel1Properties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return TutorialLevel1::StaticGetClass();
	}
};

#endif
