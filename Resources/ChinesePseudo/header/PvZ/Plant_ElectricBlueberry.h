//
//  Plant_ElectricBlueberry.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_ElectricBlueberry_h
#define PlantsVersusZombies2_Plant_ElectricBlueberry_h

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "GridItem.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "LightningCloud.h"

class Projectile;
class Zombie;

class PlantElectricBlueberry : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantElectricBlueberry, PlantFramework, RtClass) {}

	void Initialize() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	bool CanApplyPlantfood() override;
	void CancelPlantfood() override;
    Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
//    ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;

	std::string GetFireSoundEvent() const override;
	
    PlantTargetParams GetTargetParamsForWeapon(PlantWeapon i_plantWeapon) override;
    BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override { return ENTITYTYPE_ZOMBIE; }
    void Idle() override;
	BoardEntity* createCloud(PlantWeapon i_plantWeapon);
protected:
	void onAnimStoppedCallback(const std::string& i_anim) override;

private:
	bool TriggerSuperAttack();

};

class ElectricBlueberryProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricBlueberryProps, PlantPropertySheet, RtClass);
	
	ElectricBlueberryProps()
	{
		PlantFoodLightningTargets = 3;
		PlantFoodCloudSpeed = 15.0f;
		PlantFoodLightningBoltDamage = 20.0f;
		PlantFoodAttackCooldown = 2.0f;
		
		NormalLightningTargets = 1;
		NormalCloudSpeed = 15.0f;
		NormalLightningBoltDamage = 20.0f;
		NormalAttackCooldown = 2.0f;

		WeightTargetNormalZombie = 1;
		WeightTargetGargantuarZombie = 1;
		WeightTargetOtherZombie = 1;
        
        AvatarZoomInTime = 10;
        SuperRate = 0.0f;
	}
	
	// number of targets for plantfood
	int   PlantFoodLightningTargets;
	float PlantFoodCloudSpeed;
	float PlantFoodLightningBoltDamage;
	float PlantFoodAttackCooldown;
	
	// number of targets for plantfood
	int   NormalLightningTargets;
	float NormalCloudSpeed;
	float NormalLightningBoltDamage;
	float NormalAttackCooldown;
	
	int WeightTargetNormalZombie;
	int WeightTargetGargantuarZombie;
	int WeightTargetOtherZombie;
 
    float AvatarZoomInTime;
    float SuperRate;
};

class PlantAnimRig_ElectricBlueberry : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ElectricBlueberry, PlantAnimRig, RtClass);
	
	std::string getCyclingAnimName() override;
	
	bool PlayPreviewAnim(bool bHideLayer) override { return PlayAndContinue(getPreviewAnimName()); }

	std::string getPreviewAnimName();
	
	void onAnimStopped() override;
protected:
    std::string getPlantFoodMainAnimName() override;
};

class BlueberryZapCloud : public CloudBase
{
public:
    RT_CLASS_DEFINE(BlueberryZapCloud, CloudBase, RtClass);
    
    BlueberryZapCloud();
    
    void SetZombieWeights(float i_normalZombie, float i_gargantuarZombie,  float i_otherZombie);
    void SetAvatar(bool avatar);
    void SetMinifyDuration(float time);
    void Spawn();
    void SetSuper(bool i_super);
    void SetAnim(bool i_super);
    
protected:
    virtual bool WillTarget(BoardEntity* entity) override;
    virtual void onInitialized() override;
    virtual void onUpdateCloud() override;
    virtual void onStateChanged(uint i_state) override;
    virtual void onAttack(BoardEntity* target) override;
    virtual void onNoTargetRemaining() override;
    virtual void onSpawnAnimDone(const std::string &i_animName);
    
    virtual BoardEntity* pickPreferredTarget(std::vector<BoardEntity*> i_zombies, std::vector<BoardEntity*> i_gridItems) override;
    
    virtual DamageTypeFlags getDamageTypeFlags() override { return DAMAGE_LIGHTNING | DAMAGE_FROM_PLANTFOOD_EFFECT; }
    
    virtual void onDraw(Graphics* i_g) override;
    
private:
    pvztime_t m_finishTime;
    bool m_canMove;
    bool m_avatar;
    float m_minifyDuration;
    void onDieFinished(const std::string &i_animName);
    void onAttackFinished(const std::string &i_animName);
    void MarkCenterTarget(BoardEntity* i_entity);
    void DoSplashDamage(int i_sourceCol, int i_sourceRow);
    
    std::vector<int> ZombieTargetWeights;
    std::vector<BoardEntityPtr> m_hitTarget;
    bool m_super;
};

#endif
