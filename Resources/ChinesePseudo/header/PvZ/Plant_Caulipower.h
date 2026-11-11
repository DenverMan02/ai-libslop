//
//  Plant_Caulipower.h
//  PlantsVersusZombies2
//
//  Created by Greg Silva on 1/3/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Caulipower_h
#define PlantsVersusZombies2_Plant_Caulipower_h

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "GridItem.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"

class Zombie;

class PlantTypeCaulipower : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeCaulipower, PlantType, RtClass);
	const std::string& getAvatarPlantFoodLayer() const;
private:
	std::string AvatarPlantFoodLayer;
};

class PlantCaulipower : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCaulipower, PlantFramework, RtClass);

	void Initialize() override;
	void PostInitialize() override;
	
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void DoPlantfoodAttack();
	Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	ZombiePtr FindTargetZombie();

	DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
	
	PlantTargetParams GetTargetParamsForWeapon(PlantWeapon i_plantWeapon) override;
	BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override { return ENTITYTYPE_ZOMBIE; }
	bool HasShadow()  override { return false; }

	bool CheckLv5SkillTriggle();
	void ClearLv5SkillTriggle();

protected:
	enum CaulipowerWeapon
	{
		WEAPON_LV5 = WEAPON_SECONDARY,
	};

private:
	std::vector<int> ZombieTargetWeights;
	std::vector<BoardEntityPtr> PlantfoodTargetedZombies;
	
	bool m_bLevel5Triggled;

	bool ZombieIsBlacklisted(Zombie* zombie);
};

class CaulipowerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(CaulipowerProps, PlantPropertySheet, RtClass);
	
	CaulipowerProps()
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

	float GetPacketCoolDownTime(int iStarLv) const override;
};

class PlantAnimRig_Caulipower : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Caulipower, PlantAnimRig, RtClass);

	PlantAnimRig_Caulipower():m_plant(NULL), m_bLevel5Triggled(false){ }

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

class CaulipowerProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CaulipowerProjectile, Projectile, RtClass);

	void moveThroughTime(pvztime_t i_dt) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void SetTargetZombie(ZombiePtr i_targetZombie);
	void SetTargetZombie(Zombie* i_targetZombie);
	void MakePositionAdjustment();
	void SetPlantLevel(int level);
	int GetPlantLevel() const;
private:
	float calcDesiredRotation(SexyVector3 i_toTarget);
	void ChangeZombieTeam(Zombie* i_zombie) const;
	ZombiePtr m_targetZombie;
	int m_nPlantLevel;
};

class CaulipowerProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(CaulipowerProjectileProps, ProjectilePropertySheet, RtClass);
	
	bool HealsOnHypnosis;
	SexyVector2 InitialPositionOffset;
	float SpecialDamage;
};

#endif
