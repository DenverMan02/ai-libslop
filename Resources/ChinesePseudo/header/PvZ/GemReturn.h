//
//  StoreUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GemReturn_h
#define PlantsVersusZombies2_GemReturn_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "MagentoService.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"



class CGemReturnUI : public Widget, public ButtonListener ,public Sexy::ScrollWidgetListener
{
public:
	CGemReturnUI();
	virtual ~CGemReturnUI();

    void TouchEnded(const Sexy::Touch& i_touch) override;
	virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g) override;
    virtual void Draw(Graphics* i_g) override;
	virtual void Update() override;
	virtual void ButtonPress(int i_id) override;
	virtual void ButtonDepress(int i_id) override;
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {};
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {};
    
    void  onPaySucess();
    
    void WaitForTutorialClick()
    {
        m_clicked = false;
    }
    bool WasClickedForTutorial()
    {
        return m_clicked;
    }

private:
    Image* m_imgbkgddecorate;
    Rect  m_bksizeRect;
    class PVZ2UIScrollingWidget* m_scrollingWidget;
    class CItemList* m_listItem;
    class PVZ2UIButton* m_activeButton;
    bool  m_clicked;
};

#endif
