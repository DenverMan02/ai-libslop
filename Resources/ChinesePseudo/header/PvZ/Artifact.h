/*
 * Artifact.h
 *
 *  Created on: 2021-5-31
 *      Author: admin
 */

#ifndef ARTIFACT_H_
#define ARTIFACT_H_

#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "Wave.h"
#include "ZombieEnums.h"
#include "Utils.h"
#include "RestrictionSet.h"
#include "DamageInfo.h"
#include "PlantBoostPropertySheet.h"
#include "GridItemAnimation.h"
#include "Projectile.h"
#include "ProjectilePropertySheet.h"
#include "RtDelegate.h"
#include "BaseCursor.h"
#include "PacketCursor.h"
#include "TimeLine.h"
#include "ZombieBasic.h"
#include "ZombieImp.h"
#include "ZombieGargantuar.h"
#include "ZombieAnimRig_Imp.h"
#include "ZombieAnimRig_RomanBasic.hpp"
#include "GameSubSystem.h"
#include "Plant_CthulhuActinia.h"
#include "ArtifactBoost.h"

namespace Message
{
	void  NotifyArtifactToolUsed();
	void  NotifyArtifactButtonDepress(int i_usedTimes);
	void  GetArtifactBoosts(int i_id, int i_type);
	void  StartBuff();
	void  NotifyRiftTimedUsedMax();
	void  NotifyMeteorCursor(int i_gridX, int i_gridY);
	void  NotifyAcidCursor(int i_gridX, int i_gridY);
	void  NotifyAcidZombieDie(class Zombie* i_zombie);
	void  NotifyAcidReturn(int i_gridX, int i_gridY, bool i_special);
	void  NotifyAcidChanged(int i_srcGridX, int i_srcGridY);
	void  MidasTouchSpecialDied(class Zombie* i_zombie);
	void  AddMusicalSuccessedCount(int i_cnt);
	void  NotifyWidenDragon();
	// void  GetMusicalSuccessedCount(int& io_cnt);	
}

typedef RtWeakPtr<class ArtifactProperties> ArtifactPropertiesPtr;
typedef RtWeakPtr<class ArtifactCultivationProperty> ArtifactCultivationPropertyPtr;
typedef RtWeakPtr<class ArtifactDisplayActionsProperty> ArtifactDisplayActionsPropertyPtr;

enum FieldType
{
	MainField = 0,
	PassiveField1,
	PassiveField2,
	PassiveField3
};

struct ArtifactStageData
{
	ArtifactStageData()
	{
		StageMaterialRequire = 0;
		LevelUnlocked = 0;
	}

	int StageMaterialRequire;
	int LevelUnlocked;
};

struct CommonData
{
	CommonData()
	:MaxUsedTimes(0)
	,Cooldown(0)
	{

	}

	int MaxUsedTimes;
	float Cooldown;
};

enum ArtifactObtainWay
{
	ARTIFACT_UNLOCK_FREE,
	ARTIFACT_GET_IN_STORE,
	ARTIFACT_GET_IN_ACTIVITY
};

class ArtifactProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ArtifactProperties, PropertySheetBase, RtClass);

	ArtifactProperties()
	{
		IsNeedPedestal = true;
	}

	std::string TypeName;
	std::string ClassName;

	std::string Description;
	std::string Name;

	std::vector<ArtifactStageData> StageDatas;

	virtual SexyString GetDescription();
	virtual SexyString GetName();

	std::vector<std::string> MainField;
	std::vector<std::string> PassiveField1;
	std::vector<std::string> PassiveField2;
	std::vector<std::string> PassiveField3;
	std::vector<PlantBoost> Boosts;
	std::vector<PlantBoost> GlobalBoosts;
	ArtifactDisplayActionsPropertyPtr DisplayActions;
	ArtifactCultivationPropertyPtr Cultivation;
//	std::string WayToGet;
	std::string GetLevel;
	std::string DemoLevel;
	ArtifactObtainWay ObtainWay;
	std::string DemoLevelWonMessage;
	std::vector<std::string> ResourceGroups;
	bool IsNeedPedestal;

	PlantRestrictionSet TargetablePlantTypes;
};


struct ArtifactLevelUpPrice
{
	int CurrentLevel;
	int NeedRank;
	std::string MaterialName;
	int MaterialPrice;
};

struct ArtifactRankUpPrice
{
	int CurrentRank;
	int NeedLevel;
	std::string MaterialName;
	int MaterialPrice;
	int GoldNum;
};

class ArtifactCultivationProperty : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ArtifactCultivationProperty, PropertySheetBase, RtClass);

	std::vector<ArtifactLevelUpPrice> LevelUpPrice;
	std::vector<ArtifactRankUpPrice> RankUpPrice;
};


struct ArtifactPlantDisplayInfo
{
    std::string PlantName;
	int Level;
	bool Avatar;
    int Hitpoint;
    int PosX;
    int PosY;
    
    ArtifactPlantDisplayInfo()
    {
        Hitpoint = 0;
		Level = 1;
		Avatar = false;
        PosX = 0;
        PosY = 0;
    }
};

struct ArtifactZombieDisplayInfo
{
    std::string ZombieName;
	int Level;
    int Hitpoint;
    int PosX;
    int PosY;
	
    ArtifactZombieDisplayInfo()
    {
        Hitpoint = 0;
		Level = 1;
        PosX = 0;
        PosY = 0;
    }
};

struct ArtifactDisplayActionInfo
{
    std::string DisplayImage;
    std::vector<ArtifactPlantDisplayInfo> DisplayPlants;
    std::vector<ArtifactZombieDisplayInfo> DisplayZombies;
    float DisplayTime;
    int ArtifactLevel;
	bool AutoTriger;
	bool AutoClick;
	float TriggerDelay;
	std::string SkillName;
	std::string SkillIcon;
	std::string SkillDescription;
	int DisplayLevel;
	int DisplayRank;
    bool DisplayPassiveSkill;
	float DisplayPassiveSkillDelay;

    ArtifactDisplayActionInfo()
    {
        DisplayImage = "";
        DisplayTime = 0;
        ArtifactLevel = 1;
		AutoTriger = false;
		DisplayLevel = 1;
		DisplayRank = 1;
		TriggerDelay = 1;
		AutoClick = false;
		DisplayPassiveSkill = false;
		DisplayPassiveSkillDelay = 0;
    }
};

class ArtifactDisplayActionsProperty : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(ArtifactDisplayActionsProperty, PropertySheetBase, RtClass);
    
    std::vector<ArtifactDisplayActionInfo> Actions;
};


class Artifact : public GameObject
{
public:
	RT_CLASS_DEFINE(Artifact, GameObject, RtClass);
	Artifact();
	virtual ~Artifact();
	virtual void Initialize(ArtifactPropertiesPtr i_propsPtr);
	ArtifactPropertiesPtr GetProps() { return m_props; }
	virtual void Activate();
	void TriggerMain();
	virtual bool CanTriggerMain();
	virtual void DoTrigger();
	float GetTriggerLeftTime();
	virtual float GetTriggerCooldown();
	virtual int GetMaxUsedTimes();
	int GetUsedTimes();
	virtual void AutoClick() {}
	bool IsActivated() { return m_activated; }
	virtual void DisplayPassiveSkill(float i_delay) {}

	virtual void Update();
    void onPostLoad() override;

	void SetCurrentLevel(int i_level) { m_currentLevel = i_level; }
	int GetCurrentLevel() { return m_currentLevel; }

	void SetCurrentStage(int i_stage) { m_currentStage = i_stage; }
	int GetCurrentStage() { return m_currentStage; }
	bool IsFieldActivated(FieldType i_type);
	virtual void EnsureResourceGroupsLoaded();
	bool CanStartBuff() { return m_startBuff; }
	bool IsOnDisplayBoard() { return m_isOnDisplayBoard; }
	void SetIsOnDisplayBoard(bool i_isOnDisplayBoard) { m_isOnDisplayBoard = i_isOnDisplayBoard; }
	bool IsNeedPedestal() { return GetProps()->IsNeedPedestal; }
	virtual void ActivateSpeciallyOnDisplayBoard(int i_index) {}	// 0, 1, 2, 3

//	virtual bool					OnTouch(const Sexy::Touch& i_touch) override;

protected:
	void OnNotifyArtifactToolUsed();
	void OnNotifyArtifactButtonDepress(int i_usedTimes);
	void OnGetArtifactBoosts(int i_id, int i_type);
	void OnStartBuff();
	virtual bool CanGetArtifactBoosts(int i_id) { return true; }

	virtual float GetExtraHpRate(const std::string& i_typeName) { return 0; }
	virtual float GetExtraAttackRate(const std::string& i_typeName) { return 0; }
	virtual float GetExtraReducedCooldown(const std::string& i_typeName) { return 0; }
	virtual float GetExtraFastPlant(const std::string& i_typeName) { return 0; }

	const std::vector<std::string>&	GetArtResourceGroups();

	float GetBoostValue(ArtifactBoostType i_type);

	ArtifactPropertiesPtr m_props;
	bool m_activated;
	int m_currentLevel;
	int m_currentStage;
	CommonData m_commonData;
	float m_extraAttackRate;
	float m_extraHpRate;

	int m_usedTimes;
	pvztime_t m_nextMainFieldTime;
	bool m_doTrigger;
	bool m_startBuff;
	bool m_isOnDisplayBoard;
	bool m_autoClickInit;

	virtual void					registerForEvents() override;
	virtual void					unregisterForEvents() override;
};



enum GridItemArtifactTornadoState
{
    PVZ_BEGIN_ENUM(TORNADOSTATE_),
    TORNADOSTATE_UNKNOWN,
    TORNADOSTATE_RESETTING,
    TORNADOSTATE_IDLE,
    TORNADOSTATE_DEAD,
    PVZ_END_ENUM(TORNADOSTATE_)
};

class GridItemArtifactTornado : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemArtifactTornado, GridItemAnimation, RtClass);

    GridItemArtifactTornado();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(TORNADOSTATE_IDLE); }
    void SetLifeTime(float i_time) { m_lifeTime = i_time; }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemArtifactTornadoState i_state);
    void tryAbsorbZombies();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onResetFinished(const std::string &i_animName);
    void onDeadFinished(const std::string &i_animName);
    void onZombieLanding(Zombie *i_zombie);

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    bool CanBeControlled(Zombie* i_zombie);

    pvztime_t m_creationTime;
    GridItemArtifactTornadoState m_state;
    float m_lifeTime;
};

class GridItemArtifactTornadoProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemArtifactTornadoProps, GridItemAnimationProps, RtClass);
    GridItemArtifactTornadoProps()
    : Lifetime(1.0)
    , EffectRectRight(1)
    , EffectRectLeft(1)
    , EffectRectTop(1)
    , EffectRectBottom(1)
    , Damage(0.0f)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    pvztime_t Lifetime;
    std::vector<std::string> ZombieBlacklist;
    float Damage;
};

class ArtifactWindProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactWindProperties, ArtifactProperties, RtClass);

	ArtifactWindProperties()
		: HealthPercent(1.0f)
		, TornadoGridX(0)
		, TornadoGridY(0)
		, TornadoDelay(0)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float HealthPercent;
	int TornadoGridX;
	int TornadoGridY;
	float TornadoDelay;
};

class ArtifactWind : public Artifact
{
public:
	enum WindState
	{
		Generate_None,
		Generate_Wind,
		Generate_Tornado
	};

	RT_CLASS_DEFINE(ArtifactWind, Artifact, RtClass);
	~ArtifactWind();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void GenerateWind();
	void GenerateRandomWind();
	void GenerateTornado();
	void ResetValues();

	WindState m_state;
	pvztime_t m_tornadoStartTime;
	pvztime_t m_randomWindStartTime;
	float m_randomWindInterval;
	float m_flickRate;
};

class ArtifactLightningProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactLightningProperties, ArtifactProperties, RtClass);

	ArtifactLightningProperties()
	: LightningBuffDuration(0)
	, BleedingDuration(0)
	, TriggerCondition(ZCONDITION_Stucked)
	, SecondLightningDelay(5.0f)
	, FieldLightningNum(5)
	, FieldLightningDelay(20.0f)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float LightningBuffDuration;
	float BleedingDuration;
	ZombieConditions TriggerCondition;
	float SecondLightningDelay;
	int FieldLightningNum;
	float FieldLightningDelay;
};

class ArtifactLightning : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactLightning, Artifact, RtClass);
	~ArtifactLightning();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void GenerateLightning();
	void GeneratePassiveFieldLightning();
	void GeneratePassiveLightning(Zombie* i_zombie);
	void GeneratePassiveCharge(Zombie* i_zombie);
	void onZombieConditionApplied(Zombie* i_zombie, int i_condition, pvztime_t i_duration);
	void onLightningAnimCommand(const std::string& i_animLabel,
								pvztime_t i_timeStamp,
								const std::string& i_animCommand,
								const std::string& i_animCommandParam);
	void ZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);

	std::vector<RtWeakPtr<class Zombie>> m_hitZombies;
	float m_passiveLightningRate;
	float m_passiveLightningDamageRate;
	float m_passiveChargeRate;
	float m_mainSecondLightningStartTime;
	float m_passiveFieldLightningStartTime;
};



enum ArtifactVaseType
{
	ArtifactVaseType_Plant = 0,
	ArtifactVaseType_Zombie,
	ArtifactVaseType_Collectable,
	ArtifactVaseType_Count
};

struct ArtifactVaseConfigProperties
{
	ArtifactVaseConfigProperties()
	{
		TypeName = "";
        Weight   = 5;
        VaseType = ArtifactVaseType_Plant;
        Level = 1;
        HasPlantfood = false;
    }

    inline bool operator==(const ArtifactVaseConfigProperties& p) const
	{
		return ((p.TypeName == TypeName) && (p.VaseType == VaseType) && (p.Level == Level) && (p.Weight == Weight) && (p.HasPlantfood == HasPlantfood));
	}

	inline bool operator!=(const ArtifactVaseConfigProperties& p) const
	{
		return ((p.TypeName != TypeName) || (p.VaseType != VaseType) || (p.Level != Level) || (p.Weight != Weight) || (p.HasPlantfood != HasPlantfood));
	}

    std::string TypeName;
    int         VaseType;
    int         Weight;
    int 		Level;
    bool		HasPlantfood;
};

class ArtifactVaseProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ArtifactVaseProjectile, Projectile, RtClass);

    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

    void Initialize(ProbabilitySet<ArtifactVaseConfigProperties>& i_bucket);

private:
    void spawnPlants(const ArtifactVaseConfigProperties& i_config, SexyVector3 i_position);
    void spawnZombies(const ArtifactVaseConfigProperties& i_config, SexyVector3 i_position);
    void spawnCollectables(const ArtifactVaseConfigProperties& i_config, SexyVector3 i_position);

    ProbabilitySet<class ArtifactVaseConfigProperties> Bucket;
};

class ArtifactVaseProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactVaseProperties, ArtifactProperties, RtClass);

	ArtifactVaseProperties()
	{
		VaseShotHeight = 80.f;
		VaseShotTime = 1.f;
		VaseCount = 10;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;


	RtWeakPtr<RtObject> VaseProjectile;
	SexyVector3 InitialPosition;
	std::vector<ArtifactVaseConfigProperties> VaseConfigs;
	std::vector<ArtifactVaseConfigProperties> AdvancedVaseConfigs;
	float VaseShotHeight;
	float VaseShotTime;
	int VaseCount;
};

class ArtifactVase : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactVase, Artifact, RtClass);
	~ArtifactVase();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	void SetBucket(const ProbabilitySet<ArtifactVaseConfigProperties>& i_bucket) { m_bucket = i_bucket; }
	void EnsureResourceGroupsLoaded() override;
    void onPostLoad() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void InitConfigs();
	int GetSpawnLevel();
	bool IsGridValid(Point i_grid);
	void GetRandomGrids(std::vector<Point>& i_grids);
	void LaunchVases(bool i_single);
	void LaunchToGrid(Point i_grid);
	void launchProjectile(SexyVector3 i_source, SexyVector3 i_targetPosition, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit, TeamFlags i_team, BoardEntityPtr i_target);

	ProbabilitySet<ArtifactVaseConfigProperties> m_bucket;
	pvztime_t m_passiveVaseStartTime;
	float m_passiveVaseInterval;
};


enum GridItemMeteorState
{
    PVZ_BEGIN_ENUM(METEORSTATE_),
    METEORSTATE_UNKNOWN,
    METEORSTATE_RESETTING,
    METEORSTATE_IDLE,
    METEORSTATE_DEAD,
    PVZ_END_ENUM(METEORSTATE_)
};

class GridItemMeteor : public GridItemAnimation
{
public:
	enum MeteorType
	{
		MeteorType_Orange,
		MeteorType_Blue,
		MeteorType_Purple
	};

    RT_CLASS_DEFINE(GridItemMeteor, GridItemAnimation, RtClass);

    GridItemMeteor();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(METEORSTATE_IDLE); }
    void SetLifeTime(float i_lifeTime) { m_lifeTime = i_lifeTime; }
    void SetBurningDamage(float i_damage) { m_burningDamage = i_damage; }
    void SetBurningDuration(float i_duration) { m_burningDuration = i_duration; }
    void SetPercentBurningDamage(float i_damage) { m_percentBurningDamage = i_damage; }
    void SetPercentBurningDuration(float i_duration) { m_percentBurningDuration = i_duration; }
    void SetType(MeteorType i_type) { m_type = i_type; }

    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemMeteorState i_state);
    void applyBurning();
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    void convertProjectile(class Projectile *i_projectile, ProjectilePropertySheetPtr i_newProperties);
    pvztime_t m_creationTime;
    GridItemMeteorState m_state;
    float m_lifeTime;
    float m_burningDamage;
    float m_burningDuration;
    float m_percentBurningDamage;
    float m_percentBurningDuration;
    MeteorType m_type;
    std::vector<RtWeakPtr<Projectile> > m_affectedProjectiles;
};

class GridItemMeteorProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemMeteorProps, GridItemAnimationProps, RtClass);
    GridItemMeteorProps()
    : EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    std::vector<std::string> ZombieBlacklist;
};

struct ArtifactMeteorProjectileInfo
{
	ArtifactMeteorProjectileInfo()
	: m_splashRadius(0)
	, m_mainDamage(0)
	, m_destroyZombieCount(0)
	, m_stunDuration(0)
	, m_meteorDuration(0)
	, m_meteorBurningDamage(0)
	, m_meteorBurningDuration(0)
	, m_artifactLevel(1)
	{

	}

	float m_splashRadius;
	float m_mainDamage;
	int m_destroyZombieCount;
	float m_stunDuration;
	float m_meteorDuration;
	float m_meteorBurningDamage;
	float m_meteorBurningDuration;
	float m_meteorPercentBurningDamage;
	float m_meteorPercentBurningDuration;
	int m_artifactLevel;
};

class ArtifactMeteorProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ArtifactMeteorProjectile, Projectile, RtClass);

    void SetInfo(const ArtifactMeteorProjectileInfo& i_info) { m_info = i_info; }
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
    bool ignoreDeathBox() override;

private:
    void affectMainEntities();
    void affectSubEntities(SexyVector3 i_srcPosition);
    void damageEntity(Zombie* i_zombie);
    void spawnMeteor();
    void spawnMeteor(const Point& gridPosition);
    void fillMeteorInfo(GridItemMeteor* i_meteor);

    ArtifactMeteorProjectileInfo m_info;
};

class ArtifactMeteorProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactMeteorProperties, ArtifactProperties, RtClass);

	ArtifactMeteorProperties()
	{
		MeteorAngle = 45.0f;
		MeteorShotTime = 1.0f;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	RtWeakPtr<RtObject> MeteorProjectile;
	SexyVector3 InitialPositionOffset;
	float MeteorAngle;
	float MeteorShotTime;
	float MeteorShotHeight;
};

class MeteorCursor : public BaseCursor
{
public:
    RT_CLASS_DEFINE(MeteorCursor, BaseCursor, Sexy::RtClass) {}

    MeteorCursor() {}
    explicit MeteorCursor(const Sexy::Touch& i_boardSpaceTouch);
    virtual ~MeteorCursor();

protected:
    Sexy::SexyVector2 getCursorAnimOffset() const override;
    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;

private:

    Sexy::SexyVector2 m_cursorOffset;
};

class ArtifactMeteor : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactMeteor, Artifact, RtClass);
	~ArtifactMeteor();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

