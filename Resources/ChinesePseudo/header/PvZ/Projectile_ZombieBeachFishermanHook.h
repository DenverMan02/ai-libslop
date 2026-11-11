//
//  Projectile_ZombieBeachFishermanHook.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 7/14/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Projectile_ZombieBeachFishermanHook__
#define __PlantsVersusZombies2__Projectile_ZombieBeachFishermanHook__

#include "Projectile.h"

typedef RtReflectionDelegate<Delegate0> HookLandedDelegate;
class FishHookProjectile : public Projectile
{
private:
	enum HookState
	{
		PVZ_BEGIN_ENUM(HOOKSTATE_),
		HOOKSTATE_IDLE,
		HOOKSTATE_CASTING,
		HOOKSTATE_REELING,
		HOOKSTATE_BOUNCING,
		PVZ_END_ENUM(HOOKSTATE_),
	};
	
public:
	RT_CLASS_DEFINE(FishHookProjectile, Projectile, RtClass);
	
	void CastHook(const float i_timePerSquare, HookLandedDelegate i_onHookLanded);
	void ReelHook(const float i_timePerSquare, const pvztime_t i_length, SexyVector2 i_pos, HookLandedDelegate i_onHookLanded);
	
	bool IsBouncing() { return HOOKSTATE_BOUNCING == m_state; } 
	bool OnCollideEntity(BoardEntity* i_entity) override;
	PlantGroupPtr GetHookedPlantGroup();
	PlantPtr GetHookedPlant() { return m_hookedPlant.empty() ? PlantPtr() : m_hookedPlant[0]; }
	
protected:
	void onUpdate(pvztime_t i_dt) override;
	void onDestroy() override;
	
private:
	
	SexyVector3 getAttachmentPosition(PlantPtr i_plant);
	
	HookState m_state;
	
	pvztime_t m_motionStartTime;
	pvztime_t m_motionEndTime;
	SexyVector3 m_motionStartPos;
	SexyVector3 m_motionEndPos;
	HookLandedDelegate m_onHookLandedDelegate;
	std::vector<PlantPtr> m_hookedPlant;
};

class FishHookProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(FishHookProjectileProps, ProjectilePropertySheet, RtClass);
	
	FishHookProjectileProps()
	{
		// Do nothing.
	}
};

#endif /* defined(__PlantsVersusZombies2__Projectile_ZombieBeachFishermanHook__) */
