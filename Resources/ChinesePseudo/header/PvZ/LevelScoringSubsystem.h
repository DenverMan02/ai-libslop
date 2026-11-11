//
//  LevelScoringSubsystem.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 2/9/16.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelScoringSubsystem__
#define __PlantsVersusZombies2__LevelScoringSubsystem__

#include "ChallengeScoringUI.h"
#include "DamageInfo.h"
#include "GameSubSystem.h"
#include "GridItemGravestone.h"
#include "LevelModule.h"

namespace Message
{
	void ScoreCalculated(int i_score, const std::string& i_ruleset, float i_bonusMultiplier);
	void ScoreUpdated(int i_score, float i_bonusMultiplier);
	
}

struct ZombossStage;

struct ScoreDisplayModifier
{
	float ScoreMultiplierMinimum = 1.0f;
	float ScoreAwardDisplayTime = 2;
	float ScoreFadeOutTime = 0.5;
	float ScoreScale = 1;
	float ScoreEndScale = 1.2;
	float ScoreZOffset = 0;
	float ScoreYVelocity = 0;
	Color ScoreColor = Color::White;
};

class LevelScoringRules : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(LevelScoringRules, ObjectTypeDescriptor, RtClass);

	// Default values
	LevelScoringRules() {}

	pvztime_t MultiplierBaseDelayToDecay = 6.0f;
	pvztime_t MultiplierBaseReductionByMultiple = 0.1f;
	pvztime_t MultiplierNextDelayToDecay = 3.0f;
	pvztime_t MultiplierNextReductionByMultiple = 0.1f;
	pvztime_t MultiplierVisibleDecayPeriod = 1.5f;
	pvztime_t MultiplierDelayToDecayMinimum = 2.0f;

	float MultiplierMaximum = 0;
	float MultiplierStart = 1;

	float MultiplierAddWeightZombieLostHelm = 0.0f;
	float ScoreValueZombieLostHelmBase = 50;
	float ScoreValueZombieHelmPer300Health = 25;
	float ScoreValueZombieLostHelmPctPerLevel = 0.2f;

	float MultiplierAddWeightGravestoneDestroyed = 1.0f;
	float GravestoneDestroyed = 200;

	float MultiplierAddWeightZombieKill = 1.0f;
	float MultiplierAddWeightZombossStageEnd = 1.0f;
	float ScoreValueZombieKillBase = 100;
	float ScoreValueZombieKillPer300Health = 100;
	float ScoreValueZombieKillPctPerLevel = 0.2f;
	float ScorePctZombieLawnmower = 1.0f;

	std::vector<ScoreDisplayModifier> ScoreDisplayModifiers = {};

	float MultiplierPlantDiedPenaltyFraction = 0.34f;
	int MultiplierPlantDiedPenaltyMinimum = 1.0f;

	float FrenzyMultiplierToActivate = 0.0f;
	float FrenzyMultiplier = 0.0f;
	float FrenzyDuration = 0.0f;
	float FrenzyCooldownDuration = 0.0f;
};

class LevelScoringSubsystem : public GameSubSystem
{
private:
	enum ScoringState
	{
		PVZ_BEGIN_ENUM(STATE_SCORING_),
		STATE_SCORING_NORMAL,
		STATE_SCORING_FRENZY,
		STATE_SCORING_FRENZY_COOLDOWN,
		PVZ_END_ENUM(STATE_SCORING_),
	};
	
public:
	RT_CLASS_DEFINE(LevelScoringSubsystem, GameSubSystem, RtClass);
	
	LevelScoringSubsystem();
	
	void Initialize(const std::string& i_scoreRulesDefinition);
	
	void Update() override;
	
	int GetCurrentScore() { return m_currentScore; }
	int GetCurrentMultiplier() { return m_currentMultiplier; }
	void ClearCurrentScore();
	void CheatAddScore(int i_delta);
	
