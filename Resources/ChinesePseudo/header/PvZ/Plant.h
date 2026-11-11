#ifndef __PLANT_H__
#define __PLANT_H__

#include "BoardEntity.h"
#include "DamageFrost.h"
#include "PlantAnimRig.h"
#include "EffectAnimRig_PlantFoodShine.h"
#include "EffectAnimRig_StarPlantFoodShine.h"
#include "EntityComponent.h"
#include "PlantConditionTracker.h"
#include "SexyAppFramework/SexyVector.h"
#include "PlantEnums.h"
#include "PVZTypes.h"
#include "PlantPropertySheet.h"
#include "RtObject.h"
#include "AttachedEffectManager.h"
#include "StateMachine.h"
#include "BoostTracker.h"

class PlantFramework;
class Projectile;
struct PlantPropertiesAction;
class PlantType;
class MapEventItem;
struct ZombieConditionsStruct;

typedef RtWeakPtr<class Plant> PlantPtr;
typedef RtWeakPtr<class PlantGroup> PlantGroupPtr;

//PVZ2_CHINESE_BEGIN
struct RelocationEvent
{
	enum RelocationType
	{
		PVZ_BEGIN_ENUM(RELOCATION_),
		RELOCATION_FLYING,
		RELOCATION_PUSHED,
		RELOCATION_PUSHED_OFFSCREEN,
		RELOCATION_ABSORBED,
		RELOCATION_SHAKE_FADE_IN,
		RELOCATION_SHAKE_FADE_OUT,
        RELOCATION_PUSHED_DROWNED,
        RELOCATION_PULLED_BY_FAN,
        RELOCATION_SWAP,
        RELOCATION_BEGHOULED_INITIALIZATION,
		PVZ_END_ENUM(RELOCATION_),
	};

	float m_relocateFromX;
	float m_relocateFromY;
	float m_relocateToX;
	float m_relocateToY;
    float m_relocateApexHeight;
	pvztime_t m_relocateStartTime;
	pvztime_t m_relocateEndTime;
	bool m_whetherToMovePlant;
	RelocationType m_relocationType;
    SexyVector2 m_relocationOffsetFromDestination;

	RelocationEvent()
	{
		reset();
	}

	void reset()
	{
		m_relocateFromX = 0.f;
		m_relocateFromY = 0.f;
		m_relocateToX = 0.f;
		m_relocateToY = 0.f;
        m_relocateApexHeight = 200.0f;
		m_relocateStartTime = 0.f;
		m_relocateEndTime = 0.f;
		m_whetherToMovePlant = false;
		m_relocationType = RELOCATION_Invalid;
	}
};

//PVZ2_CHINESE_END

