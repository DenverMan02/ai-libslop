//
//  Plant_Chilibean_SubSystem.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/21/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_CHILIBEAN_SUBSYSTEM_H__
#define __PLANT_CHILIBEAN_SUBSYSTEM_H__

#include "TimeMgr.h"
#include "PvZ2IDs.h"
#include "GameSubSystem.h"
#include "GameEventMgr.h"
#include "Zombie.h"

enum ZombieFlatulenceState
{
	PVZ_BEGIN_ENUM(ZFLATULENCE_),
	ZFLATULENCE_Sick,
	ZFLATULENCE_Stunning,
	ZFLATULENCE_Done,
	PVZ_END_ENUM(ZFLATULENCE_)
};

class ZombieFlatulence
{
public:
	ZombieFlatulence()
	: StartTime(0.0f)
	, StunDuration(0.0f)
	, State(ZFLATULENCE_Invalid)
    , Advanced(false)
	{}

	RtWeakPtr<class Plant> Plant;
	ZombiePtr Zombie;
	pvztime_t StartTime;
	pvztime_t StunDuration;
	ZombieFlatulenceState State;
    bool Advanced;
};

class PlantChilibeanSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantChilibeanSubSystem, GameSubSystem, RtClass);

 	virtual void Update() override;
	bool IsZombieAffectedByGas(Zombie* i_zombie);
	void CauseZombieFlatulence(Plant* i_plant, Zombie* i_zombie, pvztime_t i_stunDuration, float i_damage);
    void RemoveZombieFlatulence(Zombie* i_zombie);
	
	void SpawnGasCloudOverZombie(Zombie* i_zombie, pvztime_t i_cloudDuration, bool advanced);
    void ApplyGasEffectToArea(const Sexy::Rect& i_area, pvztime_t i_stunDuration, const std::vector<int>& i_rowRestrictions, bool advanced);
    void ApplyGasEffectToZombie(Zombie* i_zombie, pvztime_t i_stunDuration, bool advanced);
protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;

private:
	void StartFlatulenceEffect(Zombie* i_zombie, pvztime_t i_stunDuration, bool advanced);
    
 	std::vector<ZombieFlatulence> m_zombieStates;
    
    float                         m_DamageAmount = 0.0f;
};

#pragma mark
class Effect_ChilibeanGasCloud : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_ChilibeanGasCloud, Effect_PopAnim, RtClass);
    
    void StartCloud(Zombie* i_zombie, pvztime_t i_cloudDuration);
    
protected:
    void onUpdate() override;
    
private:
    RtWeakPtr<Zombie> m_targetZombie;
};

#endif // __PLANT_CHILIBEAN_SUBSYSTEM_H__
