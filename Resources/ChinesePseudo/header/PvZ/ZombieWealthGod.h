//
//  ZombieWealthGod.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-1-14.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieWealthGod__
#define __PlantsVersusZombies2__ZombieWealthGod__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieWealthGodState, ZombieState)
    ZS_WealthGod_WakeUp,
    ZS_WealthGod_MoveUpDown,
STATE_ENUM_END(ZombieWealthGodState)

class ZombieWealthGod : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieWealthGod, Zombie, RtClass);
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual Rect CalcZombieAttackRect() override;
    virtual BoardEntity *findTarget() override;
    virtual bool CanBeFlicked() const override { return false; }
    virtual bool CanBeBlovered() const override { return false; }
    virtual bool CanBeStabbed() const override { return false; }
    virtual bool CanBeMowed() const override { return false; }
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Idle);
    OVERRIDE_STATE_ONENTER(ZombieState, Attack);
    OVERRIDE_STATE_UPDATE(ZombieState, Attack);
    OVERRIDE_STATE_ONEXIT(ZombieState,  Attack);
    OVERRIDE_STATE_UPDATE(ZombieState, Die);
    DECLARE_STATE_FUNCTIONS(ZombieState, WakeUp);
    DECLARE_STATE_FUNCTIONS(ZombieState, MoveUpDown);
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    virtual void registerForEvents() override;
    virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
    virtual void onAttackAnimStopped(const std::string& i_animLabel) override;
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override { return true; }
    virtual bool allowElectrocuteState() const override { return false; }
    virtual bool allowAshState() const override { return false; }
private:
    bool findTargetAndAttack();
    bool HasReachMaxColumn();
    bool IsAwake();
    void OnWakeUpDone(const std::string& i_animLabel);
    void OnZombieMoveUpDownFinish(Zombie* zombie);
    void FindTargetInRect(const Rect& rect, std::vector<BoardEntity*>& targets);
    BoardEntity* FindTargetInRect(const Rect& rect);
    void PlayEffect(const std::string& effectName, const std::string& animationName, const Point& position, int renderOrder);
    void DamageTarget(BoardEntity* target);
    class ZombieLionDance* FindZombieLionDance();
    bool CheckMoveUpDown();
    void UpdateDropCoin();
    void DropCoin();
    void DropRedPacket();
    pvztime_t CalcCoinDropInterval();
private:
    pvztime_t m_moveElapsedlTime;
    pvztime_t m_attackElapsedTime;
    pvztime_t m_moveInterval;
    pvztime_t m_attackInterval;
    pvztime_t m_coinDropInterval;
    pvztime_t m_coinDropElapsedTime;
    Rect m_attackRect;
    int m_rowMoveTo;
    AnimHandle	m_playingAnim;
    BoardEntityPtr m_target;
    const char* coinType = "super_coin_gold";
    bool       m_isOutMoveupDown;
};

class ZombieWealthGodProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieWealthGodProps, ZombiePropertySheet, RtClass);
    
    ZombieWealthGodProps()
    {
        MaxColumnReach = 5;
        MoveTime = 2.0;
        SpeedAwake = 0.185;
        SpeedEscape = 0.3;
        TotalCoin = 5000;
    }
    pvztime_t MoveTime;
    ValueRange MoveInterval;
    ValueRange AttackInterval;
    int MaxColumnReach;
    float SpeedAwake;
    float SpeedEscape;
    int TotalCoin;
};

enum ZombieAnimRigState_WealthGod
{
    ZOMBIEANIM_WEALTH_GOD_WAKE_UP = ZOMBIEANIM_USERDEFINED,
    ZOMBIEANIM_WEALTH_GOD_ESCAPE,
};

class ZombieAnimRig_WealthGod : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_WealthGod, ZombieAnimRig, RtClass);
    ZombieAnimRig_WealthGod();
    bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
    void PlayWakeUp(AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayEscape();
    bool IsAwake() { return m_isWake; }
protected:
    virtual const std::string getIdleAnimationName() override;
    virtual const std::string getWalkAnimationName() override;
private:
    bool m_isWake;
};

#endif /* defined(__PlantsVersusZombies2__ZombieWealthGod__) */
