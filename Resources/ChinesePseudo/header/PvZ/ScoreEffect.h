//
//  ScoreEffect.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.20
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ScoreEffect__
#define __PlantsVersusZombies2__ScoreEffect__

#include "BoardEntity.h"

class ScoreEffect : public BoardEntity
{
public:
	enum 
	{
		State_Begin,
		State_Scale1,
		State_Scale2,
		State_FadeOut,
		State_End,
	};
public:
	RT_CLASS_DEFINE(ScoreEffect, BoardEntity, RtClass);
	ScoreEffect();
	
	bool				ShouldDrawShadow() const override { return false; }
	virtual int		GetRenderOrder() const override { return m_renderOrder; }
	virtual int		CalcRenderOrder() const override { return m_renderOrder; }

	void				InitialiseEffect(const std::string& strScore, const std::string& font_prefix, const SexyVector2& pos);
	void				SetRenderOrder(int i_renderOrder) { m_renderOrder = i_renderOrder; }
	
protected:
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onDraw(class Sexy::Graphics* i_g) override;

protected:
	std::vector<ImagePtr>	m_ImageList;
	int				m_state;
	int				m_renderOrder;
	pvztime_t	m_startTime;
	float				m_fScale;
	int				m_iAlpha;
	SexyVector2	m_curPosition;
	SexyVector2	m_startPosition;
};

#endif /* defined(__PlantsVersusZombies2__ScoreEffect__) */
