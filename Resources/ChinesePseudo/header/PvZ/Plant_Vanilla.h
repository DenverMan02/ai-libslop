//
//  Plant_Vanilla.h
//  PlantsVersusZombies2
//
//  Created by Greg Silva on 1/3/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Vanilla_h
#define PlantsVersusZombies2_Plant_Vanilla_h

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "GridItem.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"

class Zombie;

class PlantTypeVanilla : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeVanilla, PlantType, RtClass);
	const std::string& getAvatarPlantFoodLayer() const;
private:
	std::string AvatarPlantFoodLayer;
};

class PlantVanilla : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantVanilla, PlantFramework, RtClass);

	void Initialize() override;
	bool            CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
	
	PlantTargetParams GetTargetParamsForWeapon(PlantWeapon i_plantWeapon) override;

	bool CheckLv5SkillTriggle();
	void ClearLv5SkillTriggle();

	void SpawnProjectiles();
	void createCloudEffect();

	void PlaySuperAnimation();
	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;

	void blowZombies();

	bool canBeMovedByVanilla(const Zombie* i_zombie) const;

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

protected:
	enum VanillaWeapon
	{
		WEAPON_LV5 = WEAPON_AVATAR,
	};

private:
	std::vector<int> ZombieTargetWeights;
	std::vector<BoardEntityPtr> PlantfoodTargetedZombies;
	
	bool m_bLevel5Triggled;

	bool ZombieIsBlacklisted(Zombie* zombie);

	int m_nAttackTimes;
	float m_newAvatarSkillBoostRate1;
};

class VanillaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(VanillaProps, PlantPropertySheet, RtClass);
	
	VanillaProps()
	{
		PlantFoodTargets = 3;
		PlantFoodAttackCooldown = 2.0f;
		PlantFoodPushBackDistance = 100.0f;
		PlantFoodPushBackHeight = 100.0f;
		PlantFoodPushBackTime = 1.0f;
		
		NormalHypnoTargets = 1;
		NormalAttackCooldown = 2.0f;

		WeightTargetNormalZombie = 1;
		WeightTargetGargantuarZombie = 1;
		WeightTargetOtherZombie = 1;
		Lv5TriggleRate = 0.25f;
		Level2Rate = 0.2;
		BlowDamage = 80.f;
		FlyingZombieUpAccelerationFactor = 0.f;
		FlyingZombieBlowingSpeed = 100.f;
		
	}
	
	int   PlantFoodTargets;
	float PlantFoodAttackCooldown;
	float PlantFoodPushBackDistance;
	float PlantFoodPushBackHeight;
	pvztime_t PlantFoodPushBackTime;

	// number of targets for plantfood
	int   NormalHypnoTargets;
	float NormalAttackCooldown;
	
	int WeightTargetNormalZombie;
	int WeightTargetGargantuarZombie;
	int WeightTargetOtherZombie;

	ZombieRestrictionSet CannotBeHypnotized;

	float Lv5TriggleRate;
	float AvatarFlickRate;
	float Level2Rate;

	float BlowDamage;

	float FlyingZombieUpAccelerationFactor;
	float FlyingZombieBlowingSpeed;

	float GetPacketCoolDownTime(int iStarLv) const override;
};

class PlantAnimRig_Vanilla : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Vanilla, PlantAnimRig, RtClass);

	PlantAnimRig_Vanilla():m_plant(NULL), m_bLevel5Triggled(false){ }

	std::string getCyclingAnimName() override;
	std::string getPreviewAnimName();
	
	bool PlayPreviewAnim(bool bHideLayer = false) override { return PlayAndContinue(getPreviewAnimName()); }
	void onAnimStopped() override;
	void SetPlant(PlantPtr plant) { m_plant = plant; }
	void setPlantFoodPlayCount(int plantFoodPlayCount);
	int getPlantFoodPlayCount() const;

	virtual bool playPlantFoodOn() override;
    
protected:
    virtual void onPopAnimInitialized() override;
    
private:
	std::string getPlantFoodOnAnimName() override { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }

	PlantPtr m_plant;
	bool m_bLevel5Triggled;
};

class VanillaProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(VanillaProjectile, Projectile, RtClass);
	VanillaProjectile() : m_nPlantLevel(0), m_bIsTossed(false) {}
	void moveThroughTime(pvztime_t i_dt) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void SetTargetZombie(ZombiePtr i_targetZombie);
	void SetTargetZombie(Zombie* i_targetZombie);
	void MakePositionAdjustment();
	void SetPlantLevel(int level);
	int GetPlantLevel() const;

	void SetIsTossed(bool isTossed);
	bool GetIsTossed() const { return m_bIsTossed; };

	virtual void onUpdate(pvztime_t i_dt) override;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
private:
	bool isZombieCanToss(ZombiePtr i_targetZombie);
	int32 ZombieTosserEnd();
	float calcDesiredRotation(SexyVector3 i_toTarget);
	ZombiePtr m_targetZombie;
	int m_nPlantLevel;
	bool m_bIsTossed;
};

class VanillaProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(VanillaProjectileProps, ProjectilePropertySheet, RtClass);
	
	bool HealsOnHypnosis;
	SexyVector2 InitialPositionOffset;
	float SpecialDamage;
	float Level2Rate;
};


class VanillaTornadoProjectile : public Projectile
{
public:
	enum KiwiProjectileStatus
    {
        Tornado_Flying,
        Tornado_Hitting,
    };
	RT_CLASS_DEFINE(VanillaTornadoProjectile, Projectile, RtClass);
	virtual void onUpdate(pvztime_t i_dt) override;
	virtual void onProjectileInitialized() override;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void MakePositionAdjustment();
private:
	void dealTornadoAreaDamage();
	bool isZombieShouldStun(Zombie* i_zombie);
	void onDestroy() override;
	uint32 m_state;
	
	pvztime_t k_alivePeriod;
    pvztime_t k_damageInterval;
    
    pvztime_t m_damageTime; //For dealing damage with interval
    pvztime_t m_aliveTime; //For life period
private:
	bool m_bIsCollided;
	
};

////////
class VanillaTornadoProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(VanillaTornadoProjectileProps, ProjectilePropertySheet, RtClass);
    
    VanillaTornadoProjectileProps()
    {
        AirshipDamage = 1000.0f;
    }
    
    float		AirshipDamage;
	SexyVector2 InitialPositionOffset;
};


class VanillaPlantFoodProjectile : public Projectile
{
public:
 	VanillaPlantFoodProjectile(): m_AttackTimes(0) {}
	RT_CLASS_DEFINE(VanillaPlantFoodProjectile, Projectile, RtClass);
	virtual void onUpdate(pvztime_t i_dt) override;
	virtual void onProjectileInitialized() override;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void MakePositionAdjustment();
	void moveThroughTime(pvztime_t i_dt) override;
	bool ZombieCanBeFlickedOff(const Zombie* i_zombie);
private:
	uint32 m_state;	    
	int m_AttackTimes;
	ZombiePtr m_curZombie;
};


////////
class VanillaPlantFoodProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(VanillaPlantFoodProjectileProps, ProjectilePropertySheet, RtClass);
    
    VanillaPlantFoodProjectileProps()
    {
        AirshipDamage = 1000.0f;
    }
    
    float		AirshipDamage;
	SexyVector2 InitialPositionOffset;
	float avatarTriggleRate;
};


#endif
