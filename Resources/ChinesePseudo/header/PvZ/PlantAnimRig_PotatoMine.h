//
//  PlantAnimRig_PotatoMine.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/15/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_POTATOMINE_H__
#define __PLANTANIMRIG_POTATOMINE_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

enum PlantAnimRigState_PotatoMine
{
	PLANTANIM_POTATOMINE_PLANTED = PLANTANIM_USERDEFINED,
	PLANTANIM_POTATOMINE_EMERGE,
};

class PlantAnimRig_PotatoMine : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_PotatoMine, PlantAnimRig, RtClass);
	
	typedef PopAnimRig::AnimStoppedReflectionDelegate EmergeAnimDone;
	
	virtual bool PlayInitialFrame() override;
	virtual bool PlayIdleLooped() override;
	virtual bool PlayEmergeFromGround(EmergeAnimDone i_onEmergeDone = EmergeAnimDone());
	virtual bool PlayEmergeFromGroundFast(EmergeAnimDone i_onEmergeDone = EmergeAnimDone());
	virtual bool PlaySpinningPotato();
	
	bool PlayPreviewAnim(bool bHideLayer = false) override;
	
	void SetSubmerged(bool i_submerged);
	
protected:
	virtual void onPopAnimInitialized() override;
	
	bool m_submerged;
};

#endif // __PLANTANIMRIG_POTATOMINE_H__
