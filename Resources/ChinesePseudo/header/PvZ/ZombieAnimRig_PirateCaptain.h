//
//  ZombieAnimRig_PirateCaptain.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_PIRATECAPTAIN_H__
#define __ZOMBIEANIMRIG_PIRATECAPTAIN_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_PirateCaptain : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_PirateCaptain, ZombieAnimRig, RtClass);
	
    bool StartBigCasting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
	virtual void HideHead() override;
	void ShowParrotLayers(bool i_isShown);
    
protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif //__ZOMBIEANIMRIG_PIRATECAPTAIN_H__
