/*
 * ZombieZombossMech_Steam.h
 *
 *  Created on: 2018-12-20
 *      Author: Administrator
 */

#ifndef ZOMBIEZOMBOSSMECH_STEAM_H_
#define ZOMBIEZOMBOSSMECH_STEAM_H_

#include "ZombieZombossMech_Pirate.h"
#include "ZombieAnimRig_ZombossMech.h"
#include "ZombieSteamCoalMiner.h"
#include "GridItemBoardEntityConditionTarget.h"
#include "EntityFinder.h"

class ZombossRocket;

class ZombossSteamImpCannonActionDefinition : public ZombossImpCannonActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamImpCannonActionDefinition, ZombossImpCannonActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSteamImpCannonActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamImpCannonActionHandler, ZombieActionHandler, RtClass);

	ZombossSteamImpCannonActionHandler()
		: m_endLoopingAt(PVZ_EOT())
	{}

protected:
	virtual void onStartAction() override;
	virtual void onUpdateAction() override;
	virtual void onEndAction() override;

private:
	void onRocketStartAnimDone(const std::string& i_animName);
	void onRocketLaunchAnimDone(const std::string& i_animName);
	void onRocketLaunchFireAnimDone(const std::string& i_animName);

	pvztime_t m_endLoopingAt;
};

#pragma mark Zomboss Steam Jump Action

class ZombossSteamJumpActionDefinition : public ZombossJumpActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamJumpActionDefinition, ZombossJumpActionDefinition, RtClass);

	ZombossSteamJumpActionDefinition()
	{}

	Point JumpTarget;
};

class ZombossSteamJumpActionHandler : public ZombossJumpActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamJumpActionHandler, ZombossJumpActionHandler, RtClass);

	ZombossSteamJumpActionHandler()
	{}
};

#pragma mark Zomboss Steam Random Jump Action

class ZombossSteamRandomJumpActionDefinition : public ZombossJumpActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamRandomJumpActionDefinition, ZombossJumpActionDefinition, RtClass);

	ZombossSteamRandomJumpActionDefinition()
	: MaxCol(0)
	, MaxRow(0)
	, CoalLevel(0)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	void GetRandomJumpTarget(Point& i_target, int i_maxCol, int i_maxRow, int i_width, int i_height) const;

	int MaxCol;
	int MaxRow;
	RtWeakPtr<ZombossSteamJumpActionDefinition> StartJumpAction;
	int CoalLevel;
};

enum CoalSteamZombossDeathType
{
	CoalSteamZombossDeathType_Normal,
	CoalSteamZombossDeathType_Fire,
	CoalSteamZombossDeathType_Cold
};

class GridItemCoalSteamZombossProps : public GridItemSteamCoalProps
{
public:
    RT_CLASS_DEFINE(GridItemCoalSteamZombossProps, GridItemSteamCoalProps, RtClass);
    GridItemCoalSteamZombossProps()
    {}

    std::vector<std::string> FirePlantList;
    std::vector<std::string> ColdPlantList;
};

class GridItemCoalSteamZomboss : public GridItemCoalSteam
{
public:
    RT_CLASS_DEFINE(GridItemCoalSteamZomboss, GridItemCoalSteam, RtClass);

    GridItemCoalSteamZomboss()
    : m_deathType(CoalSteamZombossDeathType_Normal)
    {

    }

    void NotifyDamageByIceburg();

protected:
    void onGridItemInitialize() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
    std::string GetAnimLabelName(GridItemCoalState i_state) override;
    void KillGridItem() override;
    void onTakeDamage(const DamageInfo& i_damage) override;
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    bool isValidFirePlant(const std::string& i_typeName);
    bool isValidColdPlant(const std::string& i_typeName);

    CoalSteamZombossDeathType m_deathType;
    DamageInfo m_lastDamageInfo;
};

class ZombossSteamRandomJumpActionHandler : public ZombossJumpActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamRandomJumpActionHandler, ZombossJumpActionHandler, RtClass);

	ZombossSteamRandomJumpActionHandler()
	{}

protected:
	void onLanding() override;
	void spawnCoals(int i_col, int i_row);
};

#pragma mark Zomboss Steam Rush Action

class ZombossSteamRushActionDefinition : public ZombossRushActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamRushActionDefinition, ZombossRushActionDefinition, RtClass);

	ZombossSteamRushActionDefinition()
	: ChargeCount(0)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;

	RtWeakPtr<ZombossSteamJumpActionDefinition> RushJumpAction;
	int ChargeCount;
};

class ZombossSteamRushActionHandler : public ZombossRushActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamRushActionHandler, ZombossRushActionHandler, RtClass);

	ZombossSteamRushActionHandler()
	: m_chargeCount(0)
	{}

protected:
	void registerForEvents() override;
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	void onRushPrepareAnimDone(const std::string& i_animName);
	void onChargeAnimDone(const std::string& i_animName);
	void onChargeEndAnimDone(const std::string& i_animName);
	void onRushEndAnimDone(const std::string& i_animName);
	void onRushStartAnimDone(const std::string& i_animName);
	void onChargeFailAnimDone(const std::string& i_animName);

	bool CheckRushingDone() override;

