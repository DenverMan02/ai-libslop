//
//  Plant_Rotoshroom.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 9/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PLANT_ROTOSHROOM_H__
#define __PLANT_ROTOSHROOM_H__

#include "GridItem.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "SexyAppBase.h"
#include "SexyVector.h"

class Zombie;
struct PlantAction;

class PlantRotoshroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantRotoshroom, PlantFramework, RtClass);
	
	PlantRotoshroom();
	
	virtual void			Initialize();
	
	// Plant Food
	virtual bool			CanApplyPlantfood();
	virtual void			ApplyPlantfood();
	virtual void			UpdatePlantfood();
	virtual void			CancelPlantfood();
	
	// Firing
	virtual SexyVector3		GetFireOriginOffset(const PlantAction& i_action, float i_plantScale);
    
    virtual Projectile*     Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon);
	virtual ZombiePtr		FindTargetZombie(PlantWeapon i_plantWeapon, bool i_findClosest);
	virtual GridItemPtr		FindTargetDamageableGridItem(int i_col, int i_row, PlantWeapon i_plantWeapon);
	
protected:
	virtual void			registerForEvents();
	virtual void			unregisterForEvents();
	
private:
	bool					onTouchEvent(const Sexy::Touch& i_touch);
	float					getNearestCardinalRotation(float i_rotation);
	
	PeashooterPlantfood m_plantfood;
	float m_rotation;
	
	// Not Serialized
	Sexy::TouchID	m_touchIdent;
	float			m_touchStartWorldX;
	float			m_touchStartWorldY;
};

#endif //__PLANT_ROTOSHROOM_H__
