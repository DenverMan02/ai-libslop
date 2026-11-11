//
//  UltraAndroid.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UltraAndroid__
#define __PlantsVersusZombies2__UltraAndroid__

#include "Ultra.h"
#include "Singleton.h"

class UltraAndroid : public Ultra, public LazySingleton<UltraAndroid>
{
public:
	void Show() override;
protected:
	void onInitialize(const std::string& i_obfuscatedUserId) override;
};

#endif /* defined(__PlantsVersusZombies2__UltraAndroid__) */
