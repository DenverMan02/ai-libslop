//
//  CannonMinigame.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CannonMinigame_h
#define PlantsVersusZombies2_CannonMinigame_h

#include "IntroModule.h"
#include "Core.h"
#include "Zombie.h"
#include "GridItem.h"
#include "AnimationMgr.h"
#include "BSpline.h"
#include "TimeLine.h"

#ifndef RELEASEFINAL
#define CANNON_EDITOR_ENABLED
#endif

struct PirateLane
{
	std::vector<SexyVector2>	SplinePoints;
};

struct ComboBracket
{
	int 	ZombiesKilled;
	float 	ScoreMultiplier;
	Color	MessageColor;
	std::string AudioCue;
	std::vector<std::string> Exclamations;
};

class CannonMinigameModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CannonMinigameModule, LevelModule, RtClass) {}

	virtual ~CannonMinigameModule();
	
protected:
	virtual void					initializeModule() override;
	virtual void					registerForEvents() override;
	
private:
	enum CannonMinigameState
	{
		CMS_BeforeGameplay,
		CMS_Gameplay,
		CMS_Outro,
        CMS_Failed,
		CMS_DONE
	};

	struct TargetListEntry
	{
		ZombiePtr zombie;
		float progress;
	};
	
	void onUpdate();
	void onEndLevel();
	
	bool canLevelEnd();
    void LevelEnded();
    void PlayerLost();

	void onLoadComplete();
	void onGameplayStarted();
	void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onZombieDestroyed(Zombie* i_zombie);
    void onZombieSpawned(Zombie* i_zombien);
    
	void updateGameplay();
	void updateScoreboard();
	
	void updateOutro();

	bool preventSave();
	
	void setState(CannonMinigameState i_newState);
	
	bool moveZombieCongaStyle(int i_laneIdx, int i_zombieIdx, float i_progress);
	void updateCongaLine();
	
	void cullDeadZombiesFromList();
	
	void buildAllSplines();
    
//PVZ2_CHINESE_BEGIN
	SexyString getComboText(int i_comboAmount);
	SexyString getExclamationText(const ComboBracket& i_bracket);
//PVZ2_CHINESE_END    
    
	
	void startOutro();
	
	int calcCoinReward(int i_score);
	void spewGoldCoin(pvztime_t i_atTime);
	void spewSilverCoin(pvztime_t i_atTime);
	
	struct LaneData
	{
		LaneData()
		{
#ifdef CANNON_EDITOR_ENABLED
			SelectedIndex = -1;
#endif
			SplineLength = 0.f;
		}
		
		void RebuildSpline();
		
		std::vector<SexyVector2>	SplinePoints;
		std::vector<SexyVector2>	SubdividedSpline;
		std::vector<TargetListEntry>	TargetList;
		float						SplineLength;
		
#ifdef CANNON_EDITOR_ENABLED
		// Editor functionality
		void AddPoint(const SexyVector2& i_loc);
		void Select(int i_idx);
		void MoveCurrent(const SexyVector2& i_newLoc);
		void DeleteCurrent();
		void SplitBeforeCurrent();
		
		int							SelectedIndex;
#endif
	};
	
	CannonMinigameState				m_state;
	
	// Lane data
	std::vector<LaneData>			m_lanes;
	
	// Combo / scoring data
	std::vector<ZombiePtr>			m_zombiesKilledSinceLastUpdate;
	int								m_score;
	
	int								m_zombiesSpawned;
	int								m_zombiesKilled;
	
	// Persistent UI
	RtWeakPtr<class Effect_FloatingText>	m_scoreDisplay;
	RtWeakPtr<class Effect_FloatingText>	m_minScoreDisplay;
	pvztime_t 			m_lastScoreChangeTime;
	float 				m_scoreBounceScale;
	int 				m_displayedScore;
    
	
	// Outro
	pvztime_t						m_outroStartTime;
	pvztime_t						m_outroEndTime;
	TimeLine 						m_rewardCoinSpewTimeline;
	TimeLineTrack<int>				m_outroScoreValue;
	TimeLineTrack<SexyVector3> 		m_outroScorePosition;		// Using 'z' value for scale
	TimeLineTrack<SexyVector3>		m_outroMinScorePosition;
    bool                            m_playerLost;

	
#ifdef CANNON_EDITOR_ENABLED
	// Editor functionality
	void	setEditorMode(bool i_editorMode);
	void	saveCurrentSplines();
	
	void	handleTouchDown(int i_screenX, int i_screenY);
	void	handleTouchMoved(int i_screenX, int i_screenY);
	void	handleTouchUp(int i_screenX, int i_screenY);
	bool	onTouchEvent(const Sexy::Touch& i_touch);
	
	void	onSaveButtonYes();
	void	onSaveButtonNo();
	
	bool	m_inEditorMode;
	bool 	m_movingPoint;
	int		m_selectedLaneIndex;
#endif
	
};

class CannonMinigameProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CannonMinigameProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return CannonMinigameModule::StaticGetClass();
	}
	
	CannonMinigameProperties()
	{
		BaseMovementRate = 60.f;
		SlowdownMovementRate = 20.f;
		
		BufferDistance = 50.f;
		
		MinRewardGold = 10;
		MaxRewardGold = 300;
        
        MinScore = 0;
        BaseZombieKillScore = 0;
        
		ZombiesCanWin = false;
	}
	
	float	BaseMovementRate;
	float	SlowdownMovementRate;
	
	float 	BufferDistance;
	
	// Setup
	std::vector<PirateLane> Lanes;
	std::vector<int>		RowHasCannon;
	bool					ZombiesCanWin;
	
	// Scoring and Combo data
	std::vector<ComboBracket> ComboBrackets;
	int						BaseZombieKillScore;
	int						MinRewardGold;
	int						MaxRewardGold;
    int                     MinScore;
};

#endif
