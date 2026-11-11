#ifndef __GridItemGravestoneZombieInCardGame_H__
#define __GridItemGravestoneZombieInCardGame_H__

#include <string>

#include "DamageInfo.h"
#include "GridItemGravestone.h"
#include "GravestoneAnimRig.h"
#include "PVZTypes.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "TimeMgr.h"

class GridItemCardGameGravestoneZombieDeathSpawner : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemCardGameGravestoneZombieDeathSpawner, GridItemGravestone, RtClass);
	
	GridItemCardGameGravestoneZombieDeathSpawner();
    void SetSpawnZombieType(ZombieTypePtr i_zombieTypePtr);

protected:
	virtual void registerForEvents() override;
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	
private:
	void OnZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
		
    int m_counter;
    ZombieTypePtr m_zombieType;
};


class GridItemCardGameGravestonePropertySheet : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemCardGameGravestonePropertySheet, GridItemAnimationProps, RtClass);

	ZombieTypePtr NormalZombie;
	ZombieTypePtr AdvanceZombie;
	int AdvanceTimes;
	float Cooldown;
};

class GridItemCardGameGravestoneZombieTimeSpawner : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemCardGameGravestoneZombieTimeSpawner, GridItemAnimation, RtClass);

	GridItemCardGameGravestoneZombieTimeSpawner();
    void SetSpawnZombieType(ZombieTypePtr i_zombieTypePtr);
	bool CanLevelUpGravestone();
	void LevelUpGravestone(int i_upLevel = 1);
	void SetTimeRate(float i_rate);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }

protected:
	virtual void registerForEvents() override;
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;

	void onAnimationDone(const std::string& i_tabel);
	
private:
	void onCardGameStaffChange(class CardGameGridItemStaff* i_staff);
	void spawnZombie();

	pvztime_t m_nextSpawnTimer;
    ZombieTypePtr m_zombieType;
	int m_levelUpTimes;
	float m_cooldownTime;
	float m_cooldownTimeRate;
	int m_advanceTimes;
};

// for zombie enemy gravestone spawner.
class GridItemCardGameGravestoneZombieTimeSpawnerEnemy : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemCardGameGravestoneZombieTimeSpawnerEnemy, GridItemAnimation, RtClass);

	GridItemCardGameGravestoneZombieTimeSpawnerEnemy();
    void SetSpawnZombieType(ZombieTypePtr i_zombieTypePtr);
	bool CanLevelUpGravestone();
	void LevelUpGravestone(int i_upLevel = 1);
	void SetTimeRate(float i_rate);
	void SetLevel(int level);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }

protected:
	virtual void registerForEvents() override;
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	
	void onAnimationDone(const std::string& i_tabel);

private:
	void onCardGameStaffChange(class CardGameGridItemStaff* i_staff);
	void spawnZombie();

	pvztime_t m_nextSpawnTimer;
    ZombieTypePtr m_zombieType;
	int m_levelUpTimes;
	float m_cooldownTime;
	float m_cooldownTimeRate;
	int m_advanceTimes;
	int m_level;
};


class CardGameGridItemStaff : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(CardGameGridItemStaff, GridItemAnimation, RtClass);

   	virtual void onGridItemInitialize() override;
	virtual void onDestroy() override;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }
protected:
	virtual void onUpdate() override;
    virtual void onKilled() override;

private:
	float m_timer;
};

namespace Message
{
	void CardGameStaffChange(class CardGameGridItemStaff* i_staff);
}

#endif
