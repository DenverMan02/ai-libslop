/*
 *  LoginSDKBase.h
 *
 *  Created on: 2014-7-22
 *      Author: lizheng
 */

#ifndef LOGIN_SDK_BASE_H_
#define LOGIN_SDK_BASE_H_

#include "core.h"
#include "GameNotify.h"
#include "RtDb.h"
#include "SexyURL.h"

class LoginSDKBase :public Sexy::RtObject
{
public:
    LoginSDKBase(){}
    
    virtual bool HandleOpenURLFunc(const SexyURL& url);

    virtual void RequestAuthorize(const Sexy::Delegate1<int>& i_callBack);
    
    virtual void OnResponseAuthorize(const char* accessToken, const char* uid, const char* date) = 0;
    
    //virtual bool CanConnectDirect();
    
    virtual void ClearCache() = 0;
    
protected:
    void ConnectOpenURLFunc();
    
    void DisconnectOpenURLFunc();
    
    virtual bool HandleOpenURL( const SexyURL& url ) = 0;

protected:
    
    std::string m_accessToken;
    std::string m_userID;
    std::string m_expireDate;
    
    Sexy::Delegate1<int> m_authorizeCallback;
    
};

#endif