//
//  ZombieZombossMech_PVZ1_Robot.h
//  PlantsVersusZombies2
//


#ifndef __ZOMBIEZOMBOSSMECH_PVZ1_ROBOT__
#define __ZOMBIEZOMBOSSMECH_PVZ1_ROBOT__

#include "EffectObject.h"
#include "GameSubSystem.h"
#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"

class ZombossRocket;

namespace Message
{
	void BreakFireBallOnScreen();
	void BreakIceBallInGridRect(Rect& i_gridRect);
	void FreezeZombossRobot(GameObject* i_instigator, float i_duration);
}

class ZombieZombossMechPVZ1RobotProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechPVZ1RobotProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechPVZ1RobotProps()
	{
		NumRocketGravestones = 2;
		FrozenDuration = 5.f;
		MaxDamageAmount = 500.f;
	}

	int NumRocketGravestones;
	ProjectilePropertySheetPtr BoneProjectileType;

	float FrozenDuration;
	float MaxDamageAmount;

	std::vector<RtWeakPtr<ZombieActionDefinition>> SpecialActionSequence;
	std::vector<RtWeakPtr<ZombieActionDefinition>> DebugActions;

};

class ZombieZombossMech_PVZ1_Robot : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_PVZ1_Robot, ZombieZombossMech, RtClass);
    
    ZombieZombossMech_PVZ1_Robot();
	
	void OnRocketHitGround(ZombossRocket* i_rocket) override;
    
	void onPlaceOnBoard() override;
    void DropAllLoot() override;
    void onDestroy() override;
	void setExtraTranslateY(int i_translateY) { m_extraAnimTranslateY = i_translateY; }

private:
	void getFreeSpacesNear(const Point& i_target, std::vector<Point>& o_freeSpaces) const;
	void pickRandomSpacesFrom(int i_numSpaces, const std::vector<Point>& i_allSpaces, std::vector<Point>& o_pickedSpaces) const;
	void tossGravestone(const Point& i_source, const Point& i_target);
    
    void OnZombieZombossDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onFreezeZombossRobot(GameObject* i_instigator, float i_duration);

    void onZombieInitialize() override;
    int CalcRenderOrder() const override;
    void onApplyCondition(ZombieConditions i_condition) override;
    void onEndCondition(ZombieConditions i_condition) override;

    class ZombossRobotSpitOutBallActionHandler* getSpitOutBallActionHandler();

    bool performRandomZombossAction() override;
    RtWeakPtr<ZombieActionDefinition> pickNextLoopAction();

    void onStartedNewStage(int i_newStageIndex) override;
    int getLastActionIndex();
    void onCompletedSkillCycle();

    void initLoopActionPool();
    void setLoopActionPoolOverride(std::vector<RtWeakPtr<ZombieActionDefinition>> i_overrideActions);
    void clearOverrideLoopActionPool();

    void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) override {};

    void onUpdate() override;
    void onDraw(class Sexy::Graphics* i_g) override;
    void TakeDamage(const DamageInfo& i_damageReceived) override;
    void Retreat(ZombieState i_endState) override;
    bool ShouldDrawShadow() const override { return false; }
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

    OVERRIDE_STATE_ONEXIT(ZombieState, ZombossIntro);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, ZombossStageChange);


    std::vector<RtWeakPtr<ZombieActionDefinition>> m_loopActionPool;
    std::vector<RtWeakPtr<ZombieActionDefinition>> m_loopActionPoolOverride;
    bool m_useLoopActionPoolOverride = false;
    int m_lastActionIndex = -1;
    int m_hasCompletedSkillCycle = 0;
    bool m_isUsingSpecialSkillCycle = false;

    float m_extraAnimTranslateY = 0.f;
};

//
//	class_ZombieAnimRig_ZombossMech_PVZ1_Robot
//
class ZombieAnimRig_ZombossMech_PVZ1_Robot : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_PVZ1_Robot, ZombieAnimRig_ZombossMech, RtClass);

	const char* getStunAnimName() const override { return ""; }
	const char* getStunLoopAnimName() const override { return ""; }
	const char* getStunEndAnimName() const override { return ""; }

