/*
 * Plant_MissileToe.h
 *
 *  Created on: 2017-10-19
 *      Author: Administrator
 */

#ifndef PLANT_MISSILETOE_H_
#define PLANT_MISSILETOE_H_

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "StandardLevelIntro.h"
#include "GameSubSystem.h"
#include "GridItemAnimation.h"

namespace Message
{
	void MissileToeSelected();
	void MissileToeLaunched();
	void MissileToeTappedOnCooldown();
}

enum MissileToeState
{
	MISSILETOE_STATE_SELECTED = STATE_FRAMEWORK_BEGIN,
	MISSILETOE_STATE_FIRING,
	MISSILETOE_STATE_PLANTFOOD,
	MISSILETOE_STATE_RECOVERING,
	MISSILETOE_STATE_RECOVERING_END,
};

class MissileToeProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MissileToeProps, PlantPropertySheet, RtClass);

	MissileToeProps()
	{
		NumPlantfoodRockets = 3;
		FireTime = 1.0f;
		PlantfoodFireTime = 0.5f;
		TargetOffset.x = 0;
		TargetOffset.y = 0;
		ChillDuration = 10.0f;
		FreezeDuration = 0.0f;
		Lvl5ProjRate = 0.0f;
		RecoverReducedRate = 0.0f;
		ImprovedReducedBonus = 0.0f;
	}

	int NumPlantfoodRockets;
	pvztime_t FireTime;
	pvztime_t PlantfoodFireTime;
	SexyVector2 TargetOffset;
	float ChillDuration;
	float FreezeDuration;
	float Lvl5ProjRate;
	float RecoverReducedRate;
	float ImprovedReducedBonus;
};

class PlantMissileToe : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMissileToe, PlantFramework, RtClass);

	PlantMissileToe();

	void Initialize() override;
	void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	void SetCanOnlyTargetZombies(bool i_x) { m_onlyTargetZombies = i_x; }
	void SetFireIgnoreBoardState(bool i_x) { m_fireIgnoreBoardState = i_x; }

	void FireMissile(const Sexy::Point& i_targetLocation);
	void NotifySetHidden(bool i_newValue, bool i_oldValue) override;

	void onApplyCondition(PlantConditions i_condition) override;
	bool IsProjectileLevel5() { return m_isCurLevel5Proj; }
	void SetLevel5Proj(bool isLv5);
	void TryShootLevel5(bool i_display);
	void AutoFire() override;

private:

	void registerForEvents() override;
	void unregisterForEvents() override;

	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCursorDestroyed(BaseCursor* i_cursor);

	void onAnimStoppedCallback(const std::string& i_animName) override;

	void setState(const int i_newState);
	bool select();
	void deselect();
	void forceStopSelection();
	bool canFire() const;

	void queueShot(pvztime_t i_launchTime, const Point& i_targetLocation);

	bool m_onlyTargetZombies;
	bool m_fireIgnoreBoardState;
	float m_recoveryTime;

	// not serialized
	class MissileToeTargetCursor* m_targetCursor;
	bool m_isCurLevel5Proj;
};

class PlantAnimRig_MissileToe : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_MissileToe, PlantAnimRig, RtClass);
	bool PlaySelected();
	bool PlayRecoverStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRecoverLoop();
	bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
	void SetIsLevel5(bool isLv5)
	{
		m_islevel5 = isLv5;
	}
private:
	bool m_islevel5 = false;
};

class MissileToeSuperProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(MissileToeSuperProjectile, Projectile, RtClass) {}

private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void MarkCenterTarget(BoardEntity* i_entity);
	void DoSplashDamage(int i_sourceCol, int i_sourceRow);
};

class MissileToeSuperProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(MissileToeSuperProjectileProps, ProjectilePropertySheet, RtClass);

	MissileToeSuperProjectileProps()
	{
		ImpactDamage = 300.0f;
	};

	float ImpactDamage;
};

class MissileToeTutorialModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(MissileToeTutorialModule, StandardLevelIntro, RtClass);

	void initializeModule() override;
	void registerForEvents() override;

	void onLevelEnded();
	void onMissileToeSelected();
	void onMissileToeLaunched();
	void onMissileToeTappedWhileCoolingDown();
	void onTutorialFinished();
	void onZombieDestroyed(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

protected:
	void startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false) override;
	void startNarration(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE) override;

private:
	void pointArrowAtZombie();
	void pointArrowAtMissileToe();

	bool m_tutorialIsActive;
	ZombiePtr m_tutorialZombie;
	PlantPtr m_tutorialMissileToe;
	RtWeakPtr<class Effect_BouncingArrow> m_bouncingArrow;
};

class MissileToeTutorialProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(MissileToeTutorialProperties, StandardLevelIntroProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return MissileToeTutorialModule::StaticGetClass();
	}

	MissileToeTutorialProperties()
	{
	}

	void GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames) const override;
};

class MissileToeLauncherSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(MissileToeLauncherSubSystem, GameSubSystem, RtClass);

	void QueueShot(PlantMissileToe* i_owner, pvztime_t i_launchTime, const Point& i_target, bool i_isPlantfood);

	struct MissileToeLauncherEntry
	{
		MissileToeLauncherEntry() {}
		MissileToeLauncherEntry(PlantMissileToe* i_owner, pvztime_t i_launchTime, const Point& i_target, bool i_isPlantfood);

		PlantPtr Owner;
		RtWeakPtr<const MissileToeProps> MissileToePropertySheet;
		pvztime_t LaunchTime;
		Point Target;
		bool m_isPlantfood;
		bool m_isLevel5;
	};

	void Update() override;

private:
	void launch(const MissileToeLauncherEntry& i_entry);

	std::vector<MissileToeLauncherEntry> m_shots;
};

enum GridItemIcePitState
{
    PVZ_BEGIN_ENUM(ICEPITSTATE_),
    ICEPITSTATE_UNKNOWN,
    ICEPITSTATE_RESETTING,
    ICEPITSTATE_IDLE,
    ICEPITSTATE_DEAD,
    PVZ_END_ENUM(ICEPITSTATE_)
};

class GridItemIcePit : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemIcePit, GridItemAnimation, RtClass);

    GridItemIcePit();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(ICEPITSTATE_IDLE); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemIcePitState i_state);
    void applyIcePit();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemIcePitState m_state;
};

class GridItemIcePitProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemIcePitProps, GridItemAnimationProps, RtClass);
    GridItemIcePitProps()
    : Lifetime(1.0)
    , IceTime(3.0)
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
    pvztime_t IceTime;
    std::vector<std::string> ZombieBlacklist;
};

class MissileToeLvl5ProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(MissileToeLvl5ProjectileProps, ProjectilePropertySheet, RtClass);

	MissileToeLvl5ProjectileProps()
	{
		AreaDamage = 0.0f;
		RowNum = 0;
		ColumnNum = 0;
	}

	float AreaDamage;
	int RowNum;
	int ColumnNum;

};

class MissileToeLvl5Projectile : public Projectile
{
public:
	RT_CLASS_DEFINE(MissileToeLvl5Projectile, Projectile, RtClass);
	MissileToeLvl5Projectile();
	virtual ~MissileToeLvl5Projectile();
private:
	RtWeakPtr<Effect_PopAnim> 	m_effectMissile;
	bool m_hitGround;
public:
	bool OnCollideGround() override;
	bool PlayLevel5TimeCountDownAnim();
	bool PlayLevel5AfterExplosionAm();
private:
	bool  InitExplosionAnim();
	void  DoExplosion(bool i_first);
private:
	void onProjectileAnimStop(const std::string& i_animName);

	void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);
	void onExplosionAnimStopped(StandaloneEffect* i_effect);
};

#endif /* PLANT_MISSILETOE_H_ */
