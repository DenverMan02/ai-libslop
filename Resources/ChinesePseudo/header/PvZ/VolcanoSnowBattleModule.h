//
//  VolcanoSnowBattleModule.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/7/21.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef VolcanoSnowBattleModule_h
#define VolcanoSnowBattleModule_h

#include "LevelModule.h"
#include "TimeMgr.h"
#include "StandaloneEffect.h"
#include "ActiveSummery.h"
#include "DangerRoomInfo.h"

struct VacationMaterialItem;

class VolcanoSnowBattleModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(VolcanoSnowBattleModule, LevelModule, RtClass);
    VolcanoSnowBattleModule();
    ~VolcanoSnowBattleModule();
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    void OnBattleEnd();
    bool IsFinish();
    float GetBossProgressShowTime();
protected:
    void registerForEvents() override;
    void postInitialize() override;
private:
    void Update();
    void ShowBattleResult();
    void OnLoadComplete();
    void GetBattleResultNameAndLabel(std::string& name, std::string& label);
    void OnBattleResultFinish(class StandaloneEffect* i_effect);
    void AddToRenderQueue(class RenderQueue* i_queue);
    void Draw(Graphics* i_g);
    void OnPlantAdded(class Plant* i_plant);
    void OnLevelEnded();
    void InitVolcanoBackgroundEffect();
    void InitSnowBackgroundEffect();
    void InitStoredPlants(const DangerRoomInfo& i_info);
    void InitSeedBank(const DangerRoomInfo& i_info);
    void GameplayStarted();
    void RequestBattleEnd();
    void ShowErrorDialog(const SexyString& tip);
    void AddStorePlantGroup(std::set<std::string>& io_resGroupNames);
    void OnRequestActivityLevelEnd(int result, class S2C_VacationLevelEndData* pVacationData);
    void StoreBossPostion();
    void ShowBossProgress();
    void OnErrorOK();
    void onNetworkError(int erroId);
    void DropLoot(const VacationMaterialItem& loot);
    void AddAnimationEvent(class AnimationMgr* mgr, pvztime_t* end);
    void OnCollectableTryToCollect(class Collectable* collectable);
    std::vector<int> StoreSeedBank();
    DangerRoomPlantInfos StoredPlantInfos();
private:
    int m_state;
    pvztime_t m_stateTime;
    StandaloneEffectPtr m_battleResultEffect;
    ActiveSummeryConfig m_config;
    SexyVector3 m_bossPosition;
};

class VolcanoSnowBattleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(VolcanoSnowBattleProperties, LevelModuleProperties, RtClass);
    
    enum BattleType
    {
        Volcano = 0,
        Snow
    };
    
    virtual RtClass* GetModuleClass() const override
    {
        return VolcanoSnowBattleModule::StaticGetClass();
    }
    
    VolcanoSnowBattleProperties();
    int LevelIndex;
    BattleType Type;
};


#endif /* VolcanoSnowBattleModule_h */
