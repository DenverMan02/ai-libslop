#ifndef GENERALTASKCONFIG_H
#define GENERALTASKCONFIG_H

#include "PVZDB.h"
#include "RtObject.h"
#include "Precompile.h"

#include<string>

//--------------------------------------------------------------------------------------------
//------------------------------------GeneralTasks--------------------------------------------
//--------------------------------------------------------------------------------------------

enum GeneralTaskStatus
{
    TASK_STATUS_INVALID = -1,
	TASK_STATUS_CREATED = 0,
	TASK_STATUS_STARTED,
	TASK_STATUS_COMPLETED,
	TASK_STATUS_REWARDED,
};

enum GeneralTaskGroup
{
    TASK_GROUP_INVALID = 0,
	TASK_GROUP_FIRST,
	TASK_GROUP_SECOND,
	TASK_GROUP_THIRD,
	TASK_GROUP_FOURTH,
};

struct GeneralTaskReward
{
	int RewardID;
	int Quantity;
};

#pragma mark - GeneralTaskData

class GeneralTaskData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(GeneralTaskData, Sexy::RtObject, RtClass);

	int 								ID;                     //id for task, a series of tasks id should be unique
	int                                 GroupID;                //here i use "int", when you inherited this class, you can change the enum type
	std::string							Name;                   //name of this task
	std::string 						Description;            //description of this task
	std::string							Background;             //background location of this task if the UI class need a background
	int									Counter;                //most of the tasks have a counter

    
	std::string                         TaskLogicModule;        //for logic task class
    std::string                         TaskSaveModule;         //for save and load class
    std::string                         TaskListenerModule;     //for Listener class
    std::string                         TaskDisplayModule;      //for UI class

	virtual RtClass* GetTaskLogicModuleClass() const;           //class for task logic class
    virtual RtClass* GetTaskListenerModuleClass() const;        //class for task listener class
    virtual RtClass* GetTaskDisplayModuleClass() const;         //class for task display class
};

typedef RtWeakPtr<class GeneralTaskData> GeneralTaskDataPtr;

//-------------------------------------For Activity HappyVaseBreaker-----------------------------------

#pragma mark - HappyVaseBreakerTaskData

class HappyVaseBreakerTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(HappyVaseBreakerTaskData, GeneralTaskData, RtClass);

    int HammerAwardNumber;
};

#pragma mark - HappyVaseBreakerTaskWorldLevelData

class HappyVaseBreakerTaskWorldLevelData : public HappyVaseBreakerTaskData
{
public:
	RT_CLASS_DEFINE(HappyVaseBreakerTaskWorldLevelData, HappyVaseBreakerTaskData, RtClass);

	HappyVaseBreakerTaskWorldLevelData();
	~HappyVaseBreakerTaskWorldLevelData();

    std::string WorldName;
	int Level;
	bool IsHardLevel;
	bool IsBossLevel;
	bool NeedWin;
};

#pragma mark - HappyVaseBreakerTaskPassSpecialData

struct HappyVaseBreakerSpecialLevel
{
	std::string WorldName;
	std::vector<int> LevelNums;
};

class HappyVaseBreakerTaskPassSpecialData : public HappyVaseBreakerTaskData
{
public:
	RT_CLASS_DEFINE(HappyVaseBreakerTaskPassSpecialData, HappyVaseBreakerTaskData, RtClass);

	std::vector<HappyVaseBreakerSpecialLevel> Levels;
	bool NeedWin;
};

#pragma mark - HappyVaseBreakerConfig

class HappyVaseBreakerConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(HappyVaseBreakerConfig, Sexy::RtObject, RtClass);

	HappyVaseBreakerConfig();
	virtual ~HappyVaseBreakerConfig();
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> HappyVaseBreakerDatas;
};

typedef RtWeakPtr<class HappyVaseBreakerConfig> HappyVaseBreakerConfigPtr;


//-------------------------------------For Activity novice seven days task-----------------------------------

#pragma mark - NoviceSevenDaysTaskData

class NoviceSevenDaysTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskData, GeneralTaskData, RtClass);

	int Integral;
	std::vector<GeneralTaskReward> TaskReward;
};

#pragma mark - NoviceSevenDaysTaskWorldLevelData

class NoviceSevenDaysTaskWorldLevelData : public NoviceSevenDaysTaskData
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskWorldLevelData, NoviceSevenDaysTaskData, RtClass);

	NoviceSevenDaysTaskWorldLevelData()
	{
		Level = 0;
		IsHardLevel = false;
		IsBossLevel = false;
		NeedWin = true;
		PennyDiffculty = -1;
		ChallengeDiffculty = -1;
	}

	std::vector<std::string> WorldNameList;
	int Level;
	bool IsHardLevel;
	bool IsBossLevel;
	bool NeedWin;
	int PennyDiffculty;//0 easy, 1 normal, 2 hard
	int ChallengeDiffculty;//0 easy, 1 normal, 2 hard
};

