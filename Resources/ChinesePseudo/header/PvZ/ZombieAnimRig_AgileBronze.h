//
//  ZombieAnimRig_AgileBronze.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 13-12-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_AgileBronze__
#define __PlantsVersusZombies2__ZombieAnimRig_AgileBronze__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_AgileBronze : public ZombieAnimRig
{
	RT_CLASS_DEFINE(ZombieAnimRig_AgileBronze, ZombieAnimRig, RtClass);

public:
	bool PlayDebut(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayReadyToJump(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayJumping();
    bool PlayLanding();
    bool PlayLandingOver(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);

    pvztime_t GetJumpingDuration();
    pvztime_t GetLandingDuration();

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;

private:
	std::string GetDebutLabel() const;
	std::string GetJumpLabel() const;
	std::string GetLandingLabel() const;
	std::string GetReadyToJumpLabel() const;
	std::string GetLandingOverLabel() const;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_AgileBronze__) */
