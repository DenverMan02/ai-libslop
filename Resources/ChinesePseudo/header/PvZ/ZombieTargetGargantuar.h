//
//  ZombieTargetGargantuar.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-10-31.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieTargetGargantuar_h
#define PlantsVersusZombies2_ZombieTargetGargantuar_h

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"
#include "ZombieTarget.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_TargetGargantuar, ZombieState_Target)
ZS_TARGET_SpecialAttack,
ZS_TARGET_SpecialAttackGap,
ZS_TARGET_SpecialAttackReady,
ZS_TARGET_Weak,
STATE_ENUM_END(ZombieState_TargetGargantuar);

class ZombieTargetGargantuar : public ZombieTarget
{
public:
	
    RT_CLASS_DEFINE(ZombieTargetGargantuar, ZombieTarget, RtClass);
    
    virtual void TargetRise(const SexyVector3& i_boardPosition) override;
    virtual Sexy::Point GetGridExtents() const override;
    void TakeDamage(const DamageInfo& i_damage) override;
    
protected:
    
    void onZombieInitialize() override;
    void onUpdate() override;
    
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void fireImpCannon();
    
    virtual void onTargetAttackAnimationDone(const std::string& i_animName) override;
    void onTargetReadyAnimationDone(const std::string& i_animName);
    void onTargetSpecialAttackAnimationDone(const std::string& i_animName);
    
    OVERRIDE_STATE_ONENTER(ZombieState, TargetAttack);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, RiseFromGround);
    DECLARE_STATE_FUNCTIONS(ZombieState, SpecialAttack);
    DECLARE_STATE_FUNCTIONS(ZombieState, SpecialAttackGap);
    DECLARE_STATE_FUNCTIONS(ZombieState, SpecialAttackReady);
    DECLARE_STATE_FUNCTIONS(ZombieState, Weak);
    
private:
    
    int m_iAttackCount = 0;
};


#endif
