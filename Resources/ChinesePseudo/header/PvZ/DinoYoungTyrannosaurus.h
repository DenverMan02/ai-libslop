
#ifndef DinoYoungTyrannosaurus_hpp
#define DinoYoungTyrannosaurus_hpp

#include <stdio.h>
#include "DinosaurYounger.h"

class Zombie;

class DinoYoungTyrannosaurus : public DinosaurYounger
{
public:
    RT_CLASS_DEFINE(DinoYoungTyrannosaurus, DinosaurYounger, RtClass);
    
    DinoYoungTyrannosaurus();
    virtual ~DinoYoungTyrannosaurus();
    
    OVERRIDE_STATE_FUNCTIONS(CreatureState, Walk);
    OVERRIDE_STATE_ONENTER(DinoYoungerState, Wake);
protected:
    void wakeAnimDoneHandler() override;
private:
    pvztime_t					m_nextActivationTime;
    pvztime_t					m_timeToWake;
    pvztime_t					m_timeToWalk;
    pvztime_t					m_dinoRunTime;
    int							m_numberOfZombiesCarriedAndDropped;
};

class DinosaurAnimRig_YoungTyrannosaurus : public DinosaurAnimRig_Younger
{
public:
    RT_CLASS_DEFINE(DinosaurAnimRig_YoungTyrannosaurus, DinosaurAnimRig_Younger, RtClass);
    
protected:
    const std::string getIdleAnimationName() override;
};

#endif /* DinoYoungTyrannosaurus_h */