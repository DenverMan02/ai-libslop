//
//  GridItemEightiesArcadeCabinet.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 8/12/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemEightiesArcadeCabinet__
#define __PlantsVersusZombies2__GridItemEightiesArcadeCabinet__

#include <stdio.h>

#include "RtDb.h"
#include "RtObject.h"
#include "GridItemJammable.h"
#include "ZombieEightiesBasic.h"

class GridItemEightiesArcadeCabinetProps : public GridItemBreakableTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemEightiesArcadeCabinetProps, GridItemBreakableTargetProps, RtClass);
	
	GridItemEightiesArcadeCabinetProps()
		: JamStyle("jam_8bit")
		, ZombieSpawnPointOffset(-80)
		, PauseAfterZombieCreationWhereCabinetDoesNotMove(1.0f)
	{
		TimeBetweenSpawns = { 10.0f, 12.0f };
		InitialPause = { 1.0f, 2.0f };
		ZombieTypesToSpawn.clear();
	}
	
	virtual ~GridItemEightiesArcadeCabinetProps() {}
	
	std::string JamStyle;
	ValueRange TimeBetweenSpawns;
	ValueRange InitialPause;
	float PauseAfterZombieCreationWhereCabinetDoesNotMove;
	float ZombieSpawnPointOffset;
	std::vector<BasicZombieWeights> ZombieTypesToSpawn;

};

enum CabinetState
{
	PVZ_BEGIN_ENUM(CABINETSTATE_),
	CABINETSTATE_RISING,
	CABINETSTATE_IDLE,
	CABINETSTATE_STARTUP,
	CABINETSTATE_PLAYING,
	CABINETSTATE_SHUTDOWN,
	PVZ_END_ENUM(CABINETSTATE_)
};

// TODO: the below is a stub value until we have an actual animation to run
const int kEightiesArcadeCabinetAnimationDuration = 2.0f;

class GridItemEightiesArcadeCabinet : public GridItemJammable
{
public:
	RT_CLASS_DEFINE(GridItemEightiesArcadeCabinet, GridItemJammable, RtClass);
	
	GridItemEightiesArcadeCabinet();
	
	bool		CanBeTargetedBy(const BoardEntity* i_entity) const override						{ return true; }
	bool		IsDamageableByPlants() const override
				{ return true; }
	void		onGridItemInitialize() override;
	
	void setState(CabinetState i_state);
	CabinetState getState();
	void updateState();
	void onUpdate() override;
	
	// be jammin
	void StartJamming() override;
	void StopJamming() override;
	bool IsJamming() override;
	
	bool CanPushMe();
	void SetRiseFromGround();
	
protected:
	bool shouldCreateZombie();
	void createZombie();
	std::string pick8BitZombie();
	void setRiseHeight(float i_arbitraryHeightLerpValue);
	EntityComponent_GroundEffect m_groundEffect;
	
private:
	CabinetState m_state;
	pvztime_t m_animRunDuration;
	pvztime_t m_cooldownEndTime;
	pvztime_t m_zombieCooldownStartTime;
	float m_risingTime;
};

class GridItemEightiesArcadeCabinetAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemEightiesArcadeCabinetAnimRig, PopAnimRig, RtClass);
	
	void PlayIdle();
	void PlayStartGame(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayVideoGameLoop();
	void PlayEndGame(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

#endif /* defined(__PlantsVersusZombies2__GridItemEightiesArcadeCabinet__) */
