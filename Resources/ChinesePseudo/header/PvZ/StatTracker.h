#ifndef __STATTRACKER_H__
#define __STATTRACKER_H__

#include "Precompile.h"

class GameSnapshot
{
	int m_plantsAlive;
	int m_zombiesAlive;
	int m_sun;
	int m_plantFood;
};

class StatTracker
{

	public:

	int m_mouseClicks;
	int m_mouseClicksTimer;
	int m_mouseClicksTimerMax;
	int m_zombieDeaths;
	int m_zombieDeathsTimer;
	int m_zombieDeathsTimerMax;
	int m_plantDeaths;
	int m_plantDeathsTimer;
	int m_plantDeathsTimerMax;
	int m_plantPlanted;
	int m_plantPlantedTimer;
	int m_plantPlantedTimerMax;
	int m_gameSnapshotTimer;
	int m_gameSnapshotTimerMax;

	std::vector<int> m_mouseClickGraph;
	std::vector<int> m_zombieDeathGraph;
	std::vector<int> m_plantDeathGraph;
	std::vector<int> m_plantPlantedGraph;
	std::vector<GameSnapshot> m_gameSnapshotGraph;
	
	StatTracker();
	~StatTracker();

	void Update();
	void AddZombieDeath();
	void AddPlantDeath();
	void AddPlantPlanted();
	void AddClick();

};

#endif //__STATTRACKER_H__



