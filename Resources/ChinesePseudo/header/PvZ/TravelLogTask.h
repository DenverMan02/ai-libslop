#ifndef TRAVELLOGTASK_H
#define TRAVELLOGTASK_H

#include "Precompile.h"
#include "RtObject.h"
#include "PVZDB.h"
#include "TravelLogConfig.h"

class LevelDefinitionForTask;

class TravelLogTask : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE_ABSTRACT(TravelLogTask, Sexy::RtObject, RtClass);
    TravelLogTask();
    virtual ~TravelLogTask();

    virtual void Init(TravelLogDataPtr i_taskData);
    virtual void SaveState();
    virtual void LoadState();
    virtual void Destory();
    virtual void TaskCompleted();
    virtual void SetTaskState(int i_state);
    virtual time_t GetRemainTime();
    virtual void AddListener() = 0;
    virtual void RemoveListener() = 0;

//private:
    int ID;
    int GID;
    int TaskProgress;
    int CurrentState;
    time_t CreationDate;
    TravelLogDataPtr TaskConfig;

protected:
    bool needRemoveListener;
};

class TravelLogTaskBattleZ : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskBattleZ, TravelLogTask, RtClass);

    TravelLogTaskBattleZ();
    ~TravelLogTaskBattleZ();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class TravelLogTaskPvP : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskPvP, TravelLogTask, RtClass);

    TravelLogTaskPvP();
    ~TravelLogTaskPvP();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//参与1次无尽挑战
class TravelLogTaskChallenge : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskChallenge, TravelLogTask, RtClass);

    TravelLogTaskChallenge();
    ~TravelLogTaskChallenge();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//参与1次潘妮追击
class TravelLogTaskPenny : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskPenny, TravelLogTask, RtClass);

    TravelLogTaskPenny();
    ~TravelLogTaskPenny();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//参与1次回忆之旅
class TravelLogTaskPVZ1 : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskPVZ1, TravelLogTask, RtClass);

    TravelLogTaskPVZ1();
    ~TravelLogTaskPVZ1();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//参与1次创意庭院
class TravelLogTaskCustomer : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskCustomer, TravelLogTask, RtClass);

    TravelLogTaskCustomer();
    ~TravelLogTaskCustomer();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class TravelLogTaskPassLevel : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskPassLevel, TravelLogTask, RtClass);

    TravelLogTaskPassLevel();
    ~TravelLogTaskPassLevel();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class TravelLogTaskPassChallenge : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskPassChallenge, TravelLogTask, RtClass);

    TravelLogTaskPassChallenge();
    ~TravelLogTaskPassChallenge();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class TravelLogTaskCollectPlantChips : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskCollectPlantChips, TravelLogTask, RtClass);

    TravelLogTaskCollectPlantChips();
    ~TravelLogTaskCollectPlantChips();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onObtainPlantChip(int i_chips);
};

class TravelLogTaskDailyIntegral : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskDailyIntegral, TravelLogTask, RtClass);

    TravelLogTaskDailyIntegral();
    ~TravelLogTaskDailyIntegral();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onObtainIntegral(int i_num);
};

class Zombie;
class DamageInfo;
class TravelLogTaskBeatZombies : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskBeatZombies, TravelLogTask, RtClass);

    TravelLogTaskBeatZombies();
    ~TravelLogTaskBeatZombies();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

class TravelLogTaskEpicTask : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskEpicTask, TravelLogTask, RtClass);

    TravelLogTaskEpicTask();
    ~TravelLogTaskEpicTask();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class TravelLogTaskWeeklyIntegral : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskWeeklyIntegral, TravelLogTask, RtClass);

    TravelLogTaskWeeklyIntegral();
    ~TravelLogTaskWeeklyIntegral();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onObtainIntegral(int i_num);
};

class TravelLogTaskWorldTask : public TravelLogTask
{
public:
    RT_CLASS_DEFINE(TravelLogTaskWorldTask, TravelLogTask, RtClass);

    TravelLogTaskWorldTask();
    ~TravelLogTaskWorldTask();

    virtual void Init(TravelLogDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
private:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

#endif