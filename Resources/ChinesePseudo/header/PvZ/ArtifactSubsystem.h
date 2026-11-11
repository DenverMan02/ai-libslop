/*
 * ArtifactSubsystem.h
 *
 *  Created on: 2022-8-24
 *      Author: zhousen
 */

#ifndef ARTIFACTSUBSYSTEM_H_
#define ARTIFACTSUBSYSTEM_H_

#include <string>
#include "Graphics.h"
#include "StateMachine.h"
#include "GameSubSystem.h"
#include "TimeMgr.h"
#include "BoardEntity.h"
#include "Zombie.h"
#include "Plant.h"
#include "GridItemAnimController.h"
#include "Projectile.h"
#include "Artifact.h"

// Artifact Watergun
struct WatergunBeamParams
{
public:
	WatergunBeamParams() {
		PushDistancePerSecond = 1.0f;
		NoPushDistancePerSecond = 3.0f;
		Duration = 6.0f;
		BigZombiePushDebuffDistance = 0.25f;
		DripZombieConditionDuration = 15.f;
		DripZombieConditionValueNormal = 8.f;
		DripZombieConditionValueBig = 4.f;
		DripPlantConditionDuration = 15.f;
		DripPlantConditionValue = 0.25f;
	}

	float PushDistancePerSecond;// N * grid width
	float NoPushDistancePerSecond;// original beam speed(N * grid width)
	pvztime_t Duration;// beam life time
	float BigZombiePushDebuffDistance;// decline distance by second
	pvztime_t DripZombieConditionDuration;// drip zombie condition duration
	float DripZombieConditionValueNormal;// drip zombie condition normal frozen time
	float DripZombieConditionValueBig;// drip zombie condition big frozen time
	pvztime_t DripPlantConditionDuration;// drip plant condition duration
	float DripPlantConditionValue;// plant speed up.
};

// WatergunBeam
class WatergunBeamEntity : public BoardEntity
{
public:
	enum BeamState
	{
		BEAMSTATE_INACTIVE,
		BEAMSTATE_ACTIVE,
		BEAMSTATE_DISABLING
	};

	RT_CLASS_DEFINE(WatergunBeamEntity, BoardEntity, Sexy::RtClass);

	WatergunBeamEntity();
	~WatergunBeamEntity();

	virtual void 	onInitialized() override;
	virtual void 	onDestroy() override;
    virtual void    onUpdate() override;
    virtual void    onDraw(Graphics* i_g) override;

    void InitParams(WatergunBeamParams param);
    void StartBeam();
    void CanShowWatergun(bool show);
    void CreateWatergunRig();

protected:
    std::vector<BoardEntity*> FindBeamCollisionTargets(BoardEntityTypeFlag type);
    Rect CalcBeamCollisionRect();

    void PushZombies();
    void PushZombie(Zombie* zombie);
    void BuffZombie(Zombie* zombie);

    void BuffPlants();
    void BuffPlant(Plant* plant);

    void PlantCreate(Plant* plant);// add plant, if can be buffed by beam.
    void ZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);// remove zombie from list, and recalc push distance delta

    bool IsActivite() { return m_beamState == BEAMSTATE_ACTIVE; }
    bool IsPush() { return !m_pushZombieList.empty(); }

    float CalcCurrentPushDelta();

    void DrawBeamRig(Graphics* i_g);
    void DrawHitRig(Graphics* i_g);
	void drawLaserFromToScreenSpace(Graphics *i_graphics, const Sexy::SexyVector2 &i_from, const Sexy::SexyVector2 &i_to,
									const Sexy::SexyVector2 &i_startArtOffset, const Sexy::SexyVector2 &i_endArtOffset, Effect_PopAnim* i_beamRig);
	void DrawCollisionInfo(Graphics* g);

	void setBeamState(BeamState i_newState);
	void UpdateBeam();

	Sexy::SexyVector2 boardToScreenSpace(const Sexy::SexyVector3& i_vector);
	Sexy::SexyVector2 artPointToScreenPoint(const Sexy::Point& i_artPoint);
	float getAngleForVector(const Sexy::SexyVector2& i_vector);

