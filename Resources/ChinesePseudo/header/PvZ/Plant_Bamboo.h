#ifndef __PLANT_BOMBOO_H__
#define __PLANT_BOMBOO_H__

#include "PlantFramework.h"
#include "EffectAnimRig_SpikeweedSaw.h"
#include "BambooProjectile.h"
#include "Projectile.h"

class PlantBamboo : public PlantFramework
{
public:
    enum Bamboo_State
    {
        BAMBOOSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
        BAMBOOSTATE_PREPARING,
        BAMBOOSTATE_ATTACKING,
        BAMBOOSTATE_PLANTFOOD,
    };
    
    
	RT_CLASS_DEFINE(PlantBamboo, PlantFramework, RtClass);
    
    PlantBamboo();
	virtual void Initialize() override;
    virtual void DoSpecial(int i_extraParam) override;
	
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;
    virtual void UpdateActions() override;
    
    
//    virtual bool CanBeTargeted();
    virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    
	virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
    bool FindTarget(PlantWeapon i_plantWeapon);
    virtual void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;
    void onPlantfoodAttackFinished(const std::string& i_animName);
    void onAttackFinished(const std::string& i_animName);
    
private:
    bool m_bAttacking;
    int m_rangeNum;
    pvztime_t m_animInterval;
    bool m_isStarAttack;
    bool m_attackDone;
    
    void setState(uint i_plantState);
    void fireProjectileCallback(pvztime_t i_atTime);
    void updateProjectile();
};


#endif
