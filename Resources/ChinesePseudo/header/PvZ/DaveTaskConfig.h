#ifndef DAVETASKCONFIG_H
#define DAVETASKCONFIG_H

#include "PVZDB.h"
#include "RtObject.h"
#include "Precompile.h"

#include<string>

enum DaveTaskStatus
{
    DT_STATUS_INVALID = -1,
	DT_STATUS_CREATED = 0,
	DT_STATUS_STARTED,
	DT_STATUS_COMPLETED,
	DT_STATUS_REWARDED,
};

enum DaveTaskGroup
{
	DT_GROUP_INVALID = -1,
	DT_GROUP_DAILY = 0,
	DT_GROUP_WEEKLY,
	DT_GROUP_STATIC
};

enum DaveTaskAwardType
{
    DT_AWARD_NAMEMAPPER_TYPE = 0,
	DT_AWARD_INTEGRAL,
	DT_AWARD_COIN,
	DT_AWARD_DAILY_CHEST,
	DT_AWARD_EPIC_CHEST,
	DT_AWARD_WORLDTASK_CHEST,
};

struct DaveTaskAward
{
	int Type;
    int SubType;
	int Amount;
};

class DaveTaskData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(DaveTaskData, Sexy::RtObject, RtClass);

	int 								ID;
	DaveTaskGroup						GroupID;
	std::string							Name;
	std::string 						Description;
	std::string							Background;
	std::vector<DaveTaskAward>			Awards;
	int									Requirement;
    bool								IsNormalChallange;
	std::string							ActivityName;

	DaveTaskData();

	virtual RtClass* GetTaskClass() const = 0;
	virtual RtClass* GetWidgetClass() const;
};

class DaveTaskPassLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPassLevelData, DaveTaskData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

class DaveTaskPvPData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPvPData, DaveTaskData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//参与1次回忆之旅
class DaveTaskPVZ1Data : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPVZ1Data, DaveTaskData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//通关1次回忆之旅
class DaveTaskPassPVZ1Data : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPassPVZ1Data, DaveTaskData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

//通关回忆之旅中任意关卡8次
class DaveTaskPassManyPVZ1Data : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPassManyPVZ1Data, DaveTaskData, RtClass);

	bool 								NeedWin;

	RtClass* GetTaskClass() const override;
};

class DaveTaskPlantAdventureData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPlantAdventureData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskEndlessData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskEndlessData, DaveTaskData, RtClass);

    bool                                NeedWin;

	RtClass* GetTaskClass() const override;
};

class DaveTaskPassEasyLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPassEasyLevelData, DaveTaskData, RtClass);

    bool                                NeedWin;

	RtClass* GetTaskClass() const override;
};

class DaveTaskPassHardLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPassHardLevelData, DaveTaskData, RtClass);

    bool                                NeedWin;

	RtClass* GetTaskClass() const override;
};

class DaveTaskBeatBossData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskBeatBossData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskBattleZData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskBattleZData, DaveTaskData, RtClass);

    bool                                NeedWin;

	RtClass* GetTaskClass() const override;
};

class DaveTaskFamilyRefreshData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskFamilyRefreshData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskNormalDrawData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskNormalDrawData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskEndlessBeatBossData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskEndlessBeatBossData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskExtinguishFireData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskExtinguishFireData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskTransgenicData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskTransgenicData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskPassPennyLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPassPennyLevelData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskKillZombieOnPennyLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskKillZombieOnPennyLevelData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskObtainPennySignalData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskObtainPennySignalData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskConsumeFuelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskConsumeFuelData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskFinishPennyLevelBossData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskFinishPennyLevelBossData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskWinPennyLevelBossData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskWinPennyLevelBossData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskObtainSunmoneyOnPennyLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskObtainSunmoneyOnPennyLevelData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};

class DaveTaskAddPlantOnPennyLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskAddPlantOnPennyLevelData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};


class DaveTaskPlantfoodOnPennyLevelData : public DaveTaskData
{
public:
	RT_CLASS_DEFINE(DaveTaskPlantfoodOnPennyLevelData, DaveTaskData, RtClass);

	RtClass* GetTaskClass() const override;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////

class DaveTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(DaveTaskConfig, Sexy::RtObject, RtClass);

	DaveTaskConfig();
	virtual ~DaveTaskConfig();
//private:
	int																					DaveTaskVersion;
	std::vector<RtEmbeddedPtr<DaveTaskData, PVZDB::TABLE_DAVETREASURE_CONFIG>>			DaveTaskDatas;	
};

class PennyTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PennyTaskConfig, Sexy::RtObject, RtClass);

	PennyTaskConfig();
	virtual ~PennyTaskConfig();
//private:
	int																					DaveTaskVersion;
	std::vector<RtEmbeddedPtr<DaveTaskData, PVZDB::TABLE_DAVETREASURE_CONFIG>>			DaveTaskDatas;	
};

typedef RtWeakPtr<class DaveTaskData> DaveTaskDataPtr;
typedef RtWeakPtr<class DaveTaskConfig> DaveTaskConfigPtr;
typedef RtWeakPtr<class PennyTaskConfig> PennyTaskConfigPtr;

#endif