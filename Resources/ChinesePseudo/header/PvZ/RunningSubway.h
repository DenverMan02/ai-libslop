/*
 * RunningSubway.h
 *
 *  Created on: 2023-5-30
 *      Author: admin
 */

#ifndef RUNNINGSUBWAY_H_
#define RUNNINGSUBWAY_H_

#include "StageModule.h"
#include "LevelModule.h"
#include "UIWidget.h"
#include "InitialGridItemPlacer.h"
#include "ChallengeUI.h"
#include "PopAnimRig.h"
#include "PVZ2UIButton.h"
#include "GridItemJammable.h"
#include "BoardRegion.h"
#include "UIEasyButtonWidget.h"

enum RunningSubwayObjectType
{
	RunningSubwayObject_Coin = 1,
	RunningSubwayObject_Obstacle
};

struct RunningPlayerInitInfo
{
	RunningPlayerInitInfo()
	: StartSpeed(0.0f)
	, StartHitPoints(1)
	, SkillActivateEnergyCount(0)
	, SkillSpeedMultiplier(0.0f)
	, SkillDuration(0.0f)
	, SkillInitEnergy(0)
	, MoveRate(1.0f)
	{

	}

	float StartSpeed;
	int StartHitPoints;
	int SkillActivateEnergyCount;
	float SkillSpeedMultiplier;
	float SkillDuration;
	int SkillInitEnergy;
	float MoveRate;
	Rect CollisionRect;
};

class RunningSubwayStage : public StageModule
{
public:
	RT_CLASS_DEFINE(RunningSubwayStage, StageModule, RtClass);

	RunningSubwayStage();
	virtual ~RunningSubwayStage();

    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:

    void initializeModule()  override;
	void registerForEvents() override;

    void renderRunBackground(Graphics* i_g);

    virtual void onLevelLoaded() override;

private:
    void generateDisabledRegion();
    void updateGridSquare(Rect i_rect);
    void addBackgroundToRenderQueue(class RenderQueue* i_queue);
    void onUpdate();
    void onGameplayStarted();
    void onNotifySpeedChanged(float i_speed);

private:
    int                         m_offset_x;
    float						m_rollValue;
};

class RunningSubwayStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(RunningSubwayStageProperties, StageModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return RunningSubwayStage::StaticGetClass();
	}

	RunningSubwayStageProperties();
};

// Character
STATE_ENUM_BASE_BEGIN(RunningPlayerState)
	RunningPlayerState_IDLE,
	RunningPlayerState_JUMPOUT,
	RunningPlayerState_PREPARE_RUN,
	RunningPlayerState_RUN,
	RunningPlayerState_DEAD,
STATE_ENUM_END(RunningPlayerState);

enum RunningPlayerMoveDirection
{
	RunningPlayerMoveDirection_UP,
	RunningPlayerMoveDirection_DOWN
};

class RunningPlayer : public BoardEntity
{
public:
    RT_CLASS_DEFINE(RunningPlayer, BoardEntity, RtClass);

    RunningPlayer();
    virtual ~RunningPlayer();

    void RunningPlayerInitialize(PopAnim* i_popAnim);

    void StartMove();

    Rect GetRunningPlayerRect();
    virtual int CalcRenderOrder() const override;

    bool isInState(RunningPlayerState i_state) const;
    void setState(RunningPlayerState i_newState);
    RunningPlayerState getState();

    void SetNextPosition(SexyVector3 nextPos);
    Sexy::SexyVector3 GetNextPosition();

    bool canMove();
    void SetWalkingRate(float i_rate);
    float GetWalkingRate();
    void SetIsMoving(bool i_moving);
    void Update();

    void PlayIdleLooped();
    void PlayJumpOut();
    void PlayPrepareRun();
    void WalkToNext();
    void PlayJumpOnBoard();
    void PlayJumpOffBoard();
    void PlayBoardRush();

    bool IsInSpecial() { return m_isInSpecial; }
    void SetInSpecial(bool i_special);

    Sexy::Point CalcRealGridPosition() const;

    virtual SexyVector2 GetDrawOffet();

protected:
    /// GameObject interface
    virtual void onInitialized() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onDraw(Graphics* i_g) override;
    //virtual void onDrawShadow(Graphics* i_g);
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;

