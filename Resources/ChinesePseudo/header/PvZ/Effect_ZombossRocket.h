//
//  Effect_ZombossRocket.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Effect_ZombossRocket__
#define __PlantsVersusZombies2__Effect_ZombossRocket__

#include "StandaloneEffect.h"
#include "TimeLine.h"

class Effect_PopAnim;
class ZombossRocket;
class CannonRocket;

class Effect_ZombossRocket : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_ZombossRocket, StandaloneEffect, RtClass);
	
	void InitializeRocket(ZombossRocket* i_controller, const Point& i_targetGridPosition, const std::string& i_popAnim, const std::string& i_animName, float i_rocketHitTime, float i_rocketSpeed);
    
    void InitializeRocket(CannonRocket* i_controller, const Point& i_boardPosition, const std::string& i_popAnim, const std::string& i_animName, float i_rocketHitTime, float i_rocketSpeed);
	
protected:
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	
private:
	void updateFromCurves();
	void buildCurves(float i_rocketHitTime, float i_rocketSpeed);
	
	RtWeakPtr<ZombossRocket>  m_rocketController;
    RtWeakPtr<CannonRocket>   m_cannonRocketController;
    
	RtWeakPtr<Effect_PopAnim> m_rocketEffect;
	Point                     m_targetBoardPixel;
	CurveCollection_Float     m_curves;
    bool                      m_IsZomboss = false;
};

#endif /* defined(__PlantsVersusZombies2__Effect_ZombossRocket__) */
