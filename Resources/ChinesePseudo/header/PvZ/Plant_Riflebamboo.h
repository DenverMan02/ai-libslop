#ifndef __Plant_Riflebamboo_H__
#define __Plant_Riflebamboo_H__

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "PlantAnimRig_Riflebamboo.h"

#include "Projectile.h"
class RiflebambooProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(RiflebambooProps, PlantPropertySheet, RtClass);

    int PlantFoodProjectileCount = 1;
    float NormalDamagePerSecond = 200;
    float ExplodeDamage = 300;
    float Timelimit = 3;
};

class PlantRiflebamboo : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantRiflebamboo, PlantFramework, RtClass);

	virtual void			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	void UpdateActions() override;
	virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;
	int MaxLevel = 1;
	bool isPlantAttack  = false ;
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
//	float m_time;
};

class RiflebambooProjectile_1 : public Projectile
{
public:
	RiflebambooProjectile_1();
	RT_CLASS_DEFINE(RiflebambooProjectile_1, Projectile, RtClass);
	virtual void moveThroughTime(pvztime_t i_dt) override;
	bool m_normalMotion = true;
	bool is_plantfood = false;
	bool has_avatar = false;
//	SexyVector3 m_velocity;
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	virtual void applyConditions(BoardEntity* i_entity);
	void explode();
	void onUpdate(pvztime_t i_dt) override;
	float T_count = 0;
	int m_state = 0;
	float T_interval_begin = 0;
	bool before_interval = false;
	RtWeakPtr<Zombie> m_hookedZombie = NULL;
	float T_limit = 3; //碰撞爆炸时间
private:


};


#endif //__Plant_Riflebamboo_H__
