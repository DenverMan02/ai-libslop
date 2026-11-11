//
//  ArenaChangeSpeedButton.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-23.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaChangeSpeedButton__
#define __PlantsVersusZombies2__ArenaChangeSpeedButton__

#include "UIWidget.h"

class ArenaChangeSpeedButton : public UIWidget, public ButtonListener
{
public:
    enum SpeedButtonState
    {
        SPEED_1,
        SPEED_2,
        SPEED_3
    };
    
    RT_CLASS_DEFINE(ArenaChangeSpeedButton, UIWidget, RtClass) {}
    
    ArenaChangeSpeedButton();
    ~ArenaChangeSpeedButton();
    
    virtual void Draw(Graphics* i_g) override;
    
protected:
    
    virtual void initLoadingResourcesGroupList() override;
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    
private:
    bool handleTouch(const Sexy::Touch& i_touch);
    void startTouch(Sexy::TouchID i_touchIdent);
    void cancelTouch();
    
    Sexy::TouchID m_touchIdent;
    SpeedButtonState m_state;
    int m_speed;
    SexyString m_speedTxt;
};

namespace Message
{
    void ArenaChangeSpeedButtonPressed(float i_speed);
}

#endif /* defined(__PlantsVersusZombies2__ArenaChangeSpeedButton__) */