#pragma mark - NoviceSevenDaysTaskConfig

class NoviceSevenDaysTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NoviceSevenDaysTaskConfig, Sexy::RtObject, RtClass);

	NoviceSevenDaysTaskConfig();
	virtual ~NoviceSevenDaysTaskConfig();
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> NoviceSevenDaysTaskData;
};

typedef RtWeakPtr<class NoviceSevenDaysTaskConfig> NoviceSevenDaysTaskConfigPtr;

//-------------------------------------For Activity call of wish task-----------------------------------

#pragma mark - CallofWishTaskData

class CallofWishTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(CallofWishTaskData, GeneralTaskData, RtClass);

	int Integral;
	std::vector<GeneralTaskReward> TaskReward;
};

#pragma mark - CallofWishTaskConfig

class CallofWishTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(CallofWishTaskConfig, Sexy::RtObject, RtClass);

	CallofWishTaskConfig();
	virtual ~CallofWishTaskConfig();
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> CallofWishTaskData;
};

typedef RtWeakPtr<class CallofWishTaskConfig> CallofWishTaskConfigPtr;

//-------------------------------------For Activity pvz1 achievement-----------------------------------

#pragma mark - PvZ1AchievementData

class PvZ1AchievementData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(PvZ1AchievementData, GeneralTaskData, RtClass);

	PvZ1AchievementData()
	:Integral(0),
	RemainingSunCurrency(0),
	SpaceTimeEnergyLimit(0)
	{
	}

	int Integral;
	int RemainingSunCurrency;
	float SpaceTimeEnergyLimit;
	std::string PlantName;
	std::string AchievementImage;
};

#pragma mark - PvZ1AchievementConfig

class PvZ1AchievementConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PvZ1AchievementConfig, Sexy::RtObject, RtClass);

	PvZ1AchievementConfig();
	virtual ~PvZ1AchievementConfig();
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> PvZ1AchievementData;
};

typedef RtWeakPtr<class PvZ1AchievementConfig> PvZ1AchievementConfigPtr;


//-------------------------------------For Activity GoldenEgg Task-----------------------------------

#pragma mark - GoldenEggTaskData

class GoldenEggTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(GoldenEggTaskData, GeneralTaskData, RtClass);

	GoldenEggTaskData()
	:Hammer(0)
	{
	}

	int Hammer;
};

#pragma mark - GoldenEggTaskConfig

class GoldenEggTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(GoldenEggTaskConfig, Sexy::RtObject, RtClass);
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> GoldenEggTaskData;
};

typedef RtWeakPtr<class GoldenEggTaskConfig> GoldenEggTaskConfigPtr;

//-------------------------------------For Activity ArborDay Task-----------------------------------

#pragma mark - ArborDayTaskData

class ArborDayTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(ArborDayTaskData, GeneralTaskData, RtClass);

	ArborDayTaskData()
	:Kettle(0)
	{
	}

	int Kettle;
};

#pragma mark - ArborDayTaskConfig

class ArborDayTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(ArborDayTaskConfig, Sexy::RtObject, RtClass);
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> ArborDayTaskData;
};

typedef RtWeakPtr<class ArborDayTaskConfig> ArborDayTaskConfigPtr;

//-------------------------------------For Activity BattleOrder Task-----------------------------------

#pragma mark - BattleOrderTaskData

class BattleOrderTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(BattleOrderTaskData, GeneralTaskData, RtClass);

	BattleOrderTaskData()
	:Integral(0)
	{
	}

	int Integral;
	std::string KillZombie;
	std::string MaterialName;
	int PennyLeague;
	int BattleZLeague;
};

#pragma mark - ArborDayTaskConfig

class BattleOrderTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(BattleOrderTaskConfig, Sexy::RtObject, RtClass);
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> BattleOrderTaskData;
};

typedef RtWeakPtr<class BattleOrderTaskConfig> BattleOrderTaskConfigPtr;



//-------------------------------------For New PVP Task-----------------------------------

#pragma mark - NewPVPTaskData

class NewPVPTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(NewPVPTaskData, GeneralTaskData, RtClass);

	NewPVPTaskData()
	{
	}

	int Integral = 0;
	bool NeedWin = false;
	bool NeedFullHitpoints = false;
	bool NeedFirstBlood = false;
	int NeedRound = 0;
	int NeedLevel = 0;
	bool NeedGargantuar = false;
	bool NeedZombieInSpeedUp = false;
	bool NeedZombieInHP = false;
	bool NeedZombieInImmune = false;
	bool NeedZombieInUpgrade = false;
	int	CounterInSingleLevel = 0;
};

