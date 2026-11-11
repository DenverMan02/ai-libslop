//
//  ICloudWrapperFactory.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen, Matt McDonald on 4/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ICloudWrapperFactory_h
#define PlantsVersusZombies2_ICloudWrapperFactory_h

#include "ICloudWrapper.h"

class ICloudWrapperFactory
{
public:
	static ICloudWrapper& CreateInstance() {
		{
#ifdef HOST_IPHONEOS
			static ICloudWrapperImpl iCloudWrapperImpl;
			return iCloudWrapperImpl;
#else
			static ICloudWrapper iCloudWrapper;
			return iCloudWrapper;
#endif // HOST_IPHONEOS
		}

	}
};

#endif
