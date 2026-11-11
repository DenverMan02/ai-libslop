//
//  ZombieNeuropathy.h
//  PlantsVersusZombies2
//
//  Created by Zhangxy on 11/14/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieNeuropathy_h
#define PlantsVersusZombies2_ZombieNeuropathy_h

#include "Zombie.h"
#include "RtObject.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

class ZombieNeuropathyProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieNeuropathyProps, ZombiePropertySheet, RtClass);
	
	float DiscardBoxSpeedScale = 0.24f;
    float HaveBoxSpeedScale = 0.8f;
};

enum NeuropathyState
{
    NEUROPATHYSTATE_DISCARDBOX,
    NEUROPATHYSTATE_HAVEBOX,
    NEUROPATHYSTATE_WALK,
};


// STATE_ENUM_CHILD_BEGIN(ZombieState_Neuropathy, ZombieState)
// ZS_SelfExplode_Detonate,
// STATE_ENUM_END(ZombieState_Neuropathy)

class ZombieNeuropathy : public Zombie
{
	RT_CLASS_DEFINE(ZombieNeuropathy, Zombie, RtClass);
    ZombieNeuropathy()
    {
        m_minrandBombing = 4.2f;
        m_maxrandBombing = 15.2f;
        DiscardBoxSpeedScale = 0.22f;
        m_HaveBomb = true;
        m_Havebox = true;
    }
    void TryDetonatedBomb();
    void onBigBangAnimationDone(StandaloneEffect* i_effect);
    void onBigBangAnimationLoop(StandaloneEffect* i_effect);
    void onDiscardBoxComplete(const std::string &i_animName);
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
    virtual void DoSpecial();
	virtual void onDraw(class Sexy::Graphics* i_g) override;
    virtual ZombieParticle* DropHead() override;
	virtual bool hasArmParticle() const {return false;}
    virtual void onPlaceOnBoard();
    void playDeathAnimation() override;

	class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
protected:
    pvztime_t m_minrandBombing;
    pvztime_t m_maxrandBombing;
    // pvztime_t m_randBombing;
	pvztime_t m_countdown;
    float DiscardBoxSpeedScale;
	NeuropathyState m_state;
	pvztime_t m_InvisibleStartTime = PVZ_EOT();

    bool m_HaveBomb;
    bool m_Havebox;
};

#endif
