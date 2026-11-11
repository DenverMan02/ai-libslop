//
//  DataPersistorFactory.h
//  PlantsVersusZombies2
//
//  Created by PopCap User on 1/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DataPersistorFactory__
#define __PlantsVersusZombies2__DataPersistorFactory__

#include "PlayerInfoDeltaHandler.h"
#include "OnlineDataPersistor.h"

class NetworkStatusDecider;
class PlayerIdentityService;
class PlayerInfoDeltaHandler;

class DataPersistorFactory
{
public:
	DataPersistorFactory(const NetworkStatusDecider& networkStatusDecider, ServerConfigGetter& serverConfigGetter, PlayerIdentityService& playerIdentityService);
	virtual ~DataPersistorFactory() {}
	IDataPersistor& GetPersistor();
	IDataPersistor& GetOfflinePersistor();
	OnlineDataPersistor& GetOnlinePersistor();
	virtual PlayerInfoDeltaHandler& GetDeltaHandler();
	
protected:
	virtual OfflineDataPersistor& getOffline();
	virtual OnlineDataPersistor& getOnline();
private:
	OfflineDataPersistor m_offlineDataPersistor;
	PlayerInfoDeltaHandler m_playerInfoDeltaHandler;
	OnlineDataPersistor m_onlineDataPersistor;
	ServerConfigGetter& m_serverConfigGetter;
	const NetworkStatusDecider& m_networkStatusDecider;
};

#endif /* defined(__PlantsVersusZombies2__DataPersistorFactory__) */
