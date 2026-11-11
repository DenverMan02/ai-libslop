#ifndef __PLANT_POISONPEASHOOTER_H__
#define __PLANT_POISONPEASHOOTER_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"


class Zombie;
class PoisonPeashooterProps;

class PoisonPeashooterCounter : public PlantFoodCounter
{
public:
	RT_CLASS_DEFINE(PoisonPeashooterCounter, PlantFoodCounter, RtClass);

	void Update();
    void SetOffset(SexyVector3 pos) { _offset = pos; }
    void SetPlantAction(PlantAction action) { _action = action; }
    void SetPlantProps(const PoisonPeashooterProps* props) { _props = const_cast<PoisonPeashooterProps*>(props); }
    void SetPlant(PlantPtr i_plant) {m_plant = i_plant; }

protected:
    SexyVector3 _offset;
    PlantAction _action;
    PoisonPeashooterProps* _props;
    PlantPtr m_plant;
};

// plant state
enum {
    STATE_INVALID = -1,
    STATE_NORMAL,
    STATE_LEVEL5PROJECTILE,// play level5 shoot counter
    STATE_MAX,
};

// Poison Peashooter Plant
class PlantPoisonPeashooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPoisonPeashooter, PlantFramework, RtClass);
    
protected:
    void ApplyPlantfood() override;
    bool CanApplyPlantfood() override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    PlantPoisonPeashooter();
    virtual ~PlantPoisonPeashooter() {}

    virtual void	Initialize() override;

    void UpdateActions()	override;
    
private:
    void firePlantFoodProjectile();
    void firePoisonPeaProjectile();

    void LaunchLevel5Projectile(PlantAction action, SexyVector3 offset, const PoisonPeashooterProps* props);

    PoisonPeashooterCounter _peashooterCounter;
};



//// Projectile
class PlantPoisonPeashooterProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PlantPoisonPeashooterProjectile, Projectile, RtClass);

    virtual ~PlantPoisonPeashooterProjectile() {}

    void InitializeValues(float i_stacks, float i_dps, float i_speedPercentDecrease, float i_duration);
    float GetResistancePiercing()  { return 0.01f; }

protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    void ExecuteLevelAction(Zombie* ptr, float count);
    void PoisonExplode(Zombie* ptr);
    
    virtual void applyConditions(BoardEntity* i_entity);
    
    float m_stacks, m_dps, m_speedPercentDecrease, m_duration;

    int m_plantLevel;// for level 2,3 extra explode
};

class PlantPoisonPeashooterLevel5Projectile : public PlantPoisonPeashooterProjectile
{
public:
    RT_CLASS_DEFINE(PlantPoisonPeashooterLevel5Projectile, PlantPoisonPeashooterProjectile, RtClass);

protected:
    void applyConditions(BoardEntity* i_entity) override;

    void PoisonGrid(Sexy::Point point);
};

//// Plantfood projectile
class PlantPoisonPeashooterPlantFoodProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PlantPoisonPeashooterPlantFoodProjectile, Projectile, RtClass);
    
    PlantPoisonPeashooterPlantFoodProjectile();
    void InitializeValues(float i_dps, float i_speedPercentDecrease, float i_duration, float i_knockDistance, float i_knockTime, float i_knockHeight, float i_gridLifeTime, float i_gridDuration, float i_gridSpeedPercentDecrease, float i_gridDPS);
    float GetResistancePiercing()  { return 0.01f; }
protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override {return true;}
    void onUpdate(pvztime_t i_dt) override;
    void onProjectileInitialized() override; 
    virtual ~PlantPoisonPeashooterPlantFoodProjectile() {}

    virtual void applyConditions(BoardEntity* i_entity);
    void spawnOrRefreshPoisonTiles();
    void addPoisonTileToBoard(Point& i_square);
    virtual void PoisonExplode(Zombie* zombie);
	void damageEntity(class BoardEntity* i_entity) override;
    
    bool m_isFirstTile;
    bool m_isAvatar;// chck plant is avatar
    int m_plantLevel;// for explode damage calc
    float m_stacks, m_dps, m_speedPercentDecrease, m_duration, m_knockDistance, m_knockTime, m_knockHeight, m_gridLifetime, m_gridDuration, m_gridSpeedPercentDecrease, m_gridDPS;
};

