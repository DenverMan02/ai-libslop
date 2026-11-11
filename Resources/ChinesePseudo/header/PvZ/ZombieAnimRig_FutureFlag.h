//

//  ZombieAnimRig_FutureFlag.h

//  PlantsVersusZombies2

//

//  Created by Austin McGee on 1/23/14.

//  Copyright (c) 2014 PopCap Games. All rights reserved.

//



#ifndef __PlantsVersusZombies2__ZombieAnimRig_FutureFlag__

#define __PlantsVersusZombies2__ZombieAnimRig_FutureFlag__



#include "ZombieAnimRig_Basic.h"



class ZombieAnimRig_FutureFlag : public ZombieAnimRig_Basic

{

public:

	RT_CLASS_DEFINE(ZombieAnimRig_FutureFlag, ZombieAnimRig_Basic, RtClass) {}



private:

	virtual const std::vector<std::string>& getHeadLayerNames() override;

	virtual const std::vector<std::string>& getArmLayerNames() override;

	virtual const std::vector<std::string>& getArmReplacementPairNames() override;

	virtual const std::vector<std::string>& getFlagHandLayerNames() override;

	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;

	virtual const std::vector<std::string>& getConeLayerNames() override;

	virtual const std::vector<std::string>& getBucketLayerNames() override;

};



#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_FutureFlag__) */

