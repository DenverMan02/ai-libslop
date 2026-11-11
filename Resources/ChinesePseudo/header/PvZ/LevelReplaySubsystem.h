//
//  LevelReplaySubsystem.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/2/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelReplaySubsystem__
#define __PlantsVersusZombies2__LevelReplaySubsystem__

#include "GameSubSystem.h"
#include "LevelReplayData.h"
#include "LevelScoringSubsystem.h"

namespace Message
{
	void ReplayScoreUpdated(int i_score, float i_bonusMultiplier);
}

class LevelRecordingBaseSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(LevelRecordingBaseSubsystem, GameSubSystem, RtClass);
	
	LevelRecordingBaseSubsystem();
	
public:
	LevelScoringSubsystem* getScoringSystem();

protected:
	virtual void start() {}
	virtual void stop() {}
	
private:
	void onLevelLoadComplete();
	void onLastStandInit();
	void onLastStandStart();
	void onGameplayStarted();
	void onGameplayEnded();
	
	bool m_waitingForLastStand;
};

class LevelRecordSubsystem : public LevelRecordingBaseSubsystem
{
public:
	RT_CLASS_DEFINE(LevelRecordSubsystem, LevelRecordingBaseSubsystem, RtClass);
	
	LevelRecordSubsystem();
	
	void Update() override;
	
	void StopRecording();
	
	void ExportToBinary(Buffer* outputBuffer) { m_data.ExportToBinary(outputBuffer); }
	bool ImportFromBinary(Buffer* inputBuffer) { return m_data.ImportFromBinary(inputBuffer); }
	void Clear() { m_data.Clear(); }
	
	bool operator==(const LevelRecordSubsystem& other) { return m_data == other.m_data; }

protected:
	void start() override;
	void stop() override;
	
private:
	
	void updateRecording();
	bool recordEvents();
	bool readyForNextEvent();
	void updateTimeForEvent();
	
	void cachePlantLoadout();
	
	pvztime_t m_lastEventTime;
	pvztime_t m_nextEventDelta;
	int m_lastScore;
	float m_lastMultiplier;
	
	bool m_recording;

	LevelReplayData m_data;
};

class LevelReplaySubsystem : public LevelRecordingBaseSubsystem
{
public:
	RT_CLASS_DEFINE(LevelReplaySubsystem, LevelRecordingBaseSubsystem, RtClass);

	LevelReplaySubsystem();

	void Update() override;
	bool IsPlaying() { return m_playing; }
	
	void Init();
	virtual void Clear() {}
	
	int GetCurrentScore() { return m_currentScore; }
	void CheatSetCurrentScore(int i_newScore) { setCurrentScore(i_newScore); }
	virtual int GetFinalScore() { return 0; }
	
	virtual bool HasPlantLoadout() { return false; }
	virtual const JoustPlayerLoadoutData* GetPlantLoadout() { return nullptr; }

	void SetForcedStopDuration(time_t i_forcedStopDuration) { m_forcedStopDuration = i_forcedStopDuration; }
	
protected:

	void start() override;
	void stop() override;
	
	virtual void processNextEvents(bool i_includeTimeDelta) {};
	virtual void loadReplay() {};
	virtual bool hasData() { return false; }
	virtual pvztime_t calculateNextTimeDelta() { return PVZ_EOT(); }

	void setCurrentScore( int i_score ) { m_currentScore = i_score; broadcastChanges(); }
	void setCurrentMultiplier( int i_multiplier ) { m_currentMultiplier = i_multiplier; broadcastChanges(); }
	void setIsPlaying( bool i_playing ) { m_playing = i_playing; }
	void updateNextDelta();
	time_t getCurrentTime() { return PVZ_T() - m_startTime; }

private:

	void broadcastChanges();
	
	pvztime_t m_startTime;
	pvztime_t m_lastEventTime;
	pvztime_t m_nextEventTime;
	pvztime_t m_forcedStopDuration;
	
	bool m_playing;
	
	int m_currentScore;
	int m_currentMultiplier;
};

class DataDrivenLevelReplaySubsystem : public LevelReplaySubsystem
{
public:
	RT_CLASS_DEFINE(DataDrivenLevelReplaySubsystem, LevelReplaySubsystem, RtClass);

	DataDrivenLevelReplaySubsystem() : LevelReplaySubsystem() {}

	int GetFinalScore() override;
	void Clear() override { m_data.Clear(); }

	bool HasPlantLoadout() override { return m_data.m_plantLoadout.Plants.size() > 0; }
	const JoustPlayerLoadoutData* GetPlantLoadout() override { return &m_data.m_plantLoadout; }

protected:
	
	void start() override;
	
	bool hasData() override { return m_data.HasData(); }
	pvztime_t calculateNextTimeDelta() override;
	void processNextEvents(bool i_includeTimeDelta) override;

	virtual void generateNextScore(float i_ratio) { DBG_ASSERT(false); }

	LevelReplayData m_data;
	
private:
	
	int m_lastConsumedEventIndex;
	
};

class SavedLevelReplaySubsystem : public DataDrivenLevelReplaySubsystem
{
public:
	RT_CLASS_DEFINE(SavedLevelReplaySubsystem, DataDrivenLevelReplaySubsystem, RtClass);
	
	SavedLevelReplaySubsystem() : DataDrivenLevelReplaySubsystem() {}
	
protected:
	void loadReplay() override;

};

class GeneratedLevelReplaySubsystem : public DataDrivenLevelReplaySubsystem
{
public:
	enum ReplayGeneratorDifficulty
	{
		REPLAY_GENERATOR_EASY,
		REPLAY_GENERATOR_NORMAL
	};
	
	RT_CLASS_DEFINE(GeneratedLevelReplaySubsystem, DataDrivenLevelReplaySubsystem, RtClass);
	
	GeneratedLevelReplaySubsystem() : DataDrivenLevelReplaySubsystem() { m_generatorDifficulty = REPLAY_GENERATOR_NORMAL; }
	
	void SetDifficulty(ReplayGeneratorDifficulty i_difficulty) { m_generatorDifficulty = i_difficulty; }
	int GetFinalScore() override { return GetCurrentScore(); }
	
protected:
	void loadReplay() override;
	
private:
	
	void generateNextScore(float i_ratio) override;
	float calcRatio(float i_base, float i_varianceMin, float i_varianceMax);
	void generateReplayLinearEarlyPeak();
	int calcCurrentMinScore();

	JoustPlayerData i_playerData;
	int	m_minScore;
	ReplayGeneratorDifficulty m_generatorDifficulty;
};

#endif
