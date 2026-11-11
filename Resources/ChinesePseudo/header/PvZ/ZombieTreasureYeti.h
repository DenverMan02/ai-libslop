//
//  ZombieTreasureYeti.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/7/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieTreasureYeti__
#define __PlantsVersusZombies2__ZombieTreasureYeti__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieTreasureYetiState, ZombieState)
	ZS_TreasureYeti_WalkBackward,
STATE_ENUM_END(ZombieTreasureYetiState);

class ZombieTreasureYeti : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieTreasureYeti, Zombie, RtClass);
    
    virtual void DropAllLoot() override;
    
    virtual bool CanBeFlickedOff() const override
	{
		return false;
	}
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }
    
    virtual ~ZombieTreasureYeti();
    
protected:
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onLostHead() override;
	virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
	virtual ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;

private:
	OVERRIDE_STATE_ONENTER(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, WalkBackward);

	void onWalkContinued(const std::string&, const std::string&, int);
	void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);

	bool m_countdownStarted;
	pvztime_t m_countdown;
	int8	m_damageIndex;

	static int ms_yetiCount;
};

class TreasureYetiSchedulingProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(TreasureYetiSchedulingProps, PropertySheetBase, RtClass);
	
	TreasureYetiSchedulingProps()
	{
		MinimumMinutesBetweenYetis = -1;
		MaximumMinutesBetweenYetis = -1;
		MinimumMinutesBetweenYetisOnRetry = -1;
		MaximumMinutesBetweenYetisOnRetry = -1;
		MinimumMinutesBeforeYeti = 0;
	}

	int MinimumMinutesBetweenYetis;
	int MaximumMinutesBetweenYetis;
	int MinimumMinutesBetweenYetisOnRetry;
	int MaximumMinutesBetweenYetisOnRetry;

	std::string LatestYetiIntroLevel;
	std::string SoonestYetiIntroLevel;
	pvztime_t MinimumMinutesBeforeYeti;
};

class TreasureYetiBlacklistProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(TreasureYetiBlacklistProps, PropertySheetBase, RtClass);

	TreasureYetiBlacklistProps()
	{
	}

	std::vector<std::string> LevelBlacklist;
};

namespace TreasureYeti
{
	void SpawnOnMap(bool i_NoneTimes=false);
	void RemoveFromMap();
	void ScheduleNextYeti();
	void YetiEscaped();
	bool IsSpawned();
	void Update();
}

namespace Message
{
	void FirstTreasureYetiSpawned();
	void TreasureYetiSpawned();
	//PVZ2_CHINESE_START
    void TreasureYetiTutorialFailed();
	//PVZ2_CHINESE_END
	void TreasureYetiRemoved();
	void TreasureYetiDefeated();
}

#endif /* defined(__PlantsVersusZombies2__ZombieTreasureYeti__) */
