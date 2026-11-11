/*
 * SocialMgr.h
 *
 *  Created on: 2013-7-26
 *      Author: wuxj
 */

#ifndef __SOCIALMGR_H__
#define __SOCIALMGR_H__

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/IAppDriver.h"
#include "core.h"
#include "NetworkData.h"
#include "SocialInfo.h"


enum SocialPlatformType
{
	SPT_None,
	SPT_WeChat,
	SPT_QQMobile,
};




struct ShareInfo
{
	std::string shareTitle ;
	std::string shareDesc;
	std::string shareUrl;
	std::string shareImageUrl;

	void Clear()
	{
		shareTitle = "";
		shareDesc = "";
		shareUrl = "";
		shareImageUrl = "";
	}
};

struct AuthInfo
{
    int32 		userId;
    std::string openId;
    std::string sessionKey;
    std::string userKey;
    std::string sessionId;
    std::string sessionType;
    std::string pf;
    std::string pfkey;

    bool        newUser;

    AuthInfo()
    {
    	userId = -1;
        
        newUser = false;
    }
};

class SocialMgr : public LazySingleton<SocialMgr>
{
	public:
		SocialMgr();
		virtual ~SocialMgr();


	public:
		bool				Init();
		void				Destory();
		bool				LoginSocialPlatform(SocialPlatformType i_platform);
		bool				LogoutSocialPlatform(bool bClean);
#ifdef HOST_ANDROID
	    void 				UpdateAuthInfo(S2C_AuthInfo& i_authInfo);
#endif
	    const AuthInfo& 	GetAuthInfo();

		bool				ShareContentToPlatform(const std::string& i_title, const std::string& i_desc, const std::string& i_url, const std::string& i_imgUrl);

		SocialPlatformType	GetSocialPlatformType();
		SocialInfo*	GetSocialInfo() const;


		ShareInfo			m_cacheShareInfo;
	protected:
		SocialPlatformType	m_socialPlatformType;
		AuthInfo			m_authInfo;
		SocialInfo*			m_socialInfo;
		SocialPlatformType  m_socialType;
	private:
		IAppDriver*			m_appDriver;
};

namespace Message
{
	void SocialLogin(int i_platform);
	void SocialLogout();
}

#endif /* __SOCIALMGR_H__ */
