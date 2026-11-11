//
//  ZombieTarget.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-8-21.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieTarget__
#define __PlantsVersusZombies2__ZombieTarget__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"
#include "StageModule.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Target, ZombieState)
ZS_TARGET_Attack,
STATE_ENUM_END(ZombieState_Target)

class ZombieTarget : public Zombie
{
public:
    
	RT_CLASS_DEFINE(ZombieTarget, Zombie, RtClass);
    
    void SetValidTimeNumber(pvztime_t i_validTime)
    {
        ValidTimeNumber = i_validTime;
    }
    
    void SetAttackOnce(bool i_once)
    {
        m_bAttackOnce = i_once;
    }
    
    virtual void TargetRise(const SexyVector3& i_boardPosition);

protected:
    
	void onZombieInitialize() override;
    void onUpdate()           override;
    void onPlaceOnBoard()     override;
    
    void onDraw(class Sexy::Graphics* i_g) override;
    
    virtual bool hasHeadParticle() const override {return false;}
    virtual bool hasArmParticle() const override {return false;}
    
    Plant * getValidTargetPlant();
    virtual void onTargetAttackAnimationDone(const std::string& i_animName);
    
    void onAppearAnimDone(const std::string& i_label);

    OVERRIDE_STATE_ONENTER(ZombieState, Idle);
    OVERRIDE_STATE_ONENTER(ZombieState, Die);
    OVERRIDE_STATE_ONENTER(ZombieState, TargetRise);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, TargetAttack);
    
    pvztime_t m_AttackColdDownTime;
    bool      m_bFirstAttackDone;
    
private:
    
    pvztime_t m_targetValidTime;
    pvztime_t ValidTimeNumber;
    
    bool      m_BeHited;
    
    int       m_nAttackNum;
    bool      m_bAttackOnce;
};

namespace Message
{
	void MissTarget();
}

#endif /* defined(__PlantsVersusZombies2__ZombieTarget__) */
