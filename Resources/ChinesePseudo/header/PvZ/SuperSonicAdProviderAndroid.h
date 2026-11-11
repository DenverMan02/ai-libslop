//
//  SuperSonicAdProviderAndroid.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 5/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SuperSonicAdProviderAndroid__
#define __PlantsVersusZombies2__SuperSonicAdProviderAndroid__

#include "AdProvider.h"
#include "Singleton.h"

class SuperSonicAdProviderAndroid : public AdProvider, public LazySingleton<SuperSonicAdProviderAndroid>
{
public:
	SuperSonicAdProviderAndroid();
	~SuperSonicAdProviderAndroid();
	void Initialize(const std::string& i_obfuscatedUserId);
protected:
	void doShowAdvertisements();
private:
	void onAppResumeFocus();
	bool mSuperSonicIsShowing;
};

#endif /* defined(__PlantsVersusZombies2__SuperSonicAdProviderAndroid__) */
