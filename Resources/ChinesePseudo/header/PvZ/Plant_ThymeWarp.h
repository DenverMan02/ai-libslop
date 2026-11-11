//
//  Plant_ThymeWarp.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PLANT_THYMEWARP_H__
#define __PLANT_THYMEWARP_H__

#include <string>

#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ZombieEnums.h"

class PlantThymeWarp : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantThymeWarp, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;
	void onAnimStoppedCallback(const std::string& i_anim) override;
	
	bool HasShadow()            override { return false; }
	bool CanBeShoveled()		override { return false; }
	bool CanBeTargeted()		override { return false; }
	bool IsInvincible() const override { return true; }
	void TakeSmashAttack(ZombiePtr i_srcZombie) override {}

private:	
	enum State
	{
		STATE_WARPING_OUT = STATE_FRAMEWORK_BEGIN,
		STATE_ZOMBIES_GONE,
		STATE_WARPING_IN,
	};
	
	bool		shouldStartDance();
	bool		shouldWarpZombiesOut();
	bool		shouldDisapearZombies();
	bool		shouldWarpZombiesIn();

	void		startDancing();
	void		startWarpingZombiesOut();
	void		startDisapearingZombies();
	void		startWarpingZombiesIn();
	
	void		findTargetsForWarp();
	bool		shouldDoStuffTo(RtWeakPtr<Zombie> zombie);

	void		warpZombieOut(RtWeakPtr<Zombie> zombie);
	void        disapearZombie(RtWeakPtr<Zombie> zombie);
	void        reapearZombie(RtWeakPtr<Zombie> zombie);
	void        warpZombieIn(RtWeakPtr<Zombie> zombie);
	
	void		healZombie(RtWeakPtr<Zombie> zombie);
	void		placeZombieInNewPosition(RtWeakPtr<Zombie> zombie);

	void		createWarpingOutEffectAt(RtWeakPtr<Zombie> zombie);
	void		createWarpingInEffectAt(RtWeakPtr<Zombie> zombie);
	void		createWarpingEffectAt(RtWeakPtr<Zombie> zombie, std::string animationName);
    
    void        quickKillZombie(RtWeakPtr<Zombie> zombie);
    void        createQuickKillEffectAt(RtWeakPtr<Zombie> zombie, std::string animationName);
	std::string	getWarpingEffectNameFor(RtWeakPtr<Zombie> zombie);

	std::vector<RtWeakPtr<Zombie>>		m_warpingZombies;
    std::vector<RtWeakPtr<Zombie>>		m_quickKillZombies;
	
	float								m_timeToStartWarpOut;
	float								m_timeToStartDisapearing;
	float								m_timeToStartWarpIn;
    float								m_timeToQuickKill;
    bool                                m_quickKillEnabled;
};

class ThymeWarpProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ThymeWarpProps, PlantPropertySheet, RtClass);
	
	ThymeWarpProps()
	: TimeBeforeWarpStart(0.0f)
	, TimeOfWarpOut(0.0f)
	, TimeZombieIsGone(0.0f)
	, TimeOfWarpIn(0.0f)
    , TransferZombieCount(5)
    , Lv3Delta(1)
    , KillZombieChance(0.6)
	{}
	
	float TimeBeforeWarpStart;
	float TimeOfWarpOut;
	float TimeZombieIsGone;
	float TimeOfWarpIn;
    int   TransferZombieCount;
    int   Lv3Delta;
    float KillZombieChance;
	std::vector<ZombieConditions> ConditionsRemovedByWarping;
};

#endif
