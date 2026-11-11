//
//  TutorialLevel4.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TutorialLevel4_h
#define PlantsVersusZombies2_TutorialLevel4_h

#include "IntroModule.h"
#include "AnimationMgr.h"
#include "GameNotify.h"
#include "StandardLevelIntro.h"
#include "Loot.h"
#include "StandaloneEffect.h"

class TutorialLevel4 : public IntroModule
{
public:
	RT_CLASS_DEFINE(TutorialLevel4, IntroModule, RtClass);
	
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
private:
	
	enum State 
	{
		PVZ_BEGIN_ENUM(STATE_TUTORIAL4_),
		STATE_TUTORIAL4_START,
		STATE_TUTORIAL4_LAWN_PREVIEW,
		STATE_TUTORIAL4_PLAYING,
		STATE_TUTORIAL4_FINISHED,
		PVZ_END_ENUM(STATE_TUTORIAL4_),
	};
	
	void					onLoaded();
	void					startIntro();
	void					onUpdate();
	void					onEndLevel();
	void					onGameWon();
	void					addToRenderQueue(class RenderQueue* i_queue);

	void					onLawnPreviewComplete();
	
	void					setupLawnPreview();
	void					setupSodRollout();
	
	void					setState(State i_state);

	void					drawLawnOverlays(Graphics* i_g);
	class Board*			getBoard();
	void					showUI(bool i_isShown);
	void					startGame();

	
	
	State					m_state; 
	AnimationMgrWkPtr		m_animationMgr;
	pvztime_t				m_sodRollTimeStart;
	pvztime_t				m_sodRollTimeEnd;
	pvztime_t				m_stateTimerEnd;
	
	StandaloneEffectPtr		m_sodRollerTop;
	bool m_skippedTutorial;
};

class TutorialLevel4Properties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(TutorialLevel4Properties, StandardLevelIntroProperties, RtClass);
	
	TutorialLevel4Properties()
	{
	}
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return TutorialLevel4::StaticGetClass();
	}
};


#endif
