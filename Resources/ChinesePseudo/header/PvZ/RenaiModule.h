/*
 * RenaiModule.h
 *
 *  Created on: 2019-7-24
 *      Author: Administrator
 */

#ifndef RENAIMODULE_H_
#define RENAIMODULE_H_

#include "LevelModule.h"
#include "MTRand.h"
#include "Precompile.h"
#include <vector>
#include "VictoryOutro.h"

typedef RtWeakPtr<class GridItemRenaiRoller> GridItemRenaiRollerPtr;
typedef RtWeakPtr<class GridItemRenaiTile> GridItemRenaiTilePtr;

enum EnvironmentState
{
	EState_None = -1,
	EState_Day,
	EState_DayTo_Night,
	EState_Night
};

class RenaiModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(RenaiModule, LevelModule, RtClass);

	RenaiModule();
	virtual ~RenaiModule();

	void SetState(EnvironmentState i_state);
	EnvironmentState GetState() { return m_currrentState; }
	void CheatStopRollers();

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;

	virtual void initializeModule() override;
	void onLoadComplete();
	void gameplayStarted();
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

private:
	void ExecuteRenaiEvents();
	void onZombieSpawned(class Zombie * i_zombie);
	void onTileStateChanged(bool i_pushed);
	void onRollerDestroyed(class GridItemRenaiRoller* i_roller);
	void DayIntoNight();
	void onShowNightWarning();
	void onShowNightWarningSet();
	void onShowNightWarningReady();
	void onEnterFade();
	void onSwitchToNight();
	void TrySwitchToNight();
	void onFadedFinishedCallback(class StandaloneEffect* i_effect);
	int getDiffTileValue();
	void MoveRollers(bool i_left, int i_level);
	void StopRollers();
	void SetupStatues();
	void SetupNightStatues();
	void SetupNightEffects();

	EnvironmentState m_currrentState;
	std::vector<GridItemRenaiRollerPtr> m_rollerList;
	std::vector<GridItemRenaiTilePtr> m_tileList;
};

class RenaiModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RenaiModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return RenaiModule::StaticGetClass();
	}

	struct StatueInfo
	{
		StatueInfo()
		{
			GridX = 0;
			GridY = 0;
			WaveNumber = 0;
			TypeName = "";
		}

		int GridX;
		int GridY;
		int WaveNumber;
		std::string TypeName;
	};

	RenaiModuleProperties()
	{
		NightStartWaveNum = -1;
	}

	std::vector<StatueInfo> StatueInfos;
	std::vector<StatueInfo> StatueNightInfos;
    int NightStartWaveNum;
};

class RenaiVictoryOutroModule : public VictoryOutroModule
{
public:
    RT_CLASS_DEFINE(RenaiVictoryOutroModule, VictoryOutroModule, RtClass);

protected:
    void giveCustomRewards() override;
};

class RenaiVictoryOutroProperties : public VictoryOutroProperties
{
public:
    RT_CLASS_DEFINE(RenaiVictoryOutroProperties, VictoryOutroProperties, RtClass);

	RtClass* GetModuleClass() const override
    {
        return RenaiVictoryOutroModule::StaticGetClass();
    }
};

namespace Message
{
	void ExecuteRenaiEvents();
}

#endif /* RENAIMODULE_H_ */