private:
	void OnNotifyMeteorCursor(int i_gridX, int i_gridY);
	bool IsGridValid(Point i_grid);
	void GetRandomGrids(std::vector<Point>& i_grids, Point i_srcPoint = Point(-1, -1));
	bool LaunchMeteor(bool i_single);
	void LaunchToGrid(Point i_grid);
	void launchProjectile(SexyVector3 i_source, SexyVector3 i_targetPosition, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit, BoardEntityPtr i_target);

	int m_mainSearchRange;
	int m_mainMeteorCount;
	float m_mainSplashRadius;
	float m_mainDamage;
	int m_mainDestroyZombieCount;
	float m_mainStunDuration;
	float m_mainMeteorDuration;
	float m_mainMeteorBurningDamage;
	float m_mainMeteorBurningDuration;

	pvztime_t m_passiveMeteorStartTime;
	float m_passiveMeteorInterval;
	float m_passiveMeteorPercentBurningDamage;
	float m_passiveMeteorPercentBurningDuration;
	Point m_mainSrcPoint;
};

// Artifact Acid
class ZombieAnimRig_ArtifactAcidBasic : public ZombieAnimRig_RomanBasic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ArtifactAcidBasic, ZombieAnimRig_RomanBasic, RtClass);

private:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
};

class ZombieArtifactAcidBasic : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieArtifactAcidBasic, ZombieBasic, RtClass);

protected:
	DamageTypeFlags getEatingDamageType() const override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
};

class ZombieAnimRig_AcidImp : public ZombieAnimRig_Imp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_AcidImp, ZombieAnimRig_Imp, RtClass);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

class ZombieArtifactAcidImp : public ZombieImp
{
public:
	RT_CLASS_DEFINE(ZombieArtifactAcidImp, ZombieImp, RtClass);

protected:
	DamageTypeFlags getEatingDamageType() const override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
};

class ZombieArtifactAcidGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieArtifactAcidGargantuar, ZombieGargantuar, RtClass);

protected:
	DamageTypeFlags getEatingDamageType() const override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
};

enum GridItemAcidState
{
    PVZ_BEGIN_ENUM(ACIDSTATE_),
    ACIDSTATE_UNKNOWN,
    ACIDSTATE_RESETTING,
    ACIDSTATE_IDLE,
    ACIDSTATE_BEGAIN_DEVOUR,
    ACIDSTATE_DEVOURING,
    ACIDSTATE_DEVOURED,
    ACIDSTATE_RETURN,
    ACIDSTATE_DEAD,
    ACIDSTATE_OCCUPIED,
    PVZ_END_ENUM(ACIDSTATE_)
};

enum GridItemAcidType
{
	GridItemAcidType_Empty,
	GridItemAcidType_LeftEdge,
	GridItemAcidType_RightEdge,
	GridItemAcidType_Center,
	GridItemAcidType_Individual
};

class GridItemAcid : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemAcid, GridItemAnimation, RtClass);

    GridItemAcid();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(ACIDSTATE_IDLE); }
    bool IsDevouring();
    void SetOccupied(bool i_occupied) { i_occupied ? setState(ACIDSTATE_OCCUPIED) : SetIdle(); }

    void ManualDestroy();

    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

    GridItemAcidType GetAcidType() { return m_acidType; }
    void SetAcidType(GridItemAcidType i_type) { m_acidType = i_type; }
    std::string GetStateAnimLabelName(GridItemAcidState i_state);

    void SetDevourReducedRate(float i_rate) { m_passiveDevourReducedRate = i_rate; }
    void SetArmorDamageTakenScale(float i_scale) { m_passiveArmorDamageTakenScale = i_scale; }
    void SetExplodeDamageTakenScale(float i_scale) { m_passiveExplodeDamageTakenScale = i_scale; }
    void SetExplodeConditionDamageTakenScale(float i_scale) { m_passiveExplodeConditionDamageTakenScale = i_scale; }
    void SetExplodeDuration(float i_duration) { m_passiveExplodeDuration = i_duration; }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemAcidState i_state);
    void applyAcid();
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void registerForEvents() override;

private:
    void OnNotifyAcidReturn(int i_gridX, int i_gridY, bool i_special);
    void onNotifyAcidChanged(int i_srcGridX, int i_srcGridY);
    void initAcidType();
    void onCreated(const std::string& animName);
    void onReturned(const std::string& animName);
    void occupyNearbyAcid(bool i_occupy);
    bool isNearbyAcidDevouring(bool i_left);
    GridItemAcidType checkNearbyAcid(bool i_left);
    bool canDevour(Zombie* i_zombie);
    bool isStraightDevouredZombie(Zombie* i_zombie);
    void setupZombieToBeDevoured(RtWeakPtr<class Zombie> i_zombie);
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    void tryBeginDevour(Zombie* i_zombie);
    void beginDevour();
    void devouring();
    void killZombie(RtWeakPtr<class Zombie> i_zombie);
    bool tryTransform(Zombie* i_zombie);
    std::string getTransformType(Zombie* i_zombie);
    void transform(Zombie* i_zombie);
    void createTransformEffect(const SexyVector3& i_position);
    bool canTransform(Zombie* i_zombie);
    void playDropEffect(bool i_bigSize);

    GridItemAcidState m_state;
    RtWeakPtr<class Zombie> m_zombieToEat;
	CurveSequence_SexyVector3 m_zombieBeginDevourCurve;
	CurveSequence_SexyVector3 m_zombieDevouringCurve;
	float m_zombieDistanceToDropTotal;
	float m_passiveDevourReducedRate;
	float m_passiveArmorDamageTakenScale;
	float m_passiveExplodeDamageTakenScale;
	float m_passiveExplodeConditionDamageTakenScale;
	float m_passiveExplodeDuration;

	GridItemAcidType m_acidType;
};

class GridItemAcidProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemAcidProps, GridItemAnimationProps, RtClass);
    GridItemAcidProps()
    : EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
    , BeginDevourTime(0.5f)
    , DevouringTime(15.0f)
    , StraightDevouringTime(0.2f)
    , Radius(0.0f)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    std::vector<std::string> ZombieBlacklist;
    float BeginDevourTime;
    float DevouringTime;
    float StraightDevouringTime;
    std::vector<std::string> SkipDevouringList;
    float Radius;
};

class ArtifactAcidProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactAcidProperties, ArtifactProperties, RtClass);

	ArtifactAcidProperties()
	: AcidReturnAddCD(0.0f)
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	float AcidReturnAddCD;
};

class AcidCursor : public PacketCursor
{
public:
    RT_CLASS_DEFINE(AcidCursor, PacketCursor, Sexy::RtClass) {}

    AcidCursor() {}
    explicit AcidCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);
    virtual ~AcidCursor();

    PlantTypePtr GetPlantType() const { return m_plantType; }

protected:
    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void tryToUse() override;

	Point GetCurrentGridPosition() override;
	void cacheOrDestroyCursor();
	bool canAffordPlant(PlantTypePtr i_plantType) const;
	Sexy::SexyVector2 getCursorAnimOffset() const override;
    bool CanUseAtCurrentPosition() override;
	bool IsInsideOriginRect() const override;

private:

	PlantTypePtr m_plantType;
};

class ArtifactAcid : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactAcid, Artifact, RtClass);
	~ArtifactAcid();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	float GetTriggerCooldown() override;
	int GetMaxUsedTimes() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void OnNotifyAcidReturn(int i_gridX, int i_gridY, bool i_special);
	void OnNotifyAcidZombieDie(class Zombie* i_zombie);
	void OnNotifyAcidCursor(int i_gridX, int i_gridY);
	void spawnAcid();
	void spawnAcid(const Point& gridPosition);
	bool shouldApplyAcidDamage(Zombie* i_zombie);
	bool shouldApplyAcidCondition(Zombie* i_zombie);
	void applyAcidExplosion(Zombie* i_zombie);

	Point m_mainSrcPoint;
	float m_passiveDevourReducedRate;
	float m_passiveArmorDamageTakenScale;
	float m_passiveExplodeDamageTakenScale;
	float m_passiveExplodeDamage;
	float m_passiveExplodeConditionDamageTakenScale;
	float m_passiveExplodeDuration;
};


class ArtifactCureProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactCureProperties, ArtifactProperties, RtClass);

	ArtifactCureProperties()
	{
		PassiveCureInterval = 20.0f;
		PassiveAttackBuffPercent = 1.0f;
		PassiveSpeedBuffPercent = 1.0f;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float PassiveCureInterval;
	float PassiveAttackBuffPercent;
	float PassiveSpeedBuffPercent;
};

class ArtifactCure : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactCure, Artifact, RtClass);
	~ArtifactCure();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

private:
	void CurePlants(float i_percent, bool i_invincible);
	void BuffPlants();
	void OnCreatePlant(Plant* plant);

	float m_mainCurePercent;
	float m_mainInvincibleDuration;
	float m_passiveImprovedCurePercent;
	float m_passiveCurePercent;
	float m_passiveBuffDuration;
	float m_passiveImprovedInvinciblePercent;
	pvztime_t m_passiveCureStartTime;
};

struct SpeedFactor
{
	SpeedFactor()
	: NormalFactor(0)
	, AdvancedFactor(0)
	{

	}

	float NormalFactor;
	float AdvancedFactor;
};

struct PlantShieldData
{
	PlantShieldData()
	: TriggerShieldTime(0)
	, PreHP(0)
	{

	}

	pvztime_t TriggerShieldTime;
	RtWeakPtr<class Plant> Plant;
	float PreHP;
};

class ArtifactShieldProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactShieldProperties, ArtifactProperties, RtClass);

	ArtifactShieldProperties()
	{
		ShieldVelocity = 0;
		ShieldRadius = 0;
		MinSpeedFactor = 0;
		MinPlantHitPoints = 0;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float ShieldVelocity;
	float ShieldRadius;
	SpeedFactor SmallSizeSpeedFactor;
	SpeedFactor MidSizeSpeedFactor;
	SpeedFactor LargeSizeSpeedFactor;
	float MinSpeedFactor;
	float MinPlantHitPoints;
};

class ArtifactShield : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactShield, Artifact, RtClass);
	~ArtifactShield();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	bool CanGetArtifactBoosts(int i_id) override;
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void GenerateShield();
	void GeneratePassiveShield(int i_col, int i_row);
	void OnNotifyShieldBlock(int i_type);
	float GetSpeedFactor(ZombieSizeType i_type);
	void OnCreatePlant(Plant* plant);
	void OnPlantDestroyed(Plant* plant);
	void CheckGeneratePassiveShield();

	RtWeakPtr<class GridItemProtectorShield> m_shield;
	float m_mainShieldDuration;
	pvztime_t m_shieldEndTime;
	float m_minShieldVelocity;
	std::vector<PlantShieldData> m_plantDatas;
	float m_passiveNoDamageDuration;
	float m_passiveShieldHP;
};

class ArtifactSquidProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactSquidProjectile, Projectile, RtClass);

	bool OnCollideGround() override;
	bool OnCollideEntity(BoardEntity* i_entity) override;
	void SetSquidHp(float i_hp) { m_SquidHP = i_hp; }
	void SetBleedingDPS(float i_dps) { m_bleedingDps = i_dps; }

private:
	float m_SquidHP = 0;
	float m_bleedingDps = 0;
};

class ArtifactSquidProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactSquidProperties, ArtifactProperties, RtClass);

	ArtifactSquidProperties()
	{
		SquidShotHeight = 80.f;
		SquidShotTime = 1.f;
		AmountToAimLeftOfZombie = 0.0f;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;


	RtWeakPtr<RtObject> SquidProjectile;
	SexyVector3 InitialPosition;
	float SquidShotHeight;
	float SquidShotTime;
	float AmountToAimLeftOfZombie;
};

class ArtifactSquid : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactSquid, Artifact, RtClass);
	~ArtifactSquid();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	//bool IsValidTarget(class Zombie* i_zombie) const;
	void GetValidTargets(std::vector<class Zombie*>& i_zombies);
	bool CanBeControlled(class Zombie* i_zombie);
	void Launch(bool i_passive);
	void LaunchToTarget(RtWeakPtr<class Zombie> i_zombie);
	void launchProjectile(SexyVector3 i_source, SexyVector3 i_targetPosition, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit, TeamFlags i_team, BoardEntityPtr i_target);

	float m_mainSquidHP;
	float m_passiveLaunchCd;
	int m_passivePickNum;
	pvztime_t m_passiveLaunchStartTime;
	float m_passiveDamageDPS;
};

/// artifact time
class ArtifactTimeProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactTimeProperties, ArtifactProperties, RtClass);

	ArtifactTimeProperties()
	{
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	pvztime_t WarpZombieDuration;// the time duration zombie's warping in.
	std::vector<ZombieConditions> ConditionsRemovedByWarping;// when zombie being warping, we should remove these conditions
	float SpeedUpPlantRatio;// plant speed up ratio
};

class ArtifactTime : public Artifact
{
public:
	enum {
		EFFECT_TIME_STOP,
		EFFECT_TIME_SPEEDUP,
	};
	RT_CLASS_DEFINE(ArtifactTime, Artifact, RtClass);
	~ArtifactTime();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

private:
	float GetExtraReducedCooldown(const std::string& i_typeName) override;

	void WarpZombiesIn();
	void warpZombieIn(RtWeakPtr<Zombie> zombie);
	void reapearZombie(RtWeakPtr<Zombie> zombie);
	void placeZombieInNewPosition(RtWeakPtr<Zombie> zombie);
	void createWarpingInEffectAt(RtWeakPtr<Zombie> zombie);
	void createWarpingEffectAt(RtWeakPtr<Zombie> zombie, std::string animationName);
	bool shouldDoStuffTo(RtWeakPtr<Zombie> zombie);
	std::string getWarpingEffectNameFor(RtWeakPtr<Zombie> zombie);

	void DoSpecial1();// passive 2 : stun all plants and zombies in right 3 x 5 grids
	void DoSpecial2();// passive 3 : speed up all plants in left 3 x 5 grids
	void CreateSpecialEffect(int type);// create time effect

	std::vector<RtWeakPtr<Zombie> > m_warpingZombies;// warping zombie list
	pvztime_t m_warpZombiesDuration;// the time duration zombie's warping in.
	float m_reduceCooldownRatio;// reduce cool down ratio
	pvztime_t m_stopDuration;// the stop effect duration
	float m_speedUpRatio;// the speed up effect ratio.
};

/// auto destroy griditem
class GridItemAutoDestroy : public GridItemAnimation
{
public:
	enum {
		STATE_NONE,
		STATE_IDLE,
		STATE_UPDATE,
		STATE_DESTROY,
		STATE_DEFINE_BEGIN,// we can define by ourselves
	};

    RT_CLASS_DEFINE(GridItemAutoDestroy, GridItemAnimation, RtClass);
    GridItemAutoDestroy();

    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetLifeTime(float i_time) { m_lifeTime = i_time; }
    void SetStartCallback(Sexy::Delegate0 func);
    void SetEndCallback(Sexy::Delegate0 func);

protected:
    void onGridItemInitialize() override;
    void onUpdate() override;
    void onDestroy() override;

    int m_state;
    pvztime_t m_lifeTime;// duration time
    pvztime_t m_startTime;// initialize time
    Delegate0 m_startFunc;// start callback
    Delegate0 m_endFunc;// end callback

};

class GridItemArtifactTimeStop : public GridItemAutoDestroy
{
public:
    RT_CLASS_DEFINE(GridItemArtifactTimeStop, GridItemAutoDestroy, RtClass);
    GridItemArtifactTimeStop();
    ~GridItemArtifactTimeStop();

    void ApplyEffectToPlant(Plant* plant);
    void EndEffectToPlant(Plant* plant);
    bool IsInEffectArea(int gridX, int gridY);

protected:
    void onDestroy() override;
    void OnCreatePlant(class Plant* plant);
    void ApplyEffectToZombie(Zombie* i_zombie);
};

class GridItemArtifactTimeSpeedUp : public GridItemAutoDestroy
{
public:
    RT_CLASS_DEFINE(GridItemArtifactTimeSpeedUp, GridItemAutoDestroy, RtClass);
    GridItemArtifactTimeSpeedUp();
    ~GridItemArtifactTimeSpeedUp();

    void SetSpeedUpRatio(float ratio){ m_speedUpRatio = ratio; }
    void SetCooldownRatio(float ratio){ m_cooldownRatio = ratio; }

    void ApplyEffectToPlant(Plant* plant);
    void EndEffectToPlant(Plant* plant);

    bool IsInEffectArea(int gridX, int gridY);

protected:
    void onDestroy() override;
    void OnCreatePlant(class Plant* plant);

private:
    float m_speedUpRatio;
    float m_cooldownRatio;
};

class ArtifactArcadeProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactArcadeProperties, ArtifactProperties, RtClass);

	ArtifactArcadeProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ArtifactArcade : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactArcade, Artifact, RtClass);
	ArtifactArcade();
	~ArtifactArcade();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;
    virtual void onDestroy() override;
	
public:
	float m_extraLeftTime;
	float m_extraDamageAmount;
	class ArtifactArcadeSubSystem* m_subsystem;
};


//artifact midastouch

class ArtifactMidasTouchProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactMidasTouchProperties, ArtifactProperties, RtClass);

	ArtifactMidasTouchProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ArtifactMidasTouch : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactMidasTouch, Artifact, RtClass);
	ArtifactMidasTouch();
	~ArtifactMidasTouch();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

public:
	int GetExtraCoinMax();

protected:
	void onMidasTouchSpecialDied(Zombie* zombie);
	void onZombieDied(Zombie* zombie, const DamageInfo* i_deathBlow);
	void SpawnCoin(const Sexy::SexyVector3& i_position, int i_coinValue);
	bool CanGoldLization(Zombie* i_zombie);
	
	int m_smallCoin;
	int m_midCoin;
	int m_bigCoin;
	float m_nextSkill;
};


//artifact skateboard

class ArtifactSkateBoardProperties : public ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactSkateBoardProperties, ArtifactProperties, RtClass);

	ArtifactSkateBoardProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ArtifactSkateBoard : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactSkateBoard, Artifact, RtClass);
	ArtifactSkateBoard();
	~ArtifactSkateBoard();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	virtual float GetExtraHpRate(const std::string& i_typeName) override;
	virtual float GetExtraAttackRate(const std::string& i_typeName) override;

	virtual void DisplayPassiveSkill(float i_delay) override;

	float m_nextSkill;
	float m_skillCoolDown;
};



// artifact_magicbeans

class ArtifactMagicBeansProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactMagicBeansProperties, ArtifactProperties, RtClass);

	ArtifactMagicBeansProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ArtifactMagicBeans : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactMagicBeans, Artifact, RtClass);
	ArtifactMagicBeans();
	~ArtifactMagicBeans();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
	void AutoClick() override;
    int m_click_time = 1;
protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;
    virtual void onDestroy() override;

public:
	float m_extraLeftTime;
	float m_extraDamageAmount;
	class ArtifactArcadeSubSystem* m_subsystem;
};

//artifact_devolve


class ArtifactDevolveProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactDevolveProperties, ArtifactProperties, RtClass);

	ArtifactDevolveProperties()
	: LightningBuffDuration(0)
	, BleedingDuration(0)
	, TriggerCondition(ZCONDITION_Stucked)
	, SecondLightningDelay(5.0f)
	, FieldLightningNum(5)
	, FieldLightningDelay(20.0f)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float LightningBuffDuration;
	float BleedingDuration;
	ZombieConditions TriggerCondition;
	float SecondLightningDelay;
	int FieldLightningNum;
	float FieldLightningDelay;
	std::vector<std::string> All_Zombies;
	std::vector<std::string> Normal_Zombies;
	std::vector<std::string> Small_Zombies;
	std::vector<std::string> Armor1_Zombies;
	std::vector<std::string> Armor2_Zombies;
	std::vector<std::string> Imp_Zombies;
	std::vector<std::string> Gargantuar_Zombies;

	std::vector<std::string> CannotBeDevolvedZombieTypes;
};

class ArtifactDevolve : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactDevolve, Artifact, RtClass);
	~ArtifactDevolve();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	bool isZombieTypeBlacklisted(const std::string& zombieTypeName);

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void GenerateLightning();
	void DevolveZombie(Zombie* i_zombie,int type = 0);
	void spawnZombies(const std::string& TypeName, SexyVector3 i_position,int level,float rate =1,int i_FogShield_level =0);
	void GeneratePassiveFieldLightning();

	std::vector<RtWeakPtr<class Zombie>> m_hitZombies;
	float m_passiveLightningRate;
	float m_passiveLightningDamageRate;
	float m_passiveChargeRate;
	float m_mainSecondLightningStartTime;
	float m_mainSecondDevolveStartTime;
	float m_passiveFieldLightningStartTime;
	bool Is_star = false;
	float m_starTime = 0;
	int FogShield_level = 0;
	int bigImp_index = 0;
};

// artifact_weathermonkey

class GridItemArtifactWeatherMonkey : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemArtifactWeatherMonkey, GridItemAnimation, RtClass);

