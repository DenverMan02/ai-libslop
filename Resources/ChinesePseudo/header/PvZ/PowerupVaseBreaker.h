//
//  PowerupVaseBreaker.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/1/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupVaseBreaker__
#define __PlantsVersusZombies2__PowerupVaseBreaker__

#include "BasePowerup.h"
#include "RestrictionSet.h"

class PowerupVaseSelector : public PowerupTouchBased
{
public:
	RT_CLASS_DEFINE(PowerupVaseSelector, PowerupTouchBased, RtClass) {}
	
	virtual void Draw(Sexy::Graphics* i_g) override;
	
protected:
	bool onTouchBegin(const Sexy::Touch& i_touch) override;
	void onTouchEnd(const Sexy::Touch& i_touch) override;
	
	virtual bool canActivateOnVase(class GridItemVase* i_vase) { return true; }
	virtual void activateOnVase(class GridItemVase* i_vase) { }

private:
	class GridItemVase* getFirstVaseAt(const Point& i_gridLoc) const;
	bool canActivateOnVase(class GridItemVase* i_vase) const;
};

class PowerupVaseBreakerReveal : public PowerupVaseSelector
{
public:
	RT_CLASS_DEFINE(PowerupVaseBreakerReveal, PowerupVaseSelector, RtClass) {}
	
	//bool ShouldDrawBoardOverlay() override { return false; }
	virtual bool ShouldHighlightUnrevealedVases() { return true; }
protected:
	bool canActivateOnVase(class GridItemVase* i_vase) override;
	void activateOnVase(class GridItemVase* i_vase) override;


	OVERRIDE_STATE_ONENTER(PowerupState, Activated);
};

class PowerupVaseBreakerColor : public PowerupVaseSelector
{
public:
	RT_CLASS_DEFINE(PowerupVaseBreakerColor, PowerupVaseSelector, RtClass) {}
	
protected:
	bool canActivateOnVase(class GridItemVase* i_vase) override;
	void activateOnVase(class GridItemVase* i_vase) override;
};

class PowerupTypeVaseBreakerButter : public PowerupType
{
public:
	RT_CLASS_DEFINE(PowerupTypeVaseBreakerButter, PowerupType, RtClass);
	
	float ButterDuration;
};

class PowerupVaseBreakerButter : public PowerupTouchBased
{
public:
	RT_CLASS_DEFINE(PowerupVaseBreakerButter, PowerupTouchBased, RtClass) {}
	
protected:
	bool onTouchBegin(const Sexy::Touch& i_touch) override;
	void onTouchMoved(const Sexy::Touch& i_touch) override;
	void onTouchEnd(const Sexy::Touch& i_touch) override;
	void onTouchCanceled() override;

	OVERRIDE_STATE_UPDATE(PowerupState, Selected);
	OVERRIDE_STATE_ONENTER(PowerupState, Activated);
	
private:
	class Zombie* getClosestButterableZombie(const SexyVector2& i_location, float i_maxGridSquareDistance);
	void setHighlightedZombie(class Zombie* i_zombie);
	
	RtWeakPtr<class Zombie> m_highlightedZombie;
};

class PowerupTypeVaseBreakerMove : public PowerupType
{
public:
	RT_CLASS_DEFINE(PowerupTypeVaseBreakerMove, PowerupType, RtClass);
	
	GridItemRestrictionSet GridItemsWhichBlockMove;
};

class PowerupVaseBreakerMove : public PowerupTouchBased
{
public:
	RT_CLASS_DEFINE(PowerupVaseBreakerMove, PowerupTouchBased, RtClass) {}
	
	PowerupVaseBreakerMove();
	
	virtual void Draw(Sexy::Graphics* i_g) override;
	
	//bool ShouldDrawBoardOverlay() override { return false; }
	virtual bool ShouldHighlightAllVases() { return !m_selectedVase.IsValid() && !m_queuedVase.IsValid(); }
protected:
	bool onTouchBegin(const Sexy::Touch& i_touch) override;
	void onTouchMoved(const Sexy::Touch& i_touch) override;
	void onTouchEnd(const Sexy::Touch& i_touch) override;
	void onTouchCanceled() override;
	
	OVERRIDE_STATE_ONENTER(PowerupState, Activated);
    OVERRIDE_STATE_ONEXIT(PowerupState, Selected);

private:
	class GridItemVase* getFirstVaseAt(const Point& i_gridLoc) const;
	bool canMoveVaseTo(const Point& i_gridLoc);
	
	void selectVase(class GridItemVase* i_vase);
	void clearSelection();
	void queueSelectedVase();
	void selectQueuedVase();
    void clearQueuedVase();
	
	RtWeakPtr<class GridItemVase> m_selectedVase;
	RtWeakPtr<class GridItemVase> m_queuedVase;
	bool m_dragging;
	bool m_movingQueuedVase;
};

#endif /* defined(__PlantsVersusZombies2__PowerupVaseBreaker__) */
