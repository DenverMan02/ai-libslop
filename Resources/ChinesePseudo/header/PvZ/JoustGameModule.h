//
//  JoustGameModule.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/29/2017.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_JoustGameModule_h
#define PlantsVersusZombies2_JoustGameModule_h

#include <vector>

#include "Core.h"
#include "LevelModule.h"
#include "BoardEnums.h"

#include "UIWidget.h"

struct PlantPowerData
{
	PlantPowerData()
	{
		Rare = 0;
		Level = 1;
		HasAvatar = false;
	}
	int Rare;
	int Level;
	bool HasAvatar;
};

class JoustGameModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(JoustGameModule, LevelModule, RtClass);
	
	JoustGameModule()
	: m_useLevelTimer(false)
	, m_levelTime(0)
	, m_peakZombieLevel(0)
	, m_cheatDetected(false)
	, m_waitingForLastStand(false)
	{}
	void	AddTime(pvztime_t i_time);
	void	CheatLoseLevel();
	void	CheatWinLevel(float i_scoreOverage);
	void	ForfeitLevel();
	time_t	GetMaxLevelTime();
	bool	CheatsUsed() { return m_cheatDetected; }
	const std::vector<PlantPowerData> &GetPlantPowerData() { return m_powerDatas; }
	int CalcTotalPlantPower();
	
protected:
	virtual ~JoustGameModule();

	void	initializeModule() override;
	void	registerForEvents() override;
	void	postInitialize() override;

private:

	class AdaptorJoustPlayMeterHUD* m_hotUIHUD;
	
	void onLastStandInit();
	void onLastStandStart();
	
	void onSeedChooserFinalized();
	void onGameplayStarted();
	void onGameplayEnded();
	void onGameplayUpdate();
	
	void playCountdownSound(int i_soundIndex);
	
	void onScoreUpdated(int score, float i_bonusMultiplier);
	void onReplayScoreUpdated(int score, float i_bonusMultiplier);
	
	void hideCoinBank();

	void initLevelTimer();
	void endLevel();
	
	void reportToSlack();
	
	void addToUIRenderQueue(class RenderQueue* i_queue);
	void drawJoustMeter(class Graphics* i_g);

	void savePlantPowerData();
	bool preventSave();

	bool	m_useLevelTimer;
	pvztime_t m_levelTime;
	int		m_peakZombieLevel;
	bool	m_cheatDetected;
	bool	m_waitingForLastStand;
	
	float	m_nextFinalCountdownSecond;
	std::vector<PlantPowerData> m_powerDatas;
};

class JoustGameModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(JoustGameModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return JoustGameModule::StaticGetClass();
	}

	JoustGameModuleProperties()
	{
		TimeLimit = 0.0f;
	}
	
	float	TimeLimit;
	
};

#endif
