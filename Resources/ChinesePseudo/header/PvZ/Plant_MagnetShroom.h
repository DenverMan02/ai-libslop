//
//  Plant_MagnetShroom.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/15/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_MagnetShroom__
#define __PlantsVersusZombies2__Plant_MagnetShroom__

#include "PlantFramework.h"
#include "MacroStateMachine.h"
#include "GameSubSystem.h"
#include "ZombieParticle.h"

STATE_ENUM_BASE_BEGIN(MagnetShroomState)
	MSS_Idle,
	MSS_Pulling,
	MSS_Holding,
	MSS_Plantfood,
STATE_ENUM_END(MagnetShroomState);

struct MagnetShroomPulledEntity
{
	MagnetShroomPulledEntity()
	{}
	MagnetShroomPulledEntity(BoardEntity* i_ent);
	
	RtWeakPtr<class BoardEntity> PulledEntity;
	SexyVector3 ImpartedVelocity;
};

class PlantAnimRig_Magnetshroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Magnetshroom, PlantAnimRig, RtClass);
	
	PlantAnimRig_Magnetshroom();
	
	bool PlayMagnetpull(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayMagnetCatch(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayMagnetHolding();
    bool PlayMagnetPlantfoodCollect();
    std::vector<std::string> GetMagnetLayers();
	
protected:
	void onPopAnimInitialized() override;
};

class PlantMagnetShroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMagnetShroom, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	bool CanEndPlantfood() override;
	void CancelPlantfood() override;
	
	Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	int GetPlantFoodPlayCount() override;

    void onKilled(bool i_instantKill) override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
	void DropAllPulledEntities();

	void NotifySetHidden(bool i_newValue, bool i_oldValue) override;
	
protected:
	DECLARE_FSM_HANDLER_BASE(MagnetShroomState);
	
protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	
private:
	void resetSearchTimer();
	bool canPullHelmType(HelmType) const;
	bool canPullHelmFrom(Zombie* i_zombie) const;
	bool canPullZombie(Zombie* i_zombie) const;
    bool canPullZombieHead(Zombie *i_zombie) const;
	void dropPulledEntity(MagnetShroomPulledEntity& i_pulledEntity);
	bool pullPulledEntity(MagnetShroomPulledEntity& i_pulledEntity, const SexyVector3& i_pullTarget, pvztime_t i_totalPullTime, float i_initialPullSpeed, float i_pullSpeedAcceleration);
	void throwPulledEntity(MagnetShroomPulledEntity& i_pulledEntity);
	void gatherValidTargets(Rect& i_targetingRect, bool i_gatherDroppedHelms, std::vector<BoardEntity*>& o_validTargets) const;
	void sortTargetList(std::vector<BoardEntity*>& io_targets) const;
    bool canThrowEntity(BoardEntity*i_pulledEntity);
    void doEntityOrbit(MagnetShroomPulledEntity& pulledEnt, int count);
    
	SexyVector3 calcPullTarget() const;
	
	class BoardEntity* tryPullHelmFrom(Zombie* i_zombie);
	class BoardEntity* tryPullZombie(Zombie* i_zombie);
    class BoardEntity* tryPullZombieHead(Zombie *i_zombie);
	class BoardEntity* tryPullZombieParticle(ZombieParticle* i_particle);
	class BoardEntity* tryPull(BoardEntity* i_target);
	
	pvztime_t m_nextTargetSearchTime;
	pvztime_t m_startThrowingTime;
	bool m_doneWithPlantfood;
	
	MagnetShroomPulledEntity m_pulledEntity;
	
	std::vector<MagnetShroomPulledEntity> m_plantfoodPulledEntities;
	
	pvztime_t m_stateStartTime;
	
	DECLARE_FSM_STATE_VALUE(MagnetShroomState);
};

// ------------

struct MagnetShroomSubSystemOwnershipRecord
{
public:
	MagnetShroomSubSystemOwnershipRecord();
	MagnetShroomSubSystemOwnershipRecord(class Plant* i_owningPlant);
	
	bool ContainsEntity(class BoardEntity* i_entity) const;
	void RemoveEntity(class BoardEntity* i_entity);

	RtWeakPtr<class Plant> OwningPlant;
	std::vector<RtWeakPtr<class BoardEntity> > OwnedEntities;
};

class MagnetShroomSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(MagnetShroomSubSystem, GameSubSystem, RtClass);
	
	void Update() override;
	
	bool IsEntityOwned(class BoardEntity* i_entity);
	void ClaimEntity(class Plant* i_owner, class BoardEntity* i_entity);
	void ReleaseEntity(class BoardEntity* i_entity);
	
private:
	int findIndexForEntity(class BoardEntity* i_entity) const;
	int findIndexForOwner(class Plant* i_owner) const;
	
	std::vector<MagnetShroomSubSystemOwnershipRecord> m_ownershipList;
};

#endif /* defined(__PlantsVersusZombies2__Plant_MagnetShroom__) */
