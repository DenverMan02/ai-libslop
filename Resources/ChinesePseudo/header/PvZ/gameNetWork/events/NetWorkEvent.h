/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 14
 ------------------------------------------------------------------------------------------------------------*/

#ifndef NETWORK_EVENT_H_
#define NETWORK_EVENT_H_

#include "ServerConfig.h"
#include "Common.h"
#include "LawnApp.h"

#include <string>

#ifndef RELEASEFINAL

#define RELEASE_SERVER_CONFIG         0
#define SHIPPING_SERVER_CONFIG        1
#define TONY_SERVER_CONFIG            2
#define ZHUWEN_SERVER_CONFIG          3
#define SHENJUN_SERVER_CONFIG         4
#define GUSHI_SERVER_CONFIG           5

#define SERVER_CONFIG                 RELEASE_SERVER_CONFIG

#endif

class  NetWorkEvent
{
public:
    NetWorkEvent();
    virtual ~NetWorkEvent();
    virtual void Update(long ms);
    virtual void Init();
    bool   IsTimeOut(long ms);
    long m_TimeGap;
    long m_nowGap;
};
typedef struct _NetworkEventConfig
{
    std::string URL;
    std::string ExtraURL;
    std::string PVPURL;
    std::string UUIDURL;
    int FriendTime;
    int HeatBeatTime;
    int GiftTime;
    static std::string m_stageURL;
    _NetworkEventConfig()
    {
        PHPServerConfig *serverConfig = gLawnApp->GetServerPHPConfig();
#ifdef RELEASEFINAL
        URL        		= serverConfig->ShippingURL;
        ExtraURL        = serverConfig->ShippingRedPackRankURL;        
        if(gLawnApp->GetPlatform() == PLATFORM_WANDOULABS_HD || gLawnApp->GetPlatform() == PLATFORM_WANDOULABS)
        {
        	PVPURL     		= serverConfig->ShippingPVPWanDouLabURL;
        }
        else
        {
        	PVPURL     		= serverConfig->ShippingPVPURL;
        }        
        UUIDURL         = serverConfig->ShippingUUIDURL;
        HeatBeatTime 	= serverConfig->HeartBeatInterval;
        FriendTime   	= serverConfig->FriendListUpdateInterval;
        GiftTime     	= serverConfig->FriendGiftUpdateInterval;
#else
#ifdef NDEBUG
        URL        		= serverConfig->ReleaseURL;
        ExtraURL        = serverConfig->ReleaseRedPackRankURL;
        PVPURL     		= serverConfig->ReleasePVPURL;
        UUIDURL         = serverConfig->ReleaseUUIDURL;
        HeatBeatTime 	= serverConfig->HeartBeatInterval;
        FriendTime   	= serverConfig->FriendListUpdateInterval;
        GiftTime     	= serverConfig->FriendGiftUpdateInterval;
#else
#if (SERVER_CONFIG == SHIPPING_SERVER_CONFIG)
        URL        		= serverConfig->ShippingURL;
        ExtraURL        = serverConfig->ShippingRedPackRankURL;
        PVPURL     		= serverConfig->ShippingPVPURL;
        UUIDURL         = serverConfig->ShippingUUIDURL;
        HeatBeatTime 	= serverConfig->HeartBeatInterval;
        FriendTime   	= serverConfig->FriendListUpdateInterval;
        GiftTime     	= serverConfig->FriendGiftUpdateInterval;
#elif (SERVER_CONFIG == TONY_SERVER_CONFIG)
        URL          	= "http://dt-13638.eamobile.ad.ea.com/pvz2ios/index.php?";
        PVPURL          = "http://dt-13638.eamobile.ad.ea.com/pvz2pvp/index.php?";
        UUIDURL         = "http://uuid.pvz2ios.popcap.com.cn:8080/gate";
        HeatBeatTime 	= 60;
#elif (SERVER_CONFIG == GUSHI_SERVER_CONFIG)
        URL          	= "http://192.168.140.130/pvz2single/index.php?";
        PVPURL          = "http://dt-13638.eamobile.ad.ea.com/pvz2pvp/index.php?";
        UUIDURL         = "http://uuid.pvz2ios.popcap.com.cn:8080/gate";

#elif (SERVER_CONFIG == SHENJUN_SERVER_CONFIG)
#ifdef HOST_IPHONEOS
        URL          	= "http://sha-vjun-001.internal.popcap.com/pvz2ios/index.php?";
        PVPURL          = "http://sha-vjun-001.internal.popcap.com/pvz2pvp/index.php?";
        UUIDURL         = "http://uuid.pvz2ios.popcap.com.cn:8080/gate";
#endif
        
#ifdef HOST_ANDROID
        URL          	= "http://sha-vjun-001.internal.popcap.com/pvz2single/index.php?";
        PVPURL          = "http://sha-vjun-001.internal.popcap.com/pvz2pvp/index.php?";
        UUIDURL         = "http://uuid.pvz2android.popcap.com.cn:8080/gate";
#endif
        HeatBeatTime 	= 60;
#else//RELEASE_SERVER_CONFIG
        URL        		= serverConfig->ReleaseURL;
        ExtraURL        = serverConfig->ReleaseRedPackRankURL;
        PVPURL     		= serverConfig->ReleasePVPURL;
        UUIDURL         = serverConfig->ReleaseUUIDURL;
        HeatBeatTime 	= serverConfig->HeartBeatInterval;
        FriendTime   	= serverConfig->FriendListUpdateInterval;
        GiftTime     	= serverConfig->FriendGiftUpdateInterval;
#endif
    #endif
        
#endif
        
        URL        		= m_stageURL.empty() ? URL : m_stageURL;
    }
    
    static void SetStageURL(const std::string& i_url) { m_stageURL = i_url; }
    static const std::string& GetStageURL() { return m_stageURL; }
    static bool HasStageURL() { return !m_stageURL.empty(); }

}NetworkEventConfig;
#endif

