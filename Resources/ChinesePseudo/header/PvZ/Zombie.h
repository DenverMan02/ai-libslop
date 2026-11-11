//
//  Zombie.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include "Precompile.h"
#include "BoardEntity.h"
#include "PVZTypes.h"
#include "ZombieType.h"
#include "StateMachine.h"
#include "StormZombieSpawner.h"
#include "StateMachineTableBuilder.h"
#include "ZombieAnimRig.h"
#include "EntityComponent.h"
#include "ZombieConditionTracker.h"
#include "Loot.h"
#include "Effect_PopAnim.h"
#include "griditem.h"
#include "ZombieParticle.h"
#include "AttachedEffectManager.h"
#include "TodCommon.h"
#include "ProbabilitySet.h"
#include "PlaybackController.h"
#include "Armor.h"

typedef RtWeakPtr<class Zombie> ZombiePtr;

/// Base Zombie State machine
using namespace Sexy;

STATE_ENUM_BASE_BEGIN(ZombieState)
	ZS_Idle,
	ZS_Walk,
	ZS_Eat,
	ZS_Attack,
	ZS_BleedingOut,
	ZS_Die,
	ZS_Electrocute,
	ZS_Ash,
	ZS_MowedDown,
	ZS_FlickedOff,
	ZS_RiseFromGround,
    ZS_RiseFromStorm,
    ZS_StormEntrance,
    ZS_TakeWeapon,
	ZS_Winning,
    ZS_Plantify,
    ZS_TargetRise,
    ZS_Glide,
    ZS_Besiege,
    ZS_DropIntoIceHole,
    ZS_StuckInGround,
    ZS_Grabbed,
    ZS_RiseFromPod,
    ZS_ResilienceEnterBreak,
    ZS_ResilienceBreak,
    ZS_ResilienceRecover,
    ZS_IntroOnBoard,
STATE_ENUM_END(ZombieState);

/// Zombie Flags
enum ZombieFlags
{
	PVZ_BEGIN_FLAG_ENUM(ZFLAG_),
	PVZ_FLAG(ZFLAG_UseAnimTranslation),
	PVZ_FLAG(ZFLAG_LostArm),
	PVZ_FLAG(ZFLAG_LostHead),
	PVZ_FLAG(ZFLAG_HasDroppedLoot),
	PVZ_FLAG(ZFLAG_NoBlinkOnDamage),
	PVZ_FLAG(ZFLAG_IsFlying),				// This zombie is not on the ground right now
	PVZ_FLAG(ZFLAG_IsJumping),
	PVZ_FLAG(ZFLAG_IsParkourJumping),				// for parkour_runner
	PVZ_FLAG(ZFLAG_WinningZombie),
	PVZ_FLAG(ZFLAG_PlayedDeathAnim),
	PVZ_FLAG(ZFLAG_SuppressDeath),			// All damage is still taken, but the Zombie will not enter the BleedingOut or Death state
	PVZ_FLAG(ZFLAG_Controlled),
	PVZ_FLAG(ZFLAG_WalkAfterRise),
	PVZ_FLAG(ZFLAG_HasTorch),
	PVZ_FLAG(ZFLAG_IsTorchBurning),
	PVZ_FLAG(ZFLAG_IgnoreAllDamage),
	PVZ_FLAG(ZFLAG_IgnoreAllDamageDuringAction),
    PVZ_FLAG(ZFLAG_HasDebugHighlight),
	PVZ_FLAG(ZFLAG_FriendZombie),
	PVZ_FLAG(ZFLAG_NotTargetable),
	PVZ_FLAG(ZFLAG_IgnoresCollisions),
    PVZ_FLAG(ZFLAG_HasBroadcastedDeath), // only broadcast death once - mainly used for ZombieAmbientAudioSubsystem
    PVZ_FLAG(ZFLAG_IsPulledByBeachZomboss),
    PVZ_FLAG(ZFLAG_MowDownByMower),
    PVZ_FLAG(ZFLAG_AnimIgnoreConditionColors),
    PVZ_FLAG(ZFLAG_MarkedForDeath),			// Zombie is marked for death
	PVZ_FLAG(ZFLAG_IgnoreFindTarget),
	PVZ_FLAG(ZFLAG_BeingSuckedIntoEndlessPitOfDespair),			// Name courtesy of jemery
	PVZ_END_FLAG_ENUM(ZFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ZombieFlags);

enum ZombieFacing
{
	PVZ_BEGIN_ENUM(ZFACING_),
	ZFACING_Left,
	ZFACING_Right,
	PVZ_END_ENUM(ZFACING_)
};

struct RiftProjectileTimer
{
public:
	RtWeakPtr<class Projectile> JuggledProjectile;
	pvztime_t ReturnTime;
};

struct ResilienceInfo
{
	ResilienceInfo()
	: m_currentResilience(0.0f)
	, m_maxResilience(0.0f)
	, m_recoverInterval(0.0f)
	, m_recoverValue(0.0f)
	, m_weakType(ZombieResistenceType_None)
	, m_nextResilienceRecoverTime(PVZ_EOT())
	, m_nextDamageThresholdResetTime(0.0f)
	, m_currentDamageAccumulation(0.0f)
	, m_currentResilienceBaseDmgAccumulation(0.0f)
	, m_currentResilienceExtraDmgAccumulation(0.0f)
	, m_nextResilienceDamageThresholdResetTime(0.0f)
	{

	}

	ResilienceInfo(float i_current, float i_max, float i_recoverInterval, float i_recoverValue, ZombieResistenceType i_weakType)
	: m_currentResilience(i_current)
	, m_maxResilience(i_max)
	, m_recoverInterval(i_recoverInterval)
	, m_recoverValue(i_recoverValue)
	, m_weakType(i_weakType)
	, m_nextResilienceRecoverTime(PVZ_EOT())
	, m_nextDamageThresholdResetTime(0.0f)
	, m_currentDamageAccumulation(0.0f)
	, m_currentResilienceBaseDmgAccumulation(0.0f)
	, m_currentResilienceExtraDmgAccumulation(0.0f)
	, m_nextResilienceDamageThresholdResetTime(0.0f)
	, m_nextResilienceBarFadeOutTime(0.0f)
	{

	}

	float m_currentResilience;
	float m_maxResilience;
	float m_recoverInterval;
	float m_recoverValue;
	ZombieResistenceType m_weakType;
	float m_nextResilienceRecoverTime;
	float m_nextDamageThresholdResetTime;
	float m_currentDamageAccumulation;
	float m_currentResilienceBaseDmgAccumulation;
	float m_currentResilienceExtraDmgAccumulation;
	float m_nextResilienceDamageThresholdResetTime;
	float m_nextResilienceBarFadeOutTime;
};

struct DamageBalancer
{
	DamageBalancer()
	:TargetFlags(DAMAGE_None),
	BalanceValue(0)
	{}

	DamageBalancer(DamageTypeFlags i_flag, float i_value)
	:TargetFlags(i_flag),
	TargetConditions(ZCONDITION_Invalid),
	BalanceValue(i_value)
	{}

	DamageBalancer(ZombieConditions i_conditions, float i_value)
	:TargetFlags(DAMAGE_None),
	TargetConditions(i_conditions),
	BalanceValue(i_value)
	{}

	DamageTypeFlags TargetFlags;
	ZombieConditions TargetConditions;
	float BalanceValue;
};


struct ZombieConditionsStruct
{
	ZombieConditionsStruct()
	:Condition(ZCONDITION_Invalid),
	Duration(1.0f),
	EventDelay(0.0f)
	{

	}

