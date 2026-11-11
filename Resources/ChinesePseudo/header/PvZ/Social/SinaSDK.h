/*
 *  SinaSDK.h
 *
 *  Created on: 2014-7-17
 *      Author: lizheng
 */

#ifndef SINA_SDK_H_
#define SINA_SDK_H_

#include "LoginSDKBase.h"

class SinaSDK : public LoginSDKBase
{
public:
	SinaSDK();

    virtual void RequestAuthorize(const Sexy::Delegate1<int>& i_callback);
    
    virtual void OnResponseAuthorize(const char* accessToken, const char* uid, const char* date);
    
    virtual void ClearCache();
    
protected:
    
    virtual bool HandleOpenURL( const SexyURL& url );
    
};


#endif /* SINA_SDK_H_ */
