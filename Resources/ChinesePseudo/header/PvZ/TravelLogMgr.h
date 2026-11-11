#ifndef TRAVELLOGMGR_H
#define TRAVELLOGMGR_H

#include "PVZDB.h"
#include "Singleton.h"
#include "TravelLogConfig.h"

class TravelLogTask;

class TravelLogManager : public LazySingleton<TravelLogManager>
{
public:
    TravelLogManager();
    virtual ~TravelLogManager();

    void                                    Init();
    bool                                    LoadConfig();
    bool                                    InitializeAllTasks();
    void                                    RefreshAllTasks();
    std::vector<TravelLogDataPtr>&          GetConfig();
    void                                    TaskFilter();
    void                                    SaveTasks();
    bool                                    IsLegalWorldTasks(TravelLogWorldTaskData* data);

    //Task operator
    TravelLogDataPtr                        GetGetTravelLogDataById(int i_idIndex);
    std::vector<TravelLogTask*>&            GetAllTasks();
    TravelLogTask*                          GetTaskByID(int i_id);
    std::vector<TravelLogTask*>             GetCompletedTasks();
    TravelLogTask*                          GetACompletedTask();
    bool                                    HaveCompletedTask();
    std::vector<TravelLogTask*>             GetTasksByGroupID(int i_gid, bool i_flag = false);//is include completed, default false;

    void                                    ClearAllTasks();
    void                                    EraseTaskByID(int i_id);

    void                                    SetChipLock(bool i_flag);
    bool                                    GetChipLock();

private:
    bool                                    m_TaskChipLock;
    std::vector<TravelLogDataPtr>           m_TravelLogConfigCache;
    TravelLogConfigPtr                      m_TravelLogConfigRaw;
    std::vector<TravelLogTask*>             m_TravelLogTasks;
};

#define gTravelLogManager (TravelLogManager::GetInstancePtr())

#endif