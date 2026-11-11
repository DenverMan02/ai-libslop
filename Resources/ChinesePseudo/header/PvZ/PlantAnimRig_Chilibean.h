//
//  Plant_Chilibean.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Chilibean_h
#define PlantsVersusZombies2_PlantAnimRig_Chilibean_h

#include "PlantAnimRig.h"

class PlantAnimRig_Chilibean : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Chilibean, PlantAnimRig, RtClass);
    
    virtual bool PlayInitialFrame() override;
    virtual bool PlayIdleLooped() override;

	void PlayFlyingAnim();
	void PlayLandingAnim();

private:
	void onLandingFinished(const std::string &name);
    std::string m_lastPlayedIdleAnim;
};

#endif
