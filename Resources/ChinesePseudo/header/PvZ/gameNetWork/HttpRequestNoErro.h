//
//  
//  PlantsVersusZombies2
//
//  Created by Zhong Weiqi on 7/24/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HttpRequest_NOERROR__
#define __PlantsVersusZombies2__HttpRequest_NOERROR__

#include <string>
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/RtDelegate.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include <map>

typedef std::map<std::string,std::string> ParaMap;
typedef ParaMap::iterator      ParaIter;


class HttpRequestNoError : public Sexy::NetworkServiceListener
{
public:
	HttpRequestNoError();
	virtual ~HttpRequestNoError();
    
	//NetworkServiceListener
	virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) {}
	virtual void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context ) {}
	virtual void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
    void StartRequest(std::string& req,std::string& content);
    void Init(int plantFormId);
private:

    Sexy::Buffer  m_Buff;
    Sexy::CritSect mHttpRequestCS;
    std::string m_Url;
    
};


#endif /* defined(__PlantsVersusZombies2__PurchaseBroker__) */
