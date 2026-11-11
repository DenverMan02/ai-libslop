//
//  Connectivity.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/7/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Connectivity__
#define __PlantsVersusZombies2__Connectivity__

class Connectivity
{
public:
	static bool IsConnectedOnWifi();
	static bool IsConnectedOnWWAN();
	static bool IsConnectedOnEthernet();
	static bool IsConnected();
};

#endif /* defined(__PlantsVersusZombies2__Connectivity__) */
