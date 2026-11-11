//
//  Plant_Peapod.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_PEAPOD_H__
#define __PLANT_PEAPOD_H__

#include "PlantFramework.h"

class PlantPeapod : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPeapod, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual float GetRefundSunAmount() override;
    virtual void UpdateActions() override;
	
	bool CanUpgrade(void);
	void Upgrade(void);
	void FireSelected(int i_faceId);

	virtual std::string GetFireSoundEvent() const override;

	int GetLevel() const { return m_level; }

private:
	int m_level;
    pvztime_t m_StartTime;
    pvztime_t m_UpgradeTime;
    bool m_bUpgradeFlag;
};

class PlantTypePeapod : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypePeapod, PlantType, RtClass) {}
	
	// Peapods can be planted on top of existing peapods, assuming there is room
	// void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
	bool CanPlantOnPlant(Plant* plant) const override;
	
};

namespace Message
{
	void PlantUpgraded(Plant* i_plant, int i_level);
}

#endif //__PLANT_PEAPOD_H__
