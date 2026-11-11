//
//  ZombieAnimRig_PirateCannon.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_PIRATECANNON_H__
#define __ZOMBIEANIMRIG_PIRATECANNON_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_PirateCannon : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_PirateCannon, ZombieAnimRig, RtClass) {}	
	
	ZombieAnimRig_PirateCannon();
	
private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
};

#endif //__ZOMBIEANIMRIG_PIRATECANNON_H__
