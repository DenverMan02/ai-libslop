//
//  GridItemBoardEntityConditionTarget.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 12/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemBoardEntityConditionTarget__
#define __PlantsVersusZombies2__GridItemBoardEntityConditionTarget__

#include <string>

#include "DamageInfo.h"
#include "DamageLifetime.h"
#include "GridItemBreakableTarget.h"
#include "RtDb.h"
#include "RtObject.h"
#include "PlantEnums.h"
#include "TimeMgr.h"

class GridItemBoardEntityConditionTargetProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemBoardEntityConditionTargetProps, GridItemBreakableTargetProps, RtClass);
    
    GridItemBoardEntityConditionTargetProps()
    {
    }
	
};

class GridItemBoardEntityConditionTarget : public GridItemBreakableTarget
{
public:
    RT_CLASS_DEFINE(GridItemBoardEntityConditionTarget, GridItemBreakableTarget, RtClass);
    GridItemBoardEntityConditionTarget();
    
    void SetOwner(BoardEntityPtr i_newOwner);
    BoardEntityPtr GetOwner() { return m_owner; }
    bool IsOwnedBy(BoardEntityPtr i_owner) { return m_owner == i_owner; }
    
    virtual bool OverrideProjectileCollision(Projectile* i_projectile);
    
    int CalcRenderOrder() const override;
	
	virtual void MoveOverTimeTo(const Sexy::Point& i_gridLocation, pvztime_t i_duration);
	
	bool IsControlled() const override;
	void SetIsControlled(bool i_isControlled) override;
    
protected:
    virtual void onUpdate() override;
    
    virtual void tryUpdatePosition();
    virtual void updatePosition();
	virtual SexyVector2 getNextBoardPosition();
	virtual bool isDoneMoving() const;
    
protected:
    BoardEntityPtr	m_owner;
	
	// BRAD Note:
	// Part of the move over time to logic. Honestly, this would probably best live in a component somewhere.
	// In fact, having a component we can attach to drive this kind of motion would be great.
	pvztime_t		m_startTime;
	pvztime_t		m_endTime;
    SexyVector2		m_startBoardLocation;
	SexyVector2		m_targetBoardLocation;
	// \BRAD Note
};

#endif /* defined(__PlantsVersusZombies2__GridItemBoardEntityConditionTarget__) */
