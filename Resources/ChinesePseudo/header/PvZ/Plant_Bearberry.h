#ifndef PLANT_BEARBERRY_H
#define PLANT_BEARBERRY_H

#include "PlantFramework.h"
#include "Projectile.h"

class BearberryProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BearberryProps, PlantPropertySheet, RtClass);

    BearberryProps()
    :DoubleAttackRate(0.1f)
    ,Level5AttackRate(0.1f)
    ,ProjectileLobHeight(350.0f)
    ,ProjectileTimeOfFlight(1.2f)
    {}

    float DoubleAttackRate;
    float Level5AttackRate;
    float ProjectileLobHeight;
    float ProjectileTimeOfFlight;
};


class PlantBearberry : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantBearberry, PlantFramework, RtClass);

	virtual void			Initialize() override;
    virtual void			UpdateActions() override;

    virtual bool 			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual void 			PlayAttackAnimation() override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

    virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	void					CancelPlantfood() override;

protected:
    void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);

private:
    int m_attackType;
    int m_attack2Count;
    int m_plantfoodCount;
};

class BearberryBasicProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BearberryBasicProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
protected:
    std::vector<BoardEntityPtr> m_entityList;
};

class BearberryLevel2Projectile : public BearberryBasicProjectile
{
public:
	RT_CLASS_DEFINE(BearberryLevel2Projectile, BearberryBasicProjectile, RtClass);

    virtual bool OnCollideGround() override;
    virtual void moveThroughTime(pvztime_t i_dt) override;
private:
    
};

class BearberryLevel5Projectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BearberryLevel5Projectile, Projectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
protected:
    std::vector<BoardEntityPtr> m_entityList;
    std::vector<ZombiePtr> m_zombieList;
};

class BearberryPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BearberryPlantfoodProjectile, Projectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
protected:
    std::vector<BoardEntityPtr> m_entityList;
};

class PlantAnimRig_Bearberry : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Bearberry, PlantAnimRig, RtClass);
private:
    std::string getPlantFoodMainAnimName() override;

};

#endif