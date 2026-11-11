//
//  HighTideSign.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HighTideSign__
#define __PlantsVersusZombies2__HighTideSign__

#include "BoardEntity.h"

typedef enum
{
	HIGH_TIDE_SIGN_HIGH_TIDE,
	HIGH_TIDE_SIGN_BOWLING_FOUL
} HIGH_TIDE_SIGN_TYPE;

class HighTideSign : public BoardEntity
{
public:
	RT_CLASS_DEFINE(HighTideSign, BoardEntity, RtClass);
	
	void Initialize(float i_highTideLevel, HIGH_TIDE_SIGN_TYPE i_signType);
	int CalcRenderOrder() const override;
    bool ShouldDrawShadow() const override { return false; }
	
protected:
	void onDraw(Sexy::Graphics* i_g) override;
	
private:
	Image* getSignImage();
	
	float m_highTideLevel;
	HIGH_TIDE_SIGN_TYPE m_signType;
	Sexy::Rect m_srcRect;
	Sexy::Rect m_destRect;
};

#endif /* defined(__PlantsVersusZombies2__HighTideSign__) */
