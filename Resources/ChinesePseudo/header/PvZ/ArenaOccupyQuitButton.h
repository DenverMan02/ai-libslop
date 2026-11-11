//
//  ArenaOccupyQuitButton.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-17.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaOccupyQuitButton__
#define __PlantsVersusZombies2__ArenaOccupyQuitButton__

#include "UIWidget.h"

class ArenaOccupyQuitButton : public UIWidget, public ButtonListener
{
public:
    RT_CLASS_DEFINE(ArenaOccupyQuitButton, UIWidget, RtClass) {}
    
    ArenaOccupyQuitButton();
    ~ArenaOccupyQuitButton();
    
    virtual void Draw(Graphics* i_g) override;
    
    void SetLabel(const SexyString& i_label);
    
protected:
    
    virtual void initLoadingResourcesGroupList() override;
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    
private:
    bool handleTouch(const Sexy::Touch& i_touch);
    void startTouch(Sexy::TouchID i_touchIdent);
    void cancelTouch();
    
    class StretchableNewLawnButton* m_startGameButton;
    Sexy::TouchID m_touchIdent;
};

namespace Message
{
    void ArenaOccupyQuitButtonPressed();
}

#endif /* defined(__PlantsVersusZombies2__ArenaOccupyQuitButton__) */
