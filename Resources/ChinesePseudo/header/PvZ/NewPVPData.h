/*
 * NewPVPData.h
 *
 *  Created on: 2022-10-8
 *      Author: admin
 */

#ifndef NEWPVPDATA_H_
#define NEWPVPDATA_H_

#include "GameSubSystem.h"
#include "TimeMgr.h"
#include "NewPVPDataPackets.h"

struct NewPVPGameEventPositionData
{
	enum PositionType
	{
		POSITION_TYPE_GRID,
		POSITION_TYPE_PIXEL
	};

	NewPVPGameEventPositionData()
	: Type(POSITION_TYPE_GRID)
	, X(0)
	, Y(0)
	{

	}

	NewPVPGameEventPositionData(PositionType i_type, float i_x, float i_y)
	: Type(i_type)
	, X(i_x)
	, Y(i_y)
	{

	}

	PositionType Type;
	float X;
	float Y;
};

struct NewPVPGameEvent
{
public:
	enum EventType
	{
		GAME_EVENT_ADD_PLANT,
		GAME_EVENT_UPGRADE_PLANT,
		GAME_EVENT_REMOVE_PLANT,
		GAME_EVENT_PLANT_DIED,
		GAME_EVENT_ADD_ZOMBIE,
		GAME_EVENT_UPGRADE_ZOMBIE,
		GAME_EVENT_USE_ZOMBIE_SKILL,
		GAME_EVENT_USE_PLANTFOOD,
		GAME_EVENT_SURRENDER,
		GAME_EVENT_OFFLINE,
		GAME_EVENT_REACH_LINE,
		GAME_EVENT_END_TURN
	};

	NewPVPGameEvent(int i_id, EventType i_event, int i_type, int i_x, int i_y, float i_value, uint32 i_seed, float i_time, const std::vector<float>& i_extraValues)
	: Event(i_event)
	, Type(i_type)
	, PositionData(NewPVPGameEventPositionData(NewPVPGameEventPositionData::POSITION_TYPE_GRID, i_x, i_y))
	, Value(i_value)
	, Seed(i_seed)
	, ElapsedTime(i_time)
	, Id(i_id)
	, ExtraValues(i_extraValues)
	{

	}

	NewPVPGameEvent(int i_id, EventType i_event, int i_type, float i_x, float i_y, float i_value, uint32 i_seed, float i_time, const std::vector<float>& i_extraValues)
	: Event(i_event)
	, Type(i_type)
	, PositionData(NewPVPGameEventPositionData(NewPVPGameEventPositionData::POSITION_TYPE_PIXEL, i_x, i_y))
	, Value(i_value)
	, Seed(i_seed)
	, ElapsedTime(i_time)
	, Id(i_id)
	, ExtraValues(i_extraValues)
	{

	}

	NewPVPGameEvent()
	: Event(GAME_EVENT_ADD_PLANT)
	, Type(-1)
	, Value(0)
	, Seed(0)
	, ElapsedTime(0)
	, Id(0)
	{

	}

public:

	EventType Event;
	int Type;
	NewPVPGameEventPositionData PositionData;
	float Value;
	uint32 Seed;
	int Id;
	std::vector<float> ExtraValues;

	float ElapsedTime;
};

struct NewPVPPlayerPlantData
{
	NewPVPPlayerPlantData() { Type = 0; Level = 0; Imitater = false; }
	NewPVPPlayerPlantData(int i_type, int i_level) { Type = i_type; Level = i_level; Imitater = false; }
	NewPVPPlayerPlantData(int i_type, int i_level, bool i_imitater) { Type = i_type; Level = i_level; Imitater = i_imitater; }

	int Type;
	int Level;
	bool Imitater;
};

struct NewPVPPlayerPlants
{
	std::vector<NewPVPPlayerPlantData> Plants;
};

class NewPVPGameData : public RtObject
{
public:
	RT_CLASS_DEFINE(NewPVPGameData, RtObject, RtClass);
	NewPVPGameData();

	void Init();
	void Clear();
	void SortEvents();