private:
	void startCharge();
	void finishCharge();
	void startRush();
	bool HasFinishedCharge();
	void onFreezeZombossRobot(GameObject* i_instigator, float i_duration);

	int m_chargeCount;
};

#pragma mark Zomboss Steam Fire Action

class PlantSorter_LowestHP
{
public:
	PlantSorter_LowestHP() {}

	bool operator()(const Point& i_a, const Point& i_b) const;
};

class ZombossSteamFireActionDefinition : public ZombossFireActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamFireActionDefinition, ZombossFireActionDefinition, RtClass);

	ZombossSteamFireActionDefinition()
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	bool pickRocketTargets(ZombieZombossMech *i_zomboss, std::vector<Point>& o_targetSquares) const override;
	bool HasEnoughTargets() const;

	RtWeakPtr<ZombossSteamJumpActionDefinition> FireJumpAction;
};

class ZombossSteamFireActionHandler : public ZombossFireActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamFireActionHandler, ZombossFireActionHandler, RtClass);

	ZombossSteamFireActionHandler()
	{}
};

#pragma mark Zomboss Steam Throw Action

class PlantSorter_HasPlant
{
public:
	PlantSorter_HasPlant() {}

	bool operator()(const Point& i_a, const Point& i_b) const;
};

class ZombossSteamThrowActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamThrowActionDefinition, ZombieActionDefinition, RtClass);

	ZombossSteamThrowActionDefinition()
	: ThrowCount(0)
	, ProjectileTimeOfFlight(1.2f)
	, ProjectileLobHeight(350.0f)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	void pickThrowTargets(ZombieWithActions *i_zomboss, std::vector<Point>& o_targetSquares, int i_pickCount) const;

	int ThrowCount;
	SexyVector3	ProjectileSpawnOffset;
	ProjectilePropertySheetPtr Projectile;
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

class ThrowCoalProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ThrowCoalProjectile, Projectile, RtClass);

	bool OnCollideGround() override;

private:
	void spawnCoals(int i_col, int i_row);
};

class ZombossSteamThrowActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamThrowActionHandler, ZombieActionHandler, RtClass);

	ZombossSteamThrowActionHandler()
	{}

	void onStartAction() override;
	void ThrowCoal();
	void SetThrowLocs(const std::vector<Point>& i_locs) { m_locs = i_locs; }
	void onThrowCoalAnimDone(const std::string& i_animName);
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	void LaunchProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);

	std::vector<Point> m_locs;
};

#pragma mark Zomboss Steam Spawn Action
// Zomboss opens a portal in front of the mech and spawns zombies in
// own row, in contrast to "Summon" which brings zombies forth all over.

class ZombossSteamSpawnActionDefinition : public ZombossSpawnActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamSpawnActionDefinition, ZombossSpawnActionDefinition, RtClass);

	ZombossSteamSpawnActionDefinition()
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
};

class ZombossSteamSpawnActionHandler : public ZombossSpawnActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamSpawnActionHandler, ZombossSpawnActionHandler, RtClass);

	ZombossSteamSpawnActionHandler()
	{}
};

#pragma mark Zomboss Steam Rest Action

class ZombossSteamRestActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamRestActionDefinition, ZombieActionDefinition, RtClass);

	ZombossSteamRestActionDefinition()
	: MaxRepeatJumpNum(0)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	Point GenerateRandomJump(ZombieWithActions* i_zomboss, const Point& i_srcPoint, std::vector<RtWeakPtr<class ZombieActionHandler>>& i_actions) const;
	Point GetRandomPoint(const Point& i_srcPoint) const;

	RtWeakPtr<ZombossSteamJumpActionDefinition> FirstJumpAction;
	int MaxRepeatJumpNum;
	Point FirstJumpTarget;
};

class ZombossSteamRestActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamRestActionHandler, ZombieActionHandler, RtClass);

	ZombossSteamRestActionHandler()
	{}

	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

	std::vector<RtWeakPtr<class ZombieActionHandler>> m_actions;
};

#pragma mark Zomboss Steam Train Spawn Action
// Zomboss opens a portal in front of the mech and spawns zombies in
// own row, in contrast to "Summon" which brings zombies forth all over.

class ZombossSteamTrainSpawnActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSteamTrainSpawnActionDefinition, ZombieActionDefinition, RtClass);

	ZombossSteamTrainSpawnActionDefinition()
	: TrainSpawnLevel(1)
	{}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zomboss) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	RtWeakPtr<ZombossSteamJumpActionDefinition> SpawnJumpAction;
	int TrainSpawnLevel;
};

enum SteamZombiePortalState
{
	SteamZombiePortalState_Init,
	SteamZombiePortalState_Opening,
	SteamZombiePortalState_Opened,
	SteamZombiePortalState_Closing,
	SteamZombiePortalState_Closed
};

struct SteamZombiePortalInfo
{
	SteamZombiePortalInfo()
	: PortalState(SteamZombiePortalState_Init)
	{

	}