//	std::string getSpawnNormalZombieAnimName(int i_row) { return StrFormat("spawn_normal_zombie_%d", i_row); }
	std::string getSpawnNormalZombieAnimName(int i_row) { return "spawn_normal_zombie"; }

	std::string getRobotGetDownAnimName() { return "get_down"; }
	std::string getRobotDownIdleAnimName() { return "down_idle"; }
	std::string getRobotMoveAnimName(int i_row, bool i_isBack) { return StrFormat("move_%d_%s", i_row, i_isBack ? "back" : "go"); }
	std::string getSpitBallAnimName(bool i_isIceBall) { return StrFormat("spit_%s_ball", i_isIceBall ? "ice" : "fire"); }
	std::string getSpitBallCommand() { return "spit"; }
	std::string getRobotStandUpAnimName() { return "stand_up"; }

	std::string getRobotThrowCarAnimName() { return "throw_car"; }
	std::string getRobotThrowCarCommand() { return "throw"; }

	std::string getRobotReachOutAnimName() { return "reach_out"; }
	std::string getRobotReachOutIdleAnimName() { return "reach_out_idle"; }
	std::string getRobotRetractHandAnimName() { return "retract_hand"; }

	std::string getRobotTrampleAnimName(int i_row) { return StrFormat("trample_%d", i_row); }
	std::string getRobotTrampleCommand() { return "trample"; }

	void onPopAnimInitialized() override;
	void SetDamagePhase(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) override;
	DamagePhase getDamagePhase() { return m_damagePhase; }
	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;

	DamagePhase m_damagePhase = DamagePhase_0;
};


//
//	class_ZombossRobotBaseZombieActionDefinition
//
class ZombossRobotBaseZombieActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRobotBaseZombieActionDefinition, ZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	float IdleDurationFirst = 0;
};

//
//	class_ZombossRobotBaseZombieActionHandler
//
class ZombossRobotBaseZombieActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRobotBaseZombieActionHandler, ZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onIdleContinued(const std::string&, const std::string&, int);

	virtual void startNextAction() {}
	virtual void endThisAction();
	bool isEnding() { return m_thisActionDone; }

	pvztime_t m_nextStartTime = PVZ_EOT();
	bool m_thisActionDone = false;
};

struct ZombossRobotSpawnZombieInfo
{
	std::string ZombieTypeName = "";
	int			Weight = 100;

	int 		Level = 1;
	int			Row = -1;
	bool		HasPlantfood = false;

    bool operator==(const ZombossRobotSpawnZombieInfo& info) const
    {
        return ZombieTypeName == info.ZombieTypeName &&
        		Row == info.Row &&
        		Level == info.Level &&
        		HasPlantfood == info.HasPlantfood &&
        		Weight == info.Weight;
    }
};

//
//	class_ZombossRobotSpawnNormalZombieActionDefinition
//
class ZombossRobotSpawnNormalZombieActionDefinition : public ZombossRobotBaseZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRobotSpawnNormalZombieActionDefinition, ZombossRobotBaseZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float 										IdleDurationFirst = 0;
	int 										SpawnTimes = 3;
	float 										TimeInterval = 5;
	std::vector<ZombossRobotSpawnZombieInfo> 	SpawnZombieTypes;

};

//
//	class_ZombossRobotSpawnNormalZombieActionHandler
//
class ZombossRobotSpawnNormalZombieActionHandler : public ZombossRobotBaseZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRobotSpawnNormalZombieActionHandler, ZombossRobotBaseZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

	void startNextAction() override;

private:
	void playSpawnNormalZombieAnim();
	void playSyncAnimation();
	void spawnZombie();

	int pickRandomRowToSpawn();
	ZombossRobotSpawnZombieInfo pickRandowSpawnZombieInfo();

	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	void onSpawnNormalZombieAnimStoppedCallback(const std::string& i_animName);

	pvztime_t									m_nextSpawnTime = PVZ_EOT();
	std::vector<int> 							m_hasSpawnedZombieRow;
	ZombossRobotSpawnZombieInfo 				m_currentSpawnZombieInfo;
	int 										m_ompletedTimes = 0;

};

enum ZombossRobotBallType
{
	BALL_TYPE_FIRE,
	BALL_TYPE_ICE
};




/* ***********************************************************************/

//
//	class_GridItemZombossRobotBallProps
//
class GridItemZombossRobotBallProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemZombossRobotBallProps, GridItemAnimationProps, RtClass);

	ZombossRobotBallType BallTYpe = BALL_TYPE_FIRE;
	std::string			BreakAnimName = "";
	std::string			SpawnAnimation = "";
	std::string 		ScrollingAnimation = "";
	std::vector<std::string> DamageAbleEntityListToFireBall;
	std::vector<std::string> DamageAbleEntityListToIceBall;
};

