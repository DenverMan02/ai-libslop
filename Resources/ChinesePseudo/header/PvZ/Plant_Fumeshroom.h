#ifndef _Plant_Fumeshroom_
#define _Plant_Fumeshroom_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"

class Zombie;

class ZombieStunEffect
{
public:
	ZombieStunEffect()
	: StartTime(0.0f)
	, IsFinished(false)
	{}

	ZombiePtr Zombie;
	pvztime_t StartTime;
	bool IsFinished;
};

class PlantFumeshroomSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantFumeshroomSubSystem, GameSubSystem, RtClass);

 	virtual void Update() override;

	void CauseZombieStun(Zombie* i_zombie, float i_stunTimeRate);

protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;

private:
	std::vector<ZombieStunEffect> m_zombieStates;
};

class PlantFumeshroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantFumeshroom, PlantFramework, RtClass);
	
	virtual void			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
    virtual Projectile*	    Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual bool			OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void Idle() override;
private:
	void					damageZombies(PlantWeapon i_plantWeapon, bool i_special);
	void					damageZombies(PlantWeapon i_plantWeapon, DamageInfo i_damage, bool i_special);
	void					pushZombieAway(Zombie* i_zombie);
	void					playZombieHitEffect(Zombie* i_zombie, SexyVector3 i_offset);

	void 					AbsorbZombieAtGrid(int i_col, int i_row);

	float					m_plantfoodDamageApplied;
	float					m_plantfoodNextHitEffect;
	float					m_plantfoodAttackDuration;
	bool					m_hasStartedPlantfoodAttack;
	std::vector<RtWeakPtr<class Zombie> >	m_absorbZombieArray;
    
    bool                    m_bInEliminate;
    PeashooterPlantfood     m_plantfood;
};

#endif //__PLANT_PEASHOOTER_H__
