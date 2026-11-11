#ifndef GENERALTASKMGR_H
#define GENERALTASKMGR_H

#include "PVZDB.h"
#include "Singleton.h"
#include "GeneralTaskConfig.h"

//here no general task manager

class GeneralTask;

class HappyVaseBreakerTaskManager : public LazySingleton<HappyVaseBreakerTaskManager>
{
public:
    HappyVaseBreakerTaskManager();
    virtual ~HappyVaseBreakerTaskManager();

    void                                    Initialize();
    //Task operator
    GeneralTask*                            GetTaskByID(int i_id);
    std::vector<GeneralTask*>               GetTasksByGroupID(int i_gid, bool i_flag = false);//is include completed, default false;
    std::vector<GeneralTask*>&              GetAllTasks();
    void                                    ClearAllTasks();

    bool                                    HaveCompletedTask();

private:
    bool                                    LoadConfig();
    void                                    CreatTask();
    void                                    FilterTask();

    std::vector<GeneralTask*>               m_Tasks;
    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    HappyVaseBreakerConfigPtr               m_TaskConfigJson;
};

#define gHappyVaseBreakerManager (HappyVaseBreakerTaskManager::GetInstancePtr())

class HappyVaseCheckBilling : public LazySingleton<HappyVaseCheckBilling>
{
public:
    HappyVaseCheckBilling();
    ~HappyVaseCheckBilling();
    
    void CheckBillingPoint(const std::string& i_str);
private:
    std::map<std::string, int> BillingMap;
};

#define gHappyVaseCheckBilling HappyVaseCheckBilling::GetInstancePtr()


#pragma mark - GeneralTaskManager

class GeneralTaskStateManager : public LazySingleton<GeneralTaskStateManager>
{
public:
    GeneralTaskStateManager()
    :m_taskLockState(false)
    {
        
    }

    void SetTaskLockState(bool i_lockState) { m_taskLockState = i_lockState; };
    bool GetTaskLockState() { return m_taskLockState; };

private:
    bool m_taskLockState;
};

#define gGeneralTaskStateManager GeneralTaskStateManager::GetInstancePtr()



#pragma mark - GeneralTaskManager

class GeneralTaskManager
{
public:
    GeneralTaskManager();
    virtual ~GeneralTaskManager();

    void Initialize();
    //Task operator
    GeneralTask* GetTaskByID(int i_id);
    std::vector<GeneralTask*> GetTasksByGroupID(int i_gid, bool i_flag = false);//is include completed, default false;
    std::vector<GeneralTask*>& GetAllTasks();
    void ClearAllTasks();
    bool HaveCompletedTask();

protected:
    virtual void CreatTask() = 0;
    virtual bool LoadConfig() = 0;
    virtual void FilterTask() = 0;
    
    std::vector<GeneralTask*> m_Tasks;
};


#pragma mark - NoviceSevenDaysManager

class NoviceSevenDaysManager : public LazySingleton<NoviceSevenDaysManager>, public GeneralTaskManager
{
public:
    NoviceSevenDaysManager();
    virtual ~NoviceSevenDaysManager();

    int GetSunNumber();

    void UpdateData();
    void ObtainIntegral(int num = 1);
    void ObtainReward(int index);

protected:
    bool LoadConfig();
    void FilterTask();
    void CreatTask();

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    NoviceSevenDaysTaskConfigPtr            m_TaskConfigJson;
private:
    void CalculResult();
    int m_result;
    int m_cacheIntegral;
    std::vector<int> m_cacheRewardIndex;
};

#define gNoviceSevenDaysManager (NoviceSevenDaysManager::GetInstancePtr())


#pragma mark - CallofWishTaskManager

class CallofWishTaskManager : public LazySingleton<CallofWishTaskManager>, public GeneralTaskManager
{
public:
    CallofWishTaskManager();
    virtual ~CallofWishTaskManager();

protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    CallofWishTaskConfigPtr                 m_TaskConfigJson;
};

#define gCallofWishTaskManager (CallofWishTaskManager::GetInstancePtr())


#pragma mark - PvZ1AchievementManager

