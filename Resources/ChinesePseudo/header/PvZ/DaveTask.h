#ifndef DAVETASK_H
#define DAVETASK_H

#include "Precompile.h"
#include "RtObject.h"
#include "PVZDB.h"
#include "DaveTaskConfig.h"

class LevelDefinitionForTask;

class DaveTask : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE_ABSTRACT(DaveTask, Sexy::RtObject, RtClass);
    DaveTask();
    virtual ~DaveTask();

    virtual void Init(DaveTaskDataPtr i_taskData);
    virtual void SaveState();
    virtual void LoadState();
    virtual void Destory();
    virtual void ForceSetState(int i_state);
    virtual void TaskCompleted();
    virtual time_t GetRemainTime();
    virtual void AddListener() = 0;
    virtual void RemoveListener() = 0;

//private:
    int ID;
    int GID;
    bool IsNormal;
    int TaskProgress;
    int CurrentState;
    std::string ActivityName;
    time_t CreationDate;
    DaveTaskDataPtr TaskConfig;

protected:
    bool needRemoveListener;
};

class DaveTaskPassLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPassLevel, DaveTask, RtClass);

    DaveTaskPassLevel();
    ~DaveTaskPassLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskPvP : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPvP, DaveTask, RtClass);

    DaveTaskPvP();
    ~DaveTaskPvP();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//参与1次回忆之旅
class DaveTaskPVZ1 : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPVZ1, DaveTask, RtClass);

    DaveTaskPVZ1();
    ~DaveTaskPVZ1();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//通关1次回忆之旅
class DaveTaskPassPVZ1 : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPassPVZ1, DaveTask, RtClass);

    DaveTaskPassPVZ1();
    ~DaveTaskPassPVZ1();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

//通关回忆之旅中任意关卡8次
class DaveTaskPasssManyPVZ1 : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPasssManyPVZ1, DaveTask, RtClass);

    DaveTaskPasssManyPVZ1();
    ~DaveTaskPasssManyPVZ1();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskPlantAdventure : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPlantAdventure, DaveTask, RtClass);

    DaveTaskPlantAdventure();
    ~DaveTaskPlantAdventure();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onPlantAdventureFinish(int i_worldId);
};

class DaveTaskEndless : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskEndless, DaveTask, RtClass);

    DaveTaskEndless();
    ~DaveTaskEndless();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskPassEasyLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPassEasyLevel, DaveTask, RtClass);

    DaveTaskPassEasyLevel();
    ~DaveTaskPassEasyLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskPassHardLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPassHardLevel, DaveTask, RtClass);

    DaveTaskPassHardLevel();
    ~DaveTaskPassHardLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class Zombie;
class DamageInfo;
class DaveTaskBeatBoss : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskBeatBoss, DaveTask, RtClass);

    DaveTaskBeatBoss();
    ~DaveTaskBeatBoss();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

class DaveTaskBattleZ : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskBattleZ, DaveTask, RtClass);

    DaveTaskBattleZ();
    ~DaveTaskBattleZ();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskFamilyRefresh : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskFamilyRefresh, DaveTask, RtClass);

    DaveTaskFamilyRefresh();
    ~DaveTaskFamilyRefresh();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;

};

class DaveTaskNormalDraw : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskNormalDraw, DaveTask, RtClass);

    DaveTaskNormalDraw();
    ~DaveTaskNormalDraw();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onFinishGacha(int type, int size);
};

class DaveTaskEndlessBeatBoss : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskEndlessBeatBoss, DaveTask, RtClass);

    DaveTaskEndlessBeatBoss();
    ~DaveTaskEndlessBeatBoss();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskExtinguishFire : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskExtinguishFire, DaveTask, RtClass);

    DaveTaskExtinguishFire();
    ~DaveTaskExtinguishFire();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onExtinguishFire(class Zombie* i_zombie);
};

class DaveTaskTransgenic : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskTransgenic, DaveTask, RtClass);

    DaveTaskTransgenic();
    ~DaveTaskTransgenic();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void FinishPlantTransgenic();
};

class DaveTaskPassPennyLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPassPennyLevel, DaveTask, RtClass);

    DaveTaskPassPennyLevel();
    ~DaveTaskPassPennyLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskKillZombieOnPennyLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskKillZombieOnPennyLevel, DaveTask, RtClass);

    DaveTaskKillZombieOnPennyLevel();
    ~DaveTaskKillZombieOnPennyLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

class DaveTaskObtainPennySignal : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskObtainPennySignal, DaveTask, RtClass);

    DaveTaskObtainPennySignal();
    ~DaveTaskObtainPennySignal();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onObtainPennySignal(int num);
};

class DaveTaskConsumeFuel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskConsumeFuel, DaveTask, RtClass);

    DaveTaskConsumeFuel();
    ~DaveTaskConsumeFuel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onConsumeFuel(int num);
};

class DaveTaskFinishPennyLevelBoss : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskFinishPennyLevelBoss, DaveTask, RtClass);

    DaveTaskFinishPennyLevelBoss();
    ~DaveTaskFinishPennyLevelBoss();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onSettlePennyLevel();
};

class DaveTaskWinPennyLevelBoss : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskWinPennyLevelBoss, DaveTask, RtClass);

    DaveTaskWinPennyLevelBoss();
    ~DaveTaskWinPennyLevelBoss();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onLevelEnded(LevelDefinitionForTask* i_defTask);
};

class DaveTaskObtainSunmoneyOnPennyLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskObtainSunmoneyOnPennyLevel, DaveTask, RtClass);

    DaveTaskObtainSunmoneyOnPennyLevel();
    ~DaveTaskObtainSunmoneyOnPennyLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onObtainSunmoney(class CollectableSun* i_sun);
};

class DaveTaskAddPlantOnPennyLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskAddPlantOnPennyLevel, DaveTask, RtClass);

    DaveTaskAddPlantOnPennyLevel();
    ~DaveTaskAddPlantOnPennyLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onAddPlant(class Plant* i_plant);
};

class DaveTaskPlantfoodOnPennyLevel : public DaveTask
{
public:
    RT_CLASS_DEFINE(DaveTaskPlantfoodOnPennyLevel, DaveTask, RtClass);

    DaveTaskPlantfoodOnPennyLevel();
    ~DaveTaskPlantfoodOnPennyLevel();

    virtual void Init(DaveTaskDataPtr i_taskData) override;
    virtual void AddListener() override;
    virtual void RemoveListener() override;
protected:
    void onApplyPlantfood(class Plant* i_plant);
};

#endif