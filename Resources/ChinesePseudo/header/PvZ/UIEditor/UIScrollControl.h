//
//  UIScrollControl.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.30.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIScrollControl_h_
#define _UIScrollControl_h_

#include "PVZ2UIButton.h"

class UIScrollControl : public Sexy::ScrollWidget
{
public:
    UIScrollControl();
	virtual ~UIScrollControl();

	virtual void    Draw(Sexy::Graphics* i_g) override;
    virtual void    AddWidget(Widget* theWidget) override;
    virtual void    RemoveWidget(Widget* theWidget) override;
    virtual void    PutBehind(Widget* theWidget, Widget* theRefWidget) override;
    virtual void    PutInfront(Widget* theWidget, Widget* theRefWidget) override;
    virtual void    Resize(int theX, int theY, int theWidth, int theHeight) override;
    
    void            SetBackground(const PVZ2UIImage& i_backgroundImage);
    void            Layout();

    void            SetAutoArrange(bool setting);
    bool            IsAutoArrange() const { return m_bAutoArrange; }
    
    void            SetPadding(int iVal);
    int             GetPadding() const { return m_iPadding; }
    
    int             GetScrollMode() const;
    void            ScrollToMax(bool animated);
    
    void            ClearContents();
    int             GetItemCount();

protected:
	PVZ2UIImage     m_backgroundImage;
    bool            m_bAutoArrange;
    int             m_iPadding;
};



#endif