class PlantPoisonPeashooterPlantFoodAvatarProjectile : public PlantPoisonPeashooterPlantFoodProjectile
{
public:
    RT_CLASS_DEFINE(PlantPoisonPeashooterPlantFoodAvatarProjectile, PlantPoisonPeashooterPlantFoodProjectile, RtClass);

protected:
    void PoisonExplode(Zombie* zombie) override;
};

//// Plant food poison trail tile
class PoisonGridItem : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(PoisonGridItem, GridItemAnimation, RtClass);
    
    void ResetTimer();
    void InitializeValues(float i_gridLifeTime, float i_gridDuration, float i_gridSpeedPercentDecrease, float i_gridDPS, float i_resistancePiercing);
	float GetResistancePiercing()  { return m_resistancePiercing; }// zhousen merge change
    void SetAvatar(bool isAvatar) { m_isAvatar = isAvatar; }

protected:
    int CalcRenderOrder() const override;
    void onGridItemInitialize() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    virtual ~PoisonGridItem() {}
    void onUpdate() override;
	
private:
    pvztime_t m_destroyTime;
    
    void applyConditions();
    void fadeTile();
    
    bool m_isAvatar;// check if damage is multiply ratio
    float m_gridLifetime, m_gridDuration, m_gridSpeedPercentDecrease, m_gridDPS, m_resistancePiercing;
};


//// Plantfood projectile props
class PoisonPeashooterPlantFoodProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PoisonPeashooterPlantFoodProjectileProps, ProjectilePropertySheet, RtClass);
    
    PoisonPeashooterPlantFoodProjectileProps()
    {
        PoisonExplodeDamage = 300.0f;
    }

    float PoisonExplodeDamage;
};

class PoisonPeashooterPlantFoodAvatarProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PoisonPeashooterPlantFoodAvatarProjectileProps, ProjectilePropertySheet, RtClass);
        
    PoisonPeashooterPlantFoodAvatarProjectileProps()
    {
        PoisonExplodeDamage = 300.0f;
    }

    float PoisonExplodeDamage;
};

//// Projectile Props
class PoisonPeashooterProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PoisonPeashooterProjectileProps, ProjectilePropertySheet, RtClass);
    
    PoisonPeashooterProjectileProps()
    {
        PoisonExplodeDamage = 300.0f;
    }

    float PoisonExplodeDamage;
};

//// Plant food posion trail tile props
class PoisonGridItemProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(PoisonGridItemProps, GridItemAnimationProps, RtClass);
    
    PoisonGridItemProps()
    {
    }
};

class PoisonPeashooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PoisonPeashooterProps, PlantPropertySheet, RtClass);
    
    PoisonPeashooterProps()
    {
        Level5ProjectileRatio = 0.1f;
        Level5ProjectileDuration = 0.5f;
        Level5ProjectileCount = 5;
        MaxStacks = 0;
        PoisonDPSPerStack = SpeedPercentDecreasePerStack = PoisonAndSlowDuration = PlantfoodPoisonDPS = PlantfoodSpeedPercentDecrease = PlantfoodPoisonAndSlowDuration = PlantfoodKnockBackDistance = PlantfoodKnockBackTime = PlantfoodKnockBackHeight = GridItemLifetime = GridItemPoisonAndSlowDuration = GridItemSpeedPercentDebuff = GridItemPoisonDPS = 0.0f;
    }

    float Level5ProjectileRatio;
    float Level5ProjectileDuration;
    int Level5ProjectileCount;

    int MaxStacks;
    
    float PoisonDPSPerStack, SpeedPercentDecreasePerStack, PoisonAndSlowDuration;
    
    float PlantfoodPoisonDPS, PlantfoodSpeedPercentDecrease, PlantfoodPoisonAndSlowDuration, PlantfoodKnockBackDistance, PlantfoodKnockBackTime, PlantfoodKnockBackHeight;
    
    float GridItemLifetime, GridItemPoisonAndSlowDuration, GridItemSpeedPercentDebuff, GridItemPoisonDPS;
};

#endif //__PLANT_POISONPEASHOOTER_H__
