//
//  ZombieAnimRig_ZombossBlade.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2-10-14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossBlade__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossBlade__

#include "Precompile.h"
#include "ZombieAnimRig_Zomboss.h"

class ZombieAnimRig_ZombossBlade : public ZombieAnimRig_Zomboss
{
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossBlade, ZombieAnimRig_Zomboss, RtClass);

public:
	bool PlayTakeShield(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlaySummon(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayChop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayBrakes(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayJump(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayLand(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayFlyOutsideScreen(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayPrepareBladeKee(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
    bool PlayTakeBladeKee(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);

	void PlayShielding();
	void PlayDashForward();
	void PlayFlyAttackForward();

private:
    
	const std::string GetChopLabel() const { return "attack"; }
    
	const std::string GetFlyOutsideScreenLabel() const { return "jump_up"; }
	const std::string GetFlyAttackForwardLabel() const { return "fly"; }
    
    const std::string GetBrakesLabel() const { return "dash_end"; }
    const std::string GetDashForwardLabel() const { return "dash_forward"; }
	const std::string GetPrepareBladeKeeLabel() const { return "power_ready"; }
    const std::string GetTakeBladeKeeLabel() const { return "power_attack"; }
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossBlade__) */
