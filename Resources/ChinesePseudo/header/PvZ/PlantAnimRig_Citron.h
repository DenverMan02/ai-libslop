//
//  PlantAnimRig_Citron.h
//  PlantsVersusZombies2
//
//  Created by PopCap User on 8/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAnimRig_Citron__
#define __PlantsVersusZombies2__PlantAnimRig_Citron__

#include <string>

#include "PlantAnimRig.h"
#include "RtObject.h"

enum PlantAnimRigState_Citron
{
	PLANTANIM_CITRON_CHARGING = PLANTANIM_USERDEFINED,
	PLANTANIM_CITRON_RECOVER,
};


class PlantAnimRig_Citron : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Citron, PlantAnimRig, RtClass);
    
    bool PlayInitialFrame() override;
    bool PlayIdleLooped() override;
	bool PlayRecovery();
	bool PlayCharging();

    bool PlayPreviewAnim(bool bHideLayer = false) override;
    
    void SetToIdleState()   { m_state = PLANTANIM_IDLE; }
    void SetToRecoverState() { m_state = (PlantAnimRigState)PLANTANIM_CITRON_RECOVER; }
	void SetToChargingState() { m_state = (PlantAnimRigState)PLANTANIM_CITRON_CHARGING; }
private:
    std::string m_lastPlayedIdleAnim;
};

#endif /* defined(__PlantsVersusZombies2__PlantAnimRig_Citron__) */
