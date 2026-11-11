//
//  IntroArenaTutorialBattleModule.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-10-19.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroArenaTutorialBattleModule__
#define __PlantsVersusZombies2__IntroArenaTutorialBattleModule__

#include "StandardLevelIntro.h"
#include "UIWidget.h"
#include "ArenaInfo.h"
#include "SeedPacket.h"
#include "GridItemBrain.h"
#include "ArenaPlantModule.h"
#include "Collectable.h"
#include "ArenaPrecompile.h"
#include "ZombieAlmanac.h"

class BouncingArrow;
#define ROW_COUNT           5
#define ROW_ZOMBIE_COUNT    4

class IntroArenaTutorialBattleModule : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(IntroArenaTutorialBattleModule, StandardLevelIntro, RtClass);
    
    IntroArenaTutorialBattleModule();
    
    float        calcGoalX();
    void         SetType(ArenaPlantType i_type) {m_type = i_type;}
    ArenaPlantType GetType() { return m_type;}
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    const std::vector<ZombieRecord>& GetZombieRecords() { return m_zombieRecords; }
    
    void         SetIsPacketMoving(bool i_moving) { m_isPacketingMoving = i_moving; }
    bool         GetIsPacketMoving() { return m_isPacketingMoving; }
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual void onPostLoad() override;
    void onEndLevel();
    
    enum TutorialState
    {
        PVZ_BEGIN_ENUM(TUTORIALSTATE_),
        TUTORIALSTATE_ADVICE_1,
        TUTORIALSTATE_BATTLE,
        TUTORIALSTATE_ADVICE_2,
        
        TUTORIALSTATE_ATTACK_ADVICE_1,
        TUTORIALSTATE_ATTACK_HIGHLIGHT_ZB,
        TUTORIALSTATE_ATTACK_PLACE_ZB,
        TUTORIALSTATE_ATTACK_START,
        TUTORIALSTATE_ATTACK_ADVICE_2,
        TUTORIALSTATE_ATTACK_HIGHLIGHT_BUF,
        TUTORIALSTATE_ATTACK_USE_BUF,
        TUTORIALSTATE_ATTACK_USE_BUF_FINISH,
        TUTORIALSTATE_ATTACK_END_INTRO,
        TUTORIALSTATE_ATTACK_END,
        PVZ_END_ENUM(TUTORIALSTATE_),
    };
    
private:
    enum BattleState
    {
        PVZ_BEGIN_ENUM(BATTLESTATE_),
        BATTLE_INIT,
        BATTLE_PREPARE,
        BATTLE_OCCUPY_PREPARE,
        BATTLE_BEGIN,
        PVZ_END_ENUM(BATTLESTATE_),
    };
    
    bool        preventSave();
    
    void        levelStarted();
    void        update();
    bool        checkWin();
    
    void        addToRenderQueue(class RenderQueue* i_queue);
    
    void        onPlantLost(class Plant * i_plant);
    void        gameplayStarted();
    
    void		initStoredPlants(ArenaInfo& i_info);
    
    void        onZombiePlanted(Zombie* i_zombie);
    void        onNoticeTryUseArenaZombie(int x, int y);
    
    void        onZombieSeedPacketSelected(SeedPacket* i_packet);
    
    Sexy::Point       GetCurrentGridPosition(Sexy::Point i_location);
    
    void        onReadyForBrains();
    void        onBrainDie(GridItemBrain * i_brain);
    
    void        createBrains();
    PopAnim*    getMowerAnim();
    const std::string& getMowerAudio();
    void        onLoadComplete() override;
    void        onTriggerTimeOver();
    void        onTriggerStartTimerOver();
    void        onGameplayEnded();
    void        onPlantTryUseFood(Plant* i_plant);
    float       GetPlantFoodInterval();
    int         BoardSpaceToGridX(const float i_pixelX);
    
    bool        IsSkill(const SeedPacketPtr& packet);
    void        CancelTouch();
    bool        HandleTouch(const Sexy::Touch& i_touch);
    
    void        onCollectableTryToInstantUse(Collectable* i_collectable);
    void        onCollectableFinishCollect();
    
    void        onZombieCloseToBottomLine(Zombie* i_zombie);
    
    int         GetRandPlantfoodZombie();
    
    void        CreateZombieVanishEffect(Zombie* i_zombie);
    
    void        onZombieVanish(class StandaloneEffect* i_effect);
    void        StartMovingZombiePacket(Zombie* i_zombie);
    void        CreateZombiePacket(Zombie* i_zombie);
    
    void        onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    
    void        EndLevel();
    
    void        initPlayerInfo();
    
    void        TriggerBattleBegin();
    void        TriggerOccupyBattleBegin();
    
    void        onPVPSkillUsed(class Zombie* pSkill, int iCost);
    
    bool        m_checkCondition;
    
    RtWeakPtr<UIWidget> m_plantCountUI;
    
    SeedPacketPtr m_seedPacket;
    int         m_nBrainsRemaining;
    bool        m_triggerEnding;
    bool        m_enablePlantfood;
    pvztime_t   m_nextPlantfoodTime;
    ArenaPlantType m_type;
    CollectablePtr m_plantfood;
    PlantPtr    m_affectedPlant;
    int         m_targetPlantfoodZombie;
    int         m_currentZomibe;
    std::vector<ZombieRecord> m_zombieRecords;
    int         m_numStar;
    ArenaType   m_pvpType;
    ZombieAlmanac						m_zombieAlmanac;
    std::vector<int>					m_killedZombies;
    bool        m_isPacketingMoving;
    BattleState m_battleState;
    bool        m_occupyQuitPressed;
    
    //add for tutorial
    TutorialState                       m_tutorialstate;
    bool                                m_doTutorialFinish;
    int                                 m_addzbCount;
    int                                 m_killzbCount;
    AnimationMgrWkPtr                   m_animationMgr;
    RtWeakPtr<BouncingArrow>            m_bouncingArrow[ROW_COUNT];
    bool  m_showEndUI;
    void  setTutorialState(TutorialState tState);
    void  onAdvice1Finish();
    void  onAdvice2Finish();
    void  onEndAttack();
    
    std::vector<int>					m_addedZombies;
    
    std::vector<Zombie*>                m_useBufZombies;
    int                                 m_useBufCount;
    bool                                m_hasSkillUsed;
};

//////

class IntroArenaTutorialBattleProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(IntroArenaTutorialBattleProperties, StandardLevelIntroProperties, RtClass);
    
    IntroArenaTutorialBattleProperties()
    {
        PlantDistance = 6.0f;
        MowerEntryAnimDuration = 2.5f;
        Duration = 360.0f;
        PlantFoodIntervalMin = 25.0f;
        PlantFoodIntervalMax = 40.0f;
        PlantFoodRate = 0.5f;
        PlantFoodZombieSeed = 9;
        PrepareDuration = 30.0f;
        ChangeCurrency = 500;
    }
    
    virtual RtClass* GetModuleClass() const override
    {
        return IntroArenaTutorialBattleModule::StaticGetClass();
    }
    
    float PlantDistance;
    float			MowerEntryAnimDuration;
    std::string 	MowerPopAnim;
    std::string 	MowerActivatedAudioEvent;
    float Duration;
    float PlantFoodIntervalMin;
    float PlantFoodIntervalMax;
    float PlantFoodRate;
    int   PlantFoodZombieSeed;
    float PrepareDuration;
    int   ChangeCurrency;
};

#endif /* defined(__PlantsVersusZombies2__IntroArenaBattle__) */
