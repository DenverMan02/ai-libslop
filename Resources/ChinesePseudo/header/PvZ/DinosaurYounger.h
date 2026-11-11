
#ifndef DinosaurYounger_hpp
#define DinosaurYounger_hpp

#include <stdio.h>
#include "Dinosaur.h"

STATE_ENUM_CHILD_BEGIN(DinoYoungerState, DinosaurState)
CS_DINOYOUNGER_Wake,
CS_DINOYOUNGER_Cry,
CS_DINOYOUNGER_Caught,
CS_DINOYOUNGER_CaughtFly,
STATE_ENUM_END(DinoYoungerState);

class Zombie;

class DinosaurYounger : public Dinosaur
{
public:
    RT_CLASS_DEFINE(DinosaurYounger, Dinosaur, RtClass);
    
    DinosaurYounger();
    virtual ~DinosaurYounger();
    
    OVERRIDE_STATE_FUNCTIONS(CreatureState, Idle);
    
    DECLARE_STATE_FUNCTIONS(DinoYoungerState, Wake);
    DECLARE_STATE_FUNCTIONS(DinoYoungerState, Cry);
    DECLARE_STATE_FUNCTIONS(DinoYoungerState, Caught);
    DECLARE_STATE_FUNCTIONS(DinoYoungerState, CaughtFly);
    
    bool CanBeCharmed() override;
    void Charm() override;
protected:
    void onPlaceOnBoard() override;
    
    void onWakeAnimDone(const std::string& i_animLabelName);
    void onCryAnimDone(const std::string& i_animLabelName);
    void onCaughtAnimDone(const std::string& i_animLabelName);
    
    virtual void wakeAnimDoneHandler();
    virtual void cryAnimDoneHandler();
    virtual void caughtAnimDoneHandler();
    protected:
    pvztime_t					m_nextActivationTime = PVZ_EOT();
    pvztime_t					m_timeToWake = PVZ_EOT();
    pvztime_t					m_timeToWalk = PVZ_EOT();
    pvztime_t					m_timeToCry = PVZ_EOT();
    pvztime_t                   m_wakeDuration = PVZ_EOT();
    int							m_numberOfZombiesCarriedAndDropped = 0;
};

class DinosaurYoungerPropertySheet : public DinosaurPropertySheet
{
public:
    RT_CLASS_DEFINE(DinosaurYoungerPropertySheet, DinosaurPropertySheet, RtClass);
    
    DinosaurYoungerPropertySheet()
    {
        ArtCenter = {90, 125};
        MovementSpeed = 145.0f;
        EventRate = 0.5;
        IdleDuration = 2.0;
        CryDuration = 1.0;
        ShakeDuration = 2.0f;
        ShakeEnabled = true;
    }
    float MovementSpeed;
    float EventRate;
    pvztime_t IdleDuration;
    pvztime_t CryDuration;
    pvztime_t ShakeDuration;
    std::string TriggerEvent;
    std::string RoarSound;
    std::string TreadSound;
    bool ShakeEnabled;
};

class DinosaurAnimRig_Younger : public CreatureAnimRig
{
public:
    RT_CLASS_DEFINE(DinosaurAnimRig_Younger, CreatureAnimRig, RtClass);
    
    void PlaySleep(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
    void PlayWake(AnimStoppedReflectionDelegate i_onStopped = {});
    void PlayCaught(AnimStoppedReflectionDelegate i_onStopped = {});
    void PlayCaughtFly(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
    
    void PlayIdleAnimation(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
    
    void PlayGrabIdle(LoopingAnimContinuedReflectionDelegate i_onStopped = {});
    
    void PlayCry(LoopingAnimContinuedReflectionDelegate i_onStopped = {});
    
    virtual const std::string getWakeAnimationName();
protected:
    virtual const std::string getCryAnimationName();
    virtual const std::string getCaughtAnimationName();
    virtual const std::string getCaughtFlyAnimationName();
    const std::string getIdleAnimationName() override;
};

#endif /* DinosaurYounger_hpp */