	ZombieConditionsStruct(ZombieConditions i_condition, pvztime_t i_duration)
	:Condition(i_condition),
	Duration(i_duration),
	EventDelay(0.0f)
	{

	}

	ZombieConditionsStruct(ZombieConditions i_condition, pvztime_t i_duration, RtWeakPtr<class BoardEntity> i_instigator)
	:Condition(i_condition),
	Duration(i_duration),
	EventDelay(0.0f),
	Instigator(i_instigator)
	{

	}

	ZombieConditionsStruct(ZombieConditions i_condition, pvztime_t i_duration, RtWeakPtr<class BoardEntity> i_instigator, pvztime_t i_eventDelay)
	:Condition(i_condition),
	Duration(i_duration),
	EventDelay(i_eventDelay),
	Instigator(i_instigator)
	{

	}

	ZombieConditions Condition;
	pvztime_t Duration;
	pvztime_t EventDelay;
	RtWeakPtr<class BoardEntity> Instigator;
};

class PlantGroup;
class Zombie : public BoardEntity
{
public:
	RT_CLASS_DEFINE(Zombie, BoardEntity, RtClass);

	/// Construction
	Zombie();
	virtual ~Zombie();

	/// Initialization
	void ZombieInitialize(ZombieTypePtr i_newType, int i_spawnedFromWave, int i_level, int i_packetLevel = 0, uint32 i_seed = 0);
	void PlaceOnStreet(SexyVector3 i_position);
	
	/// Accessors
	inline const ZombieTypePtr&	GetType() const;
    inline std::string          GetClassType() const;
	inline const ZombiePropsPtr&GetProps() const;
	inline const ZombiePropertySheet * GetZombieProps() const;
	template<class T>
	inline const T* 			GetProps() const;
	inline ZombieAnimRig*		GetAnimRig() const;
	template <class T>
	inline T* 					GetAnimRig() const;
    
    // returns true if it meets the passed in flag's requirements
    bool MatchesAny(const ZombieTestFlag i_flags) const;
    bool MatchesAny(const ZombieTestFlag i_flags, const class Plant* i_plant) const;
    
	inline int		GetSpawnedFromWave() const;
	inline float	GetHitpoints() const;
	inline float	GetMaxHitpoints() const;
    float           GetHeadDropHitPoints() const;
	inline bool		HasFullHitpoints() const;
	inline HelmType GetHelmType() const;
	inline float	GetHelmHitpoints() const;
	inline float    GetMaxHelmHitpoints() const;
	virtual float GetWalkSpeed() const { return m_walkSpeed; }
	virtual float SetWalkSpeed(float i_walkSpeed)  { m_walkSpeed = i_walkSpeed; }
    virtual SexyVector2 GetShadowScaling() const;
    const std::string& GetTypeName()  { return m_type->TypeName; }

    static ZombieResistenceRank GetResistenceRank(ZombieResistenceType i_type, ZombieTypePtr i_zombieType);
    ZombieResistenceRank GetResistenceRank(ZombieResistenceType i_type);
    static ZombieResistenceRank GetResistenceRank(float i_value);
    float GetResistenceValue(const DamageInfo& i_damage);
    float GetResistenceValue(ZombieResistenceType i_type);
    static float GetResistenceValue(ZombieResistenceType i_type, ZombieTypePtr i_zombieType);
    float GetCurrentResistenceValue(const DamageInfo& i_damage);
    float GetCurrentResistenceValue(ZombieResistenceType i_type);
    ZombieResistenceType ConvertToResistenceType(const DamageInfo& i_damage);
    void SetCurrentResistenceValue(ZombieResistenceType i_type, float i_value);
    void ChangeCurrentResistenceValue(ZombieResistenceType i_type, float i_delta, bool i_add);

    float GetCurrentResilienceValue();
    float GetMaxResilienceValue();
    void AddResilienceDamageAccumulation(float i_damage);
    float GetDamageThreshold();
    float GetResilienceBaseDamageThreshold();
    float GetResilienceExtraDamageThreshold();
    bool HasReachResilienceDamageThreshold();
    bool HasReachMaxResilienceValue();
    float SetCurrentResilienceValue(float i_value);
    float GetCurrentResilienceDamageReduced();
    void CheckResilience(const DamageInfo& i_damage);
    float GetResilienceDamage(const DamageInfo& i_damage);
    void RecoverResilience();
    ZombieResistenceType GetCurrentResilienceWeakType();
    bool IsResilienceBreak() const;

    void Heal();
    void HealHelm();

    void HealByPercent(float healPercent);
	void HealByAmount(float amount) override;

	bool OverrideProjectileCollision(class Projectile* i_projectile) override;

	//float GetArmorHitpoints() const;
	//float GetArmorHitpoints(std::string i_armorType) const;
	//float GetMaxArmorHitpoints() const;
	//float GetMaxArmorHitpoints(std::string i_armorType) const;
	//float GetTotalHitpoints() const;
	float GetLastDistanceWalked() const;

    // Base combat functionality - override when necessary
	// virtual Plant*          FindRangedTarget(std::vector<RtWeakPtr<BoardEntity> > i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity> >() );
	virtual Zombie* FindFriendlyTarget(std::vector<BoardEntityPtr> i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity>>()) const { return nullptr; }

	// plant group functions begin
	virtual PlantGroup* FindRangedTarget(std::vector<RtWeakPtr<BoardEntity>> i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity>>() );
	bool IsValidRangedTarget(PlantGroup* plant);
	bool CanNormalDamagePlantGroup(PlantGroup* i_plant, bool checkInvincible = false);
	// bool WillTargetPlant(PlantGroup* i_plantGroup);
	void eatPlantGroup(PlantGroup *i_targetPlant);

	// plant group functions end

    // If set, we will only ever target this entity from normal eat/ranged attack search functions
	void            SetForcedTarget(BoardEntity* i_forcedTarget);
	BoardEntity*    GetForcedTarget() const;
	virtual bool    IsValidRangedTarget(Plant* plant);
    
    bool WillTargetPlant(Plant* i_plant);
    
    float			GetExtraDPSmodifier() const;
    float			GetExtraHitPointsmodifier() const;
    
#ifndef WANTS_CHEATS_DISABLED
	void SetDebugHighlight(const Color& i_color);
	void ClearDebugHighlight();
#endif

	virtual int CalcHelmDamageIndex() const;
	virtual int CalcProgressMeterHitpoints() const;

	ZombieFacing 	GetFacing() const;
	void 			SetFacing(ZombieFacing i_facing);
    void            SetTranslationMultiplier(float i_newMultiplier);
    float           GetTranslationMultiplier() const;
	void SetRenderLayerOffset(int i_layerOffset) { m_zombieRenderLayerOffset = i_layerOffset; }

    virtual Sexy::Point GetGridExtents() const override;
	/// Poke!
	virtual void TakeFatalDamage(const DamageInfo& i_damage) override;
	void TakeFatalDamage(class BoardEntity* i_instigator);
    
    virtual void DoSpecial();
    
    virtual bool DoSkill(ZombieSkillType skill_type) { return false; }
	
	virtual void TakeDamage(const DamageInfo& i_damage) override;
	void SetDamageScale(float i_damageScale);
    float	     GetAwakenScaledLevel() const { return m_awakenScaleLevel; };
    
    void SetMergeLevel(int i_mergeLevel);
    int GetMergeLevel() { return m_mergeLevel; }

    void SetExtraEatDPS(float i_dps);
    float GetExtraEatDPS() { return m_extraEatDPS; }

    void SetPacketLevel(int i_packetLevel);
    int GetPacketLevel() { return m_packetLevel; }

    void SetBaseEatDPS(float i_dps);

    virtual BoardEntity *findTarget();