class PvZ1AchievementManager : public LazySingleton<PvZ1AchievementManager>, public GeneralTaskManager
{
public:
    PvZ1AchievementManager();
    virtual ~PvZ1AchievementManager();

protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    PvZ1AchievementConfigPtr                m_TaskConfigJson;
};

#define gPvZ1AchievementManager (PvZ1AchievementManager::GetInstancePtr())


#pragma mark - GoldenEggTaskManager

class GoldenEggTaskManager : public LazySingleton<GoldenEggTaskManager>, public GeneralTaskManager
{
protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    GoldenEggTaskConfigPtr                  m_TaskConfigJson;
};

#define gGoldenEggTaskManager (GoldenEggTaskManager::GetInstancePtr())


#pragma mark - ArborDayTaskManager

class ArborDayTaskManager : public LazySingleton<ArborDayTaskManager>, public GeneralTaskManager
{
protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>        m_TaskConfigs;
    ArborDayTaskConfigPtr                  m_TaskConfigJson;
};

#define gArborDayTaskManager (ArborDayTaskManager::GetInstancePtr())


#pragma mark - BattleOrderTaskManager

class BattleOrderTaskManager : public LazySingleton<BattleOrderTaskManager>, public GeneralTaskManager
{
protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    BattleOrderTaskConfigPtr                m_TaskConfigJson;
};

#define gBattleOrderTaskManager (BattleOrderTaskManager::GetInstancePtr())


#pragma mark - NewPVPTaskManager

class NewPVPTaskManager : public LazySingleton<NewPVPTaskManager>, public GeneralTaskManager
{
protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    NewPVPTaskConfigPtr               	 	m_TaskConfigJson;
};

#define gNewPVPTaskManager (NewPVPTaskManager::GetInstancePtr())


#pragma mark - UnchartedBirthdayTaskManager

class UnchartedBirthdayTaskManager : public LazySingleton<UnchartedBirthdayTaskManager>, public GeneralTaskManager
{
protected:
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    UnchartedBirthdayTaskConfigPtr          m_TaskConfigJson;
};

#define gUnchartedBirthdayTaskManager (UnchartedBirthdayTaskManager::GetInstancePtr())


#pragma mark - CornucopiaGradeTaskManager

class CornucopiaGradeTaskManager : public LazySingleton<CornucopiaGradeTaskManager>,public GeneralTaskManager
{
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    CornucopiaGradeTaskConfigPtr            m_TaskConfigJson;
};

#define gCornucopiaGradeTaskManager (CornucopiaGradeTaskManager::GetInstancePtr())


#pragma mark - InvitationGradeTaskManager

class InvitationGradeTaskManager : public LazySingleton<InvitationGradeTaskManager>,public GeneralTaskManager
{
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    InvitationGradeTaskConfigPtr            m_TaskConfigJson;
};

#define gInvitationGradeTaskManager (InvitationGradeTaskManager::GetInstancePtr())


#pragma mark - PlantCultivateTaskManager

class PlantCultivateTaskManager : public LazySingleton<PlantCultivateTaskManager>,public GeneralTaskManager
{
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    PlantCultivateTaskConfigPtr             m_TaskConfigJson;
};

#define gPlantCultivateTaskManager (PlantCultivateTaskManager::GetInstancePtr())


#pragma mark - GiftFoReturnTaskManager

class GiftFoReturnTaskManager : public LazySingleton<GiftFoReturnTaskManager>, public GeneralTaskManager
{
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    GiftFoReturnTaskConfigPtr               m_TaskConfigJson;
};

#define gGiftFoReturnTaskManager (GiftFoReturnTaskManager::GetInstancePtr())


#pragma mark - DaveKitchenTaskManager

class DaveKitchenTaskManager : public LazySingleton<DaveKitchenTaskManager>, public GeneralTaskManager
{
    bool LoadConfig() override;
    void FilterTask() override;
    void CreatTask() override;

    std::vector<GeneralTaskDataPtr>         m_TaskConfigs;
    DaveKitchenTaskConfigPtr                m_TaskConfigJson;
};

#define gDaveKitchenTaskManager (DaveKitchenTaskManager::GetInstancePtr())


#endif
