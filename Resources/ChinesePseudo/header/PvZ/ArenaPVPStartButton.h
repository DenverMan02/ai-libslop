//
//  ArenaPVPStartButton.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-12.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaPVPStartButton__
#define __PlantsVersusZombies2__ArenaPVPStartButton__

#include "UIWidget.h"

class ArenaPVPStartButton : public UIWidget, public ButtonListener
{
public:
    RT_CLASS_DEFINE(ArenaPVPStartButton, UIWidget, RtClass) {}
    
    ArenaPVPStartButton();
    ~ArenaPVPStartButton();
    
    virtual void Draw(Graphics* i_g) override;
    virtual void onUpdate() override;
    
    void SetLabel(const SexyString& i_label);
    
    void SetStart(bool i_start);
    void SetDuration(float i_duration) { m_duration = i_duration; }
    
protected:
    
    virtual void initLoadingResourcesGroupList() override;
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    
private:
    bool handleTouch(const Sexy::Touch& i_touch);
    void startTouch(Sexy::TouchID i_touchIdent);
    void cancelTouch();
    
    class StretchableNewLawnButton* m_startGameButton;
    Sexy::TouchID m_touchIdent;
    
    bool                        m_hasStart;
    pvztime_t                   m_endTime;
    float                       m_remainTime;
    float                       m_duration;
};

namespace Message
{
    void ArenaPVPButtonPressed();
    void ChangePlayerCooldownEnd();
}

#endif /* defined(__PlantsVersusZombies2__ArenaPVPStartButton__) */
