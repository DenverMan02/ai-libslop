//
//  ZombieZombossMech.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 9/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieZombossMech_h
#define PlantsVersusZombies2_ZombieZombossMech_h

#include <set>
#include <string>
#include <vector>

#include "BoardEnums.h"
#include "PVZTypes.h"
#include "Point.h"
#include "Rect.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "StateMachine.h"
#include "TimeLine.h"
#include "TimeMgr.h"
#include "Utils.h"
#include "Zombie.h"
#include "ZombiePropertySheet.h"
#include "ZombieWithActions.h"
#include "ZombossActions.h"

class BoardEntity;
class PlantType;
class ZombossRocket;

namespace Message
{
	void ZombossStageEnding(Zombie* i_zombie, int i_scoreValue);
	void ZombossIntroDone();
}

STATE_ENUM_CHILD_BEGIN(ZombossMechState, ZombieWithActionsState)
	ZombossPreIntro,
	ZombossIntro,
	ZombossIdle,
	ZombossStun,
	ZombossStageChange,
	ZombossDeath,
	ZombossExiting,
STATE_ENUM_END(ZombossMechState);

struct ZombossStage
{
	ZombossStage()
	{
		// Set sane initial values
		HitPoints = 1000;
        Level = 1;
		DamageIndexFull = 0;
		DamageIndexHalf = 1;
		AnimRateModifier = 1.f;
		ChilledDurationFromFrozen = 10.0f;
		MinColumn = 6;
		MaxColumn = 7;
		IdleTime.SetRange(1.f, 1.f);

		StunTime = 3.0f;
		StunDamageScale = 2.f;
		StunStaggerBackMovement = 30.f;
		StunStaggerBackTime = 0.4f;

	}

	/// Properties

	//	Hitpoints		- Amount of damage Zomboss can take before leaving this stage
	int HitPoints;
    //  Level
	int Level;
	//	DamageIndexFull - Damage index to use for this phase when we are at full stage health
	int DamageIndexFull;
	//	DamageIndexHalf - Damage index to use for this phase when we are at half stage health
	int DamageIndexHalf;

	//	AnimRateModifier - Anim rate scale applied to all Zomboss animations
	float AnimRateModifier;

	// ChilledDurationFromFrozen	- Duration to be chilled instead of frozen, if Zomboss is frozen
	float ChilledDurationFromFrozen;

	/// Positioning

	//	MinColumn		- Leftmost column Zomboss will move into (indexed from 0)
	//	MaxColumn		- Rightmost column Zomboss will move into (indexed from 0)
	int MinColumn;
	int MaxColumn;

	//	Retreat			- Parameters used when Zomboss retreats to the back row to shake off the pain
	RtWeakPtr<ZombieActionDefinition> RetreatAction;

	//	Stun
	float StunTime;
	float StunDamageScale;
	Color StunDamageColorFlash;
	float StunStaggerBackMovement;
	float StunStaggerBackTime;

	//  IdleTime		- Amount of time to wait between attack phases
	ValueRange IdleTime;

	/// Actions
	std::vector<RtWeakPtr<ZombieActionDefinition>> Actions;
};

struct ZombossPostStageScoring
{
    ZombossPostStageScoring()
    {
        HitPoints = 0;
        Score = 0;
    }

    int HitPoints;
    int Score;
};

struct ZombossStageScoring
{
    ZombossStageScoring()
    {
        UseUnlimitedStages = false;
    }

    bool UseUnlimitedStages;
    std::vector<int> DefinedScores;
    std::vector<int> DefinedStagesToInterpolate;
    ZombossPostStageScoring PostDefinedStages;
};

class ZombieZombossMechProps : public ZombiePropertySheet
{
	public:
	RT_CLASS_DEFINE(ZombieZombossMechProps, ZombiePropertySheet, RtClass);

	ZombieZombossMechProps()
	{
		// Set sane initial values
		SquashZombies = false;
        SquashGridItems = false;
		EnterRow = 3;
		EnterColumn = 6;
		HideDuringIntro = false;
        CanTransform = false;
	}

	//	Enter	- Not part of the action choosing process, describes how he enters the screen
	//		Row				- Row that we should start on
	//		Column			- Column that we should start on
	//		HideDuringIntro	- Don't show Zomboss Mech during the intro narrative
	int  EnterRow;
	int  EnterColumn;
	bool HideDuringIntro;

	//	SquashZombies	- If true, when Zomboss lands on a zombie, he will squish them as well as plants
	bool SquashZombies;
    
    // SquashGridItems	- If true, when Zomboss lands on a grid item, he will squish them as well as plants (inc. Lilypad)
	bool SquashGridItems;

