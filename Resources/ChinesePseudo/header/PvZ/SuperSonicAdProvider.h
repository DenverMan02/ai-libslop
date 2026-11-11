//
//  SuperSonicAdProvider.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 5/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SuperSonicAdProvider__
#define __PlantsVersusZombies2__SuperSonicAdProvider__

#define SUPERSONIC_ENABLED_OVERRIDE_KEY "SuperSonicEnabledOverride"
#define SUPERSONIC_USE_DEMO_CAMPAIGNS_KEY "SuperSonicUseDemoCampaigns"

#include "AdProviderFactory.h"
#include "Singleton.h"

class SuperSonicAdProvider : public AdProviderFactory, public LazySingleton<SuperSonicAdProvider>
{
protected:
	AdProvider& PlatformSpecificInstance() override;
	const std::string getEnabledOverrideKey() override;
	const std::string getUseDemoCampaignsKey() override;
};

#endif /* defined(__PlantsVersusZombies2__SuperSonicAdProvider__) */
