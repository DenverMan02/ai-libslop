//
//  Plant_Holonut.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Holonut_h
#define PlantsVersusZombies2_Plant_Holonut_h

#include "DamageInfo.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "TimeMgr.h"

class PlantHolonut : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHolonut, PlantFramework, RtClass);
	
	virtual void Initialize() override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool CanBeTargeted() override;
	virtual void UpdateActions() override;
	
	virtual DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
	virtual void		onDestroy() override;
	
	virtual void PlayChewedOnSound() override;
    void Idle() override;

    //bool OverrideProjectileCollision(class Projectile* pProjectile) override;
protected:
	bool isHiding() const;
	void setHiding(bool i_hiding);
    void ClearShield();
    float GetRegenerateTime();
	
private:
	void regenerateFromDeath();
	
	pvztime_t m_lastTookDamageTime;
	pvztime_t m_hideStartTime;
	int			m_regenerateAfterDeathCount;
};

namespace Message
{
	void HolonutWillDie();
}

#endif
