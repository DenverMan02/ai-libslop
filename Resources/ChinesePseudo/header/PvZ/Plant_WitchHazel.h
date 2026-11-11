//
//  Plant_WitchHazel.h
//  PlantsVersusZombies2
//
//  Created by Kobylarek, Alexander on 8/15/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_WitchHazel_h
#define Plant_WitchHazel_h

#include <string>
#include "BoardEntity.h"
#include "DamageInfo.h"
#include "GridItem.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"

class Projectile;
class Zombie;

class PlantWitchHazel : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantWitchHazel, PlantFramework, RtClass);
	
	void Initialize() override;
	void PostInitialize() override;
	void UpdateUnconditionally() override;
	void UpdateActions() override;
    void CancelPlantfood() override;
	bool CanApplyPlantfood() override;
    
    void RecoverMagicAnim();
    
	Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
	std::string GetFireSoundEvent() const override;
	GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon) override { return GridItemPtr(); }
	PlantTargetParams GetTargetParamsForWeapon(PlantWeapon i_plantWeapon) override;
	ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	ZombiePtr FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams, Rect i_attackRect) override;
	
	void ShowPersistentEffects(bool i_show) override;
	void OnRelocationBegun() override;
	void OnRelocationComplete() override;
    
private:
    
    void DoIntervalFixing();
    
	void spawnAttack(Zombie* i_target, int i_damage, std::string& i_animName, std::string& i_animLabel, PlantTypePtr i_transformationPlant, int i_transformationLevel);
	
	void updateMagicState();
	void updateMagicEffects(const std::string& i_effectName, const std::string& i_layerName, const SexyVector2& i_offset);
	
	bool zombieIsBlacklisted(const Zombie* i_zombie) const;
    
    ZombiePtr FindAnotherZombie(ZombiePtr zombie, PlantWeapon i_weapon);
	
	enum MagicState
	{
		MAGICSTATE_HIDE,
		MAGICSTATE_HIDDEN,
		MAGICSTATE_CHARGING,
		MAGICSTATE_IDLE
	};
	
	MagicState m_magicState;
	pvztime_t m_magicChargeTime;
	bool m_showPersistentMagic;
};

class WitchHazelProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(WitchHazelProps, PlantPropertySheet, RtClass);
	
	WitchHazelProps()
	{
		MagicOffset = { 0, 0 };
		DecayDelay = 0.5f;
		
		BasicTransformationType = "puffshroom";
		PlantfoodTransformationType = "toadstool";
		
		BasicTransformationLevel = -1;
		PlantfoodTransformationLevel = -1;
        
        TransformationUndamagedLevel = 2;
        TransformationUndamagedDuration = 3.f;
        
        MagicChargeDecLevel = 3;
        MagicChargeDecTime = 5.f;
        
        ComboLevel = 5;
        ComboRate = 0.3f;
        
        AvataredPlantfoodDamageInc = 500;
	}
	
	SexyVector2 MagicOffset;
	float DecayDelay;
	
	std::string BasicTransformationType;
	std::string PlantfoodTransformationType;
	
	int BasicTransformationLevel;
    int PlantfoodTransformationLevel;
    
    int TransformationUndamagedLevel;
    float TransformationUndamagedDuration;
    
    int MagicChargeDecLevel;
    float MagicChargeDecTime;
    
    int ComboLevel;
    float ComboRate;
    
    int AvataredPlantfoodDamageInc;
	
	std::vector<std::string> ZombieTransformationBlackList;
};

class PlantAnimRig_WitchHazel : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_WitchHazel, PlantAnimRig, RtClass);
	
	PlantAnimRig_WitchHazel() {};
	
protected:
	void onPopAnimInitialized() override;
};

#endif /* Plant_WitchHazel_h */