    void Hypnotize(bool i_healOnHypnotism, float i_healPercentage, BoardEntity* i_instigator = nullptr);
	void Gum(std::string i_gumType, float i_gumHitpoints, BoardEntity* i_instigator = nullptr);
	void Petrify(float i_stoneBlockHealth, std::string i_stoneBlockType);
    virtual void AssignCatastrophicDamage() {} // this is for Zomboss, specifically so that Lost City Bug can override it.
    void TurnToAsh();
    virtual ZombieParticle* DropArm();
    virtual ZombieParticle* DropHead();
    virtual ZombieParticle* DropHelm();
	class ZombieParticle* DropArmor(ArmorTypeFlags i_flag, DamageTypeFlags i_damageFlags);
    void RegrowArm();
    void SetSizeType(ZombieSizeType sizetype);
    ZombieSizeType GetSizeType() const;
    void SetOwnerPlant(RtWeakPtr<class Plant> i_ownerPlant);
	void SetHitpoints(float i_hitpoints);
    void setHelm(HelmType i_helmType, float i_helmHitpoints);
    void setHelmHitpoints(float i_helmHitpoints);
    float getLeftHitPer(bool includeHelm); // 0.0 - 1.0f
    void SetStormType(StormType i_stormType);
    void SetMaxHitpoints(float i_maxHitpoints);
	void SetHasPlantFood(bool i_hasFood);
	void SetHasDroppedLoot(bool i_hasDroppedLoot);
    void SetHasLeader(bool i_hasLeader);
    void SetHasLeader(bool i_hasLeader, float leaderHitpointMulti);
	void SetIsUsingAnimTranslation(bool i_hasAnimTranslation);
	void SetIsFlying(bool i_flying);
	void SetIsJumping(bool i_jumping);
	void SetIsParkourJumping(bool i_jumping);
	void SetIsControlled(bool i_controlled);
	void SetIsWinningZombie();
	void SetSuppressDeath(bool i_suppressDeath);
	void SetIsTargetable(bool i_isTargetable);
	void SetIgnoresAllDamage(bool i_ignoreDamage);
	void SetIgnoresCollisions(bool i_ignoresCollisions);
	void SetIsFriendZombie(bool i_isFriendZombie);
	void SetIgnoreFindTarget(bool i_isIgnore);
	void SetIsBeingPulledByOlivePit(bool i_pulled);
	bool IsBeingPulledByOlivePit() const { return TestFlag(m_zombieFlags, ZFLAG_BeingSuckedIntoEndlessPitOfDespair); }
	void MowDown();
//	virtual void RiseFromGround(const SexyVector3& i_boardPosition, bool i_walkAfterRise = false);
	void SetDamageFlash(float i_duration);
	void RiseFromGround(const SexyVector3& i_boardPosition, bool i_walkAfterRise = false);
    void StuckIntoGround(const SexyVector3& i_boardPosition, pvztime_t i_stuckTime, pvztime_t i_underTime, float i_stuckHeight, pvztime_t i_intoGroundTime = 0.0f, bool hasStuckEffect = true);
    void StuckIntoGround_2(const SexyVector3& i_boardPosition, pvztime_t i_stuckTime, pvztime_t i_underTime, float i_stuckHeight, pvztime_t i_intoGroundTime = 0.0f, bool hasStuckEffect = true);
    float getStuckIntoGroundHeight();
    void AddStuckTime(float extendedTime);
    void DoDropIntoIceHole(const SexyVector3& i_boardPosition, bool bSpecial = false);
    void RiseFromStorm(const SexyVector3& i_boardPosition);
	void StormEntrance(int i_gridX, int i_gridY);
	virtual void SetIsFlagZombie(bool i_hasFlag);
	virtual void SetIdleState();
	virtual void SetWalkingState();
	virtual void SetGrabbedState();
	void StartRushOnScreen();
    virtual void LaunchedByGargantuar() {}
    virtual void RiseFromPod(const SexyVector3& i_boardPosition);
    
    void BreakResilience();

	MATH_TYPE GetFacingMultiplier() const;
    
	void StartWarpIn(float ofDuration = 1.75);
	void StartWarpOut(float ofDuration = 1.75);
    
	void Nudge(float i_destinationX, float i_speed, bool i_canReverseDirection);
    void SetIsPulledByBeachZomboss(bool i_pulled);
    
    void SetAnimIgnoreConditionColors(bool i_ignoresColors);
    
    void  SetZombieScale(float i_scale);
    float GetZombieScale();
    
    // Stuff to do with jamming zombies
    virtual void StartJamming(){};
    virtual void StopJamming(){};
    virtual std::string GetJamStyle(){ return "";};

	/// Conditions
	void ApplyCondition(ZombieConditions i_condition, pvztime_t i_duration, pvztime_t i_eventDelay = 0.0f, bool i_isAppend = true);
	void ApplyCondition(const ZombieConditionsStruct& i_conditionsStruct);
	void EndCondition(ZombieConditions i_condition);
	void ClearConditions();
    void EndConditions(std::vector<ZombieConditions> i_condition);
	bool HasCondition(ZombieConditions i_condition) const;
    
    EEliminateType GetEliminateColor();
    void SetEliminateColor(int i_color);
    void SetEliminateColor(EEliminateType i_color);

    virtual void ApplyStun(pvztime_t i_time);
	virtual void EMPeachStun(pvztime_t i_time) { ApplyStun(i_time); }
	virtual bool IsStunned() const { return HasCondition(ZCONDITION_Stunned); }
    
    virtual void ApplyNumb(pvztime_t i_time);
    virtual bool IsNumb() const { return HasCondition(ZCONDITION_Numb); }
    virtual bool CanBeNumb();
    
    bool IsInSandStorm() const;
    virtual bool CanApplyVenomStack();
    
	// Condition dispatch.
	void NotifyApplyCondition(ZombieConditions i_condition);
	void NotifyEndCondition(ZombieConditions i_condition);
    void NotifyConditionEvent(ZombieConditions i_condition);
	virtual void onApplyCondition(ZombieConditions i_condition);
	virtual void onEndCondition(ZombieConditions i_condition) {}
	virtual void choosePostStormState();
	virtual void chooseDeathState(const DamageInfo& i_deathBlow);

	void CheckVenomStack();

	// Skill
	void StartPerformingSkills();
	void StopPerformingSkills();
    
    // pvp zombie spawn ramification
    
    void SetSpawnRamification(bool bSpawn) { m_bSpawnRamification = bSpawn; }
    bool GetSpawnRamification() { return m_bSpawnRamification; }

	// Loot
	void SetLoot(Loot i_loot);
	Loot GetLoot();
	virtual void DropAllLoot();

	virtual int 	Rand();
	virtual int		Rand(int range);
	virtual float	Rand(float range);

	virtual float 	RandWithOriginal(float i_original);
	virtual float	RandWithOriginal(int range, float i_original);
	virtual float	RandWithOriginal(float range, float i_original);

	float 			GetRandomValue(const ValueRange& i_range);

	///	Test!
	virtual bool IsDying() const;
    virtual bool IsBleedingOut() const;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    virtual bool IsSwingingIn() const { return false; }
    virtual void OnBeforeBlown(BoardEntity* i_blowSource) {}
    //PVZ2_CHINESE_START
    virtual bool CollidesWithFlying() const { return false; }
    //PVZ2_CHINESE_END
    
	virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

	//ZhRed Add
	virtual void onArmorDropped(std::string i_armorType) { };
	virtual void SetSpeedScale(float i_speedScale);
	float GetSpeedScale();
	void SetDpsScale(float i_dpsScale);
	float GetDpsScale() const;
	float GetArmorHitpoints() const;
	float GetArmorHitpoints(std::string i_armorType) const;
	float GetMaxArmorHitpoints() const;
	float GetMaxArmorHitpoints(std::string i_armorType) const;

