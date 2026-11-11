//
//  CodeRewardUI.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16/11/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef CodeRewardUI_h
#define CodeRewardUI_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "RechargeRewardConfig.h"
#include "NetworkData.h"
#include "UISingletonDialog.h"

class CodeRewardUI : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::EditListener
{
public:
    enum
    {
        btnClose,
        btnCharge,
    };
    
    CodeRewardUI();
    virtual ~CodeRewardUI();
    
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;

    virtual bool	AllowKey(int theId, KeyCode theKey) override;
    virtual void    EditWidgetText(int i_id, const SexyString& i_string) override;
    virtual bool    AllowChar(int i_id, SexyChar i_char) override;
    virtual bool	AllowText(int theId, const SexyString& theText) override;
    
    void onRewardResult(bool i_success, const S2C_CodeRewardResult* pData);
private:
    Rect m_dialogRect;
    Rect m_editRect;
    Rect m_inputRect;

    PVZ2UIButton* m_closeButton = nullptr;
    PVZ2UIEditWidget* m_editWidget = nullptr;
    PVZ2UIButton* m_chargeButton = nullptr;
    
    class CodeRewardErrorDialog* pErrorDialog = nullptr;
    class CodeRewardDlg*        pCodeRewardDlg = nullptr;
    
    void showError(bool iserror, const SexyString& iContent);
    void showRewardList(const S2C_CodeRewardResult* pData);
};

class CodeRewardErrorDialog : public Sexy::Widget, public Sexy::ButtonListener
{
public:

    CodeRewardErrorDialog();
    virtual ~CodeRewardErrorDialog();
    
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    void showError(bool iserror, const SexyString& iContent);

private:
    Rect m_dialogRect;
    SexyString m_timeError;
    SexyString m_contentError;
    bool        m_isError;
};

class CodeRewardDlg : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    CodeRewardDlg();
    virtual ~CodeRewardDlg();
    
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    void showRewardList(const S2C_CodeRewardResult* pData);
    int  calStartX(int rowCount);
private:
    std::vector<S2C_CodeRewardPlantNum>   m_rewardList;
    SexyString m_contentTitle;
    Rect m_dialogRect;
    
    int m_startX;
    int m_startY;
    int m_firstRowCount;
};

#endif /* CodeRewardUI_h */
