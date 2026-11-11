//
//  Plant_SunGun.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/19/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_SunGun__
#define __PlantsVersusZombies2__Plant_SunGun__

#include "GameSubSystem.h"
#include "MacroStateMachine.h"
#include "Plant_MagnetShroom.h"
#include "PlantFramework.h"

STATE_ENUM_BASE_BEGIN(SunGunState)
SGS_Planting,
SGS_Collecting,
SGS_Firing,
SGS_Dying,
STATE_ENUM_END(SunGunState);

class PlantSunGun : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSunGun, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	bool CanApplyPlantfood() override { return false; }
	bool IsInvincible() const override { return true; }
	bool CanBeTargeted() override { return false; }
	bool CanBeShoveled() override { return false; }
	void TakeSmashAttack(ZombiePtr i_srcZombie) override {}
	
	void IncrementSunsCollected(const int i_sunCurrency);
	void IncrementSunsClaimed(const int i_sunCurrency);
	void DecrementSunsClaimed(const int i_sunCurrency);
	bool CanClaimSun();
	
protected:
	DECLARE_FSM_HANDLER_BASE(SunGunState);
	
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	
private:
	DECLARE_FSM_STATE_VALUE(SunGunState);
	
	int m_sunsClaimed;
	int m_sunCurrencyClaimed;
	int m_sunCurrencyCollected;
	
	std::vector<MagnetShroomPulledEntity> m_pulledEntities;
};

class PlantAnimRig_SunGun : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_SunGun, PlantAnimRig, RtClass);
	
	PlantAnimRig_SunGun();
	
	bool PlayGunPlanted(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayGunCollecting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayGunFiring(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayGunDying(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	std::string GetPlantingAnimName() const { return "plantfood_on"; }
	std::string GetCollectingAnimName() const { return "plantfood_collection"; }
	std::string GetFiringAnimName() const { return "plantfood"; }
	std::string GetDyingAnimName() const { return "plantfood_off"; }
	
protected:
	void onPopAnimInitialized() override;
};

inline void PlantSunGun::IncrementSunsCollected(const int i_sunCurrency)
{
	m_sunCurrencyCollected += i_sunCurrency;
}

#endif /* defined(__PlantsVersusZombies2__Plant_SunGun__) */
