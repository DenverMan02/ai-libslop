//
//  
//  PlantsVersusZombies2
//
//  Created by Zhong Weiqi on 7/24/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LOAD_PIC_HttpRequest__
#define __PlantsVersusZombies2__LOAD_PIC_HttpRequest__

#include <string>
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/RtDelegate.h"
#include "SexyAppFramework/NetworkServiceManager.h"

class LoadPicHttpRequest : public Sexy::NetworkServiceListener
{
public:
	LoadPicHttpRequest();
	virtual ~LoadPicHttpRequest();
    
	//NetworkServiceListener
	virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );
	virtual void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context );
	virtual void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
    void StartRequest(const std::string& req);
    void LoadPic(const std::string& url,const std::string& uuId);
    
private:
    Sexy::Buffer  m_Buff;
    Sexy::CritSect mHttpRequestCS;
    std::string m_CurUuId;
    std::string  m_ext;
};


#endif /* defined(__PlantsVersusZombies2__PurchaseBroker__) */
