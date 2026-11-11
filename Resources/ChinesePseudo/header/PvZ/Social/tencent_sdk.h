/*
 * tencent_sdk.h
 *
 *  Created on: 2014-7-18
 *      Author: lizheng
 */

#ifndef TENCENT_SDK_H_
#define TENCENT_SDK_H_

#include "loginsdkbase.h"

class tencentSDK : public LoginSDKBase
{
public:
	tencentSDK();

    virtual void RequestAuthorize(const Sexy::Delegate1<int>& i_callback);
    
    virtual void OnResponseAuthorize(const char* accessToken, const char* uid, const char* date);
    
    virtual void ClearCache();
protected:
    virtual bool HandleOpenURL( const SexyURL& url );
    
};


#endif /* TENCENT_SDK_H_ */
