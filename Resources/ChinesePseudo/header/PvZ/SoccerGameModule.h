//
//  StarChallengeModule.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SoccerChallengeModule_h
#define PlantsVersusZombies2_SoccerChallengeModule_h

#include <vector>

#include "LevelModule.h"
#include "Plant.h"
#include "Zombie.h"
#include "EffectObject.h"
#include "Projectile.h"
#include "BoardTransforms.h"
#include "WaveGeneratorModule.h"

namespace Message
{
	void NotifyLeft30Seconds();
}

class SoccerWaveGeneratorModule : public WaveGeneratorModule
{
public:
	RT_CLASS_DEFINE(SoccerWaveGeneratorModule, WaveGeneratorModule, RtClass);

protected:
	bool GetIsDoneSpawning() override;
};

class SoccerWaveGeneratorProperties : public WaveGeneratorProperties
{
public:
	RT_CLASS_DEFINE(SoccerWaveGeneratorProperties, WaveGeneratorProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return SoccerWaveGeneratorModule::StaticGetClass();
	}
};

class FootballProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(FootballProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	void onDestroy() override;
	void onInitialized() override;
};

class BoardEntity_Football : public BoardEntity
{
public:
	RT_CLASS_DEFINE(BoardEntity_Football, BoardEntity, RtClass);

	void SetShooter(PlantPtr shooter);

	void Pass(BoardEntity* passer, BoardEntity* target);

protected:
	void onInitialized() override;

	void PassToTargetDone(BoardEntity* target);
	void PassToTargetShooter(BoardEntity* target);

	void onPlantDied(Plant* plant);

protected:
	float m_flightTime;
	RtWeakPtr<Effect_PopAnim> m_football;
	PlantPtr m_shooter;
};

class SoccerGameModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(SoccerGameModule, LevelModule, RtClass);
    
    // AddResourceRequirements
    //	- Add ResourceGroup names to the array passed in, these groups
    //	will be loaded along with other level resources at Board initialization
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames);

    void GameplayStarted();
    void GameplayEnded();
    void GameplayUpdate();
    bool checkWinCondition();

    void onPlantDied(Plant* i_plant,bool bSelfKill);
    void onZombieDied(Zombie* zombie, const DamageInfo* i_deathBlow);

    bool IsCarrier(Plant* i_plant);
    void PassAndShoot(Plant* i_plant);
    void SetFootballCheckWin(FootballProjectile* football);
    void RemoveFootballCheckWin(FootballProjectile* football);
    void DoShot(const SexyVector3& i_position, BoardEntity* i_instigator);

    uint32 GetPlantScore(){ return m_PlantsScore; }
    uint32 GetZombieScore(){ return m_ZombiesScore; }

    void onUpdate();
    pvztime_t GetGameEndTime() { return m_GameEndTime; }
    void onDraw(Sexy::Graphics* i_g);
    void addToRenderQueue(class RenderQueue* i_queue);

    void CreateSoccerCursor();
protected:

	// In lieu of a constructor, you may use this function to initialize variables after
	// being added to a LevelModuleManager
	virtual void initializeModule();

	// This is your one chance to hook into LevelModuleManager callbacks!
	virtual void registerForEvents() override;

	bool CheckZombieGoal();
	bool CheckPlantGoal();

	

	bool checkDoesZombieWin(Zombie* zombie);
	void CreateDefenceEffect(bool i_zombie);

private:
	void onNotifyGameBegin();
	void OnEffectDone(class StandaloneEffect* i_effect);
	void CreateScoreText();

private:
	BoardEntityPtr m_BallCarrier;
	pvztime_t m_GameEndTime;
	uint32 m_PlantsScore;
	uint32 m_ZombiesScore;

	pvztime_t m_PassTime;

	FootballProjectile* m_footballCheckWin;
	Effect_PopAnim* m_carrierCursor;
	pvztime_t m_adviceEndTime;
	bool m_hasDisplayedAdvice;
	bool m_ballCarrierChanged;
	StandaloneEffectPtr m_defence_effect;
	bool m_hasGoal;
};

class SoccerGameModuleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(SoccerGameModuleProperties, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return SoccerGameModule::StaticGetClass();
    }
    
    SoccerGameModuleProperties(): GameTime(180.f), RoundIndex(0), ZombieWinPositionX(-80)
    {

    }
    
    pvztime_t GameTime;
    pvztime_t PassTime;
    uint32 RoundIndex;
    float ZombieWinPositionX;
};

class SoccerGameWinOutro: public OutroModule
{
public:
    RT_CLASS_DEFINE(SoccerGameWinOutro, OutroModule, RtClass);

    SoccerGameWinOutro(): PlantsScore(0), ZombiesScore(0){}

    void ShowEndLevelUI();
    void CreateGameOverEffect();
    void OnGameOverEffectDone(class StandaloneEffect* i_effect);

    void SetScore(uint32 plantsScore, uint32 zombiesScore);

    virtual void registerForEvents() override;
protected:
    uint32 PlantsScore;
    uint32 ZombiesScore;
};

class SoccerGameWinOutroProps: public OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(SoccerGameWinOutroProps, OutroModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
	{
		return SoccerGameWinOutro::StaticGetClass();
	}
};

class SoccerGameLossOutro: public OutroModule
{
public:
    RT_CLASS_DEFINE(SoccerGameLossOutro, OutroModule, RtClass);

    SoccerGameLossOutro(): PlantsScore(0), ZombiesScore(0){}

    void ShowEndLevelUI();
    void CreateGameOverEffect();
    void OnGameOverEffectDone(class StandaloneEffect* i_effect);

    void SetScore(uint32 plantsScore, uint32 zombiesScore);

    virtual void registerForEvents() override;
protected:
    uint32 PlantsScore;
    uint32 ZombiesScore;
};

class SoccerGameLossOutroProps: public OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(SoccerGameLossOutroProps, OutroModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
	{
		return SoccerGameLossOutro::StaticGetClass();
	}
};


#endif
