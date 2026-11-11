//
//  UUIDCreator.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 1/9/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UUIDCreator__
#define __PlantsVersusZombies2__UUIDCreator__

#ifdef HOST_ANDROID
#include "drivers/app/android/JavaInterface.h"
#endif

class UUIDCreator
{
public:
    virtual std::string Create();
};



#if defined(HOST_IPHONEOS)

#elif defined(HOST_ANDROID)
	inline std::string UUIDCreator::Create()
	{
		return Android::Util::GetUUIDString();
	}
#else
	inline std::string UUIDCreator::Create()
	{
		return "No UUIDs for this platform";
	}
#endif



#endif /* defined(__PlantsVersusZombies2__UUIDCreator__) */