protected:
	BeamState m_beamState;
	SexyVector2 m_lastBeamEnd;// maybe no use
	SexyVector2 m_previousBeamEnd;// maybe no use

	SexyVector2 m_beamTargetPositionBoardSpace;// maybe no use
	SexyVector2 m_beamStartPositionBoardSpace;
	SexyVector2 m_beamCurrentPositionBoardSpace;

	RtWeakPtr<class Effect_PopAnim> m_beamRig;
	RtWeakPtr<class Effect_PopAnim> m_beamHitRig;
	RtWeakPtr<class Effect_PopAnim> m_watergunRig;
	bool m_canShowWatergun;

	pvztime_t m_beamEndTime;// beam end time

	std::vector<ZombiePtr> m_pushZombieList;// put zombie list.
	std::vector<PlantPtr> m_buffPlantList;// buff plant list.

	float m_pushDistanceDelta;// push distance delta
	float m_pushDistanceDeltaNoPush;// distance delta no push.
	pvztime_t m_duration;// duration time
	float m_bigZombiePushDebuffDistance;// add one big zombie, how many distance should be decline by one second.
	float m_dripZombieConditionDuration;// drip zombie condition duration
	float m_dripZombieConditionValueNormal;// drip zombie condition normal frozen time
	float m_dripZombieConditionValueBig;// drip zombie condition big frozen time
	float m_dripPlantConditionDuration;// drip plant condition duration
	float m_dripPlantConditionValue;// plant speed up.

	Point m_BeamStartOffset;
	Point m_BeamArtStartOffset;
	Point m_BeamArtEndOffset;
	Point m_BeamHitPivotOffset;
};

typedef RtWeakPtr<WatergunBeamEntity> WatergunBeamPtr;

// Watergun SubSystem
class ArtifactWatergunSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ArtifactWatergunSubSystem, GameSubSystem, RtClass);

	ArtifactWatergunSubSystem();
    ~ArtifactWatergunSubSystem();

    virtual void onDestroy() override;
	virtual void Update() override;
	virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

    void RegisterEvents();
    void UnregisterEvents();
    void Start();
    void End();
    void FillWatergunBeamParams(WatergunBeamParams params);

protected:
    void DrawWaterbeam(Sexy::Graphics *i_g);


private:
    std::vector<WatergunBeamPtr> m_WatergunBeamList;// beam ptr list.
    WatergunBeamParams m_WatergunBeamParams;
};


// Artifact Blackhole
enum ArtifactBlackholeType
{
	Blackhole_Invalid = -1,
	Blackhole_Main,// main skill
	Blackhole_Other,// passive 2
	Blackhole_Max,
};

// GridItemArtifactBlackholeProps
class GridItemArtifactBlackholeProps : public GridItemAnimControllerProps
{
public:
	RT_CLASS_DEFINE(GridItemArtifactBlackholeProps, GridItemAnimControllerProps, RtClass);

	GridItemArtifactBlackholeProps();

	Rect SearchTargetRect;
};


// GridItemArtifactBlackhole

enum {
	BLACKHOLE_STATE_WAVEDRAG = GRID_ITEM_STATE_CUSTOM_BEGIN,
};

class GridItemArtifactBlackhole : public GridItemAnimController
{
public:
	RT_CLASS_DEFINE(GridItemArtifactBlackhole, GridItemAnimController, RtClass);

	GridItemArtifactBlackhole();
	virtual ~GridItemArtifactBlackhole();

	void onGridItemInitialize() override;
	void onUpdate() override;
	int CalcRenderOrder() const override;
    void KillGridItem() override;

	void SetType(ArtifactBlackholeType type) { m_type = type; }
	void SetZombieMass(float value1, float value2, float value3, float value4);
	void SetBigZombieDamage(float damage);
	void SetWaveDragEnable(bool enable);

protected:
	void OnEndAnimDone(const std::string& name) override;
	void PlayWaveDragAnim();
	void OnWaveDragAnimDone(const std::string& name);

	std::vector<BoardEntity*> FindTargets();
	void DragZombie(Zombie* zombie);
	void DragZombieByWave(Zombie* zombie);
	bool IsZombieValid(Zombie* zombie);
	void UpdateDragZombies();
	void UpdateDamageZombies();
	void OnZombieTossEnd(Zombie* i_zombie);
	void WaveDragZombies();
	void StopDragZombies();

	bool IsImpZombieMass(Zombie* zombie);
	bool IsSmallZombieMass(Zombie* zombie);
	bool IsMidZombieMass(Zombie* zombie);
	bool IsBigZombieMass(Zombie* zombie);

	float CaclZombieMass(Zombie* zombie);

protected:
	ArtifactBlackholeType m_type;
	Rect m_searchTarget;
	float m_impZombieMass;
	float m_smallZombieMass;
	float m_midZombieMass;
	float m_bigZombieMass;
	float m_bigZombieDamage;
	bool m_waveDragEnable;
	std::vector<ZombiePtr> m_zombieList;
};

