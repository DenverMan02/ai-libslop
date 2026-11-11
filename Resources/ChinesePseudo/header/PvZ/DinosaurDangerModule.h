//
//  DinosaurDangerModule.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16/12/06.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DinosaurDangerModule_h
#define DinosaurDangerModule_h

#include "LevelModule.h"
#include "TimeMgr.h"
#include "StandaloneEffect.h"
#include "ActiveSummery.h"
#include "DangerRoomInfo.h"
#include "TimeChallengeEndLevelUI.h"

class DinosaurDangerModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(DinosaurDangerModule, LevelModule, RtClass);
    DinosaurDangerModule();
    ~DinosaurDangerModule();
    
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    void onShowEndLevelUI();
    
    void OnCollectableTryToCollect(class Collectable* i_collectable);
    void onZombieDropLoot(Zombie* i_zombie);
    
    static bool IsInDinosaurDangerBattle();
    
protected:
    void registerForEvents() override;
    void postInitialize() override;
    
private:
    void Update();
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
    void OnRequestDinosaurDangerEnd(int result);
    void StoreBossPostion();
    void ShowBossProgress();
    void OnErrorOK();

    void OnStartGameButtonPressed();
    void KillEndLevelUI();
    void GameplayEnded();
    void OnContinue(TimeChallengeEndLevelUI* ui);
    void ShowAirShipHelth();
    std::vector<int> StoreSeedBank();
    DangerRoomPlantInfos StoredPlantInfos();
private:
    int mSmallDropCount = 0;
    int mBigDropCount = 0;
    
};

class DinosaurDangerProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(DinosaurDangerProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return DinosaurDangerModule::StaticGetClass();
    }
    
    DinosaurDangerProperties();
    int BigPak;
    int SmallPak;
};


#endif /* DinosaurDangerModule_h */
