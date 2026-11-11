/*
 * Plant_NukeLauncher.h
 *
 *  Created on: 2021-5-11
 *      Author: admin
 */

#ifndef PLANT_NUKELAUNCHER_H_
#define PLANT_NUKELAUNCHER_H_

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "StandardLevelIntro.h"
#include "Effect_BouncingArrow.h"
#include "GameSubSystem.h"
#include "GridItemAnimation.h"
#include "Zombie.h"

enum RocketType
{
	RocketType_Normal,
	RocketType_Plantfood,
	RocketType_Avatar,
	RocketType_Super
};

class NukeLauncherProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(NukeLauncherProps, PlantPropertySheet, RtClass);

	NukeLauncherProps()
	{
		FireTime = 1.0f;
		TargetOffset.x = 0;
		TargetOffset.y = 0;
		NumPlantfoodRockets = 0;
		NumAvatarRockets = 0;
		PlantfoodFireTime = 0;
		AvatarFireTime = 0;
		CostPerExistingPlant = 0;
	}

	pvztime_t FireTime;
	SexyVector2 TargetOffset;
	int NumPlantfoodRockets;
	int NumAvatarRockets;
	pvztime_t PlantfoodFireTime;
	pvztime_t AvatarFireTime;
	int CostPerExistingPlant;
};

class PlantTypeNukeLauncher : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeNukeLauncher, PlantType, RtClass) {}

    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    int GetExistingLevelCount() const;
    int CalcCostForLevelCount(int i_count, PlantAvatarType i_avatarType) const;
};

class PlantNukeLauncher : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantNukeLauncher, PlantFramework, RtClass);
	PlantNukeLauncher();
	void Initialize() override;
    void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	float GetRefundSunAmount() override;

	ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	GridItemPtr FindTargetDamageableGridItem(PlantWeapon i_plantWeapon) override;
	virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void queueShot(pvztime_t i_launchTime, const Point &i_targetLocation, RocketType i_type = RocketType_Normal);
	void addShot(float plantFoodFireTime, int& io_shot, const Point& i_point , RocketType i_type = RocketType_Plantfood);

private:
	void DoPlantfood(bool i_avatar);
    void registerForEvents() override;
    void unregisterForEvents() override;
};


class PlantAnimRig_NukeLauncher : public PlantAnimRig
{
public:
	//RT_CLASS_DEFINE(PlantAnimRig_Banana, PlantAnimRig, RtClass) {}
	RT_CLASS_DEFINE(PlantAnimRig_NukeLauncher, PlantAnimRig, RtClass);
	//bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;

	std::string getIdleAnimationName()override;
	std::string getAttackAnimationName() override;
	std::string getPlantFoodMainAnimName() override;
};

class NukeLauncherSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(NukeLauncherSubSystem, GameSubSystem, RtClass);

	NukeLauncherSubSystem();

	struct NukeLauncherEntry
	{
		NukeLauncherEntry() {}
		NukeLauncherEntry(PlantNukeLauncher* i_owner, pvztime_t i_launchTime, const Point& i_target, RocketType i_type = RocketType_Normal);

		//PlantBanana *m_owerPlant;
		PlantPtr Owner;
		RtWeakPtr<const NukeLauncherProps> NukeLauncherPropertySheet;
		pvztime_t LaunchTime;
		RocketType Type = RocketType_Normal;
		Point Target;
	};

	void QueueShot(PlantNukeLauncher* i_owner, pvztime_t i_launchTime, const Point& i_target, RocketType i_type = RocketType_Normal);
	void Update() override;
	NukeLauncherEntry* GetLauncherEntry(int i);
	void AddTransformEntry(ZombiePtr i_zombie);
	void hideShowOriginal(ZombiePtr i_zombie, bool i_hide);
	bool tryTransform(class Zombie* i_zombie, int i_level, int i_maxAffectLevel, bool i_affectBigSize = false);
	bool canTransform(class Zombie* i_zombie, int i_maxAffectLevel);
	void transform(class Zombie* i_zombie, int i_level);
	void doStun(class Zombie* i_zombie);
	void createTransformEffect(const SexyVector3& i_position);
	std::string getTransformType(Zombie* i_zombie);

protected:
	void registerForEvents() override;

private:
	void launch(const NukeLauncherEntry& i_entry);
	void onZombieConditionEnded(Zombie* i_zombie, int i_condition);

	std::vector<NukeLauncherEntry> m_shots;
	std::vector<ZombiePtr> m_transformedEntries;

};

class NukeLauncherProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(NukeLauncherProjectileProps, ProjectilePropertySheet, RtClass);

    NukeLauncherProjectileProps()
    {
    	RadiationItemName = "radiation";
    }

    std::string RadiationItemName;
};

class NukeLauncherProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(NukeLauncherProjectile, Projectile, RtClass);
    NukeLauncherProjectile()
    {}

protected:
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

private:
    void SpawnRadiationPiles(const Point& gridPosition);
    void CreateRadiation(const Point& gridPosition);
    void GetRadiationArea(std::vector<Point>& i_points, const Point& gridPosition);
};

class NukeLauncherPlantfoodProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(NukeLauncherPlantfoodProjectile, Projectile, RtClass);

protected:
    virtual bool canAffectBigSize() { return false; }
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

class NukeLauncherAvatarProjectile : public NukeLauncherPlantfoodProjectile
{
public:
    RT_CLASS_DEFINE(NukeLauncherAvatarProjectile, NukeLauncherPlantfoodProjectile, RtClass);

protected:
    bool canAffectBigSize() override { return true; }
};

enum GridItemRadiationPileState
{
    PVZ_BEGIN_ENUM(RADIATIONPILESTATE_),
    RADIATIONPILESTATE_UNKNOWN,
    RADIATIONPILESTATE_RESETTING,
    RADIATIONPILESTATE_IDLE,
    RADIATIONPILESTATE_DEAD,
    PVZ_END_ENUM(RADIATIONPILESTATE_)
};

class GridItemRadiationPile : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemRadiationPile, GridItemAnimation, RtClass);

    GridItemRadiationPile();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(RADIATIONPILESTATE_IDLE); }
    void SetMaxAffectZombieLevel(int i_level) { m_affectZombieLevel = i_level; }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemRadiationPileState i_state);
    void applyRadiation();
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemRadiationPileState m_state;
    int m_affectZombieLevel;
};

class GridItemRadiationPileProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemRadiationPileProps, GridItemAnimationProps, RtClass);
    GridItemRadiationPileProps()
    : Lifetime(1.0)
    , RadiationTime(2.0)
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
    pvztime_t RadiationTime;
    std::vector<std::string> ZombieBlacklist;
    std::string	SmallSizeType;
    std::string	MidSizeType;
    std::string	LargeSizeType;
};

#endif /* PLANT_NUKELAUNCHER_H_ */
