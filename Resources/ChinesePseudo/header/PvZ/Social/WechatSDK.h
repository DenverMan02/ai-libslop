
#ifndef WECHAT_SDK_H_
#define WECHAT_SDK_H_

#include "LoginSDKBase.h"

class WechatSDK : public LoginSDKBase
{
public:
	WechatSDK();
    
    void DoSDKShare(const std::string& i_url, bool toTimeLine);
    
    bool IsSDKInstalled();

    virtual void RequestAuthorize(const Sexy::Delegate1<int>& i_callback);
    
    virtual void OnResponseAuthorize(const char* accessToken, const char* uid, const char* date);
    
    virtual void ClearCache();
    
protected:
    
    virtual bool HandleOpenURL( const SexyURL& url );
    
};


#endif