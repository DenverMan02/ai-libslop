#ifndef TRAVELLOGCONFIG_H
#define TRAVELLOGCONFIG_H

#include "PVZDB.h"
#include "RtObject.h"
#include "Precompile.h"

#include<string>

enum TravelLogStatus
{
    TL_STATUS_INVALID = -1,
	TL_STATUS_CREATED = 0,
	TL_STATUS_STARTED,
	TL_STATUS_COMPLETED,
	TL_STATUS_REWARDED,
	TL_STATUS_RECYCLED
};

enum TravelLogGroup
{
	TL_GROUP_INVALID = -1,
	TL_GROUP_DAILY = 0,
	TL_GROUP_WEEKLY,
	TL_GROUP_STATIC
};

enum TravelLogAwardType
{
	TL_AWARD_INTEGRAL = 0,
	TL_AWARD_COIN,
	TL_AWARD_DAILY_CHEST,
	TL_AWARD_EPIC_CHEST,
	TL_AWARD_WORLDTASK_CHEST,
	TL_AWARD_DAVE_INTEGRAL,
};

enum EnumTaskIcon
{
	TASK_ICON_NO_ICON = 0,
	TASK_ICON_PVP,
	TASK_ICON_BATTLE_Z,
	TASK_ICON_INTEGRAL,
	TASK_ICON_WORLDLEVEL,
	TASK_ICON_CHALLENGE,
	TASK_ICON_CHIP,
	TASK_ICON_ADVENTURE,
};

struct TravelLogAward
{
	int Type;
	int Amount;
};

class TravelLogData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(TravelLogData, Sexy::RtObject, RtClass);

	int 								ID;
	TravelLogGroup						GroupID;
	std::string							Name;
	std::string 						Description;
	std::string							Background;
	std::vector<TravelLogAward>			Awards;
	int									Requirement;
	int									TaskIcon;					

	virtual RtClass* GetTaskClass() const = 0;
	virtual RtClass* GetWidgetClass() const;
};

class TravelLogBattleZData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogBattleZData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

class TravelLogPvPData : public TravelLogData
{
public:
	RT_CLASS_DEFINE(TravelLogPvPData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//无尽挑战
class TravelLogChallengeData : public TravelLogData
{
public:
	RT_CLASS_DEFINE(TravelLogChallengeData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//潘妮追击
class TravelLogPennyData : public TravelLogData
{
public:
	RT_CLASS_DEFINE(TravelLogPennyData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//回忆之旅
class TravelLogPVZ1Data : public TravelLogData
{
public:
	RT_CLASS_DEFINE(TravelLogPVZ1Data, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//创意庭院
class TravelLogCustomerData : public TravelLogData
{
public:
	RT_CLASS_DEFINE(TravelLogCustomerData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

class TravelLogPassLevelData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogPassLevelData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

class TravelLogPassChallengeData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogPassChallengeData, TravelLogData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

class TravelLogCollectPlantChipsData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogCollectPlantChipsData, TravelLogData, RtClass);

	RtClass* GetTaskClass() const override;
};

class TravelLogDailyIntegralData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogDailyIntegralData, TravelLogData, RtClass);

	RtClass* GetTaskClass() const override;
};

class TravelLogBeatZombiesData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogBeatZombiesData, TravelLogData, RtClass);

	std::string							WorldName;
	std::string 						ZombieName;

	RtClass* GetTaskClass() const override;
	virtual RtClass* GetWidgetClass() const override;
};

class TravelLogEpicTaskData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogEpicTaskData, TravelLogData, RtClass);

	bool 								NeedWin;
	std::vector<std::string>			LevelList;

	RtClass* GetTaskClass() const override;
	virtual RtClass* GetWidgetClass() const override;
};

class TravelLogWeeklyIntegralData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogWeeklyIntegralData, TravelLogData, RtClass);

	RtClass* GetTaskClass() const override;
};

class TravelLogWorldTaskData : public TravelLogData 
{
public:
	RT_CLASS_DEFINE(TravelLogWorldTaskData, TravelLogData, RtClass);

	std::string							WorldName;
	int 								Level;
	bool								IsHard;
	bool								IsBoss;
	bool 								NeedWin;
	
	RtClass* GetTaskClass() const override;
	virtual RtClass* GetWidgetClass() const override;
};

////////////////////////////////////////////////Boundary line////////////////////////////////////////////////////////////////////////

class TravelLogConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TravelLogConfig, Sexy::RtObject, RtClass);

	TravelLogConfig();
	virtual ~TravelLogConfig();
//private:
	std::vector<RtEmbeddedPtr<TravelLogData, PVZDB::TABLE_TRAVELLOG_CONFIG>>			TravelLogDatas;	
};

typedef RtWeakPtr<class TravelLogData> TravelLogDataPtr;
typedef RtWeakPtr<class TravelLogConfig> TravelLogConfigPtr;

class TravelLogSeverData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TravelLogSeverData, Sexy::RtObject, RtClass);

	TravelLogSeverData(){};
	virtual ~TravelLogSeverData(){};

	std::vector<int>	m_vecData;

};

struct TLServerReward
{
	int item;
	int quantity;
};

class TravelLogRewardData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(TravelLogRewardData, Sexy::RtObject, RtClass);

	TravelLogRewardData(){};
	virtual ~TravelLogRewardData(){};

	std::vector<TLServerReward>	m_vecData;
};

#endif