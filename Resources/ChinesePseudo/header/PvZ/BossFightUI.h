//
//  BossFightUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/9/10.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BossFightUI__
#define __PlantsVersusZombies2__BossFightUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "MagentoService.h"

class BossFightUI : public Sexy::Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    BossFightUI();
    ~BossFightUI();
    
    virtual void Update();
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Draw(Graphics* i_g);
    virtual void ButtonDepress(int i_id);
    
    // implement of Sexy::ScrollWidgetListener
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}
    
    void UpdateTimeLabel(Sexy::Graphics* i_g);
private:
    Sexy::Rect m_timeRect;
    Sexy::Rect m_rectDialog;
    SexyString m_strTime;
    PVZ2UIButton* m_startButton;
};


#endif /* defined(__PlantsVersusZombies2__BossFightUI__) */