	float GetTotalHitpoints() const;
	// Armor
	virtual DamageInfo onArmorDamageTaken(const DamageInfo& i_incomingDamage, std::string i_armorType) { return i_incomingDamage; };
	// Armor
	void AddArmor(std::string i_armorType);

	bool HasArmor(ArmorTypeFlags i_armorFlags) const;
	bool HasArmor(std::string i_armorType) const;
	bool HasArmor(std::vector<std::string> i_armorTypes) const;

	void RemoveArmor(ArmorTypeFlags i_armorFlags);
	void RemoveArmor(std::string i_armorFlags);

	int GetArmorCount() const { return (int)m_armor.size(); }
	virtual bool HasMetallicArmor();

	bool IsSuspended();
	bool IsSlowed();
	bool IsControlled() const;
	bool IsFlying() const;
	bool IsJumping() const;
	bool IsParkourJumping() const;
	bool IsInvisible() const;
	bool IsOnGround() const;
    bool IsOnBoard() const;
    bool IsOnBoardOrClose(int i_maxGridDistFromRight = 1) const;
	bool IsFlickedOff() const;
	bool IsRisingFromGround() const;
    bool IsDropingIntoHole() const;
	bool IsSuppressingDeath() const;
	bool IsTargetable() const;
    bool IsIgnoringAllDamage() const;
	bool DoesIgnoresCollisions() const;
    RtWeakPtr<class Plant> GetOwnerPlant() const;
	bool HasArm() const;
	bool HasHead() const;
    virtual bool CanDropArm() const;
	virtual bool CanDropHead() const;
	bool HasTorch() const;
	bool IsTorchBurning() const;
	bool GetHasPlantFood() const;
    bool GetHasLeader() const;
	bool GetHasDroppedLoot() const;
    bool IsFriendZombie() const;
	float GetHitpointsUntilBleedout() const;
	bool GetCanTriggerWin() const;
    bool CanSurrender() const;
	bool IsValidPinchTarget() const;
    bool CanBeLaunchedByPlants() const;
    bool CanBeLaunchedByPlantsExtra() const;
    virtual bool CanBeTossedByPlants(ZombieTossedPower i_tossStrength) const;
    virtual bool IsAffectedBySliderTiles() const;
    bool CannotStunnedByStreetLamp() const;
    bool IsWinningZombie() const;
    bool IsInWater() const;
    bool IsMowDownByMower() const;
	bool IsIgnoreFindTarget() const;

	virtual bool HasGravity() override;
    
    virtual bool IsHelmMetallic();
    virtual bool CanBePulledHelm();
	virtual Sexy::Rect calcCollisionRect() override;
	
	virtual Sexy::Rect CalcZombieAttackRect();
	virtual SexyVector3 CalcPositionInTime(pvztime_t i_time);
	virtual SexyVector3 CalcProjectileTargetLocation(float i_inTime = 0.f);
	virtual class GameSubSystem* GetSubSystem();
	virtual int CalcRenderOrder() const override;
	


	virtual RtWeakPtr<PopAnim> GetHeadParticlePopAnim();
	
	// ZFACTOR
	virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const
	{
		//return true;
        if (!IsTargetable())
        {
            return false;
        }
        
        if (!i_ignoreInvisible && IsInvisible())
        {
            return false;
        }
        
        return IsOnTeam(TEAM_ZOMBIES);
	}
	virtual bool CanBeMowed() const
	{
		//return true;
        return IsOnTeam(TEAM_ZOMBIES);
	}
    virtual bool CanBeFlicked() const
	{
		if (!IsTargetable())
		{
			return false;
		}
        
        return GetProps()->CanBeFlicked;
	}
    virtual bool CanBeBlovered() const
	{
		return true;
	}
	bool ExplodesWhenMowed() const
	{
		return GetProps()->ExplodesWhenMowed;
	}
	
	bool NormalDeathWhenMowed() const
	{
		return GetProps()->NormalDeathWhenMowed;
	}
    
    virtual bool CanBeFlickedOff() const;
    
    virtual bool CanBeStabbed() const
	{
        return true;
	}
    
    virtual bool CanBePoisoned() const
    {
        return true;
    }
    
    virtual bool CanBeHypnotized() const { return true; }

	virtual bool CanBeGummed() const { return true; }

    void SetElectrocuteColor(const std::string& i_color)
    {
        m_electrocuteColor = i_color;
    }
    
    std::string GetElectrocuteColor() const {return m_electrocuteColor; }
    
    virtual bool IgnoreKillbox() const { return false; }

	ZombieConditionTracker& GetConditionTracker();
    SexyVector3 LayerToWorld(const std::string& i_layerName);

	void FlickOff(const SexyVector3 &i_target);
    void FlickOff(const SexyVector3& i_target, float i_velocity, float i_rotationsPerSecond);
	SexyVector3 GetFlickOffStartPositon();

	/// Static helper functions for reading values out of Plant Property Sheets
	static SexyString GetFormattedNameString(ZombieTypePtr i_zombieType);
	static SexyString GetFormattedToolTip(ZombieTypePtr i_zombieType);
	static SexyString GetFormattedDescription(ZombieTypePtr i_zombieType);
	static SexyString GetFormattedDescriptionHeader(ZombieTypePtr i_zombieType);

    static bool IsHelmTypeMetallic(HelmType i_helmType);
    bool CanbeCorroded(HelmType i_helmType);
    bool ShouldClipWithWater() const override;
    virtual GroundEffectType GetTideEffect() const;
    
    // Mark a zombie for death if that death is certain in advance
    // Some plants can use this to avoid targeting those zombies
    void SetMarkedForDeath() { SetFlag(m_zombieFlags, ZFLAG_MarkedForDeath, true); }
    void RemoveMarkedForDeath() { SetFlag(m_zombieFlags, ZFLAG_MarkedForDeath, false); }
    bool IsMarkedForDeath() const { return TestFlag(m_zombieFlags, ZFLAG_MarkedForDeath); }
    
    virtual bool ShouldDrawShadow() const override;
	virtual BoardEntity *FindEatTarget();
    
    void GetZombieAteHypnoShroomScale(float& o_scale) const;
    
    ZombieState getState() const;
    
    void SetTargetPosition(const SexyVector3 & i_position) { m_TargetPosition = i_position; }
    const SexyVector3 & GetTargetPosition(){ return m_TargetPosition; }
    bool TargetPostionIsVaild() { return (m_TargetPosition.x != 0.0f && m_TargetPosition.y != 0.0f); }
    void ResetTargetPostion()
    {
        m_TargetPosition.x = 0.0f;
        m_TargetPosition.y = 0.0f;
        m_TargetPosition.z = 0.0f;
    }
    
    void SetMoveVelocity(const float fVelocity) { m_MoveVelocity = fVelocity; }
    const float GetMoveVeloctiy() { return m_MoveVelocity; }
    void ResetMoveVeloctiy() { m_MoveVelocity = 0.0f; }

    void SetSunDrop(const int i_sunDrop) { m_sunDrop = i_sunDrop; }
    int  GetSunDrop() const { return m_sunDrop; }
    
    virtual void CreateZombieLevelEffect(bool i_street);
    
    void CreateSpeedUpEffect();
    void DestroySpeedUpEffect();
    
    virtual void CreateArenaSpawnEffect();
    virtual void CreateNewPVPSpawnEffect();
    
    void setZombieState(ZombieState i_newState, bool i_reenterIfAlreadyInState = false);
    void reenterZombieState();
    
