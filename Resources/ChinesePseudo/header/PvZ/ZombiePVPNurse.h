//
//  ZombiePVPNurse.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-11-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombiePVPNurse__
#define __PlantsVersusZombies2__ZombiePVPNurse__

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombiePropertySheet.h"
#include "RestrictionSet.h"
#include "Projectile.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_PVPNurse, ZombieState)
ZS_PVPNurse_Treat,
STATE_ENUM_END(ZombieState_PVPNurse)

class ZombiePVPNurseProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePVPNurseProps, ZombiePropertySheet, RtClass);
    
    ZombiePVPNurseProps()
    {
        
    }
    
    std::vector<std::string> BoardDesZombies;
    ValueRange TimeBeforeFirstTreat;
    ValueRange TimeBetweenTreat;
    PlantRestrictionSet TargetablePlantTypes;
    int AddHP = 0;
    
    ProjectilePropertySheetPtr          Projectile;
};

class ZombiePVPNurse : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePVPNurse, Zombie, RtClass);
    
protected:
    void onZombieInitialize() override;
	void onUpdate() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void ApplyZombieFood() override;
    
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    OVERRIDE_STATE_UPDATE(ZombieState, Attack);
	DECLARE_STATE_FUNCTIONS(ZombieState, Treat);

private:
    
    bool IsValidTreatTarget(BoardEntityPtr ptrBoardEntity);
    
    bool IsArenaValidTreatTarget(BoardEntityPtr ptrBoardEntity);
    
    bool IsBoardValidTreatTarget(BoardEntityPtr ptrBoardEntity);
    
    std::vector<BoardEntityPtr> GetValidTreatTarget();
    
    std::vector<BoardEntityPtr> GetArenaValidTreatTarget();
    
    std::vector<BoardEntityPtr> GetBoardValidTreatTarget();
    
    void onTreatAnimationDone(const std::string& i_animName);
    
    void DoConfirmTarget();
    
    bool IsArenaBattle();
    
    bool IsZombieInPool(Zombie* pZombie);
    
    float GetTimeBeforeFirstTreat();
    
    float GetTimeBetweenTreat();
    
private:
    
    pvztime_t m_nextTreatTime = PVZ_EOT();
    std::vector<BoardEntityPtr> m_vptrBoardEntityTargets;
    
};

////////////

enum ZombieAnimRigState_PVPNurse
{
	ZOMBIEANIM_PVPNURSE_TREAT = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_PVPNurse : public ZombieAnimRig
{
public:
    
    RT_CLASS_DEFINE(ZombieAnimRig_PVPNurse, ZombieAnimRig, RtClass) {}
    
	bool StartTreat(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
};

class PVPNurseProjectile : public Projectile
{
    
public:
    
    RT_CLASS_DEFINE(PVPNurseProjectile, Projectile, RtClass);
    
    PVPNurseProjectile()
    : m_bQuite(false)
    , m_iRemainAngle(0)
    , m_iRemainAngleSpeed(0)
    , m_bArenaBattle(false)
    {}
    
    void moveThroughTime(pvztime_t i_dt) override;
    
    bool OnCollideGround() override;
    
    void SetEndTime(pvztime_t iEndTime) { m_iEndTime = iEndTime; }
    
    void SetAddHP(int iAdd) { m_iAddHP = iAdd; }
    
    void SetIsArenaBattle(bool bArena) { m_bArenaBattle = bArena; }
    
    void DoArenaCollideProcess();
    
    void DoBoardCollideProcess();
    
private:
    
    bool m_bQuite;
    
    bool m_bArenaBattle;
    
    pvztime_t m_iEndTime;
    
    float m_iRemainAngle;
    
    float m_iRemainAngleSpeed;
    
    int m_iAddHP;
    
};

#endif /* defined(__PlantsVersusZombies2__ZombiePVPNurse__) */
