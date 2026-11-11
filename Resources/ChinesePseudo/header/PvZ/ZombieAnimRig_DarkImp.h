//
//  ZombieAnimRig_DarkImp.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 9/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_DARKIMP_H__
#define __ZOMBIEANIMRIG_DARKIMP_H__

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig_Imp.h"

class ZombieAnimRig_DarkImp : public ZombieAnimRig_Imp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_DarkImp, ZombieAnimRig_Imp, RtClass) {}
	
protected:
	virtual const std::vector<std::string>& getConeLayerNames();
	virtual const std::vector<std::string>& getBucketLayerNames();
	virtual const std::vector<std::string>& getCrownLayerNames();
};

#endif
