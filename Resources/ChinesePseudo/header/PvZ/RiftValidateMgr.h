/*
 * RiftValidateMgr.h
 *
 *  Created on: 2022-4-26
 *      Author: admin
 */

#ifndef RIFTVALIDATEMGR_H_
#define RIFTVALIDATEMGR_H_

#include "Singleton.h"
#include "Core.h"
#include "Timer.h"
#include "LevelModule.h"
#include "NetworkData.h"

namespace Message
{
    void RiftTimedEventTimerStarted();
    void RiftTimedEventTimerNotify();
    void RiftTimedEventGamePlaySend();
}

class UIWidget;

class RiftTimedEventModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(RiftTimedEventModule, LevelModule, RtClass);

    RiftTimedEventModule();
    ~RiftTimedEventModule();

    void registerForEvents() override;

    void Initialize(pvztime_t i_startTime = 0.0f);

    void onGameplayStarted();
    void onGameplayEnded();
    void onGameplayRealUpdate();

    void Update();

    float GetUsedTime() { return m_usedTime; }

private:
    void onLoadComplete();
    void initLevelTimer();
    void updateLevelTimerUI();
    void onNotifyReachMaxInterval();
    void onReachMaxInterval();
    void onNotifyRiftPostEndPlay();

    RtWeakPtr<UIWidget> m_widget;
    bool m_levelHasStarted;

    pvztime_t m_usedTime;
    pvztime_t m_finishTime;
    pvztime_t m_nextNotifyTime;
};

class RiftTimedEventModuleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(RiftTimedEventModuleProperties, LevelModuleProperties, RtClass);

    RtClass* GetModuleClass() const override
    {
        return RiftTimedEventModule::StaticGetClass();
    }
};

typedef RtWeakPtr<const RiftTimedEventModuleProperties> RiftTimedEventModulePropertiesPtr;

struct ValidatePlantAttackCD
{
	ValidatePlantAttackCD()
	: Min(0.0f)
	, Max(0.0f)
	{

	}

	float Min;
	float Max;
};

struct ValidatePlantData
{
	ValidatePlantData()
	: PlantId(-1)
	, Cost(0)
	, Cooldown(0.0f)
	, Level(1)
	, Accessory(-1)
	{

	}

	int PlantId;
	int Cost;
	float Cooldown;
	int Level;
	std::vector<std::string> Family;
	int Accessory;
	ValidatePlantAttackCD AttackCooldown;
};

class ValidateGameStartData : public RtObject
{
public:
    RT_CLASS_DEFINE(ValidateGameStartData, RtObject, RtClass);
    ValidateGameStartData();
public:
    std::vector<ValidatePlantData> m_plantInfos;

    pvztime_t m_time;
    int m_sun;
    int m_plantfood;

    bool SerializeJson(const std::string &i_json);
    std::string SerializeObj();
};

struct ValidateDamageInfoData
{
	ValidateDamageInfoData()
	: PlantId(-1)
	, Level(0)
	, DamageDealt(0.0f)
	{

	}

	ValidateDamageInfoData(int i_plantId, int i_level, float i_damageDealt)
	: PlantId(i_plantId)
	, Level(i_level)
	, DamageDealt(i_damageDealt)
	{

	}

	int PlantId;
	int Level;
	float DamageDealt;
};

struct ValidateZombieInfoData
{
	ValidateZombieInfoData()
	: Health(0.0f)
	, MaxHealth(0.0f)
	{

	}

	ValidateZombieInfoData(float i_health, float i_maxHealth)
	: Health(i_health)
	, MaxHealth(i_maxHealth)
	{

	}

	float Health;
	float MaxHealth;
};

enum ValidateToolPacketType
{
	ToolPacketType_None = -1,
	ToolPacketType_LevelUp,
	ToolPacketType_Plantfood,
	ToolPacketType_Artifact
};

struct ValidateToolPacketData
{
	ValidateToolPacketData()
	: Type(ToolPacketType_None)
	, UsedCount(0)
	, UsedSun(0)
	{

	}

	ValidateToolPacketData(ValidateToolPacketType i_type, int i_usedCount, int i_usedSun)
	: Type(i_type)
	, UsedCount(i_usedCount)
	, UsedSun(i_usedSun)
	{

	}

	ValidateToolPacketType Type;
	int UsedCount;
	int UsedSun;
};

class ValidateGamePlayData : public RtObject
{
public:
    RT_CLASS_DEFINE(ValidateGamePlayData, RtObject, RtClass);
    ValidateGamePlayData();

    void Reset();
public:
    std::vector<ValidateDamageInfoData> m_damageInfos;
    std::vector<ValidateZombieInfoData> m_zombieInfos;
    std::vector<ValidateToolPacketData> m_toolInfos;
    std::vector<int> m_plantLevels;

    int m_zombieDied;
    int m_sunUsed;
    int m_plantfoodUsed;
    int m_zombieSunDropped;
    int m_artifactTriggered;

    bool SerializeJson(const std::string &i_json);
    std::string SerializeObj();
};

class ValidateNetworkResponseData : public INetworkData
{
public:
    RT_CLASS_DEFINE(ValidateNetworkResponseData, INetworkData, Sexy::RtClass);

public:
    bool Success;
    int ErrorCode;
};

class RiftValidateMgr : public LazySingleton<RiftValidateMgr>
{
public:
	RiftValidateMgr();
	virtual ~RiftValidateMgr();

	void Update();
	void AddTimerModuleIfNeeded();

	void SetGameStartData(const ValidateGameStartData& i_data) { m_gameStartData = i_data; }
	const ValidateGameStartData& GetGameStartData() { return m_gameStartData; }

	void NotifyZombieDiedAndSunDrop(int i_sunDropped);

	float GetLevelUsedTime();

	bool IsValidateLevel();

private:
	void trySendGameStartInfos();
	void trySendGamePlayInfos();
	void onArtifactTrigger();
	void onRiftTimedEventTimerStarted();
	void onNotifyRiftPostEndPlay();
	void onRiftTimedEventTimerNotify();
	void onZombiePlaceOnBoard(class Zombie* zombie);
	void onZombieDied(class Zombie* zombie, const DamageInfo* i_deathBlow);
	void onSunSpent(int i_amount);
	void onPlantfoodUsed(class PlantGroup* plant);
	void onZombieDamageTakenRaw(class Zombie* i_zombie, const DamageInfo& i_damage);
	void onNotifyToolPacketUsed(const std::string& i_typeName, int i_delta, int i_usedCount);
	void forceExit(int i_errorCode);
	void onforceExit();

	void gatherGamePlayPlantLevels();
	void gatherGameStartInfos();
	void sendGameStartInfos(const std::string& i_info);
	void sendGamePlayInfos(const std::string& i_info);
	void getSelectedPlantTypes(std::vector<std::string>& i_infos);
	void tryReplaceDamageInfo(class Plant* plant, const DamageInfo& i_damage);

	ValidateGameStartData m_gameStartData;
	ValidateGamePlayData m_gamePlayData;
};


#endif /* RIFTVALIDATEMGR_H_ */
