//
//  Ultra.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Ultra__
#define __PlantsVersusZombies2__Ultra__

#include "Singleton.h"

class AdProvider;

class Ultra
{
public:
	static Ultra& PlatformSpecificInstance();
	
	virtual ~Ultra() {}
	Ultra();
	void Initialize(const std::string& i_obfuscatedUserId, Delegate2<int, int>& i_addCoinsToBeAwarded, Delegate0& i_onAdvertisementsClosed);
	
	virtual void Show() = 0;
	
	bool HasAdvertisements();
    int GetNumAdvertisementsAvailable();
    bool SuperSonicHasAdvertisements() const;
	
protected:
	virtual void onInitialize(const std::string& i_obfuscatedUserId) = 0;
	
    bool showSuperSonic();
	bool showAdProvider(AdProvider* i_adProvider);
	
    AdProvider* mSuperSonic;
    bool m_useSuperSonicV6;
	
private:
	std::vector<AdProvider*> mAdProviders;
	Delegate2<int, int> mAddCoinsToBeAwarded;
	Delegate0 mOnAdvertisementsClosed;
};

#endif /* defined(__PlantsVersusZombies2__Ultra__) */
