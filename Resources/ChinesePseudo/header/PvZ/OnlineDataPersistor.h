//
//  OnlineDataPersistor.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 1/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OnlineDataPersistor__
#define __PlantsVersusZombies2__OnlineDataPersistor__

#include <string>
#include "IDataPersistor.h"
#include "NetworkRequestor.h"
#include "PvZ2NetworkServiceListener.h"
#include "SexyAppFramework/RtObject.h"


namespace Sexy
{
	class StructuredData;
}
class PlayerIdentityService;
class PlayerInfoDeltaHandler;
class Throttles;

class SaveNetworkServiceListener : public PvZ2NetworkServiceListener
{
public:
	SaveNetworkServiceListener(PlayerInfoDeltaHandler& theHandler);
	SaveNetworkServiceListener(PlayerInfoDeltaHandler& theHandler, Throttles& throttles);
	void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );
	void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context );
	void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
	
private:
	PlayerInfoDeltaHandler& m_playerInfoDeltaHandler;
	Throttles &m_throttles;
};

class LoadNetworkServiceListener : public PvZ2NetworkServiceListener
{
public:
	LoadNetworkServiceListener(IDataPersistor& offlinePersistor);
	LoadNetworkServiceListener(IDataPersistor& offlinePersistor, Throttles& throttler);
	void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );
	void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );
	void ServiceRequestCompleted( const Sexy::Buffer* buffer, const void* context );
	void ServiceRequestFailed( const Sexy::StructuredData* response, const void* context );
	
protected:
	virtual void loadFromBuffer(Sexy::RtSerialBuffer& i_buffer);
	virtual void notifyDataLoaded();

private:
	IDataPersistor& m_offlinePersistor;
	Throttles& m_throttles;
	
};

class OnlineDataPersistor : public IDataPersistor, NetworkRequestor
{
public:
	OnlineDataPersistor(ServerConfigGetter& serverConfigGetter, PlayerIdentityService& playerIdentityService, IDataPersistor& offlineDataPersistor, PlayerInfoDeltaHandler& theHandler);
	void Load();
	void LoadWithNotify();
	bool Save();
	bool isWaitingForResponse();
	bool IsFileExist(){ return false; }
	
protected:
	static std::string dataAsJson(Sexy::RtSerialRtonWriter& i_rtWriter);
	void addArguments(Sexy::StructuredData& request);

private:
	PlayerIdentityService& m_playerIdentityService;
	IDataPersistor& m_offlineDataPersistor;
	
	PlayerInfoDeltaHandler& m_deltaHandler;
protected:
	LoadNetworkServiceListener m_loadListener;
	SaveNetworkServiceListener m_saveListener;
};

namespace Message
{
	void PersistorLoadComplete();
}

#endif /* defined(__PlantsVersusZombies2__OnlineDataPersistor__) */
