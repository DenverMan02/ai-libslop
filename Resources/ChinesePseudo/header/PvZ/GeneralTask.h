#ifndef GENERALTASK_H
#define GENERALTASK_H

#include "Precompile.h"
#include "RtObject.h"
#include "PVZDB.h"
#include "GeneralTaskConfig.h"

class Zombie;
class DamageInfo;

#define GENERAL_TASK_LISTENER_DESTRUCT(xClass) \
    virtual ~xClass() \
    { \
       RemoveListener();\
    } \

#pragma mark - GeneralTaskListener

class GeneralTaskListener : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(GeneralTaskListener, Sexy::RtObject, RtClass);

    GeneralTaskListener();
    virtual ~GeneralTaskListener();

    virtual void RegisterListener(class GeneralTask* i_task);
    void RemoveListener();//this function will be called in destruct function
    virtual int JumpToTargetTask() { return 0; }
//protected:
    virtual void CounterAdd(int i_num = 1);
    virtual void CounterSet(int i_num);

    bool NeedRemoveListener;
    class GeneralTask* GeneralTaskPtr;
};


#pragma mark - GeneralTask

class GeneralTask : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE_ABSTRACT(GeneralTask, Sexy::RtObject, RtClass);
    GeneralTask();
    virtual ~GeneralTask();

    virtual bool Init(GeneralTaskDataPtr i_taskDataPtr);
    virtual void SetState(int i_state);

    virtual void LoadTask() = 0;
    virtual void SaveTask() = 0;

    virtual void FinishTask();

    virtual void OnCompletedTask();
    virtual bool IsLocked();
//private:
    int ID;
    int GID;
    int TaskProgress;
    int CurrentState;
    time_t CreationDate;
    GeneralTaskDataPtr TaskConfig;
    GeneralTaskListener* TaskListener;




};


//-------------------------------------For Activity HappyVaseBreaker-----------------------------------

#pragma mark - HappyVaseBreakerTask

class HappyVaseBreakerTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(HappyVaseBreakerTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
};

//-------------------------------------For Activity Novice Seven Days task-----------------------------------

#pragma mark - NoviceSevenDaysTask

class NoviceSevenDaysTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(NoviceSevenDaysTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
};

//-------------------------------------For Activity Call of Wish task-----------------------------------

#pragma mark - CallofWishTask

class CallofWishTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(CallofWishTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;

    virtual void FinishTask();
};

//-------------------------------------For Activity PvZ1 Achievement-----------------------------------

#pragma mark - PvZ1Achievement

class PvZ1Achievement : public GeneralTask
{
public:
    RT_CLASS_DEFINE(PvZ1Achievement, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;

    virtual void FinishTask() override;
    virtual void OnCompletedTask() override;
};

//-------------------------------------For Activity GoldenEggTask-----------------------------------

#pragma mark - GoldenEggTask

class GoldenEggTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(GoldenEggTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;
};

//-------------------------------------For Activity ArborDayTask-----------------------------------

#pragma mark - ArborDayTask

class ArborDayTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(ArborDayTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;
};

//-------------------------------------For Activity BattleOrderTask-----------------------------------

#pragma mark - BattleOrderTask

class BattleOrderTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(BattleOrderTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;
};

//-------------------------------------For New PVP-----------------------------------

#pragma mark - NewPVPTask

class NewPVPTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(NewPVPTask, GeneralTask, RtClass);

    NewPVPTask();
    virtual ~NewPVPTask();

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;
    virtual bool IsLocked() override;

    void SetUnlockTime(time_t i_time);

    virtual void OnCompletedTask() override;

    int TaskProgressInSingleLevel;
    time_t m_unlockTime;
};

//-------------------------------------For Uncharted Birthday-----------------------------------

#pragma mark - UnchartedBirthdayTask

class UnchartedBirthdayTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(UnchartedBirthdayTask, GeneralTask, RtClass);

    UnchartedBirthdayTask();
    virtual ~UnchartedBirthdayTask();

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;

    virtual void OnCompletedTask() override;
};

