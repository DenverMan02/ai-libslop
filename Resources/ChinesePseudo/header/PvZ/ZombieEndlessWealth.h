//
//  ZombieEndlessWealth.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16-10-17.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEndlessWealth__
#define __PlantsVersusZombies2__ZombieEndlessWealth__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieEndlessWealthState, ZombieState)
    ZS_EndlessWealth_MoveUpDown,
    ZS_EndlessWealth_Escape,
    ZS_EndlessWealth_Backward,
STATE_ENUM_END(ZombieEndlessWealthState)

class ZombieEndlessWealth : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieEndlessWealth, Zombie, RtClass);
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual void onEndCondition(ZombieConditions i_condition)  override;
    virtual Rect CalcZombieAttackRect() override;
    virtual BoardEntity *findTarget() override;
    virtual bool CanBeFlicked() const override { return false; }
    virtual bool CanBeBlovered() const override { return false; }
    virtual bool CanBeStabbed() const override { return false; }
    virtual bool CanBeMowed() const override { return false; }
    virtual bool IsDying() const override;
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_ONENTER(ZombieState, Idle);
    OVERRIDE_STATE_UPDATE(ZombieState, Idle);
    OVERRIDE_STATE_ONENTER(ZombieState, Attack);
    OVERRIDE_STATE_UPDATE(ZombieState, Attack);
    OVERRIDE_STATE_ONEXIT(ZombieState,  Attack);
    OVERRIDE_STATE_UPDATE(ZombieState, Die);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, MoveUpDown);
    DECLARE_STATE_FUNCTIONS(ZombieState, Escape);
    DECLARE_STATE_FUNCTIONS(ZombieState, Backward);
    
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

    void OnZombieMoveUpDownFinish(Zombie* zombie);
    void FindTargetInRect(const Rect& rect, std::vector<BoardEntity*>& targets);
    BoardEntity* FindTargetInRect(const Rect& rect);
    void PlayEffect(const std::string& effectName, const std::string& animationName, const Point& position, int renderOrder);
    void DamageTarget(BoardEntity* target);
    bool CheckMoveUpDown();
    void UpdateDropCoin();
    void DropCoin();
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
    int m_moveCount;
    pvztime_t m_moveStopTime;
    pvztime_t m_backwardTime;
    float m_backwardTotalLength;
    AnimHandle	m_playingAnim;
    BoardEntityPtr m_target;
    const char* coinType = "coin_gold";
    bool       m_isOutMoveupDown;
};

class ZombieEndlessWealthProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieEndlessWealthProps, ZombiePropertySheet, RtClass);
    
    ZombieEndlessWealthProps()
    {
        MaxColumnReach = 5;
        MoveTime = 2.0;
        SpeedAwake = 0.185f;
        SpeedEscape = 0.3f;
        BaseCoin = 1000;
        DropCoinRate = 0.5f;
        MoveCount = 3;
        MoveStopTime = 2.0f;
        BackwardTime = 1.0f;
        BackwardSpeed = 1.5f;
    }
    
    pvztime_t MoveTime;
    ValueRange MoveInterval;
    ValueRange AttackInterval;
    int MaxColumnReach;
    float SpeedAwake;
    float SpeedEscape;
    int BaseCoin;
    int MoveCount;
    float MoveStopTime;
    float BackwardTime;
    float BackwardSpeed;
    float  DropCoinRate;
    std::string DropCoinType1;
    float  DropCoinType1Rate;
    std::string DropCoinType2;
    float  DropCoinType2Rate;
};

enum ZombieAnimRigState_EndlessWealth
{
    ZOMBIEANIM_ENDLESSWEALTH_ESCAPE = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_EndlessWealth : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_EndlessWealth, ZombieAnimRig, RtClass);
    ZombieAnimRig_EndlessWealth();
    bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
    void PlayEscape();
protected:
    virtual const std::string getIdleAnimationName() override;
    virtual const std::string getWalkAnimationName() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEndlessWealth__) */
