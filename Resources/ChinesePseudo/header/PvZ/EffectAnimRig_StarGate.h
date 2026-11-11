//
//  EffectAnimRig_StarGate.h
//  PlantsVersusZombies2
//
//  Created by astajos on 3/22/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_StarGate_h
#define PlantsVersusZombies2_EffectAnimRig_StarGate_h

#include <string>

#include "PopAnimRig.h"
#include "RtDelegate.h"
#include "RtObject.h"

class EffectAnimRig_StarGate : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(EffectAnimRig_StarGate, PopAnimRig, RtClass);
    
    EffectAnimRig_StarGate();
    
    void PlayUnavailableIdle();
    void PlayLockedIdle();
    void PlayOpenIdle();
    void PlayUnlockingSequence(Delegate0 i_sequenceFinishedDelegate);
    void PlayInteractableSequence(Delegate0 i_sequenceFinishedDelegate);
    
    void SetIsFlipped(bool i_isFlipped);
    
private:
    void onUnlockingSequenceContinued(const std::string& i_oldAnimName);
    void onLockingSequenceContinued(const std::string& i_oldAnimName);
    void onInteractableSequenceContinued(const std::string& i_oldAnimName);
    
    std::string m_orientation;
    Delegate0 m_sequenceFinishedDelegate;
};

#endif
