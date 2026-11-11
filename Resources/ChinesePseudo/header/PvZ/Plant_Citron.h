//
//  Plant_Citron.h
//  PlantsVersusZombies2
//
//  Created by Andy Seavy on 7/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PLANT_CITRON_H__
#define __PLANT_CITRON_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "PlatformAutodetect.h"
#include "Projectile.h"
#include "ProjectilePropertySheet.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "GameSubSystem.h"

class BoardEntity;
class Zombie;

enum Citron_State
{
	CITRONSTATE_IDLE = STATE_FRAMEWORK_BEGIN, // bobbing around, ready to spew the goods
	CITRONSTATE_ATTACK,                       // plasma is released
    CITRONSTATE_RECOVER,                      // citron is pulling itself together
    CITRONSTATE_CHARGING,                     // getting charged up.
    CITRONSTATE_PLANTFOOD,                    // in plantfood state.
};

class PlantCitron : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCitron, PlantFramework, RtClass);

    PlantCitron();
	
    void	Initialize() override;
    void	UpdateActions() override;
	bool	CanApplyPlantfood() override;
	void	ApplyPlantfood() override;
	void	CancelPlantfood() override;

	void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;
    
    void ReleaseChainLightning();
    void Idle() override;
	virtual Projectile*	addProjectile(int weapon);
protected:
    void			setState(uint i_plantState);
    void 			fireProjectileCallback(pvztime_t i_atTime);
    
    ZombiePtr       FindTargetLightningZombie();
    
private:
    std::vector<BoardEntityPtr> m_hitTargets;
    
    ProjectilePtr               m_plantfood_proj;
    
    pvztime_t                   m_releaseChainTime;
};

class GiantPlasmaProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(GiantPlasmaProjectileProps, ProjectilePropertySheet, RtClass);
	
	GiantPlasmaProjectileProps()
	{
		MinTossAngle = 25.0f;
		MaxTossAngle = 55.0f;
		TossSpeed = 600.0f;
		TossSpinRadiansPerSecond = -500.0f;
	}
	
	float MinTossAngle;
	float MaxTossAngle;
	float TossSpeed;
	float TossSpinRadiansPerSecond;
};

class GiantPlasmaProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(GiantPlasmaProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;

private:
    void playHitEffect(BoardEntity* i_thitOwner, bool i_playSpark);
    void hitMechZombie(Zombie* i_zombie);
    void hitNormalZombie(Zombie* i_zombie);
};

class PlasmaCloudProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PlasmaCloudProjectileProps, ProjectilePropertySheet, RtClass);
    
    PlasmaCloudProjectileProps()
    {
        CloudDamage = 0;
        CloudDuration = 0;
    }
    
    float CloudDamage = 0;
    float CloudDuration = 0;
};

class PlasmaCloudProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PlasmaCloudProjectile, Projectile, RtClass);

    void SetCloudDamage(float i_damage);
    void SetDuration(float i_duration);

protected:
	virtual void onProjectileInitialized() override;
    bool handleImpact(BoardEntity* i_impactedEntity) override;
private:
    void PlayCloundEffect(const SexyVector2& pos);

    float m_cloudDamage;
    float m_duration;
};

class ContinuousDamageSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ContinuousDamageSystem, GameSubSystem, RtClass);
private:
    class Item
    {
    public:
        void ApplyDamage();
        Item(float damage, pvztime_t endTime, const SexyVector2& pos, float radius);
        Item();
    public:
        SexyVector2 m_pos;
        float m_radius = 0;
        float m_damage = 0;
        pvztime_t m_endTime = 0;
        pvztime_t m_lastDamageTime = 0;
        BoardEntityTypeFlag m_targetType = ENTITYTYPE_ZOMBIE | ENTITYTYPE_GRIDITEM;
        TeamFlags m_teamFlag = TEAM_ZOMBIES;
    };
public:
    void Update() override;
    void AddItem(float damage, float duration, const SexyVector2& pos, float radius);
private:
    pvztime_t m_nextUpdate = 0;
    std::vector<Item> m_item;
};

#endif // __PLANT_CITRON_H__
