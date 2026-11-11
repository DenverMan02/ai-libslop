/*
 * RandZombieModule.h
 *
 *  Created on: Feb 7, 2014
 *      Author: lijie
 */

#ifndef RANDZOMBIEMODULE_H_
#define RANDZOMBIEMODULE_H_

#include "LevelModule.h"
#include "Core.h"
#include "ZombieType.h"
#include "PVZTypes.h"
#include "WaveGeneratorModule.h"

typedef std::list<ZombieTypePtr> ZombieTypeList;
typedef std::map<ZombieTypePtr, uint32> ZombieLevelMap;

struct RandZombieInfo
{
	ZombieTypePtr Type;
	uint32 FirstWave;
	uint32 LastWave;
	uint32 Level;
    
    RandZombieInfo()
    {
        Level = 1;
    }
};

class RandZombieModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(RandZombieModule, LevelModule, RtClass);

	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:
	virtual void registerForEvents() override;
    
     virtual void onPostLoad() override;

private:
	void onLoadComplete();
	void onNewWave(int i_waveIndex, const WaveDefinition* i_currentDefinition);

	void AddRandZombie(int i_waveIndex, int i_totalCost);

	void SetupRandZombieLevel();

	ZombieLevelMap m_ZombieLevelMap;
};

class RandZombieProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RandZombieProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return RandZombieModule::StaticGetClass();
	}

	RandZombieProperties()
	{
		m_vecRandZombieInfoList.clear();
		m_vecZombielistPool.clear();
	}

	void SetupRandZombieList() const;

	std::vector<RandZombieInfo> m_vecRandZombieInfoList;
	mutable std::vector<ZombieTypeList> m_vecZombielistPool;
	//mutable ZombieLevelMap m_ZombieLevelMap;
};


#endif /* RANDZOMBIEMODULE_H_ */
