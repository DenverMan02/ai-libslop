//
//  MergePlayerInfosOnServer.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen, Matt Westhoff on 3/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MergePlayerInfosOnServer__
#define __PlantsVersusZombies2__MergePlayerInfosOnServer__

#include "NetworkRequestor.h"
#include "PvZ2NetworkServiceListener.h"

class MessageRouter;
class GameEventNotification;
class PlayerIdentityService;

class MergeNetworkServiceListener : public PvZ2NetworkServiceListener
{
public:
	MergeNetworkServiceListener(MessageRouter& i_messageRouter);
	void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );
	void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context );
	void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
	
private:
	MessageRouter& m_messageRouter;
};

class MergePlayerInfosOnServer : public NetworkRequestor
{
public:
	MergePlayerInfosOnServer(MessageRouter& i_messageRouter, ServerConfigGetter& serverConfigGetter);
	virtual ~MergePlayerInfosOnServer(){}
	
protected:
	void onBindAskForMerge(const Sexy::StructuredData* i_response);
	bool isWaitingForResponse();
	void addArguments(Sexy::StructuredData& request);
	
	MergeNetworkServiceListener m_serviceListener;
private:
	std::string m_boundPcpId;
	std::string m_requestedPcpId;
};

#endif /* defined(__PlantsVersusZombies2__MergePlayerInfosOnServer__) */