    virtual void initializePAM(PopAnim* i_popAnim);
    virtual void onAnimStopped(const std::string& i_animName);
    void onJumpOnBoard(const std::string &i_animName);
    void onJumpOffBoard(const std::string &i_animName);

private:

    int32 getRunningPlayerStateSerialization();
    void setRunningPlayerStateSerialization(int32 i_state);

    // Snake State Machine
    DECLARE_STATE_FUNCTIONS(RunningPlayerState, IDLE);
    DECLARE_STATE_FUNCTIONS(RunningPlayerState, JUMPOUT);
    DECLARE_STATE_FUNCTIONS(RunningPlayerState, PREPARERUN);
    DECLARE_STATE_FUNCTIONS(RunningPlayerState, RUN);
    DECLARE_STATE_FUNCTIONS(RunningPlayerState, DEAD);
private:
    SexyVector3                                 m_startPosition;
    SexyVector3                                 m_nextPosition;
    pvztime_t                                   m_startingMovingTime;
    float                                       m_walkingRate;
    bool                                        m_isMoving;
    StateMachine<RunningPlayerState>   			m_runningPlayerState;

    bool										m_isInSpecial;

protected:
    RtWeakPtr<class PopAnimRig>                 m_popAnimRig;
};

// Module

struct GridItemTrackInfo
{
	GridItemTrackInfo()
	{

	}

	GridItemTrackInfo(GridItemPtr i_gridItem, Point i_location)
	: GridItem(i_gridItem)
	, Location(i_location)
	{

	}

	GridItemPtr GridItem;
	Point		Location;
};

struct RunningSkillInfo
{
	RunningSkillInfo()
	: m_skillEndTime(0.0f)
	, m_currentEnergyCount(0)
	, m_speedMultiplier(0.0f)
	{

	}

	pvztime_t m_skillEndTime;
	int m_currentEnergyCount;
	float m_speedMultiplier;
};

class RunningSubwayModule : public LevelModule
{
public:

    RT_CLASS_DEFINE(RunningSubwayModule, LevelModule, RtClass);

    RunningSubwayModule();
    ~RunningSubwayModule();

    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    const class RunningSubwayModuleProperties * GetRunningSubwayModuleProps();

    void RunningPlayerMoveTo(RunningPlayerMoveDirection i_move);

    float GetBaseSpeed();
    void SetCurrentSpeed(float i_speed);
    float GetCurrentSpeed() { return m_currentSpeed; }
    void SetSpeedValue(float i_speedValue) { m_currentSpeedValue = i_speedValue; }
    int GetBaseHitPoints();
    float GetMoveRate();
    Rect GetPlayerCollisionRect() const;

    int GetScorePerGrid();
    int GetBaseSkillEnergyCount();
    int GetSkillEnergyActivateCount();
    float GetBaseSkillSpeedMultiplier();
    float GetSkillDuration();
    void SetCurrentSkillEnergyCount(int i_count);
    int GetCurrentSkillEnergyCount() { return m_currentSkill.m_currentEnergyCount; }

    void AddCurrentScore(int i_score);

    class RunningSubwaySkillButton* GetSkillButton();

    Rect CalcRunningPlayerSelfRect() const;

protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void postInitialize() override;

    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();

    bool canMove(bool i_up, const Point& i_location);

    void trySpawnRunningPlayer();
    RunningPlayer* CreateRunningPlayer();
    std::string GetRunningPlayerPam();
    bool		IsRiderKilled();
	void        onRunningPlayerDying();
	void		InitRunningPlayer(RtWeakPtr<PopAnim> i_animPtr);

	RunningPlayer* m_player;

	void        onRunningPlayerKilled();
	void        onRunningPlayerDied();
	void 		onTargetFailed();
	void 		onNotifyStartRunning();
	void 		onNotifyJumpOnBoard();
	void 		onNotifyJumpOffBoard();
	void 		onNotifyActivateSkill();

private:
	bool reachTarget();

	SexyVector3 calcRunningPlayerNextPosition(RunningPlayerMoveDirection i_move);

	void pickClosestGridItem(GridItemTrackInfo& i_trackInfo, std::vector<BoardEntity*> i_map);
	void pickAndGenerate(std::vector<BoardEntity*>& i_map, int i_startCol);
    void generateGridMap();
    std::string pickNextGridMap();
    std::string getGridItemTypeName(RunningSubwayObjectType i_type);
    void addGridItem(std::vector<BoardEntity*>& i_map, int i_row, int i_col);
    bool canGenerateNextGridMap();
    void checkMapGeneration();
    void updateRunningPlayer();

