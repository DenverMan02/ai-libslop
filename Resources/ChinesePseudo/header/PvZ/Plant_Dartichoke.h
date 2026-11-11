//
//  Plant_Dartichoke
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/24/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __Plant_Dartichoke__
#define __Plant_Dartichoke__

#include "BoardEntity.h"
#include "ClassBucketFilter.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "Plant.h"
#include "RtObject.h"
#include "Zombie.h"
#include <string>
//#include "RtObject.h"

class DartichokeProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(DartichokeProps, PlantPropertySheet, RtClass);
	
	DartichokeProps()
	{
		ThistlePlantfoodUnaimedRepeatCount = 5;
		ThistleUnaimedOffsetStart = -8;
		ThistleAimedOffsetStart = -4;
		ThistleUnaimedSlotDegrees = 15;
        DartichokeNormalBoostChance = 0;
        DartichokeMaxAmmo = 2;
        DartichokeOutOfAmmoSadSeconds = 6;
        RestTimeRate1 = 0.75;
        RestTimeRate2 = 0.5;
        ThunderBoostCoolDown = 10.0f;
        CurrentCoolDownTime = 0.0f;

	}
	
	int ThistlePlantfoodUnaimedRepeatCount;
	int ThistleUnaimedOffsetStart;
	int ThistleAimedOffsetStart;
	int ThistleUnaimedSlotDegrees;
    
    float DartichokeNormalBoostChance;
    
    int DartichokeMaxAmmo;
    float DartichokeOutOfAmmoSadSeconds;
    float RestTimeRate1;
    float RestTimeRate2;
    float ThunderBoostCoolDown;
    float CurrentCoolDownTime;
    ClassBucketFilter MainTargetPriority;
    std::vector<std::string> DangerEnemyList;


    std::vector<ValueRange> PlantfoodStartOffset;
};

class PlantDartichoke : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantDartichoke, PlantFramework, RtClass);

    PlantDartichoke();

	Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

    void Initialize() override;
    void PostInitialize() override;
	void UpdateUnconditionally() override;
    void UpdateActions() override;
    void CancelExhausted() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	int	GetPlantFoodPlayCount() override;
	Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;

    BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override { return ENTITYTYPE_ZOMBIE; }

    std::vector<std::string>& GetDangerEnemyList(){return Pt_DangerEnemyList;}
    RtWeakPtr<class BoardEntity> FindDangerousTarget(PlantWeapon i_plantWeapon);
    std::string DangerEnemy;
protected:
    int calcZombieTargetWeight(Zombie* i_zombie, PlantTargetParams& i_targetParams) override;
    
private:
	ZombiePtr FindTargetZombie(Rect& i_rect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	class DartichokeLeaf* fireRotatedProjectile(PlantWeapon i_plantWeapon, int i_forwardSlotOffset);
    
    void fillAmmo();
    void updateAmmo();

	bool m_hasTarget;
	BoardEntityPtr m_target;
	int m_pfTargetIndex;
	int m_pfShotIndex;
	std::vector<RtWeakPtr<BoardEntity>> m_pfTargets;
    int m_currentAmmo;
    int m_plantfoodAmmoLeft;
    float m_mainAttackRefreshTime;
public:
    pvztime_t SkillCoolDown;
    pvztime_t CurrentTime;
    int currentPlantLev;
    std::vector<std::string> Pt_DangerEnemyList;
};

class PlantAnimRig_Dartichoke : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Dartichoke, PlantAnimRig, RtClass);

	PlantAnimRig_Dartichoke();
    
    void UpdateAmmo(int i_ammo, int i_ammoMax);
    void setPlant(PlantDartichoke* plant){m_plant = plant;};
    
    PlantDartichoke* m_plant;
private:

	std::string getPlantFoodOnAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override;
        
    const std::vector<std::string>& getFullAmmoLayerNames();
    const std::vector<std::string>& getHalfAmmoLayerNames();
    const std::vector<std::string>& getEmptyAmmoLayerNames();
    
    std::string getExhaustedOnAnimName() override;
    std::string getExhaustedAnimName() override;
    std::string getExhaustedOffAnimName() override;
    std::string getAttackAnimationName() override;

};

class DartichokeLeafProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(DartichokeLeafProps, ProjectilePropertySheet, RtClass);

	DartichokeLeafProps()
	: SuperClass {}
	, MaxRotationsPerSecond {1.0}
	, Lifetime {5.0}
	{
		Level5Damage = 1200;
	}

	float MaxRotationsPerSecond;
	float Lifetime;
	float Level5Damage;
};

class DartichokeLeaf : public Projectile
{
public:
	RT_CLASS_DEFINE(DartichokeLeaf, Projectile, RtClass);
	DartichokeLeaf();

	void SetOverrideTarget(BoardEntity* i_overrideTarget);
	void SetLevel5Projectile(bool isLevel5) { m_isLevel5 = isLevel5; }

protected:
	void onDeflection(class BoardEntity* i_deflector) override;
	void moveThroughTime(pvztime_t i_dt) override;
	bool handleImpact(BoardEntity* i_impactedEntity) override;
	void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const override;
	void KillSplashZombies();// lv5 bullet splash damage kill zombie
	bool CheckValidKillZombie(Zombie* zombie);// kill conditions
	void TakeLevel5Damage(BoardEntity* ptr);

	RtWeakPtr<BoardEntity> m_overrideTarget;
    bool m_firstRotation = true;
	bool m_deflected;
	float m_createTime;
	bool m_isLevel5;
};

#endif
