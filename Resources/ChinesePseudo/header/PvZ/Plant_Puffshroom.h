//
//  Plant_Puffshroom.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 8/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PLANT_PUFFSHROOM_H__
#define __PLANT_PUFFSHROOM_H__

#include "GridItem.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "TimeMgr.h"

class Zombie;

namespace Message
{
	void PuffshroomGotPlantfood(const Point& i_sourceGridLocation);
}

class PlantPuffshroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPuffshroom, PlantFramework, RtClass);
	
	PlantPuffshroom();
	virtual ~PlantPuffshroom();
	
	void			Initialize() override;
	bool			CanApplyPlantfood() override;
	void			ApplyPlantfood() override;
	void			UpdatePlantfood() override;
	void			CancelPlantfood() override;
	void			UpdateActions() override;
	bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    Projectile*	    Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	bool			IsInvincible() const override;

    Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	
	void			NotifySetHidden(bool i_newValue, bool i_oldValue) override;
	bool			IsVanishing() const;
    
protected:
	void			onAnimStoppedCallback(const std::string&) override;
	void			onPlantDecayPaused();
	void			onPlantDecayResumed();
	
private:
	void onPuffshroomGotPlantfood(const Point& i_sourceGridLocation);
	void triggerPlantfoodFromColony();
	void doPlantfoodEffect();
	
	void updateDecay();
	bool canStateChange();
	bool hasNoExpiration();
	bool isPlantDecayPaused();
	bool decayStageHasEnded(const int i_decayStage);
	void onVanished(const std::string& i_animName);
    bool shouldPlantDecayBePaused();
	pvztime_t getExpireTime();
	
	std::vector<pvztime_t> m_futurePlantfoodFromColony;
	PeashooterPlantfood m_plantfood;
	bool m_usePlantfoodShine;
	pvztime_t m_decayStartTime;
	pvztime_t m_decayPauseStartTime;
	int m_decayStage;
};

#endif //__PLANT_PUFFSHROOM_H__
