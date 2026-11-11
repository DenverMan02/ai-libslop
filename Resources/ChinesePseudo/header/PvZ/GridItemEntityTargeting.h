//
//  GridItemEntityTargeting.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 8/15/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef GridItemEntityTargeting_h
#define GridItemEntityTargeting_h

#include "BoardEntity.h"
#include "DamageInfoProps.h"
#include "GridItemConditionTracker.h"
#include "GridItemBreakableTarget.h"
#include "PlantEnums.h"
#include "RtDb.h"
#include "RtObject.h"
#include "ZombieEnums.h"

enum GridItemEffectType
{
	EFFECT_TYPE_DAMAGE,
	EFFECT_TYPE_HEALING
};

//TODO: If design wants different targeting systems, add them here
enum GridItemTargetingArea
{
	TARGET_CIRCLE,
	TARGET_RECT,
	TARGET_LANE,
	TARGET_BOARD
};

struct GridItemConditionEntry
{
	GridItemConditionEntry()
	{
		Condition = GCONDITION_Invalid;
	}
	
	GridItemConditions Condition;
	ValueRange Duration;
};

class GridItemConditionProps
{
public:
	GridItemConditionProps(const std::vector<GridItemConditionEntry>& gridItemConditions)
	:m_gridItemConditions(gridItemConditions)
	{}
	
	void ApplyGridItemConditionsTo(DamageInfo& damageInfo);
	
private:
	const std::vector<GridItemConditionEntry>& m_gridItemConditions;
};

class GridItemAction : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(GridItemAction, PropertySheetBase, RtClass);
	
	GridItemAction()
	: TargetArea(TARGET_CIRCLE)
	, Damage(0.f)
	, SecondsBetweenEffects(1.f)
	, RangeInGridSquares(1.f)
	, HitAnimLoopTime(0.f)
	{}
	
	virtual ~GridItemAction() {}
	
	GridItemEffectType					Type;
	std::string							ActionAnimationName;
	std::string							HitPopAnim;
	std::string							HitAnimStartName;
	std::string							HitAnimLoopName;
	pvztime_t							HitAnimLoopTime;
	std::string							HitAnimEndName;
	Point								HitAffectOffset;
	std::vector<TeamFlags>  			TeamsToAffect;
	std::vector<BoardEntityTypeFlag> 	EntitiesToAffect;
	GridItemTargetingArea				TargetArea;
	float								Damage;
	float								SecondsBetweenEffects;
	float								RangeInGridSquares;
	std::vector<ZombieConditionEntry> 	ZConditions;
	std::vector<PlantConditionEntry> 	PConditions;
	std::vector<GridItemConditionEntry> GConditions;
	
	virtual void Execute(std::vector<BoardEntity*> i_targets, DamageInfo i_info) const;
	DamageInfo BuildDamageInfo(BoardEntity* i_instigator) const;
	TeamFlags GetAffectedTeams() const;
	BoardEntityTypeFlag GetAffectedTypes() const;
	
protected:
	

};

class GridItemEntityTargetingProps : public GridItemBreakableTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemEntityTargetingProps, GridItemBreakableTargetProps, RtClass);
	
	GridItemEntityTargetingProps()
	{
		
	}
	
	std::vector<TeamFlags> Teams;
	std::vector<GridItemAction> Actions;
};

class GridItemEntityTargeting : public GridItemBreakableTarget
{
	RT_CLASS_DEFINE(GridItemEntityTargeting, GridItemBreakableTarget, RtClass);
	GridItemEntityTargeting();
	
public:
	void SetActive(bool i_active);
	
protected:
	void registerForEvents() override;
	void onUpdate() override;
	void onGridItemInitialize() override;
	virtual void onLevelStart();
	virtual void onBasicLevelStart();
	virtual void onLastStandLevelStarting();

	virtual bool findTargets(std::vector<BoardEntity*>& o_targets, TeamFlags i_teamsToTarget, BoardEntityTypeFlag i_entitiesToTarget, GridItemTargetingArea i_area, float i_range);
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);
	virtual void playActionAnimation(std::string i_animName);
	virtual void onAnimationComplete(const std::string& i_animName);

private:
	bool m_actionInProgress;
	std::vector<pvztime_t> m_actionTimers;
	int m_lastUsedAction;
};

#endif /* GridItemEntityTargeting_h */
