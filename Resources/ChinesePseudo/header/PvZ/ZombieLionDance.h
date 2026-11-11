//
//  ZombieLionDance.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-1-12.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLionDance__
#define __PlantsVersusZombies2__ZombieLionDance__

#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieLionDanceState, ZombieState)
   ZS_LionDance_MoveUpDown,
STATE_ENUM_END(ZombieLionDanceState)

class ZombieLionDance : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieLionDance, Zombie, RtClass);
    virtual bool CanBeFlicked() const override { return false; }
    virtual bool CanBeBlovered() const override { return false; }
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual Rect CalcZombieAttackRect() override;
    virtual bool CanBeStabbed() const override { return false; }    
    virtual void DropAllLoot() override;
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Idle);
    OVERRIDE_STATE_ONENTER(ZombieState, Attack);
    OVERRIDE_STATE_UPDATE(ZombieState, Attack);
    OVERRIDE_STATE_ONEXIT(ZombieState,  Attack);
    DECLARE_STATE_FUNCTIONS(ZombieState, MoveUpDown);
    
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    virtual void registerForEvents() override;
    virtual void onAttackAnimStopped(const std::string& i_animLabel) override;
    virtual void onTurnedToAsh() override;
    virtual std::vector<BoardEntityPtr> findAttackTargets() override;
    virtual bool allowElectrocuteState() const override { return false; }
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
private:
    void OnZombieMoveUpDownFinish(Zombie* zombie);
    void PlayFireEffect();
    void PlayAshEffect(const SexyVector2& offset, const std::string& effectName);
    bool HasReachMaxColumn();
private:
    pvztime_t m_moveElapsedlTime;
    pvztime_t m_attackElapsedTime;
    pvztime_t m_moveInterval;
    pvztime_t m_attackInterval;
    bool m_bOnBoard;
};

class ZombieLionDanceProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieLionDanceProps, ZombiePropertySheet, RtClass);
    
    ZombieLionDanceProps()
    {
        MaxColumnReach = 5;
        MoveTime = 2.0;
    }
    pvztime_t MoveTime;
    ValueRange MoveInterval;
    ValueRange AttackInterval;
    int MaxColumnReach;
};



#endif /* defined(__PlantsVersusZombies2__ZombieLionDance__) */