#pragma mark - NewPVPTaskConfig

class NewPVPTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NewPVPTaskConfig, Sexy::RtObject, RtClass);
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> NewPVPTaskData;
};

typedef RtWeakPtr<class NewPVPTaskConfig> NewPVPTaskConfigPtr;

//-------------------------------------For New PVP Task-----------------------------------


//------------------------------------- Uncharted birthday-------------------------------------

#pragma mark - UnchartedBirthdayTaskData

class UnchartedBirthdayTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(UnchartedBirthdayTaskData, GeneralTaskData, RtClass);

	UnchartedBirthdayTaskData()
	{
	}

	int Integral = 0;
	std::vector<std::string> ChallengeCollections;
	std::vector<GeneralTaskReward> TaskReward;
	std::string WorldName = "uncharted_anniversary_halloween";
};

#pragma mark - UnchartedBirthdayTaskConfig

class UnchartedBirthdayTaskConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(UnchartedBirthdayTaskConfig, Sexy::RtObject, RtClass);
//private:
	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> UnchartedBirthdayTaskData;
};

typedef RtWeakPtr<class UnchartedBirthdayTaskConfig> UnchartedBirthdayTaskConfigPtr;

//------------------------------------- Uncharted birthday-------------------------------------


//-------------------------------------For cornucopia grade Task-----------------------------------

#pragma mark - CornucopiaGradeTaskData

class CornucopiaGradeTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(CornucopiaGradeTaskData, GeneralTaskData, RtClass);

	int Integral = 0;
};


#pragma mark - CornucopiaGradeTaskConfig

class CornucopiaGradeTaskConfig: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(CornucopiaGradeTaskConfig, Sexy::RtObject, RtClass);	

	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> CornucopiaGradeTaskData;
};

typedef RtWeakPtr<class CornucopiaGradeTaskConfig> CornucopiaGradeTaskConfigPtr;


#pragma mark - InvitationGradeTaskData

class InvitationGradeTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(InvitationGradeTaskData, GeneralTaskData, RtClass);

	int Integral = 0;
};

#pragma mark - InvitationGradeTaskConfig

class InvitationGradeTaskConfig: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(InvitationGradeTaskConfig, Sexy::RtObject, RtClass);	

	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> InvitationGradeTaskData;
};

typedef RtWeakPtr<class InvitationGradeTaskConfig> InvitationGradeTaskConfigPtr;



//-------------------------------------For plant cultivate Task-----------------------------------

#pragma mark - PlantCultivateTaskData

class PlantCultivateTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(PlantCultivateTaskData, GeneralTaskData, RtClass);

	int Integral = 0;
};


#pragma mark - PlantCultivateTaskConfig

class PlantCultivateTaskConfig: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PlantCultivateTaskConfig, Sexy::RtObject, RtClass);	

	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> PlantCultivateTaskData;
};

typedef RtWeakPtr<class PlantCultivateTaskConfig> PlantCultivateTaskConfigPtr;



//-------------------------------------For Gift For Return Task-----------------------------------

#pragma mark - GiftFoReturnTaskData

class GiftFoReturnTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(GiftFoReturnTaskData, GeneralTaskData, RtClass);

	int Integral = 0;
};


#pragma mark - GiftFoReturnTaskConfig

class GiftFoReturnTaskConfig: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(GiftFoReturnTaskConfig, Sexy::RtObject, RtClass);	

	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> GiftFoReturnTaskData;
};

typedef RtWeakPtr<class GiftFoReturnTaskConfig> GiftFoReturnTaskConfigPtr;



//-------------------------------------Dave Kitchen Task-----------------------------------

#pragma mark - DaveKitchenTaskData

class DaveKitchenTaskData : public GeneralTaskData
{
public:
	RT_CLASS_DEFINE(DaveKitchenTaskData, GeneralTaskData, RtClass);

	int Integral = 0;
};


#pragma mark - DaveKitchenTaskConfig

class DaveKitchenTaskConfig: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(DaveKitchenTaskConfig, Sexy::RtObject, RtClass);	

	std::vector<RtEmbeddedPtr<GeneralTaskData, PVZDB::TABLE_GENERALTASK_CONFIG>> DaveKitchenTaskData;
};

typedef RtWeakPtr<class DaveKitchenTaskConfig> DaveKitchenTaskConfigPtr;


#endif