enum PlantFlags
{
	PVZ_BEGIN_FLAG_ENUM(PFLAG_),
	PVZ_FLAG(PFLAG_SpawnedByPlant),
	PVZ_FLAG(PFLAG_SpawnedByImitater),
    PVZ_FLAG(PFLAG_TravellingOutsideGroup),
	PVZ_END_FLAG_ENUM(PFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(PlantFlags);

enum PLANT_LAYER
{
	PLANT_LAYER_BELOW = -1,
	PLANT_LAYER_MAIN = 0,
	PLANT_LAYER_REANIM,
	PLANT_LAYER_REANIM_HEAD,
	PLANT_LAYER_REANIM_BLINK,
	PLANT_LAYER_ON_TOP,

	NUM_PLANT_LAYERS = PLANT_LAYER_ON_TOP - PLANT_LAYER_BELOW
};

enum PlantWeapon
{
	WEAPON_PRIMARY,
	WEAPON_SECONDARY,
	WEAPON_AVATAR,
    WEAPON_SUPERSKILL,
    WEAPON_SUPERSKILL_FOOD,
    WEAPON_SUPERSKILL_AVATAR,
};

STATE_ENUM_BASE_BEGIN(PlantState)
	STATE_NOTREADY,
	STATE_READY,
	STATE_DOINGSPECIAL,
	STATE_BEINGREMOVED,

	STATE_IDLE,

	STATE_PLANTFOOD,
    STATE_BEING_HELPED,
    STATE_EXHAUSTED,	// Start -> Loop -> End timed exhaustion
    STATE_CHARGING,
	STATE_CYCLING,
	// Plant specific enums below
	STATE_FRAMEWORK_BEGIN,
STATE_ENUM_END(PlantState);

enum TargetParamsDistanceWeight
{
    TARGET_PARAMS_DISTANCE_ANY,
    TARGET_PARAMS_DISTANCE_CLOSEST,
    TARGET_PARAMS_DISTANCE_FARTHEST
};

enum TargetParamsFlags
{
    PVZ_BEGIN_FLAG_ENUM(TARGET_PARAMS_FLAGS_),
    
    PVZ_FLAG(TARGET_PARAMS_FLAGS_TARGET_BLEEDERS),
    PVZ_FLAG(TARGET_PARAMS_FLAGS_LIMIT_RIGHT_OF_CENTER),
    PVZ_FLAG(TARGET_PARAMS_FLAGS_IGNORE_MARKED_FOR_DEATH),
    
    PVZ_END_FLAG_ENUM(TARGET_PARAMS_FLAGS_),
};

enum PlantHelpType
{
	PLANT_HELP_WIND,
};



struct PlantTargetParams
{
    PlantTargetParams() :
    targetFlags(TARGET_PARAMS_FLAGS_TARGET_BLEEDERS),
    distanceWeight(TARGET_PARAMS_DISTANCE_CLOSEST)
    {}
    
    PlantTargetParams(TargetParamsDistanceWeight i_distanceWeight, TargetParamsFlags i_targetFlags)
    {
        distanceWeight = i_distanceWeight;
        targetFlags = i_targetFlags;
    }
    
    PlantTargetParams(TargetParamsDistanceWeight i_distanceWeight, int i_targetFlags)
    {
        distanceWeight = i_distanceWeight;
        targetFlags = (TargetParamsFlags) i_targetFlags;
    }
    
    TargetParamsDistanceWeight	distanceWeight;
    TargetParamsFlags			targetFlags;
};


struct PlantAddition
{
    enum PAdditonRLS
    {
        PAdditonRLS_Error = 0,
        PAdditonRLS_ATK_Add,
        PAdditonRLS_ATK_Muti,
        PAdditonRLS_SPD_Add
    };

public:
    PlantAddition()
    :type(PlantAdditionType::PAddition_Invalid),
    rls(PAdditonRLS_Error),
    timer(0),
    value(0)
    {

    }

    PlantAddition(PlantAdditionType i_addition, PAdditonRLS i_rule, pvztime_t i_timer, float i_value)
    :type(i_addition),
    rls(i_rule),
    timer(i_timer),
    value(i_value)
    {

    }

    PlantAdditionType type;
    PAdditonRLS rls;
    pvztime_t timer;
    float value;
};


struct UBoostInfo
{
	UBoostInfo()
	: m_uBoostDamagePerHit(0.0f)
	, m_uBoostDisabledTime(PVZ_EOT())
	, m_uBoostDamageTotal(0.0f)
	, m_uBoostDamageLimit(0.0f)
	, m_uBoostDamageDuration(0.0f)
	{

	}

	UBoostInfo(float i_dmgPerHit, float i_disabledTime, float i_dmgTotal, float i_dmgLimit, float i_duration)
	: m_uBoostDamagePerHit(i_dmgPerHit)
	, m_uBoostDisabledTime(i_disabledTime)
	, m_uBoostDamageTotal(i_dmgTotal)
	, m_uBoostDamageLimit(i_dmgLimit)
	, m_uBoostDamageDuration(i_duration)
	{

	}

	float m_uBoostDamagePerHit;
	float m_uBoostDisabledTime;
	float m_uBoostDamageTotal;
	float m_uBoostDamageLimit;
	float m_uBoostDamageDuration;
};

class Plant : public BoardEntity
{
public:
	RT_CLASS_DEFINE(Plant, BoardEntity, RtClass);

	Plant();
	virtual ~Plant();
    
	void PlantInitialize(int i_x, int i_y, PlantTypePtr i_plantType, bool bAvatarEnable = true, bool bLevelEnable = true, int i_level=-1, bool i_useBoost = false, bool playlevelEffect = true, bool duplicate = false, bool ignore_plantfood = false, uint32 i_seed = 0);
	void InitializeAnimRig();
	void InitializeFromPropertySheet();
    void UpdateLaunchInterval(float percent);
	
	virtual bool Serialize(const RtSerializeContext& inContext) override;
	
	void	KillPlant(bool bSelfKill = false, bool bInstantKill = false, DamageTypeFlags i_lastDamageType = DAMAGE_NONE);

	int 	Rand();
	int		Rand(int range);
	float	Rand(float range);
    
	int     Shovel() override;
	bool 	IsDelayDestroy();
	
	// Callbacks from our AnimRig
	void OnUseSpecialAnimCommand(pvztime_t i_timeStamp);
	void OnUseActionAnimCommand(pvztime_t i_timeStamp);
	void OnAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	
	void onUpdate() override;
	void UpdateShooter();
	void UpdateAbilities();
	void UpdateDamageStates();
	void UpdateAnimRig();
    void UpdatePVP();
    
    virtual Sexy::Point GetGridExtents() const override;
    void SetIsThrownAway(bool i_thrown = true);
    bool IsThrownAway();

    void SetIsControlled(bool i_controlled);
    bool IsControlled();

	virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

	void internalPlantDraw(Sexy::Graphics* i_g);
	void onDraw(Sexy::Graphics* i_g) override;
	void onDrawShadow(Sexy::Graphics* i_g) override;
    bool ShouldDrawShadow() const override;
	
	void onDestroy() override;
	void Heal();
	void DoSpecial();
	void DoRowAreaDamage(float i_damage, DamageTypeFlags i_damageFlags);
    int	 GetMaxHitpoints();
	
	virtual void TakeDamage(const DamageInfo& i_damage) override;
	virtual void TakeDamageNoInvincible(const DamageInfo& i_damage) override;
	virtual void TakeFatalDamage(const DamageInfo& i_damage) override;
    void SetHealth(const float i_health);
	bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    bool ReceiveHelp(PlantHelpType i_helpType);
    
    virtual void TakeCure(int value, bool playEffect = true);
    virtual void TakeArrowCure(int value);
    
    void OnEventCall(RealObject* pTarget);
	
	void TakeSmashAttack(RtWeakPtr<class Zombie> i_srcZombie);
	void TakeGridItemSmashAttack(RtWeakPtr<class GridItem> i_srcGridItem);
	bool TryBlockZombossRush(Zombie* i_zomboss);
    
    bool CanApplyPlantfood();
    bool IsInHomeWorld();

	void PlayAttackAnimation();
    void StartPlantfoodState();
	void EnablePlantfoodAnimation(PlantAnimRig::PlantFoodMainAnimStartedDelegate i_mainAnimStarted = PlantAnimRig::PlantFoodMainAnimStartedDelegate(), PlantAnimRig::PlantFoodMainAnimLoopedDelegate i_mainAnimLooped = PlantAnimRig::PlantFoodMainAnimLoopedDelegate(), PlantAnimRig::PlantFoodMainAnimEndedDelegate i_mainAnimEnded = PlantAnimRig::PlantFoodMainAnimEndedDelegate());
	void DisablePlantfoodAnimation();
	void HidePlantfoodAnimationEffect();
	
	void ResetLaunchTimer(bool i_useInitialTiming);
	void ResetLaunchTimer(float i_forcedInterval);
    
    void SendHelpToPlants(PlantHelpType i_helpType, Rect& i_gridAreaToHelp, int i_windHelpLimit = INT_MAX);
	
    SexyVector2 GetRelocationBoardSpaceOffsetFromDestination();
	void FadeIn(pvztime_t i_duration);
    
    SexyVector3 GetRelocationPosition() const;
    void Relocate(int i_relocationGridX, int i_relocationGridY, pvztime_t i_relocationDuration, float i_relocateApexHeight, RelocationEvent::RelocationType i_relocationType);
	
	Projectile* Fire(RtWeakPtr<class Zombie> targetZombie, int row, PlantWeapon i_plantWeapon);
	Projectile* SpecialFire(RtWeakPtr<class Zombie> targetZombie, int row, std::string projectileAliases);
    bool 	CanFindTarget(PlantWeapon i_plantWeapon);
    bool	CanFindTargetInRow(int i_row, PlantWeapon i_plantWeapon);
    RtWeakPtr<class BoardEntity>	FindTarget(PlantWeapon i_plantWeapon);
    RtWeakPtr<class BoardEntity>	FindTargetInRow(int i_row, PlantWeapon i_plantWeapon);
	
	void SetGridLoc(int i_gridX, int i_gridY);
    void SetGridLocSilent(int i_gridX, int i_gridY);
	void SetIsPreviewPlant();
    void SetIsDuplicatePlant(bool i_duplicate);
    bool GetIsDuplicatePlant() { return m_isDuplicate; }
	void SetHighlighted(bool i_highlighted);
	void SetPlantfoodShineColor(const Color& i_color);
	
	Sexy::Point 	GetCenterPt();
	void 			GetFireOrigin(int &originX, int &originY);
	PlantAnimRig* 	GetAnimRig() { return m_animRig; }
	int				GetHeight() const;
	int				GetWidth() const;
    
    bool			AddFrost(int i_amount);
    
    virtual BoardEntityHeight GetEntityHeight() const override;
	
	virtual Sexy::Rect calcCollisionRect() override;
	Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon);
    
    virtual SexyVector3 CalcProjectileTargetLocation(float i_inTime = 0.f);

	PlantTypePtr GetType() const;
	PlantPropsPtr GetProps() const;
	
    void SetInvincible(bool is_invincible, bool is_needEffect, pvztime_t i_time);
	bool IsInvincible(bool dontConsiderPlantfood = false) const;
    bool IsPeachInvincible() { return m_bIsInvincible; }
    virtual bool IsInPlantFoodState() const {return m_isInPlantFoodState;}
    float GetRelocationSpeedInGridSquaresPerSecond() const;
    virtual bool BlockRailcartMovement() const;
	bool IsOnBoard();
    bool IsOnBoardGrid();
	bool CanBeTargeted();
    bool CanBeTargetedBy(const BoardEntity* i_entity);
    bool CanBeRangeTargeted();
	bool CanBeShoveled() override;
    void SetProtectedFromShovel(bool i_x) { m_protectedFromShovel = i_x; }
    
    void SetIsSleepping(bool i_isSleepping, float durationTime = -1.0f);
    bool IsSleepping() const { return m_isSleepping; }
	
	void SetSpeedModifier(float i_modifier);
    void ChangeSpeedModifier(float i_modifier, float i_time);
    
    bool ShouldClipWithWater() const override;
    float getTideDepthHeightMaxPct() override;
    
    /// Conditions
    void OnApplyZombieCondition(class Zombie* i_zombie, ZombieConditionsStruct& i_conditionsStruct);
	void NotifyApplyCondition(PlantConditions i_condition);
	void NotifyEndCondition(PlantConditions i_condition);
	void NotifyConditionEvent(PlantConditions i_condition);
	EntityCondition& ApplyCondition(PlantConditions i_condition, pvztime_t i_duration, pvztime_t i_eventDelay = 0);
	void EndCondition(PlantConditions i_condition);
	void ClearConditions();
	bool HasCondition(PlantConditions i_condition) const;
	bool IsSuspended();
	bool IsSlowed();
    bool IsIceblocked();
    bool IsSwapping();
	void SetDamageFlash(float i_duration);
	bool WasKilledByZombies();
    float GetZombieConditionExtendRate(ZombieConditions i_condition);

    void ApplyAddition(PlantAdditionType i_addition, float i_value, pvztime_t i_duration, PlantAddition::PAdditonRLS i_rule);
    float GetAdditionValue(PlantAddition::PAdditonRLS i_rule) const;

    void SetGeneSkillBoost(int i_skillBoost);
    float GetGeneSkillBoost();
    
    void NotifyDamagedEntity(BoardEntity *entity)  override;
    bool TryApplyDamageToEntity(DamageInfo &damageInfo, BoardEntity *entity) override;
    void NotifyComponentOwner() override;

	virtual int CalcRenderOrder() const override;

	DamageInfo calcDamageInfoFromPlantAction(const PlantAction& i_action);
    void        SetExtraLevelDamge(float ratio);
    float       GetExtraLevelDamge() const;
	float		GetExtraDPSmodifier() const;
	float		GetExtraHitPointsmodifier() const;

	int			GetMaxAffectZombieLevel();

	PlantConditionTracker& GetConditionTracker();

	//PVZ2_CHINESE_BEGIN
	void addRelocationEvent(const RelocationEvent& i_event);
	void clearRelocationEvents();
	inline bool isRelocating() const {return m_curRelocationEvent.m_relocationType != RelocationEvent::RELOCATION_Invalid;}
	void SetAvatarEnable(bool bAvatar);
    void SetAvatarActive(bool bActive);
	bool GetAvatarEnable();
    int GetMiniLevel(){ return m_iMiniLevel; }
    int GetMaxLevel(){ return m_iMaxLevel; }
	//PVZ2_CHINESE_END

	/// Static helper functions for reading values out of Plant Property Sheets
    static SexyString GetFormattedNameString(PlantTypePtr i_seedType);
	static SexyString GetFormattedToolTip(PlantTypePtr i_seedType);
	static SexyString GetFormattedDescription(PlantTypePtr i_seedType);
	static SexyString GetFormattedDescriptionHeader(PlantTypePtr i_seedType);
    //PVZ2_CHINESE_BEGIN
    static SexyString GetFormattedDescriptionEx(PlantTypePtr i_seedType, Color& i_DesColor,MapEventItem* pEvtItem);
    //PVZ2_CHINESE_END
    
    static int GetPlantPieceCountByLevel(PlantTypePtr i_seedType, int i_level);

    void    beThrown();
    
    void	bePushed();

    void    SetBombProjectile(const Projectile * i_projectile);
    
    void    SetShowUpgrade(bool i_show_upgrade);
    
    void    SetUpgradePercent(float i_upgrade_percent);
    
    void    PlayAttackUpEffect();
    
    void    SetAttackUpValue(bool bAttackUp, pvztime_t tAttackUpTime = PVZ_EOT(), float iAppendPercent = 0);

    void    SetAttackUpConstValue(bool bAttackUp, pvztime_t tAttackUpTime = PVZ_EOT(), float iAppendConstValue = 0);

    void    SetTupleSpellPlantFood(bool bTupleSpell);
    bool    GetTupleSpellPlantFood() {return m_bIsTupleSpellPlantFood;}
    
    void 	StartLossLife(pvztime_t duration, float percentOfMaxHealth);
    void 	EndLossLife();
    
    void 	StartCureLife(pvztime_t duration, float percentOfMaxHealth);
    void 	EndCureLife();

    void 	CheckUBoost();
    float   GetUBoostDamageTotal();

    void    FullHealth();
    void    SetSkillProbability(int i_probability);
    bool    IsSkillCheat();
    bool    IsSkillActivate();
    
    virtual void SetCurrentLevel(int i_level) override;
    
    void    SetPlantAvatarValue(int iAvatar);
    int     GetPlantAvatarValue() const { return m_iAvatar; }

    void    SetPlantAvatarShowIndex(int index);
    int     GetPlantAvatarShowIndex() const { return m_avatarIndex; }
    
    void    SetPlantLevelValue(int iLevel);
    int     GetPlantLevelValue() const { return m_iLevel; }
    
    int     IsDead() { return m_bDead; }
    
    void    IsImpactedByObject(RtWeakPtr<RtObject> i_object);
    virtual bool OverrideProjectileCollision(Projectile* i_projectile) override;
    
    bool DefaultBoardEntityProjectileCollisionOverride(class Projectile* i_projectile) { return SuperClass::OverrideProjectileCollision(i_projectile); }
    bool    TryBlockPush();
    bool    TryBlockPushOffBoard(class Zombie* i_srcZombie, const int i_direction);
    void  SetMaxHealth(float maxHealth);
    float GetMaxHealth() { return m_PlantMaxHealth > 0 ? m_PlantMaxHealth : (m_pCachedPlantPropertySheet->Hitpoints + m_extraHp) * m_extraHpRate * GetExtraHitPointsmodifier(); }

    void    SetExtraNormalDamge(float ratio) { m_extraNormalDamage = ratio; }
    float	GetExtraNormalDamage() { return m_extraNormalDamage + m_uBoostInfo.m_uBoostDamageTotal; }
    float	GetExtraSpecialDamage() { return m_extraSpecialDamage; }
    float	GetExtraHpRate() { return m_extraHpRate; }
    void    SetExtraHpRate(float rate) { m_extraHpRate = rate; }
    int		GetExtraHp() { return m_extraHp; }
    float	GetExtraAtkRate() { return m_extraAtkRate; }
    float   GetTotalDamageRate();
    float   GetDamageConstValue();
    float   GetFastCoolDown() { return m_reducedCooldown; }
    void    SetFastCoolDownRatio(float ratio);
    void 	RecoverFastCoolDownRatio();
    bool	CanLiveOnWater() { return m_plantOnWater; }
    void    SetCanLiveOnWater(bool i_liveWater) { m_plantOnWater = i_liveWater; }
    
    void PlantReturnSun();
    void ProduceExtraSun();

    bool IsProtect();
    bool IsInPlantDefence();
    void CopyBoostProperty(const Plant* src, PlantBoostType type);
    
    float	GetAwakenDamage() { return m_awakenDamage; }
    
    EffectAnimRig_PlantFoodShine * GetPlantFoodShine() { return m_pCachedEffectAnimRig_PlantFoodShine; }
    AttachedEffectManager& GetAttachedEffectManager() { return m_attachedEffects; }
    AttachedBoardEntityManager& GetAttachedBoardEntityManager() { return m_attachedBoardEntities; }
    AttachedEffect& AddAttachedEffect(const char* iEffectName, const char* iPanAnimName, const char* iAnimName, const SexyVector3& iOffset, int iRenderLayerOffset = 1, bool playOnce = false);
    void RemoveAttachedEffect(const char* iEffectName);
    virtual SexyVector3 GetStunnedEffectOffset() const;

	/// Internal functions
    void Water(bool water, pvztime_t duration = -1.0f);
    bool IsWatering();
    bool CanBeWatered();
    void PlaySongEffect(int level);
    
    float GetPoisonBoost();
    void OnKillZombie(Zombie* i_zombie);

    bool IsCatchedByParrot() {return m_isCathedByParrot;}
    void SetCachedByParrot(bool isCathed) {m_isCathedByParrot = isCathed;}
    
	float GetHealth() { return m_PlantHealth; }
	bool isShowShadowBoost() const { return m_bIsShowShadowBoost; }
	void setShowShadowBoost(bool isShowShadowBoost);
	virtual bool HasGravity() override;
	EntityComponent_GroundEffect GetGroundEffect() { return m_groundEffect; }
    float GetSlingShotExtraDamage();
    void resetSlingShot();

    // plant group functions begin
    void SetTravellingOutsideGroup(bool i_travelling) { SetFlag(m_plantFlags, PFLAG_TravellingOutsideGroup, i_travelling); };
    void StartRelocate(Sexy::Point i_relocationGrid, pvztime_t i_relocationDuration, float i_relocateApexHeight, RelocationEvent i_relocationEvent); 
    bool IsTravellingOutsideGroup() const { return IsBeingRemoved() || TestFlag(m_plantFlags, PFLAG_TravellingOutsideGroup); }
    bool IsBeingRemoved() const { return m_state == STATE_BEINGREMOVED; }
    void StartExternalRemoval();

    MultiPlantGridLayer GetMultiPlantGridLayer() { return m_multiPlantGridLayer; }
    void SetMultiPlantGridLayer(MultiPlantGridLayer i_multiPlantGridLayer) { m_multiPlantGridLayer = i_multiPlantGridLayer; }
    MultiPlantGridLayer GetMultiPlantDrawLayer() { return m_multiPlantDrawLayer; }
    void SetMultiPlantDrawLayer(MultiPlantGridLayer i_multiPlantDrawLayer) { m_multiPlantDrawLayer = i_multiPlantDrawLayer; }

    bool IsConvertedByCondition();
    bool AbsorbsSmashAttack();
    bool GetProtectedFromShovel() { return m_protectedFromShovel; }
    bool CanBeConvertedByCondition();
    bool IsFrostImmune();

    float GetFrostAmount() { return m_frostInfo.GetFrostAmount(); }
    void ClearFrost();

    // bool UsePlantfoodLayer();

    // plant gourp functions end

	void AddTag(const std::string& i_tag);
	void DelTag(const std::string& i_tag);
	bool HasTag(const std::string& i_tag);
	void ClearTag();

    void SetInvalidCollisionRect() { invalidateCollisionRect(); }

    void SetNotConsumeSun() { m_consumeSun = false; }
    bool IsConsumeSun() { return m_consumeSun; }
    bool IsVine() const; 
    bool IsIgnoreControlAndDmg() const; // for nightcap

    bool GetMarkedForDeath() {return m_markedfordeath;}
    bool SetMarkedForDeath(bool i_markedfordeath) { m_markedfordeath = i_markedfordeath;}
protected:
	virtual void onPostLoad() override;
    void onHiddenChanged(bool i_hidden, bool i_oldhidden) override;
	
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    
    virtual void onApplyCondition(PlantConditions i_condition);
    virtual void onEndCondition(PlantConditions i_condition); 

	virtual void CreateLevelEffect() override;
	void onLevelUp(int i_targetLevel) override;
	void onLevelUpFailed(int i_targetLevel) override;
	bool CanLevelUp(int i_targetLevel) override;
private:
	void initializeMembers();
	void constructAndSetFrameworkFromType();
    float updateRelocationPositionAndRotation();
	
	// Because of our plant/plantframework split, plantframeworks don't have RtIds and can't
	// create RtReflectionDelegates that point back to them. Ugh.
	// These functions call through to equivalent functions on the PlantFramework, so feel
	// free to use them as slightly clunky ReflectionDelegate targets
	void onStandaloneEffectFinishedCallback(class StandaloneEffect*);
	void onAnimStoppedCallback(const std::string&);
	void onPlantfoodStartedCallback();
	void onPlantfoodLoopedCallback();
	void onPlantfoodEndedCallback();

    void updateGroundEffect();
    void updateUBoost();
    
    /// Conditions
	void updateSpeed();
	void forceApplyConditionEffects();

    void PostDeadMessage(bool bSelfKill);
	
	/// Public members
public:
    template <typename T>
    T* GetPlantFramework();
    
	PlantFramework*			m_plantFramework;
    bool m_shouldUseStarPFEffect;
	
	ValueRange m_initialLaunchInterval;
	ValueRange m_launchInterval;

	///  Render Properties
    float m_baseScale;
	
	///  Plant State
	uint m_state;
    PlantFlags m_plantFlags;
    
    float m_PlantLastHealth;
    float m_showHealthBarTime;
	float m_PlantHealth;
    float m_PlantMaxHealth;
	float m_speedModifier;
    float m_baseSpeedModifier;
    float m_extraCurePercent;
    
    UBoostInfo m_uBoostInfo;

    DamageTypeFlags m_lastDamageType;
	
	int m_row;
	int m_column;
	
	bool m_isOnBoard;			// behind accessor (call pre init?? make param to init?
	bool m_isShooter;
    bool m_isThrownAway = false;
    bool m_isControlled = false;
    float m_extraValue = 0.0f;

	pvztime_t m_disappearTime;
	pvztime_t m_doSpecialTime;
	pvztime_t m_stateEndTime;
	pvztime_t m_launchTime;
	pvztime_t m_plantFoodEndTime;
	pvztime_t m_timeTillNextDamageFlash;
	pvztime_t m_fadeInDuration;
	pvztime_t m_fadeInEndTime;
    pvztime_t m_speedChangeTime;

	int	m_damageStates;
	int m_currentDamageState;

	bool m_mirror;

	int m_currentPlantActionIdx;
	
    int     m_starLevel;
    
    bool    m_canAttack;
	/// Internal members
protected:
	PlantTypePtr m_type;
	PlantAnimRigPtr m_animRig;
	PopAnimRigPtr m_animPotRig;
	RtWeakPtr<class EffectAnimRig_PlantFoodShine> m_plantFoodShine;
    RtWeakPtr<class EffectAnimRig_StarPlantFoodShine> m_starPlantFoodShine;
    bool m_isInPlantFoodState;
    bool			m_protectedFromShovel;
    bool			m_isDuplicate;
    pvztime_t       m_InvincibleTime;
    bool            m_bIsInvincible;
    
//PVZ2_CHINESE_BEGIN
    std::vector<RelocationEvent> m_relocationEvents;
    RelocationEvent m_curRelocationEvent;
    float m_xShakeOffset;
    float m_yShakeOffset;
    bool m_bAvatar;
    bool m_bAvatarActive;
    int m_iMiniLevel;
    int m_iMaxLevel;
//PVZ2_CHINESE_END

    bool  m_show_upgrade;
    float m_upgrade_percent;
    float m_lastUpgradepercent;
    pvztime_t   m_upgradeSetTime;
    
    RtWeakPtr<Projectile> m_BombProjectile;
	bool m_bIsShowShadowBoost;
private:
    PlantPropertySheet * m_pCachedPlantPropertySheet;
    PlantAnimRig * m_pCachedPlantAnimRig;
    EffectAnimRig_PlantFoodShine * m_pCachedEffectAnimRig_PlantFoodShine;

    EffectAnimRig_StarPlantFoodShine* m_pCachedEffectAnimRig_StarPlantFoodShine;
    
    MultiPlantGridLayer m_multiPlantGridLayer;
    MultiPlantGridLayer m_multiPlantDrawLayer;
    
    pvztime_t m_tAttackUpTime;
    bool      m_bIsAttackUp;
    float     m_iAppendAttackUpPercent;

    pvztime_t m_tAttackUpConstValueTime;
    bool      m_bIsAttackUpConstValue;
    float     m_iAppendAttackUpConstValue;
    bool      m_bIsTupleSpellPlantFood;

    pvztime_t m_tLossLifeTime;// the time that loss plant life in poison
    bool	 m_bIsLossLife; // check in loss life state
    float	 m_iLossLifePerFrame;// the loss of life in each frame

    pvztime_t m_tCureLifeTime;// the time that cure plant life in watermist
    bool    m_bIsCureLife;// check in cure life state
    float   m_iCureLifePerFrame;// the cure of life in each frame

    bool    m_bCheatSkill;
    int     m_skillProbability;
    int     m_skillProbIndex;
    bool    m_isSleepping;
    pvztime_t m_sleepingEndTime;
    
    int     m_iLevel;
    int     m_iAvatar;
    int     m_avatarIndex;
    
    bool m_hasPlayedThreePeaterSound;
    
    bool m_bDead;
    
    EntityComponent_GroundEffect m_groundEffect;
    
    FrostInfo	m_frostInfo;
    
    // Conditions;
	PlantConditionTracker m_conditionTracker;
	AttachedBoardEntityManager m_attachedBoardEntities;
	AttachedEffectManager m_attachedEffects;

    PlantBoostTrackerManager m_boostTrackerManager;

	// For boost damage
	float m_extraNormalDamage;
	float m_extraSpecialDamage;
    float m_extraLevelDamage;
	// For boost hitpoints
	float m_extraHpRate;
	int m_extraHp;
	// For boost attack speed
	float m_extraAtkRate;
	// For boost water plant
	bool m_plantOnWater;
	// For boost hp regenerate
    std::vector<std::vector<float>> m_extraReg;
	// For boost hp regenerate last regenerate time
	std::vector<pvztime_t> m_lastRegenTime;
    // For boost sunmoney
    std::vector<std::vector<float>> m_extraSun;
    // For boost fast cooldown
    float m_reducedCooldown;
    // For plant awaken
    float m_awakenDamage;
    // For boost invincible
    std::vector<std::vector<float>> m_invincible;
    std::vector<pvztime_t> m_invincibleLastTime;
    std::vector<float> m_invincibleCurDamage;
    // For boost ghost
    std::vector<std::vector<float>> m_ghost;
    // For boost plant sun refund
    std::vector<std::vector<float>> m_sunRefund;
    // For boost poison
    float m_improvePoison;
    // For boost stun zombie on eaten
    float m_stunBoostCoolDown;
    float m_stunBoostTimer;
    // For boost create plantfood on kill zombie
    float m_plantfoodRateOnKillZombie;
    float m_plantfoodRateOnKillZombieTimer;
    // For boost create sunmoney on kill zombie
    float m_sunmoneyRateOnKillZombie;
    // For boost create coin on kill zombie
    float m_coinRateOnKillZombie;
    //for boost damage reduction
    bool m_enableDamageRecord;
    pvztime_t m_lastDamageRecord;
    float m_damageRecordValue;
    float m_damageReduceValue;
    //for boost sling shot
    float m_perSlingShotDamage;
    float m_slingShotTimer;
    float m_slingShotCounter;
    //for boost extend condition
    std::vector<std::pair<PlantBoostType, float>> m_boostConditionExtend;
    std::vector<PlantAddition> m_addtions;

    //for gene skill boost 
    //for extend, can use std::vector<std::vector<float>> 
    //the outer vector is for different gene; the inner is for muti value, usually has one
    float m_geneSkillBoost;

    bool m_isCathedByParrot;

    pvztime_t m_waterDurationEnd;// water time duration.

    class Sexy::MTRand* m_randomObject;

    std::set<std::string> m_tags;    

    bool m_consumeSun;
    bool m_markedfordeath;
};

template<typename T>
T* Plant::GetPlantFramework()
{
	return ((RtObject*)m_plantFramework)->CastChecked<T>();
}

namespace Message
{
	void PlantDied(Plant* i_plant);
	void PlantDiedBy(Plant* i_plant,bool bSelfKill);
	void PlantPlantfooded(Plant* i_plant);
	void PlantAttacked(Plant* i_plant,int targets,int totalDamage);
	void PlantDamageTaken(Plant* i_plant, DamageInfo& i_damageRemaining);
    void PlantSmashedToDeath(Plant* i_plant);
    void PlantConvertedToProjectile(Plant* i_plant);
	void PlantAbsorbed(const Sexy::Point& i_gridPos, pvztime_t i_duration);
    void PlantFoodStart();
    void PlantFoodEnd(Plant* i_plant);
    void PlantDestory(Plant* i_plant);
    void PlantFire();
    void PlantCombos(Plant* i_plant);
    void PlantIcecubed(Plant* i_plant);
    void PlantFrost(Plant* i_plant);
    void PlantPlaced(Plant* i_plant);
    void PlantTryUseFood(Plant* i_plant);
    void PlantConditionApplied(Plant* i_plant, int i_condition);
    void PlantConditionEnded(Plant* i_plant, int i_condition);
    void PlantFlickOffByProtectorShield(Plant* i_plant);

    void PlantMoving(Plant* i_plant, Point& i_targetGridLocation);
    void PlantRevertedByCondition(Plant* i_plant, int i_baseCondition, int i_groupCondition);
    void PlantfoodUsed(const std::string& i_plantName);
}

#endif //__PLANT_H__
