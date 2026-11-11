//
//  ZombieAnimRig_MonkBlade.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-1-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_MonkBlade__
#define __PlantsVersusZombies2__ZombieAnimRig_MonkBlade__


#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_MonkBlade : public ZombieAnimRig
{
public:
    
    RT_CLASS_DEFINE(ZombieAnimRig_MonkBlade, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_MonkBlade();
    
protected:	
    
    virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::string getEatAnimationName() override;
    bool m_bCrazy = false;
};


#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_MonkBlade__) */