    bool checkWin();
    void onUpdate();
    void testMoveBoard();

    void loadComplete();
    void levelStarted();
    void gameplayStarted();
    bool preventSave();

    void onGamePlayStarted();
    void initSpeed();
    void initSkill();
    void initHP();
    void initUI();
    bool isInSkill();
    void startRun();
    void initSkillButton();
    bool canActivateSkill();
    void checkActivateSkill();
    void autoActivateSkill();
    void activateSkill();
    void activateSkillValue();
    void updateSkill();
    void endSkill();
    void endSkillValue();
    void onNotifyCoinCollected();
    void onNotifyGotHit();

    void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_rect) const;
    void checkRunningPlayerCollision();

private:

    bool                                    m_GameStarted;
    bool                                    m_hasWon;
    bool                                    m_checkCondition;

    Sexy::TouchID 							m_touchIdent;
    bool                                    m_touchHasHandled;
    SexyVector2                             m_touchStart;
	bool                                    m_touchIsMove;
	bool                                    m_bCanTouch;
	bool                                    m_isPlayerDying;

    RtWeakPtr<class BoardGridMapProps> 			CurrentGridMap;
    std::vector<GridItemPtr>				m_board;
    std::vector<GridItemPtr>				m_nextBoard;
    int										m_currentMapIndex;

    GridItemTrackInfo						m_firstCreatedGridItemInfo;
    GridItemTrackInfo						m_secondCreatedGridItemInfo;

    float									m_currentSpeed;
    float									m_currentSpeedValue;
    float									m_totalDistance;

    RunningSkillInfo						m_currentSkill;
    int										m_currentHitPoints;

    RtWeakPtr<UIWidget>                     m_scoreUI;
    int										m_currentScore;
    int										m_targetScore;

    RtWeakPtr<class RunningSubwaySkillButton> 			m_skillButton;
};

class RunningSubwayModuleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(RunningSubwayModuleProperties, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return RunningSubwayModule::StaticGetClass();
    }

    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

    RunningSubwayModuleProperties()
    : TargetScore(0)
    , ScorePerGrid(0)
    {

    }

    std::vector<std::string> GridMapCollection;
    RunningPlayerInitInfo RunningPlayerInfo;
    int TargetScore;
    int ScorePerGrid;
};

// Grid item

class GridItemRunningSubwayObjectProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayObjectProps, GridItemBreakableTargetProps, RtClass);

    GridItemRunningSubwayObjectProps()
    {

    }
    virtual ~GridItemRunningSubwayObjectProps() {}
};

class GridItemRunningSubwayObject : public GridItemBoardEntityConditionTarget
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayObject, GridItemBoardEntityConditionTarget, RtClass);

    GridItemRunningSubwayObject();
    ~GridItemRunningSubwayObject();

    bool		IsDamageableByPlants() const override
				{ return false; }
    void		onGridItemInitialize() override;
    bool IsControlled() const override;

    bool IsDamageable() const override;

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    bool ShouldDrawShadow() const override;

    void onUpdate() override;
    void onDraw(Graphics* i_g) override;

    void SetNextPosition(const SexyVector3& i_position) { m_nextPosition = i_position; }
    const SexyVector3& GetNextPosition() { return m_nextPosition; }

    virtual void OnCollide(BoardEntity* i_entity) {}

protected:

    void updatePosition() override;
    SexyVector2	getRenderOffset() override;
private:
    void drawObjectAnim(Graphics* i_g);
    void checkEdge();

    SexyVector3 m_nextPosition;
};

class GridItemRunningSubwayObjectAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayObjectAnimRig, PopAnimRig, RtClass);

    GridItemRunningSubwayObjectAnimRig();

    void PlayIdle();
    virtual std::string getIdleAnimLabel();
};

// Coin
class GridItemRunningSubwayCoin : public GridItemRunningSubwayObject
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayCoin, GridItemRunningSubwayObject, RtClass);

    GridItemRunningSubwayCoin();
    ~GridItemRunningSubwayCoin();

    void OnCollide(BoardEntity* i_entity) override;
    Sexy::Rect calcCollisionRect() override;
};

