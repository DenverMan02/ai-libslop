//
//  UIWidgetImage.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.28
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIPage_h_
#define _UIPage_h_

#include "Widget.h"
#include "TodCommon.h"
#include "UIListener.h"
#include "StringHelper.h"

//-----------------------------------------------------
class UIPage : public Sexy::Widget, public UI::RadioListener
{
public:
	UIPage();
	virtual~UIPage();
    virtual void                Resize(int theX, int theY, int theWidth, int theHeight);
    
    // UI::RadioListener
    //using UI::RadioListener::RadioSelectionChanged;
    virtual void                RadioSelectionChanged(class UIWidgetRadio* pRadioBtn);

    void                        SetPageImage(Sexy::Image* pImgN, Sexy::Image* pImgS);
    Sexy::Image*                GetPageImageNormal() { return m_pImageNormal; }
    Sexy::Image*                GetPageImageSelected() { return m_pImageSelected; }
    void                        SetClickable(bool setting);
    bool                        IsClickable() const;
    
    // Page begin from 0 to N.
    void                        SetCurPage(int iPage);
    void                        SetMaxPage(int iPage);
    int                         GetCurPage();
    int                         GetMaxPage();
    
    void                        SetPadding(int iVal) { m_iPadding = iVal; }
    int                         GetPadding() const { return m_iPadding; }
    
protected:
    class UIWidgetRadio*        createPageButton();
    void                        resizePageButtons();
    
protected:
    Sexy::Image*                m_pImageNormal;
    Sexy::Image*                m_pImageSelected;
    std::vector<class UIWidgetRadio*>   m_btnList;
    int                         m_iPadding;
    
public:
    class UI::PageListener*   m_PageListener;
};





#endif /* STATIC_TEXT_H_ */