	//		CrosshairPopAnim	- PopAnim to use for the crosshair effect
	//		CrosshairAnimation	- Animation to play for the crosshair
	std::string CrosshairPopAnim;
	std::string CrosshairAnimation;
	std::string RocketAnimation;
	std::string RocketExplosionAnimation;
    
    bool CanTransform;
    
	// Stages!
	std::vector<ZombossStage> Stages;

	// Scoring
	ZombossStageScoring UnlimitedStages;
};

class ZombieZombossMech : public ZombieWithActions
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech, ZombieWithActions, RtClass);

    ZombieZombossMech();
	virtual ~ZombieZombossMech();

	static void GetRequiredAssetGroupsForZombossType(ZombieTypePtr i_zombossMechType, std::set<std::string>& io_resourceGroups);
	static void GetRequiredAssetGroupsForSpawnedZombies(ZombieTypePtr i_zombossMechType, std::set<std::string>& io_resourceGroups);

	bool IgnoreKillbox() const override;

	//ZombieThreatLevel GetThreatAlertLevel() override;
	SexyVector2 GetShadowScaling() const override;
	bool IsBleedingOut() const override;

	bool CanBeMowed() const override;
	bool CanBeBlovered() const override;
    
    bool CanBeFlickedOff() const override
	{
        return false;
	}
    
    bool CanBeStabbed() const override
    {
        return false;
    }
    
    bool CanBePoisoned() const override
    {
        return false;
    }

    bool hasArmParticle() const override { return false; }

	void TakeDamage(const DamageInfo& i_damage) override;

	/// Zomboss-specific public interface

	virtual void OnLevelBegin();
	void StartBattling();
	virtual void BeginExiting();

	void SetIdleState() override;
	
	const int GetStageIndex() { return m_currentStageIndex; }

	// Targeting / Movement
	std::vector<Point> GatherValidAdjacentPositions(bool i_vertical, bool i_horizontal) const;
	void GatherEntitiesAtPosition(std::vector<BoardEntity*>& o_entities, BoardEntityTypeFlag i_entityTypes, const Point& i_position) const;
	bool IsPositionOverAttackTarget(const Point& i_position) const;
	void PickRetreatTarget(Point& o_targetPosition) const;
	void UpdatePositionFromCurve(const CurveCollection_Float& i_movementCurves);

	// Stompy stomp
	bool IsPlantfoodedPlantUnderfoot() const;
	void KillEntitiesUnderfoot();
	void StompEntitiesUnderfoot();
    
    // Summoning
	virtual bool TryHandleSummonZombie(Zombie* i_zombie, const SexyVector3& i_targetPosition) const;
	virtual bool HasSummonAnimation() { return true; }

	// Jumping around
	virtual void Retreat(ZombieState i_endState);

	// Stun
	void DoStun();
	virtual bool HasStunAnimation() { return true; }

	// Stage change
	virtual bool TryChangeStage();

	// Zombie spawn tracking
	void IncrementZombieWaveCounter();
	int GetZombieWaveCounter() const;
	void SetNextZombieWaveWithPlantfood(int i_wave);
	int GetNextZombieWaveWithPlantfood() const;
	std::vector<Loot>& GetLootForSpawnedZombies();

	// Speed modification
	const pvztime_t GetZomboss_T();
	const pvztime_t GetZomboss_T_Modifier();
	void SetAnimRateModifier(const float i_animRateModifier);
	void ForceAnimRateModifierForActiveStage();

	// Rocket launching
	virtual void OnRocketHitGround(ZombossRocket* i_rocket);
	virtual void OnRocketCountered(ZombossRocket* i_rocket);
	void OnRocketDestroyed(ZombossRocket* i_rocket);

	void CreateRocketControllers(const std::vector<Point>& i_targetSquares, std::vector<ZombossRocket*>& o_newRockets);
	void StartRocketEffectsOn(const std::vector<Point>& i_targetSquares, float i_hitTime, float i_speed, const std::string& i_dropSound);

	void CounterRocketTargeting(const Point& i_location);
	void CounterAllRockets();
    void CounterAllUndroppedRockets();
	class ZombossRocket* FindActiveRocketTargetingSquare(const Point& i_square) const;

	// Stun from plantfood damage
	void ResetPlantfoodDamageCounter();
	float GetPlantfoodDamageCounterValue() const;

	// Death
	bool IsRunningDeathSequence() const;
	bool IsDead() const;
    
    // Audio
    virtual bool UsesDefaultZombossAudio() { return false; }
    
    void setLastAction(ZombieActionDefinitionPtr i_lastAction);
    ZombieActionDefinitionPtr getLastAction() { return m_lastAction; }
    
    void setStageIndex(int i_index);
    
    // Cheat kill zomboss
    bool ShouldCheatKillZomboss() const { return m_cheatKillZombie; }
    void SetCheatKillZomboss(bool i_kill) { m_cheatKillZombie = i_kill; }
    float GetStunHpFactor();
