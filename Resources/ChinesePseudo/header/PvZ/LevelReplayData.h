//
//  LevelReplayData.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/3/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelReplayData__
#define __PlantsVersusZombies2__LevelReplayData__

#include "GameSubSystem.h"
#include "LevelScoringSubsystem.h"
#include "JoustDataPackets.h"

struct LevelReplayEvent
{
public:
	enum EventType
	{
		LEVEL_REPLAY_EVENT_TIME_DELTA,
		LEVEL_REPLAY_EVENT_SCORE,
		LEVEL_REPLAY_EVENT_MULTIPLIER,
		LEVEL_REPLAY_EVENT_GENERATED_SCORE_RATIO,
	};
	
	const std::string ToString();
	
public:
	std::string convertEventTypeToDebugString(EventType i_eventType);
	
	EventType Event;
	float Data;
	
};

class LevelReplayData
{
public:
	static int GetDataVersion();
	static bool IsBinaryValid(const Buffer* inputBuffer);
	
public:
	void Init(const std::string& i_levelName, uint64 i_randomSeed) { m_levelName = i_levelName; m_randomSeed = i_randomSeed; }
	void Clear();

	void AddEvent(LevelReplayEvent::EventType i_eventType, float i_data, const std::string& i_cheatLog);
	
	pvztime_t CalculateNextTimeDelta(int i_startIndex);

	bool HasData() const { return m_events.size() > 0; }
	int GetEventCount() const { return (int) m_events.size(); }
	const LevelReplayEvent& GetEvent(int i_index) const { return m_events[i_index]; }
	const LevelReplayEvent* GetLastEvent(LevelReplayEvent::EventType i_type);
	
	void ExportToBinary(Buffer* outputBuffer);
	bool ImportFromBinary(const Buffer* inputBuffer);
	
	bool operator==(const LevelReplayData& other);

	SexyString ToString();
	
public:	// do not directly access - this is public for reflection

	std::vector<LevelReplayEvent>	m_events;
	std::string						m_levelName;
	uint64							m_randomSeed;
	JoustPlayerLoadoutData			m_plantLoadout;
};

#endif
