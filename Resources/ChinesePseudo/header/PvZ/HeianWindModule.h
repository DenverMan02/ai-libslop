/*
 * HeianWindModule.h
 *
 *  Created on: 2020-11-30
 *      Author: admin
 */

#ifndef HEIANWINDMODULE_H_
#define HEIANWINDMODULE_H_

//#include "LevelModule.h"
#include "MTRand.h"
//#include "Precompile.h"
#include <vector>
#include "VictoryOutro.h"

enum HeianWindState
{
	HeianWindNone,
	HeianWindFirstWave,
	HeianWindSecondWave
};

struct WindInfo
{
	WindInfo()
	:Row(-1)
	,AffectZombies(0)
	,Distance(0)
	,MoveTime(0)
	{

	}

	int Row;
	int AffectZombies;
	float Distance;
	float MoveTime;
};

struct WaveWindInfo
{
	WaveWindInfo()
	:WaveNumber(-1)
	,WindDelay(0)
	,StartDelay(0)
	{

	}

	int WaveNumber;
	float WindDelay;
	std::vector<WindInfo> WindInfos;
	float StartDelay;
};

class HeianWindModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(HeianWindModule, LevelModule, RtClass);

	HeianWindModule();
	virtual ~HeianWindModule();

	void SetState(HeianWindState i_state);
	HeianWindState GetState() { return m_currentWindState; }

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;

	virtual void initializeModule() override;
	void onLoadComplete();
	void gameplayStarted();
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

private:
	void onZombieSpawned(class Zombie * i_zombie);
	const WaveWindInfo& FindWaveWindInfo(int i_waveNumber);
	void setupWinds(const WaveWindInfo& i_info);
	void onUpdate();
	void updateStates();
	void SendWarning();
	void onShowWindWarning();

	std::vector<WindInfo> m_currentWinds;
	float m_currentDelay;
	HeianWindState m_currentWindState;
	pvztime_t m_nextWind;
	std::vector<int> m_windRows;
	float m_startTime;
};

class HeianWindModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(HeianWindModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return HeianWindModule::StaticGetClass();
	}

	HeianWindModuleProperties()
	{

	}

	std::vector<WaveWindInfo> WaveWindInfos;
};


#endif /* HEIANWINDMODULE_H_ */
