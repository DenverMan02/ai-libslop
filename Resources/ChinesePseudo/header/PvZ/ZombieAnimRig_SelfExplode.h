//
//  ZombieAnimRig_SelfExplode.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-11-15.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_SelfExplode__
#define __PlantsVersusZombies2__ZombieAnimRig_SelfExplode__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_SelfExplode : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_SelfExplode, ZombieAnimRig, RtClass) {}
    
	void SetTorchLayers(const bool i_visible);
    
    bool PlayBigBang(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    virtual const std::string GetArmParticleName() override;
    
    //virtual void  onAnimStopped();
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_SelfExplorer__) */
