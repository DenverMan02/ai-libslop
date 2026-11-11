//
//  GridItemBrain.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-24.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemBrain__
#define __PlantsVersusZombies2__GridItemBrain__

#include "Precompile.h"
#include "GridItem.h"

class GridItemBrain : public GridItem
{
public:
	
	RT_CLASS_DEFINE(GridItemBrain, GridItem, RtClass);
    
    GridItemBrain();
	virtual ~GridItemBrain();
    
    void	LawnBrainInitialize(PopAnim* i_mowerPopAnim, int i_row);
    
    int	    GetRow() { return m_row; }
    
    static SexyVector2	GetArtOffset();
    
    virtual Sexy::Rect calcCollisionRect() override;
    
    /// BoardEntity interface
	virtual int 		CalcRenderOrder() const override;
    
    virtual void TakeDamage(const DamageInfo& i_damage) override;
    
protected:
	
	virtual void				onGridItemInitialize() override;
	virtual void				onUpdate() override;
    virtual void                onDestroy() override;
    virtual void                onDraw(Graphics* i_g) override;
    virtual void                KillGridItem() override;
    void                        onAnimStoppedCallback(const std::string& i_animLabel);
    bool                        CanBeTargetedBy(const BoardEntity* i_entity) const override;
    
private:
    void                        initializePAM(PopAnim* i_mowerPopAnim);
    float                       getRowToPixelY();
	
private:
	
    int                         m_row;
	
	RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    bool                        m_hasPlayDieAnim;
};

class GridItemBrainProps : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemBrainProps, GridItemPropertySheet, RtClass);
};

namespace Message
{
	void BrainDie(GridItemBrain * i_brain);
}

#endif /* defined(__PlantsVersusZombies2__GridItemBrain__) */
