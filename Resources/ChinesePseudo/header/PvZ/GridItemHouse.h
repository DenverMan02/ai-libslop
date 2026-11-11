//
//  GridItemHouse.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-16.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemHouse__
#define __PlantsVersusZombies2__GridItemHouse__

#include "Precompile.h"
#include "GridItem.h"

class GridItemHouse : public GridItem
{
public:
	
	RT_CLASS_DEFINE(GridItemHouse, GridItem, RtClass);
    
    GridItemHouse();
	virtual ~GridItemHouse();
    
    void    TakeDamage(const DamageInfo& i_damage) override;
    
    void	LawnHouseInitialize(PopAnim* i_mowerPopAnim, int i_row);
    
    //int	    GetRow() { return m_row; }
    
    virtual Sexy::Rect calcCollisionRect() override;
    
    /// BoardEntity interface
	virtual int 		CalcRenderOrder() const override;
    
protected:
	
	virtual void				onGridItemInitialize() override;
	virtual void				onUpdate() override;
    virtual void                onDestroy() override;
    virtual void                onDraw(Graphics* i_g) override;
    
private:
    void                        initializePAM(PopAnim* i_mowerPopAnim);
    void                        onAnimStopped(const std::string& i_animName);
    void                        onTipAnimStopped(const std::string& i_animName);
    void                        ChangeTip();
    
private:
	
    int                         m_row = 0;
	
	RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    RtWeakPtr<class PopAnimRig>	m_popAnimTipRig;
};

class GridItemHouseProps : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemHouseProps, GridItemPropertySheet, RtClass);
};

#endif /* defined(__PlantsVersusZombies2__GridItemHouse__) */
