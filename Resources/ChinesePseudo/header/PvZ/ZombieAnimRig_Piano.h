//
//  ZombieAnimRig_Piano.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_PIANO_H__
#define __ZOMBIEANIMRIG_PIANO_H__

#include <string>
#include <vector>

#include "PopAnimRig.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "ZombieAnimRig.h"
#include "Core.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

enum ZombiePianoDamageState
{
	PVZ_BEGIN_ENUM(PIANODAMAGE_),
	PIANODAMAGE_NEEDSINIT,
	PIANODAMAGE_NONE,
	PIANODAMAGE_NEEDDAMAGE,
	PIANODAMAGE_PLAYING,
	PIANODAMAGE_DAMAGED,
	PVZ_END_ENUM(PIANODAMAGE_)
};

class ZombieAnimRig_Piano : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Piano, ZombieAnimRig, RtClass);

	ZombieAnimRig_Piano();

	void SetAnimRateOverride(float i_multiplier) override;
	void ClearAnimRateOverride() override;

	bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
    bool PlayWalk(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
	bool PlayEat() override;
	AnimHandle PlayDie() override;
	void PlayPianoDeath();
	bool IsPianoAnimPlaying();

	void SetDamaged();
	void SetUndamaged();
	void UpdatePiano();
	void DrawPiano(Sexy::Graphics* i_g);

	void AddWarpEffect();
	void RemoveWarpEffect();

protected:
	void onPreDraw(Graphics* i_g) override;
	void onPopAnimInitialized() override;

	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;

private:
	bool choosePianoPlayingAnimation();

	void onPianoPlayAnimationEnd(const std::string& i_name);
	void onPianoDamageAnimationEnd(const std::string& i_name);

	ZombiePianoDamageState m_damageState;
	PopAnimRigPtr m_piano;
};

#endif
