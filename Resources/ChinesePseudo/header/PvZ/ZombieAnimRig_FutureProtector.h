//

//  ZombieAnimRig_FutureProtector.h

//  PlantsVersusZombies2

//

//  Created by Michael Fromwiller on 7/22/13.

//  Copyright (c) 2013 PopCap Games. All rights reserved.

//



#ifndef __PlantsVersusZombies2__ZombieAnimRig_FutureProtector__

#define __PlantsVersusZombies2__ZombieAnimRig_FutureProtector__



#include <string>

#include <vector>



#include "PopAnimRig.h"

#include "RtObject.h"

#include "ZombieAnimRig_Mech.h"



enum ZombieAnimRigState_Protector

{

	ZOMBIEANIM_PROTECTOR_ACTIVATING_SHIELD = ZOMBIEANIM_USERDEFINED+1,

	ZOMBIEANIM_PROTECTOR_HAS_SHIELD,

	ZOMBIEANIM_PROTECTOR_DEACTIVATING_SHIELD,

};



class ZombieAnimRig_FutureProtector : public ZombieAnimRig_Mech

{

public:

    RT_CLASS_DEFINE(ZombieAnimRig_FutureProtector, ZombieAnimRig_Mech, RtClass);

    

	// Protector specific functionality

	virtual bool ActivateShield(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	virtual bool DeactivateShield(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	

	void SetDamageState(const int i_state) override;

	

protected:

	virtual void onPopAnimInitialized() override;

	virtual const std::vector<std::string>& getHeadLayerNames() override;

	virtual const std::vector<std::string>& getArmLayerNames() override;

	virtual const std::vector<std::string>& getArmReplacementPairNames() override;

	

	virtual void onAnimStopped() override;

};





#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_FutureProtector__) */

