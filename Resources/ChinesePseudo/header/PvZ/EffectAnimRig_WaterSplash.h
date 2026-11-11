//
//  EffectAnimRig_WaterSplash.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_WaterSplash_h
#define PlantsVersusZombies2_EffectAnimRig_WaterSplash_h

#include "PopAnimRig.h"

class EffectAnimRig_WaterSplash : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_WaterSplash, PopAnimRig, RtClass) {}
	
	bool PlayRandomSplash(PopAnimRig::AnimStoppedDelegate i_onStopped);
	
protected:
	virtual void onPopAnimInitialized() override;
	virtual void onPreDraw(Graphics* i_g) override;
	virtual void onPostDraw(Graphics* i_g) override;
};

#endif