//-------------------------------------For Cornucopia-----------------------------------

#pragma mark - CornucopiaGradeTask

class CornucopiaGradeTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(CornucopiaGradeTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;    
};

//-------------------------------------For Invitation-----------------------------------

#pragma mark - InvitationGradeTask

class InvitationGradeTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(InvitationGradeTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;    
};

//-------------------------------------For PlantCultivate-----------------------------------

#pragma mark - PlantCultivateTask

class PlantCultivateTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(PlantCultivateTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;    
};

//-------------------------------------For GiftFoReturn-----------------------------------

#pragma mark - GiftFoReturnTask

class GiftFoReturnTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(GiftFoReturnTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;    

    virtual bool IsLocked() override;
    void SetUnlockTime(time_t i_time);
    time_t m_unlockTime;
};

//-------------------------------------For DaveKietchen-----------------------------------

#pragma mark - DaveKitchenTask

class DaveKitchenTask : public GeneralTask
{
public:
    RT_CLASS_DEFINE(DaveKitchenTask, GeneralTask, RtClass);

    virtual void LoadTask() override;
    virtual void SaveTask() override;
    virtual void FinishTask() override;
};


//listeners

#pragma mark - GeneralTaskAdventureListener

class GeneralTaskAdventureListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskAdventureListener, GeneralTaskListener, RtClass);

    GeneralTaskAdventureListener();
    virtual ~GeneralTaskAdventureListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onPlantAdventureFinish(int i_worldId);
};


#pragma mark - GeneralTaskDailyConsumeGemsListener

class GeneralTaskDailyConsumeGemsListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskDailyConsumeGemsListener, GeneralTaskListener, RtClass);

    GeneralTaskDailyConsumeGemsListener();
    virtual ~GeneralTaskDailyConsumeGemsListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onRefreshTaskInfo();
};


#pragma mark - GeneralTaskLoginListener

class GeneralTaskLoginListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskLoginListener, GeneralTaskListener, RtClass);

    virtual void RegisterListener(GeneralTask* i_task) override;
};


#pragma mark - GeneralTaskAccumLoginListener

class GeneralTaskAccumLoginListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskAccumLoginListener, GeneralTaskListener, RtClass);

    virtual void RegisterListener(GeneralTask* i_task) override;
};


#pragma mark - GeneralTaskWorldLevelListener

class GeneralTaskWorldLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskWorldLevelListener, GeneralTaskListener, RtClass);

    GeneralTaskWorldLevelListener();
    virtual ~GeneralTaskWorldLevelListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskPassWorldLevelListener

class GeneralTaskPassWorldLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPassWorldLevelListener, GeneralTaskListener, RtClass);

    GeneralTaskPassWorldLevelListener();
    virtual ~GeneralTaskPassWorldLevelListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskCollectPlantChipsListener

class GeneralTaskCollectPlantChipsListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskCollectPlantChipsListener, GeneralTaskListener, RtClass);

    GeneralTaskCollectPlantChipsListener();
    virtual ~GeneralTaskCollectPlantChipsListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onObtainPlantChip(int i_chips);
};


#pragma mark - GeneralTaskPanneyGachaListener

class GeneralTaskPanneyGachaListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPanneyGachaListener, GeneralTaskListener, RtClass);

    GeneralTaskPanneyGachaListener();
    virtual ~GeneralTaskPanneyGachaListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onFinishGacha(int type, int size);
};


#pragma mark - GeneralTaskChallengeListener

class GeneralTaskChallengeListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskChallengeListener, GeneralTaskListener, RtClass);

    GeneralTaskChallengeListener();
    virtual ~GeneralTaskChallengeListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - GeneralTaskMiniGameListener

class GeneralTaskMiniGameListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskMiniGameListener, GeneralTaskListener, RtClass);

    GeneralTaskMiniGameListener();
    virtual ~GeneralTaskMiniGameListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - GeneralTaskBattleZListener

class GeneralTaskBattleZListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskBattleZListener, GeneralTaskListener, RtClass);

    GeneralTaskBattleZListener();
    virtual ~GeneralTaskBattleZListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskPvPListener

class GeneralTaskPvPListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPvPListener, GeneralTaskListener, RtClass);

    GeneralTaskPvPListener();
    virtual ~GeneralTaskPvPListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskAvatarTransgenosisListener

class GeneralTaskAvatarTransgenosisListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskAvatarTransgenosisListener, GeneralTaskListener, RtClass);

    GeneralTaskAvatarTransgenosisListener();
    virtual ~GeneralTaskAvatarTransgenosisListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void FinishAvatarTransgenic();
};


#pragma mark - GeneralTaskPlantTransgenosisListener

class GeneralTaskPlantTransgenosisListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPlantTransgenosisListener, GeneralTaskListener, RtClass);

    GeneralTaskPlantTransgenosisListener();
    virtual ~GeneralTaskPlantTransgenosisListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void FinishPlantTransgenic();
};

#pragma mark - GeneralTaskGemsRechargeDailyListener

class GeneralTaskGemsRechargeDailyListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskGemsRechargeDailyListener, GeneralTaskListener, RtClass);

    GeneralTaskGemsRechargeDailyListener();
    virtual ~GeneralTaskGemsRechargeDailyListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void OnGemsRecharge(int num);
};

#pragma mark - GeneralTaskGemsRechargeListener

class GeneralTaskGemsRechargeListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskGemsRechargeListener, GeneralTaskListener, RtClass);

    GeneralTaskGemsRechargeListener();
    virtual ~GeneralTaskGemsRechargeListener();

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void OnGemsRecharge(int num);
};


#pragma mark - NoviceSevenDaysTaskPassLevelWithCheckListener
class NoviceSevenDaysTaskPassLevelWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskPassLevelWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskPassLevelWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
    void OnWorldMapWorldLoaded();

    std::string m_centerOnEvent;
    std::string m_theLevel;
};

#pragma mark - GeneralTaskStarObtainWithCheckListener
class GeneralTaskStarObtainWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskStarObtainWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskStarObtainWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnObtainStar(int num);
};

#pragma mark - GeneralTaskPlantLevelUpListener
class GeneralTaskPlantLevelUpListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPlantLevelUpListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPlantLevelUpListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnPlantLevelUp();
};

#pragma mark - NoviceSevenDaysTaskPassLevelPVPListener
class NoviceSevenDaysTaskPassLevelPVPListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskPassLevelPVPListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskPassLevelPVPListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

//通关3次回忆之旅
#pragma mark - PassLevelPVZ1Listener

class PassLevelPVZ1Listener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PassLevelPVZ1Listener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PassLevelPVZ1Listener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;

protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

//在回忆之旅中通关1次精英僵尸
#pragma mark - TaskPassLevelPVZ1Listener

class TaskPassLevelPVZ1Listener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(TaskPassLevelPVZ1Listener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(TaskPassLevelPVZ1Listener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

//参与1次回忆之旅
#pragma mark - NoviceSevenDaysTaskPassLevelPVZ1Listener
class NoviceSevenDaysTaskPassLevelPVZ1Listener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskPassLevelPVZ1Listener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskPassLevelPVZ1Listener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

//参与2次回忆之旅
#pragma mark - NoviceSevenDaysTaskPassLevelPVZ1Listener2
class NoviceSevenDaysTaskPassLevelPVZ1Listener2 : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskPassLevelPVZ1Listener2, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskPassLevelPVZ1Listener2)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

//参与5次回忆之旅
#pragma mark - NoviceSevenDaysTaskPassLevelPVZ1Listener5
class NoviceSevenDaysTaskPassLevelPVZ1Listener5 : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskPassLevelPVZ1Listener5, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskPassLevelPVZ1Listener5)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - NoviceSevenDaysTaskChallengeLevelListener
class NoviceSevenDaysTaskChallengeLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskChallengeLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskChallengeLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - NoviceSevenDaysTaskAdventureListener
class NoviceSevenDaysTaskAdventureListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskAdventureListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskAdventureListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onPlantAdventureFinish(int i_worldId);
};

