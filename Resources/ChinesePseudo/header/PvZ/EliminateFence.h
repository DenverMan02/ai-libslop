//
//  EliminateFence.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-5-6.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemEliminateFence__
#define __PlantsVersusZombies2__GridItemEliminateFence__

#include "BoardEntity.h"

enum EFenceType
{
    EFenceType_Down = 0,
    EFenceType_Right,
    EFenceType_Count
};

class EliminateFence : public BoardEntity
{
public:
	RT_CLASS_DEFINE(EliminateFence, BoardEntity, RtClass);
    
	EliminateFence();
	virtual ~EliminateFence();
    
    void EliminateFenceInitialize(EFenceType i_type);
    
    void takeFenceDamge();
    
    int CalcRenderOrder() const override;
    bool ShouldDrawShadow() const override { return false; }

    EFenceType GetFenceType();
    
    int m_row;
    int m_col;
    
protected:
    
	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate()                        override;
	virtual void onDestroy()                       override;
    
    void onPlayDieEnd(const std::string& i_animLabelName);
    
private:
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    EFenceType                  m_type;
    
    int                         m_Health;
    int                         m_eliminateCountOfTakeDamge;
};

namespace Message
{
	void EliminateFenceDestroyed(int i_row,int i_col,int i_type);
}

#endif /* defined(__PlantsVersusZombies2__GridItemEliminateFence__) */
