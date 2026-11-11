//
//  ZombieTargetArchmage.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-10-30.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieTargetArchmage_h
#define PlantsVersusZombies2_ZombieTargetArchmage_h

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"
#include "BoardEnums.h"
#include "ZombieTarget.h"

class ZombieTargetArchmage : public ZombieTarget
{
public:
	
    RT_CLASS_DEFINE(ZombieTargetArchmage, ZombieTarget, RtClass);
    
    virtual void TargetRise(const SexyVector3& i_boardPosition) override;
    
protected:
    
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    OVERRIDE_STATE_ONENTER(ZombieState, TargetAttack);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, RiseFromGround);
};

#endif
