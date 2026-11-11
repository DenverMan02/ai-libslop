/*
 * CardGameModule.h
 *
 *  Created on: 2022-5-30
 *      Author: zhousen
 */

#ifndef CARDGAMEMODULE_H_
#define CARDGAMEMODULE_H_

#include "LevelModule.h"
#include "TimeMgr.h"
#include "PVZTypes.h"
#include "StateMachine.h"

// Card Game Messages
namespace Message
{
    void CardGameIntroStart();
    void CardGameIntroEnd();

    void CardGamePickCardStart(int round);
    void CardGamePickCardEnd();

    void CardGamePlayerActionStart();
    void CardGamePlayerActoinEnd();

    void CardGamePlayerDiscardStart();
    void CardGamePlayerDiscardEnd();

    void CardGameEnemyActionStart();
    void CardGameEnemyActionEnd();

    void CardGameRoundFinishStart();
    void CardGameRoundFinishEnd();

    void CardGameResultStart();
    void CardGameResultEnd();
};

// Card Game State
STATE_ENUM_BASE_BEGIN(CardGameState)
    CardGameState_Init,
	CardGameState_Intro,
	CardGameState_Pick,
	CardGameState_PlayerAction,
    CardGameState_PlayerDiscard,
    CardGameState_EnemyAction,
    CardGameState_RoundFinish,
    CardGameState_Result,
    CardGameState_End,
STATE_ENUM_END(CardGameState);

// Card Game Module
class CardGameModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CardGameModule, LevelModule, RtClass);

    CardGameModule();
    virtual ~CardGameModule();

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	void initializeModule() override;
    void registerForEvents() override;
	void unregisterForEvents() override;
	void postInitialize() override;

    bool isInState(CardGameState i_state) const;
    int  GetStateSerialization() const;
	void onUpdate();
	void onLoadComplete();
	void GamePlayStarted();
	void GamePlayEnded();
    void addToRenderQueue(RenderQueue* i_queue);

    void SetState(CardGameState state);
    void SetStateMachineState(CardGameState state);

    void GenerateHomeProgress();
    void GeneratePresetCards();
    void GenerateTutorialCardGrids();

    // enemy
    void GenerateEnemyOnBoard();
    void GenerateTower(class GridItemCardGameZombie* parent, std::vector<class GridItemCardGameTowerGenerateData> TowerList, int level);

    // show advice
    void AddAdvice(SexyString strName, pvztime_t duration = 1.0f);
    void AddMessage(std::string name, Color color, pvztime_t duration = 1.0f);

    // animation
    void StartTimeEvent(pvztime_t timeAfterNow, std::string funcName);
    pvztime_t GetPlayerActionCountDownTime() const;
    void ClearTimeEvent();

    // call back func
	void EndPlayerActionRound();
    void EndDiscardCards();

    // Intro
    void CardEffectPreTrigger();
    void ItemEffectPreTrigger();
    void GenerateCardPool();
    void RandomCardIntoPool();
    bool IsIntroEnd();

    // Pick
    void FillPlayerPoint();
    int PickCards(int num);
    void FillPool();

    // Player Action
    void PlayerAction();
    bool IsPlayerActionOver();

    // Player Discard
    void DiscardCards();

    // Enemy Action
    void EnemyAction();
    bool IsEnemyActionOver();
    
    void OnNotifyDrawCardsActionDone();
    void OnNotifyPlayCardsActionDone();
    void OnNotifyCardTutorial(bool i_trigger);

protected:
    DECLARE_STATE_FUNCTIONS(CardGameState, INIT);
    DECLARE_STATE_FUNCTIONS(CardGameState, INTRO);
    DECLARE_STATE_FUNCTIONS(CardGameState, PICK);
    DECLARE_STATE_FUNCTIONS(CardGameState, PLAYERACTION);
    DECLARE_STATE_FUNCTIONS(CardGameState, PLAYERDISCARD);
    DECLARE_STATE_FUNCTIONS(CardGameState, ENEMYACTION);
    DECLARE_STATE_FUNCTIONS(CardGameState, ROUNDFINISH);
    DECLARE_STATE_FUNCTIONS(CardGameState, RESULT);
    DECLARE_STATE_FUNCTIONS(CardGameState, END);

protected:
    StateMachine<CardGameState>  m_cardGameState;
    AnimationMgrWkPtr       m_animationMgr;
    int m_round;// the current round index.
    int m_playerCardsNumber;// current cards number player has.
    int m_playerCardsPoints;// current cards point player has.
    pvztime_t m_playerActionRoundTimeLimitMax;// the time limit in player action
    pvztime_t m_playerActionRoundTimeStart;// the time when player start to play
    class CardGameRoundModule*	m_roundModule;// card game round module
};


// GridItemCardGameTowerGenerateData
struct GridItemCardGameTowerGenerateData
{
	GridItemCardGameTowerGenerateData() {
		Name = "";
		GridX = 0;
		GridY = 0;
	}

	std::string Name;
	int GridX;
	int GridY;
};

// card game zombie generate data
struct CardGameZombieGenerateData
{
	CardGameZombieGenerateData() {
		Name = "";
		Level = 2;
		GridX = 0;
		GridY = 0;
	}

	std::string Name;
	int Level;
	int GridX;
	int GridY;
	std::vector<GridItemCardGameTowerGenerateData> TowerList;// defend tower generate data
};

struct PresetCard
{
	PresetCard()
	: Id(0)
	, Count(0)
	{

	}

	int Id;
	int Count;
};

struct TutorialCard
{
	TutorialCard()
	: Id(-1)
	, GridX(-1)
	, GridY(-1)
	{

	}

	int Id;
	int GridX;
	int GridY;
};

class CardGameModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CardGameModuleProperties, LevelModuleProperties, RtClass);
	
    virtual RtClass* GetModuleClass() const override
	{
		return CardGameModule::StaticGetClass();
	}

    CardGameModuleProperties();

    int PlayerCardsNumberMax;
    int PlayerCardsPointsMax;
    pvztime_t PlayerActionRoundTimeLimitMax;
	std::vector<CardGameZombieGenerateData> DefaultZombieList;
	std::vector<PresetCard> PresetCards;
	std::vector<TutorialCard> TutorialCards;
};

#endif /* CARDGAMEMODULE_H_ */
