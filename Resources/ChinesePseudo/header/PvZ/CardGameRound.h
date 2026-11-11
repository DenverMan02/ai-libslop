/*
 * CardGameRound.h
 *
 *  Created on: 2022-6-2
 *      Author: zhousen
 */

#ifndef CARDGAMEROUND_H_
#define CARDGAMEROUND_H_

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "GameObject.h"
#include "LevelModule.h"
#include "Loot.h"
#include "PVZDB.h"
#include "PVZTypes.h"
#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "SexyAppFramework/MTRand.h"
#include "TimeMgr.h"
#include "TodDebug.h"
#include "WaveGenerator.h"
#include "CardGameModule.h"

class CardGameRoundModule;
class CardGameRound;
class CardGameRoundProperties;
class CardGameRoundAction;
class CardGameRoundActionProperties;
class CardGameZombieGenerateRoundActionProperties;

typedef RtWeakPtr<CardGameRoundProperties> CardGameRoundPropertiesPtr;
typedef RtWeakPtr<CardGameRoundActionProperties> CardGameRoundActionPropertiesPtr;
typedef RtWeakPtr<CardGameZombieGenerateRoundActionProperties> CardGameZombieGenerateRoundActionPropertiesPtr;


// actions type serials
enum CardGameRoundActionType
{
	RoundActionInvalid = -1,
	RoundActionZombie,
	RoundActionMax,
};

// CardGameRoundProperties
class CardGameRoundProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE_ABSTRACT(CardGameRoundProperties, PropertySheetBase, RtClass);

	int RoundIndex;// round start from 0.(means real round 1)

	std::vector<CardGameRoundActionPropertiesPtr> RoundActioProps;
};

// CardGameRoundActionProperties
class CardGameRoundActionProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE_ABSTRACT(CardGameRoundActionProperties, PropertySheetBase, RtClass);

	CardGameRoundActionType Type;
};

// Spawn Card Zombie Action
class CardGameZombieGenerateRoundActionProperties : public CardGameRoundActionProperties
{
public:
	RT_CLASS_DEFINE_ABSTRACT(CardGameZombieGenerateRoundActionProperties, CardGameRoundActionProperties, RtClass);

	std::vector<CardGameZombieGenerateData> ZombieList;
};

// Spawn Card TowerDefend Action

// Card Game Round Module
class CardGameRoundModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CardGameRoundModule, LevelModule, RtClass);

	CardGameRoundModule();
	virtual ~CardGameRoundModule();

protected:
	virtual void postInitialize() override;
	virtual void registerForEvents() override;

protected:
	void onLevelInit();
	void onGameplayStarted();
	void onUpdate();

	std::vector<CardGameRound*> m_Rounds;
};

// Card Game Round Properties
class CardGameRoundModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CardGameRoundModuleProperties, LevelModuleProperties, RtClass);

	CardGameRoundModuleProperties();

	virtual RtClass* GetModuleClass() const override
	{
		return CardGameRoundModule::StaticGetClass();
	}

	std::vector<CardGameRoundPropertiesPtr> RoundProps;
};


// CardGameRoundAction
class CardGameRoundAction
{
public:
	CardGameRoundAction();
	virtual ~CardGameRoundAction();

	virtual void Init(int roundIndex, CardGameRoundActionPropertiesPtr props);

protected:
	virtual void registerForEvents();
	virtual void DoAction(int roundIndex);
	virtual void DoRealAction();

protected:
	int m_RoundIndex;
	CardGameRoundActionPropertiesPtr m_Props;
};

// zombie generate action
class CardGameZombieGenerateRoundAction : public CardGameRoundAction
{
public:
	CardGameZombieGenerateRoundAction();
	virtual ~CardGameZombieGenerateRoundAction();

	virtual void Init(int roundIndex, CardGameRoundActionPropertiesPtr props) override;

protected:
	virtual void DoRealAction() override;

	CardGameZombieGenerateRoundActionPropertiesPtr m_realProps;
};


// CardGameRound
class CardGameRound
{
public:
	CardGameRound();
	virtual ~CardGameRound();

	virtual void Init(CardGameRoundPropertiesPtr props);

protected:
	virtual void registerForEvents();

protected:
	int m_roundIndex;
	std::vector<CardGameRoundAction*> m_Actions;
	CardGameRoundPropertiesPtr m_Props;
};


// actions factory
class CardGameRoundActionFactory
{
public:
	static CardGameRoundAction* CreateCardGameRoundAction(CardGameRoundActionType type);
};

#endif /* CARDGAMEROUND_H_ */
