//
//  PublicDefine.h
//  WGPlatform
//
//  Created by fly chen on 2/25/13.
//  Copyright (c) 2013 tencent.com. All rights reserved.
//

#ifndef WGPlatform_PublicDefine_h
#define WGPlatform_PublicDefine_h

typedef enum _ePlatform
{
    ePlatform_None,
    ePlatform_Weixin,          
    ePlatform_QQ,
    ePlatform_WTLogin,
    ePlatform_QQHall
}ePlatform;

typedef enum _eFlag
{
    eFlag_Succ              = 0x0,
    eFlag_QQ_NoAcessToken   = 0x1000,     //QQ&QZone login fail and can't get accesstoken
    eFlag_QQ_UserCancel     = 0x1001,     //QQ&QZone user has cancelled login process (tencentDidNotLogin)
    eFlag_QQ_LoginFail      = 0x1002,     //QQ&QZone login fail (tencentDidNotLogin)
    eFlag_QQ_NetworkErr     = 0x1003,     //QQ&QZone networkErr
    eFlag_QQ_NotInstall     = 0x1004,     //QQ is not install
    eFlag_QQ_NotSupportApi  = 0x1005,     //QQ don't support open api

    eFlag_WX_NotInstall     = 0x2000,     //Weixin is not installed
    eFlag_WX_NotSupportApi  = 0x2001,     //Weixin don't support api
    eFlag_WX_UserCancel     = 0x2002,     //Weixin user has cancelled
    eFlag_WX_UserDeny       = 0x2003,     //Weixin User has deny
    eFlag_WX_LoginFail      = 0x2004,     //Weixin login fail
    eFlag_WX_RefreshTokenSucc = 0x2005, // Weixin 刷新票据成功
    eFlag_WX_RefreshTokenFail = 0x2006, // Weixin 刷新票据失败
    eFlag_Error				= 0xFFFF
}eFlag;


typedef enum _eShare
{
    eShare_Succ              = 0x0,
    /*
     EQQAPISENDSUCESS = 0,
     EQQAPIQQNOTINSTALLED = 1,
     EQQAPIQQNOTSUPPORTAPI = 2,
     EQQAPIMESSAGETYPEINVALID = 3,
     EQQAPIMESSAGECONTENTNULL = 4,
     EQQAPIMESSAGECONTENTINVALID = 5,
     EQQAPIAPPNOTREGISTED = 6,
     EQQAPISENDFAILD = -1
     */
    /*
     WXSuccess           = 0,
     WXErrCodeCommon     = -1,
     WXErrCodeUserCancel = -2,
     WXErrCodeSentFail   = -3,
     WXErrCodeAuthDeny   = -4,
     WXErrCodeUnsupport  = -5,
     */
}eShare;

typedef enum _eTokenType
{
    eToken_QQ_Access = 1,
    eToken_QQ_Pay,
    eToken_WX_Access,       //只为兼容 目前不用
    eToken_WX_Code,
    eToken_WX_Refresh,
}eTokenType;


typedef enum _ePermission
{
    eOPEN_NONE                              = 0,
    eOPEN_PERMISSION_GET_USER_INFO          = 0x2,
    eOPEN_PERMISSION_GET_SIMPLE_USER_INFO   = 0x4,
    eOPEN_PERMISSION_ADD_ALBUM              = 0x8, 
    eOPEN_PERMISSION_ADD_IDOL               = 0x10,
    eOPEN_PERMISSION_ADD_ONE_BLOG           = 0x20,
    eOPEN_PERMISSION_ADD_PIC_T              = 0x40,
    eOPEN_PERMISSION_ADD_SHARE              = 0x80,
    eOPEN_PERMISSION_ADD_TOPIC              = 0x100,
    eOPEN_PERMISSION_CHECK_PAGE_FANS        = 0x200,
    eOPEN_PERMISSION_DEL_IDOL               = 0x400,
    eOPEN_PERMISSION_DEL_T                  = 0x800,
    eOPEN_PERMISSION_GET_FANSLIST           = 0x1000,
    eOPEN_PERMISSION_GET_IDOLLIST           = 0x2000,
    eOPEN_PERMISSION_GET_INFO               = 0x4000,
    eOPEN_PERMISSION_GET_OTHER_INFO         = 0x8000,
    eOPEN_PERMISSION_GET_REPOST_LIST        = 0x10000,
    eOPEN_PERMISSION_LIST_ALBUM             = 0x20000,
    eOPEN_PERMISSION_UPLOAD_PIC             = 0x40000,
    eOPEN_PERMISSION_GET_VIP_INFO           = 0x80000,
    eOPEN_PERMISSION_GET_VIP_RICH_INFO          = 0x100000,
    eOPEN_PERMISSION_GET_INTIMATE_FRIENDS_WEIBO = 0x200000,
    eOPEN_PERMISSION_MATCH_NICK_TIPS_WEIBO      = 0x400000,
    eOPEN_PERMISSION_GET_APP_FRIENDS            = 0x800000,
    eOPEN_ALL                                   = 0xffffff,
}ePermission;

#endif