protected:
    
    void clearActionRepeats() { m_actionRepeatsLeft = 0; }
    
	void setStartingPlaceOnBoard();

	const ZombossStage& getStage(int i_stageIndex, int& o_maxHealth) const;
	const ZombossStage& getActiveStage() const;
    
    virtual void startRandomAction();

	virtual void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons);

	bool canBeStunned() const;

    void onPostLoad() override;
	void onZombieInitialize() override;
	void registerForEvents() override;

	void onPlaceOnBoard() override;
	void onUpdate() override;
	void onApplyCondition(ZombieConditions i_condition) override;
    virtual void onZombossExitFinal();
    
    bool isImmuneToShrinking() override { return true; }

	CurveCollection_Float& getMovementCurve();
	CurveSequence_Color& getColorCurve();

	// Resource management
	void loadResourceGroupsForSpawnedZombies() const;
	void unloadResourceGroupsForSpawnedZombies() const;

	// Action picking
	virtual bool performRandomZombossAction();
	bool tryPerformZombossAction(ZombieActionDefinitionPtr i_action);
	int pickRandomRepeatCountForAction(ZombieActionDefinitionPtr i_action) const;
	void pickRandomRepeatCountForLastAction();
	bool tryRepeatAction();

	// Zomboss movement
	bool isPositionValid(const Point& i_position) const;
	Sexy::Rect getGridRectForPosition(const Point& i_position) const;
	std::vector<Point> gatherValidPositionsInRect(const Sexy::Rect& i_gridRect) const;
	int getRetreatColumn() const;

	// Stompy stomp
	void gatherEntitiesUnderfoot(std::vector<BoardEntity*>& o_entities) const;
	virtual bool isPlantAllowedUnderZomboss(const PlantType* i_plant);
	void stompEntityInFront(bool i_highAttack);

	// Anim Callbacks
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	virtual void onIntroAnimDone(const std::string& i_animName);
	void onDyingAnimDone(const std::string& i_animName);
	void onStunAnimDone(const std::string& i_animName);
	void onStunEndAnimDone(const std::string& i_animName);
    void onTransformEndAnimDone(const std::string& i_animName);
    
	// Spawn!
	void nukeSpawnedZombies() const;

	// Stun!
	virtual void buildStunMovementCurve();
	void buildStunColorCurve();

	// Change Stage or Die!
	bool shouldZombossDie() const;
	bool shouldZombossChangeStages() const;

	virtual void onStartedNewStage(int i_newStageIndex);
	
	// Damage effects
	void setDamageEffectsAllowed(bool i_canShowDamageEffects);
	void updateDamageEffects(int i_stageIndex);
	virtual SexyVector3 getDamageEffectsBoardSpaceOffset() const { return SexyVector3(0.f, 0.f, 0.f); }

	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossPreIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossStun);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossStageChange);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossDeath);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombossExiting);

protected:

    // Timing value for state transitioning
    pvztime_t m_scheduledStateEndTime;

private:
    int getActiveStageScore();
    int getStageScore(int i_index);

	// Current stage index
	int m_currentStageIndex;
	int m_actionRepeatsLeft;
	ZombieActionDefinitionPtr m_lastAction;
    std::map<ZombieActionDefinitionPtr,pvztime_t>     m_mapactionFreezeEndTime;

	// Curve sequence that's used in various states for movement positioning
	CurveCollection_Float m_movementCurves;
	CurveCollection_Float m_effectCurves;

	CurveSequence_Color m_colorCurve;

	// Timing value that is affected by slowdown effects
	pvztime_t m_zombossScaledTime;

	// State-specific flags
	bool m_startedFade;
	bool m_dyingAnimDone;
	bool m_exitAnimDone;
	bool m_playingStunStart;
	bool m_playingStunEnd;
    bool m_playingTransform;
	bool m_takenStunAttack;
	bool m_haveShownHalfDamagePhase;
    bool m_cheatKillZombie;

	float m_plantfoodDamageTaken;

	int m_zombieWavesFullySpawned;
	int m_nextZombieWaveWithPlantfood;
    int m_zombossStageEndIndex;

	std::vector<RtWeakPtr<class ZombossRocket> > m_activeRockets;

	RtWeakPtr<class Effect_PopAnim> m_zombieDamageSparks;
    bool m_canShowDamageEffects;
	int m_droppedDebrisCount;

	std::vector<Loot> m_lootForSpawnedZombies;
};

#endif
