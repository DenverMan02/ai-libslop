//
//  ZombieAnimRig_ZombossMech.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/9/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_ZombossMech__
#define __PlantsVersusZombies2__ZombieAnimRig_ZombossMech__

#include "ZombieAnimRig.h"
#include "ZombieZombossMech.h"

class ZombieAnimRig_ZombossMech : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech, ZombieAnimRig, RtClass);
	
	void onPopAnimInitialized() override;
	
	/// Animations
	virtual void PlayIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	void PlayPreIntro(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	void PlayIntro(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual void PlayWalkForDirection(ZombossWalkDirection i_walkDir, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayWalkForward(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayWalkBackward(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayWalkUp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayWalkDown(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRushForward();
	void PlayJumpStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayJumpMid(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayJumpLand(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayStomp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayPortalStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayPortalLoop(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	void PlayPortalEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlaySummoning(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual void PlayRocketStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRocketLaunch(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayStun(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayStunLoop();
	void PlayStunEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayZombossDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayZombossDieTalk();
	void PlayExit(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayTransform(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
	/// Layer visibility
	enum DamagePhase
	{
		DamagePhase_0,
		DamagePhase_1,
		DamagePhase_2,
		DamagePhase_3,
		DamagePhase_4,
		DamagePhase_5,
		DamagePhase_6
	};
	virtual void SetDamagePhase(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase);
	
	virtual const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const;
	virtual const char* getPreIntroAnimName() const;
	virtual const char* getIntroAnimName() const;
	virtual const char* getIdleAnimName() const;
	virtual const char* getWalkForwardAnimName() const;
	virtual const char* getWalkBackwardAnimName() const;
	virtual const char* getWalkUpAnimName() const;
	virtual const char* getWalkDownAnimName() const;
	virtual const char* getRushForwardAnimName() const;
	virtual const char* getJumpStartAnimName() const;
	virtual const char* getJumpMidAnimName() const;
	virtual const char* getJumpLandAnimName() const;
	virtual const char* getStompAnimName() const;
	virtual const char* getPortalStartAnimName() const;
	virtual const char* getPortalLoopAnimName() const;
	virtual const char* getPortalEndAnimName() const;
    virtual const char* getSummoningAnimName() const;
	virtual const char* getRocketStartAnimName() const;
	virtual const char* getRocketLaunchAnimName() const;
	virtual const char* getStunAnimName() const;
	virtual const char* getStunLoopAnimName() const;
	virtual const char* getStunEndAnimName() const;
	virtual const char* getZombossDieAnimName() const;
	virtual const char* getZombossDieTalkAnimName() const;
	virtual const char* getExitAnimName() const;
	virtual const Sexy::FPoint getTeleportationEffectOffset() const;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_ZombossMech__) */
