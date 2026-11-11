//
//  DataPersistorObjectsFactory.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 1/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DataPersistorObjectsFactory__
#define __PlantsVersusZombies2__DataPersistorObjectsFactory__

#include "Singleton.h"
#include "ICloudWrapper.h"
#include "UUIDCreator.h"
#include "NetworkStatusDecider.h"
#include "ServerConfig.h"
#include "DataPersistorFactory.h"
#include "PlayerIdentityService.h"

// Ties all relevant classes together, but has the benefit that the DataPersistorFactory is testable.

class DataPersistorObjectsFactory : public LazySingleton<DataPersistorObjectsFactory>
{
public:
	DataPersistorObjectsFactory();
	
	PlayerIdentityService& GetPlayerIdentityService();
	DataPersistorFactory& GetDataPersistorFactory();

private:
	ICloudWrapper& m_iCloudWrapper;
	UUIDCreator	m_uuidCreator;
	NetworkStatusDecider m_networkStatusDecider;
	ServerConfigGetter m_serverConfigGetter;
	PlayerIdentityService m_playerIdentityService;
	DataPersistorFactory m_dataPersistorFactory;
};

#endif /* defined(__PlantsVersusZombies2__DataPersistorObjectsFactory__) */