#pragma mark - NoviceSevenDaysTaskBattleZListener
class  NoviceSevenDaysTaskBattleZListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskBattleZListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskBattleZListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - GeneralTaskDailyTravelLogListener
class GeneralTaskDailyTravelLogListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskDailyTravelLogListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskDailyTravelLogListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnFinishTravelogDailyTask();
};

#pragma mark - NoviceSevenDaysTaskEndlessListener
class NoviceSevenDaysTaskEndlessListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskEndlessListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskEndlessListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - NoviceSevenDaysTaskPennyLevelListener
class NoviceSevenDaysTaskPennyLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskPennyLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskPennyLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - GeneralTaskPennyLevelListener
class GeneralTaskPennyLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPennyLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPennyLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};

#pragma mark - GeneralTaskWorldTravelLogListener
class GeneralTaskWorldTravelLogListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskWorldTravelLogListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskWorldTravelLogListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnFinishTravelogWorildTask();
};

#pragma mark - GeneralTaskSpecialTravelLogListener
class GeneralTaskSpecialTravelLogListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskSpecialTravelLogListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskSpecialTravelLogListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnFinishTravelogSpecialTask();
};

#pragma mark - GeneralTaskPlantFamilyRefreshWithCheckListener
class GeneralTaskPlantFamilyRefreshWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPlantFamilyRefreshWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPlantFamilyRefreshWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnPlantFamilyRefresh();
};

#pragma mark - GeneralTaskTransgenosisWithCheckListener
class GeneralTaskTransgenosisWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskTransgenosisWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskTransgenosisWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void FinishPlantTransgenic();
    void FinishAvatarTransgenic();
};

#pragma mark - GeneralTaskSetPvPLabLevelWithCheckListener
class GeneralTaskSetPvPLabLevelWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskSetPvPLabLevelWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskSetPvPLabLevelWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnSetPvPLabLevel(int label, int level);
};

#pragma mark - GeneralTaskSetDangerRoomMaxLevelWithCheckListener
class GeneralTaskSetDangerRoomMaxLevelWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskSetDangerRoomMaxLevelWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskSetDangerRoomMaxLevelWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnSetDangerRoomMaxLevel(int level);
};

#pragma mark - GeneralTaskPVPBuyShopObjectListener
class GeneralTaskPVPBuyShopObjectListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPVPBuyShopObjectListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPVPBuyShopObjectListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnPVPBuyShopObject();
};

#pragma mark - GeneralTaskSteadyAccessoryListener
class GeneralTaskSteadyAccessoryListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskSteadyAccessoryListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskSteadyAccessoryListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnSteadyAccessory();
};

#pragma mark - GeneralTaskObtainAccessoryPieceListener
class GeneralTaskObtainAccessoryPieceListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskObtainAccessoryPieceListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskObtainAccessoryPieceListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnObtainAccessoryPiece(int i_pieceId, int i_amount);
};

//水晶商店
#pragma mark - GeneralTaskBuySecretStoreListener
class GeneralTaskBuySecretStoreListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskBuySecretStoreListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskBuySecretStoreListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnBuySecretStore();
};

#pragma mark - NoviceSevenDaysTaskUnlockWorldWithCheckListener
class NoviceSevenDaysTaskUnlockWorldWithCheckListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NoviceSevenDaysTaskUnlockWorldWithCheckListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NoviceSevenDaysTaskUnlockWorldWithCheckListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void OnPurchaseWorld(const class MapEventItem* i_gateEvent);
};

