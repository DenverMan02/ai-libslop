
#ifndef DinoYoungBrontosaurus_hpp
#define DinoYoungBrontosaurus_hpp

#include <stdio.h>
#include "DinosaurYounger.h"

class Zombie;

class DinoYoungBrontosaurus : public DinosaurYounger
{
public:
    RT_CLASS_DEFINE(DinoYoungBrontosaurus, DinosaurYounger, RtClass);
    
    DinoYoungBrontosaurus();
    virtual ~DinoYoungBrontosaurus();
    
    OVERRIDE_STATE_UPDATE(DinoYoungerState, Wake);
    OVERRIDE_STATE_UPDATE(DinoYoungerState, Cry);
    
protected:
    bool shouldDestroyWhenOffScreen() override;
    void wakeAnimDoneHandler() override;
    void cryAnimDoneHandler() override;
    void caughtAnimDoneHandler() override;
};

class DinosaurAnimRig_YoungBrontosaurus : public DinosaurAnimRig_Younger
{
public:
    RT_CLASS_DEFINE(DinosaurAnimRig_YoungBrontosaurus, DinosaurAnimRig_Younger, RtClass);
    
protected:
    const std::string getIdleAnimationName() override;
    const std::string getCaughtAnimationName() override;
};

#endif /* DinoYoungBrontosaurus_hpp */
