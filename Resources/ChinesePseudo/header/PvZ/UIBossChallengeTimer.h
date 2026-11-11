//
//  UIBossChallengeTimer.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/8/24.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIBossChallengeTimer_h
#define UIBossChallengeTimer_h

#include "RtObject.h"
#include "UIWidget.h"
#include "PrimeTextWidget.h"

class BossChallengeTimer : public UIWidget
{
public:
    RT_CLASS_DEFINE(BossChallengeTimer, UIWidget, RtClass);
    
    BossChallengeTimer();
    virtual ~BossChallengeTimer();
    
    virtual void				Draw(Graphics* i_g) override;
    virtual void             onUpdate() override;
    
    void Start(bool start);
    void Reset();
    float GetTime();
private:
    bool                  m_start = false;
    pvztime_t             m_startTime = 0;
    pvztime_t             m_endTime = 0;
    float                 m_second = 0;
};

#endif /* UIBossChallengeTimer_h */
