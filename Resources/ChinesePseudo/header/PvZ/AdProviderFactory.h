//
//  AdProviderFactory.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 3/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdProviderFactory__
#define __PlantsVersusZombies2__AdProviderFactory__

class AdProvider;

enum AdProviderEnabledOverrideState
{
	NO_OVERRIDE = 0,
	FORCE_DISABLE_AD_PROVIDER = 1,
	FORCE_ENABLE_AD_PROVIDER = 2,
};

class AdProviderFactory
{
public:
	virtual ~AdProviderFactory() {}
	AdProviderFactory();
	
	AdProvider* InitializeAndGet(bool i_enableProvider);
	bool IsEnabled();
	
	bool EnabledValueFromConfig;
	AdProviderEnabledOverrideState EnabledOverrideValue;
	bool UsingDemoCampaigns;
protected:
	virtual AdProvider& PlatformSpecificInstance() = 0;
	virtual const std::string getEnabledOverrideKey() = 0;
	virtual const std::string getUseDemoCampaignsKey() = 0;
};

#endif /* defined(__PlantsVersusZombies2__AdProviderFactory__) */
