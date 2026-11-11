//

//  UIWidgetImage.h

//  PlantsVersusZombies2

//

//  Created by Wu, Emma on 2015.10.28

//  Copyright (c) 2015 PopCap Games. All rights reserved.

//



#ifndef _UITabControl_h_

#define _UITabControl_h_



#include "UIWidgetBackground.h"

#include "TodCommon.h"

#include "UIListener.h"

#include "StringHelper.h"



//-----------------------------------------------------

class UITabContent : public Sexy::Widget

{

    friend class UITabControl;

public:

    UITabContent();

    

    void                    SetAttachTab(class UIWidgetRadio* pAttach);

    class UIWidgetRadio*    GetAttachTab() { return m_attachedTab; }

    

    void                    SetTabID(int tabID);

    int                     GetTabID() const;

    void                    SetTabName(const SexyString& tabName);

    const SexyString&       GetTabName() const;

    

    void                    SetTabImage(const std::string& str, bool drawTab = true);

    const std::string&      GetTabImage() const { return m_tabImage; }

    bool					GetDrawTab() { return m_drawTab; }

protected:

    class UIWidgetRadio*    m_attachedTab;

    int                     m_tabID;

    SexyString              m_tabName;

    std::string             m_tabImage;

    bool					m_drawTab;

};



//-----------------------------------------------------

class UITabControl : public Sexy::Widget, public UI::RadioListener

{

public:

    enum

    {

        Type_Default = 0,

        Type_TopWide = 1,

        Type_Horisontal = 2,

        Type_Vertical = 3,

        Type_Horisontal_Center = 4,
    };

public:

	UITabControl();

	virtual ~UITabControl();



	virtual void                Update();

	virtual void                Draw(Sexy::Graphics* i_g);

    virtual void                AddWidget(Widget* theWidget);

    virtual void                RemoveWidget(Widget* theWidget);

    virtual void                Resize(int theX, int theY, int theWidth, int theHeight);

    

    // UI::RadioListener

    //using UI::RadioListener::RadioSelectionChanged;

    virtual void                RadioSelectionChanged(class UIWidgetRadio* pRadioBtn);

    

    void                        SetBackground(Sexy::Image* pImg);

    Sexy::Image*                GetBackground() { return m_backgroundImage; }

    void							SetType(int iType);

    int							GetType() const { return m_type; }

    void                        SetTabSize(int iWidth, int iHeight);

    UITabContent*               AddTab(int tabID, const std::string& widget_name = StringHelper::Empty);

    bool                        DeleteTab(int tabID);

    UITabContent*               GetTab(int tabID);

    UITabContent*               GetTab(class UIWidgetRadio* pTabBtn);

    UITabContent*               GetTabSelected();

    int                         GetTabSelectedID();

    void                        SetTabSelected(UITabContent* pTabContent);

    void                        SetTabVisible(int tabID, bool bVisible);

    void                        SetListener(class UI::TabControlListener* listener);

    static bool                 IsTabButton(Sexy::Widget* pWidget);

    void						SetTabWidthHeight(int i_width, int i_height);

protected:

    class UIWidgetRadio*        createTabButton();

    void                        resizeTabButtons();

    void                        changeTabSelected();

    void                        makeTabVisible(UITabContent* pTab);

    int                         getUniqueTabID();

    

protected:

    Sexy::Widget*               m_tabButtonPane;

    

    Sexy::Image*                m_backgroundImage;

    int                         m_type;

    

    UITabContent*               m_pSelectedTab;

    int                         m_tabButtonWidth;

    int                         m_tabButtonHeight;

public:

    class UI::TabControlListener*   m_TabControlListener;

};











#endif /* STATIC_TEXT_H_ */

