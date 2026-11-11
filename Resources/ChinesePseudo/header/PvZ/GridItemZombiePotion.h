//
//  GridItemZombiePotion.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemZombiePotion__
#define __PlantsVersusZombies2__GridItemZombiePotion__

#include "GridItemAnimation.h"

class ZombiePotionProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(ZombiePotionProps, GridItemAnimationProps, RtClass);

	ZombiePotionProps()
	{}

	std::vector<ZombieConditions> EffectStacks;
	std::string EffectSound;
	std::string DestroyedSound;
	std::string DestroyedSoundGargantuar;
	std::string PopAnimEffect;
	std::string PopAnimDestroyed;
};

class GridItemZombiePotion : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemZombiePotion, GridItemAnimation, RtClass);

	GridItemZombiePotion();

	bool IsDamageableByPlants() const override { return false; }
	bool ShouldClipWithWater() const override {return true;}
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;

	bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
	void TakeDamage(const DamageInfo& i_damage) override;

private:
	void onSpawnAnimStopped(const std::string &i_animName);

	bool m_spawned;
};

enum GridItemPotionPoisonPileState
{
    PVZ_BEGIN_ENUM(POTIONPOISONPILESTATE_),
    POTIONPOISONPILESTATE_UNKNOWN,
    POTIONPOISONPILESTATE_RESETTING,
    POTIONPOISONPILESTATE_IDLE,
    POTIONPOISONPILESTATE_DEAD,
    PVZ_END_ENUM(POTIONPOISONPILESTATE_)
};

class GridItemPotionPoisonPile : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemPotionPoisonPile, GridItemAnimation, RtClass);

    GridItemPotionPoisonPile();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(POTIONPOISONPILESTATE_IDLE); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemPotionPoisonPileState i_state);
    void applyPoison();
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    pvztime_t m_creationTime;
    GridItemPotionPoisonPileState m_state;
    pvztime_t m_nextAffectTime;
};

class GridItemPotionPoisonPileProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemPotionPoisonPileProps, GridItemAnimationProps, RtClass);
    GridItemPotionPoisonPileProps()
    : Lifetime(1.0)
    , EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
    , AffectInterval(0)
    , AffectDamage(0)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    pvztime_t Lifetime;
    float AffectInterval;
    float AffectDamage;
};

// GridItemBoundTile

enum BoundTileState
{
	BoundTile_Invalid = -1,
	BoundTile_Idle,
	BoundTile_Bound,
	BoundTile_Cooldown,
	BoundTile_TransIdle,
	BoundTIle_Max,
};

class GridItemZombieBoundTileProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemZombieBoundTileProps, GridItemAnimationProps, RtClass);

	GridItemZombieBoundTileProps();

	float BoundHeight;// toss height
	pvztime_t BoundDuration;// toss duration
	int BoundTileSmallZombie;// distance toss small zombie
	int BoundTileMidZombie;// distance toss mid zombie
	std::string PopAnimIdle;
	std::string PopAnimBound;
	std::string PopAnimCooldown;
	float SmallZombieDropDamage;
	float MidZombieDropDamage;
	pvztime_t BoundCooldownDuration;
};

class GridItemZombieBoundTile : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemZombieBoundTile, GridItemAnimation, RtClass);

	GridItemZombieBoundTile();

	bool IsDamageableByPlants() const override { return false; }
	bool ShouldClipWithWater() const override {return true;}
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

protected:
	void SetState(BoundTileState state);
	void OnStartAnimStopped(const std::string &i_animName);
	void OnBoundAnimStopped(const std::string &i_animName);
	void OnCooldownnimStopped(const std::string &i_animName);
	std::vector<BoardEntity*> FindTargets();
	void BoundZombies(std::vector<BoardEntity*> zombies);
	void OnZombieTossEnd(Zombie* i_zombie);

protected:
	int m_state;
	pvztime_t m_endCooldownTime;
};

#endif /* defined(__PlantsVersusZombies2__GridItemZombiePotion__) */
