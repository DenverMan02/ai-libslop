//
//  Effect_BouncingArrow.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_BouncingArrow_h
#define PlantsVersusZombies2_Effect_BouncingArrow_h

#include "StandaloneEffect.h"

class Effect_BouncingArrow : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_BouncingArrow, StandaloneEffect, RtClass);
	
    void SetTransX(bool i_transX);
	void SetRotation(float i_rads);
	void SetArrowImage(ImagePtr i_image);
	void SetBounceHeightsBoardSpace(float i_minBounceHeight, float i_maxBounceHeight);
	void ResetStartTime();
    
    void PointUp() { SetRotation(SexyMath::DegToRad(180)); }
	void PointDown() { SetRotation(SexyMath::DegToRad(0)); }
	void PointLeft() { SetRotation(SexyMath::DegToRad(270)); }
	void PointRight() { SetRotation(SexyMath::DegToRad(90)); }

protected:
	// Virtual internal dispatches
	virtual void onInitialized() override;
	virtual void onDraw(class Graphics* i_g) override;
	
private:
	ImagePtr 	m_image;
	
	pvztime_t 	m_startTime;
	float 		m_rotationRads;
	float		m_minBounceHeightScreenSpace;
	float		m_maxBounceHeightScreenSpace;
    
    bool        m_IsTransX;
};

typedef RtWeakPtr<class Effect_BouncingArrow> Effect_BouncingArrowPtr;

#endif
