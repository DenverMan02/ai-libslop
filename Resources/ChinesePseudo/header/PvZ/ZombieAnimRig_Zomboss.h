//
//  ZombieAnimRig_Zomboss.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2-10-14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_Zomboss__
#define __PlantsVersusZombies2__ZombieAnimRig_Zomboss__

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Zomboss : public ZombieAnimRig
{
	RT_CLASS_DEFINE(ZombieAnimRig_Zomboss, ZombieAnimRig, RtClass);

public:
	bool PlayIntro(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayZombossDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayEpilogue(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayChangeStage(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);

	virtual ZombieParticle* DropHead(Zombie* i_zombie) override
    {
        return NULL;
    }
    
	virtual ZombieParticle* DropArm(Zombie* i_zombie) override
    {
        return NULL;
    }
    
protected:
    
	virtual const std::string GetIntroLabel() const { return "intro"; }
	virtual const std::string GetDieLabel() const { return "die_talk"; }
	virtual const std::string GetEpilogueLabel() const { return "die_exit"; }
	virtual const std::string GetChangeStageLabel() const { return "angry"; }
    
    virtual const std::string GetTakeShieldLabel() const { return "defence_start"; }
	virtual const std::string GetShieldingLabel() const { return "defence_idle"; }
	virtual const std::string GetSummonLabel() const { return "summon"; }
    
    virtual const std::string GetJumpLabel() const { return "jump_up"; }
    virtual const std::string GetLandLabel() const { return "jump_down"; }
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_Zomboss__) */