public:
    void setValues(int i_stage, ProjectilePropertySheetPtr i_projectile);
    void fireBullet();
    void setProjectileDamageAmount(float i_damgaeAmount) { m_damageAmount = i_damgaeAmount; }
    void setBoostDistanceValue(float i_distance) { m_boostDistanceValue = i_distance; }

protected:
    void onGridItemInitialize() override;
    void onFinished(const std::string &i_animName);
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);

private:
	void SetHideMowers(bool i_flg);
	void HideArtifactUI();

    int m_stage = 0;
    ProjectilePropertySheetPtr m_projectilePropPtr;
    float m_damageAmount;
    float m_boostDistanceValue = 0.0f;
};

class ArtifactWeatherMonkeyProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ArtifactWeatherMonkeyProjectileProps, ProjectilePropertySheet, RtClass);

	std::vector<std::string> CannotBePushedZombieTypes;
};

class ArtifactWeatherMonkeyProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactWeatherMonkeyProjectile, Projectile, RtClass);

	ArtifactWeatherMonkeyProjectile();

	bool OnCollideEntity(BoardEntity* i_entity) override;
	void moveThroughTime(pvztime_t i_dt) override;
	void explode();
	void setOwnerStage(int i_ownerStage) { m_ownerStage = i_ownerStage; }
	bool canBePushed(Zombie* i_zombie);
	void setBoostDistanceValue(float i_distance) { m_boostDistanceValue = i_distance; }

private:
	int m_ownerStage;
	float m_explodeX;
	bool m_hasTriggered;
	std::vector<RtWeakPtr<Zombie>> m_pushingZombies;
	float m_boostDistanceValue;
};

class ArtifactWeatherMonkeyProjectileSmallProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ArtifactWeatherMonkeyProjectileSmallProps, ProjectilePropertySheet, RtClass);

	ArtifactWeatherMonkeyProjectileSmallProps(){}

	float MaxRotationsPerSecond = 1.0;
};



class ArtifactWeatherMonkeyProjectileSmall : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactWeatherMonkeyProjectileSmall, Projectile, RtClass);

	enum
	{
		k_upperLimit = 100000,
	};

	 void FindNewTarget();
	 void SetOverrideTarget(BoardEntity* i_overrideTarget);
	 static bool CanBeTarget(BoardEntity* i_entity);
	 void SetDamageRate(float i_damageRate) { m_damageRate = i_damageRate; }
	 void start();

protected:
	 void onBezierDone(BoardEntity * target);
	 BoardEntity* FindTargetWithFlag(BoardEntityTypeFlag i_flag);
	 void moveThroughTime(pvztime_t i_dt) override;
	 bool OnCollideEntity(BoardEntity* i_entity) override;
	 void onDeflection(class BoardEntity* i_deflector) override;
	 float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
	 SexyVector3 GetTargetPos(BoardEntity* i_target);
	 void onProjectileInitialized() override;

private:
	RtWeakPtr<BoardEntity> m_overrideTarget;
	bool m_deflected = false;
	float m_numbRate = 0.f;
	float m_numbDuration = 0.f;
	bool m_bezierFlying = false;
	int m_index = 0;
	SexyVector3 m_originalPos;
	SexyVector2 m_bezierPos;
	float m_damageRate;
};




class ArtifactWeatherMonkeyProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactWeatherMonkeyProperties, ArtifactProperties, RtClass);

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float BaseWaveInterval = 3.0f;
	int BaseWaveNum = 2;
	ProjectilePropertySheetPtr Projectile;
	ProjectilePropertySheetPtr ProjectileSmall;
	pvztime_t MissileInterval = 15.0f;
};

class ArtifactWeatherMonkey : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactWeatherMonkey, Artifact, RtClass);
	ArtifactWeatherMonkey();
	~ArtifactWeatherMonkey();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void SpawnWeatherMonkey();
	void SpawnMissile();


	float m_bulletDamgaAmount = 0.0f;
	float m_missileDamageRate = 0.0f;
	pvztime_t m_nextMissileTime = PVZ_EOT();
};


// artifact_gashapon

class ArtifactGashaponProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactGashaponProperties, ArtifactProperties, RtClass);

	ArtifactGashaponProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::string PamName;
	std::string AnimLabelToPlay;
	std::vector<float> Possibility2s;
	std::vector<float> Possibility3s;
};

class ArtifactGashapon : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactGashapon, Artifact, RtClass);
	ArtifactGashapon();
	~ArtifactGashapon();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;
    virtual void onDestroy() override;

public:
	class ArtifactGashaponSubSystem* m_subsystem;
};


// artifact_UFO

class ArtifactUFOProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactUFOProperties, ArtifactProperties, RtClass);

	ArtifactUFOProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::string PamName;
	std::string AsAnimLabelToPlay;
	std::string AsStopAnimLabelToPlay;
	std::string PsAnimLabelToPlay;
	std::string PsStopAnimLabelToPlay;
	
	std::vector<std::string> CannotBeRised;

	float MinRaiseSpeed;
};

class ArtifactUFO : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactUFO, Artifact, RtClass);
	ArtifactUFO();
	~ArtifactUFO();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);
    bool canBeTargeted(BoardEntity* i_entity);
    void doRiseSingleZombie(BoardEntity* i_entity);
    void doRiseAllZombies();
    class ArtifactUFOSubSystem* getMyRiseSystem() { return m_subsystem; }

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;
    virtual void onDestroy() override;

    void onLandedCallback(Zombie *i_zombie);
    float calcVelocityRate(BoardEntity* i_entity);
    void checkPassiveSkill2();

public:
	class ArtifactUFOSubSystem* m_subsystem;
	pvztime_t m_riseTime;
	pvztime_t m_psInterval;
	pvztime_t m_timer;
	pvztime_t m_backCd;
	float m_backWidth;
	float m_zombieFallDamageAmount;

	std::vector<RtWeakPtr<Zombie>> m_risedZombies;
	std::vector<RtWeakPtr<class UFO>> m_ufos;
};



// artifact_prismtower

class ArtifactPrismTowerProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactPrismTowerProperties, ArtifactProperties, RtClass);

	ArtifactPrismTowerProperties()
	{

	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::string PamName;
	std::vector<std::string> DisabledPercentDamage;
};

class ArtifactPrismTower : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactPrismTower, Artifact, RtClass);

	enum State
	{
		STATE_PRISMTOWER_INVALID,
		STATE_PRISMTOWER_DISABLED,
		STATE_PRISMTOWER_ENABLED
	};

	ArtifactPrismTower();
	~ArtifactPrismTower();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	int GetMaxUsedTimes() override;
	void ActivateSpeciallyOnDisplayBoard(int i_index) override;

	float testfunction(BoardEntity* i_ent, float i_time){ return 0.0f; }

	bool IsEnabled() { return m_state == STATE_PRISMTOWER_ENABLED;  }
	float DpsCalculator(BoardEntity* i_ent, float i_elapsed);
	float GetCurrentEnergyValue() {return m_currentEnergy; }
	float GetCurrentEnergyCeiling() { return m_currentEnergyCeiling; }
	float GetExplodeDamageMultiplier() { return (GetCurrentStage() > 3) ? m_explododeDamageMultiplier : 0; };

    class ArtifactPrismTowerSubSystem* getMySystem() { return m_subsystem; }

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;
    virtual void onDestroy() override;
    void SetState(State i_state);

public:
	class ArtifactPrismTowerSubSystem* m_subsystem;
	float m_currentEnergy;
	State m_state;
	float m_initialPercentageDamage;
	float m_initialFixedDamage;
	float m_increasedPercentageDamagePerSecond;
	float m_increasedFixedDamagePerSecond;
	float m_initialEnergyCeiling;
	float m_initialEnergyConsumptionPerSecond;
	float m_initialEnergyRecoveryPerSecond;
	float m_timeTakesToBreakTheShield;
	float m_energyCeilingPlus;
	float m_energyRecoveryPerSecondPlus;
	float m_damageIncreaseSpeedIncreasePercentage;
	float m_explododeDamageMultiplier;
	float m_currentEnergyConsumptionPerSecond;
	float m_currentEnergyRecoveryPerSecond;
	float m_currentEnergyCeiling;
	float m_currentDamageIncreaseMultiplier;
};


// artifact_dinosaurhorn

class ArtifactDinosaurHornProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactDinosaurHornProperties, ArtifactProperties, RtClass);

	struct TypeToSpawnDes
	{
	    std::string EntityName = "";
	    int 		Weight = 0;
	    int 		MinNumToSeckill = 0;
	    int 		MaxNumToSeckill = 0;
	    float 		DamageAmountToSurvivor = 0.0f;
	};

	ArtifactDinosaurHornProperties()
	{
		MusicalNoteEffectPlayInterval = 4.0f;
		MagicalNoteEffectPopanimOffset = {0, 0};
		MagicalNoteEffectPopanimName = "";
		MagicalNoteEffectAnimationToPlay = "idle";
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<TypeToSpawnDes> DinosTypeToSpawn;
	float MusicalNoteEffectPlayInterval;
	SexyVector2 MagicalNoteEffectPopanimOffset;
	std::string MagicalNoteEffectPopanimName;
	std::string MagicalNoteEffectAnimationToPlay;
};

class ArtifactDinosaurHorn : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactDinosaurHorn, Artifact, RtClass);

	ArtifactDinosaurHorn();
	~ArtifactDinosaurHorn();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	void ActivateSpeciallyOnDisplayBoard(int i_index) override;

	float getCurrentStunDuration() { return m_currentStunDuration; }
	float getDinosaurTreadDamageAmount() { return m_dinosaurTreadDamageAmount; }
	float getDinosaurTreadStunDuration() { return m_dinosaurTreadStunDuration; }
	float getBoostDamageValue() { return m_boostDamageValue; }

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void triggerDinosaurRun();
	void triggerDinosaurTread();

	void showDinoRunAdvice();
	void showDinoTreadAdvice();

	void spawnMusicalNoteEffect();
	bool canTriggerDinosaurTread();

private:
	pvztime_t m_timeToTriggerDinosaurRun;
	pvztime_t m_timeToTriggerDinosaurTread;
	pvztime_t m_timeToShowDinosaurRunAdvice;
	pvztime_t m_timeToShowDinosaurTreadAdvice;
	pvztime_t m_timeToPlayMusicalNoteEffect;
	float m_currentStunDuration;
	int m_dinosNumPerLine;
	float m_initialStunDuration;
	float m_stunDurationPlus;
	float m_dinosaurTreadTriggerInterval;
	float m_dinosaurTreadDamageAmount;
	float m_dinosaurTreadStunDuration;
	float m_boostDamageValue;
};

