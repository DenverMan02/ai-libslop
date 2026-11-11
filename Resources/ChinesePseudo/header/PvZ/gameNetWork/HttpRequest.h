//
//  
//  PlantsVersusZombies2
//
//  Created by Zhong Weiqi on 7/24/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HttpRequest__
#define __PlantsVersusZombies2__HttpRequest__

#include <string>
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/RtDelegate.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include <map>

typedef std::map<std::string,std::string> ParaMap;
typedef ParaMap::iterator      ParaIter;
enum ErroId
{
    ERRO_NETWORK_CONNECT_FAILD         = -1,
    ERRO_SERVER_MSGID_NOT_EXIT         = -2,
    ERRO_SERVER_MSGRET_NOT_EXIT        = -3,
    ERRO_SERVER_MSG_JSON_PARSER_FAILDE = -4,
};

class HttpRequest : public Sexy::NetworkServiceListener
{
public:
	HttpRequest();
	virtual ~HttpRequest();
    
	//NetworkServiceListener
	virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) {}
	virtual void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context ) {}
	virtual void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );

    void StartRequest(std::string& req,std::string& content, const std::string& strUrl = EmptyUrl);
private:

    Sexy::Buffer  m_Buff;
    Sexy::CritSect mHttpRequestCS;
    std::string m_Url;
    static const std::string EmptyUrl;

};


#endif /* defined(__PlantsVersusZombies2__PurchaseBroker__) */
