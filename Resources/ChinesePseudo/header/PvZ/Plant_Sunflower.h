#ifndef __PLANT_SUNFLOWER_H__
#define __PLANT_SUNFLOWER_H__

#include "PlantFramework.h"
#include "RtObject.h"
#include "SunProducer.h"
#include "Plant.h"
#include "Projectile.h"
#include "AnimRigLayerSet.h"
#include "GridItemAnimation.h"
class Collectable;
/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/



class PlantSunflower : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSunflower, PlantFramework, RtClass);

	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	virtual void	DoSpecial(int i_extraParam = 0) override;
	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
	virtual void	ProduceSun(const PlantAction& i_fromAction) override;
	virtual void 	ProduceCoin(const PlantAction& i_fromAction);
	virtual void 	onKilled(bool i_instantKill) override;
	void			onGroundCherryApplyPlantFood();
	void 			registerForEvents() override;
	void 			unregisterForEvents() override;

	int m_plantFoodSunsToSpawn;
	bool m_ProduceSunfirst = true;
protected:
    virtual void ProduceSun(const PlantAction& i_fromAction, const std::string& sunTypeName);
    virtual void ProduceCoin(const PlantAction& i_fromAction, const std::string& coinTypeName);
    Collectable * ProduceCollectable(const PlantAction& i_fromAction, const std::string &collectableTypeName);
private:
	virtual std::string getCollectableTypeName();
};


enum SeedState
{
    PVZ_BEGIN_ENUM(SEEDSTATE_),
    SEEDSTATE_UNKNOWN,
    SEEDSTATE_BIRTH,
    SEEDSTATE_IDLE,
    SEEDSTATE_ATTACK,
    SEEDSTATE_BINDED,
    SEEDSTATE_BINDED_DEATH,
    PVZ_END_ENUM(SEEDSTATE_)
};


class GridItemSunSeed : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemSunSeed, GridItemAnimation, RtClass);
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	GridItemSunSeed()
	: m_state(SEEDSTATE_UNKNOWN)
	{}
	void updateState();
	int	CalcRenderOrder() const override;
	SeedState getState();
	void setState(SeedState i_state);
	PlantingReason GetCantPlantReason() const;
	void setExtraTime(float i_second);
	pvztime_t m_Time;
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	virtual void sunflowerOnTakeDamage();
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
private:
	ZombiePtr m_bindedZombie;
	SeedState m_state;
	int m_damageStates;
	int m_currDamageState;
	void onAttackAnimDone(const std::string& i_animLabelName);
	void tryFindZombie();
	void setBindZombie(ZombiePtr i_zombie) { m_bindedZombie = i_zombie; }

	void onZombieDeath(Zombie* zombie, const DamageInfo* i_deathBlow);
	bool IsInState(uint32 state) const { return m_state == state; }

	float m_extraTime;
};


class GridItemSunSeedAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemSunSeedAnimRig, PopAnimRig, RtClass) {}

    GridItemSunSeedAnimRig();
    void PlayIdle();
    void PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};



#endif //__PLANT_SUNFLOWER_H__