/// artifact watergun
class ArtifactWatergunProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactWatergunProperties, ArtifactProperties, RtClass);

	ArtifactWatergunProperties()
	{
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

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

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

class ArtifactWatergun : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactWatergun, Artifact, RtClass);
	~ArtifactWatergun();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

	void UpdateBuffPlants();

private:
	pvztime_t m_buffPlantsTimeInterval;// passive field2
	pvztime_t m_buffPlantsEndTime;// buff plants end time
	float m_buffPlantsDuration;// buff plants duration time.
};


/// artifact blackhole
class ArtifactBlackholeProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactBlackholeProperties, ArtifactProperties, RtClass);

	ArtifactBlackholeProperties()
	{
		ImgZombieMass = 0.2f;
		SmallZombieMass = 0.5f;
		MidZombieMass = 2.0f;
		BigZombieMass = 5.0f;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float ImgZombieMass;
	float SmallZombieMass;
	float MidZombieMass;
	float BigZombieMass;
};

class ArtifactBlackhole : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactBlackhole, Artifact, RtClass);
	~ArtifactBlackhole();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
	void AutoClick() override;

protected:
	void UpdatePassiveBlackhole();
	void GenerateRandomPassiveBlackhole();

private:
	pvztime_t m_mainDuration;// main trigger duration time
	float m_bigZombieDamage;// big zombie in blackhole damage per second.
	pvztime_t m_mainWaveDragDuration;
	pvztime_t m_passiveField2TimeInterval;
	pvztime_t m_passiveField2Duration;
	pvztime_t m_passiveField2EndTime;
	pvztime_t m_passiveField3Duration;
	float m_impZombieMass = 0.0f;
	float m_midZombieMass = 0.0f;
	float m_smallZombieMass = 0.0f;
	float m_bigZombieMass = 0.0f;
};

// artifact magichat
class ArtifactMagichatProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactMagichatProperties, ArtifactProperties, RtClass);

	ArtifactMagichatProperties()
	{
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ArtifactMagichat : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactMagichat, Artifact, RtClass);
	~ArtifactMagichat();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

protected:
	void SummonMagicZombies(int row);
	void SummonMagicZombies();
	void UpdateSummonZombieRandom();
	void SpawnEffect(Zombie* zombie, std::string startAnimationName);

private:
	int m_currentLevelZombie;
	pvztime_t m_passiveField2EndTime;
	pvztime_t m_passiveField2TimeInterval;
	int m_passiveField1RecoveryTimes;
	int m_passiveField2LineCount;
	int m_passiveField2ZombieCount;
	float m_passiveField3MagichatLife;
	float m_passiveField3MagichatDuration;
};

// artifact beehive
class ArtifactBeehiveProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactBeehiveProperties, ArtifactProperties, RtClass);

	ArtifactBeehiveProperties()
	{
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ArtifactBeehive : public Artifact
{
public:
	enum ArtifactBeeType {
		BEE_TYPE_SMALL1,
		BEE_TYPE_SMALL2,
		BEE_TYPE_SMALL3,
		BEE_TYPE_BIG1,
		BEE_TYPE_BIG2,
		BEE_TYPE_BIG3,
	};
	RT_CLASS_DEFINE(ArtifactBeehive, Artifact, RtClass);
	~ArtifactBeehive();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
	bool CanTriggerMain() override;

	float GetExtraFastPlant(const std::string& i_typeName) override;

	int GetCurrentBeeCount() { return m_currentBeeCount; }
	int GetMaxBeeCount() { return m_beeCountMax; }

	void registerForEvents() override;
	void unregisterForEvents() override;

protected:
	void SpawnBees();
	void GenerateBee(ArtifactBeeType type, int index);
	int CalcSpawnBeeCount();// calc bee count when plant creating
	void GenerateBeeFromPlant(Plant* plant);
	void OnCreatePlant(Plant* plant);
	SexyVector3 RandomBeePosition(SexyVector3 center, float radius);
    BoardEntity* FindTarget();
    std::vector<BoardEntity*> FindTargets();
    ArtifactBeeType GetRandomBeeType(bool isBig);
    ArtifactBeeType GetBeeType(bool isBig, int index);
    SexyVector2 CalcMoveTarget(ArtifactBeeType type, Rect rect);

protected:
	int m_currentBeeCount;
	int m_beeCountMax;
	float m_beeDamage;
	float m_beeDamageMax;
	float m_reducePlantCooldownRatio;
	float m_extraBeeRatio;
	int m_extraBeeCount;
	float m_bigBeePoisonLifePercent;
	float m_generateRandomRadius;
};

/// artifact evolution

class ArtifactEvolutionProperties : ArtifactProperties
{
	RT_CLASS_DEFINE(ArtifactEvolutionProperties, ArtifactProperties, RtClass);
	ArtifactEvolutionProperties()
	{

	}

	std::vector<std::string> plantBlackList;
};

class ArtifactEvolution : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactEvolution , Artifact, RtClass);
	ArtifactEvolution ();
	~ArtifactEvolution ();

	void 	Activate() override;
	void 	DoTrigger() override;
	void 	Update() override;

//	int m_click_time = 1;
	void 	AutoClick() override;

	struct evolutionaryInformation
	{
		evolutionaryInformation() {}
		evolutionaryInformation(Point i_Target, std::string i_middleAnimation, PlantTypePtr i_plantType, int level, PlantPtr i_plant);

		Point Target;
		PlantTypePtr plantType;
		std::string middleAnimation;
		int level;
		PlantPtr m_plant;
	};

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

	void 	GetPlantTypes();
	void 	UpdatePassiveEvolution();
	void 	EvolutionaryDesignatedPlant(PlantPtr);
	void 	GroupPlantEvolution(int gridX, int gridY);
	void 	AutogenousPlants(int gridX, int gridY);
	int 	findLowestLevelInTeamSeeds();
	void 	AddAPlant();
	void	setRenderTransformForRig(PopAnimRig* i_rig, const float i_xOffset);
	PlantPtr 	FindTheLowestCostplant();
	PlantTypePtr 	RandomlyChooseAHigherCostPlant(int m_cost, int m_x, int m_y);

private:
	bool m_autoClick = false;
	std::vector<PopAnimRigPtr> m_tiledRigs;
	std::vector<PlantTypePtr> m_plantTypes;
	std::vector<std::string> m_blackList;
	SexyVector3 targetPostion;
	pvztime_t passiveEffectTime;
	pvztime_t m_passiveField2EndTime;
	pvztime_t m_passiveField2TimeInterval;
	pvztime_t m_passiveField2Duration;
	pvztime_t m_passiveField3Duration;
};

class Effect_evolveLight :	public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_evolveLight, Effect_PopAnim, RtClass);
	Effect_evolveLight(){
		m_info.Target = Point(1,1);
		m_info.level = 1;
		m_info.middleAnimation = "loop";
		m_info.plantType = NULL;
		m_info.m_plant = NULL;
	}
	void playEvolveLight(Point i_point, std::string i_middleAnimation);
	void setevolutionaryInformation(ArtifactEvolution::evolutionaryInformation info);

private:
	void startEvolveLight(Point i_point, std::string i_middleAnimation);
	virtual void onAnimStopped(const std::string& i_animLabel);
	ArtifactEvolution::evolutionaryInformation m_info;
};


// artifact snowdrift

class ArtifactSnowdriftProperties : ArtifactProperties
{
	RT_CLASS_DEFINE(ArtifactSnowdriftProperties, ArtifactProperties, RtClass);
	ArtifactSnowdriftProperties()
	{

	}
	
	ProjectilePropertySheetPtr SnowBallProjectile;
	ProjectilePropertySheetPtr IcebulletsProjectile;
};

class ArtifactSnowdrift : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactSnowdrift , Artifact, RtClass);
	ArtifactSnowdrift ();
	~ArtifactSnowdrift ();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
	pvztime_t GetMainEndTime() { return m_mainEndTime; }
	// void AutoClick() override;

protected:

	void UpdatePassiveSnowdrift();
	void throwSnowball();
	void turn2Snowman();
	void freezeBoard();
	BoardEntity* tryAttack();
	void fireIcebullets();
	void repelZombies();
	void OnZombieConditionTimeAppend(Zombie* i_zombie, int i_condition, float* i_rate, bool i_isAppend);
	void LaunchZombie(Zombie* zombie);
	void KillFlyZombie(Zombie* zombie) { zombie->SetHidden(true); }

private:

	enum Snowdrift_State
	{
		None,
		Idle,
		Playing,
		End
	};

	Snowdrift_State m_state = None;
	int m_click_time = 1;
	float m_oligemicPercent;
	pvztime_t m_effectDuration;
	pvztime_t m_snowdriftDuration;
	pvztime_t m_snowdriftEndTime;
	pvztime_t passiveEffectTime;
	pvztime_t m_passiveField1Duration;
	pvztime_t m_passiveField2Cooldown;
	pvztime_t m_passiveField2Duration;
	pvztime_t m_passiveField2EndTime;
	pvztime_t m_passiveField3Duration;
	pvztime_t m_passiveField3EndTime;
	pvztime_t m_mainEndTime = 0.0;
	float m_passiveField3Damage;
	float m_repulseDistancePercent;
	bool m_isEnd = false;
	Effect_PopAnim* m_effect = nullptr;
};

class ArtifactSnowBallProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactSnowBallProjectile, Projectile, RtClass);
	void onProjectileInitialized() override;
	void damageEntity(BoardEntity* i_entity) override;
	bool handleImpact(BoardEntity* i_impactedEntity /* =NULL */) override;
	class BoardEntity* GetTarget() override;
};

class ArtifactIcebulletsProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactIcebulletsProjectile, Projectile, RtClass);
	void onProjectileInitialized() override;
	void damageEntity(BoardEntity* i_entity) override;
	bool handleImpact(BoardEntity* i_impactedEntity /* =NULL */) override;
private:

};


class Effect_Snowdrift : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_Snowdrift, Effect_PopAnim, RtClass);
private:
	void onAnimStopped(const std::string& i_animLabel);
	
};


class ArtifactSnowdriftSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ArtifactSnowdriftSubSystem, GameSubSystem, RtClass);

	ArtifactSnowdriftSubSystem() {}
	void AddTransformEntry(ZombiePtr i_zombie);
	void hideShowOriginal(ZombiePtr i_zombie, bool i_hide);
	bool canTransform(class Zombie* i_zombie);
	void Update();
	void transform(class Zombie* i_zombie, int i_level, pvztime_t duration, float oligemicPercent);
