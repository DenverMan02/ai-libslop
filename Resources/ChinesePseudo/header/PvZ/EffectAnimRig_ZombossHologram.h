//
//  EffectAnimRig_ZombossHologram.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/7/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_ZombossHologram__
#define __PlantsVersusZombies2__EffectAnimRig_ZombossHologram__

#include <string>

#include "PopAnimRig.h"
#include "RtObject.h"

class WorldData;

enum ZombossHologramState
{
	HologramClosed,
	HologramOpenIntoActive,
	HologramOpenIntoTaunt,
	HologramOpenIntoDefeated,
	HologramTaunt,
	HologramClosing,
	HologramActiveIdle,
	HologramDefeated,
};

class EffectAnimRig_ZombossHologram : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_ZombossHologram, PopAnimRig, RtClass){};
    
	EffectAnimRig_ZombossHologram();
	~EffectAnimRig_ZombossHologram();
	
	void SelectAndBeginStateForWorld(const std::string& i_worldName);
	void PlayTauntSequence();
	void PlayActiveIdleLooped();
	void PlayActivateSequence();
	void PlayDefeatedSequence();

	std::string PickActiveIdleAnim();
	std::string PickTauntAnim();
	std::string GetDefeatedAnim();
	std::string GetOpenAnim();
	std::string GetCloseAnim();

	void PopAnimPlaySample(const std::string& i_sampleName, int i_pan, double i_volume, double i_numSteps) override;
	
private:
	void onSwitchedWorlds(WorldData* i_world);
    void onFinished(const std::string& i_anim);
	
	ZombossHologramState m_state;
	std::string m_lastPickedIdleAnim;
	int m_finishedIdles;
};


#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_ZombossHologram__) */
