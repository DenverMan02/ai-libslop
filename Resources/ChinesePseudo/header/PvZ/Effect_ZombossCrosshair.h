//
//  Effect_ZombossCrosshair.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Effect_ZombossCrosshair__
#define __PlantsVersusZombies2__Effect_ZombossCrosshair__

#include "StandaloneEffect.h"
#include "TimeLine.h"

class Effect_PopAnim;

class Effect_ZombossCrosshair : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_ZombossCrosshair, StandaloneEffect, RtClass);
	
	Effect_ZombossCrosshair()
	{}
	
	void InitializeCrosshair(const Point& i_Pos,
                             const std::string& i_popAnimName,
                             const std::string& i_popAnimAnim,
                             float i_introTime,
                             bool  b_IsgridLoc = true);
	void StartOutro(float i_outroTime, float i_endScale, float i_endRotation);

protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;

private:
	void buildIntroCurves(float i_introTime, float i_startScale, float i_startRotationDegs);
	void buildOutroCurves(float i_outroTime, float i_endScale, float i_endRotationDegs);
	void updateFromCurves();
	
	RtWeakPtr<Effect_PopAnim> m_crosshairEffect;
	CurveCollection_Float m_curves;
};

#endif /* defined(__PlantsVersusZombies2__Effect_ZombossCrosshair__) */
