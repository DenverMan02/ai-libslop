//
//   RvsChecker.h
//  PlantsVersusZombies2
//
//  Created by Zhong Weiqi on 6/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RvsChecher__
#define __PlantsVersusZombies2__RvsChecher__

#include <string>
#include "SexyAppFramework/IPurchaseDriver.h"
#include "SexyAppFramework/RtDelegate.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include "PVZ2UIDialog.h"


enum RvsState
{
	RvsState_None,
	RvsState_Waiting,
	RvsState_Sucess,
    RvsState_Failed
};

class RvsChecker : public Sexy::NetworkServiceListener
{
public:
    
	RvsChecker();
	virtual ~RvsChecker();
    
	//NetworkServiceListener
	virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) {}
	virtual void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context ) {}
	virtual void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
    int GetRvsStat(){ return m_RvsStat;};
    void StartCheckRvsStat();
    
private:
    int  m_RvsStat;
    
};

namespace Message
{
	void PurchaseDialogClosed();
}

#endif /* defined(__PlantsVersusZombies2__PurchaseBroker__) */
