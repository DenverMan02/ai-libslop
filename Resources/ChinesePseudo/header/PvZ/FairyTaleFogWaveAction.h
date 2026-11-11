/*
 * FairyTaleFogWaveAction.h
 *
 *  Created on: 2022-3-18
 *      Author: admin
 */

#ifndef FAIRYTALEFOGWAVEACTION_H_
#define FAIRYTALEFOGWAVEACTION_H_

#include "Wave.h"
#include "GameSubSystem.h"
#include "GameEventMgr.h"
#include "GridItemBoardEntityConditionTarget.h"

typedef RtWeakPtr<class GridItemFairyTaleFog> GridItemFairyTaleFogPtr;

static const std::vector<std::string> k_defaultBuffableProjectiles = {"PeaDefault",
        "ThreepeaterPeaDefault",
        "ThreepeaterPeaSnow",
        "ThreepeaterPeaFire",
        "ThreepeaterPeaUltraFire",
        "PlantfoodPeaDefault",
        "FirePeaDefault",
        "UltraFirePeaDefault",
        "SnowPeaDefault",
        "GiantPeaDefault",
        "GiantFirePeaDefault",
        "GiantUltraFirePeaDefault",
        "CannonballDefault",
        "CabbageDefault",
        "MelonDefault",
        "WinterMelonDefault",
        "KernelDefault",
        "ButterDefault",
        "StarFruitShot",
        "BloomerangDefault",
        "BloomerangAvatar",
        "PlasmaBall",
        "PuffSporeDefault",
        "ThrownZombieParticle",
        "GuacodileDefault",
        "HomingThistleDefault",
        "HomingThistlePlantfood",
        "BowlingBulbDefault",
        "BowlingBulbDefault2",
        "BowlingBulbDefault3",
        "PameBulletNormal",
        "PameBulletPlantfood",
        "PameBulletAvatarPlantfood",
        "PeanutDefault",
        "IceLancePeaDefault",
        "PepperpultDefault",
        "PepperpultPlantfoodDefault",
        "XShotShot",
        "XShotGiantShot",
        "StingerDefault",
        "AkeeDefault",
        "MegaAkeeDefault",
        "NekotailStabDefault",
        "NekotailStabAdvance",
        "HugeNekotailStab",
        "wasabiwhipLevel5",
        "BearberryDefaultProjectile",
        "BearberryLevel2Projectile",
        "PoisonPeaDefault",
		"HeadbutterlettuceButterDefault",
		"HeadbutterlettuceLevel2ButterDefault",
		"HeadbutterlettucePlantfoodButterDefault",
		"HeadbutterlettuceAvatarPlantfoodButterDefault"};

enum GridItemFairyTaleFogState
{
    PVZ_BEGIN_ENUM(FAIRYTALEFOGSTATE_),
    FAIRYTALEFOGSTATE_UNKNOWN,
    FAIRYTALEFOGSTATE_RESETTING,
    FAIRYTALEFOGSTATE_IDLE,
    FAIRYTALEFOGSTATE_DEAD,
    FAIRYTALEFOGSTATE_APPEAR,
    FAIRYTALEFOGSTATE_DISAPPEAR,
    PVZ_END_ENUM(FAIRYTALEFOGSTATE_)
};

struct FogMovingData
{
	FogMovingData()
	: m_movingDistance(0)
	, m_movingTime(0)
	, m_finalGridX(0)
	, m_finalGridY(0)
	{

	}

	FogMovingData(int i_movingDistance, float i_movingTime, int i_gridX, int i_gridY)
	: m_movingDistance(i_movingDistance)
	, m_movingTime(i_movingTime)
	, m_finalGridX(i_gridX)
	, m_finalGridY(i_gridY)
	{

	}

	int m_movingDistance;
	float m_movingTime;
	int m_finalGridX;
	int m_finalGridY;
};

class GridItemFairyTaleFog : public GridItemBoardEntityConditionTarget
{
public:
    RT_CLASS_DEFINE(GridItemFairyTaleFog, GridItemBoardEntityConditionTarget, RtClass);

