//
//  ZombieWithPushingAction.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 8/12/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieWithPushingAction__
#define __PlantsVersusZombies2__ZombieWithPushingAction__

#include <stdio.h>
#include "ZombieWithActions.h"
#include "BoardConstants.h"

constexpr int32_t kIceBlockSpawnColumn = BoardConstants::NUMBER_OF_COLUMNS_RAW + 1;

class ZombieWithPushingAction : public ZombieWithActions
{
public:
	RT_CLASS_DEFINE(ZombieWithPushingAction, ZombieWithActions, RtClass);
	
	void onPlaceOnBoard() override;
	
	bool tryToPlaceCorrectlyOnBoard();
	virtual void spawnGridItemThatZombiePushes(int32_t column);
	
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
protected:
	void setPushingProperties(int numItemsToSpawnWith);
	bool tryPush();
	
private:
	int m_numberOfIGriditemsToSpawnWith = 0;
};

class ZombiePushGridItemActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombiePushGridItemActionDefinition, ZombieActionDefinition, RtClass);
	ZombiePushGridItemActionDefinition();
	
	GridItemRestrictionSet	PushableGridItems;
	GridItemRestrictionSet	PushBlockingGridItems;
	PlantRestrictionSet		NotSquashedPlants;
	float					RelocationDuration;
	Rect					PushRectangle;
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	GridItem* FindReachableGridItem(Zombie* i_zombie) const;
	bool CanPushGridItem(Zombie* zombie, GridItem* i_griditem) const;
	
	GridItem* FindGriditemAt(const Sexy::Point& i_gridLocation) const;
	
private:
	bool				shouldPushGridItem(GridItem* item, ZombieWithActions* i_zombie) const;
	bool				isPushBlockedAt(const Sexy::Point& i_gridLocation) const;
	const GridItem*		findPushBlockerAt(const Sexy::Point& i_gridLocation) const;
	const Plant*		findPlantAt(const Sexy::Point& i_gridLocation) const;
	bool				isGriditemInFlight(const GridItem* i_griditem) const;
	const Sexy::Point	getGridPushDestination(GridItem* i_icecube) const;
};

class ZombiePushGriditemActionHandler : public ZombieActionHandler
{
private:
	struct PushInProgress
	{
		PushInProgress() {}
		PushInProgress(RtWeakPtr<GridItem> i_iceBlock);
		
		RtWeakPtr<GridItem> Griditem;
		SexyVector3 StartPosition;
		SexyVector3 EndPosition;
	};
	
public:
	RT_CLASS_DEFINE(ZombiePushGriditemActionHandler, ZombieActionHandler, RtClass);
	
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	
	void onAnimationDone(const std::string& i_animName);
	
private:
	void beginPushing(GridItem* i_griditem);
	bool hasGridItemToPush();
	void haltAction();
	
	bool m_hasPushed = false;
};

class ZombieWithPushingActionAnimRig : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieWithPushingActionAnimRig, ZombieAnimRig, RtClass);
	
	bool PlayWalk(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	
	virtual void DoPush(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual void CancelPush();
	
protected:
	void onPopAnimInitialized() override;
	
	void onAnimContinued(const std::string &i_oldAnimName, const std::string &i_newAnimName, int i_playCount);
	
private:
	PopAnimRig::LoopingAnimContinuedReflectionDelegate	m_pushingActionOnLoopingAnimContinued;
	PopAnimRig::AnimStoppedReflectionDelegate			m_pushingActionOnAnimStopped;
	bool												m_startPush = false;
};

#endif /* defined(__PlantsVersusZombies2__ZombieWithPushingAction__) */
