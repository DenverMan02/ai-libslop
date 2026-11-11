//
//  GridItemAnimation.h
//  PlantsVersusZombies2
//
//  GridItem with common AnimRig functionality and condition tracking (which does FX).
//
//  Created by Jason Emery on 8/26/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//


#ifndef __GRIDITEM_ANIMATION_H__
#define __GRIDITEM_ANIMATION_H__

#include "GridItem.h"
#include "PopAnimRig.h"

class GridItemAnimation : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemAnimation, GridItem, RtClass);

	GridItemAnimation();
	virtual ~GridItemAnimation();

	virtual void	SetDamageFlash(float i_duration);

	PopAnimRigPtr	GetAnimRig() { return m_animRig; }
    PopAnimRigPtr	GetLinkedAnimRig();
    AttachedEffect* GetLinkedEffect();
    bool			HasLinkedAnimRig();
	int				CalcRenderOrder() const override;
	void			SetMoveSmoothly(bool i_moveSmoothly) { m_moveSmoothly = i_moveSmoothly; }

	virtual Sexy::Rect calcCollisionRect() override;

	void SetScale(float i_scale);
	float GetScale();
	void SetHealthBarVisible(bool i_visible);
	bool GetHealthBarVisible();

protected:
	void		setDefaultAnimRig();
	void		setAnimRig(const std::string& i_popAnim, const std::string& i_animRigClass);
    
	void		onGridItemInitialize() override;
	void 		onGridItemPostInitialize() override;
	void		onUpdate() override;
	void		onDraw(Graphics* i_g) override;

	virtual Point	getGridExtents();
	virtual SexyVector2	getRenderOffset();
    virtual SexyVector2 getRenderScale();
    
    bool			m_hasLinkedAnimRig;
    bool 			m_moveSmoothly;
private:

	void		drawAnimation(Graphics* i_g);
	void		drawHealthBar(Graphics* i_g);

	PopAnimRigPtr m_animRig;
	float         m_scale;
	bool 		  m_showHealthBar;
};

namespace Message
{
	void NotifyGridItemPlaceOnBoard(GridItemAnimation* i_gridItem);
}

#endif