//
//	class_GridItemZombossRobotBall
//
class GridItemZombossRobotBall : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemZombossRobotBall, GridItemAnimation, RtClass);

	void onGridItemInitialize() override;
	void onUpdate() override;
	void crushEntities();
	void checkAndCreateBurntEffect();
	void doBreaking();

	void registerForEvents() override;
	void onBreakFireBallOnScreen();
	void onBreakIceBallInGridRect(Rect i_gridRect);
	void onAnimStopped(const std::string& i_animLabel);

	void onDraw(Graphics* i_g) override;
	int	CalcRenderOrder() const override;

	void TakeDamage(const DamageInfo& i_damage) override;

	void initializeHitpoints(float i_hitpoints);

	bool m_hasBroken = false;
	bool m_isScrolling = false;
	pvztime_t m_trajectoriesTimer = PVZ_EOT();
};

//
//	class_ZombossRobotSpitBallActionDefinition
//
class ZombossRobotSpitBallActionDefinition : public ZombossRobotBaseZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRobotSpitBallActionDefinition, ZombossRobotBaseZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float 	IdleDurationFirst = 0;
	int		WeightOfFireBall = 50;
	int 	WeightOfIceBall = 50;
	float 	StayDurationBeforeBall = 5.f;
	float 	StayDurationAfterBall = 5.f;

	float 	MoveSpeed = 100.f;
	float 	BallHitpoints = 1200.f;
};


enum ZombossRobotSpitBallState
{
	ROBOT_BALL_STATE_INVALID,
	ROBOT_BALL_STATE_IDLE,
	ROBOT_BALL_STATE_GET_DOWN,
	ROBOT_BALL_STATE_DOWN_IDLE_PRE,
	ROBOT_BALL_STATE_MOVE_OUT,
	ROBOT_BALL_STATE_SPIT_BALL,
	ROBOT_BALL_STATE_MOVE_BACK,
	ROBOT_BALL_STATE_DOWN_IDLE_LAST,
	ROBOT_BALL_STATE_STAND_UP
};

//
//	class_ZombossRobotSpitBallActionHandler
//
class ZombossRobotSpitOutBallActionHandler : public ZombossRobotBaseZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRobotSpitOutBallActionHandler, ZombossRobotBaseZombieActionHandler, RtClass);

	void pushLeftTime();
	void popLeftTime();

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

	void startNextAction() override;

private:
	void playGetDownAnim();
	void playDownIdleAnim();

	void playStandUpAnim();
	void playSpitBallAnim();

	void playMoveAnim(int i_row, bool i_isBack);

	void spawnBall();

	int pickRandomRowToSpit();
	ZombossRobotBallType pickRandomBallType();

	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	void onSpitAnimStoppedCallback(const std::string& i_animName);

	void setState(ZombossRobotSpitBallState i_newState);

	pvztime_t	m_getDownTime = PVZ_EOT();
	pvztime_t	m_moveOutTime = PVZ_EOT();
	pvztime_t	m_standUpTime = PVZ_EOT();
	ZombossRobotBallType 	m_ballType = BALL_TYPE_FIRE;
	int 		m_ballRow = -1;

	ZombossRobotSpitBallState m_state = ROBOT_BALL_STATE_INVALID;
	pvztime_t m_endTime = PVZ_EOT();
	float m_leftTime = PVZ_EOT();
};

//
//	class_ZombossRobotCarProjectile
//
class ZombossRobotCarProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ZombossRobotCarProjectile, Projectile, RtClass);

	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;
	bool OnCollideRoof() override;
	void reBoundOut();
	void setStartPosition(SexyVector3 i_startPos) { m_startPosition = i_startPos; }
	void setEndPosition(SexyVector3 i_endPos);
	void crushEntities();

	SexyVector3 m_startPosition;
	SexyVector3 m_endPosition;
};


//
//	class_ZombossRobotThrowCarActionDefinition
//
class ZombossRobotThrowCarActionDefinition : public ZombossRobotBaseZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRobotThrowCarActionDefinition, ZombossRobotBaseZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float 	IdleDurationFirst = 0;
};

