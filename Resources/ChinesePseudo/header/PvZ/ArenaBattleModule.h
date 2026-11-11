/*
 * ArenaBattleModule.h
 *
 *  Created on: 2015-10-12
 *      Author: jianglc
 */

#ifndef ARENABATTLEMODULE_H_
#define ARENABATTLEMODULE_H_

#include "LevelModule.h"
#include "UIWidget.h"
#include "ArenaInfo.h"
#include "SeedPacket.h"
#include "GridItemBrain.h"
#include "ArenaPlantModule.h"
#include "Collectable.h"
#include "ArenaPrecompile.h"
#include "ZombieAlmanac.h"

namespace Message
{
    void NotifyLostBrain(int i_leftBrain);
    void PVPBattleStart();
    void NotifyPlantfoodUsed(class Plant* i_plant);
}

class ArenaBattleModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(ArenaBattleModule, LevelModule, RtClass);

    ArenaBattleModule();

    float        calcGoalX();
    void         SetType(ArenaPlantType i_type) {m_type = i_type;}
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    const std::vector<ZombieRecord>& GetZombieRecords() { return m_zombieRecords; }
    int         GetNumStar() const { return m_numStar; }
    
    void         SetIsPacketMoving(bool i_moving) { m_isPacketingMoving = i_moving; }
    bool         GetIsPacketMoving() { return m_isPacketingMoving; }
    time_t       GetBattleElapseTime();
    time_t       GetBattleRemainTime();
    
    void        SetPlaybackState();
    void        UsePlantfood(Plant* i_plant);
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void onPostLoad() override;
    
    enum TutorialState
    {
        PVZ_BEGIN_ENUM(TUTORIALSTATE_),
        TUTORIALSTATE_ADVICE_1,
        TUTORIALSTATE_BATTLE,
        TUTORIALSTATE_ADVICE_2,
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
        BATTLE_Playback,
        PVZ_END_ENUM(BATTLESTATE_),
    };
    
    void        levelStarted();
    void        update();
    void        onPauseUpdate();
    bool        checkWin();

    void        onPlantLost(class Plant * i_plant);
    void        gameplayStarted();

	void		initStoredPlants(ArenaInfo& i_info);
    
    void        onNoticeTryUseArenaZombie(int x, int y);
    
    void        onZombieSeedPacketSelected(SeedPacket* i_packet);
    
    Sexy::Point       GetCurrentGridPosition(Sexy::Point i_location);
    
    void        onReadyForBrains();
    void        onBrainDie(GridItemBrain * i_brain);
    
    void        createBrains();
    PopAnim*    getMowerAnim();
    const std::string& getMowerAudio();
    void        onLoadComplete();
    void        onTriggerTimeOver();
    void        onTriggerStartTimerOver();
    void        onChangePlayerCooldownEnd();
    void        onGameplayEnded();
    void        onPlantTryUseFood(Plant* i_plant);
    float       GetPlantFoodInterval();
    int         BoardSpaceToGridX(const float i_pixelX);
    
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
    
    void        onPVPBattleEnding(bool i_success, int i_errorCode);
    void        OnCloseDialog();
    void        OnCloseStartErrorDialog();
    void        onMsgError(int erroId, const std::string& requestID);
    void        onNotifyBattleEndingNetworkError();
    
    void        TriggerBattleBegin();
    void        TriggerOccupyBattleBegin();
    void        TriggerPlaybackBegin();
    
    void        onArenaPVPButtonPressed();
    void        onArenaOccupyButtonPressed();
    
    void        onArenaStartPVPButtonPressed();
    
    void        onPVPSkillUsed(class Zombie* pSkill, int iCost);
    
    void        onBattleStart(bool i_success, int i_errorCode);
    
    void        onArenaOccupyQuitButtonPressed();
    
    void        onConfirmQuitBattle();
    void        onCancelQuitBattle();
    
    class PVZ2UIDialog* showExitMenu_Internal(SexyString i_headerLabel, SexyString i_messageBody);
    void        onArenaEndingButtonPressed();
    
    bool        IsSkill(const SeedPacketPtr& packet);
    void        AddZombie(const ZombieTypePtr& zombie, const Point& grid);
    void CancelTouch();
    bool HandleTouch(const Sexy::Touch& i_touch);
    void onPingSuccess(bool timeout);
    void onTimeOutOk();
    bool LostAllZombie();
    bool PingTimeout();
    int  CalcLostZombieCost();
    int  CheckEndStars();
    
    bool        m_checkCondition;

    RtWeakPtr<UIWidget> m_plantCountUI;
    
    SeedPacketPtr m_seedPacket;
    int         m_nBrainsRemaining;
    bool        m_triggerEnding;
    bool        m_enablePlantfood;
    pvztime_t   m_nextPlantfoodTime;
    pvztime_t  m_nextPing;
    pvztime_t m_lastPingSuccess;
    ArenaPlantType m_type;
    CollectablePtr m_plantfood;
    PlantPtr    m_affectedPlant;
    int         m_targetPlantfoodZombie;
    int         m_currentZomibe;
    std::vector<ZombieRecord> m_zombieRecords;
    std::vector<PvpPlantLostRecord> m_plantRecords;
    int         m_numStar;
    ArenaType   m_pvpType;
    ZombieAlmanac						m_zombieAlmanac;
    std::vector<int>					m_killedZombies;
    bool        m_isPacketingMoving;
    BattleState m_battleState;
    bool        m_occupyQuitPressed;
    bool        m_surrender;
    
    //add for tutorial
    TutorialState m_tutorialstate;
    bool          m_doTutorialFinish;
    int   m_addzbCount;
    int   m_killzbCount;
    void  setTutorialState(TutorialState tState);
    void  onAdvice1Finish();
    void  onAdvice2Finish();
    
    
    // for playback
public:
    void            UsePlantfoodForPlayback(Plant* i_plant);
protected:
    void            onPlantfoodSpawned(class CollectablePlantfood* i_plantfood);
protected:
    std::vector<CollectablePtr>     m_plantfoodCaches;
};

class ArenaBattleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ArenaBattleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return ArenaBattleModule::StaticGetClass();
	}

	ArenaBattleProperties()
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


#endif /* ARENABATTLEMODULE_H_ */