	SteamZombiePortalState PortalState;
	RtWeakPtr<class EffectAnimRig_ZombiePortal> PortalAnim;
	Point Location;
};

class ZombossSteamTrainSpawnActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSteamTrainSpawnActionHandler, ZombieActionHandler, RtClass);

	ZombossSteamTrainSpawnActionHandler()
	: m_zombiePortalClosedTime(PVZ_EOT())
	, m_trainMoved(false)
	{}

    void AddToRenderQueue(class RenderQueue* i_queue) override;

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	void registerForEvents() override;

private:
	void onNotifySteamTrainMoving();
	void drawZombieSpawnPortal(Sexy::Graphics* i_graphics);

	void onPortalStartAnimDone(const std::string& i_animName);
	void onPortalStopAnimDone(const std::string& i_animName);
	void onZombiePortalOpenAnimDone(const std::string& i_animName);
	void onZombiePortalCloseAnimDone(const std::string& i_animName);

	void createZombiePortal(int i_col, int i_row);
	void spawnTrains();

	std::vector<SteamZombiePortalInfo> m_zombiePortalAnim;
	pvztime_t m_zombiePortalClosedTime;
	bool m_trainMoved;
};

// Trains
enum SteamTrainState
{
	SteamTrainState_Init,
	SteamTrainState_Idle,
	SteamTrainState_Move,
	SteamTrainState_Explode
};

class GridItemSteamTrainProps : public GridItemBoardEntityConditionTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemSteamTrainProps, GridItemBoardEntityConditionTargetProps, RtClass);
	GridItemSteamTrainProps()
	: SpeedPerGrid(1.0f)
	, Damage(1.0f)
	, HitpointsPercent(0.2f)
	, WaitingTime(1.0f)
	, DamageStateCount(2)
	{}

	float SpeedPerGrid;
	float Damage;
	float HitpointsPercent;
	float WaitingTime;
	int8 DamageStateCount;
};

class GridItemSteamTrain : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemSteamTrain, GridItemBoardEntityConditionTarget, RtClass);

	GridItemSteamTrain();

public:
	void SetTrainState(SteamTrainState i_state);
	SteamTrainState GetTrainState() { return m_state; }
	void SetStartCol(int i_col) { m_startCol = i_col; }
	int GetStartCol() { return m_startCol; }
	void SetMaxHP(float i_masterHP);

protected:
	void onTakeDamage(const DamageInfo& i_damage) override;
	void onKilled() override;
	int CalcRenderOrder() const override;

	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void onGridItemInitialize() override;

	void onUpdate() override;
	void onDraw(Graphics* i_g) override;
    Sexy::Rect calcCollisionRect() override;

    virtual void crushEntities();
    bool isDoneMoving() const override;

	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
    void drawSteamTrainAnim(Graphics* i_g);
    void onApplyDrawClipRect(class Sexy::Graphics *i_g) override;

private:
    void updateState();
	void checkEdge();
	bool reachEdge();
	int	calcDamageState();

	SteamTrainState m_state;
	int m_startCol;
	pvztime_t m_startMovingTime;
	int	m_currDamageState;
	int	m_damageStates;
};

class GridItemSteamTrainAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemSteamTrainAnimRig, PopAnimRig, RtClass);

    GridItemSteamTrainAnimRig() {}

    void PlayMove();
    void PlayIdle();
    void SetDamageState(int i_damageState);
};

class ZombieAnimRig_ZombossMech_Steam : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_Steam, ZombieAnimRig_ZombossMech, RtClass);

	ZombieAnimRig_ZombossMech_Steam()
	: m_rocketCount(0)
	{

	}

	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;

	void PlayImpCannonStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayImpCannonLaunch(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void PlayImpCannonLaunchLoop();
	void PlayImpCannonLaunchFire(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void PlayPrepareRushStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayCharge(int i_chargeCount, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayChargeEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayChargeFail(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRushEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRushStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayThrowCoal(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	const char* getRushForwardAnimName() const override;
	const char* getRocketLaunchAnimName() const override;

	void SetRocketCount(int i_count) { m_rocketCount = i_count; }

	int m_rocketCount;
};

class ZombieZombossMechSteamProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechSteamProps, ZombieZombossMechProps, RtClass);
};

class ZombieZombossMech_Steam : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Steam, ZombieZombossMech, RtClass);

	ZombieZombossMech_Steam()
	: m_currentStageActionIndex(0)
	{

	}

	void SetCurrentImpCannonActionDef(ZombieActionDefinitionPtr i_actionDef);
	void OnRocketHitGround(ZombossRocket* i_rocket) override;

protected:
	void onStartedNewStage(int i_newStageIndex) override;
	bool performRandomZombossAction() override;
	bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
	bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
private:
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void launchCannonImps();
	void resetActionIndex();

	ZombieActionDefinitionPtr m_impCannonActionDef;

	int m_currentStageActionIndex;
};

namespace Message
{
	void NotifySteamTrainMoving();
}


#endif /* ZOMBIEZOMBOSSMECH_STEAM_H_ */
