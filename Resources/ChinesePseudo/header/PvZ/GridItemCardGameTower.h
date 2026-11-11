/*
 * GridItemCardGameTower.h
 *
 *  Created on: 2022-6-13
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMETOWER_H_
#define GRIDITEMCARDGAMETOWER_H_

#include <string>

#include "DamageInfo.h"
#include "DamageLifetime.h"
#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"
#include "RtDb.h"
#include "RtObject.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Rect.h"

// Card Game Tower State
enum CardGameTowerState
{
	CardGameTower_Invalid = -1,
	CardGameTower_Idle,
	CardGameTower_Attack,
	CardGameTower_End,
	CardGameTower_Max,
};


class GridItemCardGameTowerProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameTowerProps, GridItemAnimationProps, RtClass);

    GridItemCardGameTowerProps();

    std::string PopAnimIdleAnim;
    std::string PopAnimAttackAnim;
    std::string PopAnimEndAnim;
    float BaseDamage;
    Rect AttackRect;
    float AffectRadius;
};


// GridItemCardGameTower
class GridItemCardGameTower : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemCardGameTower, GridItemAnimation, RtClass);
    GridItemCardGameTower();

    void SetParentZombie(GridItemCardGameZombie* zombie);

protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    virtual bool CheckAttack();
    virtual Rect CalcAttackRect();
    virtual bool FindAttackTarget(int row, Rect attackRect);

    virtual void SetState(CardGameTowerState state);
    virtual void UpdateIdle();
    virtual void UpdateAttack();
    virtual void Attack();

    void DamageTarget(class BoardEntity* i_target);
    void CreateDamageEffect(class BoardEntity* i_target);
    void StopDamageEffect();
    void InitDamageEffect();
    virtual void DamageZombie(Zombie* zombie);
    virtual void DamageGridItem(GridItem* griditem);
    virtual void DamagePlant(Plant* plant);

    virtual float GetDamageAmount();

    virtual void PlayIdleAnim();
    virtual void PlayAttackAnim();
    virtual void PlayEndAnim();

    virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param);

protected:
    CardGameTowerState m_state;
    GridItemCardGameZombie* m_parentZombie;
    Rect m_attackRect;
    float m_baseDamage;
    class BoardEntity* m_lockedTarget;
    class LightningBolt* m_bolt;
};


#endif /* GRIDITEMCARDGAMETOWER_H_ */
