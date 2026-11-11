//
//  ZombieGentleman.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 03/12/16.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieGentleman_h
#define PlantsVersusZombies2_ZombieGentleman_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"

STATE_ENUM_CHILD_BEGIN(ZombieSkiState, ZombieState)
    ZS_Ski_RushPre,
    ZS_Ski_RushSpeed,
    ZS_Ski_RushStop,
    ZS_Ski_UpGrade,
    ZS_Ski_FlyJump,
    ZS_Ski_FlyDrop,
STATE_ENUM_END(ZombieSkiState)

#define SKIANIM_LABEL_DEC(__sublabel__, __superfunc__) \
const std::string __superfunc__() override   \
{   \
if (m_ptrOwner && m_ptrOwner->CastChecked<ZombieGentleman>()->IsShiing()) \
{   \
return #__sublabel__;  \
}   \
return SuperClass::__superfunc__(); \
}

class ZombieGentlemanProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieGentlemanProps, ZombiePropertySheet, RtClass);
    
    int     ViewDistance;
    float   NorSkiSpeed;
    float   RushPreSpeed;
    float   RushSpeed;
    float   RushStopSpeed;
    float   SpaceCDTime;
    
};

class ZombieGentleman : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieGentleman, Zombie, RtClass);
    
    ZombieGentleman() : m_bSkiing(true), m_bHasUmbrella(true), m_jumpTime(0), m_IsDroped(false), m_isJumpFly(false) { }
    ~ZombieGentleman();
    bool IsShiing() const;
    bool IsHasUmbrella() const;
    void setIsHasUmbrella(bool isHasUmbrella);
    bool getIsDroped() const;

    bool isNotCanJumpOver(const BoardEntity* i_entity);

    void					onZombieTossDrop(Zombie* i_zombie);
    bool   getIsJumpFly() const { return m_isJumpFly; };
    void  setIsJumpFly(bool isJumpFly);
protected:
    
    void onZombieInitialize() override;
    
    void onUpdate() override;
    
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    DECLARE_STATE_FUNCTIONS(ZombieState, RushPre);
    DECLARE_STATE_FUNCTIONS(ZombieState, RushSpeed);
    DECLARE_STATE_FUNCTIONS(ZombieState, RushStop);
    DECLARE_STATE_FUNCTIONS(ZombieState, UpGrade);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyJump);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyDrop);
    
    int SearchFrontWalrusStatue();
    
    void CheckAndDoUpGrade();
    
    int32 ZombieTosserEnd();
    
    void DoThrowSkiTools();
    
    void LockState(bool bLock);
    
    float  ClacFlyXDistance();
    
private:
    bool m_bSkiing;
	pvztime_t m_jumpTime;
    bool      m_bHasUmbrella;
    bool m_IsDroped;
    bool m_isJumpFly;
};

class ZombieAnimRig_Gentleman : public ZombieAnimRig
{
public:
    
	RT_CLASS_DEFINE(ZombieAnimRig_Gentleman, ZombieAnimRig, RtClass);
    
    void SetOwner(const RtWeakPtr<GameObject>& ptr) { m_ptrOwner = ptr; }
    
    void PlayRushPre();
    
    void PlayRush();
    
    void PlayRushStop();
    
    void PlayUpGrade();
    
    void PlayFly();
    
    void PlayShortFly();
    
    void PlayLanding();
    
    void PlayShortLanding();

    void SetLayerVisibilityForCurrentState();

protected:
    
    //  SKIANIM_LABEL_DEC(zombie_skee_walk, getWalkAnimationName);
    
    //  SKIANIM_LABEL_DEC(seek_idle, getIdleAnimationName);

    virtual const std::string getWalkAnimationName() override;
    virtual const std::string getEatAnimationName() override;
    virtual bool PlayEat() override;
    
private:
    
    void OnRushPreEnd(const std::string& strLabel);
    
    void OnRushStopEnd(const std::string& strLabel);
    
    void OnUpGradeEnd(const std::string& strLabel);
    
    void OnLandDownEnd(const std::string& strLabel);
    
    void OnLandStandEnd(const std::string& strLabel);
    
    void SetOwnerState(ZombieState st);

    bool IsOwnerDying();

    
private:
    
    RtWeakPtr<GameObject> m_ptrOwner;
    int                   m_iCurCol = 0;
    int                   m_eSkiOldState = ZombieState_INVALID;
};

#endif
