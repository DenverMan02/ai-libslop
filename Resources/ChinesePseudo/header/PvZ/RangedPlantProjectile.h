//
//  RangedPlantProjectile.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 8/23/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __RANGED_PLANT_PROJECTILE_H__
#define __RANGED_PLANT_PROJECTILE_H__

#include "PlatformAutodetect.h"
#include "Projectile.h"
#include "RtObject.h"
#include "TimeMgr.h"

class BoardEntity;

class RangedPlantProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(RangedPlantProjectile, Projectile, RtClass);
	
protected:
	RangedPlantProjectile();
	
	virtual void onSetInstigator(BoardEntity* i_instigator) override;
	virtual void moveThroughTime(pvztime_t i_dt) override;
	virtual void onPostUpdate() override;
	
private:
	int32 m_projectileRange;
	float m_traveledDistance;
};

#endif // __RANGED_PLANT_PROJECTILE_H__
