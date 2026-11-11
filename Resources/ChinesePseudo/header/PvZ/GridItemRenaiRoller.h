/*
 * GridItemRenaiRoller.h
 *
 *  Created on: 2019-7-27
 *      Author: Administrator
 */

#ifndef GRIDITEMRENAIROLLER_H_
#define GRIDITEMRENAIROLLER_H_

#include "RtDb.h"
#include "RtObject.h"
#include "GridItemJammable.h"

enum RollerSpeedLevel
{
	SPEED_LEVEL_1,
	SPEED_LEVEL_2,
	SPEED_LEVEL_3,
	SPEED_LEVEL_COUNT
};

class GridItemRenaiRollerProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemRenaiRollerProps, GridItemBreakableTargetProps, RtClass);

    GridItemRenaiRollerProps()
    {
    	AffectRadius = 0.0f;
    	AffectInterval = 1.0f;
    }
    virtual ~GridItemRenaiRollerProps() {}

    float AffectRadius;
    float AffectInterval;
    std::vector<float> AffectDamages;
    std::vector<float> SpeedLevels;
};

enum RollerState
{
    PVZ_BEGIN_ENUM(ROLLERSTATE_),
    ROLLERSTATE_IDLE,
    ROLLERSTATE_ROLLTODESTROY,
    ROLLERSTATE_ROLLTOLEFT,
    ROLLERSTATE_ROLLTORIGHT,
    ROLLERSTATE_STOPTOLEFT,
    ROLLERSTATE_STOPTORIGHT,
    PVZ_END_ENUM(ROLLERSTATE_)
};

enum RollerAnimState
{
	PVZ_BEGIN_ENUM(ROLLERANIMSTATE_),
	ROLLERANIMSTATE_ROLLTOLEFT,
	ROLLERANIMSTATE_ROLLTORIGHT,
	PVZ_END_ENUM(ROLLERANIMSTATE_)
};

class GridItemRenaiRoller : public GridItemBoardEntityConditionTarget
{
public:
    RT_CLASS_DEFINE(GridItemRenaiRoller, GridItemBoardEntityConditionTarget, RtClass);

    GridItemRenaiRoller();
    ~GridItemRenaiRoller();

    bool		IsDamageableByPlants() const override
				{ return false; }
    void		onGridItemInitialize() override;
    bool IsControlled() const override;

    bool IsDamageable() const override;

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

    void MoveOverTimeTo(const Sexy::Point& i_gridLocation, pvztime_t i_duration) override;

    bool isSameLocation(const Sexy::Point& i_atLocation) override;
    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    bool ShouldDrawShadow() const override;

    void FlyOutBoard(int i_gridY);

    void setSpeedLevel(RollerSpeedLevel i_level) { m_currentSpeedLevel = i_level; }
    void setState(RollerState i_state);
    RollerState getState();
    void updateState();
    void onUpdate() override;
    void onDraw(Graphics* i_g) override;

    void onRollAnimDone(const std::string& i_animLabelName);
    virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
    void registerForEvents() override;
    void onPostLoad() override;
    void stopMoving();
    bool canChangeState(RollerState i_state);
protected:
    Sexy::Rect calcCollisionRect() override;
    void onDrawShadow(class Sexy::Graphics* i_g) override;

    void onBreakAnimDone(const std::string& i_animLabelName);
    void onLinkedOnAnimDone(const std::string& i_animLabelName);
    void onRollerLoopAnimDone(const std::string& i_animLabelName);
    bool isDoneMoving() const override;
    void updatePosition() override;
    void onDestroy() override;
    SexyVector2	getRenderOffset() override;
private:
    float CalcRollTime(int i_col, int i_finalCol);
    bool IsInState(uint32 state) const { return m_state == state; }
    void drawRollerAnim(Graphics* i_g);
    void doRoll(bool i_left, bool i_fromIdle);
    void playLinkedAnim(bool i_on, RollerState i_preState);
    void playLinkedLoopAnim();
    void doReverseRoll(bool i_left, int i_finalCol);
    void adjustRollAnim(RollerAnimState i_animState, bool i_startup);
    void checkEdge();
    void checkCollision();
    void damageEntities();
    void resetValues();
    void checkStopLocation();
    bool reachFinalLocation(RollerState i_state);

    RollerState m_state;
    float m_rotation;
    pvztime_t m_affectTime;
    float m_finalStopX;
    RollerSpeedLevel m_currentSpeedLevel;
    RollerAnimState m_previousState;
};

class GridItemRollerAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemRollerAnimRig, PopAnimRig, RtClass);

    GridItemRollerAnimRig();

    void PlayIdle();
    void PlayRoll(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

namespace Message
{
    void NotifyRollerDestroy(GridItemRenaiRoller* i_roller);
    void NotifyKillPlant();
}


#endif /* GRIDITEMRENAIROLLER_H_ */
