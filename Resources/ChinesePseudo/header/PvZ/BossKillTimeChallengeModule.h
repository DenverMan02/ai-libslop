//
//  BossKillTimeChallengeModule.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/8/23.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef BossKillTimeChallengeModule_h
#define BossKillTimeChallengeModule_h

#include "LevelModule.h"
#include "TimeMgr.h"
#include "StandaloneEffect.h"
#include "ActiveSummery.h"
#include "DangerRoomInfo.h"
#include "TimeChallengeEndLevelUI.h"

struct VacationMaterialItem;

//-----------------------------------------------------
// BossChallengeConfig
//-----------------------------------------------------
class BossChallengeConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(BossChallengeConfig, Sexy::RtObject, Sexy::RtClass);
    
    bool Init();
    BossChallengeConfig();
public:
    float m_fitPlantDamageRate = 0;
    float m_unFitPlantDamageRate = 0;
    PlantRestrictionSet	m_redPlants;
    PlantRestrictionSet m_bluePlants;
    PlantRestrictionSet m_electricPlants;
    PlantRestrictionSet m_purplePlant;
};

class BossKillTimeChallengeModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(BossKillTimeChallengeModule, LevelModule, RtClass);
    BossKillTimeChallengeModule();
    ~BossKillTimeChallengeModule();
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    void OnBattleEnd();
    void ShowEndLevelUI();
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
    void ShowErrorDialog(const SexyString& tip);
    void AddStorePlantGroup(std::set<std::string>& io_resGroupNames);
    void OnRequestBossChallengeLevelEnd(int result, const class S2C_BossChallengeLevelEndData* data);
    void StoreBossPostion();
    void ShowBossProgress();
    void OnErrorOK();
    void onNetworkError(int erroId, const std::string& requestID);
    void DropLoot(const VacationMaterialItem& loot);
    void DropLoot(int id, int count);
    void AddAnimationEvent(class AnimationMgr* mgr, pvztime_t* end);
    void OnCollectableTryToCollect(class Collectable* collectable);
    void OnStartGameButtonPressed();
    void KillEndLevelUI();
    void CloseBattleResult();
    void GameplayEnded();
    void OnContinue(TimeChallengeEndLevelUI* ui);
    void ShowAirShipHelth();
    std::vector<int> StoreSeedBank();
    DangerRoomPlantInfos StoredPlantInfos();
private:
    bool m_win = false;
    int m_state = 0;
    int m_score = 0;
    pvztime_t m_stateTime = 0;
    StandaloneEffectPtr m_battleResultEffect;
    BossChallengeConfig m_config;
    SexyVector3 m_bossPosition;
    TimeChallengeEndLevelUI* m_endLevelUI = nullptr;
    pvztime_t m_nextRequestTime;
    int m_requestCount;
};

class BossKillTimeChallengeProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(BossKillTimeChallengeProperties, LevelModuleProperties, RtClass);
    
    enum BattleType
    {
        Volcano = 0,
        Snow,
        Lightning,
        Purple
    };
    
    virtual RtClass* GetModuleClass() const override
    {
        return BossKillTimeChallengeModule::StaticGetClass();
    }
    
    BossKillTimeChallengeProperties();
    int LevelIndex;
    BattleType Type;
};


#endif /* BossKillTimeChallengeModule_h */
