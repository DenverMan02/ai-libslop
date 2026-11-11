/*
 * Plant_Electricitea_Subsystem.h
 *
 *  Created on: 2019-10-10
 *      Author: Administrator
 */

#ifndef PLANT_ELECTRICITEA_SUBSYSTEM_H_
#define PLANT_ELECTRICITEA_SUBSYSTEM_H_

#include "Plant_Electricitea.h"
#include "GameSubSystem.h"
#include "RtDb.h"
#include "RtObject.h"

class Zombie;

struct SparkingZombieTracker
{
public:
	ZombiePtr Zombie;
	SexyVector3 RootPosition;
	pvztime_t BurstTime;
	float ResistancePiercing;
	ElectriciteaBurstProperties Props;
};

class PlantElectriciteaSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantElectriciteaSubSystem, GameSubSystem, RtClass);

	void Update() override;
	bool CanZombieBurst(Zombie* i_zombie) const;
	void StartZombieBurst(Zombie* i_zombie, ElectriciteaBurstProperties i_props);
	void EndZombieBurst(Zombie* i_zombie);

protected:
	void fireZombieBurst(const SparkingZombieTracker& i_trackerToFire);
	void propagateZombieBurst(const SparkingZombieTracker& i_trackerToPropagate);
	std::vector<BoardEntityPtr> findTargets(SexyVector3 i_origin, int i_numTargets, int i_range, std::vector<BoardEntityPtr> i_targetsToExclude);
	bool isValidTarget(BoardEntity* i_target) const;

private:
	std::vector<SparkingZombieTracker> m_sparkingZombies;
	PlantPtr m_owner;
};


#endif /* PLANT_ELECTRICITEA_SUBSYSTEM_H_ */
