//
//  WhackAMoleModule.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WhackAMoleModule_h
#define PlantsVersusZombies2_WhackAMoleModule_h

#include <vector>

#include "LevelModule.h"
#include "Plant.h"
#include "Zombie.h"
#include "EffectObject.h"
#include "BoardTransforms.h"
#include "WaveGeneratorModule.h"
#include "IntrosWhackAMole.h"
#include "OutroModule.h"
#include "TimeChallengeEndLevelUI.h"

enum prop_type{
    prop_normal,
    prop_coin,
    prop_gem,
};

enum ContinuityHit_state
{
	state_NoCombo,
    state_InCombo
};

class WhackAMoleWaveGeneratorModule : public WaveGeneratorModule
{
public:
	RT_CLASS_DEFINE(WhackAMoleWaveGeneratorModule, WaveGeneratorModule, RtClass);
};

class WhackAMoleWaveGeneratorProperties : public WaveGeneratorProperties
{
public:
	RT_CLASS_DEFINE(WhackAMoleWaveGeneratorProperties, WaveGeneratorProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return WhackAMoleWaveGeneratorProperties::StaticGetClass();
	}
};

class Effect_HammerEffect: public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_HammerEffect, Effect_PopAnim, RtClass);
    void Destroy() override;
protected:
    
	void onAnimStopped(const std::string& i_animLabel) override;
};

class WhackAMoleModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(WhackAMoleModule, LevelModule, RtClass);
    
    // AddResourceRequirements
    //	- Add ResourceGroup names to the array passed in, these groups
    //	will be loaded along with other level resources at Board initialization
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames);

    void GameplayStarted();
    void GameplayEnded();
    void GameplayUpdate();

    bool checkWinCondition();

    uint32 GetScore(){ return m_Score; }

    void onUpdate();


    bool         handleTouch(const Sexy::Touch& i_touch);
	void         cancelTouch();
    void        SetCanTouch(bool i_canTouch);

    void    handleTouchDown(int i_screenX, int i_screenY);
    void calcScore(MoleType type);
    void updateTargetScore(uint32 targetSocre);
    void CreateHammerUI();
    void ShowEndLevelUI();

    void DoThrowSkiTools(int splatPosX, int splatPosY);

    void CreateContinuityHitNum();

    void PlayerLost();

    void  useGemFinish(bool isSuccess, prop_type type);

    bool getIsGameStarted() const { return m_bIsGameStarted; };

    void useGemFinishIOS(const bool& i_Success);

    float getContinuityHitAddition();

    void onDraw(Sexy::Graphics* i_g);
    void addToRenderQueue(class RenderQueue* i_queue);
    void    onAnimStopped(const std::string &i_animName);

    void UpdateWhackAMoleBehaviorEventLog(bool isWin);
protected:

	// In lieu of a constructor, you may use this function to initialize variables after
	// being added to a LevelModuleManager
	virtual void initializeModule();

	// This is your one chance to hook into LevelModuleManager callbacks!
	virtual void registerForEvents() override;

    void onPropTouch(const int i_type);

    void OnContinue(TimeChallengeEndLevelUI* ui);
    void KillEndLevelUI();
	
private:
	void onNotifyGameBegin();

private:
	pvztime_t m_GameEndTime;
	uint32 m_Score;

	pvztime_t m_PassTime;
	pvztime_t m_propLastTime;
	bool m_hasDisplayedAdvice;

    // Sexy::TouchID m_touchIdent;
	SexyVector2   m_touchStart;
    bool          m_touchIsMove;
    bool          m_bCanTouch;

    prop_type m_curPropType;
    TimeChallengeEndLevelUI* m_endLevelUI;

    class WhackAMoleUI *m_pCoin_Hammer;
    class WhackAMoleUI *m_pGem_Hammer;

    class Effect_HammerEffect* m_pHammerEffect;

    int m_nContinuityHitNum;
    ContinuityHit_state m_ContinuityHitState;
    pvztime_t m_ContinuityHitTime;

    class Effect_FloatingText* m_pContinuityHitText;

    RtWeakPtr<class Effect_FloatingText>	m_scoreDisplay;
	RtWeakPtr<class Effect_FloatingText>	m_minScoreDisplay;

    bool m_bIsGameStarted;
    class UISteamMiniGameScore* m_pScore;

    bool m_bIsRandom;
private:
    int m_nGemHammerUseTimes;
    int m_nCoinhammerUseTimes;
};

class WhackAMoleModuleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(WhackAMoleModuleProperties, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return WhackAMoleModule::StaticGetClass();
    }
    
    WhackAMoleModuleProperties(): GameTime(180.f), RoundIndex(0), ZombieWinPositionX(-80)
    ,MinWinScore(1000), OneScore(500), ContinuityHitLastTime(5.0f), HardLevelMinWinScore(1000)
    {

    }
    
    pvztime_t GameTime;
    pvztime_t PassTime;
    uint32 RoundIndex;
    float ZombieWinPositionX;
    float CoinHammerLastTime;
    float GemHammerLastTime;
    uint32 MinWinScore;
    uint32 HardLevelMinWinScore;
    uint32 OneScore;
    uint32  CoinHammerCost;
    uint32  GemHammerCost;
    float ContinuityHitLastTime;
};

class WhackAMoleWinOutro: public OutroModule
{
public:
    RT_CLASS_DEFINE(WhackAMoleWinOutro, OutroModule, RtClass);

    WhackAMoleWinOutro(): m_Score(0) {}

    void ShowEndLevelUI();

    void SetScore(int score);

    virtual void registerForEvents() override;
protected:
    uint32 m_Score;
};

class WhackAMoleWinOutroProps: public OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(WhackAMoleWinOutroProps, OutroModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
	{
		return WhackAMoleWinOutro::StaticGetClass();
	}
};

class WhackAMoleLossOutro: public OutroModule
{
public:
    RT_CLASS_DEFINE(WhackAMoleLossOutro, OutroModule, RtClass);

    WhackAMoleLossOutro(): m_Score(0) {}

    void ShowEndLevelUI();

    void SetScore(uint32 score);

    virtual void registerForEvents() override;
protected:
    uint32 m_Score;
};

class WhackAMoleLossOutroProps: public OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(WhackAMoleLossOutroProps, OutroModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
	{
		return WhackAMoleLossOutro::StaticGetClass();
	}
};


namespace Message {
    void PropTouch(const int i_type);
}


#endif