	void SetUIVisible(bool i_visible) { m_comboMeter->SetVisible(i_visible); }
	
private:
	// Good Score Events
	void onZombieBleedingOut(Zombie *i_zombie, const DamageInfo* i_deathBlow);
	void onZombieHypnotized(Zombie *i_zombie);
	void onZombieDied(Zombie *i_zombie, const DamageInfo* i_deathBlow);
	void applyZombieDeath(Zombie *i_zombie, const DamageInfo* i_deathBlow);
	void onZombieDropArmor(Zombie *i_zombie, std::int64_t i_damageFlags);
	void onGravestoneDestroyed(GridItemGravestone* i_gravestone);
	void onZombossStageEnded(Zombie* i_zombie, int i_scoreValue);

	// Bad Score Events
	void onPlantDamageTaken(Plant* i_plant, DamageInfo& i_damageRemaining);
	void onPlantSmashedToDeath(Plant* i_plant);

	void applyZombieScore(Zombie* i_zombie, float i_score, const std::string& i_debugPrefix);
	void addToMultiplier(float i_weightedIncrease, bool i_resetDecayTimer);
	void addScore(int i_score, const std::string& i_debugPrefix);
	void showFloatingScoreIncrease(int i_score, SexyVector3 i_position, float i_bonusMultiplier);

	void doMultiplierDecay();
	void doMultiplierPenalty(float i_penaltyFraction, int i_penaltyLevelsMin);

	void onGameplayStarted();
	void onGameplayEnded();
	
	void onLastStandInit();
	void onLastStandStart();
	void startScoringSystem();

	void startFrenzy();
	void updateFrenzy();
	void updateFrenzyCooldown();
	bool isMultiplierLocked();

	Rect calculateGridFootprint(SexyVector3& i_position, Point& i_gridExtents);
	float getZombieBonusModifier(Zombie* i_zombie);
	float getBonusModifier(Rect i_searchRect);
	
	void updateUI();

	void setDecayDelayToNext();
	void setDecayDelayToBase();

	int calculateZombieValue(Zombie *i_zombie);
	int calculateZombieArmorValue(Zombie *i_zombie);
	void calculateTotalLevelBonusFactor();
	
	float getTotalMultiplierWithBonuses() { return m_currentMultiplier * m_levelBonusMultiplier; }
	
	pvztime_t			m_nextMultiplierDecrease;
	int					m_currentScore;
	int					m_currentMultiplier;
	float				m_levelBonusMultiplier;
	
	float				m_progressToNextMultiplier;
	bool				m_levelEnded;
	
	pvztime_t			m_stateStartTime;
	ScoringState		m_state;
	
	RtWeakPtr<ChallengeScoringUI> m_comboMeter;
	
	RtWeakPtr<LevelScoringRules> m_rules;

	bool 				m_waitingForLastStand;
};

class LevelScoringModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LevelScoringModule, LevelModule, RtClass);
	
	float GetPlantBonusFactor(const std::string& i_plantTypeName);
	
	int	GetTotalBonusScoringFactor();
	bool IsUsingBonusFactors();
	
	float ConvertBonusFactorToMultiplier(int i_factor);
	
	std::vector<std::string> GetBonusPlants();

protected:
	void initializeModule() override;
	
	void postInitialize() override;
};

struct LevelScoringPlantBonusTier
{
	int							Multiple;
	std::vector<std::string>	Plants;
};

class LevelScoringModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelScoringModuleProperties, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return LevelScoringModule::StaticGetClass();
	}
	LevelScoringModuleProperties()
	{
		PlantBonusMultiplier = 0.25;
	}
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	std::vector<LevelScoringPlantBonusTier>	PlantBonuses;
	float		PlantBonusMultiplier;
	
	std::string ScoringRulesType;
	int StartingPlantfood = -1;
};


#endif /* defined(__PlantsVersusZombies2__LevelScoringSubsystem__) */
