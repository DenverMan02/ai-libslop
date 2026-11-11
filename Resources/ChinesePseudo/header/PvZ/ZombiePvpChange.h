//
//  ZombiePvpChange.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 15/11/9
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePvpChange_h
#define PlantsVersusZombies2_ZombiePvpChange_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieBasic.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"
#include "Projectile.h"

class ZombiePvpChangeProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePvpChangeProps, ZombiePropertySheet, RtClass);
    
    ZombiePvpChangeProps()
    {
        SkillSpanTime = 20.0f;
        HelmAdd = 1100.0f;
    }
    
    float   SkillSpanTime;
    float   HelmAdd;
};

class ZombiePvpChange : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombiePvpChange, ZombieBasic, RtClass);

protected:
	virtual void onUpdate() override;
    virtual void onZombieInitialize() override;
    
    virtual void ApplyZombieFood() override;
    virtual void CancelZombieFood() override;
    
    float   m_skillTime;
};

#endif
