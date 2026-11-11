//
//  ZombieSkyCity.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 06/26/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSkyCity_h
#define PlantsVersusZombies2_ZombieSkyCity_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "ZombieWithActions.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"
#include "Projectile.h"

class ZombieSkyCityProps : public ZombieWithActionsProps
{
public:
    
    RT_CLASS_DEFINE(ZombieSkyCityProps, ZombieWithActionsProps, RtClass);
    
    ZombieSkyCityProps()
    : FindAirShipOffset(Sexy::Point(0, 0))
    , IsContinueDamage(true)
    , AttactShipPrepareAnim(false)
    , DamageValue(0.0f) { }
    
    Sexy::Point FindAirShipOffset;
    bool        IsContinueDamage;
    bool        AttactShipPrepareAnim;
    float       DamageValue;
    
};

class ZombieSkyCity : public ZombieWithActions
{
public:
    
	RT_CLASS_DEFINE(ZombieSkyCity, ZombieWithActions, RtClass);
    
    ZombieSkyCity() : m_bPlayEatAirShip(false), m_bDieOnAirShip(false) { }
    
    virtual ~ZombieSkyCity() { }
    
    virtual BoardEntity *findTarget() override;
    
    OVERRIDE_STATE_ONENTER(ZombieState, Eat);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    OVERRIDE_STATE_ONEXIT(ZombieState, Eat);
    
    void playDeathAnimation() override;
    
    void onAttackAnimDone(const std::string& i_animName);
    bool IsContinueDamageForAirShip();
    
    bool IsAttactShipPrepareAnim();
    
    void PlayEatAirShipAnim();
    
    void ShowZombieHitShipEffect();
    
    void PlayPrepareEatShipAnim();
    
    void onAttackPrePareAnimDone(const std::string& i_animName);
    
    void PlayEndEatShipAnim();
    
    void onAttackEndAnimDone(const std::string& i_animName);
    
    void DoAttackShip();
    
private:
    bool m_bPlayEatAirShip;
    
    RtWeakPtr<class GridItemAirship> m_ptrLockAirShip;
    
    bool m_bDieOnAirShip;
};

class ZombieAnimRig_SkyCity : public ZombieAnimRig  //need obs follow ZombieSkyCity
{
public:
    
	RT_CLASS_DEFINE(ZombieAnimRig_SkyCity, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_SkyCity() {}
    
    virtual ~ZombieAnimRig_SkyCity() {}
    
    bool PlayEatAirShip();
    
    bool PlaySingleEatAirShip(AnimStoppedDelegate i_onAnimStopped);
    
    bool PlayPrepareEatShip(AnimStoppedDelegate i_onAnimStopped);
    
    bool PlayEndEatShip(AnimStoppedDelegate i_onAnimStopped);
    
    AnimHandle PlayOnAirShipDie();
    
protected:
    
    virtual const std::string getEatAirShipAnimationName();
    
    virtual const std::string getDieOnAirShipAnimationName();
    
    virtual const std::string getPrepareEatAirShipAnimationName();
    
    virtual const std::string getEndEatAirShipAnimationName();
    
    bool PlayEatShipWithDelegate(const std::string& strLabel, AnimStoppedDelegate i_onAnimStopped);
};


#endif
