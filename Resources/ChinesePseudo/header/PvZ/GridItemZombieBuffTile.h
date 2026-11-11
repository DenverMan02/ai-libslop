/*
 * GridItemZombieBuffTile.h
 *
 *  Created on: 2021-8-10
 *      Author: admin
 */

#ifndef GRIDITEMZOMBIEBUFFTILE_H_
#define GRIDITEMZOMBIEBUFFTILE_H_

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"
#include "GameSubSystem.h"

enum GridItemZombieBuffTileState
{
    PVZ_BEGIN_ENUM(ZOMBIEBUFFTILESTATE_),
    ZOMBIEBUFFTILESTATE_UNKNOWN,
    ZOMBIEBUFFTILESTATE_RESETTING,
    ZOMBIEBUFFTILESTATE_IDLE,
    ZOMBIEBUFFTILESTATE_DEAD,
    PVZ_END_ENUM(ZOMBIEBUFFTILESTATE_)
};

class GridItemZombieBuffTile : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemZombieBuffTile, GridItemAnimation, RtClass);

    GridItemZombieBuffTile();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(ZOMBIEBUFFTILESTATE_RESETTING); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemZombieBuffTileState i_state);
    virtual void applyEffects();
    virtual void doApplyEffects(const std::vector<BoardEntity*>& i_zombies);
    virtual bool canApplyEffects(const BoardEntity* i_entity);
    virtual void doApplyEffect(const BoardEntity* i_entity);
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	virtual SexyVector2	getRenderOffset() override;

private:
    void onResetFinished(const std::string &i_animName);
    void getValidZombies(std::vector<BoardEntity*>& i_zombies);
    void CheckGridPlants(int i_gridX, int i_gridY);

    pvztime_t m_creationTime;
    GridItemZombieBuffTileState m_state;
};

class GridItemZombieBuffTileProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemZombieBuffTileProps, GridItemAnimationProps, RtClass);
    GridItemZombieBuffTileProps()
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
};

class GridItemZombieBuffTileShield : public GridItemZombieBuffTile
{
public:
    RT_CLASS_DEFINE(GridItemZombieBuffTileShield, GridItemZombieBuffTile, RtClass);

    GridItemZombieBuffTileShield();
protected:
    void doApplyEffect(const BoardEntity* i_entity) override;
};

class GridItemZombieBuffTileShieldProps : public GridItemZombieBuffTileProps
{
public:
    RT_CLASS_DEFINE(GridItemZombieBuffTileShieldProps, GridItemZombieBuffTileProps, RtClass);
    GridItemZombieBuffTileShieldProps()
    : ShieldHP(1.0)
    , ShieldSizeX(0)
    , ShieldSizeY(0)
    {}

    float ShieldHP;
	float ShieldSizeX;
	float ShieldSizeY;
};

struct ShieldRecord
{
	ShieldRecord()
    :ShieldHP(0)
    ,ShieldSizeX(0)
	,ShieldSizeY(0)
    {}

    float ShieldHP;
    float ShieldSizeX;
    float ShieldSizeY;
    RtWeakPtr<class Zombie> Zombie;
};

struct BuffShieldData
{
	BuffShieldData()
	{}

	RtWeakPtr<class Zombie> Zombie;
	RtWeakPtr<class GridItemProtectorShield> Shield;
};

class BuffShieldSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(BuffShieldSubsystem, GameSubSystem, RtClass);

    void Generate(ShieldRecord i_record);
    void Update() override;

protected:
    void onInitialized() override;
    void registerForEvents() override;
    bool canGenerate(RtWeakPtr<class Zombie> i_zombie);

private:
    void onZombieDestroyed(class Zombie* i_zombie);

    std::vector<BuffShieldData> m_entities;
};

class GridItemZombieBuffTileCondition : public GridItemZombieBuffTile
{
public:
    RT_CLASS_DEFINE(GridItemZombieBuffTileCondition, GridItemZombieBuffTile, RtClass);

    GridItemZombieBuffTileCondition();
protected:
    void doApplyEffect(const BoardEntity* i_entity) override;
};

class GridItemZombieBuffTileConditionProps : public GridItemZombieBuffTileProps
{
public:
    RT_CLASS_DEFINE(GridItemZombieBuffTileConditionProps, GridItemZombieBuffTileProps, RtClass);
    GridItemZombieBuffTileConditionProps()
    : Duration(0)
    , PopAnimEffect("")
    {}

    ZombieConditions Condition;
    float Duration;
    std::string PopAnimEffect;
};


#endif /* GRIDITEMZOMBIEBUFFTILE_H_ */
