//
//  UIInputDialog.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/9/24.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UIInputDialog__
#define __PlantsVersusZombies2__UIInputDialog__
#pragma once

#include "UIDialog.h"
#include "EditListener.h"

class UIInputDialog : public UI::Dialog, public Sexy::EditListener
{
public:
    typedef Sexy::Delegate2<UIInputDialog*, int> InputCallbackEvent;
    enum
    {
        Btn_Cancel = 0,
        Btn_OK = 1,
    };
public:
    static UIInputDialog*               Create(bool bModel);
    UIInputDialog();
    virtual ~UIInputDialog();
    virtual bool							OnCreate();
    virtual std::string				GetLayoutName() { return "uiinput"; }
    virtual void                        OnClose();
    //virtual void							Draw(Sexy::Graphics* i_g);
    
    // ButtonListener
    virtual void							ButtonDepress(int i_id);
    // callback
    void                                SetCallback(InputCallbackEvent iEvent) {m_callbackEvent = iEvent;}
    void                                SetMessage(const std::string& strTips, const std::string& strInput);
    std::string                         GetInputText();
protected:
    class EditWidget*                   m_pInput;
    class UIWidgetText*                 m_pText;
    InputCallbackEvent                  m_callbackEvent;
    bool                                m_bModel;
};

#endif /* defined(__PlantsVersusZombies2__UIInputDialog__) */
