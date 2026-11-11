//
//  Effect_BeachWaterWave.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-1-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_BeachWaterWave_h
#define PlantsVersusZombies2_Effect_BeachWaterWave_h

#include "Effect_PopAnim.h"

class Effect_BeachWaterWave : public Effect_PopAnim
{
    
public:
    
	RT_CLASS_DEFINE(Effect_BeachWaterWave, Effect_PopAnim, RtClass);
    
    Effect_BeachWaterWave();
    
    void onDraw(Graphics* i_g) override;
    
    void registerForEvents() override;
    
protected:
    
    void DoChangeColor(bool bFadeOut);
    
protected:
    
    bool m_bNeedFade;
    
    bool m_bFadeOut;
    
    pvztime_t m_tChangerColorStarTime;
};

#endif
