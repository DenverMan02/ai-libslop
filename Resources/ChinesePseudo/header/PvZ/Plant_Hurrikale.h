//
//  Plant_Hurrikale.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 10/28/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Hurrikale__
#define __PlantsVersusZombies2__Plant_Hurrikale__

#include <string>

#include "PlantFramework.h"
#include "PlantPropertySheet.h"

class HurrikaleProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HurrikaleProps, PlantPropertySheet, RtClass);
	
	HurrikaleProps()
	: FlyingZombieBlowingSpeed{100.f}
	, FlyingZombieUpAccelerationFactor{0.f}
	, GroundZombieBlowingSpeed{1.f}
	, BlowDuration{1.f}
	, ChillDuration{3.f}
	{}
	
	float FlyingZombieBlowingSpeed;
	float FlyingZombieUpAccelerationFactor;
	float GroundZombieBlowingSpeed;
	float BlowDuration;
	float ChillDuration;
};

class PlantHurrikale : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHurrikale, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
	bool IsInvincible() const override { return true; }
	bool CanBeShoveled()		override { return false; }
	bool CanBeTargeted()		override { return false; }
	void TakeSmashAttack(ZombiePtr i_srcZombie)	override {}
	
protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	
private:
	void startBlowing();
	void stopBlowing();
	void blowZombies();
	void createCloudEffect();
	bool canBeMovedByHurrikale(const Zombie* i_zombie) const;
	bool canBeChilledByHurrikale(const Zombie* i_zombie) const;
	void nudgeZombie(Zombie* i_zombie, float i_destinationX, float i_speed);
	
	pvztime_t m_blowStartTime;
	bool m_isBlowing = false;
};

namespace Message
{
    void HurrikaleWind(int iRow);
}

#endif /* defined(__PlantsVersusZombies2__Plant_Hurrikale__) */
