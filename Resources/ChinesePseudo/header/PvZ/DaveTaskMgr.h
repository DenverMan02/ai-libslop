#ifndef DAVETASKMGR_H
#define DAVETASKMGR_H

#include "PVZDB.h"
#include "Singleton.h"
#include "DaveTaskConfig.h"

class DaveTask;

class DaveTaskManager : public LazySingleton<DaveTaskManager>
{
public:
    DaveTaskManager();
    virtual ~DaveTaskManager();

    void                                    Init();
    void                                    Refresh();
    bool                                    LoadConfig();
    void                                    FilterTask();
    void                                    CreatTask();

    std::vector<DaveTaskDataPtr>&           GetConfig();

    //Task operator
    DaveTask*                               GetTaskByID(int i_id);
    std::vector<DaveTask*>                  GetTasksByGroupID(int i_gid, bool i_flag = false);//is include completed, default false;
    std::vector<DaveTask*>&                 GetAllTasks();
    void                                    ClearAllTasks();

    bool                                    HaveCompletedTask();

    void                                    SetIsEndLevelWin(bool i_isWin);
    bool                                    GetIsEndLevelWin();

private:
    std::vector<DaveTaskDataPtr>            m_daveTaskConfigCache;
    DaveTaskConfigPtr                       m_daveTaskConfigRaw;
    std::vector<DaveTask*>                  m_daveTaskTasks;
    bool                                    m_isEndLevelWin;
};

class PennyTaskManager : public LazySingleton<PennyTaskManager>
{
public:
    PennyTaskManager();
    virtual ~PennyTaskManager();

    void                                    Init();
    void                                    Refresh();
    bool                                    LoadConfig();
    void                                    FilterTask();
    void                                    CreatTask();

    std::vector<DaveTaskDataPtr>&           GetConfig();

    //Task operator
    DaveTask*                               GetTaskByID(int i_id);
    std::vector<DaveTask*>                  GetTasksByGroupID(int i_gid, bool i_flag = false);//is include completed, default false;
    std::vector<DaveTask*>&                 GetAllTasks();
    void                                    ClearAllTasks();

    bool                                    HaveCompletedTask();

    void                                    SetIsEndLevelWin(bool i_isWin);
    bool                                    GetIsEndLevelWin();

    void                                    SetPennyZPS(int i_zps);
    int                                     GetPennyZPS();

private:
    std::vector<DaveTaskDataPtr>            m_daveTaskConfigCache;
    PennyTaskConfigPtr                      m_daveTaskConfigRaw;
    std::vector<DaveTask*>                  m_daveTaskTasks;
    bool                                    m_isEndLevelWin;
    int                                     m_pennyZPS;
};


#define gDaveTaskManager (DaveTaskManager::GetInstancePtr())
#define gPennyTaskManager (PennyTaskManager::GetInstancePtr())

#endif