#ifndef __BOOST_TRACKER_DERIVE__
#define __BOOST_TRACKER_DERIVE__

#include "BoostTracker.h"

class TrueDamageAppendBoostTracker : public PlantBoostTracker
{
public:
    TrueDamageAppendBoostTracker();
    void InitData(float rate, float duration, float cooldown, float append);
    virtual void Update(class Plant* plant) override;

private:
    float m_boostRate;
    float m_duration;
    float m_cooldown;
    float m_appendRate;
    float m_timeCounter;
    float m_secondCounter;
};


#endif