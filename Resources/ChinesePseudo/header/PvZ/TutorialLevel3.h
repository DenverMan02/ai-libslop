//
//  TutorialLevel3.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TutorialLevel3_h
#define PlantsVersusZombies2_TutorialLevel3_h

#include "IntroModule.h"
#include "AnimationMgr.h"
#include "Zombie.h"
#include "GameNotify.h"
#include "StandardLevelIntro.h"
#include "AnimationControllerHelpers.h"
#include "Effect_BouncingArrow.h"

class TutorialLevel3 : public IntroModule
{
public:
	RT_CLASS_DEFINE(TutorialLevel3, IntroModule, RtClass);
	
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
private:
	
	enum State 
	{
		PVZ_BEGIN_ENUM(STATE_TUTORIAL3_),
		STATE_TUTORIAL3_START,
		STATE_TUTORIAL3_LAWN_PREVIEW,
		STATE_TUTORIAL3_1_WAIT,
		STATE_TUTORIAL3_2_TAP_ON_SHOVEL,
		STATE_TUTORIAL3_3_TAP_ON_PLANT,
		STATE_TUTORIAL3_4_TAP_ON_SHOVEL,
		STATE_TUTORIAL3_5_TAP_ON_PLANT,
		STATE_TUTORIAL3_6_TAP_ON_SHOVEL,
		STATE_TUTORIAL3_7_TAP_ON_PLANT,
		STATE_TUTORIAL3_8_START_PLAYING,
		STATE_TUTORIAL3_9_PLAYING_WITH_3_SUNFLOWERS,
		STATE_TUTORIAL3_10_NEED_MORE_SUNFLOWERS,
		STATE_TUTORIAL3_11_FINISHED,
		PVZ_END_ENUM(STATE_TUTORIAL3_),
	};
	
	void					startIntro();
	void					onUpdate();
	void					onEndLevel();
	void					addToRenderQueue(class RenderQueue* i_queue);

    void					onPlantDied(Plant* i_plant);
	void					onPlantShoveled(Plant* i_plant);
    void					onPlantPlanted(Plant* i_plant);
	void					onCursorAdded(class BaseCursor* i_cursor);
	void					onCursorDestroyed(class BaseCursor* i_cursor);
	void					onGameplayEnded();
	void					onGameWon();
	void					onLawnPreviewComplete();

	void					setupLawnPreview();
	void					setupSodRollout();
	void					setupTutorialAdvice();

	
	void					setState(State i_state);

	void					drawLawnOverlays(Graphics* i_g);
	class Board*			getBoard();
	void					showUI(bool i_isShown);
	void					startGame();

	void					showShovelArrow();
	void					showPlantArrows(bool i_show=true);

    
	
	State					m_state; 
	AnimationMgrWkPtr       m_animationMgr;
	pvztime_t				m_sodRollTimeStart;
	pvztime_t				m_sodRollTimeEnd;
	pvztime_t				m_stateTimerEnd;

    Effect_BouncingArrowPtr m_bouncingArrow;


    std::vector<Effect_BouncingArrowPtr>	m_bouncingArrowPlants;

	int						m_sunflowerCount;
	int						m_peashooterCount;
};

class TutorialLevel3Properties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(TutorialLevel3Properties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return TutorialLevel3::StaticGetClass();
	}
};

#endif
