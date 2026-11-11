//
//  ComponentPropagatedBurst.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/28/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentPropagatedBurst__
#define __PlantsVersusZombies2__ComponentPropagatedBurst__

#include "ComponentBase.h"
#include "PropertySheetBase.h"
#include "StandaloneEffect.h"
#include "TimeMgr.h"
#include "DamageInfo.h"
#include <deque>
#include "EntityFinder.h"

class Plant;
class BoardEntity;

//
// NOTE
// This code came from Jalapeno & Lava Guava.  It should be compatible and we
// should unify it back in at some point.
//

enum PropagationShape
{
	PVZ_BEGIN_ENUM(PROPAGATE_SHAPE_),
	PROPAGATE_SHAPE_Row,
	PVZ_END_ENUM(PROPAGATE_SHAPE_),
};

enum PropagationAction
{
	PVZ_BEGIN_ENUM(PROPAGATE_ACTION_),
	PROPAGATE_ACTION_Damage,
	PROPAGATE_ACTION_Charm,
	PVZ_END_ENUM(PROPAGATE_ACTION_),
};

class ComponentPropagatedBurstProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ComponentPropagatedBurstProps, PropertySheetBase, RtClass);
	
	ComponentPropagatedBurstProps()
	: Shape(PROPAGATE_SHAPE_Row)
    , PropagationDelay(0.75f)
	, Action(PROPAGATE_ACTION_Damage)
	, ContinualAction(false)
	, EffectLoop(false)
	, EffectLoopCount(0)
	{}
	
	ComponentPropagatedBurstProps& operator=(const ComponentPropagatedBurstProps& i_props)
	{
		Shape = i_props.Shape;
		PropagationDelay = i_props.PropagationDelay;
		PopAnimEffectName = i_props.PopAnimEffectName;
		Action = i_props.Action;
		ContinualAction = i_props.ContinualAction;
		EffectLoop = i_props.EffectLoop;
		EffectLoopCount = i_props.EffectLoopCount;
		
		return *this;
	}

	PropagationShape	Shape;
	float				PropagationDelay;
	PropagationAction	Action;
    std::string			PopAnimEffectName;
	bool				ContinualAction;
	bool				EffectLoop;
	int					EffectLoopCount;
};

class ComponentPropagatedBurst : public ComponentBase
{
public:
	RT_CLASS_DEFINE(ComponentPropagatedBurst, ComponentBase, RtClass);

	ComponentPropagatedBurst()
	: m_startTime{PVZ_T()}
	, m_lastExplosionPropagationDistance(0)
	{}
	
	void	SetProps(const ComponentPropagatedBurstProps& i_props);

	virtual void onBegin() override;
	virtual void onUpdate() override;
	
protected:

	ComponentPropagatedBurstProps m_props;

private:
	
	void		updateDamage(bool i_onlyOnExpansion);
	void		explode();
	bool		doDamage(BoardEntity* i_entity, DamageInfo& i_damage);
	void		setEndTime(pvztime_t i_endTime);
	void		queueEffect(pvztime_t i_effectDelay, int i_renderOrder, SexyVector3 i_effectLocation);

	pvztime_t	m_startTime;
	pvztime_t	m_endTime;
	int			m_lastExplosionPropagationDistance;
	std::vector<BoardEntityPtr> m_damagedEntities;
};

#endif
