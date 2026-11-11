//
//  ZombieAnimRig_CowboyBasic.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_COWBOYBASIC_H__
#define __ZOMBIEANIMRIG_COWBOYBASIC_H__

#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_CowboyBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_CowboyBasic, ZombieAnimRig_Basic, RtClass) {}
	
	ZombieAnimRig_CowboyBasic();
	
	void SetDancing(bool i_dancing);
	virtual void SetLayerVisibilityForCurrentState() override;

private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
	virtual const std::string getWalkAnimationName() override;

	virtual void onAnimStopped() override;
	virtual void onAnimSequenceContinued() override;
	
	bool m_dancing;
};

#endif
