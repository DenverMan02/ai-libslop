//
//  AccountBindDialog.h
//  PlantsVersusZombies2
//
//  Created by lizheng on 7/24/14.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef IOS_ACCOUNTBIND_DIALOG_h
#define IOS_ACCOUNTBIND_DIALOG_h


#include "ButtonListener.h"
#include "Widget.h"
#include "Dialog.h"
#include "ButtonWidget.h"
#include "PVZ2UIButton.h"
#include "CameraPreviewWidget.h"
#include "CheckboxListener.h"
#include "LoginSDKMgr.h"

enum WindowShowState
{
    ON_BIND_WINDOW = 0,
    ON_TRANSFER_WINDOW,
};

enum AccountBindButtons
{
    AccountBindDialog_ExitButton,
    
    AccountBindDialog_LoginSinaButton,
    AccountBindDialog_LoginWechatButton,
    AccountBindDialog_LoginTencentButton,
    
    AccountBindDialog_LogoutSinaButton,
    AccountBindDialog_LogoutWechatButton,
    AccountBindDialog_LogoutTencentButton,
    
    AccountBindDialog_TransferSinaButton,
    AccountBindDialog_TransferWechatButton,
    AccountBindDialog_TransferTencentButton,
    
    AccountBindDialog_ShowBindWindowButton,
    AccountBindDialog_ShowTransferWindowButton,
    
    AccountBindDialog_PolicyButton,
};

class AccountBindDialog : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    AccountBindDialog();
	virtual ~AccountBindDialog();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);

    virtual void Update();
    
    virtual void ButtonPress(int i_id);
    
    virtual void ButtonDepress(int i_id);
    
    virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    
    PVZ2UIButton* createIconButton(const int i_xPos, const int i_yPos, const AccountBindButtons i_button, bool isgreen, int platform_id, const std::string& text);
    
    void OnBindingSuccess();
    void OnBindingFailed(int errorcode);
    
    void OnUnboundSuccess();
    void OnUnboundFailed(int errorcode);
    
    void OnTransferSuccess();
    void OnTransferFailed(int errorcode);

private:
    void InitializeControls();
    
    void updateDialogStatus();
    
    void ShowLogoScreen();
    
    void onSDKLoginCallback(int result);
    void onSDKLogoutCallback(int result);
    void onSDKTransferCallback(int result);
    
    void sinaLogin();
    void wechatLogin();
    void wechatUNInstalled();
    void tencentLogin();
    
    void sinaLogout();
    void wechatLogout();
    void tencentLogout();
    
    void sinaTransfer();
    void wechatTransfer();
    void tencentTransfer();
    
    Sexy::Rect    m_rectDialog;
    Sexy::Rect    m_rectInternal;
    Sexy::Rect    m_rectTitle;
    
    LoginSDKType    m_currentLoginSDKType;
    WindowShowState m_tabState;
    
    PVZ2UIButton* m_LoginSinaButton;
    PVZ2UIButton* m_LogoutSinaButton;
    PVZ2UIButton* m_TransferSinaButton;
    
    PVZ2UIButton* m_LoginWechatButton;
    PVZ2UIButton* m_LogoutWechatButton;
    PVZ2UIButton* m_TransferWechatButton;
    
    PVZ2UIButton* m_LoginTencentButton;
    PVZ2UIButton* m_LogoutTencentButton;
    PVZ2UIButton* m_TransferTencentButton;
    
    PVZ2UIButton* m_PolicyButton;
    
    PVZ2UIButton* m_BindWindowButton;
    PVZ2UIButton* m_TransferWindowButton;
};

#endif