//
//	class_ZombossRobotThrowCarActionHandler
//
class ZombossRobotThrowCarActionHandler : public ZombossRobotBaseZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRobotThrowCarActionHandler, ZombossRobotBaseZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void startNextAction() override;
	Rect pickRandomCrushRect();
	void playThrowCarAnim();
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
//	void crushEntities();
	void onThrowCarAnimStoppedCallback(const std::string& i_animName);
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	void drawCrushRect(Sexy::Graphics *i_g);
	pvztime_t m_throwCarTime = PVZ_EOT();
	Rect m_crushRect = Rect();

};



class RappellingZombieInfo
{
public:
	RtWeakPtr<Zombie> ZombiePtr;
	SexyVector3 StartPosition;
	SexyVector3 Position;
	pvztime_t StartTime = PVZ_EOT();
	SexyVector3 Velocity;
	std::function<void(Zombie*)> LandedFunction;
};

//
//	class_ZombossRobotRappellingSubSystem
//
class ZombossRobotRappellingSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombossRobotRappellingSubSystem, GameSubSystem, RtClass);

	void Update() override;
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	void drawLine(Sexy::Graphics *i_g);

	void rappellingZombie(Zombie* i_zombie, SexyVector3 i_startPosition, float i_speed = 0, std::function<void(Zombie*)> i_landedFunction = nullptr);

private:
	std::vector<RappellingZombieInfo> m_rappellingZombieInfos;
	std::vector<RappellingZombieInfo> m_newRappellingZombieInfos;
	std::vector<RtWeakPtr<Zombie>> m_deadZombies;
};


class ZombossRobotAirDropZombieInfo
{
public:
	std::string ZombieTypeName = "";
	int			Weight = 100;
	int			Level = 1;
	bool		HasPlantfood = false;
	int			Column = -1;
	int			Row = -1;

	bool operator==(const ZombossRobotAirDropZombieInfo& info) const
	{
		return ZombieTypeName == info.ZombieTypeName &&
				Weight == info.Weight &&
				Level == info.Level &&
				HasPlantfood == info.HasPlantfood &&
				Column == info.Column &&
				Row == info.Row;
	}
};

//
//	class_ZombossRobotAirDropActionDefinition
//
class ZombossRobotAirDropZombieActionDefinition : public ZombossRobotBaseZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRobotAirDropZombieActionDefinition, ZombossRobotBaseZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float 	IdleDurationFirst = 0;
	float 	AirDropDuration = 0;
	int 	MinColumn = 1;
	int 	MaxColumn = 3;

	std::vector<ZombossRobotAirDropZombieInfo> AirDropZombiePool;
};

//
//	class_ZombossRobotAirDropActionHandler
//
class ZombossRobotAirDropZombieActionHandler : public ZombossRobotBaseZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRobotAirDropZombieActionHandler, ZombossRobotBaseZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void startNextAction() override;
	std::vector<ZombossRobotAirDropZombieInfo> pickRandomAirDropZombies();
	void playReachOutAnim();
	void playReachOutIdleAnim();
	void playRetractHandAnim();
//	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	void airDropZombies();
	SexyVector3 calcAirDropStartPosition(int i_gridX, int i_gridY, float i_spaceY);
	void onAnimStoppedCallback(const std::string& i_animName);
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	void drawDestinationRect(Sexy::Graphics *i_g);
//	void drawLine(Sexy::Graphics *i_g);
	pvztime_t m_reachOutTime = PVZ_EOT();
	pvztime_t m_retractHandTime = PVZ_EOT();
	std::vector<ZombossRobotAirDropZombieInfo> m_zombiesToDrop;

};



//
//	class_ZombossRobotTrampleActionDefinition
//
class ZombossRobotTrampleActionDefinition : public ZombossRobotBaseZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossRobotTrampleActionDefinition, ZombossRobotBaseZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float 	IdleDurationFirst = 0;
};

//
//	class_ZombossRobotTrampleActionHandler
//
class ZombossRobotTrampleActionHandler : public ZombossRobotBaseZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossRobotTrampleActionHandler, ZombossRobotBaseZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void startNextAction() override;
	Rect pickRandomCrushRect();
	void playTrampleAnim();
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	void crushEntities();
	void onTrampleAnimStoppedCallback(const std::string& i_animName);
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	void drawCrushRect(Sexy::Graphics *i_g);
	pvztime_t m_trampleCarTime = PVZ_EOT();
	Rect m_crushRect = Rect();
};



#endif /* __ZOMBIEZOMBOSSMECH_PVZ1_ROBOT__ */

