//
//  Plant_Vacuumshroom.h
//  PlantsVersusZombies2
//
//  Created by Scott Eberline on 10/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef _PLANT_VACUUM_SHROOM_H_
#define _PLANT_VACUUM_SHROOM_H_

#include "Plant_Wallnut.h"


enum VacuumState
{
	VACUUMSTATE_VACUUMING = STATE_FRAMEWORK_BEGIN,
	VACUUMSTATE_COOLDOWN
};


class PlantVacuumshroom : public PlantWallnut
{
public:
	RT_CLASS_DEFINE(PlantVacuumshroom, PlantWallnut, RtClass);

    virtual void				Initialize() override;
	virtual void				UpdateActions() override;

private:
	void						transitionToState(uint i_plantState);

	void						scanZombiesToVacuumIfTime();
	void						scanZombiesToVacuum();
	void						filterZombiesToVacuum();
	void						vacuumZombies();
    void						vacuumZombie(Zombie* i_zombie);

	void						calcNextZombieScanTime();
	void						calcCooldownEndTime();
	void						calcVacuumArea();

	bool						hasZombieToVacuum() const;
	bool						isCooldownEnded() const;

	static bool					isGameplayEnded();
	static bool					canVacuumZombie(BoardEntity* i_entity);

	//	transient member variables

	std::vector<BoardEntity*>	m_zombiesToVacuum;
	Rect						m_vacuumArea;

	//	persistent member variables

	pvztime_t					m_nextZombieScanTime;
	pvztime_t					m_cooldownEndTime;
};


#endif  // !defined(_PLANT_VACUUM_SHROOM_H_)
