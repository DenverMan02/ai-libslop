//
//  UIWidgetRadio.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.28
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIWidgetRadio_h_
#define _UIWidgetRadio_h_

#include "ButtonWidget.h"

namespace UI
{
    class RadioListener;
}

class UIWidgetRadio : public Sexy::ButtonWidget
{
public:
    enum AlignType
    {
        Align_Normal = 0,
        Align_Center = 1,
        Align_TabBottom = 2,
        Align_TabTop = 3,
        Align_TabTopWide = 4,
        Align_Horizontal = 5,
        Align_Vertical = 6,
    };
    enum
    {
        Color_Text = ButtonWidget::NUM_COLORS,
        Color_TextSelected,
    };
public:
	UIWidgetRadio();
	virtual ~UIWidgetRadio();
    
    virtual void    Draw(Sexy::Graphics* i_g) override;
    void            TouchBegan(const Sexy::Touch& i_touch) override;
    void            TouchMoved(const Sexy::Touch& i_touch) override;
    void            TouchEnded(const Sexy::Touch& i_touch) override;
    void            TouchesCanceled() override;
    
    void            SetSelected(bool setting);
    bool            IsSelected() const;
    
    void            SetAlign(int val) { m_align = val; }
    int             GetAlign() const { return m_align; }

protected:
    bool            m_bSelected;
    Sexy::TouchID   m_touchIdent;
    bool            m_touchIsOver;
    int             m_align;
public:
    class UI::RadioListener* m_RadioListener;

};



#endif
