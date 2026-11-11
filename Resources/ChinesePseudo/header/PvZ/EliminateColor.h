//
//  EliminateColor.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-5-21.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EliminateColor__
#define __PlantsVersusZombies2__EliminateColor__

#include "BoardEntity.h"
#include "Effect_PopAnim.h"

class EliminateColor : public BoardEntity
{
public:
	RT_CLASS_DEFINE(EliminateColor, BoardEntity, RtClass);
    
	EliminateColor();
	virtual ~EliminateColor();
    
    void            EliminateColorInitialize();
    
    int CalcRenderOrder() const override;
    
    void playDisappearAnim();
    
    int m_row;
    int m_col;
    
protected:
    
	virtual void onDraw(class Sexy::Graphics* i_g) override;
    
	virtual void onUpdate() override;
	virtual void onDestroy() override;
    
    void onDisappearAnimDone(const std::string& i_animLabel);
    
private:
    
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
};

namespace Message
{
	void EliminateColorDisappear(int i_row,int i_col);
}

#endif /* defined(__PlantsVersusZombies2__EliminateColor__) */
