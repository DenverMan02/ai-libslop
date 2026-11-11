//
//  ZombieAnimRig_MonkBlade.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-1-2.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_MonkNunchaku__
#define __PlantsVersusZombies2__ZombieAnimRig_MonkNunchaku__


#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Hammer.h"


class ZombieAnimRig_MonkNunchaku : public ZombieAnimRig_Hammer
{
public:
    
    RT_CLASS_DEFINE(ZombieAnimRig_MonkNunchaku, ZombieAnimRig_Hammer, RtClass);
    
    ZombieAnimRig_MonkNunchaku();
    
    virtual void PlayRest() override;
    virtual void PlayBlock() override;
    
    void PlayBlockReturn(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    
protected:	
    
    virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};


#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_MonkBlade__) */
