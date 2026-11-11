//
//  Plant_Springbean.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 4/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Springbean_h
#define PlantsVersusZombies2_PlantAnimRig_Springbean_h

#include "PlantAnimRig.h"

enum {
    SPRINGBEAN_ATTACK_START, 
    SPRINGBEAN_ATTACK_WAIT, 
    SPRINGBEAN_ATTACK_END,
    
};

class PlantAnimRig_Springbean : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Springbean, PlantAnimRig, RtClass);
    
    virtual bool PlayInitialFrame() override;
    virtual bool PlayIdleLooped() override; // for now since flash has idle1 & idle2

    bool PlayPreviewAnim(bool bHideLayer = false) override;
    
    void SetToAttackState() { m_state = PLANTANIM_ATTACK; }
    void SetToIdleState()   { m_state = PLANTANIM_IDLE; }
private:
    std::string m_lastPlayedIdleAnim;
};

#endif
