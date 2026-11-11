
#ifndef DinoYoungPterodactyl_hpp
#define DinoYoungPterodactyl_hpp

#include "Dinosaur.h"
#include "DinosaurYounger.h"

class Zombie;
class DinosaurPterodactyl;

class DinoYoungPterodactyl : public DinosaurYounger
{
public:
    RT_CLASS_DEFINE(DinoYoungPterodactyl, DinosaurYounger, RtClass);
    
    DinoYoungPterodactyl();
    virtual ~DinoYoungPterodactyl();
    
    OVERRIDE_STATE_FUNCTIONS(DinoYoungerState, Cry);
    OVERRIDE_STATE_UPDATE(DinoYoungerState, CaughtFly);
    
    bool shouldDestroyWhenOffScreen() override;
protected:
    void wakeAnimDoneHandler() override;
    void cryAnimDoneHandler() override;
    void caughtAnimDoneHandler() override;
protected:
    void spawnPtero();
private:
    void move(float i_xSpeed, float i_zSpeed);
    bool isOffBoard() const;
    friend class DinosaurPterodactyl;
    RtWeakPtr<DinosaurPterodactyl> m_ptero;
};

class DinosaurAnimRig_YoungPterodactyl : public DinosaurAnimRig_Younger
{
public:
    RT_CLASS_DEFINE(DinosaurAnimRig_YoungPterodactyl, DinosaurAnimRig_Younger, RtClass);
    
protected:
    const std::string getCryAnimationName() override;
    const std::string getIdleAnimationName() override;
};

#endif /* DinoYoungPterodactyl_h */
