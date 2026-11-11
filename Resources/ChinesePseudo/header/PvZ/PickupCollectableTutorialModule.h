//
//  PickupCollectableTutorialModule.h
//  PlantsVersusZombies2
//
//  Created by jsola on 1/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PickupCollectableTutorialModule_h
#define PlantsVersusZombies2_PickupCollectableTutorialModule_h

#include "LevelModule.h"
#include "TimeMgr.h"
#include "StandaloneEffect.h"
#include "Loot.h"
#include "GameEventMgr.h"
#include "Zombie.h"

class PickupCollectableTutorialModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PickupCollectableTutorialModule, LevelModule, RtClass);

	virtual void initializeModule() override;
	virtual void registerForEvents() override;

private:
	void onZombieSpawned(class Zombie* i_zombie);
	void onZombieDropLoot(class Zombie* i_zombie);
	
	void startFirstCoinTutorial(class Zombie* i_zombie);
	void onCoinClicked(Collectable* i_collectable);
	void onCoinBanked(Collectable* i_collectable);
	
	void onUpdate();
	void onEndLevel();
	
	void continueLevel();
	
	bool					m_coinDropperSpawned;
	ZombiePtr				m_coinDropper;
	bool					m_coinDropped;
	bool					m_coinCollected;
	RtWeakPtr<class Collectable>	m_coin;
	
	pvztime_t				m_displayAdviceAfter;
	pvztime_t				m_continueLevelAfter;
	StandaloneEffectPtr		m_bouncingArrow;
};

class PickupCollectableTutorialProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PickupCollectableTutorialProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PickupCollectableTutorialModule::StaticGetClass();
	}
	
	PickupCollectableTutorialProperties()
	{
		LootType = LOOT_Invalid;
	}
	
	std::string		PickupAdvice;
	std::string		PostPickupAdvice;

	std::string	 	DropperZombieType;
	Loot			LootType;
};

#endif
