#ifndef __PLANTFOOD_CAPTURE_SUBSYSTEM_H__
#define __PLANTFOOD_CAPTURE_SUBSYSTEM_H__

#include <vector>
#include "GameSubSystem.h"
#include "PVZTypes.h"
#include "RtDb.h"
#include "TimeMgr.h"
#include "BoardEntity.h"
#include "CollectablePlantfood.h"

class Zombie;

struct PlantfoodOwnerLink
{
	RtWeakPtr<BoardEntity>		        Owner;
	RtWeakPtr<CollectablePlantfood>	    Plantfood;
	pvztime_t           		        TimeGrabbed;
};

enum PlantfoodCaptureOwnerType
{
	PLANTFOOD_OWNER_None,
	PLANTFOOD_OWNER_AkinndoZombie,
};

class PlantfoodCaptureSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantfoodCaptureSubSystem, GameSubSystem, RtClass);
	
	// override functions from GameSubSystem
    void Update() override;
	virtual void AssociateWithSubSystem(RtWeakPtr<BoardEntity> i_object);
	
protected:
	void registerForEvents() override;

	/// Private implementation
private:
	void onZombieDestroyed(Zombie* i_zombie);

	void eraseOwner(BoardEntity* i_owner);
	
	void				        clearCollections();
    void				        addPlantfoodLink(RtWeakPtr<CollectablePlantfood> i_plantfood, RtWeakPtr<BoardEntity> i_ownerID);
	void				        removePlantfoodLink(RtWeakPtr<CollectablePlantfood> i_plantfood);
	PlantfoodOwnerLink*		    getPlantfoodLink(RtWeakPtr<CollectablePlantfood> i_plantfood);
	void				        incrementPlantfoodlinkTimers();
	const PlantfoodOwnerLink*   getPlantfoodOwnerLink(RtWeakPtr<CollectablePlantfood> i_plantfood);
	void				        capturePlantfood(CollectablePlantfood* i_plantfood);
	void				        uncapturePlantfood(CollectablePlantfood* i_plantfood);
	void				        movePlantfoodTowardCaptor(CollectablePlantfood* i_plantfood, const PlantfoodOwnerLink* plantfoodlink, RtWeakPtr<BoardEntity> claimingOwner);
	RtWeakPtr<BoardEntity>      findNearest(const SexyVector3& plantfoodPosition);
	PlantfoodCaptureOwnerType	calcOwnerType(RtWeakPtr<BoardEntity> i_owner);
    
	std::vector<RtWeakPtr<BoardEntity> > 	m_owners;
	std::vector<PlantfoodOwnerLink>			m_plantfoodLinks;
};

#endif // __ZOMBIE_RA_SUBSYSTEM_H__
