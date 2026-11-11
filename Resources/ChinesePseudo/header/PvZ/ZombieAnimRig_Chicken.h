//
//  ZombieAnimRig_Chicken.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_CHICKEN_H__
#define __ZOMBIEANIMRIG_CHICKEN_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Chicken : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Chicken, ZombieAnimRig, RtClass);

    virtual AnimHandle PlayDie() override;

	void SetColor(const Color& i_color);
	void SetBoneLegVisibility(bool i_visible);
	void SetFriedChickenDeath(bool i_enable);

protected:
	virtual const std::string getWalkAnimationName() override;

private:
	Color m_color;
	bool m_friedChickenDeath = false;
};

class ZombieAnimRig_Weasel : public ZombieAnimRig_Chicken
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Weasel, ZombieAnimRig_Chicken, RtClass);
protected:
    virtual const std::string getWalkAnimationName() override;
};

#endif
