#ifndef __PLANT_IMPATIENSSHOOTER_H__
#define __PLANT_IMPATIENSSHOOTER_H__

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "PlantAnimRig_Impatiensshooter.h"

#include "Projectile.h"
class ImpatiensshooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ImpatiensshooterProps, PlantPropertySheet, RtClass);

    int PlantFoodProjectileCount = 1;
};

class PlantImpatiensshooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantImpatiensshooter, PlantFramework, RtClass);

	virtual void			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	void UpdateActions() override;
	virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;
	int MaxLevel;
	bool isPlantAttack ;
	int temp;
	int flag;
    float updateTemp;

protected:

private:

    enum State
    {
        STATE_PLANTFOOD_ATTACK = STATE_FRAMEWORK_BEGIN,
        STATE_TRANSITION,
        STATE_RECOVERY,
        STATE_ATTACK
    };
    virtual void    onAnimStoppedCallback(const std::string& name) override;
    void firePlantFoodProjectile(pvztime_t i_atTim);
    class Projectile* FireProjectile(PlantWeapon weapon);
	void setState(const uint i_state);
	int32_t m_growthLevel;
	float m_time;
};

class ImpatiensProjectile_1 : public Projectile
{
public:
	RT_CLASS_DEFINE(ImpatiensProjectile_1, Projectile, RtClass);
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void applyConditions(BoardEntity* i_entity);
private:

};
class ImpatiensProjectile_2 : public Projectile
{
public:
	RT_CLASS_DEFINE(ImpatiensProjectile_2, Projectile, RtClass);
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void applyConditions(BoardEntity* i_entity);
private:
};

class ImpatiensProjectile_3 : public Projectile
{
public:
	RT_CLASS_DEFINE(ImpatiensProjectile_3, Projectile, RtClass);
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void applyConditions(BoardEntity* i_entity);
private:
};

class ImpatiensProjectile_4 : public Projectile
{
public:
	RT_CLASS_DEFINE(ImpatiensProjectile_4, Projectile, RtClass);
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void applyConditions(BoardEntity* i_entity);
private:
};

class ImpatiensProjectile_5 : public Projectile
{
public:
	RT_CLASS_DEFINE(ImpatiensProjectile_5, Projectile, RtClass);
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void applyConditions(BoardEntity* i_entity);
private:
};

#endif //__PLANT_IMPATIENSSHOOTER_H__
