/*
 *  LoginSDKMgr.cpp
 *
 *  Created on: 2014-7-22
 *      Author: lizheng
 */

#ifndef LOGIN_SDK_MGR_H_
#define LOGIN_SDK_MGR_H_

#include "core.h"
#include "GameNotify.h"
#include "RtDb.h"
#include "SexyURL.h"

enum LoginSDKType
{
    SDK_NONE = 0,
    SDK_SINA,
    SDK_TENCENT,
    SDK_WECHAT,
    SDK_NUMBER,
};

class SinaSDK;
class WechatSDK;
//class tencentSDK;

class LoginSDKMgr : public LazySingleton<LoginSDKMgr>
{
public:
	LoginSDKMgr();
    virtual ~LoginSDKMgr();
    
    void SDKLogin(int sdkType, const Sexy::Delegate1<int>& i_callBack);
    
    void DoSDKShare(int sdkType, const std::string& i_url, bool toTimeLine);
    
    bool IsSDKInstalled(int sdkType);
    
    
    void setSinaSDKUUID(const std::string& value)  { m_sinaSDKUUID    = value;}
    void setWechatSDKUUID(const std::string& value){ m_wechatSDKUUID  = value;}
    void setTencentUUID(const std::string& value)  { m_tencentSDKUUID = value;}
    
    std::string getSinaSDKUUID()    const { return m_sinaSDKUUID;     }
    std::string getWechatSDKUUID()  const { return m_wechatSDKUUID;   }
    std::string getTencentSDKUUID() const { return m_tencentSDKUUID;  }
    
    void setIsReceivedBindingData(bool flag){m_receivedBindingData = flag;}
    bool getIsReceivedBindingData(){return m_receivedBindingData;}
    
    bool isAlreadyBoundSinaSDK()    const { return m_sinaSDKUUID    != ""; }
    bool isAlreadyBoundWechatSDK()  const { return m_wechatSDKUUID  != ""; }
    bool isAlreadyBoundTencentSDK() const { return m_tencentSDKUUID != ""; }
    
private:
    SinaSDK*                m_sinaSDK;
    std::string             m_sinaSDKUUID;
    
    WechatSDK*              m_wechatSDK;
    std::string             m_wechatSDKUUID;
    
//    tencentSDK*             m_tencentSDK;
    std::string             m_tencentSDKUUID;
    
    bool                    m_receivedBindingData;
};



#endif /* LOGIN_SDK_MGR_H_ */
