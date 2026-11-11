/*
 * HeianWindSystem.h
 *
 *  Created on: 2020-11-30
 *      Author: admin
 */

#ifndef HEIANWINDSYSTEM_H_
#define HEIANWINDSYSTEM_H_

#include "GameSubSystem.h"
#include "Core.h"
#include "Projectile.h"

struct HeianWindRecord
{
	HeianWindRecord()
    :AffectZombies(0)
    ,MoveDistance(0)
	,AffectRow(-1)
	,MoveTime(0)
	,FlickRate(0)
    {}

    int AffectZombies;
    float MoveDistance;
    int AffectRow;
    float MoveTime;
    float FlickRate;
};

struct PushZombieData
{
	PushZombieData()
	:TargetX(0)
	{}

	RtWeakPtr<class Zombie> Zombie;
	float TargetX;
};

class HeianTornadoProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(HeianTornadoProps, ProjectilePropertySheet, RtClass);

    HeianTornadoProps()
    {
    	AffectZombies = 0;
    	PushDistance = 260.0f;
    }

    int AffectZombies;
    float PushDistance;
};

class HeianTornado : public Projectile
{
public:
	RT_CLASS_DEFINE(HeianTornado, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	float SyncParameters();

protected:
	void onInitialized() override;
	void onProjectileInitialized() override;
	virtual void moveThroughTime(pvztime_t i_dt) override;

protected:
	void endPush();
	void endPush(RtWeakPtr<class Zombie> i_zombie, int i_index);
	bool searchGrids();

	std::vector<PushZombieData> m_pushedZombies;
	std::vector<RtWeakPtr<class Zombie>> m_completedZombies;
};

class HeianTornadoElite : public HeianTornado
{
public:
	RT_CLASS_DEFINE(HeianTornadoElite, HeianTornado, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class HeianWindSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(HeianWindSubsystem, GameSubSystem, RtClass);

    void Generate(HeianWindRecord i_record);
    void GenerateTornado(int i_row);
    void GenerateTornadoElite(int i_row);
    void GenerateTornadoNewPVP(int i_row);

protected:
    void onInitialized() override;
    void registerForEvents() override;

private:
    void playSmallWindEffect(int i_row, bool i_reverse);
    void playLargeWindEffect(bool i_reverse);
    Rect getRectByRow(int i_row);

    void findTargets(int i_row, std::vector<class BoardEntity*>& targets);
    void findTargets(std::vector<class BoardEntity*>& targets);
    bool CanBeControlled(Zombie* i_zombie);

    void tryFlickZombie(class Zombie* i_zombie);
    void moveZombie(class BoardEntity* i_impactedEntity, float i_distance, float i_time, float i_height, float i_flickRate);

};


#endif /* HEIANWINDSYSTEM_H_ */
