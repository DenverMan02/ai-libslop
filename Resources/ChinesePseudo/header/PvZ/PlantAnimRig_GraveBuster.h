//
//  PlantAnimRig_GraveBuster.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIM_GRAVEBUSTER_H__
#define __PLANTANIM_GRAVEBUSTER_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_GraveBuster : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_GraveBuster, PlantAnimRig, RtClass){}

	virtual bool PlayInitialFrame() override;

	virtual bool PlayPlantAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	virtual bool PlayEatAnim();
    std::string GetPriviewAnim();
	bool PlayPreviewAnim(bool bHideLayer = false) override;
};

#endif // __PLANTANIM_GRAVEBUSTER_H__
