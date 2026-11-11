//
//  GridItemMechanismPlank.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2/19/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __GridItemMechanismPlank_H__
#define __GridItemMechanismPlank_H__

#include "Precompile.h"
#include "GridItem.h"

enum MechanismPlankMoveDirection
{
	MoveInvalid,
	MovePlankUp,
	MovePlankDown,
};

class GridItemMechanismPlank : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemMechanismPlank, GridItem, RtClass);

	GridItemMechanismPlank(){}
	virtual ~GridItemMechanismPlank(){}

	virtual void onGridItemInitialize() override;

	int CalcRenderOrder() const override;

	void setMovement(int i_targetRow, MechanismPlankMoveDirection i_moveDirection);
	bool isRelocating() const;

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
	virtual void onDraw(class Graphics* i_g) override;
	virtual void onUpdate() override;

private:
	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCancelEvent();

	void tryMoveUp();
	void tryMoveDown();
	void updateAttachedPlant();
	bool canMoveTo(int i_gridX, int i_gridY) const;
    bool canMoveable();
    
private:
	Sexy::TouchID 					m_owningTouchIdent = Sexy::InvalidTouchID;
	MechanismPlankMoveDirection 	m_moveDirection = MoveInvalid;
	int 							m_targetRow = -1;
	int 							m_originRow = -1;
	int								m_touchBeginY = 0;
	float 							m_velocity = 0.0f;
	RtWeakPtr<class Plant>			m_attachedPlant;
	RtWeakPtr<class GridItem>		m_attachedItem;
};

inline bool GridItemMechanismPlank::isRelocating() const
{
	return m_moveDirection != MoveInvalid;
}

namespace Message
{
    void MechanismPlankMoved(GridItemMechanismPlank* i_plank);
}


#endif