    void  SetRotation(float rotation) { m_rotation = rotation; }
    float GetRotation(){ return m_rotation; }
    
    const float GetCriticalPos();
    
    bool HasBroadcastedDeath() const { return TestFlag(m_zombieFlags, ZFLAG_HasBroadcastedDeath); }
    
    void SetDangerDrop(bool bDrop) { m_bDangerDrop = bDrop; }
    bool GetDangerDrop()           { return m_bDangerDrop;  }
    
    void SetDropLoot(bool i_drop) { m_canDropLoot = i_drop; }
    bool GetDropLoot() { return m_canDropLoot; }
    
    bool IsAddSnake()              { return m_IsAddSnake; }
    float GetAcidDamageScale(int level);
    void PlayAcidEffect();
    void PlayArtifactAcidEffect();
    void PlayExtraResilienceDamageEffect(ZombieResistenceType i_weakType);
    void initResilienceBar();
    void updateResilienceBar();
    
    bool IsInmmuneFireDamage() { return GetProps()->FireDamageMultiplier < EPSILON; }
    
    virtual bool isImmuneToShrinking() {return false;}
    virtual bool willDieToShrinking() {return false;}
    
    // Action Support
    	void SetZombieFlag(ZombieFlags i_flag, bool i_value) { SetFlag(m_zombieFlags, i_flag, i_value); }

	AttachedBoardEntityNode* GetOrCreateAttachedBoardEntity(const std::string& i_entityName);
    AttachedBoardEntityNode* GetAttachedBoardEntity(const std::string i_entityName);
    AttachedEffect& AddAttachedEffect(const char* iEffectName, const char* iPanAnimName, const char* iAnimName, const SexyVector3& iOffset, int iRenderLayerOffset = 1, bool playOnce = false);
    void RemoveAttachedEffect(const char* iEffectName);
    AttachedEffectManager& GetAttachedEffects() { return m_attachedEffects; }
    AttachedBoardEntityManager& GetAttachedBoardEntityManager() { return m_attachedBoardEntities; }
    
    virtual void 	StartLossLife(pvztime_t duration, float percentOfMaxHealth);
    virtual void 	EndLossLife();

    virtual void SetIsSleepping(bool i_isSleepping, float durationTime = -1.0f);
    bool IsSleepping() const { return m_isSleepping; }

    // Sun claiming
    virtual bool CanClaimSun() { return false; }
    virtual bool ShouldReleaseSun() { return false; }
    virtual void DecrementSunsClaimed(const int i_sunCurrency) {}
    virtual void IncrementSunsClaimed(const int i_sunCurrency) {}
    virtual void IncrementSunsCollected(const int i_sunCurrency) {}
    
    // Target History
	void AddToTargetHistory(BoardEntityPtr i_entity);
	const std::vector<BoardEntityPtr>& GetTargetHistory() { return m_targetHistory; }
	bool IsInTargetHistory(BoardEntityPtr i_entity);
	void ClearTargetHistory();

	// Target maybee
	void AddToTargetbyMaybee(BoardEntityPtr i_entity);
	const std::vector<BoardEntityPtr>& GetTargetbyMaybee() { return m_beTargetbyMaybee; }		
	void ClearTargetbyMaybee(BoardEntityPtr i_entity);

    virtual float GetBaseEatDPS();
    bool CanInvokeInvisible();
    void InvokeInvisible(bool invoke, bool i_fadeIn = false, bool i_canBeTargeted = false);
    InvisibleState GetInvisibleState() const;
    void PutZombieWillPath(std::vector<Point>& vp, bool bGridPath = true) { m_vWillPath = vp; m_bGridPath = bGridPath; }
    
    void AddBarrageXItem(int i_gridX, int i_por);
    void AddBarrageYItem(int i_gridY, int i_por);

    void EndInvokeInvisibleEffect();
    void SetBesieged(bool i_besieged);
    void SetBesiegeRate(float i_rate);
    void SetBesiegeHit(int i_hit);
    void PlayAidEffect();
     static float GetMinifyTime();
    virtual bool allowElectrocuteState() const { return true; }
	bool canApplyLightningHit() const { return PVZ_T() > m_canLightningHitTime; }
	void increaseLightningHitTime() { m_canLightningHitTime = PVZ_T() + 1.0f; }
    virtual bool allowAshState() const { return true; }
    virtual void ApplyZombieFood();
    virtual void CancelZombieFood();
    virtual bool IsInZombieFoodState();
    
	// Armor
    void 		setStateMachineTimeScale(float scale);
    float       getStateMachineTimeScale() const;
    bool        IsBoss();
    int GetBossStage();
    int GetSummonZombieLevel();
    
    bool HasFogImmune() const;
    bool IsBerserk() const;

	void SetConditionTracker(ZombieConditions i_condition, float i_additionalValue)
	{
		m_conditionTracker.SetAdditionalValue(i_condition, i_additionalValue);
	}
	void SetExtraConditionTracker(ZombieConditions i_condition, float i_additionalValue)
	{
		m_conditionTracker.SetExtraAdditionalValue(i_condition, i_additionalValue);
	}
	void SetExtraConditionTracker2(ZombieConditions i_condition, float i_additionalValue)
	{
		m_conditionTracker.SetExtraAdditionalValue2(i_condition, i_additionalValue);
	}

	DamageInfo calcEatDamageSuspended();

	float CalcSpecialConditionsDamageDot(float dot);// special conditions damage ratio change
	void PlayEnhancedShadowMistAnimation(int level);// play shadow mist animation 1 ~ 2

	virtual SexyVector3 GetStunnedEffectOffset() const;
	virtual SexyVector3 GetResilienceActivatedEffectOffset() const;

	virtual bool IsEliteZombie() const;// check if is elite zombie
	virtual int GetLimitDamage() const;// get zombie limit damage
	virtual EliteZombie_Type GetEliteZombieType() const;// get elite zombie type
	virtual bool CanEliteImmuneCondition() const;// check if can immune condition

	virtual bool CanShowHealthBarByDamage() const;
	virtual bool CanEliteScaleByZombie() const;// normal zombie scale like elite zombie.
	virtual bool CanEliteImmunittiesByZombie() const;// normal zombie immunities like elite zombie.
	virtual bool CanNoInvincibleTakeDamage() const;

	void DropAndHiddenAllZombieParticle();

protected:
	/// State machine!
	void        updateStateMachine();
    void registerForEvents() override;


    bool        isInState(uint32 i_state) const;
    void		setBlinkOnDamage(bool i_blinkOnDamage)
	{
		SetFlag(m_zombieFlags, ZFLAG_NoBlinkOnDamage, !i_blinkOnDamage);
	}

	void 		setUseAnimTranslation(bool i_useAnimTranslation)
	{
		SetFlag(m_zombieFlags, ZFLAG_UseAnimTranslation, i_useAnimTranslation);
	}
	void		spreadBadSmell();
	void 		spreadPoison();
	void		spreadChemistPoison();
	void 		doSpreadChemistPoison(int i_sourceCol, int i_sourceRow);
	void 		updateGhostLanternAttack();

	virtual void processCardGameMoveToEnemy();
	virtual void processCardGameMoveToBoss();
	
	int32		getZombieStateSerialization();
	void		setZombieStateSerialization(int32 i_state);

    virtual void OnInvisibleStateChanged(InvisibleState oldState, InvisibleState newState);
	virtual bool hasHeadParticle() const;
	virtual bool hasArmParticle() const;

    virtual bool canAttack();
    
    virtual SexyVector3 GetNumbEffectOffset() const;
    
	void 		setupSkills(const std::vector<struct ZombieSkillData>& i_zombieSkillData, pvztime_t i_skillInterval);
    
