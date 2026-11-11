//
//  Plant_ShadowShroom.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 11/9/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_ShadowShroom__
#define __PlantsVersusZombies2__Plant_ShadowShroom__

#include "AnimRigLayerSet.h"
#include "DamageInfo.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "PlantAnimRig.h"
#include "RtObject.h"
#include "ZombieEnums.h"
#include "GameSubSystem.h"

struct ZombiePushInfo
{
	ZombiePushInfo()
    {
		StartPosition = 1.0f;
		IsFinished = false;
    }

    RtWeakPtr<class Zombie> Zombie;
    float StartPosition;
    bool IsFinished;
};

class PlantShadowShroomSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantShadowShroomSubSystem, GameSubSystem, RtClass);

	PlantShadowShroomSubSystem();
	~PlantShadowShroomSubSystem() override;

 	virtual void Update() override;

 	void MarkZombie(Zombie* zombie, float i_startPosition);
 	void FinishZombie(Zombie* zombie);

protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;

private:
	std::vector<ZombiePushInfo> m_zombiePushVector;
	int m_range;
	void PushZombieAway(const ZombiePushInfo& i_info);
	void onZombieNudgeEnd(Zombie* zombie);
};

class PlantShadowShroom : public PlantFramework
{
public:
	static const std::string k_boostedOffLayerSetName;
	static const std::string k_boostedOnLayerSetName;
	
public:
	RT_CLASS_DEFINE(PlantShadowShroom, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateUnconditionally() override;
	bool CanApplyPlantfood() override;
	DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	virtual void onKilled(bool i_instantKill) override;
	
private:
	bool isZombieBlacklisted(Zombie* i_zombie);
	bool isBoosted();
	void playSplatEffect();
	void poisonZombie(Zombie* i_zombie);
	void pushZombieAway(Zombie* i_zombie);
};

class ShadowShroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ShadowShroomProps, PlantPropertySheet, RtClass);
	
	ShadowShroomProps()
	{
		PoisonDPS = 100.f;
		PoisonDuration = 10.f;
		AvatarPoisonDPS = 60.0f;
		AvatarPoisonDuration = 60.0f;
		PushBackRate = 0.5f;
		ImprovedPushBackBonus = 1.0f;
		PushBackRange = 1;
	}
	
	float PoisonDPS;
	float PoisonDuration;
	float AvatarPoisonDPS;
	float AvatarPoisonDuration;
	std::vector<std::string> CannotBePoisoned;
	float PushBackRate;
	float ImprovedPushBackBonus;
	int PushBackRange;
};

class PlantAnimRig_ShadowShroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ShadowShroom, PlantAnimRig, RtClass);
	
	void AddBoostedLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowBoostedLayerSet(std::string setName);
	
	bool PlayZenGardenIdleAnim() override;
	bool PlayPreviewAnim(bool bHideLayer = false) override;
    
    void PopAnimPlaySample(const std::string& i_sampleName, int i_pan, double i_volume, double i_numSteps) override;
	
protected:
	void onPopAnimInitialized() override;
	
private:
	AnimRigLayerSet m_boostedLayerSet;
};

#endif /* defined(__PlantsVersusZombies2__Plant_ShadowShroom__) */
