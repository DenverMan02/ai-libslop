/*
 * 	GridItemZombieTent.h
 *  2022-2-8
 */

#ifndef _GRIDITEM_ZOMBIETENT_H_
#define _GRIDITEM_ZOMBIETENT_H_

#include "GravestoneAnimRig.h"
#include "GridItemGravestone.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "GameSubSystem.h"


class TentZombieWeights : public BasicZombieWeights
{
public:
	RT_CLASS_DEFINE(TentZombieWeights, BasicZombieWeights, RtClass);

	TentZombieWeights()
	{
		Level = 1;
	}

	int Level;
};

class GridItemZombieTentProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemZombieTentProps, GridItemGravestonePropertySheet, RtClass);
	ValueRange TimeBetweenSpawns = { 10.0f, 12.0f };
	std::vector<TentZombieWeights> ZombieTypesToSpawn;
	int ZombieSpawnPointOffset = -80;
	float ProductInterval = 5.0f;
};

class GridItemZombieTent : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemZombieTent, GridItemGravestone, RtClass);

	void CalcDamageState();
	int	CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const override;
	pvztime_t GetNextSpawnTime() { return m_nextSpawnTime; }
	void SetNextSpawnTime(pvztime_t i_nextSpawnTime) { m_nextSpawnTime = i_nextSpawnTime; }
	void KillGridItem() override;

	bool ShouldBlockLevelCompletion() const override { return true; }

	void SetTentLevel(int level);
	void setValues(float i_hitpoints, float i_productionInterval, std::vector<TentZombieWeights> i_zombieTypesToSpawn);

protected:
	void onTakeDamage(const DamageInfo& i_damage) override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onPlaceOnBoard() override;

private:
	void onDestroyAnimCompleted();
	std::string pickBasicZombie();
	int getZombieLevelInitial(std::string i_zombieTypeName);
	pvztime_t m_nextSpawnTime = PVZ_EOT();
	bool m_hasPlayedDeathAnim = false;
	std::vector<TentZombieWeights> m_zombieTypesToSpawn;
	float m_productionInterval;
};

struct TentZombieTranStruct
{
	std::string Before;
	std::string After;
};

class GridItemFestivalZombieTentProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemFestivalZombieTentProps, GridItemGravestonePropertySheet, RtClass);
	ValueRange TimeBetweenSpawns = { 10.0f, 12.0f };
	std::vector<TentZombieWeights> ZombieTypesToSpawn;
	int ZombieSpawnPointOffset = -80;
	float ProductInterval = 5.0f;

	std::vector<TentZombieTranStruct> ZombieTransform;
	std::string ZombieSpawnOnDestory;
};

class GridItemFestivalZombieTent : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemFestivalZombieTent, GridItemGravestone, RtClass);

	void CalcDamageState();
	int	CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const override;
	pvztime_t GetNextSpawnTime() { return m_nextSpawnTime; }
	void SetNextSpawnTime(pvztime_t i_nextSpawnTime) { m_nextSpawnTime = i_nextSpawnTime; }
	void KillGridItem() override;

	bool ShouldBlockLevelCompletion() const override { return true; }

	void SetTentLevel(int level);
	void setValues(float i_hitpoints, float i_productionInterval, std::vector<TentZombieWeights> i_zombieTypesToSpawn);

protected:
	void onTakeDamage(const DamageInfo& i_damage) override;
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onPlaceOnBoard() override;

private:
	void onDestroyAnimCompleted();
	std::string pickBasicZombie();
	int getZombieLevelInitial(std::string i_zombieTypeName);

	void SpawnZombie(ZombieTypePtr i_zombieType);

	pvztime_t m_nextSpawnTime = PVZ_EOT();
	bool m_hasPlayedDeathAnim = false;
	std::vector<TentZombieWeights> m_zombieTypesToSpawn;
	float m_productionInterval;
};

class ZombieTentAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieTentAnimRig, GravestoneAnimRig, RtClass);

	ZombieTentAnimRig();

	void PlayStationary();
	void PlayDestroy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void SetDamageState(int i_damageState, bool i_isAnimated) override;
	void onAnimStopped() override;

private:
	bool m_inIntroAnim;
	bool m_isDying;
};


struct WalkingOutZombie
{
	SexyVector3 startPos;
	pvztime_t 	totalTime;
	pvztime_t	startTime;

	float 		oldScale;
	Color 		oldPamColor;

	float 		startScale;

	RtWeakPtr<class Zombie> zombie;
};

class ZombieWalkOutSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombieWalkOutSubSystem, GameSubSystem, RtClass);

	ZombieWalkOutSubSystem();

	void OutZombie(Zombie* i_zombie, SexyVector3 i_startPos, float i_totalTIme);

	void Update() override;

	std::vector<WalkingOutZombie> m_walkingOutZombies;
	std::vector<WalkingOutZombie> m_newWalkingOutZombies;
	std::vector<RtWeakPtr<class Zombie>> m_deadZombies;

	float m_scaleValue;
};


#endif /* _GRIDITEM_ZOMBIETENT_H_ */
