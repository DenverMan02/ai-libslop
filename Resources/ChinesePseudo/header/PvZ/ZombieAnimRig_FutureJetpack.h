//

//  ZombieAnimRig_FutureJetpack.h

//  PlantsVersusZombies2

//

//  Created by jsola on 10/5/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieAnimRig_FutureJetpack_h

#define PlantsVersusZombies2_ZombieAnimRig_FutureJetpack_h



#include <string>

#include <vector>



#include "PopAnimRig.h"

#include "RtObject.h"

#include "ZombieAnimRig.h"



class ZombieAnimRig_FutureJetpack : public ZombieAnimRig

{

	RT_CLASS_DEFINE(ZombieAnimRig_FutureJetpack, ZombieAnimRig, RtClass);

	

public:

	

	void PlayDropIn(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void PlayFlyUp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void PlayFlyDown(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void PlayFlyIdle();

	

	void SetDiscoMode(bool i_disco);

	

protected:

	

	virtual void onPopAnimInitialized() override;

	

	virtual const std::vector<std::string>& getHeadLayerNames() override;

	virtual const std::vector<std::string>& getArmLayerNames() override;

	virtual const std::vector<std::string>& getArmReplacementPairNames() override;



	virtual const std::string GetHeadParticleName() override;

	

	const std::vector<std::string>& getDiscoLayerNames();

	

private:

	bool m_discoMode = false;

};



#endif

