//
//  Network.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 9/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Network_h
#define PlantsVersusZombies2_Network_h

inline bool IsNetworkUp()
{
	return gSexyAppBase->mHttpDriver->GetNetworkStatus() != IHttpDriver::NET_NOT_REACHABLE;
}

#endif
