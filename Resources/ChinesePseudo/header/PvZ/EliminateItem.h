//
//  EliminateItem.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-3-16.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridEliminateItem__
#define __PlantsVersusZombies2__GridEliminateItem__

#include "BoardEntity.h"
#include "Effect_PopAnim.h"

/*
enum EEliminateType
{
    EEliminateType_Green = 0,
    EEliminateType_Brown,
    EEliminateType_Red,
    EEliminateType_Purple,
    EEliminateType_Blue,
    EEliminateType_PlantFood,
    EEliminateType_Count
};
*/

enum EEliminateType
{
    EEliminateType_Red = 0,
    EEliminateType_Brown,
    EEliminateType_Green,
    EEliminateType_Blue,
    EEliminateType_Purple,
    EEliminateType_PlantFood,
    EEliminateType_Clone,
    EEliminateType_Count,
    EEliminateType_None,
};

class EliminateItem : public BoardEntity
{
public:
	RT_CLASS_DEFINE(EliminateItem, BoardEntity, RtClass);
    
	EliminateItem();
	virtual ~EliminateItem();
    
    bool CanTouchable();

    Rect GetAttackRect();
    
    void            EliminateItemInitialize(EEliminateType i_type);
    
    EEliminateType  getEliminateType() const;
    
    void setSelect(bool    i_select);
    bool IsSelect();
    
    void setAlpha(bool     i_alpha);
    void setBlock();
    bool IsBlock();
    void takeBlockDamge();
    
    void playPlantFood();
    
    void playShowTip(bool i_show);
    
    bool IsNearBy(EliminateItem * other);
    bool IsNearByPlantFood(EliminateItem * other);
    
    int CalcRenderOrder() const override;
    bool ShouldDrawShadow() const override { return true; }
    
    int m_row;
    int m_col;
    
protected:
    
	virtual void onDraw(class Sexy::Graphics* i_g) override;
    virtual void onDrawShadow(class Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
    
    void onBlockDamge1(StandaloneEffect* i_effect);
    void onBlockDamge2(StandaloneEffect* i_effect);
    
    void onPlantFoodAnimDone(const std::string& i_animLabel);
    
private:
    
    EEliminateType  m_eliminateType;
    bool            m_select;
    bool            m_block;
    bool            m_alpha;
    
    int             m_blockHealth;
    int             m_eliminateCountOfTakeDamge;
    
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    RtWeakPtr<Effect_PopAnim> m_effect;
};

#endif /* defined(__PlantsVersusZombies2__GridEliminateItem__) */
