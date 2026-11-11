//
//  EffectAnimRig_LinkedTile.h
//  PlantsVersusZombies2
//
//  Created by jsola on 9/17/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_LinkedTile_h
#define PlantsVersusZombies2_EffectAnimRig_LinkedTile_h

#include "PopAnimRig.h"

class EffectAnimRig_LinkedTileConnect : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_LinkedTileConnect, PopAnimRig, RtClass) {}
	
	void PlayOn();
	void PlayGlow();
	AnimHandle PlayOff(AnimStoppedDelegate i_onAnimStopped = AnimStoppedDelegate());
	
private:
	virtual void onPopAnimInitialized() override;
	virtual void onAnimStopped() override;
	bool m_continueToGlow = false;
};

class EffectAnimRig_LinkedTile : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_LinkedTile, PopAnimRig, RtClass) {}
	
	void PlayIdle();
	void PlayPlantEnteredTile();
	void PlayPlantLeftTile();
	void PlayActivation();
	
	void SetPlantIsOnTile(bool i_onTile)
	{
		m_plantOnTile = i_onTile;
	}
	
private:
	virtual void onAnimStopped() override;
	
	bool m_plantOnTile = false;
};

#endif
