//
//  EASquaredCore.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredCore__
#define __PlantsVersusZombies2__EASquaredCore__

namespace EASquaredCore {
	
	bool inSelectedMonetizationGroup(int transactionCount, const std::string& monetizationGroup);
	bool playerHasTooManyCoins(int playerCoins, int maximumCoins);
	bool playerInstalledRecently(int daysSinceInstall, int minimumDaysSinceInstall);
}


#endif /* defined(__PlantsVersusZombies2__EASquaredCore__) */
