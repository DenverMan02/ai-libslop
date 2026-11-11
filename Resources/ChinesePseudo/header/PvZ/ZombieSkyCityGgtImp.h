//
//  ZombieSkyCityGgtImp.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 10/06/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSkyCityGgtImp_h
#define PlantsVersusZombies2_ZombieSkyCityGgtImp_h

#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"

class ZombieSkyCityGgtImp : public ZombieImp
{
public:
	RT_CLASS_DEFINE(ZombieSkyCityGgtImp, ZombieImp, RtClass);

	ZombieSkyCityGgtImp();

protected:
    
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    
    OVERRIDE_STATE_ONENTER(ZombieState, ImpFlying);
    OVERRIDE_STATE_ONEXIT(ZombieState, ImpFlying);
    
    BoardEntity *findTarget() override;
};


class ZombieAnimRig_SkyCityGgtImp : public ZombieAnimRig_Imp
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_SkyCityGgtImp, ZombieAnimRig_Imp, RtClass);
    
    ZombieAnimRig_SkyCityGgtImp() : m_iNeedJump(0) { }
    
    void SetNeedJump(int iJump) { m_iNeedJump = iJump; }
    
protected:
    
    const std::string getDieAnimationName() override;
    
private:
    
    int m_iNeedJump; //0 die, 1 skee, 2 skee2
};


#endif