    float getTideDepthHeightMaxPct() override;
	virtual Sexy::Rect calcRangedTargetGridRect() { return Sexy::Rect(); }

	// Individual states
	DECLARE_STATE_FUNCTIONS(ZombieState, Idle);
	DECLARE_STATE_FUNCTIONS(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, Attack);
	DECLARE_STATE_FUNCTIONS(ZombieState, BleedingOut);
	DECLARE_STATE_FUNCTIONS(ZombieState, Die);
	DECLARE_STATE_FUNCTIONS(ZombieState, Electrocute);
	DECLARE_STATE_FUNCTIONS(ZombieState, Ash);
	DECLARE_STATE_FUNCTIONS(ZombieState, MowedDown);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlickedOff);
	DECLARE_STATE_FUNCTIONS(ZombieState, Winning);
    DECLARE_STATE_FUNCTIONS(ZombieState, Plantify);
    DECLARE_STATE_FUNCTIONS(ZombieState, Grabbed);
	
	// FIX - Move out of here? Not universal Zombie abilities!
	DECLARE_STATE_FUNCTIONS(ZombieState, RiseFromGround);
    DECLARE_STATE_FUNCTIONS(ZombieState, StuckIntoGround);
	DECLARE_STATE_FUNCTIONS(ZombieState, RiseFromStorm);
	DECLARE_STATE_FUNCTIONS(ZombieState, StormEntrance);
    DECLARE_STATE_FUNCTIONS(ZombieState, DropIntoIceHole);
    DECLARE_STATE_FUNCTIONS(ZombieState, TakeWeapon);
    DECLARE_STATE_FUNCTIONS(ZombieState, TargetRise);
    DECLARE_STATE_FUNCTIONS(ZombieState, Glide);
    DECLARE_STATE_FUNCTIONS(ZombieState, Besiege);
    DECLARE_STATE_FUNCTIONS(ZombieState, RiseFromPod);
    DECLARE_STATE_FUNCTIONS(ZombieState, ResilienceEnterBreak);
    DECLARE_STATE_FUNCTIONS(ZombieState, ResilienceBreak);
    DECLARE_STATE_FUNCTIONS(ZombieState, ResilienceRecover);
	DECLARE_STATE_FUNCTIONS(ZombieState, IntroOnBoard);

    void spawnTransitionAnimation();

	virtual void onAttackAnimStopped(const std::string& i_animLabel);
	virtual void onResilienceBreakAnimStopped(const std::string& i_animLabel);
	virtual void onResilienceRecoverAnimStopped(const std::string& i_animLabel);
    void onStabbedDone(class Plant * i_plant);
    virtual void onResilienceRecovered();
    

	/// GameObject/BoardEntity interface - when derviving you must call up to the super class.
	virtual void onInitialized() override;
	virtual void onPostLoad() override;
	virtual void onPlaceOnBoard() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onDrawShadow(class Sexy::Graphics* i_g) override;
	virtual void onDrawRotation(class Sexy::Graphics* i_g, SexyTransform2D& i_transform);

	/// Zombie interface
	virtual void onPlaceOnStreet();
	virtual void onZombieInitialize();
    virtual void onZombiePostLoad();
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);
    virtual void onLostHead();
    virtual void onElectrocuted();
    virtual void onTurnedToAsh();
    virtual void onLostArm() {}
    virtual void onRegrowArm() {}
	virtual void onMowedDown();
    virtual void onSetHelm() {}
	virtual void onExternalControlEvent() {};
    virtual void onStartBleeding();
	// Overrides / Handlers
	virtual DamageInfo modifyBodyDamage(const DamageInfo& i_incomingDamage);

	virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived);
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived);
	virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived);
	virtual ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints);
    virtual DamageInfo takeHelmDamage(const DamageInfo& i_incomingDamage);

    virtual std::string getAshPAMName() const { return "POPANIM_EFFECTS_ZOMBIE_ASH"; }
	virtual std::string getElectrocutePAMName() const;
    
    virtual DamageTypeFlags getEatingDamageType() const { return DAMAGE_FROM_EATING; }
    virtual void OnGroundEffectChange(GroundEffectType from, GroundEffectType to) {}
	
	// getHeadDropFraction / getArmDropFraction
	//	- Return the percentage of total hitpoints you should have before dropping
	//	your arm or your head.
	//	- Return 0 if you want the arm or head to drop when the zombie dies
	//	- Return a negative value if you never want the arm or head to drop
	virtual float getHeadDropFraction() const;
	virtual float getArmDropFraction() const;

	// findPlantTarget
	//	- Look for a plant to eat and return it!
	// virtual class Plant* findPlantTarget();

	// findGridItemTarget
	//	- Look for a plant to eat and return it!
	// virtual RtWeakPtr<class GridItem> findGridItemTarget();
    virtual RtWeakPtr<class GridItemArmrack> findArmrackTarget();

    virtual std::vector<BoardEntityPtr> findAttackTargets();

    bool canTargetPlant(Plant* i_plant);
	BoardEntity* findEatTarget(int row, Rect attackRect);
	virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight);
	virtual bool onCanTargetPlant(Plant* i_plant);

	/// Protected helpers
	pvztime_t getTimeInState() const;
	virtual DamageInfo calcEatDamage();
    virtual void eatTarget(BoardEntity* i_target);
    virtual void eatZombie(Zombie* i_targetZombie);
	virtual void eatPlant(Plant* i_targetPlant);
	virtual void eatGridItem(GridItemPtr i_targetGridItem);
	virtual void attackPlant(Plant* i_targetPlant);
	virtual void attackGridItem(RtWeakPtr<class GridItem> i_targetGridItem);
	virtual void attackZombie(const ZombiePtr& zombie);
	void initializeAnimRigForType(ZombieTypePtr i_type);
	virtual void playDeathAnimation();
    void updateRushCondition();
    void updateResilienceDamageThreshold();
	void endRushOnScreen();
    void broadcastZombieDied(const DamageInfo* i_deathBlow);
	virtual SexyVector3 getGumPosition();
    
    void DetachAttachedEffect(const char* i_entityName);
    AttachedEffect* GetAttachedEffect(const std::string i_entityName);
    
    virtual void playEatSound();

	// Hack! Re-applies current condition effects to anim rigs and movement speed
	void forceApplyConditionEffects();
	virtual void applyButterGraphicalEffects();
	void applyPoisonGraphicalEffects();
    virtual void takeBodyDamage(const DamageInfo& i_incomingDamage);
    
    void updateGroundEffect();
    void updateCheckForPitOfDoomDeath();
    void UpdateLevelEffect();

    void setHasTorch(bool i_hasTorch);
    void setIsTorchBurningFlag(bool i_isBurning);
    
    void initializeResistences();
    void initializeResilience();
    
    virtual bool isInPerformingSkillState();

    RtWeakPtr<class GridItemArmrack> m_armrackGridItem;

    AttachedEffectManager& GetAttachedEffectManager() { return m_attachedEffects; }
//    ZombieFlags& GetFlag() { return m_zombieFlags; }
    void OnAmberFinish(StandaloneEffect* i_effect);
    virtual float GetAmberScale();
    int calcDamageIndex(float i_currentHitPoints, float i_maxHitpoints, int i_damageStates) const;
    
    HelmType		m_helm;
    std::string spawnFromPodAnimationName;
    void SetNextChewSoundTime(pvztime_t i_time) { m_nextChewSoundTime = i_time; }
    pvztime_t GetNextChewSoundTime(pvztime_t i_time) { return m_nextChewSoundTime; }
    
    virtual void    UpdatePVP();
    void            RefreshLastHealth();

    void onLevelUp(int i_targetLevel) override;
    bool CanLevelUp(int i_targetLevel) override;
