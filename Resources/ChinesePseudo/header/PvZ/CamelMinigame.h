//
//  CamelMinigame.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CamelMinigame_h
#define PlantsVersusZombies2_CamelMinigame_h

#include "StandardLevelIntro.h"
#include "Core.h"
#include "GameEventMgr.h"
#include "AnimationMgr.h"
#include "Zombie.h"

enum CardType
{
	PVZ_BEGIN_ENUM(CARDTYPE_),
	CARDTYPE_RED,
	CARDTYPE_BLUE,
	CARDTYPE_GREEN,
	CARDTYPE_YELLOW,
	CARDTYPE_BLACK,
	PVZ_END_ENUM(CARDTYPE_),
};

class CamelMinigameModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(CamelMinigameModule, StandardLevelIntro, RtClass);
	
	void					OnCamelTouch(ZombiePtr i_zombie);
	
protected:
	
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	virtual bool			suppressReadySetGo() const override { return true; }
	virtual void			onStandardIntroComplete() override;

private:
	
	enum State
	{
		PVZ_BEGIN_ENUM(STATE_CAMEL_),
		STATE_CAMEL_LOADING,
		STATE_CAMEL_START,
		STATE_CAMEL_DAVE_INTRO,
		STATE_CAMEL_WAIT_FOR_FIRST_TAP,
		STATE_CAMEL_WAIT_FOR_SECOND_TAP,
		STATE_CAMEL_MESSAGES_START,
		STATE_CAMEL_READY,
		STATE_CAMEL_SET,
		STATE_CAMEL_MATCH,
		STATE_CAMEL_PLAYING,
		PVZ_END_ENUM(STATE_CAMEL_),
	};
	
	enum CardState
	{
		PVZ_BEGIN_ENUM(STATE_CARD_),
		STATE_CARD_NONE,
		STATE_CARD_ONE,
		STATE_CARD_MATCHING,
		STATE_CARD_MATCH,
		STATE_CARD_NO_MATCH,
		PVZ_END_ENUM(STATE_CARD_),
	};

	void					showTools(bool i_isShown);

	void					doMinigameIntro();
	void					onEndLevel();
	void					onUpdate();

	void					addToRenderQueue(class RenderQueue* i_queue);
    void					setState(State i_state);
	
	void					onNarrationFinished();
	void					onZombieSpawned(Zombie* i_zombie);
	
    void					introduceDave();
    void					setupDaveProlog();
	
	void					slowDownLeftMostZombies();
	void					setCardState(CardState i_cardState);
	void					updateCardState();
	void					checkCurrentPairForMatchAndChangeState();

	CardType				getUnmatchedLeftCardType();
	void					spawnFirstZombie();
	
	float					getProgress();
	
	SexyVector3				pickSpotForNewCamelChain(class ZombieCamelTouch* i_newCamel);
	
    
	AnimationMgrWkPtr       m_animationMgr;
    Point                   m_bouncingArrowPos;
    
	State					m_state;
	CardState				m_cardState;
	pvztime_t				m_cardStateBeginTime;
	ZombiePtr				m_activeCard;
	ZombiePtr				m_secondCard;
	std::vector<int>		m_colorsUsed;
	int						m_lastWaveCounter;
	int						m_totalCamelsTouched;
	
};

class CamelMinigameProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(CamelMinigameProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{	
		return CamelMinigameModule::StaticGetClass(); 
	}

	CamelMinigameProperties()
	{
		ShowTutorial = false;
		
		CardTypesUsed = 4;
		
		CardMatchingTime = 0.5f;
		CardMatchTime = 0.0f;
		CardNoMatchTime = 1.5f;
		
		MinSpawnXStart = 500.f;
		MinSpawnXEnd = 200.f;
		MaxSpawnX = 600.f;
		
		InitialTutorialZombieRiseDelay = 2.f;
		CamelSegmentRiseStagger = 0.33f;

		AdditionalXBufferBetweenChains = 50.f;
	}
	
	bool ShowTutorial;
	
	int	CardTypesUsed;
	
	float CardMatchingTime;
	float CardMatchTime;
	float CardNoMatchTime;
	
	float InitialTutorialZombieRiseDelay;
	float CamelSegmentRiseStagger;
	
	float MinSpawnXStart;
	float MinSpawnXEnd;
	
	float MaxSpawnX;
	
	float AdditionalXBufferBetweenChains;
};

#endif
