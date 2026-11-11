//
//  HotUIConfig
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/18/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIConfig__
#define __PlantsVersusZombies2__HotUIConfig__

#include <cstddef>
#include <string>

#include "ObjectTypeDescriptor.h"
#include "RtDb.h"
#include "RtObject.h"

class HotUIConfig : public ObjectTypeDescriptor
{
public:
	static const HotUIConfig* GetConfig();
	
public:
	RT_CLASS_DEFINE(HotUIConfig, ObjectTypeDescriptor, RtClass);
    
	HotUIConfig()
	{
		
	}

public:
	std::vector<std::string>	ReloadableMenus;
	
};

#endif
