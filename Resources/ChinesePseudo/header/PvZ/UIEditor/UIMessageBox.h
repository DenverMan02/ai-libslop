//
//  UIMessageBox.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.12.9.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UIMessageBox__
#define __PlantsVersusZombies2__UIMessageBox__
#pragma once

#include "UISingletonDialog.h"
#include "StringHelper.h"
#include "LuaEngine.h"

class UIMessageBox : public UISingletonDialog<UIMessageBox>
{
public:
    typedef Sexy::Delegate2<UIMessageBox*, int> MessageCallbackEvent;
    enum
    {
        Btn_Close = 0,
        Btn_OK = 1,
        Btn_Cancel = 2,
        Btn_Confirm = 3,
        Btn_Confirm2 = 4,
        Btn_Confirm3 = 5
    };
    enum ShowType
    {
        Type_ShowClose = 1<<0,
        Type_ShowOK = 1<<1,
        Type_ShowCancel = 1<<2,
        
        Type_Default = 0xFF,
    };
    enum BtnMode
    {
    	BtnMode_Both,
    	BtnMode_Gem,
    	BtnMode_AD,
    	BtnMode_ExtraGem,
    	BtnMode_Extra
    };
public:
    UIMessageBox();
    virtual ~UIMessageBox();
    virtual bool							OnCreate() override;
    virtual std::string                 GetLayoutName() override { return "uimessagebox"; }
    virtual void                        OnClose() override;
    //virtual void							Draw(Sexy::Graphics* i_g);
    
    void 								SetNewBackground(int i_addWidth, int i_addHeight, BtnMode i_btnMode);
    void								SetADMessage(const SexyString&strTips);

    // ButtonListener
    virtual void							ButtonDepress(int i_id) override;
    // callback
    void	                             	Draw(Sexy::Graphics* i_g) override;
    void                                SetCallback(MessageCallbackEvent iEvent) {m_callbackEvent = iEvent;}
    void                                SetCancelCallback(MessageCallbackEvent iEvent) {m_cancelCallbackEvent = iEvent;}
    void                                SetExtraCallback(MessageCallbackEvent iEvent) {m_extraCallbackEvent = iEvent;}
    void                                SetExtraCancelCallback(MessageCallbackEvent iEvent) {m_extraCancelCallbackEvent = iEvent;}
    void                                SetLuaCallback(LUA_FUNCTION nHandler) {m_luaHandler = nHandler;}
    void                                SetMessage(const SexyString&strTips, const SexyString& strTitle);
    void                                SetMessage(const std::string& strTips, const std::string& strTitle = StringHelper::Empty);
    void                                SetShowType(int i_type = Type_Default); // enum ShowType
    void                                SetBackground(const std::string& strImage);
    void                                SetBackground(Sexy::Image* pImage);
	void				                    SetBackgroundDarken(bool hasBackgroundDarken, float backgroundAlphaPercent = 0.5);
    class PVZ2UIButton*                 GetButtonOK();
    class PVZ2UIButton*                 GetButtonCancel();
    class PVZ2UIButton*                 GetButtonCloseOld();

    class PVZ2UIButton*					GetButtonLeft();
    class PVZ2UIButton*					GetButtonRight();
    class PVZ2UIButton*					GetButtonExtra();
    class PVZ2UIButton*                 GetButtonCloseNew();

    class UIWidgetText*                 GetTextWidget() { return m_pText; }
    void                                SetTitleFont(int idx);
    void                                SetTextFont(int idx);

    void                                SetTextColor(Sexy::Color color);
    // Color::White
protected:
    bool				m_hasBackgroundDarken;
    float            m_backgroundAlphaPercent;
    class UIWidgetText*                 m_pText;
    class UIWidgetImage*                m_pBackground;
    MessageCallbackEvent               m_callbackEvent;
    MessageCallbackEvent               m_cancelCallbackEvent;
    MessageCallbackEvent               m_extraCallbackEvent;
    MessageCallbackEvent               m_extraCancelCallbackEvent;
    int                 m_luaHandler = 0;
};

#endif /* defined(__PlantsVersusZombies2__UIMessageBox__) */
