//
//  ZombieAnimRig_Bull.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Bull_h
#define PlantsVersusZombies2_ZombieAnimRig_Bull_h

#include "ZombieAnimRig.h"
#include "ZombieAnimRig_BullRider.h"

class ZombieAnimRig_Bull : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Bull, ZombieAnimRig, RtClass);

	ZombieAnimRig_Bull();
	virtual ~ZombieAnimRig_Bull();
	
	bool PlayPawing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayPreRun(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	bool PlayRearing(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	SexyVector2 GetHeadOffset() override;

	void SetDamageState(const int i_state);
	void SetRunning(bool i_running);
	void HideRider();

protected:
	virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
	virtual const std::string getDieAnimationName() override;
    const bool getDieShouldBlend() override { return false; }

private:
	bool m_running;

	void onPopAnimInitialized() override;
};

#endif
