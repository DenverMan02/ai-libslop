//
//  Zombie_Ra_Subsystem.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_RA_SUBSYSTEM_H__
#define __ZOMBIE_RA_SUBSYSTEM_H__

#include <vector>

#include "GameSubSystem.h"
#include "PVZTypes.h"
#include "RtDb.h"
#include "TimeMgr.h"

class CollectableSun;
class Zombie;
class ZombieRa;
namespace Sexy {
class SexyVector3;
}  // namespace Sexy

struct SunOwnerLink
{
	RtWeakPtr<BoardEntity>		Owner;
	RtWeakPtr<CollectableSun>	Sun;
	SunCurrency					SunValue;
	pvztime_t           		TimeGrabbed;
};

enum ValidOwnerType
{
	SUN_OWNER_None,
	SUN_OWNER_RaZombie,
	SUN_OWNER_CrystalSkull,
	SUN_OWNER_SunGun,
	SUN_OWNER_SolarTruck
};

class ZombieRaSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombieRaSubSystem, GameSubSystem, RtClass);
	
	// override functions from GameSubSystem
    void Update() override;
	virtual void AssociateWithSubSystem(RtWeakPtr<BoardEntity> i_object);
	

protected:
	void registerForEvents() override;

	/// Private implementation
private:
	void onZombieDestroyed(Zombie* i_zombie);
	void onPlantDied(Plant* i_plant);
	void eraseOwner(BoardEntity* i_owner);
	
	void				clearCollections();
    void				addSunLink(RtWeakPtr<CollectableSun> i_sun, RtWeakPtr<BoardEntity> i_ownerID, int i_sunValue);
	SunOwnerLink*		getSunLink(RtWeakPtr<CollectableSun> i_sun);
	void				incrementSunlinkTimers();
	const SunOwnerLink* getSunOwnerLink(RtWeakPtr<CollectableSun> i_sun);
	void				uncaptureSun(CollectableSun* sun);
	void				removeSunLink(RtWeakPtr<CollectableSun> i_sun);
	void				moveSunTowardCaptor(CollectableSun* sun, const SunOwnerLink* sunlink, RtWeakPtr<BoardEntity> claimingOwner);
	void				captureSun(CollectableSun* sun);
	RtWeakPtr<BoardEntity> findNearest(const SexyVector3& sunPosition);
	ValidOwnerType		calcOwnerType(RtWeakPtr<BoardEntity> i_owner);
    
	std::vector<RtWeakPtr<BoardEntity> > 	m_Owners;
	std::vector<SunOwnerLink>			m_sunLinks;
};

#endif // __ZOMBIE_RA_SUBSYSTEM_H__