// GridItemArtifactBlackholeTileProps
class GridItemArtifactBlackholeTileProps : public GridItemAnimControllerProps
{
public:
	RT_CLASS_DEFINE(GridItemArtifactBlackholeTileProps, GridItemAnimControllerProps, RtClass);

	GridItemArtifactBlackholeTileProps();

	Rect SwallowTargetRect;
};

// GridItemArtifactBlackholeTile
class GridItemArtifactBlackholeTile : public GridItemAnimController
{
public:
	RT_CLASS_DEFINE(GridItemArtifactBlackholeTile, GridItemAnimController, RtClass);

	GridItemArtifactBlackholeTile();
	virtual ~GridItemArtifactBlackholeTile();

	void onGridItemInitialize() override;
	void onUpdate() override;
	int CalcRenderOrder() const override;
    void KillGridItem() override;

protected:
	void UpdateSwallowZombies();
	Rect CalcSwallowRect();
	std::vector<BoardEntity*> FindTargets();
	void SwallowZombies(std::vector<BoardEntity*> i_zombies);
	bool IsZombieValid(Zombie* zombie);
	void KillZombie(Zombie* zombie);
	void KillPlant();
	void SetupZombieToBeSwallowed(Zombie* i_zombie);

protected:
	std::vector<ZombiePtr> m_zombieSwallowList;
	std::vector<CurveSequence_SexyVector3> m_zombieSwallowCurves;
};


// artifact beehive bee entity

STATE_ENUM_BASE_BEGIN(ABEState)
ABEState_INIT,
ABEState_FLYTOTARGET,
ABEState_ATTACK,
ABEState_FLYAWAY,
ABEState_TURNBACK,
ABEState_END,
STATE_ENUM_END(ABEState);

class ArtifactBeeEntity : public BoardEntity
{
public:
	RT_CLASS_DEFINE(ArtifactBeeEntity, BoardEntity, RtClass);

	ArtifactBeeEntity();
	virtual ~ArtifactBeeEntity();

    void    ArtifactBeeEntityInitialize(ArtifactBeehive::ArtifactBeeType type, float damage, float damageMax, float poisonLifePercent, bool flyToArtifact);

    int  CalcRenderOrder()  const override;
    bool ShouldDrawShadow() const override { return false; }

    void MoveToTarget(SexyVector2 i_endPosition);
    void SetTarget(BoardEntityPtr i_target);

protected:

    virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	void onPostLoad() override;

    DECLARE_STATE_FUNCTIONS(ABEState, INIT);
    DECLARE_STATE_FUNCTIONS(ABEState, FLYTOTARGET);
    DECLARE_STATE_FUNCTIONS(ABEState, ATTACK);
    DECLARE_STATE_FUNCTIONS(ABEState, FLYAWAY);
    DECLARE_STATE_FUNCTIONS(ABEState, TURNBACK);
    DECLARE_STATE_FUNCTIONS(ABEState, END);

    void setState(ABEState i_newState);
    bool isInState(ABEState i_state) const;

    int32 getStateSerialization();
    void  setStateSerialization(int32 i_state);

    void onFlyToTargetDone(BoardEntity * target);
    void onFlyAwayDone(BoardEntity * target);
    void onTurnBackDone(BoardEntity * target);

    void onAttackAnimDone(const std::string& i_label);

    void onAnimCommand(const std::string& i_animLabel,
                       pvztime_t i_timeStamp,
                       const std::string& i_animCommand,
                       const std::string& i_animCommandParam);

    BoardEntity* FindTarget();    
	SexyVector2 CalcMoveTarget(ArtifactBeehive::ArtifactBeeType type, Rect rect);
    bool IsBig();

    bool CheckTargetOutOfOriginalPosition();

private:
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    StateMachine<ABEState> 		m_ABEState;

    SexyVector2                 m_posLast;
    SexyVector3                 m_posTakeOff;
    float                       m_angle;
    bool                        m_mirrorX;

    ArtifactBeehive::ArtifactBeeType             m_type;
    BoardEntityPtr				m_target;
    SexyVector3					m_orginalTargetPosition;

    float						m_beeDamage;
    float 						m_beeDamageMax;
    float						m_poisonLifePercent;

    float 						m_totalDamage;
    bool 						m_flyToArtifact;
};

#endif /* ARTIFACTSUBSYSTEM_H_ */