#pragma mark - CallofWishObtainIntegralListener
class CallofWishObtainIntegralListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(CallofWishObtainIntegralListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(CallofWishObtainIntegralListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void OnGenericObtainIntegral(int taskType, int i_num);
};

// PvZ1 Achievement 

#pragma mark - GeneralRemainingSunCurrencyListener

class GeneralRemainingSunCurrencyListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralRemainingSunCurrencyListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralRemainingSunCurrencyListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

#pragma mark - PvZ1FinishAllHardLevelListener

class PvZ1FinishAllHardLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1FinishAllHardLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishAllHardLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

#pragma mark - GeneralKillEliteZombieListener

class GeneralKillEliteZombieListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(GeneralKillEliteZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralKillEliteZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

#pragma mark - PvZ1FinishHardLevelOlnyPvZ1Listener

class PvZ1FinishHardLevelOlnyPvZ1Listener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1FinishHardLevelOlnyPvZ1Listener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishHardLevelOlnyPvZ1Listener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

#pragma mark - PvZ1FinishAllThemeLevelListener

class PvZ1FinishAllThemeLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1FinishAllThemeLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishAllThemeLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};


#pragma mark - GeneralMagnetShroomEffectListener

class GeneralMagnetShroomEffectListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralMagnetShroomEffectListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralMagnetShroomEffectListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onMagnetShroomPullHelm(class Plant* i_plant, class BoardEntity* i_boardEntity);
};

#pragma mark - GeneralPlantKillZombieListener

class GeneralPlantKillZombieListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(GeneralPlantKillZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralPlantKillZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

#pragma mark - GeneralPlantHypnoZombieListener

class GeneralPlantHypnoZombieListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(GeneralPlantHypnoZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralPlantHypnoZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onPlantHypnoZombie(Plant* i_plant, Zombie* i_zombie);
};

#pragma mark - GeneralShieldArtifactKillZombieListener

class GeneralShieldArtifactKillZombieListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(GeneralShieldArtifactKillZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralShieldArtifactKillZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onShieldArtifactKillZombie(Zombie* i_zombie);
};

#pragma mark - GeneralVaseArtifactProducePlantCardListener

class GeneralVaseArtifactProducePlantCardListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(GeneralVaseArtifactProducePlantCardListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralVaseArtifactProducePlantCardListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onVaseArtifactProducePlantCard(const std::string& i_plantName);
};


#pragma mark - PvZ1FinishLevelListener

class PvZ1FinishLevelListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(PvZ1FinishLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};


#pragma mark - PvZ1FinishHardLevelListener

class PvZ1FinishHardLevelListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(PvZ1FinishHardLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishHardLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

private:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};


#pragma mark - GeneralTaskSuperVIPLoginListener

class GeneralTaskSuperVIPLoginListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskSuperVIPLoginListener, GeneralTaskListener, RtClass);

    virtual void RegisterListener(GeneralTask* i_task) override;
};

#pragma mark - GeneralTaskDIYLevelListener

class GeneralTaskDIYLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskDIYLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskDIYLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskPlayCustomLevelListener

class GeneralTaskPlayCustomLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPlayCustomLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPlayCustomLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskEvaluateCustomLevelListener

class GeneralTaskEvaluateCustomLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskEvaluateCustomLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskEvaluateCustomLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onEvaluateCustomLevel(bool i_like);
};


#pragma mark - GeneralTaskThumbsUpCustomLevelListener

class GeneralTaskThumbsUpCustomLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskThumbsUpCustomLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskThumbsUpCustomLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onEvaluateCustomLevel(bool i_like);
};


#pragma mark - GeneralTaskPublishCustomLevelListener

class GeneralTaskPublishCustomLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPublishCustomLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPublishCustomLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onPublishCustomLevel();
};


#pragma mark - GeneralTaskPlayNormalOrUnchartLevelListener

class GeneralTaskPlayNormalOrUnchartLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPlayNormalOrUnchartLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPlayNormalOrUnchartLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskPlayUnchartLevelListener

class GeneralTaskPlayUnchartLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPlayUnchartLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPlayUnchartLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskAnyGachaListener

class GeneralTaskAnyGachaListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskAnyGachaListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskAnyGachaListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onFinishGacha(int type, int size);
    void onFinishSecretGacha(int number);
    void onFinishLimitGacha(int number);
};


#pragma mark - GeneralTaskSecretGachaListener

class GeneralTaskSecretGachaListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskSecretGachaListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskSecretGachaListener)

    virtual void RegisterListener(GeneralTask* i_task) override;

