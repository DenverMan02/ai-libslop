//
//  ZombieSkyCityGargantuar.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 6/11/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSkyCityGargantuar_h
#define PlantsVersusZombies2_ZombieSkyCityGargantuar_h

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


class ZombieSkyCityGargantuarProps : public ZombieGargantuarProps
{
public:
    RT_CLASS_DEFINE(ZombieSkyCityGargantuarProps, ZombieGargantuarProps, RtClass);
    
    ZombieSkyCityGargantuarProps()
    : ThrowIntervalCol(2)
    {
        
    }
    
    int ThrowIntervalCol;
};

class ZombieSkyCityGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieSkyCityGargantuar, ZombieGargantuar, RtClass);
    
    ZombieSkyCityGargantuar() : m_bAttackAirShip(false) {}
    
    virtual ~ZombieSkyCityGargantuar();
    
protected:
    
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_ONENTER(ZombieState, Smashing);
    
    void playDeathAnimation() override;
    
    bool isImpReadyToBeThrown() override;
    
    bool hasHeadParticle() const override { return false; }
    std::string getAshPAMName() const override;
private:
    
    int GetRemainImp();
    
    void ThrowRemainImp();
    
    void OnDeadThrowEnd(const std::string& strLabel);
    
private:
    
    bool m_bAttackAirShip;
    
};

#endif
