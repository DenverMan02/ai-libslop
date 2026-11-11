//
//  TimerBank.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-10-15.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TimerBank_h
#define PlantsVersusZombies2_TimerBank_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PrimeTextWidget.h"

namespace Message
{
    void TriggerTimeOver();
}

class TimerBank : public UIWidget
{
public:
    RT_CLASS_DEFINE(TimerBank, UIWidget, RtClass);
    
    TimerBank();
    virtual ~TimerBank();
    
    // Public Interface (Inheritable)
    virtual void				Draw(Graphics* i_g) override;
    virtual void                onUpdate() override;
    
    //PVZ2_CHINESE_START
    Rect GetUIRect();
    //PVZ2_CHINESE_END
    void SetStart(bool i_start);
    void SetDuration(float i_duration) { m_duration = i_duration; }
    bool HasStart();
    float GetRemainTime();
    float GetDuration();
    float GetElapseTime();
protected:
    // Protected Interface (Inheritable)
    //OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
    OVERRIDE_STATE_UPDATE(WidgetState, Ready);
    
    virtual void				initLoadingResourcesGroupList() override;
    virtual void				registerForEvents() override;
    virtual void				unregisterForEvents() override;
private:
    PrimeTextWidget*            m_textWidget;
    bool                        m_hasStart;
    pvztime_t                   m_endTime;
    float                       m_remainTime;
    float                       m_duration;
};

#endif
