//
//  ServerConfig.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 3/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ServerConfig__
#define __PlantsVersusZombies2__ServerConfig__
#include "PVZDB.h"

class ServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(ServerConfig, Sexy::RtObject, Sexy::RtClass);
    
	std::string ip;
    std::string fb_app_id;
    std::string fb_permissions;
};

class CDNConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(CDNConfig, Sexy::RtObject, Sexy::RtClass);

	std::string ip;
};

class MetricsServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(MetricsServerConfig, Sexy::RtObject, Sexy::RtClass);
	
	MetricsServerConfig()
	{
		CopernicusURL = "http://statstest.pt.popcap.com.cn";//PVZ2_CHINESE
		Environment = "TEST";
	}

	std::string CopernicusURL;
	std::string Environment;
};

class SwrveServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(SwrveServerConfig, Sexy::RtObject, Sexy::RtClass);

	SwrveServerConfig()
	{
		APIKey = "3loBa749z28yVqmeyb9";
		EventsServer = "http://api.swrve.com.cn/";//PVZ2_CHINESE
		ABServer = "http://abtest.swrve.com.cn/";//PVZ2_CHINESE
	}

	std::string APIKey;
	std::string EventsServer;
	std::string ABServer;
};

//PVZ2_CHINESE_START
class UpdateServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(UpdateServerConfig, Sexy::RtObject, Sexy::RtClass);
    std::string ReleaseURL;
    std::string ShippingURL;
    
    std::string ReleaseFListURL;
    std::string ReleaseRsbURL;
    std::string ShippingFListURL;
    std::string ShippingRsbURL;
    
	std::string GetUpdateURL();
    std::string GetFListURL();
    std::string GetRsbURL();
};
//PVZ2_CHINESE_END

class CustomLevelServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(CustomLevelServerConfig, Sexy::RtObject, Sexy::RtClass);
    std::string ReleaseURL;
    std::string ShippingURL;

	std::string GetURL();
};

class LawnStringServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(LawnStringServerConfig, Sexy::RtObject, Sexy::RtClass);
    std::string ReleaseFileInfoURL;
    std::string ShippingFileInfoURL;
    std::string ReleaseFileURL;
    std::string ShippingFileURL;

	std::string GetFileURL();
	std::string GetFileInfoURL();
};

class ServerConfigGetter
{
public:
	virtual ~ServerConfigGetter() {}
    const std::string& IP();
	const std::string& AppId();
	const std::string& Permissions();
protected:
	virtual ServerConfig* getServerConfig();
};

class MagentoServerConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(MagentoServerConfig, Sexy::RtObject, Sexy::RtClass);

	MagentoServerConfig()
	{
		MagentoBaseProductURL = "http://pvz-shop-almost.pt.popcap.com.cn/index.php/shiny/1.1/product";//PVZ2_CHINESE
		MagentoBaseCategoryURL = "http://pvz-shop-almost.pt.popcap.com.cn/index.php/shiny/1.1/category";//PVZ2_CHINESE
		ReceiptValidationURL = "https://sandbox.itunes.apple.com/verifyReceipt";
        bIsSandBox = true;
	}

	std::string MagentoBaseProductURL;
	std::string MagentoBaseCategoryURL;
	std::string ReceiptValidationURL;
    bool        bIsSandBox;
};
class LogServerConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(LogServerConfig, Sexy::RtObject, Sexy::RtClass);
    LogServerConfig()
    {
    	ReleaseLogServerIp 	= "10.88.230.233";
    	ShippingLogServerIp	= "pvz2log.pvz2ios.popcap.com.cn";
        LogServerPort 		= 4346;
    }
    std::string ReleaseLogServerIp;
    std::string ShippingLogServerIp;
    int         LogServerPort;
};
class TGALogConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TGALogConfig, Sexy::RtObject, Sexy::RtClass);
    TGALogConfig()
    {
    	ReleaseURL 	= "http://106.75.9.138/pvz2logs/tologs";
    	ShippingURL	= "http://106.75.9.138/pvz2logs/tologs";
    }
    std::string ReleaseURL;
    std::string ShippingURL;
};
class PHPServerConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PHPServerConfig, Sexy::RtObject, Sexy::RtClass);
    PHPServerConfig()
    {
    	ReleaseURL 				= "";
    	ShippingURL				= "";
        ReleaseRedPackRankURL   = "";
        ShippingRedPackRankURL  = "";
        ReleasePVPURL			= "";
        ShippingPVPURL			= "";
        ShippingPVPWanDouLabURL = "";
        ReleaseUUIDURL			= "";
        ShippingUUIDURL			= "";
    	HeartBeatInterval		= 0;
    	FriendListUpdateInterval= 0;
    	FriendGiftUpdateInterval= 0;
    }
    std::string ReleaseURL;
    std::string ShippingURL;
    std::string ReleaseRedPackRankURL;
    std::string ShippingRedPackRankURL;
    std::string ReleasePVPURL;
    std::string ShippingPVPURL;
    std::string ShippingPVPWanDouLabURL;
    std::string ReleaseUUIDURL;
    std::string ShippingUUIDURL;
    int32 		HeartBeatInterval;
    int32		FriendListUpdateInterval;
    int32		FriendGiftUpdateInterval;
};
class TimeServerConfig : public Sexy::RtObject
{
    RT_CLASS_DEFINE(TimeServerConfig, Sexy::RtObject, Sexy::RtClass);
    TimeServerConfig()
    {
    	ReleaseURL				= "";
    	ShippingURL				= "";
    }
    std::string ReleaseURL;
    std::string ShippingURL;
};

class ForceUpdateConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(ForceUpdateConfig, Sexy::RtObject, Sexy::RtClass);

	std::string ForceUpdateURL;	
};

class DraperConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(DraperConfig, Sexy::RtObject, Sexy::RtClass);
	
	std::string DraperURL;
};

class RechargeCheckConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(RechargeCheckConfig, Sexy::RtObject, Sexy::RtClass);
	
	std::string ReleaseCheckServerURL;
	std::string ShippingCheckServerURL;
};


#endif /* defined(__PlantsVersusZombies2__ServerConfig__) */
