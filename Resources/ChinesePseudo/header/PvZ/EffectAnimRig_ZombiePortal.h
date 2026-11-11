//
//  EffectAnimRig_ZombiePortal.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 12/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_ZombiePortal__
#define __PlantsVersusZombies2__EffectAnimRig_ZombiePortal__

#include "PopAnimRig.h"
#include "RtObject.h"

namespace Sexy {
	class Graphics;
}  // namespace Sexy

class EffectAnimRig_ZombiePortal : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_ZombiePortal, PopAnimRig, RtClass);
	
	void PlayOpen(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayLooped();
	void PlayClose(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
private:
	const char* getOpenAnimName() const;
	const char* getLoopedAnimName() const;
	const char* getCloseAnimName() const;

};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_ZombiePortal__) */