//    void RefreshStats();
    virtual void setNewPAM(std::string i_pamStr);

    // Intor On Board State
    void OnIntroOnBoardEffectComplete(StandaloneEffect* i_effect);

public:
    ZombieFlags& GetFlag() { return m_zombieFlags; }
    virtual void RefreshStats();
	PlaybackController&		GetPlaybackController() { return m_playbackController; }
    virtual void            ClearPlaybackParams(int i_type) {}
    virtual void            TriggerPlaybackParams(int i_type);
    bool IsNotTargetableFlagSet() const;
    bool IsClonedZombie() { return m_isCloned; }
    void SetIsClonedZombie(bool i_isCloned) { m_isCloned = i_isCloned; }
    bool IsCloneable() { return m_isCloneable; }
    void SetIsCloneable(bool i_isCloneable) { m_isCloneable = i_isCloneable; }
    void SetOriginalZombie(ZombiePtr i_zombie) { m_originalZombie = i_zombie; }
    ZombiePtr GetOriginalZombie() { return m_originalZombie; }
    EntityComponent_GroundEffect GetGroundEffect() { return m_groundEffect; }

	void BalanceDamage(DamageInfo& i_damageInfo);
	void SetDamageBalancer(DamageTypeFlags i_flags, float i_value);
	void SetDamageBalancer(ZombieConditions i_conditions, float i_value);

	inline void SetMoveToEnemy(bool i_flag) { m_cardGame_moveToEnemy = i_flag; }
	inline bool GetMoveToEnemy() { return m_cardGame_moveToEnemy; }
	inline void SetMoveToBoss(bool i_flag) { m_cardGame_moveToBoss = i_flag; }
	inline bool GetMoveToBoss() { return m_cardGame_moveToBoss; }

	void AddTag(const std::string& i_tag);
	void DelTag(const std::string& i_tag);
	bool HasTag(const std::string& i_tag);
	void ClearTag();

	void BindImageToSprite(const std::string& i_spriteName, Sexy::Image* i_image);
	void UnbindImageFromSprite(const std::string& i_spriteName, Sexy::Image* i_image);// nullptr means all

protected:
    
    ZombieAnimRig *				m_pCachedZombieAnimRig;
    pvztime_t                   m_nextChewSoundTime;
    ZombieFlags                 m_zombieFlags;
    AnimHandle                  m_playingAnim;
    
    ProbabilitySet<int>         m_GlideXWeights;
    ProbabilitySet<int>         m_GlideYWeights;
    bool m_isInZombieFood;
	PlaybackController			m_playbackController;
	std::vector<ArmorPtr> m_armor;
	pvzAccumulatedTime_t		m_elapsedTimeInState;
	EntityComponent_GroundEffect	m_groundEffect;

	bool 						m_isEliteZombie;
	pvztime_t					m_drawHealthBarTime;// time to control draw elite zombie healthbar
	bool 						m_enableShowHealthBarByDamage;
	bool 						m_enableEliteScale;
	bool 						m_enableEliteImmunities;
	bool 						m_enableNoInvincibleTakeDamage;

private:
	
    void setState(const StateDefinition<ZombieState>& i_newState, bool i_reenterIfAlreadyInState);
    
	void initializeAnimRig();	
	void updateSpeed();
	void startWalk();
	float GetBaseWalkSpeed();
	void updateOverlayEffects();

	void buildProjectileSets();
	bool canJuggleProjectile(Projectile* i_projectile);
	bool isProjectileArrivingAtCatchableAngle(Projectile* i_projectile);
	bool canThrowProjectile(Projectile* i_projectile);
	void storeProjectileInJuggleLimbo(Projectile* i_projectile);
	void updateJunggle();
	void dropAllProjectiles();
	void launchProjectile(Projectile *i_projectile);
    
    void createPlantifiedEffect();
    
	bool canPerformSkill();
    void TakeIntervalSkill();

    void CheckWarningRequest();
    void onStreetLampChanged(PlantFramework* i_plant, int i_state);
    void SetInvisibleState(InvisibleState state);
    void UpdateInvisibleState();
    void UpdateCloneableState();
    bool CheckAllStreetLamp();
    void UpdatePosition();
    
    void GetNextGlideTarget();
    void GetNextBesiegeTarget();
    void UpdateMinifyState();
    
    void UpdateLeaderCondition();
    void onLeaderConditionEnd();
    float CalcExtraDpsFactor();
    float CalcExtraHpFactor();

    void DrawHealthBar(Sexy::Graphics* i_g);
    void DrawHealthBarAndResilienceBar(Sexy::Graphics* i_g);

    void UpdateDripWaterConditionDamage(const DamageInfo &i_damage);

	

	/// Serialized properties
	
	/// The zombie's 'guts' go here
	ZombieTypePtr			m_type;
	ZombieAnimRigPtr		m_animRig;

	/// Run-time state info (ie: good stuff to serialize)
	StateMachine<ZombieState> 	m_stateMachine;
	float 						m_stateMachineTimeScale;
	

	ZombieFacing	m_facing;
	float			m_hitpoints;
	float			m_maxHitpoints;
	float			m_damageScale;
    float           m_awakenScaleLevel;
	float			m_walkSpeed;
	int				m_mergeLevel;
	float			m_extraEatDPS;
	
	// New PVP
	int				m_packetLevel;
	float			m_baseEatDPS;

    ZombieSizeType  m_ZombieSizeType;
	float			m_helmHitpoints;
	float			m_maxHelmHitpoints;
	int				m_spawnedFromWave;
    
    float           m_ZombieLastHealth;
    float           m_showHealthBarTime;
    
    pvztime_t       m_lastGlideTime;
    SexyVector3     m_nextGlidePosition;
    SexyVector3     m_startGlidePosition;
    bool            m_isGliding;
    
    pvztime_t       m_stuckIntoGroundTime;
    pvztime_t       m_stuckUnderGroundTime;
    pvztime_t		m_stuckGoDownGroundTime;
    float			m_stuckGoDownGroundSpeed;
    float           m_stuckIntoGroundHeight;
    bool            m_isStuckedUnderGround;
    bool			m_hasStuckEffect;
    SexyVector3		m_stuckTargetPos;
    
    int             m_besiegeHit;
    pvztime_t       m_besiegeRate;
    pvztime_t       m_lastBesiegeTime;
    pvztime_t       m_lastBesiegeStepTime;
    pvztime_t       m_lastGridDelayTime;
    SexyVector3     m_nextBesiegePosition;
    SexyVector3     m_startBesiegePosition;
    bool            m_isBesieged;
    
	pvztime_t		m_mowedStartTime;
    bool            m_beginPlayLevelEffect;
	float 			m_flickedStartTime;
	SexyVector3     m_flickOffStartPosition;
	SexyVector3     m_flickOffTarget;
    SexyVector3     m_TargetPosition;
    float           m_MoveVelocity;
    float           m_flickOffTimeToTarget;
	float           m_flickOffFinalRotation;
	float           m_rotation;
    float           m_scale;
	int m_zombieRenderLayerOffset;

    EEliminateType  m_eliminateColor;
    
    RtWeakPtr<class Plant> m_ownerPlant;
    
    SexyVector2 m_stormTargetLocation;
    StormType m_stormType;

	// Conditions;
	ZombieConditionTracker m_conditionTracker;
    AttachedEffectManager m_attachedEffects;
	AttachedBoardEntityManager m_attachedBoardEntities;

	DamageInfo m_killingBlowDamageInfo;

    pvztime_t m_tLossLifeTime;// the time that loss life in poison
	bool	 m_bIsLossLife;// check in loss life state
	float	 m_iLossLifePerFrame;// the loss of life in each frame

	bool    m_isSleepping;
    pvztime_t m_sleepingEndTime;

