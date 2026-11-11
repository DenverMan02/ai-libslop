//
//  ArenaOccupyStartButton.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-16.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaOccupyStartButton__
#define __PlantsVersusZombies2__ArenaOccupyStartButton__

#include "UIWidget.h"

class ArenaOccupyStartButton : public UIWidget, public ButtonListener
{
public:
    RT_CLASS_DEFINE(ArenaOccupyStartButton, UIWidget, RtClass) {}
    
    ArenaOccupyStartButton();
    ~ArenaOccupyStartButton();
    
    virtual void Draw(Graphics* i_g) override;
    
    void SetLabel(const SexyString& i_label);
    void SetPVPCoin(int iVal);
    
protected:
    
    virtual void initLoadingResourcesGroupList() override;
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    
private:
    bool handleTouch(const Sexy::Touch& i_touch);
    void startTouch(Sexy::TouchID i_touchIdent);
    void cancelTouch();
    
    class StretchableNewLawnButton* m_startGameButton;
    Sexy::TouchID m_touchIdent;
    int     m_pvpcoin = 0;      //-1 means not show coin
};

namespace Message
{
    void ArenaOccupyButtonPressed();
    void ArenaStartPVPButtonPressed();
}

#endif /* defined(__PlantsVersusZombies2__ArenaOccupyStartButton__) */
