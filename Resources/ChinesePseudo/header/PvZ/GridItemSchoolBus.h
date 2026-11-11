/*
 * GridItemSchoolBus.h
 *
 *  Created on: 2023-5-10
 *      Author: admin
 */

#ifndef GRIDITEMSCHOOLBUS_H_
#define GRIDITEMSCHOOLBUS_H_

#include "GridItemBoardEntityConditionTarget.h"
#include "Zombie.h"
#include "Projectile.h"
#include "ZombieLollipops.h"

enum SchoolBusState
{
	SchoolBusState_Idle,
	SchoolBusState_Move,
	SchoolBusState_Broken,
	SchoolBusState_BrokenMove,
	SchoolBusState_Attack
};

struct SchoolBusZombieDes
{
	SchoolBusZombieDes()
	: Level(1)
	, TypeName("pirate_imp")
	{

	}

	int Level;
	std::string TypeName;
};

struct GriditemSchoolBusParams
{
	GriditemSchoolBusParams()
	: SchoolBusHitPoints(3000.0f)
	, SchoolBusSpeed(0.185f)
	{

	}

    float			SchoolBusHitPoints;
    float 			SchoolBusSpeed;

	std::vector<SchoolBusZombieDes>	Zombies;
};

class GridItemSchoolBusProps : public GridItemBoardEntityConditionTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemSchoolBusProps, GridItemBoardEntityConditionTargetProps, RtClass);
	GridItemSchoolBusProps()
	{}
};

class GridItemSchoolBus : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemSchoolBus, GridItemBoardEntityConditionTarget, RtClass);

	GridItemSchoolBus();

public:
	void SetSchoolBusParams(GriditemSchoolBusParams i_params);
	static GridItemSchoolBus* AddSchoolBusWithParams(const std::string& i_gridItemTypeName, int i_gridX, int i_gridY, GriditemSchoolBusParams i_params, int i_level = 1);
	void TakeDamage(const DamageInfo& i_damage) override;

	void SetBusState(SchoolBusState i_state);
	SchoolBusState GetBusState() { return m_state; }
	bool IsDamaged() { return m_hasDamaged; }

protected:

	virtual void updateOthers() {}
	void updateState();
	virtual void onAttack() {}
	virtual void onUpdateAttack() {}

	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void onGridItemInitialize() override;

	void onUpdate() override;
	void onDraw(Graphics* i_g) override;
    void updatePosition() override;
    Sexy::Rect calcCollisionRect() override;
	void SetFlyingDestinationWithTravelTime(Zombie* zombie, const SexyVector3 i_destination, const float i_timeToTravel, const float i_apex = 64.0f, bool i_invincibleWhileInAir = false);
	virtual void onSchoolBusBroken();

    virtual void crushEntities();
    bool isDoneMoving() const override;

    SexyVector2 getNextBoardPosition() override;
    bool isSameLocation(const Sexy::Point& i_atLocation) override;
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
    void spawnImp(const SchoolBusZombieDes i_zombieDes,const int i_row);
    void drawSchoolBusAnim(Graphics* i_g);

    float		m_schoolBusHitPoints;
    float 		m_schoolBusSpeed;

	std::vector<SchoolBusZombieDes>		m_zombies;
	bool 		m_hasBroken;
	bool 		m_hasDamaged;

private:
	void checkEdge();
	void onBrokenAnimDone(const std::string& i_animLabelName);
	void updateBrokenMove(pvztime_t i_dt);

	SchoolBusState m_state;
	SexyVector3 m_brokenVelocity;
	int m_distance;
};

class GridItemSchoolBusAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemSchoolBusAnimRig, PopAnimRig, RtClass);

    GridItemSchoolBusAnimRig() {}

    void PlayMove();
    void PlayBrokenMove();
    void PlayBroken(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

class GridItemSchoolBusSpecial : public GridItemSchoolBus
{
public:
	RT_CLASS_DEFINE(GridItemSchoolBusSpecial, GridItemSchoolBus, RtClass);

	GridItemSchoolBusSpecial();

protected:
	void onAttack() override;
	void onUpdateAttack() override;
	void onGridItemInitialize() override;
	void updateOthers() override;

private:
	void startSpawnAnim();
	void onSpawnAnimDone();
	void onShoot();
	void onLaunch();
	void TakeShoot(class Plant *i_targetPlant);
	void checkForAirbubbleRelease();
	class Plant* findPlantForAirbubbleToAttack();
	void OnAirbubbleLaunched();
	void throwLollipop(const Point& i_gridLoc);
	bool findTargetPosition(Point& o_targetPoint);
	bool isPendingGraveAt(int i_gridX, int i_gridY);
	bool isTombraiserZombieAt(int i_gridX, int i_gridY);
	ProjectilePropertySheetPtr getLollipopProjectileType();
	bool isInExistPosition(const Point& i_point);

	bool        m_attacked;

	float       m_airbubbleHealth;
	pvztime_t   m_airbubbleLaunchTime;
	PlantPtr    m_target;
	ZombiePtr   m_airbubblePtr;

	int 		m_previousCol;
	std::vector<Point> 		m_throwingTargets;
	std::vector<SpellBolt> m_pendingGraves;
	bool		m_firstThrown;
};

class GridItemSchoolBusSpecialAnimRig : public GridItemSchoolBusAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemSchoolBusSpecialAnimRig, GridItemSchoolBusAnimRig, RtClass);

    GridItemSchoolBusSpecialAnimRig();

    typedef RtReflectionDelegate<Delegate0> PowerAnimDoneReflectionDelegate;
	typedef RtReflectionDelegate<Delegate0> ShootAirbubbleReflectionDelegate;
	typedef RtReflectionDelegate<Delegate0> LaunchAirbubbleReflectionDelegate;

	bool PlayPowerAnim(bool i_broken, PowerAnimDoneReflectionDelegate i_onAnimDone, ShootAirbubbleReflectionDelegate i_airbubble,
			LaunchAirbubbleReflectionDelegate i_launchBubble);
	virtual void onAnimStopped() override;
	virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;

	PowerAnimDoneReflectionDelegate m_onAnimDone;
	ShootAirbubbleReflectionDelegate m_airbubble;
	LaunchAirbubbleReflectionDelegate m_launchBubble;

private:
	SchoolBusState m_state;
};

#endif /* GRIDITEMSCHOOLBUS_H_ */
