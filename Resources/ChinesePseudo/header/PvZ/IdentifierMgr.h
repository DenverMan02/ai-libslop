//
//  IdentifierMgr.hpp
//  PlantsVersusZombies2
//
//  Created by chenjd on 16/3/22.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef IdentifierMgr_hpp
#define IdentifierMgr_hpp

#include "Singleton.h"
#include "TimeMgr.h"

namespace Message
{
    void UUIDDialogClosed();
}

class IdentifierMgr : public LazySingleton<IdentifierMgr>
{
public:
    
    IdentifierMgr();
    virtual ~IdentifierMgr();
    
    bool    EnableBind();

    void    Init();
    
    void    Update();
    
    void    TryIdentifierInit();
    void    TryIdentifierCheck();
    
    void    TryBind();
    
    bool    IsRequestFinished();
    bool    IsRequestInit();
    bool    IsRequestCheck();
    bool    IsRequestTimeOut();
    
    std::string GetUUID();
    std::string GetAccessToken();
    bool        IsBind();
    bool 		NeedUUIDLogin();
    void		SetUUIDLogin(bool login);
    
    void    ResetKeychain();
    
    bool    haveBindTip();
    void    setBindTip();
    
    std::string GenerateLocalUUID();
    
    /*
    void    ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context) override;
    void    ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context) override;
    void    ServiceRequestCompleted(ImageLib::Image*&, const void* i_context) override;
    void    ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context) override;
    */
    
protected:
    
    enum IdentifierAPICode
    {
        IdentifierAPICode_Init           = 10001,
        IdentifierAPICode_Login          = 10002,
        IdentifierAPICode_LogOut         = 10003
    };
    
    enum IdentifierMgrState
    {
        IdentifierMgrState_Init = 0,
        IdentifierMgrState_RequestCheck,
        IdentifierMgrState_RequestInit,
        IdentifierMgrState_RequestInitFinished,
        
        IdentifierMgrState_Error,
        IdentifierMgrState_TimeOut,
        IdentifierMgrState_Finished
    };
    
    
private:
    
    //void    TryInitRequest();
    //void    TryLoginRequest();
    
    bool    VerifyMD5();

    void    SaveToKeychain();
    
    void    onNotifyUUIDInit(bool i_success, const std::string& uuid, const std::string& access_token);
    void    onNotifyUUIDCheck(int result, const std::string& access_token);
    void    onNotifyUUIDBind(bool i_success);
    void    onNotifyUUIDLogin(bool i_success);
    
    std::string ReadFromSaveFile(const std::string& path);
    void        SaveToLoaclFile(const std::string& path, const std::string& content);
    
    //dialog
    void onBindTipCancel();
    void onBindTipOK();
    
    //double dialog
    void onBindDoubleTipCancel();
    void onBindDoubleTipOK();
    
    void onRestartApp();
    
    void onBindDialogClosed();

private:
    
    std::string        m_uuid;
    std::string        m_access_token;
    std::string        m_verify;
    
    bool               m_bind;
    
    bool               m_initBind;
    
    IdentifierMgrState m_state;
    
    pvztime_t          m_TimeOut;

    std::string 	   m_StorageHome;
    std::string 	   m_StorageData;
    
    std::string 	   m_packageName;
    
    bool               m_BindTip;
    std::string		   m_needUUIDLogin;// zhousen "yes" : we should run V220 login. "no" : we should run V202 login
};

#endif /* IdentifierMgr_hpp */
