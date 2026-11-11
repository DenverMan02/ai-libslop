//
//  ZombieAnimRig_Pumpkin.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/10/23.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_Pumpkin__
#define __PlantsVersusZombies2__ZombieAnimRig_Pumpkin__

#include <stdio.h>

#include "PopAnimRig.h"
#include "RtObject.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Imp.h"

class ZombieAnimRig_Pumpkin : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Pumpkin, ZombieAnimRig, RtClass) {}
    
    virtual void updateHeadLayer(int i_layerIndex, const std::string& i_color);
    
    virtual void dropHead(const std::string& i_color);
    
protected:
    
};

class ZombieAnimRig_PumpkinImp : public ZombieAnimRig_Imp
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_PumpkinImp, ZombieAnimRig_Imp, RtClass) {}
    
    virtual void updateHeadLayer(int i_layerIndex, const std::string& i_color);
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_Pumpkin__) */