	void AddEvent(int i_id, NewPVPGameEvent::EventType i_eventType, float i_time, int i_type = -1, int i_x = -1, int i_y = -1, float i_value = 0, uint32 i_seed = 0, const std::vector<float>& i_extraValues = {});
	void AddEvent(int i_id, NewPVPGameEvent::EventType i_eventType, float i_time, int i_type = -1, float i_x = 0, float i_y = 0, float i_value = 0, uint32 i_seed = 0, const std::vector<float>& i_extraValues = {});
	void RemoveEvent(int i_index);

	bool HasData() const { return m_events.size() > 0; }
	int GetEventCount() const { return (int) m_events.size(); }
	const NewPVPGameEvent& GetEvent(float i_time);
	const NewPVPGameEvent* GetLastEvent(NewPVPGameEvent::EventType i_type);
	const NewPVPGameEvent& GetFirstEvent();

	bool SerializeJson(const std::string &i_json);
	std::string SerializeObj();

public:
	std::vector<NewPVPGameEvent>	m_events;
	//NewPVPPlayerPlants				m_plants;
};



class NewPVPDataBaseSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(NewPVPDataBaseSubsystem, GameSubSystem, RtClass);

	NewPVPDataBaseSubsystem();

protected:
	virtual void start() {}
	virtual void stop() {}
	virtual void realUpdate() {}
	virtual void update() {}
	virtual void timeout() {}
	virtual void loaded() {}

	virtual void Update() override;

private:
	void onLevelLoadComplete();
	void onGameplayStarted();
	void onGameplayEnded();
	void onGameplayRealUpdate();
	void onNotifyReachMaxInterval();
};

class NewPVPDataSubsystem : public NewPVPDataBaseSubsystem
{
public:
	RT_CLASS_DEFINE(NewPVPDataSubsystem, NewPVPDataBaseSubsystem, RtClass);

	NewPVPDataSubsystem();

	void update() override;
	void realUpdate() override;
	void timeout() override;
	void loaded() override;

	void StopRunning();

	void Clear() { m_selfData.Clear(); m_oppoentData.Clear(); }
	void ClearSelf() { m_selfData.Clear(); }
	void ClearOppoent() { m_oppoentData.Clear(); }

	void AddEvent(TriggerEventType i_triggerType, NewPVPGameEvent::EventType i_eventType, int i_type = -1, int i_x = -1, int i_y = -1, float i_value = 0, uint32 i_seed = 0, const std::vector<float>& i_extraValues = {});

	bool IsCurrentReachLimit() { return m_reachFPSLimit; }

protected:
	void start() override;
	void stop() override;

private:

	void updateGame();
	void updateOppoent();
	void updateSync();
	bool readyForSyncEvents();
	void sync();
	void syncRestAndFetch();
	void syncRestOppoent();
	void doPost(const std::string& i_info, bool i_fake = false);
	void doSync(const std::string& i_info, bool i_fake = false);
	void getSyncInfo(std::string& i_info);
	void resetNextSyncTime();
	void resetUsedTimeSegment();
	void onMsgError(int erroId, const std::string& requestID);
	void onTimeOut(class UIMessageBox* box, int buttonID);

	void cachePlants();
	// requests
	void requestOppoent(const NewPVPGameEvent& i_event);

	// responses
	void onPlantAdded(class Plant* i_plant, int i_x, int i_y);
	void onPlantUpgraded(int i_x, int i_y);
	void onPlantRemoved(int i_x, int i_y);
	void onZombieAdded(std::string i_zombieTypeName);
	void onZombieUpgraded();
	void onZombieSkillUsed();
	void onPlantfoodUsed();
	void onSurrender();
	void onReachLine(int i_row);
	void onTurnEnded(int i_current);

	pvztime_t m_nextEventSyncTime;
	pvztime_t m_usedTime;

	bool m_running;
	bool m_checkTimeout;

	NewPVPGameData m_selfData;
	NewPVPGameData m_oppoentData;
	NewPVPGameData m_fakeOppoentData;
	int m_currentEventIndex;
	bool m_reachFPSLimit;
	int m_totalDisconnectCount;

	// fake
	bool m_fakeRequest;
};

#endif /* NEWPVPDATA_H_ */