    GridItemFairyTaleFog();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(FAIRYTALEFOGSTATE_IDLE); }

    bool IsIdle() { return m_state == FAIRYTALEFOGSTATE_IDLE; }

    void SetData(const FogMovingData& i_data) { m_movingData = i_data; }

    void DoAppear();
    void DoDisappear();

    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;
    void onDraw(Graphics* i_g) override;

    void setState(GridItemFairyTaleFogState i_state);
    void applyShield();
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    void updatePosition() override;

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    void drawFogAnim(Graphics* i_g);
    void appear();
    void disappear();
    void tryOverrideCondition(Zombie* i_zombie, ZombieConditions i_condition);
    std::string GetPlayAnimName();
    bool canFogShieldActivated(Zombie* i_zombie);

    pvztime_t m_creationTime;
    GridItemFairyTaleFogState m_state;

    FogMovingData m_movingData;
};

class GridItemFairyTaleFogProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemFairyTaleFogProps, GridItemBreakableTargetProps, RtClass);
    GridItemFairyTaleFogProps()
    : Lifetime(1.0)
    , EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    pvztime_t Lifetime;
    std::vector<std::string> ZombieBlacklist;
    ZombieConditions ConditionApplied;
};

struct BuffedProjectileData
{
	BuffedProjectileData()
	{

	}

	BuffedProjectileData(RtWeakPtr<class Projectile> i_ptr, const SexyVector3& i_velocityScale)
	: ProjectilePtr(i_ptr)
	, VelocityScale(i_velocityScale)
	{

	}

	RtWeakPtr<class Projectile> ProjectilePtr;
	SexyVector3 VelocityScale;
};

class FairyTaleFogSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(FairyTaleFogSubSystem, GameSubSystem, RtClass);

    FairyTaleFogSubSystem();

    void Update() override;

    void TryFogAppear(const std::string& i_type, const Sexy::Rect& i_range, int i_movingDistance, float i_movingTime);
    void TryFogDisappear();
    void TryWindAppear(float i_duration, const std::vector<std::string>& i_buffableProjectiles, float i_velocityScale);
    bool IsFogDoneMoving();
    void SetRequestNextWaveVisible(bool i_visible) { m_requestNextWaveVisible = i_visible; }

protected:
	void registerForEvents() override;

private:
	void playWindEffect();
	void buffProjectiles();
	void recoverProjectiles();
	void debuffZombies();
	void recoverZombies();
	bool canBeTargeted(Zombie * zombie);
	bool canBuffProjectile(Projectile *i_projectile);
	void buildProjectileSet(const std::vector<std::string>& i_buffableProjectiles);
	void resetWinds();
	void onSetNextWaveVisible(bool i_visible);

	Sexy::Rect m_currentRange;
	std::vector<GridItemFairyTaleFogPtr> m_fogs;
	pvztime_t m_windEndTime;
	std::vector<RtWeakPtr<class Zombie>> m_debuffedZombies;

	std::vector<BuffedProjectileData> m_buffedProjectiles;
	std::set<const ProjectilePropertySheet*> m_buffableProjectiles;
	float m_projectileVelocityScale;
	bool m_requestNextWaveVisible;
};

class FairyTaleWindWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(FairyTaleWindWaveAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

private:
	pvztime_t m_windTipTime;
};

class FairyTaleWindWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(FairyTaleWindWaveActionProps, WaveActionProperties, RtClass);

	FairyTaleWindWaveActionProps()
	: Duration(0)
	, VelocityScale(0)
	{
		for(auto& info : k_defaultBuffableProjectiles)
		{
			BuffableProjectiles.push_back(info);
		}
	}

	RtClass* GetActionClass() const override { return FairyTaleWindWaveAction::StaticGetClass(); }

	std::vector<std::string> BuffableProjectiles;
	float Duration;
	float VelocityScale;
};

class FairyTaleFogWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(FairyTaleFogWaveAction, WaveAction, RtClass);

	FairyTaleFogWaveAction();

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	void OnSetNextWaveVisible(bool i_visible);

private:
	pvztime_t m_fogTipTime;
};

class FairyTaleFogWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(FairyTaleFogWaveActionProps, WaveActionProperties, RtClass);

	FairyTaleFogWaveActionProps()
	: Distance(6)
	, MovingTime(0)
	, FogType("")
	{

	}

	RtClass* GetActionClass() const override { return FairyTaleFogWaveAction::StaticGetClass(); }

	Sexy::Rect Range;
	int Distance;
	float MovingTime;
	std::string FogType;
};


#endif /* FAIRYTALEFOGWAVEACTION_H_ */