protected:
	void registerForEvents() override;

private:
	void repelEntity();
	void onZombieConditionEnded(Zombie* i_zombie, int i_condition);

	std::vector<ZombiePtr> m_transformedEntries;

};


// artifact guitar

class ArtifactGuitarProperties : public ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactGuitarProperties, ArtifactProperties, RtClass);
	ArtifactGuitarProperties()
	{}
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const;
	//PlantRestrictionSet TargetableCreatedPlantTypes;
	ProjectilePropertySheetPtr MusicalNotesProjectile;
	ProjectilePropertySheetPtr GuitarSoundProjectile;
	std::vector<float> MusicalInterval;
	pvztime_t SuccessfulTimestamp;
	pvztime_t PerfectTimestamp;
};

class ArtifactGuitar : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactGuitar , Artifact, RtClass);
	ArtifactGuitar();
	~ArtifactGuitar();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
	void SetEnd() { setState(ArtifactGuitarState_End); }
	void fireGuitarSoundProjectile();
	void fireMusicalNotesProjectile();
	void reset();	
	
	enum ArtifactGuitarState
	{		
		ArtifactGuitarState_Idle,
		ArtifactGuitarState_Start,
		ArtifactGuitarState_Effect,
		ArtifactGuitarState_End,
	};
	ArtifactGuitarState GetState() { return m_state; }

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

	void onDestroy();
	void onPlantCreate(Plant* i_plant);
	void onAddMusicalSuccessedCount(int i_cnt);		
	void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> * io_plantingErrors);
	void onGatherPlantinglessRestrictions(const Sexy::Point& i_atLocation, std::vector<PlantingReason> *io_plantingErrors);
private:
	void plantingReason(std::vector<PlantingReason> * io_plantingErrors);
	void disableUI(bool i_visible);

	void setState(ArtifactGuitarState i_state);
	void addMusicalNotes();
	void playAudio();
	// void destroyMusicalEffect();
	void addForegroundToRenderQueue(RenderQueue* i_queue);
	void renderForeground(Graphics* i_g);


	int		  m_successedCnt;
	int		  m_currentNotesIdx;
	int		  m_guitarLevel;
	float	  m_mainBaseDamage1;
	float	  m_mainBaseDamage2;
	float	  m_mainBaseDamage3;	
	float	  m_passive1Boost;
	pvztime_t m_passive2Cooldown;
	float	  m_passive2Damage;
	float	  m_passive3Damage;
	ArtifactGuitarState m_state;
	pvztime_t m_nextMusicalNoteTime;
	pvztime_t m_nextFireTime;
	// std::vector<Effect_PopAnim*> m_musicalVec;
	std::set<int> m_storePositions;
};

// artifact silverkey
class ArtifactSilverKeyProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactSilverKeyProperties, ArtifactProperties, RtClass);

	ArtifactSilverKeyProperties()
	{
		SpawnGargantuarBaseLevel = 4;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> ZombieBlacklist;
	std::vector<int> SpawnGargantuarSumConditions;
	int SpawnGargantuarBaseLevel;
};

class ArtifactSilverKeyCursor : public PacketCursor
{
public:
    RT_CLASS_DEFINE(ArtifactSilverKeyCursor, PacketCursor, Sexy::RtClass) {}

    ArtifactSilverKeyCursor() {}
    explicit ArtifactSilverKeyCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);
    virtual ~ArtifactSilverKeyCursor();

    PlantTypePtr GetPlantType() const { return m_plantType; }

protected:
    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void tryToUse() override;

	Point GetCurrentGridPosition() override;
	void cacheOrDestroyCursor();
	bool canAffordPlant(PlantTypePtr i_plantType) const;
	Sexy::SexyVector2 getCursorAnimOffset() const override;
    bool CanUseAtCurrentPosition() override;
	bool IsInsideOriginRect() const override;

private:
	PlantTypePtr m_plantType;
};

class SilverkeyTentacleShadow : public BoardEntity
{
public:
	RT_CLASS_DEFINE(SilverkeyTentacleShadow, BoardEntity, RtClass);

	SilverkeyTentacleShadow();

	void SetTarget(ZombiePtr target);

protected:
	void onUpdate() override;
	void onDestroy() override;
	void onDrawShadow(class Sexy::Graphics* i_g) override;

	void GenerateTentacle(int x, int y, ZombiePtr zombie = ZombiePtr());

protected:
	Point m_targetLocation;
	ZombiePtr m_target;
	SexyVector3 m_targetVector;
};

/// Silverkey Gargantuar
class ZombieSilverkeyGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieSilverkeyGargantuar, ZombieGargantuar, RtClass);

protected:
    void onInitialized() override;
	BoardEntity *findTarget() override;
    bool isImpReadyToBeThrown() override;
};

class ArtifactSilverKey : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactSilverKey , Artifact, RtClass);
	ArtifactSilverKey ();
	~ArtifactSilverKey ();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;
	void AutoClick() override;

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

	void SpawnTentacle();
	void GenerateTentacle(int x, int y, ZombiePtr zombie = ZombiePtr());
	void SpawnGargantuar(int absorbCount);

	bool IsAbsorbTarget(const ZombiePtr& i_potentialZombie);
	bool IsZombieBlacklisted(const ZombiePtr i_zombie, const std::vector<std::string>& i_blacklist);
protected:
	pvztime_t m_tentacleTimeInterval;
	pvztime_t m_tentacleSpawnEndTime;
	int m_tentacleCount;
	float m_absorbRadius;
	int m_absorbZombieCountMax;
};

class GridItemCthulhuActiniaTentacleArtifact : public GridItemCthulhuActiniaTentacle
{
public:
	RT_CLASS_DEFINE(GridItemCthulhuActiniaTentacleArtifact, GridItemCthulhuActiniaTentacle, RtClass);

	GridItemCthulhuActiniaTentacleArtifact();
	virtual ~GridItemCthulhuActiniaTentacleArtifact();

	void onGridItemInitialize() override;
	void onUpdate() override;

protected:
	void UpdateIdle() override;
	void SetState(int state) override;
	void SwallowZombies(std::vector<BoardEntity*> i_zombies) override;
	void OnAttackAnimDone(const std::string& name) override;
	void OnPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params) override;

	void PlayDarkEffect(const SexyVector2& start);
	void DarkEffectFlyEnd(float value);

protected:
	RtWeakPtr<class AddCthulhuEnergyEffect> m_darkEffect;
};

// GridItemArtifactSilverkeyGateProps
class GridItemArtifactSilverkeyGateProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemArtifactSilverkeyGateProps, GridItemAnimControllerProps, RtClass);

	GridItemArtifactSilverkeyGateProps();

	pvztime_t Duration;
	std::vector<std::string> ZombieBlacklist;
};

class GridItemArtifactSilverkeyGate : public GridItemAnimation
{
public:
	enum {
		SILVERKEY_GATE_INVALID = -1,
		SILVERKEY_GATE_SPAWN,
		SILVERKEY_GATE_ABSORB,
		SILVERKEY_GATE_SPAWNZOMBIE,
		SILVERKEY_GATE_END,
		SILVERKEY_GATE_DESTROY,
		SILVERKEY_GATE_MAX,
	};
	RT_CLASS_DEFINE(GridItemArtifactSilverkeyGate, GridItemAnimation, RtClass);

	GridItemArtifactSilverkeyGate();
	virtual ~GridItemArtifactSilverkeyGate();

	void onGridItemInitialize() override;
	void onUpdate() override;
	int CalcRenderOrder() const override;
    void KillGridItem() override;

    void SetAbsorbRadius(float radius);
    void SetAbsorbZombieMax(int count);
    void SetSpawnGargantuarLevelConditions(std::vector<int> conditions, int base);
    void SetPassiveField3Enable(bool enable);

    void SummonZombie();
    void PlayEnd();

protected:
    void SetState(int state);
    void SpawnGargantuar(int absorbCount);
	void PlayDarkEffect(const SexyVector2& start);
	void DarkEffectFlyEnd(float value);
	void DarkEffectFlyEnd2(float value, AddCthulhuEnergyEffect* effect);


	void AbsorbZombies();
	std::vector<ZombiePtr> FindTarget(Rect search, int countMax);
	void AbsorbTarget(ZombiePtr zombie);
	void OnPopAnimDone(const std::string& name);
	void OnZombieTossEnd(Zombie* i_zombie);

	bool IsAbsorbTarget(const ZombiePtr& i_potentialZombie);
	bool IsZombieBlacklisted(const ZombiePtr i_zombie, const std::vector<std::string>& i_blacklist);

	void PlayWindEffect();
	void PlaySummonEffect();
	void PlayWindEndEffect();

protected:
	int m_state;
	RtWeakPtr<class AddCthulhuEnergyEffect> m_darkEffect;
	std::vector<RtWeakPtr<class AddCthulhuEnergyEffect> > m_darkEffects;
	float m_searchRadius;
	int m_zombieCountMax;
	std::vector<int> m_spawnGargantuarLevelConditions;
	int m_spawnGargantuarBaseLevel;
	bool m_passiveField3Enable;
	pvztime_t m_gateEndTime;
	int m_absorbZombieCount;
	std::vector<ZombiePtr> m_zombieList;
	RtWeakPtr<class SilverkeyGateEffect> m_gateEffect;
};

class SilverkeyGateEffect : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(SilverkeyGateEffect, Effect_PopAnim, RtClass);

    enum {
    	GATE_EFFECT_INVALID = -1,
    	GATE_EFFECT_START,
    	GATE_EFFECT_LOOP,
    	GATE_EFFECT_END,
    	GATE_EFFECT_SPAWNZOMBIE,
    	GATE_EFFECT_MAX,
    };

    SilverkeyGateEffect();

    void onInitialized() override;

    void Start();
    void SetGate(RtWeakPtr<GridItemArtifactSilverkeyGate> gate);
    void SetState(int state);

    void PlaySummon();
    void PlayEnd();

protected:
    void onAnimStopped(const std::string& i_animLabel) override;
    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

protected:
    int m_state;
    RtWeakPtr<GridItemArtifactSilverkeyGate> m_gate;
};

// Artifact Dragon
enum TestDragonNodeType
{
	TestDragonNode_Head,
	TestDragonNode_Seg,
	TestDragonNode_Tail
};

