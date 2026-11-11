//
//  Plant_Cactus.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/18/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Cactus__
#define __PlantsVersusZombies2__Plant_Cactus__

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"

class Zombie;

class PlantCactus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCactus, PlantFramework, RtClass);
	
	void					Initialize() override;
	void					UpdateActions() override;
	bool					CanApplyPlantfood() override;
    void			        CancelPlantfood() override;
	void					ApplyPlantfood() override;
	bool					FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	Projectile*				Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	BoardEntityHeight		GetEntityHeight() const override;
	
	SexyVector2				GetShadowOffset() override { return SexyVector2(2.0f, 8.0f); }
	
	void onDestroy() override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
private:
	enum State
	{
		STATE_COWER_IDLE = STATE_FRAMEWORK_BEGIN,
		STATE_COWER_ATTACK,
		STATE_LEVEL5
	};
	
	void onAnimStoppedCallback(const std::string& i_animName) override;
	
	bool shouldBeCowering();
	
	Rect calcRectForPlantPosition(Rect i_rangeRect);
	Rect getCowerRect();
	Rect getUncowerRect();
	Rect getSpikeRect();
	
	pvztime_t m_lastSpikeTime;
	bool m_hasBeenPlantfooded;
    int m_plantFoodShotAngle;
    int m_maxAngle;
    int m_DeltaAngle;
    pvztime_t m_nextPlantFoodShotTime;
    float m_plantFoodShotInterval;
    int m_roundIndex;
	float m_reShootRate;

};

class CactusProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(CactusProps, PlantPropertySheet, RtClass);
	
	CactusProps()
	{
		SpikeDamage = 10;
		SpikeCooldown = 0.5f;
		PFSpikeDamage =  10;
		PFSpikeCooldown = 0.5f;
        SilverBulletChance = 0.6;
		SmallCactusRate = 0.1f;
	}
	
	Rect DuckAndCoverRange;
	Rect StayDuckedRange;
	Rect SpikeRange;
	int SpikeDamage;
	pvztime_t SpikeCooldown;
	int PFSpikeDamage;
	pvztime_t PFSpikeCooldown;
    float SilverBulletChance;
	float SmallCactusRate;
	ZombieRestrictionSet ZombiesWhichDoNotCauseCower;
};

class PlantAnimRig_Cactus : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Cactus, PlantAnimRig, RtClass);
	
	PlantAnimRig_Cactus();
	
	bool PlayEnterCower();
	bool PlayExitCower();
	bool PlayCowerAttack();
	void PlayCowerIdle();
    void TurnPlantFoodEffectOn();
    
	void PlayPlantfood(PopAnimRig::AnimStoppedReflectionDelegate onStop);
    void PlayAvatarPlantfood(PopAnimRig::AnimStoppedReflectionDelegate onStop);
	void PlayPlantfoodUp(PopAnimRig::AnimStoppedReflectionDelegate onStop);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	void PlayLevel5Attack(PopAnimRig::AnimStoppedReflectionDelegate onStop);
	
private:
	void onCowerContinued();
	void onCowerEnded();
	
	std::string getIdleAnimationName() override;
	
	bool m_hasBeenPlantfooded;
};

class CactusProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CactusProjectile, Projectile, RtClass);
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
    void IncreaseInitialPierceChance();
    void SetConditionIndex(int index);
	
protected:
	void onProjectileInitialized() override;
	
private:
	float m_currentPierceChance;
    int m_conditionIndex;
	std::vector<BoardEntityPtr> m_targetsAlreadyHit;
};

class CactusProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(CactusProjectileProps, ProjectilePropertySheet, RtClass);
	
	CactusProjectileProps()
	{
		InitialPierceChance = 90;
		PierceChanceReductionPerHit = 10;
	}
    
    
	
	int InitialPierceChance;
	int PierceChanceReductionPerHit;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Cactus__) */