protected:
    void onFinishSecretGacha(int number);
};


#pragma mark - GeneralTaskBreakHappyVaseListener

class GeneralTaskBreakHappyVaseListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskBreakHappyVaseListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskBreakHappyVaseListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onHappyVaseBreaker_BreakVase();
};


#pragma mark - GeneralTaskBreakGoldenEggListener

class GeneralTaskBreakGoldenEggListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskBreakGoldenEggListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskBreakGoldenEggListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onFestivalGoldenEgg_BreakEgg();
};


#pragma mark - GeneralTaskFightZodiacListener

class GeneralTaskFightZodiacListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskFightZodiacListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskFightZodiacListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onFightZodiac_UseFirework(int i_fireWorkNumber, bool i_killedZodiac);
};


#pragma mark - GeneralTaskVaseBreakerPassWorldPacketListener

class GeneralTaskVaseBreakerPassWorldPacketListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskVaseBreakerPassWorldPacketListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskVaseBreakerPassWorldPacketListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
};


#pragma mark - GeneralTaskChangeMaterialListener

class GeneralTaskChangeMaterialListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskChangeMaterialListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskChangeMaterialListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onBeforeChangeMaterialNumber(int i_matId, int i_diff);
};


#pragma mark - GeneralTaskRichManRollDiceListener

class GeneralTaskRichManRollDiceListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskRichManRollDiceListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskRichManRollDiceListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onRichMan_RollDice();
};


#pragma mark - GeneralTaskPassBossChallengeLevelListener

class GeneralTaskPassBossChallengeLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPassBossChallengeLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPassBossChallengeLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onWinBossChallenge();
};


#pragma mark - GeneralTaskPennyLeagueListener

class GeneralTaskPennyLeagueListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPennyLeagueListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPennyLeagueListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
};


#pragma mark - GeneralTaskBattleZLeagueListener

class GeneralTaskBattleZLeagueListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskBattleZLeagueListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskBattleZLeagueListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
};

//战令-消耗钻石
#pragma mark - GeneralTaskConsumeGemsListener

class GeneralTaskConsumeGemsListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskConsumeGemsListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskConsumeGemsListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onRefreshTaskInfo();
};


//神秘商店
#pragma mark - GeneralTaskRealSecretStoreListener
class GeneralTaskRealSecretStoreListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskRealSecretStoreListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskRealSecretStoreListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onBuySecretStore();
};


#pragma mark - PvZ1BeatEliteZombieListener
class PvZ1BeatEliteZombieListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1BeatEliteZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1BeatEliteZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

#pragma mark - PvZ1FinishWithBeatEliteAndLostPlantsListener
class PvZ1FinishWithBeatEliteAndLostPlantsListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1FinishWithBeatEliteAndLostPlantsListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishWithBeatEliteAndLostPlantsListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

#pragma mark - PvZ1FinishNormalDifferentThemeListener
class PvZ1FinishNormalDifferentThemeListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1FinishNormalDifferentThemeListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1FinishNormalDifferentThemeListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

#pragma mark - PvZ1PassAllHardEliteListener
class PvZ1PassAllHardEliteListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(PvZ1PassAllHardEliteListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(PvZ1PassAllHardEliteListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};

// 参与n场newPVP对战
#pragma mark - NewPVPPassLevelListener
class NewPVPPassLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NewPVPPassLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPPassLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onPassLevel(bool i_isWin, bool i_isFullHitpoints, int i_curRound);
};

// newPVP 消耗n点阳光
#pragma mark - NewPVPTakeSunMoneyListener
class NewPVPTakeSunMoneyListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NewPVPTakeSunMoneyListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPTakeSunMoneyListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onTakenSunMoney(int32 i_newCount);
};

// newPVP 种植n棵植物
#pragma mark - NewPVPAddPlantListener
class NewPVPAddPlantListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NewPVPAddPlantListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPAddPlantListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onPlantAdded(int i_type, int i_level);
};

