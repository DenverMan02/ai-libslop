//
//  ZombieAnimRig_Gargantuar.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/4/2013.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Gargantuar_h
#define PlantsVersusZombies2_ZombieAnimRig_Gargantuar_h

#include <string>
#include <vector>

#include "RtObject.h"
#include "ZombieAnimRig.h"

enum ZombieAnimRigState_Gargantuar
{
	ZOMBIEANIM_GARGANTUAR_THROWING = ZOMBIEANIM_USERDEFINED,
    ZOMBIEANIM_GARGANTUAR_WEAK,
    ZOMBIEANIM_GARGANTUAR_READY,
};

class ZombieAnimRig_Gargantuar : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Gargantuar, ZombieAnimRig, RtClass);
    
    bool ThrowingLittleZombie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool ThrowFastStandby(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool ThrowingLittleZombieFast(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool WeakTime();
    void SetAmmoLayersVisibility(const std::vector<std::string>& i_layers, bool i_isVisible);
protected:
	virtual const std::string GetHeadParticleName() override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;
};

class ZombieAnimRig_SummerGargantuar : public ZombieAnimRig_Gargantuar
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_SummerGargantuar, ZombieAnimRig_Gargantuar, RtClass);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
};

class ZombieAnimRig_ChildrensdayGargantuar : public ZombieAnimRig_Gargantuar
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ChildrensdayGargantuar, ZombieAnimRig_Gargantuar, RtClass);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
};

#endif
