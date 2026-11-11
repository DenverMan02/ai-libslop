//
//  PlantAnimRig_MagicBeans.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/15/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_MAGICBEANS_H__
#define __PLANTANIMRIG_MAGICBEANS_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

enum PlantAnimRigState_MagicBeans
{
	PLANTANIM_MAGICBEANS_PLANTED = PLANTANIM_USERDEFINED,
	PLANTANIM_MAGICBEANS_EMERGE,
};

class PlantAnimRig_MagicBeans : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_MagicBeans, PlantAnimRig, RtClass);

	typedef PopAnimRig::AnimStoppedReflectionDelegate EmergeAnimDone;

	virtual bool PlayInitialFrame() override;
	virtual bool PlayIdleLooped() override;
	virtual bool PlayEmergeFromGround(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual bool PlayShake(EmergeAnimDone i_onEmergeDone = EmergeAnimDone());
	virtual bool PlayEmergeFromGroundFast(EmergeAnimDone i_onEmergeDone = EmergeAnimDone());
	virtual bool PlaySpinningBeans();
	bool PlayDie(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

	bool PlayPreviewAnim(bool bHideLayer = false) override;

	void SetSubmerged(bool i_submerged);

protected:
	virtual void onPopAnimInitialized() override;

	bool m_submerged;
};

#endif // __PLANTANIMRIG_MagicBeans_H__
