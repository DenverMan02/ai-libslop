//
//  TutorialLevel2.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TutorialLevel2_h
#define PlantsVersusZombies2_TutorialLevel2_h

#include "IntroModule.h"
#include "AnimationMgr.h"
#include "Zombie.h"
#include "GameNotify.h"
#include "StandardLevelIntro.h"
#include "StandaloneEffect.h"
#include "AnimationControllerHelpers.h"

class TutorialLevel2 : public IntroModule
{
public:
	RT_CLASS_DEFINE(TutorialLevel2, IntroModule, RtClass);
	
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
private:
	
	enum State 
	{
		PVZ_BEGIN_ENUM(STATE_TUTORIAL2_),
		STATE_TUTORIAL2_START,
		STATE_TUTORIAL2_LAWN_PREVIEW,
		STATE_TUTORIAL2_1_WAITING_FOR_PACKET, 
		STATE_TUTORIAL2_2_TAP_PACKET,
		STATE_TUTORIAL2_3_TAP_TO_PLANT,
		STATE_TUTORIAL2_4_WAITING_FOR_PACKET, 
		STATE_TUTORIAL2_5_TAP_PACKET,
		STATE_TUTORIAL2_6_TAP_TO_PLANT,
		STATE_TUTORIAL2_7_WAITING_FOR_PACKET,
		STATE_TUTORIAL2_8_TAP_PACKET,
		STATE_TUTORIAL2_9_TAP_TO_PLANT,
		STATE_TUTORIAL2_10_FINISHED,
		PVZ_END_ENUM(STATE_TUTORIAL2_),
	};
	
	void					startIntro();
	void					onUpdate();
	void					onEndLevel();
	void					addToRenderQueue(class RenderQueue* i_queue);

    void					onPlantPlanted(Plant* i_plant);
	void					onCursorAdded(class BaseCursor* i_cursor);
	void					onGameplayEnded();
	void					onLawnPreviewComplete();
	void					onGameWon();

	void					setupLawnPreview();
	void					setupSodRollout();
	void					setupTutorialAdvice();
	
	void					setState(State i_state);

	void					drawLawnOverlays(Graphics* i_g);
	class Board*			getBoard();
	void					showUI(bool i_isShown);
	void					startGame();

	
	State					m_state;

	pvztime_t				m_sodRollTimeStart;
	pvztime_t				m_sodRollTimeEnd;
	pvztime_t				m_stateTimerEnd;
    
    AnimationMgrWkPtr		m_animationMgr;
	BouncingArrowWkPtr      m_bouncingArrow;

	StandaloneEffectPtr		m_sodRollerTop;
	StandaloneEffectPtr		m_sodRollerBottom;
	
};

class TutorialLevel2Properties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(TutorialLevel2Properties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return TutorialLevel2::StaticGetClass();
	}
};

#endif