// newPVP 部署n只僵尸
#pragma mark - NewPVPAddZombieListener
class NewPVPAddZombieListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NewPVPAddZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPAddZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onZombieAdded(struct NewPVPAddZombieMessageData* i_data);
};

// NewPVP 消灭n只僵尸
#pragma mark - NewPVPKillZombieListener

class NewPVPKillZombieListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(NewPVPKillZombieListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPKillZombieListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
private:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

// NewPVP 升级n次向日葵等级
#pragma mark - NewPVPUpgradeSunListener

class NewPVPUpgradeSunListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(NewPVPUpgradeSunListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPUpgradeSunListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
private:
    void onSunUpgraded();
};

// NewPVP 对敌方基地造成n点伤害
#pragma mark - NewPVPDamageOpponentBasesListener

class NewPVPDamageOpponentBasesListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(NewPVPDamageOpponentBasesListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPDamageOpponentBasesListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
private:
    void onDamageTaken(float i_damagePoints);
};

// NewPVP 首先对敌方基地造成伤害n次
#pragma mark - NewPVPFirstBloodListener

class NewPVPFirstBloodListener : public GeneralTaskListener
{
public:
    RT_CLASS_DEFINE(NewPVPFirstBloodListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPFirstBloodListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
private:
    void onFirstBlood();
};

// newPVP 单局部署n只僵尸
#pragma mark - NewPVPAddZombieInSingleLevelListener
class NewPVPAddZombieInSingleLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(NewPVPAddZombieInSingleLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(NewPVPAddZombieInSingleLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    virtual int JumpToTargetTask() override;
protected:
    void onZombieAdded(struct NewPVPAddZombieMessageData* i_data);
    void onLevelLoadComplete();

    void counterAddInSingleLevel(int i_num = 1);
    void conterSetInSingleLevel(int i_num);
};

// 累计获得 基因序列或者基因精华
#pragma mark - ObtainGeneSequenceOREssenceLevelListener
class ObtainGeneSequenceOREssenceLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(ObtainGeneSequenceOREssenceLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(ObtainGeneSequenceOREssenceLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onAddGene(int i_num);

};

// Uncharted birthday level finished task
#pragma mark - UnchartedBirthdayLevelFinishedListener
class UnchartedBirthdayLevelFinishedListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(UnchartedBirthdayLevelFinishedListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(UnchartedBirthdayLevelFinishedListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelFinished(bool i_win);
};

#pragma mark - UnchartedBirthdayLevelFinishedChallengeListener
class UnchartedBirthdayLevelFinishedChallengeListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(UnchartedBirthdayLevelFinishedChallengeListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(UnchartedBirthdayLevelFinishedChallengeListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelFinished(bool i_win);
};

#pragma mark - RecruitNumListener
class RecruitNumListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(RecruitNumListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(RecruitNumListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onAddRecruitNum();
};

#pragma mark - RecruitStarNumListener
class RecruitStarNumListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(RecruitStarNumListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(RecruitStarNumListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
    
protected:
    void onAddRecruitNum();
};


#pragma mark - GeneralTaskPassPennyOrPvZ1LevelListener
class GeneralTaskPassPennyOrPvZ1LevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPassPennyOrPvZ1LevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPassPennyOrPvZ1LevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onLevelEnded(class LevelDefinitionForTask* i_defTask);
    void onPvZ1FinishLevel(int levelNodeID, bool isHard);
};


#pragma mark - GeneralTaskPassEndlessOrPvPLevelListener
class GeneralTaskPassEndlessOrPvPLevelListener : public GeneralTaskListener
{
public:
	RT_CLASS_DEFINE(GeneralTaskPassEndlessOrPvPLevelListener, GeneralTaskListener, RtClass);
    GENERAL_TASK_LISTENER_DESTRUCT(GeneralTaskPassEndlessOrPvPLevelListener)

    virtual void RegisterListener(GeneralTask* i_task) override;
protected:
    void onFinishEndlessLevel(bool i_isWin);
    void onPassLevel(bool i_isWin, bool i_isFullHitpoints, int i_curRound);
};

#endif
