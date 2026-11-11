/*
 * GridItemMazeStatue.h
 *
 *  Created on: 2019-11-11
 *      Author: Administrator
 */

#ifndef GRIDITEMMAZESTATUE_H_
#define GRIDITEMMAZESTATUE_H_

#include "RtDb.h"
#include "RtObject.h"
#include "GridItemJammable.h"

class GridItemMazeStatueProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemMazeStatueProps, GridItemBreakableTargetProps, RtClass);

    GridItemMazeStatueProps()
    {
    	BonusCredit = 0.0f;
    }
    virtual ~GridItemMazeStatueProps() {}

    float BonusCredit;
};

enum MazeStatueState
{
    PVZ_BEGIN_ENUM(MAZESTATUESTATE_),
    MAZESTATUESTATE_IDLE,
    MAZESTATUESTATE_ROTATING_RIGHT,
    MAZESTATUESTATE_ROTATING_LEFT,
    MAZESTATUESTATE_REVEALING,
    MAZESTATUESTATE_BREAKING,
    PVZ_END_ENUM(MAZESTATUESTATE_)
};

class GridItemMazeStatue : public GridItemBoardEntityConditionTarget
{
public:
    RT_CLASS_DEFINE(GridItemMazeStatue, GridItemBoardEntityConditionTarget, RtClass);

    GridItemMazeStatue();
    ~GridItemMazeStatue();

    bool		IsDamageableByPlants() const override
				{ return false; }
    void		onGridItemInitialize() override;
    bool IsControlled() const override;

    bool IsDamageable() const override;

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    int CalcRenderOrder() const override;

    void setState(MazeStatueState i_state);
    MazeStatueState getState();
    void updateState();
    void onUpdate() override;
    void onDraw(Graphics* i_g) override;

    virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
    void registerForEvents() override;
    void unregisterForEvents() override;
    void onPostLoad() override;
    void SetRadius(float i_radius) { m_radius = i_radius; }
    void SetStartDegree(float i_degree) { m_startDegree = i_degree; }
    void SetStartPosition(const SexyVector3& i_start) { m_startPosition = i_start; }
    void PrepareMoving(const SexyVector3& i_start, float i_startDegree, float i_radius, pvztime_t i_duration, MazeStatueState i_state);
    void SetTargetPosition(const Point& i_target) { m_targetPosition = i_target; }
    void ResetLocation();
    void SetTriggerTouch(bool i_trigger) { m_triggerTouch = i_trigger; }
    void SetIsTarget(bool i_target) { m_isTarget = i_target; }
    bool IsTarget() { return m_isTarget; }
protected:
    SexyVector2 getNextBoardPosition() override;
    void tryUpdatePosition() override;
    void updatePosition() override;
    bool isDoneMoving() const override;
    void onAnimEnded(const std::string &i_animLabel);
    void onDestroy() override;
private:
    bool IsInState(uint32 state) const { return m_state == state; }
    void drawStatueAnim(Graphics* i_g);
    void MoveOverTimeTo(float i_degree);
    void SetFinalPosition();
    bool onTouchEvent(const Sexy::Touch& i_touch);
    void onTouchCancelEvent();
    bool IsDisableForTouch();
    void BreakStatue();
    void RevealStatue();
    void onNotifyStatueReveal();
    void onNotifyStatueEnable(bool i_enable);
    void onNotifyStatueBreak();

    MazeStatueState m_state;
    pvztime_t		m_startTime;
    pvztime_t		m_endTime;
    float			m_startDegree;
    float			m_targetDegree;
    float 			m_radius;
    SexyVector3		m_startPosition;
    pvztime_t		m_duration;
    Point			m_targetPosition;
    Sexy::TouchID	m_owningTouchIdent;
    bool			m_touchHovering;
    bool			m_triggerTouch;
    bool			m_isTarget;
};

class GridItemMazeStatueAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemMazeStatueAnimRig, PopAnimRig, RtClass);

    GridItemMazeStatueAnimRig();

    void PlayIdle();
    void PlayBreak(bool i_target, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayReveal(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayClose(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

namespace Message
{
    void NotifyStatueDestroy(GridItemMazeStatue* i_statue);
    void NotifyStatueHit(float i_x, float i_y);
}

#endif /* GRIDITEMMAZESTATUE_H_ */
