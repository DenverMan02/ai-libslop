//
//  ZombiePVPGargantuar.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 11/11/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePVPGargantuar_h
#define PlantsVersusZombies2_ZombiePVPGargantuar_h

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieGargantuar.h"
#include "ZombiePropertySheet.h"

class ZombiePVPGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombiePVPGargantuar, ZombieGargantuar, RtClass);
    
    ZombiePVPGargantuar() : m_iSkillThrowCount(0) {}
    
    virtual ~ZombiePVPGargantuar() {}
    
protected:
    
    bool isImpReadyToBeThrown() override;
    
    void ApplyZombieFood() override;
    int GetImpTargetColumn() override;
    OVERRIDE_STATE_ONENTER(ZombieState, ThrowImp);
    
private:
    
    int GetRemainImp();
    
    void ThrowRemainImp();
    
    void OnSkillThrowEnd(const std::string& strLabel);
    
private:
    
    int m_iSkillThrowCount;
};

#endif