enum TestDragonType
{
	Dragon_Large,
	Dragon_Small
};

struct DragonInfo
{
	DragonInfo()
	: m_head(NULL)
	, m_tail(NULL)
	, m_type(Dragon_Large)
	, m_damageInterval(0.0f)
	, m_nextDamageTime(0.0f)
	{

	}

	DragonInfo(class TestDragon* i_head, class TestDragon* i_tail, TestDragonType i_type, float i_damageInterval)
	: m_head(i_head)
	, m_tail(i_tail)
	, m_type(i_type)
	, m_damageInterval(i_damageInterval)
	{

	}

	class TestDragon* m_head;
	class TestDragon* m_tail;
	TestDragonType m_type;
	float m_damageInterval;
	pvztime_t m_nextDamageTime;
};

class ArtifactDragonSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ArtifactDragonSubsystem, GameSubSystem, RtClass);

    ArtifactDragonSubsystem();
    ~ArtifactDragonSubsystem() override;

    void registerForEvents() override;

    void SetWidenDurationAdded(float i_addTime) { m_widenDurationAdded = i_addTime; }

    ProjectilePropertySheetPtr getTestDragonProjectileType(TestDragonNodeType i_type, TestDragonType i_dragonType);

    void DragonTest(int i_length, const SexyVector3& i_srcPosition, TestDragonType i_dragonType, float i_damageInterval, float i_baseDamage);
    class Projectile* createDragon(const SexyVector3& i_srcPosition, TestDragonNodeType i_type, TestDragonType i_dragonType);
    void SetUpdateCount(int i_count) { m_dragonUpdateCount = i_count; }
    int GetUpdateCount() { return m_dragonUpdateCount; }
    void updateDragonVelocity();

    void Update() override;

    void DragonExit();
    void RemoveDragon(TestDragonType i_dragonType);
    class TestDragon* GetHead(TestDragonType i_type);
    void EnableDragonDamage(TestDragonType i_dragonType, bool i_enable);

    void WidenDragon(bool i_enable);

private:
    void onArtifactClearBoard();
    void updateDragonDamage();
    void updateWidenDragon();

//    class TestDragon* m_head;
//    class TestDragon* m_tail;
    int m_dragonUpdateCount;

    std::vector<DragonInfo> m_dragonInfos;
    pvztime_t m_widenEndTime;
    float m_widenDurationAdded;
};

class TestDragonProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(TestDragonProps, ProjectilePropertySheet, RtClass);

	TestDragonProps()
	{
        MaxRotationsPerSecond = 1.0;
        MaxSpeed = 0.0f;
		MinSpeed = 0.0f;
		RemoveDelay = 0.0f;
		ChangeTargetDelay = 0.0f;
		AccelerateDegree = 0.0f;
	}

	float MaxRotationsPerSecond;
	float MaxSpeed;
	float MinSpeed;
	SexyVector3 Acceleration;
	float RemoveDelay;
	float ChangeTargetDelay;
	float AccelerateDegree;
};

struct TestDragonInfo
{
	TestDragonInfo()
	: Rotation(0.0f)
	, LastDt(0.0f)
	{

	}

	TestDragonInfo(float i_rotation, const SexyVector3& i_velocity, const SexyVector3& i_target, pvztime_t i_lastDt)
	: Rotation(i_rotation)
	, Velocity(i_velocity)
	, Target(i_target)
	, LastDt(i_lastDt)
	{

	}

	float Rotation;
	SexyVector3 Velocity;
	SexyVector3 Target;
	pvztime_t LastDt;
};

struct PathInfo
{
	PathInfo(const SexyVector3& i_target, float i_keepTime, float i_duration = PVZ_EOT())
	: KeepTime(i_keepTime)
	, Target(i_target)
	, Duration(i_duration)
	{

	}

	PathInfo()
	: KeepTime(0.0f)
	, Duration(PVZ_EOT())
	{

	}

	float KeepTime;
	SexyVector3 Target;
	float Duration;
};

class TestDragon : public Projectile
{
public:
	RT_CLASS_DEFINE(TestDragon, Projectile, RtClass);

	TestDragon();

	void SetDragonType(TestDragonType i_type) { m_dragonType = i_type; }
	TestDragonType GetDragonType() { return m_dragonType; }
	void SetOverrideTarget(BoardEntity* i_overrideTarget, int i_pathSize);
	void SetRotatedVelocity(float i_magnitude);
	void SetType(TestDragonNodeType i_type) { m_type = i_type; }
	TestDragonNodeType GetType() const { return m_type; }
	void CreateRandomPosition();
	void GetRandomGrids(std::vector<Point>& i_grids);
	bool IsGridValid(Point i_grid);
	void SetUpdateCount(int i_count) { m_updateCount = i_count; }
	int GetUpdateCount() { return m_updateCount; }
	void FindNewTarget(int i_pathSize);
	void AddInitUpdateInfo();
	int GetMoveTimesToDestination(const SexyVector3& i_target, pvztime_t i_dt);
	void SetCanDealDamage(bool i_enable) { m_canDealDamage = i_enable; }
	bool CanDealDamage() { return m_canDealDamage; }

	void SetPath(const std::vector<PathInfo>& i_paths) { m_paths = i_paths; }
	void SetIndex(int i_index) { m_index = i_index; }
	int GetIndex() const { return m_index; }

	void Exit();
	bool WillExit();
	bool IsExiting();
	bool IsWiden();
	void CheckWidenAnim(bool i_enable);

public:
	TestDragon* m_prev;
	TestDragon* m_next;
	std::vector<TestDragonInfo> m_lastUpdateInfos;

protected:

	void onUpdate(pvztime_t i_dt) override;
	void moveThroughTime(pvztime_t i_dt) override;

    float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
    SexyVector3 GetTargetPos(BoardEntity* i_target);
    bool OnCollideEntity(BoardEntity* i_entity) override;
    BoardEntity* FindTargetWithFlag(BoardEntityTypeFlag i_flag);
    BoardEntity* FindBall();
    bool CanBeTarget(BoardEntity* i_entity);
    bool ignoreDeathBox() override;
    bool reachMaxSpeed(pvztime_t i_dt);
    bool reachMinSpeed(pvztime_t i_dt);
    bool hasEmptyTarget();
    int CalcRenderOrder() const override;

    void addLastUpdateInfo(float i_rotation, const SexyVector3& i_velocity, const SexyVector3& i_target, pvztime_t i_lastDt);

	RtWeakPtr<BoardEntity> m_overrideTarget;
	TestDragonNodeType m_type;
	SexyVector3 m_randomPosition;
	int m_updateCount;
	std::vector<BoardEntityPtr> m_hitEntities;
	pvztime_t m_nextChangePositionTime;

	TestDragonType m_dragonType;
	std::vector<PathInfo> m_paths;

	pvztime_t m_currentPositionStartTime;
	SexyVector3 m_exitPosition;
	pvztime_t m_removeTime;
	bool m_canDealDamage;
	bool m_towardsRight;
	int m_index;
};

enum GridItemBallState
{
    PVZ_BEGIN_ENUM(BALLSTATE_),
    BALLSTATE_UNKNOWN,
    BALLSTATE_RESETTING,
    BALLSTATE_IDLE,
    BALLSTATE_DEAD,
    PVZ_END_ENUM(BALLSTATE_)
};

class GridItemBall : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemBall, GridItemAnimation, RtClass);

    GridItemBall();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetResetting() { setState(BALLSTATE_RESETTING); }
    void SetIdle() { setState(BALLSTATE_IDLE); }
    void SetLifeTime(float i_lifeTime) { m_lifeTime = i_lifeTime; }
    void Kill() { setState(BALLSTATE_DEAD); }

    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

    bool ShouldDrawShadow() const override;
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;
    void onDrawShadow(Sexy::Graphics* i_g) override;

    void setState(GridItemBallState i_state);
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    bool OverrideProjectileCollision(Projectile* i_projectile) override;

    void OnPopAnimDone(const std::string& name);

private:
    pvztime_t m_creationTime;
    GridItemBallState m_state;
    float m_lifeTime;
};

class GridItemBallProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemBallProps, GridItemAnimationProps, RtClass);
    GridItemBallProps()
    : EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;
};

class ArtifactBallProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ArtifactBallProjectile, Projectile, RtClass);

    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
    void moveThroughTime(pvztime_t i_dt) override;

private:
    void spawnBall();
    void spawnBall(const Point& gridPosition);

    bool m_goUp = true;
};

class ArtifactDragonProperties : ArtifactProperties
{
public:
	RT_CLASS_DEFINE(ArtifactDragonProperties, ArtifactProperties, RtClass);

	ArtifactDragonProperties()
	: BaseDuration(0)
	, DamageInterval(0)
	, SmallDragonLength(0)
	, DurationAdded(0)
	, WidenDurationAdded(0)
	, MaxBallAllowed(0)
	{}

	float BaseDuration;
	float DamageInterval;
	int SmallDragonLength;
	ValueRange ThrowBallInterval;
	RtWeakPtr<RtObject> BallProjectile;
	float BallShotHeight;
	float BallShotTime;
	float DurationAdded;
	float WidenDurationAdded;
	int MaxBallAllowed;
};

class ArtifactDragon : public Artifact
{
public:
	RT_CLASS_DEFINE(ArtifactDragon, Artifact, RtClass);
	~ArtifactDragon();

	void Activate() override;
	void DoTrigger() override;
	void Update() override;

	SexyVector3 GetSelfPosition();

protected:
	float GetExtraHpRate(const std::string& i_typeName) override;
	float GetExtraAttackRate(const std::string& i_typeName) override;

private:
	void GenerateUltraDragon();
	void GenerateMinorDragon();
	bool IsGridValid(Point i_grid);
	void GetRandomGrids(std::vector<Point>& i_grids);
	void LaunchBalls(bool i_single);
	void LaunchToGrid(Point i_grid);
	void launchProjectile(SexyVector3 i_source, SexyVector3 i_targetPosition, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit, TeamFlags i_team, BoardEntityPtr i_target);
	void onNotifyWidenDragon();
	bool CanLaunchBalls();

	float m_mainDragonDuration;
	float m_mainDragonExitTime;
	float m_mainDragonDamage;
	int m_mainDragonLength;
	pvztime_t m_passiveDragonStartTime;
	float m_passiveDragonInterval;
	float m_passiveThrowBallInterval;
	pvztime_t m_passiveNextThrowBallTime;
	float m_passiveDragonDamage;
};

#endif /* ARTIFACT_H_ */
