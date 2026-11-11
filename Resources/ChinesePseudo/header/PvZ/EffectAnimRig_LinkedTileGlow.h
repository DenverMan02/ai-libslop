//
//  EffectAnimRig_LinkedTileGlow.h
//  PlantsVersusZombies2
//
//  Created by jsola on 9/21/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_LinkedTileGlow_h
#define PlantsVersusZombies2_EffectAnimRig_LinkedTileGlow_h

#include "PopAnimRig.h"

class EffectAnimRig_LinkedTileGlow : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_LinkedTileGlow, PopAnimRig, RtClass) {}
	
	void PlayMovingTileFadeIn();
	void PlayMovingTileIdle();
	void PlayMovingTileFadeOut(AnimStoppedDelegate i_onAnimStopped);
	
	void PlayUnderGlowIdle();
	void PlayUnderGlowFadeOut(AnimStoppedDelegate i_onAnimStopped);

protected:
	virtual void onPopAnimInitialized() override;
	virtual void onAnimStopped() override;
	bool m_toMovingTileIdle;
};

#endif