//	std::vector<PlantFamilyResistance> m_familyResistances;
	std::vector<BoardEntityPtr> m_targetHistory;
	std::vector<BoardEntityPtr> m_beTargetbyMaybee;

	Loot m_loot;
    Color m_highlightColor;
    bool m_isBeingDestroyed;
    
	//Skill-related
	bool							  m_canPerformSkill;
    pvztime_t                         m_delayTimeToPerformSkill;
    pvztime_t						  m_skillInterval;
    std::vector<class ZombieSkill>    m_zombieSkills;

    //zombie warning
    bool							  m_needWarning;
    std::string						  m_warningMessage;

    ZombiePropertySheet *		m_pCachedZombiePropertySheet;
    
    std::string                       m_electrocuteColor;
    float                             m_translationMultiplier;
    
    int                               m_sunDrop;
    
    RtWeakPtr<BoardEntity>            m_forcedTarget;
    
    bool                              m_bDangerDrop;
    bool                              m_bDropIntoIceHole;
    bool                              m_IsAddSnake;
    int                               m_previousCol;
    InvisibleState                    m_invisibleState;
    bool							  m_canBeTargetedWhenInvisible;
    std::vector<Point>                m_vWillPath;
    bool                              m_bGridPath;
    bool							  m_detected;
    bool                              m_canDropLoot;
    bool                              m_bSpawnRamification;
    float                             m_iSyringeHP;
    bool 							  m_isCloned;
    bool							  m_isCloneable;
    bool                              m_bIsLeaderZombieWrapout;
    float                             m_leaderWrapoutTime;
    float                             m_extraDps = 1.0f;
    float                             m_extraHP = 1.0f;
	bool							  m_alreadyKilled;
	RtWeakPtr<class Plant>			  m_lastCauseDamage;
	pvztime_t 						  m_InvisibleFadeInStartTime;
	pvztime_t 						  m_canLightningHitTime;

	float m_speedScale;
	float m_dpsScale;

	std::set<const ProjectilePropertySheet*> m_juggleableProjectiles;
	std::set<const ProjectilePropertySheet*> m_unthrowableProjectiles;
	std::set<const ProjectilePropertySheet*> m_angleAgnosticProjectiles;
	std::vector<RiftProjectileTimer> m_juggledProjectiles;
	pvztime_t 						  m_accumulatedTime;
	bool								m_ReachLine;
	ZombiePtr m_originalZombie;
	bool m_enterBoardX;
	std::vector<DamageBalancer> m_damageBalancer;
	bool m_cardGame_moveToEnemy;
	bool m_cardGame_moveToBoss;
	std::set<std::string> m_tags;
	std::vector<std::pair<std::string, Sexy::Image*>> m_spriteBind;

	std::vector<float> m_currentResistence;
	ResilienceInfo m_currentResilience;

public:
	bool m_launchByLemon;
	bool m_launchByFishhookgrass = false;
	int m_launchLevelByFishhookgrass = 0;
	float m_fall_point = 0;
	bool m_hasDownGradedByHocusCrocus = false;

	// New PVP Rand Seed
	class MTRand* m_randomObject;
};

namespace Message
{
	void ZombieAddedToBoard(Zombie* i_zombie);
    void ZombieRiseFromGround(Zombie* i_zombie);
    void ZombieStuckIntoGround(Zombie* i_zombie);
	void ZombieDestroyed(Zombie* i_zombie);
	void ZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void ZombieDropHead(Zombie* i_zombie);
	void ZombieDropLoot(Zombie* i_zombie);
    void ZombieCloseToHouse(Zombie* i_zombie);
	void SandstormSpawned(Zombie* i_zombie);
	void SandstormDestroyed(Zombie* i_zombie);
    void ZombieDamageTaken(Zombie* i_zombie, const DamageInfo& i_damage);
    void ZombieDamageTakenRaw(Zombie* i_zombie, const DamageInfo& i_damage);
	void ZombieHelmDamageTaken(Zombie* i_zombie, const DamageInfo& i_damage);
    void ZombieReaddedToBoard(Zombie* i_zombie);
    void ZombiePlantified(Zombie* i_zombie);
    void NoticeZombieWarning(int i_row, int i_col, const std::string& i_narrativeID);
    void ZombieWarningEffectStarted();
    void ZombieEndWillPath(Zombie* i_zombie);
    void ZombieCloseToBottomLine(Zombie* i_zombie);
	void ZombiePlaybackAddParams(Zombie* i_zombie, int i_type);
	void ZombieDropArmor(Zombie* i_zombie, const std::int64_t i_damageFlags);
	void ZombieBurnedToAsh(Zombie* i_zombie);
	void ZombieElectrified(Zombie* i_zombie);
	void ZombieConditionPrepare(Zombie* i_zombie, int* i_condition, pvztime_t* i_duration);
	void ZombieConditionApplied(Zombie* i_zombie, int i_condition, pvztime_t i_duration);
	void ZombieConditionTimeAppend(Zombie* i_zombie, int i_condition, float* i_rate, bool i_isAppend);
	void ZombieConditionEnded(Zombie* i_zombie, int i_condition);
	void ZombieNudgeEnd(Zombie* i_zombie);
	void ZombieBleedingOut(Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void ZombieReachLine(Zombie* i_zombie);
	void PlantKillZombie(const std::string& plantName);
	void ZombieEnterBoardX(Zombie* i_zombie);
	void ZombieEnterSandstorm(Zombie* i_zombie);
	void ZombieExitSandstorm(Zombie* i_zombie);
	void ZombieSpawnedByTent(Zombie* i_zombie);
}

inline const ZombieTypePtr & Zombie::GetType() const
{
	return m_type;
}

inline std::string Zombie::GetClassType() const
{
	return m_type->ZombieClass;
}

inline const ZombiePropsPtr & Zombie::GetProps() const
{
	DBG_ASSERT(m_type.IsValid());
	return m_type->Properties;
}

inline const ZombiePropertySheet * Zombie::GetZombieProps() const
{
	return m_pCachedZombiePropertySheet;
}
template<class T>
inline const T* Zombie::GetProps() const
{
	const ZombiePropsPtr & zombieProps = GetProps();
	const T* typedProps = zombieProps->Cast<const T>();
	return typedProps;
}

inline ZombieAnimRig* Zombie::GetAnimRig() const
{
	return m_animRig->CastChecked<ZombieAnimRig>();
}
template <class T>
inline T* Zombie::GetAnimRig() const
{
	return GetAnimRig()->CastChecked<T>();
}

inline int Zombie::GetSpawnedFromWave() const
{
	return m_spawnedFromWave;
}
inline float Zombie::GetHitpoints() const
{
	return m_hitpoints;
}

inline void Zombie::SetMaxHitpoints(float i_maxHitpoints)
{
	m_maxHitpoints = i_maxHitpoints;
}

inline float Zombie::GetMaxHitpoints() const
{
	return m_maxHitpoints;
}
inline bool Zombie::HasFullHitpoints() const
{
	return (m_maxHitpoints == m_hitpoints && m_maxHelmHitpoints == m_helmHitpoints);
}
inline HelmType Zombie::GetHelmType() const
{
	return m_helm;
}
inline float Zombie::GetHelmHitpoints() const
{
	return m_helmHitpoints;
}
inline float Zombie::GetMaxHelmHitpoints() const
{
	return m_maxHelmHitpoints;
}

#endif