class GridItemRunningSubwayCoinAnimRig : public GridItemRunningSubwayObjectAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayCoinAnimRig, GridItemRunningSubwayObjectAnimRig, RtClass);

    GridItemRunningSubwayCoinAnimRig();

    std::string getIdleAnimLabel() override;
};

// Obstacle
class GridItemRunningSubwayObstacleProps : public GridItemRunningSubwayObjectProps
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayObstacleProps, GridItemRunningSubwayObjectProps, RtClass);

    GridItemRunningSubwayObstacleProps()
    : CollisionWidth(0)
    , CollisionHeight(0)
    {

    }
    virtual ~GridItemRunningSubwayObstacleProps() {}

    int CollisionWidth;
    int CollisionHeight;
};

class GridItemRunningSubwayObstacle : public GridItemRunningSubwayObject
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayObstacle, GridItemRunningSubwayObject, RtClass);

    GridItemRunningSubwayObstacle();
    ~GridItemRunningSubwayObstacle();

    void OnCollide(BoardEntity* i_entity) override;
    Sexy::Rect calcCollisionRect() override;

private:
    void onBreakAnimDone(const std::string& i_animLabelName);

    bool m_hasHitted;
};

class GridItemRunningSubwayObstacleAnimRig : public GridItemRunningSubwayObjectAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemRunningSubwayObstacleAnimRig, GridItemRunningSubwayObjectAnimRig, RtClass);

    GridItemRunningSubwayObstacleAnimRig();

    void PlayBreak(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

    std::string getIdleAnimLabel() override;
};

// Region
class BoardRegionDisabledArea : public BoardRegion
{
public:
	RT_CLASS_DEFINE(BoardRegionDisabledArea, BoardRegion, RtClass);

	BoardRegionDisabledArea();
};

// UI
class RunningSubwayTargetUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(RunningSubwayTargetUI, ChallengeUI, RtClass);

    RunningSubwayTargetUI();
    void SetScore(int i_count);
	void SetTarget(int i_target);
	int GetScore() const { return m_score; }
	int GetTarget() const { return m_target; }

protected:
	virtual SexyString getCountText() override;

private:
	int	m_score;
	int m_target;
};

class RunningSubwaySkillButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(RunningSubwaySkillButton, UIEasyButtonWidget, RtClass);

    RunningSubwaySkillButton();
    virtual ~RunningSubwaySkillButton();

    virtual void Draw(Graphics* i_g) override;
    Rect							CalcPlusButtonRect();

    void SetCanActivate(bool i_activate);
    bool CanActivate() { return m_canActivate; }

    virtual void OnClick();
    virtual void InitParam();

	virtual bool					OnTouch(const Sexy::Touch& i_touch) override;

	void SetCurrentValue(int i_value) { m_currentValue = i_value; }
	int GetCurrentValue() { return m_currentValue; }

	void SetMaxValue(int i_value) { m_maxValue = i_value; }
	int GetMaxValue() { return m_maxValue; }

protected:
    void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed) override;
    virtual void					registerForEvents() override;
    virtual void					unregisterForEvents() override;

protected:
    void activate();
    void disabled();

    bool m_prepare;
    ImagePtr m_normalImg;
    ImagePtr m_pressedImg;

    int m_currentValue;
    int m_maxValue;
    bool m_canActivate;
    bool m_activated;

    RtWeakPtr<class Effect_PopAnim> m_warningEffect;
};

// Utils
namespace RunningSubwayUtils
{
	float GetRunningPlayerBaseSpeed();
	void SetSpeedValue(float i_value);
	bool IsDisabledRegion(const Point& i_gridLoc);
	bool IsDisabledRegion(const Sexy::SexyVector3 &i_position);
	Rect GetRunningPlayerRect();
	bool IsPlayingRunningSubway();
}

// Message
namespace Message
{
	void NotifySpeedChanged(float i_newSpeedValue);
	void NotifyCoinCollected();
	void NotifyGotHit();
	void NotifyPlayerKilled();
	void RunningPlayerDied();
	void NotifyStartRunning();
	void NotifyJumpOnBoard();
	void NotifyJumpOffBoard();
	void NotifyActivateSkill();
}

#endif /* RUNNINGSUBWAY_H_ */
